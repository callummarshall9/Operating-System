#ifndef SERIAL_IO
#define SERIAL_IO

#define PORT 0x3f8   /* COM1 */

int serial_received() {
   return inb(PORT + 5) & 1;
}
 
char read_serial() {
   while (serial_received() == 0);
 
   return inb(PORT);
}

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}

void write_serial_int(uint8_t i) {
	while(is_transmit_empty() == 0);
	outb(PORT,i);
}
 
void write_serial_char(char a) {
   while (is_transmit_empty() == 0);
 
   outb(PORT,a);
}

void write_serial_string(const char* str) {
	for (size_t i = 0; str[i] != '\0'; i ++) { // Keep placing characters until we hit the null-terminating character ('\0')
		write_serial_char(str[i]);
	} 
}

void init_serial() {
	outb(PORT + 1, 0x00);    // Disable all interrupts
	outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	write_serial_string("init_serial:COM1\n");
}

#endif
