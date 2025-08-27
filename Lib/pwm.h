#include <intrins.h>

#define pwmPeriod 0xB7FE

sbit servo = P1^3;

unsigned int ON_Period, OFF_Period;

void Timer0_Init() {
	TMOD = 0x01;
	TL0 = pwmPeriod;
	TH0 = pwmPeriod >> 8;
	TR0 = 1;
}

void Timer0_ISR() interrupt 1 {
	servo = !servo;
	if (servo) {
		TL0 = ON_Period;
		TH0 = ON_Period >> 8;
	} else {
		TL0 = OFF_Period;
		TH0 = OFF_Period >> 8;
	}
}

void servo_spin(float angle) {
	float countValue = 65535 - pwmPeriod;
	ON_Period = countValue / 100 * angle;
	OFF_Period = countValue - ON_Period;
	ON_Period = 65535 - ON_Period;
	OFF_Period = 65535 - OFF_Period;
}