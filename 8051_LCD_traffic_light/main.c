#include <REGX52.H>
#include <intrins.h>
#include "../Lib/delay.h"
#include "../Lib/lcd.h"
#include "../Lib/pwm.h"

#define sevenSegPort P0

sbit A1 = P2^2;
sbit B1 = P2^3;
sbit C1 = P2^4;
sbit greenLED = P1^0;
sbit yellowLED = P1^1;
sbit redLED = P1^2;

unsigned char code sevenSeg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char counter = 30;
unsigned int greenSignal = 1;

void display7seg(unsigned char num);
void signals(unsigned char state);

int main() {
	EA = 1;
	ET0 = 1;
	Timer0_Init();
	LCD_Init();
	while(1) {
		if (counter > 5 && greenSignal) {
			signals(2);
		} else if (counter <= 5 && counter > 0 && greenSignal) {
			signals(1);
		} else if (counter > 0 && !greenSignal) {
			signals(0);
		}
		if (counter == 0) {
			counter = 30;
			greenSignal = !greenSignal;
		}
		display7seg(counter);
		counter--;
		if (greenSignal) {
			servo_spin(10);
		} else {
			servo_spin(5);
		}
	}
	return 0;
}

void display7seg(unsigned char num) {
	unsigned int i;
	unsigned char tens = num/10;
	unsigned char units = num%10;
	for (i = 0; i < 500; i++) {
		sevenSegPort = sevenSeg[tens];
		A1 = 1;
		B1 = 0;
		C1 = 0;
		delay(1);
		A1 = 1;
		B1 = 1;
		C1 = 1;
		sevenSegPort = sevenSeg[units];
		A1 = 0;
		B1 = 0;
		C1 = 0;
		delay(1);
		A1 = 1;
		B1 = 1;
		C1 = 1;
	}
}

void signals(unsigned char state) {
	if (state == 0) {
		redLED = 1;
		greenLED = 0;
		yellowLED = 0;
		cmd(0x01);
		showlines(0, 6, "STOP");
	} else if (state == 1) {
		yellowLED = 1;
		greenLED = 0;
		redLED = 0;
		cmd(0x01);
		showlines(0, 3, "Slow Down");
	} else if (state == 2) {
		greenLED = 1;
		yellowLED = 0;
		redLED = 0;
		cmd(0x01);
		showlines(0, 3, "Welcome to");
		showlines(1, 0, "Hotel California");
	}
}