/* Scan code set taken from: https://wiki.osdev.org/PS2_Keyboard */

char top_keys[10] = "qwertyuiop";
char middle_keys[9] = "asdfghjkl";
char bottom_keys[7] = "zxcvbnm";

char get_scan_code() {
    char c=0;
    do {
        if(inb(0x60)!=c) {
            c=inb(0x60);
            if(c>0)
                return c;
        }
    } while(1);
}

int is_modifier(int scan_code) {
	return (scan_code == 0x1C || scan_code == 0x01);
}

int is_enter(int scan_code) {
	return (scan_code == 0x1C);
}

int is_escape(int scan_code) {
	return (scan_code == 0x01);
}

int is_space(int scan_code) {
	return (scan_code == 0x39);
}

char get_char(int scan_code) {
	if(scan_code >= 0x10 && scan_code <= 0x19) {
		return top_keys[scan_code-0x10];
	} else if(scan_code >= 0x1E && scan_code <= 0x26) {
		return middle_keys[scan_code-0x1E];
	} else if(scan_code >= 0x2C && scan_code <= 0x32) {
		return bottom_keys[scan_code-0x2C];
	} else if(is_space(scan_code)) {
		return ' ';
	}
	return ';';
}


char* get_input(char *buffer) {
	int prev_scan_code = 0;
	int pointer = 0;
	while(!is_enter(prev_scan_code)) {
		int current_scan_code = get_scan_code();
		if(!is_modifier(current_scan_code) && current_scan_code != prev_scan_code) {
			buffer[pointer] = get_char(current_scan_code);
			pointer++;
			term_putc(get_char(current_scan_code));
		}
		prev_scan_code = current_scan_code;
	} return buffer;
}
