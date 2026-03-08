#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.9"
# dependencies = ["pyusb"]
# ///
"""usb_diag.py — Host-side tool for the MSM8909 USB diagnostic console.

Connects to the minimal programmer's diagnostic mode over USB bulk
and provides an interactive terminal.

Usage:
    uv run tools/usb_diag.py                          # interactive mode
    uv run tools/usb_diag.py -c "i"                   # single command
    uv run tools/usb_diag.py --flash tmp/minimal.elf  # upload + connect

macOS: install libusb via Homebrew, then run without sudo:
    brew install libusb

Linux: install udev rules once (needs sudo), then run without sudo:
    sudo tools/usb_diag.py --install-udev
"""

import sys
import os
import struct
import time
import argparse
import usb.core
import usb.util

UDEV_RULES_PATH = "/etc/udev/rules.d/99-qc-edl.rules"
UDEV_RULES = """\
# Qualcomm EDL (Emergency Download) / Sahara / Diag — 05c6:9008
SUBSYSTEM=="usb", ATTR{idVendor}=="05c6", ATTR{idProduct}=="9008", MODE="0666", TAG+="uaccess"
"""


def install_udev_rules():
    """Write udev rules for passwordless USB access and reload udevadm."""
    if os.geteuid() != 0:
        print("Error: --install-udev requires root (run with sudo).", file=sys.stderr)
        sys.exit(1)
    with open(UDEV_RULES_PATH, "w") as f:
        f.write(UDEV_RULES)
    print(f"Written: {UDEV_RULES_PATH}")
    os.system("udevadm control --reload-rules && udevadm trigger")
    print("udev rules reloaded. Reconnect the device if already plugged in.")
    print("You can now run this tool without sudo.")

# Device VID/PID — our programmer keeps PBL's identity (05C6:9008)
# so the host handle survives the brief controller stop→start.
DEVICE_VID = 0x05C6
DEVICE_PID = 0x9008
EP_OUT     = 0x01  # Endpoint 1 OUT (host → device)
EP_IN      = 0x81  # Endpoint 1 IN  (device → host)

# Sahara command IDs
SAHARA_HELLO       = 0x01
SAHARA_HELLO_RESP  = 0x02
SAHARA_READ_DATA   = 0x03
SAHARA_END_IMAGE   = 0x04
SAHARA_DONE        = 0x05
SAHARA_DONE_RESP   = 0x06
SAHARA_RESET       = 0x09
SAHARA_CMD_READY   = 0x0b
SAHARA_SWITCH_MODE = 0x0c

# Sahara modes
SAHARA_MODE_IMAGE_TX = 0x00
SAHARA_MODE_COMMAND  = 0x03


# ==========================================================================
# Sahara uploader
# ==========================================================================

def sahara_find(timeout=10):
    """Wait for a Sahara (EDL) device to appear."""
    print(f"Waiting for Sahara device {DEVICE_VID:04x}:{DEVICE_PID:04x}...",
          end="", flush=True)
    deadline = time.time() + timeout
    while time.time() < deadline:
        dev = usb.core.find(idVendor=DEVICE_VID, idProduct=DEVICE_PID)
        if dev is not None:
            print(" found!")
            return dev
        print(".", end="", flush=True)
        time.sleep(0.5)
    print(" timeout!")
    return None


