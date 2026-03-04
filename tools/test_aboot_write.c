/*
 * test_aboot_write.c — Test whether the aboot partition is writable.
 *
 * Flips a single bit in the last sector (expected to be zero-padding),
 * syncs, reads back, and verifies. Then restores the original byte.
 *
 * Usage:  ./test_aboot_write /dev/block/by-name/aboot
 *    or:  ./test_aboot_write /dev/block/mmcblk0p5   (whatever aboot is)
 *
 * Build: arm-linux-gnueabi-gcc -static -o test_aboot_write test_aboot_write.c
 *    or: $NDK/toolchains/.../bin/clang --target=armv7a-linux-androideabi21 \
 *            -static -o test_aboot_write test_aboot_write.c
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/fs.h>  /* BLKGETSIZE64 */

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s /dev/block/by-name/aboot\n", argv[0]);
		return 1;
	}

	const char *dev = argv[1];
	int fd = open(dev, O_RDWR | O_SYNC);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	/* Get partition size. */
	unsigned long long size = 0;
	if (ioctl(fd, BLKGETSIZE64, &size) < 0) {
		perror("BLKGETSIZE64");
		close(fd);
		return 1;
	}
	printf("partition: %s  size: %llu bytes (%llu sectors)\n",
	       dev, size, size / 512);

	if (size < 1024) {
		fprintf(stderr, "partition too small\n");
		close(fd);
		return 1;
	}

	/* Target: last 512-byte sector (should be zero padding). */
	off_t offset = (off_t)(size - 512);
	unsigned char orig[512], modified[512], readback[512];

	/* Read the last sector. */
	if (pread(fd, orig, 512, offset) != 512) {
		perror("pread original");
		close(fd);
		return 1;
	}

	/* Verify the sector is entirely zero before we touch it. */
	int nonzero = 0;
	for (int i = 0; i < 512; i++)
		if (orig[i] != 0) nonzero++;
	printf("last sector at offset %lld: %d/512 non-zero bytes\n",
	       (long long)offset, nonzero);

	if (nonzero != 0) {
		fprintf(stderr, "ABORT: last sector is not all zeros — refusing to modify\n");
		close(fd);
		return 1;
	}

	/* Flip one bit in the last byte. */
	memcpy(modified, orig, 512);
	modified[511] ^= 0x01;

	printf("writing: byte[511] 0x%02x -> 0x%02x\n", orig[511], modified[511]);

	/* Write. */
	ssize_t w = pwrite(fd, modified, 512, offset);
	if (w != 512) {
		if (w < 0)
			perror("pwrite");
		else
			fprintf(stderr, "pwrite: short write (%zd/512)\n", w);
		close(fd);
		return 1;
	}

	/* Force flush to hardware. */
	if (fsync(fd) < 0) {
		perror("fsync");
		/* continue anyway to read back */
	}

	/* Drop page cache for this fd so we re-read from hardware. */
	if (ioctl(fd, BLKFLSBUF) < 0)
		perror("BLKFLSBUF (non-fatal)");

	/* Close and re-open to defeat any kernel caching. */
	close(fd);
	fd = open(dev, O_RDONLY);
	if (fd < 0) {
		perror("re-open for readback");
		return 1;
	}

	if (pread(fd, readback, 512, offset) != 512) {
		perror("pread readback");
		close(fd);
		return 1;
	}

	if (memcmp(readback, modified, 512) == 0) {
		printf("RESULT: WRITE SUCCEEDED — read back matches modified data\n");
		printf("        The eMMC accepted the write. Restoring original...\n");

		/* Restore original. */
		close(fd);
		fd = open(dev, O_RDWR | O_SYNC);
		if (fd >= 0) {
			pwrite(fd, orig, 512, offset);
			fsync(fd);
			close(fd);
			printf("        Original restored.\n");
		}
		return 0;
	}

	if (memcmp(readback, orig, 512) == 0) {
		printf("RESULT: WRITE FAILED — read back matches ORIGINAL data\n");
		printf("        The eMMC silently rejected the write.\n");
		printf("        This confirms hardware write protection.\n");
	} else {
		printf("RESULT: UNEXPECTED — read back differs from both original and modified!\n");
		printf("        orig[511]=0x%02x  modified[511]=0x%02x  readback[511]=0x%02x\n",
		       orig[511], modified[511], readback[511]);
	}

	close(fd);
	return 1;
}
