/*
 * restore_aboot_sector.c — Restore the last sector of aboot to all zeros.
 *
 * Verifies the sector contains exactly 511 zero bytes and 0x01 at byte[511]
 * (the expected state after test_aboot_write), then writes all zeros back.
 *
 * Usage:  ./restore_aboot_sector /dev/block/mmcblk0p17
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s /dev/block/mmcblk0pXX\n", argv[0]);
		return 1;
	}

	const char *dev = argv[1];
	int fd = open(dev, O_RDWR | O_SYNC);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	unsigned long long size = 0;
	if (ioctl(fd, BLKGETSIZE64, &size) < 0) {
		perror("BLKGETSIZE64");
		close(fd);
		return 1;
	}

	off_t offset = (off_t)(size - 512);
	unsigned char sector[512], readback[512];

	if (pread(fd, sector, 512, offset) != 512) {
		perror("pread");
		close(fd);
		return 1;
	}

	/* Verify it's exactly our expected damage: all zeros except byte[511] == 0x01. */
	int ok = 1;
	for (int i = 0; i < 511; i++) {
		if (sector[i] != 0x00) {
			fprintf(stderr, "ABORT: byte[%d] = 0x%02x, expected 0x00\n", i, sector[i]);
			ok = 0;
		}
	}
	if (sector[511] != 0x01) {
		fprintf(stderr, "ABORT: byte[511] = 0x%02x, expected 0x01\n", sector[511]);
		ok = 0;
	}
	if (!ok) {
		fprintf(stderr, "Sector does not match expected pattern. Refusing to write.\n");
		close(fd);
		return 1;
	}

	printf("sector at offset %lld matches expected pattern (511 zeros + 0x01)\n",
	       (long long)offset);
	printf("writing all zeros...\n");

	memset(sector, 0, 512);
	if (pwrite(fd, sector, 512, offset) != 512) {
		perror("pwrite");
		close(fd);
		return 1;
	}
	fsync(fd);
	ioctl(fd, BLKFLSBUF);

	/* Verify. */
	close(fd);
	fd = open(dev, O_RDONLY);
	if (fd < 0) {
		perror("re-open");
		return 1;
	}
	if (pread(fd, readback, 512, offset) != 512) {
		perror("pread readback");
		close(fd);
		return 1;
	}

	unsigned char zeros[512];
	memset(zeros, 0, 512);
	if (memcmp(readback, zeros, 512) == 0) {
		printf("RESTORED: sector is all zeros again\n");
		close(fd);
		return 0;
	}

	fprintf(stderr, "FAILED: readback[511] = 0x%02x, expected 0x00\n", readback[511]);
	close(fd);
	return 1;
}
