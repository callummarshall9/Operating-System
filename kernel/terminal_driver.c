const size_t TERMINAL_ADDRESS = 0xB8000;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) TERMINAL_ADDRESS;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if(data[i] == '\n') {
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
			terminal_column = 0;
		} else {
			terminal_putchar(data[i]);
		}
	}
}

void terminal_write_integer(int data) {
	if(data < 100) {
		int ten = data / 10;
		int digit = data % 10;
		char first_char = (char)ten;
		char second_char = (char)digit;
		char represent[2];
		represent[0] = first_char;
		represent[1] = second_char;
		terminal_write_string(represent);
	}
}

void terminal_write_string(const char* data) {
	terminal_write(data, strlen(data));
}
