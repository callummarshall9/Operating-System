/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
#include "vga_textmode.c"
#include "terminal_driver.c"
#include "keyboard.c"

void kernel_main(void) {
  terminal_initialize();
  terminal_write_string("Input: ");
  char previous_char = '`';
  int bufferPointer = 0;
  char buffer[256];
  while(true) {
    char current_char = get_scan_code();
    int current_char_code = (int)current_char;
    if(current_char != previous_char) {
      if(current_char_code == 0x1C) {//Enter is pressed.
        terminal_initialize();
        terminal_write_string("Input: ");
        process_buffer(buffer);
        for(int i = 0; i < 256; i++) {
          buffer[i] = ' ';
        }
        bufferPointer = 0;
      } else if (current_char_code == 0x0E) {//Backspace is pressed.
        terminal_initialize();
        terminal_write_string("Input: ");
        bufferPointer = bufferPointer - 1;
        for(int i = 0; i < bufferPointer; i++) {
          terminal_putchar(buffer[i]);
        }
      } else {
        buffer[bufferPointer] = scan_char(current_char + 1);
        terminal_putchar(buffer[bufferPointer]);
        bufferPointer = bufferPointer + 1;
      }
    }
    previous_char = current_char;
  }
}

void process_buffer(char *buffer) {
  if(starts_with(buffer, "login", 5) == 1) {
    reset_terminal();
    terminal_write_string("Fuck the world!");
  }
}

void reset_terminal() {
  terminal_initialize();
}

int starts_with(char *buffer, char *needle, int needle_lengh) {
  for(int i = 0; i < needle_lengh; i++) {
    if(buffer[i] != needle[i]) {
      return 0;
    }
  }
  return 1;
}