def sahara_upload(elf_path, timeout=10):
    """Upload an ELF programmer to the device via Sahara protocol.

    Returns the open USB device handle (programmer is now executing).
    The caller owns the handle and must not release it — the programmer
    inherits the live USB session, so disconnecting would kill it.
    Raises on error.
    """
    dev = sahara_find(timeout=timeout)
    if dev is None:
        raise RuntimeError("Sahara device not found")

    try:
        if dev.is_kernel_driver_active(0):
            dev.detach_kernel_driver(0)
    except (usb.core.USBError, NotImplementedError):
        pass
    try:
        dev.set_configuration()
    except usb.core.USBError:
        pass  # macOS: device already configured by the OS
    usb.util.claim_interface(dev, 0)

    with open(elf_path, "rb") as f:
        image = f.read()
    print(f"Programmer: {elf_path} ({len(image)} bytes)")

    SAHARA_CMD_NAMES = {
        0x01: "HELLO", 0x02: "HELLO_RESP", 0x03: "READ_DATA", 0x04: "END_IMAGE",
        0x05: "DONE", 0x06: "DONE_RESP", 0x09: "RESET", 0x0a: "RESET_RESP",
        0x0b: "CMD_READY", 0x0c: "SWITCH_MODE",
    }

    def recv(timeout_ms=5000):
        data = bytes(dev.read(EP_IN, 8192, timeout=timeout_ms))
        if len(data) >= 4:
            cmd = struct.unpack_from("<I", data)[0]
            name = SAHARA_CMD_NAMES.get(cmd, f"cmd={cmd:#x}")
            print(f"[sahara] rx {len(data):3d}b  {name}  {data.hex()}")
        return data

    def send(data):
        if len(data) >= 4:
            cmd = struct.unpack_from("<I", data)[0]
            name = SAHARA_CMD_NAMES.get(cmd, f"cmd={cmd:#x}")
            print(f"[sahara] tx {len(data):3d}b  {name}  {data.hex()}")
        dev.write(EP_OUT, data)

    def make_hello_resp(version, compat, pkt_len, mode):
        fixed = struct.pack("<IIIIII", SAHARA_HELLO_RESP, pkt_len,
                            version, compat, 0, mode)
        return fixed + b"\x00" * max(0, pkt_len - len(fixed))

    # --- Hello + SWITCH_MODE dance (matches Go tool exactly) ---
    # 1. Recv HELLO (mode=0)
    pkt = recv()
    cmd, pktlen = struct.unpack_from("<II", pkt)
    if cmd != SAHARA_HELLO:
        raise RuntimeError(f"Expected HELLO (0x01), got {cmd:#x}")
    dev_version, dev_compat, dev_maxpkt, dev_mode = struct.unpack_from("<IIII", pkt, 8)
    print(f"  Sahara HELLO: version={dev_version} compat={dev_compat} maxpkt={dev_maxpkt:#x} mode={dev_mode}")

    # 2. Send HELLO_RESP requesting COMMAND mode (mode=3).
    #    With mode=0 (IMAGE_TX), the PBL starts READ_DATA immediately but
    #    then ignores DONE after transfer. The Go tool enters COMMAND mode
    #    first, then switches back — this makes DONE work.
    send(make_hello_resp(dev_version, dev_compat, pktlen, SAHARA_MODE_COMMAND))

    # 3. Recv CMD_READY (0x0b)
    pkt = recv()
    cmd2 = struct.unpack_from("<I", pkt)[0]
    if cmd2 != SAHARA_CMD_READY:
        raise RuntimeError(f"Expected CMD_READY (0x0b), got {cmd2:#x}")
    print("  CMD_READY received")

    # 4. Send SWITCH_MODE → mode=3 (same value the Go tool uses on the wire)
    send(struct.pack("<III", SAHARA_SWITCH_MODE, 12, SAHARA_MODE_COMMAND))

    # 5. Recv second HELLO (mode=3)
    pkt = recv()
    cmd, pktlen = struct.unpack_from("<II", pkt)
    if cmd != SAHARA_HELLO:
        raise RuntimeError(f"Expected HELLO after SWITCH_MODE, got {cmd:#x}")
    dev_version, dev_compat, dev_maxpkt, dev_mode = struct.unpack_from("<IIII", pkt, 8)
    print(f"  Sahara HELLO (post-switch): version={dev_version} mode={dev_mode}")

    # 6. Send HELLO_RESP with mode=0 (IMAGE_TX) — NOT echoing mode=3.
    #    Echoing mode=3 re-enters command mode (CMD_READY loop).
    #    The Go tool sends SWITCH_MODE(3) then HELLO_RESP(0) to start transfer.
    send(make_hello_resp(dev_version, dev_compat, pktlen, SAHARA_MODE_IMAGE_TX))

    # --- Image transfer loop ---
    while True:
        pkt = recv()
        if len(pkt) < 8:
            raise RuntimeError(f"Short Sahara packet: {pkt.hex()}")
        cmd, pktlen = struct.unpack_from("<II", pkt)

        if cmd == SAHARA_READ_DATA:
            image_id, offset, length = struct.unpack_from("<III", pkt, 8)
            chunk = image[offset:offset + length]
            if len(chunk) == 0:
                raise RuntimeError(f"ReadData beyond image: offset={offset:#x} len={length:#x}")
            print(f"[sahara] tx {len(chunk):5d}b  data  image[{offset:#x}:{offset+length:#x}]")
            dev.write(EP_OUT, chunk)

        elif cmd == SAHARA_END_IMAGE:
            image_id, status = struct.unpack_from("<II", pkt, 8)
            if status != 0:
                raise RuntimeError(f"EndImageTx error status={status:#x}")
            print(f"  Image transfer complete (image_id={image_id})")
            send(struct.pack("<II", SAHARA_DONE, 8))
            # Expect DONE_RESP or second END_IMAGE confirming execution
            pkt2 = recv()
            cmd2 = struct.unpack_from("<I", pkt2)[0]
            if cmd2 == SAHARA_DONE_RESP:
                print(f"  Programmer launched (DONE_RESP)")
            elif cmd2 == SAHARA_END_IMAGE:
                _, exec_status = struct.unpack_from("<II", pkt2, 8)
                print(f"  Programmer launched (exec status={exec_status})")
            else:
                print(f"  Post-DONE response: {pkt2.hex()}")
            break

        else:
            raise RuntimeError(f"Unexpected Sahara command {cmd:#x}: {pkt.hex()}")

    # Keep the SAME USB handle — do NOT release it.
    # The original firehose programmer works the same way: the Go client
    # (client/sahara/sahara.go) sends DONE_RSP then sleeps 1.5s, then
    # starts firehose XML on the same device handle.  No reconnect.
    #
    # The programmer takes ~2s to boot (entry.S: DDR init with brief
    # 50ms LED pulses, then main→usb_init→usb_poll).  We sleep 3s
    # for margin, then the first host read will trigger enumeration
    # (SET_CONFIGURATION) which makes the programmer go online.
    print("Sahara upload complete — waiting for programmer to boot...")
    return dev


