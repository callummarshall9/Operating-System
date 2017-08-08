rm -rf output/*
cd barebones-toolchain
. ./setenv.sh
cd ..
yasm -felf32 boot.asm -o "$PWD/output/boot.o"
i686-elf-gcc -c kernel/kernel.c -o "$PWD/output/kernel.o" -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o "$PWD/output/myos.bin" -ffreestanding -O2 -nostdlib "$PWD/output/boot.o" "$PWD/output/kernel.o" -lgcc
cp "$PWD/output/myos.bin" isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub2-mkrescue -o "$PWD/output/myos.iso" "$PWD/isodir"
