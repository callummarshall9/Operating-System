// GCC provides these header files automatically
// They give us access to useful things like fixed-width types
#include <stddef.h>
#include <stdint.h>
#include "io/utils.c"
#include "io/serial.c"
#include "vga/term.c"
#include "multibootspec/multiboot.h"
#include "string/utils.c"
#include "mm/mmap.c"
#include "mm/liballoc_hooks.c"
#include "mm/liballoc/liballoc.h"
#include "mm/liballoc/liballoc.c"
 
// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif
 
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))
// This is our kernel's main function
void kernel_main(uint32_t magic, unsigned long header)
{
	// We're here! Let's initiate the terminal and display a message to show we got here.
 	init_serial();//Initialise serial.
	term_init();//Initialise terminal.
	// Display some messages
	term_print("Hello, World!\n");
	term_print("Welcome to the kernel.\n");
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		term_print("Error: not compliant bootloader for multiboot v1 specification!");
		return;
	}
	verified_mboot_hdr = (multiboot_info_t *) header;
	mboot_reserved_start = (uint32_t)header;
	mboot_reserved_end = (uint32_t)(verified_mboot_hdr + sizeof(multiboot_info_t));
	next_free_frame = 1;
	/*if (CHECK_FLAG (mbi->flags, 6))
         {
           multiboot_memory_map_t *mmap;
     
           printf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
                   (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
           for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
                (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
                mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                         + mmap->size + sizeof (mmap->size))) {
		if(mmap->type == 1) {//Memory is avaliable
			unsigned long length = mmap->len;
			int format_length = length / (1024.00 * 1024.00);
			printf("Availiable segment found, Length %d MiB \n", format_length);
		}
             	printf (" size = 0x%x, base_addr = 0x%x%08x,"
                     " length = 0x%x%08x, type = 0x%x\n",
                     (unsigned) mmap->size,
                     (unsigned) (mmap->addr >> 32),
                     (unsigned) (mmap->addr & 0xffffffff),
                     (unsigned) (mmap->len >> 32),
                     (unsigned) (mmap->len & 0xffffffff),
                     (unsigned) mmap->type);
		}
         }*/
}	
