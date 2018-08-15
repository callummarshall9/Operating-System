#include <stddef.h>
#include <stdint.h>

register uint16_t *sp asm ("sp");
//register int *ss asm ("ss");
extern void write_serial_int(uint16_t i);

void interrupt_handler(void)
{
	write_serial_int(*sp);
	//write_serial_int(ss);
}
