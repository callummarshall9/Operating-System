cd barebones-toolchain
. ./setenv.sh
cd ..
echo "Cleaning";
rm bin/*.o
rm mykernel.elf
echo "Building start.o";
i686-elf-gcc -std=gnu99 -ffreestanding -g -c start.s -o "$PWD/bin/start.o";
sleep 1;
echo "Building isr_wrapper.o";
i686-elf-gcc -std=gnu99 -ffreestanding -g -c isr_wrapper.s -o "$PWD/bin/isr_wrapper.o";
sleep 1;
i686-elf-gcc -std=gnu99 -ffreestanding -g -c interrupt_handler.c -o "$PWD/bin/interrupt_handler.o";
sleep 1;
echo "Building kernel.o";
i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o "$PWD/bin/kernel.o";
sleep 1;
echo "Building elf file";
i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld "$PWD/bin/start.o" "$PWD/bin/kernel.o" "$PWD/bin/isr_wrapper.o" "$PWD/bin/interrupt_handler.o" -o mykernel.elf -lgcc;

