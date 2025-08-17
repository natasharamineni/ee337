#include <at89c5131.h>
#include "lcd.h"

sbit AFG=P3^4;
sbit DIP=P1^0;
int seconds=0, second, minutes;
unsigned char min, sec, time[5]="00:00";

void timer0_isr () interrupt 1
{
	seconds = seconds + 1;
	second = seconds % 60;
		minutes = seconds/60;
		time[4] = second%10 + '0';
		time[3] = second/10 + '0';
		time[2] = ':';
		time[1] = minutes%10 + '0';
		time[0] = minutes/10 + '0';
	TH0 = 0xFF;
	TL0 = 0xC4;
	AFG=DIP=1;
	TR0 = 1;
}

void main()
{
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string("00:00");
	AFG=DIP=1;
	while(1){
	while(DIP==0){AFG=DIP=1;}
	TMOD = 0x05;
	TH0 = 0xFF;
	TL0 = 0xC4;
	ET0 = 1;
	EA = 1;

	while(DIP==1)
	{
		TR0 = 1;
		lcd_cmd(0x80);
		msdelay(4);
		lcd_write_string(time);
		AFG=DIP=1;
	}
	TR0 = 0;
}
	
}		