# Makefile

CFLAGS=-m32 -ffreestanding -O2 -nostdlib
LDFLAGS=-m elf_i386 -T linker.ld

all: kernel.bin

kernel.bin: boot.o kernel.o vga.o
    ld $(LDFLAGS) -o kernel.bin -e _start boot.o kernel.o vga.o

boot.o: boot.asm
    nasm -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
    gcc $(CFLAGS) -c kernel.c -o kernel.o

vga.o: vga.c
    gcc $(CFLAGS) -c vga.c -o vga.o

clean:
    rm -f *.o kernel.bin
