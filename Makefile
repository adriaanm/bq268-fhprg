# Top-level Makefile — delegates to src/

.PHONY: all elf clean

all:
	$(MAKE) -C src

elf:
	$(MAKE) -C src elf

clean:
	$(MAKE) -C src clean
