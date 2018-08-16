if grub2-file --is-x86-multiboot mykernel.elf; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
