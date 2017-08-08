static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

char get_scan_code()
{
	char c=0;
	do {
		if(inb(0x60)!=c) {
			c=inb(0x60);
			if(c>0) {
				return c;
			}
		}
	}
	while(1);
}


char scan_char(char charToScan) {
	int character = (int)charToScan;
	char returnCharacter = '`';
	switch(character) {
    case 3:
      returnCharacter = '1';
      break;
    case 4:
      returnCharacter = '2';
      break;
    case 5:
      returnCharacter = '3';
      break;
    case 6:
      returnCharacter = '4';
      break;
    case 7:
      returnCharacter = '5';
      break;
    case 8:
      returnCharacter = '6';
      break;
    case 9:
      returnCharacter = '7';
      break;
    case 10:
      returnCharacter = '8';
      break;
    case 11:
      returnCharacter = '9';
      break;
    case 12:
      returnCharacter = '10';
      break;
		case 29:
			returnCharacter = '-';
			break;
		case 58:
			returnCharacter = '=';
			break;
		case 17:
			returnCharacter = 'q';
			break;
		case 18:
			returnCharacter = 'w';
			break;
		case 19:
			returnCharacter = 'e';
			break;
		case 20:
			returnCharacter = 'r';
			break;
		case 21:
			returnCharacter = 't';
			break;
		case 22:
			returnCharacter = 'y';
			break;
		case 23:
			returnCharacter = 'u';
			break;
		case 24:
			returnCharacter = 'i';
			break;
		case 25:
			returnCharacter = 'o';
			break;
		case 26:
			returnCharacter = 'p';
			break;
		case 31:
			returnCharacter = 'a';
			break;
		case 32:
			returnCharacter = 's';
			break;
		case 33:
			returnCharacter = 'd';
			break;
		case 34:
			returnCharacter = 'f';
			break;
		case 35:
			returnCharacter = 'g';
			break;
		case 36:
			returnCharacter = 'h';
			break;
		case 37:
			returnCharacter = 'j';
			break;
		case 38:
			returnCharacter = 'k';
			break;
		case 39:
			returnCharacter = 'l';
			break;
		case 45:
			returnCharacter = 'z';
			break;
		case 46:
			returnCharacter = 'x';
			break;
		case 47:
			returnCharacter = 'c';
			break;
		case 48:
			returnCharacter = 'v';
			break;
		case 49:
			returnCharacter = 'b';
			break;
		case 50:
			returnCharacter = 'n';
			break;
		case 51:
			returnCharacter = 'm';
			break;
	}
	return returnCharacter;
}

char get_char() {
	return scan_char(get_scan_code() + 1);
}
