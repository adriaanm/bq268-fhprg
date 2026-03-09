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
import hashlib
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


def read_gpt(dev):
    """Read GPT partition table from device.

    Sends 'G' command, parses response lines until 'END'.
    Returns dict: { "aboot": (start_sector, count, attrs), ... }
    attrs is 0 if not present in output.
    """
    dev.write(EP_OUT, b"G\n")
    time.sleep(0.1)
    resp = read_response(dev, timeout=5000)
    text = resp.decode("ascii", errors="replace")

    partitions = {}
    for line in text.strip().split("\n"):
        line = line.strip()
        if line == "END":
            break
        if line.startswith("ERR"):
            raise RuntimeError(f"GPT read failed: {line}")
        parts = line.split()
        if len(parts) >= 3:
            name = parts[0]
            start = int(parts[1], 16)
            sectors = int(parts[2], 16)
            attrs = int(parts[3], 16) if len(parts) >= 4 else 0
            partitions[name] = (start, sectors, attrs)
    return partitions


def flash_partition(dev, image_path, partition_name):
    """Verified flash: upload image, SHA256 verify transfer, write+readback verify.

    1. Read GPT to get partition start/size
    2. Read binary, zero-pad to partition size
    3. Send 'F name', wait for READY
    4. Send raw data, wait for SHA256
    5. Compare SHA256, send CONFIRM
    6. Wait for DONE + readback SHA256
    """
    print(f"Reading GPT...")
    gpt = read_gpt(dev)
    if partition_name not in gpt:
        raise RuntimeError(f"Partition '{partition_name}' not found. Available: {', '.join(sorted(gpt.keys()))}")

    start, sectors, attrs = gpt[partition_name]
    if attrs:
        print(f"  GPT attrs: 0x{attrs:016x}")

    total_bytes = sectors * 512
    print(f"Partition '{partition_name}': start=0x{start:x}, sectors=0x{sectors:x} ({total_bytes} bytes)")

    with open(image_path, "rb") as f:
        data = f.read()

    if len(data) > total_bytes:
        raise RuntimeError(f"Image ({len(data)} bytes) exceeds partition size ({total_bytes} bytes)")

    # Zero-pad to partition size
    if len(data) < total_bytes:
        data += b"\x00" * (total_bytes - len(data))

    expected_hash = hashlib.sha256(data).hexdigest()
    print(f"Image SHA256: {expected_hash}")

    # Send F command
    cmd = f"F {partition_name}\n"
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

    # Wait for SHA256
    resp = read_response(dev, timeout=30000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")
    if not resp_str.startswith("SHA256 "):
        raise RuntimeError(f"Expected SHA256, got: {resp_str}")

    device_hash = resp_str[7:71]
    if device_hash != expected_hash:
        print(f"  MISMATCH! Expected: {expected_hash}")
        print(f"             Got:      {device_hash}")
        dev.write(EP_OUT, b"ABORT\n")
        raise RuntimeError("Upload SHA256 mismatch — data corrupted in transfer")

    print(f"  Upload SHA256 verified OK")

    # Send CONFIRM to trigger write + readback
    dev.write(EP_OUT, b"CONFIRM\n")

    # Wait for DONE + readback hash
    resp = read_response(dev, timeout=60000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")

    if resp_str.startswith("ERR"):
        raise RuntimeError(f"Write failed: {resp_str}")
    if not resp_str.startswith("DONE "):
        raise RuntimeError(f"Expected DONE, got: {resp_str}")

    readback_hash = resp_str[5:69]
    if readback_hash != expected_hash:
        print(f"  READBACK MISMATCH!")
        print(f"    Expected: {expected_hash}")
        print(f"    Got:      {readback_hash}")
        raise RuntimeError("Readback SHA256 mismatch — write did not persist")

    print(f"  Readback SHA256 verified OK")
    print(f"Flash complete: {partition_name} written and verified.")


def raw_read(dev, addr, length, output_path):
    """Send R command, receive READY + binary data + SHA256, save to file.

    The device sends READY\\n, then raw bytes, then SHA256 <hex>\\n
    all back-to-back. We accumulate everything and split after.
    """
    print(f"  Dumping 0x{addr:x} + 0x{length:x} ({length} bytes) to {output_path}")

    cmd = f"R {addr:x} {length:x}\n"
    dev.write(EP_OUT, cmd.encode())
    time.sleep(0.05)

    # Accumulate: READY line + binary data + SHA256 line
    buf = b""
    deadline = time.time() + 30
    while time.time() < deadline:
        try:
            chunk = bytes(dev.read(EP_IN, 16384, timeout=5000))
            buf += chunk
            # Check if we have READY\n + length bytes of data
            nl = buf.find(b"\n")
            if nl >= 0 and len(buf) >= nl + 1 + length:
                # Got all data, try one more read for SHA line
                try:
                    buf += bytes(dev.read(EP_IN, 4096, timeout=500))
                except usb.core.USBTimeoutError:
                    pass
                break
        except usb.core.USBTimeoutError:
            break

    # Split at first newline → READY line
    nl = buf.find(b"\n")
    if nl < 0:
        print(f"  No response from device")
        return False

    ready_line = buf[:nl].decode("ascii", errors="replace").strip()
    print(f"  Device: {ready_line}")
    if not ready_line.startswith("READY"):
        return False

    rest = buf[nl + 1:]
    data = rest[:length]
    trailing = rest[length:]

    if len(data) < length:
        print(f"  Short read: got {len(data)}/{length} bytes")

    # Parse SHA256 from trailing bytes
    sha_line = trailing.decode("ascii", errors="replace").strip()
    if sha_line.startswith("SHA256 "):
        device_hash = sha_line[7:71]
        expected = hashlib.sha256(data).hexdigest()
        if device_hash == expected:
            print(f"  SHA256 OK: {device_hash}")
        else:
            print(f"  SHA256 MISMATCH! device={device_hash} local={expected}")
    else:
        print(f"  (no SHA256 received)")

    with open(output_path, "wb") as f:
        f.write(data)
    print(f"  Saved {len(data)} bytes to {output_path}")
    return True


def dump_memory(dev, addr, length, output_path):
    """CLI entry point for --dump-memory. Waits for device then calls raw_read."""
    print(f"Dumping 0x{addr:x} + 0x{length:x} ({length} bytes) to {output_path}")

    # Wait for device to be ready (programmer may still be booting)
    for attempt in range(5):
        try:
            resp = send_command(dev, "")
            if resp:
                sys.stdout.write(resp.decode("ascii", errors="replace"))
                sys.stdout.flush()
            break
        except usb.core.USBError:
            print(f"  Device not ready, retrying ({attempt+1}/5)...")
            time.sleep(1)

    if not raw_read(dev, addr, length, output_path):
        raise RuntimeError("Raw read failed")


def handle_flash_interactive(dev, args_str, image_path):
    """Handle an 'F' command in interactive mode using the pre-loaded image.

    Sends the F command, then drives the READY→data→SHA256→CONFIRM→DONE
    handshake using the image file. The user sees each step printed.
    """
    if not image_path:
        print("[no --image specified, passing F command through raw]")
        resp = send_command(dev, "F" + args_str)
        if resp:
            sys.stdout.write(resp.decode("ascii", errors="replace"))
            sys.stdout.flush()
        return

    with open(image_path, "rb") as f:
        image_data = f.read()

    # Send F command to device
    cmd = "F" + args_str
    dev.write(EP_OUT, (cmd + "\n").encode())
    time.sleep(0.05)

    # Wait for READY (tells us sector + count)
    resp = read_response(dev, timeout=5000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")

    if resp_str.startswith("ERR"):
        return
    if not resp_str.startswith("READY"):
        print(f"  Unexpected response (expected READY)")
        return

    # Parse READY sector count
    parts = resp_str.split()
    if len(parts) < 3:
        print("  Malformed READY response")
        return
    sectors = int(parts[2], 16)
    total_bytes = sectors * 512

    # Pad/truncate image to partition size
    data = image_data
    if len(data) > total_bytes:
        print(f"  WARNING: image ({len(data)} bytes) exceeds partition ({total_bytes} bytes), truncating")
        data = data[:total_bytes]
    if len(data) < total_bytes:
        data += b"\x00" * (total_bytes - len(data))

    expected_hash = hashlib.sha256(data).hexdigest()
    print(f"  Image SHA256: {expected_hash}")
    print(f"  Sending {len(data)} bytes...")

    # Send raw data
    chunk_size = 4096
    sent = 0
    while sent < len(data):
        end = min(sent + chunk_size, len(data))
        dev.write(EP_OUT, data[sent:end])
        sent = end
    print(f"  Sent {sent} bytes")

    # Wait for SHA256
    resp = read_response(dev, timeout=30000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")

    if not resp_str.startswith("SHA256 "):
        print(f"  Unexpected response (expected SHA256)")
        return

    device_hash = resp_str[7:71]
    if device_hash != expected_hash:
        print(f"  MISMATCH! Expected: {expected_hash}")
        print(f"             Got:      {device_hash}")
        print("  Sending ABORT")
        dev.write(EP_OUT, b"ABORT\n")
        resp = read_response(dev, timeout=2000)
        if resp:
            print(f"  Device: {resp.decode('ascii', errors='replace').strip()}")
        return

    print(f"  Upload SHA256 verified OK")
    print(f"  Send CONFIRM to write, or type 'n' to abort: ", end="", flush=True)

    try:
        answer = input().strip().lower()
    except (EOFError, KeyboardInterrupt):
        answer = "n"

    if answer == "n":
        dev.write(EP_OUT, b"ABORT\n")
        resp = read_response(dev, timeout=2000)
        if resp:
            print(f"  Device: {resp.decode('ascii', errors='replace').strip()}")
        return

    dev.write(EP_OUT, b"CONFIRM\n")

    # Wait for DONE + readback hash
    resp = read_response(dev, timeout=60000)
    resp_str = resp.decode("ascii", errors="replace").strip()
    print(f"  Device: {resp_str}")

    if resp_str.startswith("ERR"):
        print(f"  Write failed!")
        return
    if not resp_str.startswith("DONE "):
        print(f"  Unexpected response (expected DONE)")
        return

    readback_hash = resp_str[5:69]
    if readback_hash != expected_hash:
        print(f"  READBACK MISMATCH!")
        print(f"    Expected: {expected_hash}")
        print(f"    Got:      {readback_hash}")
    else:
        print(f"  Readback SHA256 verified OK — write successful")


def handle_raw_read_interactive(dev, args_str):
    """Handle an 'R addr len [file]' command in interactive mode."""
    parts = args_str.strip().split()
    if len(parts) < 2:
        print("Usage: R ADDR LEN [FILE]")
        return

    addr = int(parts[0], 16)
    length = int(parts[1], 16)
    output_path = parts[2] if len(parts) >= 3 else f"tmp/dump_{addr:x}.bin"
    raw_read(dev, addr, length, output_path)


def interactive_mode(dev, vid=DEVICE_VID, pid=DEVICE_PID, image_path=None):
    """Interactive terminal mode.

    If image_path is set, 'F' commands are intercepted to handle the
    verified flash handshake using that file. All other commands pass through.
    """
    if image_path:
        print(f"[image loaded: {image_path}]")
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
            stripped = line.strip()
            if stripped.startswith("F") and (len(stripped) == 1 or stripped[1] == " "):
                handle_flash_interactive(dev, stripped[1:], image_path)
            elif stripped.startswith("R") and len(stripped) > 1 and stripped[1] == " ":
                handle_raw_read_interactive(dev, stripped[2:])
            else:
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
    parser.add_argument("--flash-partition", nargs=2, metavar=("NAME", "FILE"),
                        help="Verified flash: write FILE to partition NAME")
    parser.add_argument("--image", metavar="FILE",
                        help="Image file for interactive F commands")
    parser.add_argument("--dump-memory", nargs=3, metavar=("ADDR", "LEN", "FILE"),
                        help="Dump memory region to file (hex addr and len)")
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

    if args.dump_memory:
        addr_str, len_str, out_file = args.dump_memory
        dump_memory(dev, int(addr_str, 16), int(len_str, 16), out_file)
    elif args.flash_partition:
        part_name, image_file = args.flash_partition
        # Init eMMC first
        print("Initializing eMMC...")
        resp = send_command(dev, "e")
        if resp:
            sys.stdout.write(resp.decode("ascii", errors="replace"))
            sys.stdout.flush()
        flash_partition(dev, image_file, part_name)
    elif args.command:
        resp = send_command(dev, args.command)
        if resp:
            sys.stdout.write(resp.decode("ascii", errors="replace"))
    else:
        interactive_mode(dev, vid=vid, pid=pid, image_path=args.image)


if __name__ == "__main__":
    main()