# ==========================================================================
# Diag device
# ==========================================================================

def find_device(timeout=30, vid=DEVICE_VID, pid=DEVICE_PID):
    """Wait for the diagnostic device to appear."""
    print(f"Waiting for diag device {vid:04x}:{pid:04x}...",
          end="", flush=True)
    deadline = time.time() + timeout
    while time.time() < deadline:
        dev = usb.core.find(idVendor=vid, idProduct=pid)
        if dev is not None:
            print(" found!")
            return dev
        print(".", end="", flush=True)
        time.sleep(0.5)
    print(" timeout!")
    return None


def setup_device(dev, set_config=True):
    """Configure the USB device for communication."""
    try:
        if dev.is_kernel_driver_active(0):
            dev.detach_kernel_driver(0)
    except (usb.core.USBError, NotImplementedError):
        pass
    if set_config:
        try:
            dev.set_configuration()
        except usb.core.USBError:
            pass  # macOS: device already configured by the OS
    usb.util.claim_interface(dev, 0)
    return dev


def read_response(dev, timeout=2000, follow_timeout=500):
    """Read all available data from the device.

    After the first chunk arrives, keep reading with a shorter timeout
    (follow_timeout) to catch multi-write responses from the device.
    """
    data = b""
    cur_timeout = timeout
    while True:
        try:
            chunk = dev.read(EP_IN, 4096, timeout=cur_timeout)
            data += bytes(chunk)
            # After first data, use shorter timeout for follow-up chunks
            cur_timeout = follow_timeout
        except usb.core.USBTimeoutError:
            break
        except usb.core.USBError as e:
            if "timeout" in str(e).lower():
                break
            raise
    return data


def send_command(dev, cmd):
    """Send a command and return the response."""
    dev.write(EP_OUT, (cmd + "\n").encode())
    time.sleep(0.05)
    return read_response(dev)


