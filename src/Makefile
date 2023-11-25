PREFIX = arm-none-eabi-
AS = $(PREFIX)as
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AR = $(PREFIX)ar
CFLAGS = -mthumb -mthumb-interwork -mcpu=arm968e-s -nostdlib -ggdb
ARFLAGS = rc
LD = $(PREFIX)ld
BIN = $(PREFIX)objcopy
LDFLAGS = -T linker.ld --whole-archive
DIS = $(PREFIX)objdump

OBJS = build/hello-world.o build/uart.o build/entry.a

BUILT = hello-world.elf hello-world.bin hello-world.dis

all : prebuild build

prebuild :
	@mkdir -p "build"

build : build/hello-world.elf
	@echo Complete.

.PHONY : prebuild build

build/hello-world.elf : $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	$(BIN) -O binary build/hello-world.elf build/hello-world.bin
	$(DIS) -d build/hello-world.elf > build/hello-world.dis
	encrypt_crc build/hello-world.bin build/hello-world_crc.bin

build/%.o : %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c -o $@ $^

build/%.o : %.s
	@mkdir -p $(shell dirname $@)
	$(AS) -g -o $@ $<

# entry.a

build/entry.a : build/entry/ll.o build/entry/boot_vectors.o build/entry/boot_handlers.o build/entry/arm.o build/entry/arch_main.o
	$(AR) $(ARFLAGS) $@ $^

clean :
	rm -f *.o
	rm -R build/*
