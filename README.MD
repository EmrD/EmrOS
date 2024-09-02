gcc -m32 -ffreestanding -O2 -nostdlib -c kernel.c -o kernel.o

gcc -m32 -ffreestanding -O2 -nostdlib -c vga.c -o vga.o

ld -m elf_i386 -T linker.ld -o kernel.bin -e _start boot.o kernel.o vga.o

mkdir -p iso/boot/grub

cp kernel.bin iso/boot/kernel.bin

cat > iso/boot/grub/grub.cfg << EOF
menuentry "EmrOS" {
    multiboot /boot/kernel.bin
    boot
}
EOF


grub-mkrescue -o EmrOS.iso iso

qemu-system-i386 -cdrom EmrOS.iso