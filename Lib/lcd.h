#define lcd_data P0

sbit rw = P2^5;
sbit rs = P2^6;
sbit en = P2^7;

void lcd_delay(unsigned int t) {
	unsigned int x, y;
	for (x = 0; x < t; x++) {
		for (y = 0; y < 100; y++);
	}
}

void cmd(unsigned char a) {
	lcd_data = a;
	rs = 0;
	rw = 0;
	en = 1;
	lcd_delay(1);
	en = 0;
	lcd_delay(5);
}

void dat(unsigned char b) {
	lcd_data = b;
	rs = 1;
	rw = 0;
	en = 1;
	lcd_delay(1);
	en = 0;
	lcd_delay(5);
}

void show(unsigned char* s) {
	int i;
	for (i = 0; s[i] != 0; i++) {
		dat(s[i]);
	}
}

void showlines(char row, char pos, char* s) {
	if (row == 0) {
		cmd((pos & 0x0F) | 0x80);
	} else if (row) {
		cmd((pos & 0x0F) | 0xC0);
	}
	show(s);
}

void LCD_Init() {
	cmd(0x38);
	cmd(0x0E);
	cmd(0x01);
	cmd(0x06);
	cmd(0x0C);
	cmd(0x80);
}