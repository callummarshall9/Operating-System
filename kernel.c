// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include <stddef.h>
#include <stdint.h>
#include "mm/malloc.c"
#include "io/utils.c"
#include "io/serial.c"
#include "vga/term.c"
 
// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif
 
void fprintf(
 
// This is our kernel's main function
void kernel_main()
{
	// We're here! Let's initiate the terminal and display a message to show we got here.
 	init_serial();//Initialise serial.
	term_init();//Initialise terminal.
 
	// Display some messages
	term_print("Hello, World!\n");
	term_print("Welcome to the kernel.\n");
}
