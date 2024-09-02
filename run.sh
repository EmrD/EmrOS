#!/bin/bash

# Çıktı dosyalarını temizle
rm -f kernel.o vga.o kernel.bin EmrOS.iso

# Kernel ve vga dosyalarını derle
echo "Derleme işlemleri başlatılıyor..."

gcc -m32 -ffreestanding -O2 -nostdlib -c kernel.c -o kernel.o
if [ $? -ne 0 ]; then
    echo "kernel.c derlenirken hata oluştu!"
    exit 1
fi

gcc -m32 -ffreestanding -O2 -nostdlib -c vga.c -o vga.o
if [ $? -ne 0 ]; then
    echo "vga.c derlenirken hata oluştu!"
    exit 1
fi

# Bağlama işlemi
echo "Bağlama işlemi başlatılıyor..."

ld -m elf_i386 -T linker.ld -o kernel.bin -e _start boot.o kernel.o vga.o
if [ $? -ne 0 ]; then
    echo "Bağlama işlemi sırasında hata oluştu!"
    exit 1
fi

# ISO yapısını oluşturma
echo "ISO yapısı oluşturuluyor..."

mkdir -p iso/boot/grub

cp kernel.bin iso/boot/kernel.bin

cat > iso/boot/grub/grub.cfg << EOF
menuentry "EmrOS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# ISO dosyasını oluşturma
grub-mkrescue -o EmrOS.iso iso
if [ $? -ne 0 ]; then
    echo "ISO dosyası oluşturulurken hata oluştu!"
    exit 1
fi

echo "İşlem başarıyla tamamlandı!"