def write_image(dev, image_path, start_sector):
    """Write a binary image to eMMC via bulk write command (W).

    1. Read file, pad to 512-byte boundary
    2. Send 'W sector count' command
    3. Wait for READY response
    4. Send raw data in USB chunks
    5. Wait for OK response
    """
    with open(image_path, "rb") as f:
        data = f.read()

    # Pad to 512-byte sector boundary
    pad = (512 - (len(data) % 512)) % 512
    if pad:
        data += b"\x00" * pad
    count = len(data) // 512

    print(f"Writing {image_path}: {len(data)} bytes ({count} sectors) at sector 0x{start_sector:x}")

    # Send W command
    cmd = f"W {start_sector:x} {count:x}\n"
    dev.write(EP_OUT, cmd.encode())

    # Wait for READY
    resp = read_response(dev, timeout=5000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")
    if not resp_str.startswith("READY"):
        raise RuntimeError(f"Expected READY, got: {resp_str}")

    # Send raw data in 4096-byte USB chunks
    chunk_size = 4096
    sent = 0
    while sent < len(data):
        end = min(sent + chunk_size, len(data))
        dev.write(EP_OUT, data[sent:end])
        sent = end
    print(f"  Sent {sent} bytes")

    # Wait for OK
    resp = read_response(dev, timeout=30000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")
    if not resp_str.startswith("OK"):
        raise RuntimeError(f"Write failed: {resp_str}")
    print("Write complete.")


def interactive_mode(dev, vid=DEVICE_VID, pid=DEVICE_PID):
    """Interactive terminal mode."""
    try:
        banner = read_response(dev, timeout=1000)
        if banner:
            sys.stdout.write(banner.decode("ascii", errors="replace"))
            sys.stdout.flush()
    except Exception:
        pass

    while True:
        try:
            line = input()
        except (EOFError, KeyboardInterrupt):
            print("\nBye.")
            break

        if line.strip().lower() in ("quit", "exit", "q"):
            break

        try:
            resp = send_command(dev, line)
            if resp:
                sys.stdout.write(resp.decode("ascii", errors="replace"))
                sys.stdout.flush()
        except usb.core.USBError as e:
            print(f"[USB error: {e}]")
            try:
                dev2 = find_device(timeout=10, vid=vid, pid=pid)
                if dev2:
                    dev = setup_device(dev2)
                    print("[reconnected]")
                else:
                    print("[device lost]")
                    break
            except usb.core.USBError as e2:
                print(f"[reconnect failed: {e2}]")
                break


def main():
    parser = argparse.ArgumentParser(description="MSM8909 USB diagnostic console")
    parser.add_argument("-c", "--command", help="Execute a single command and exit")
    parser.add_argument("-t", "--timeout", type=int, default=30,
                        help="Diag device discovery timeout (seconds)")
    parser.add_argument("--flash", metavar="ELF",
                        help="Upload programmer ELF via Sahara then connect")
    parser.add_argument("--sahara-timeout", type=int, default=10,
                        help="Sahara device discovery timeout (seconds)")
    parser.add_argument("--write-aboot", metavar="FILE",
                        help="Write binary image to aboot partition (sector 0x280C00)")
    parser.add_argument("--install-udev", action="store_true",
                        help=f"Install udev rules to {UDEV_RULES_PATH} (needs sudo)")
    args = parser.parse_args()

    if args.install_udev:
        install_udev_rules()
        return

    vid, pid = DEVICE_VID, DEVICE_PID
    dev = None
    if args.flash:
        try:
            dev = sahara_upload(args.flash, timeout=args.sahara_timeout)
        except RuntimeError as e:
            print(f"Sahara upload failed: {e}", file=sys.stderr)
            sys.exit(1)
        # Match Go client: sleep then try same handle.
        # The programmer does BCR reset (PHY keeps D+ up), then re-enumerates.
        # The OS may or may not invalidate the old handle depending on
        # whether it detected a brief disconnect during BCR.
        print("Programmer running — waiting 3s for boot + enumeration...")
        time.sleep(3)

        # Try the Sahara handle first (like Go client does)
        handle_ok = False
        try:
            dev.write(EP_OUT, b"\n")
            resp = bytes(dev.read(EP_IN, 4096, timeout=2000))
            if resp:
                handle_ok = True
                print("Sahara handle alive — reusing.")
        except usb.core.USBError:
            pass

        if not handle_ok:
            # Handle died (ENODEV) — find the re-enumerated device
            print("Sahara handle stale — reconnecting...")
            try:
                usb.util.release_interface(dev, 0)
                usb.util.dispose_resources(dev)
            except Exception:
                pass
            dev = find_device(timeout=args.timeout, vid=vid, pid=pid)
            if dev is None:
                print("Device not found after reconnect.", file=sys.stderr)
                sys.exit(1)
            dev = setup_device(dev)

    if dev is None:
        dev = find_device(timeout=args.timeout, vid=vid, pid=pid)
        if dev is None:
            print("Device not found. Is the programmer running?", file=sys.stderr)
            sys.exit(1)
        dev = setup_device(dev)

    try:
        mfg = dev.manufacturer
        prod = dev.product
        print(f"Connected: {mfg} {prod}")
    except (ValueError, usb.core.USBError):
        print("Connected (string descriptors unavailable)")

    if args.write_aboot:
        # Init eMMC first, then write
        print("Initializing eMMC...")
        resp = send_command(dev, "e")
        if resp:
            sys.stdout.write(resp.decode("ascii", errors="replace"))
            sys.stdout.flush()
        write_image(dev, args.write_aboot, 0x280C00)
    elif args.command:
        resp = send_command(dev, args.command)
        if resp:
            sys.stdout.write(resp.decode("ascii", errors="replace"))
    else:
        interactive_mode(dev, vid=vid, pid=pid)


if __name__ == "__main__":
    main()
