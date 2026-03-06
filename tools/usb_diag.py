#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.9"
# dependencies = ["pyusb"]
# ///
"""usb_diag.py — Host-side tool for the MSM8909 USB diagnostic console.

Connects to the minimal programmer's diagnostic mode over USB bulk
and provides an interactive terminal.

Usage:
    uv run tools/usb_diag.py             # interactive mode
    uv run tools/usb_diag.py -c "i"      # single command mode

On Linux, you may need a udev rule or run as root:
    sudo uv run tools/usb_diag.py
"""

import sys
import time
import argparse
import usb.core
import usb.util

VID = 0x05C6
PID = 0xF001
EP_OUT = 0x01  # Endpoint 1 OUT (host → device)
EP_IN  = 0x81  # Endpoint 1 IN  (device → host)


def find_device(timeout=30):
    """Wait for the diagnostic device to appear."""
    print(f"Waiting for device {VID:04x}:{PID:04x}...", end="", flush=True)
    deadline = time.time() + timeout
    while time.time() < deadline:
        dev = usb.core.find(idVendor=VID, idProduct=PID)
        if dev is not None:
            print(" found!")
            return dev
        print(".", end="", flush=True)
        time.sleep(0.5)
    print(" timeout!")
    return None


def setup_device(dev):
    """Configure the USB device for communication."""
    try:
        if dev.is_kernel_driver_active(0):
            dev.detach_kernel_driver(0)
    except (usb.core.USBError, NotImplementedError):
        pass

    dev.set_configuration()
    return dev


def read_response(dev, timeout=2000):
    """Read all available data from the device."""
    data = b""
    while True:
        try:
            chunk = dev.read(EP_IN, 4096, timeout=timeout)
            data += bytes(chunk)
            # Short packet = end of response
            if len(chunk) < 512:
                break
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
    time.sleep(0.05)  # small delay for device to process
    return read_response(dev)


def interactive_mode(dev):
    """Interactive terminal mode."""
    # Read initial banner
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
            # Try to reconnect
            dev2 = find_device(timeout=10)
            if dev2:
                dev = setup_device(dev2)
                print("[reconnected]")
            else:
                print("[device lost]")
                break


def main():
    parser = argparse.ArgumentParser(description="MSM8909 USB diagnostic console")
    parser.add_argument("-c", "--command", help="Execute a single command and exit")
    parser.add_argument("-t", "--timeout", type=int, default=30,
                        help="Device discovery timeout (seconds)")
    args = parser.parse_args()

    dev = find_device(timeout=args.timeout)
    if dev is None:
        print("Device not found. Is the programmer running?", file=sys.stderr)
        sys.exit(1)

    dev = setup_device(dev)
    print(f"Connected: {dev.manufacturer or 'QC'} {dev.product or 'DIAG'}")

    if args.command:
        resp = send_command(dev, args.command)
        if resp:
            sys.stdout.write(resp.decode("ascii", errors="replace"))
    else:
        interactive_mode(dev)


if __name__ == "__main__":
    main()
