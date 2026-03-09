# Device Properties Analysis

This document summarizes key information extracted from `original_props` (live `getprop` dump), `backups/build.prop` (system partition), and `backups/prop.default` (boot image properties).

## Key Device Information

*   **Model:** `BQ268`
*   **Device Codename:** `UdoSmart`
*   **Manufacturer:** `udotech`
*   **Brand:** `qcom`
*   **Build fingerprint:** `qcom/msm8909go/msm8909go:8.1.0/OPM1.171019.026/udosma07091241:user/test-keys`

## Hardware

*   **SoC:** Qualcomm Snapdragon 210/212 (`msm8909`)
*   **Architecture:** 32-bit ARM (`armeabi-v7a`)
*   **RAM:** Low RAM / Android Go device (`ro.config.low_ram=true`, heap 36m)
*   **Display:** LCD density 90 dpi, 90° hardware rotation (`ro.sf.lcd_density=90`, `ro.sf.hwrotation=90`)
*   **Bootloader:**
    *   `ro.boot.flash.locked=0` (Likely unlocked)
    *   `ro.oem_unlock_supported=true`

## Software

*   **Android Version:** 8.1.0 (Oreo)
*   **SDK Version:** 27
*   **Security Patch Level:** 2019-03-05
*   **Treble Support:** Enabled (`ro.treble.enabled=true`)
*   **Build type:** `user` (but signed with `test-keys`, not `release-keys` — unusual, may ease custom image flashing)
*   **Build date:** Wed Jul 9 2025 (`ro.build.date.utc=1752036101`) — actively maintained ODM ROM
*   **ADB/Debug:**
    *   `ro.adb.secure=1` (ADB auth required)
    *   `ro.debuggable=0`
    *   `ro.secure=1`
*   **Security:**
    *   Verified Boot (`ro.boot.veritymode=enforcing`)
    *   Crypto State: `unencrypted`
    *   Expected recovery hash: `ro.expect.recovery_id=0x3d90949af504388de0936ef34559d93fc16882ed...` (bootloader verifies recovery partition against this value)

## Fastboot

From `fastboot getvar all` (source of truth):

| Variable | Value |
|----------|-------|
| `unlocked` | `yes` |
| `secure` | `no` |
| `kernel` | `lk` (Little Kernel) |
| `product` | `MSM8909` |
| `variant` | `MTP eMMC` |
| `version` | `0.5` |
| `max-download-size` | `0xfa00000` (~250 MB) |
| `version-baseband` | (empty) |
| `version-bootloader` | (empty) |

**Implication:** `unlocked:yes` + `secure:no` means the bootloader will accept unsigned images. Custom boot/recovery images can be flashed without signature matching.

## Partitions

The device uses the `by-name` partition naming scheme.
*   The `config` partition is located at `/dev/block/bootdevice/by-name/config`.
*   The `misc` partition is identified as `mmcblk0p28`.
*   Default USB configuration: `diag,serial_smd,rmnet_qti_bam,adb`

### Full Partition Layout (from `fastboot getvar all`)

| Partition | Size (hex) | Size |
|-----------|-----------|------|
| `sbl1` / `sbl1bak` | `0x80000` | 512 KB each |
| `rpm` / `rpmbak` | `0x80000` | 512 KB each |
| `tz` / `tzbak` | `0x200000` | 2 MB each |
| `aboot` / `abootbak` | `0x100000` | 1 MB each |
| `keymaster` / `keymasterbak` | `0x80000` | 512 KB each |
| `cmnlib` / `cmnlibbak` | `0x40000` | 256 KB each |
| `devcfg` | `0x40000` | 256 KB |
| `apdp` | `0x40000` | 256 KB |
| `devinfo` | `0x100000` | 1 MB |
| `sec` | `0x4000` | 16 KB |
| `ssd` | `0x2000` | 8 KB |
| `fsc` | `0x400` | 1 KB |
| `DDR` | `0x8000` | 32 KB |
| `pad` | `0x100000` | 1 MB |
| `modemst1` / `modemst2` | `0x180000` | 1.5 MB each |
| `fsg` | `0x180000` | 1.5 MB |
| `modem` | `0x4200000` | ~66 MB |
| `boot` | `0x2000000` | **32 MB** |
| `recovery` | `0x2000000` | **32 MB** |
| `system` | `0x38400000` | **~900 MB** (ext4) |
| `vendor` | `0xfa00000` | **250 MB** |
| `cache` | `0x6e00000` | **110 MB** (ext4) |
| `persist` | `0x2000000` | 32 MB |
| `userdata` | `0x86e79a00` | **~2.1 GiB** (ext4) |
| `misc` | `0x800000` | 8 MB |
| `oem` | `0x800000` | 8 MB |
| `keystore` | `0x80000` | 512 KB |
| `splash` | `0xa00000` | 10 MB |
| `config` | `0x80000` | 512 KB |

## Device-Specific / Notable Properties

*   **`persist.youdo.phone.enable=1`** — Unknown "YouDo phone" feature flag, likely related to PTT/walkie-talkie functionality.
*   **`ro.telephony.default_network=22,20`** — Dual SIM (DSDS) network mode configuration.
*   **`persist.sys.usb.config=diag,serial_smd,rmnet_qti_bam,adb`** — Qualcomm diagnostic interface (`diag`) enabled by default on USB, useful for low-level debugging.
*   **`ro.build.flavor=msm8909go-user`** — Confirms msm8909 Go (Android Go) variant.

