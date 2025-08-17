#include <at89c5131.h>
#include "lcd.h"

code unsigned char display_msg1[]="  START PROGRAM ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]="   FIRST INPUT  ";						//Display msg on 2nd line of lcd
code unsigned char display_msg3[]="   NEXT INPUT   ";
code unsigned char display_msg4[]="   SORTING...   ";
code unsigned char display_msg5[]="     SORTING    ";
code unsigned char display_msg6[]="    COMPLETED   ";
code unsigned char display_msg7[]="  NUMBER TO BE  ";
code unsigned char display_msg8[]="    SEARCHED    ";
code unsigned char display_msg9[]="  THE INDEX IS  ";
code unsigned char display_msg10[]="     NUMBER     ";
code unsigned char display_msg11[]="    NOT FOUND   ";
unsigned char a,b;
unsigned char arr[5];
int i,j,k,m,index,flag,n;
unsigned char index1;

void main()
{
	lcd_init();
	P1=0x0F;
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);												
	msdelay(5000);
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg2);	
	P1 = P1 | 0x0F;
	msdelay(5000);
	b = P1;
	b = P1 & 0x0F;
	arr[0] = b;
	a = b;
	a = a << 4;
	P1 = a;
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg3);	
	P1 = P1 | 0x0F;
	msdelay(5000);
	for(i=1; i<4; i++){
	b = P1;
	b = b & 0x0F;
	arr[i]= b;
	a = b;
	a = a << 4;
	P1=0x0F;
	msdelay(1000);
	P1 = a;
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg3);
	P1 = P1 | 0x0F;	
	msdelay(5000);}
	b = P1;
	b = b & 0x0F;
	arr[4]= b;
	a = b;
	a = a << 4;
	P1=0x0F;
	msdelay(1000);
	P1 = a;
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg4);
	msdelay(5000);
	P1 = 0x0F;
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg5);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(display_msg6);
	msdelay(1000);
	for(k=0; k<4; k++){
		for(j=0; j<4-k; j++){
		if(arr[j]>arr[j+1]){
			char temp = arr[j+1];
			arr[j+1] = arr[j];
			arr[j] = temp;}}}
	for(m=0; m<5; m++){
		a = arr[m];
		a = a << 4;
		P1 = a;
		msdelay(5000);
		P1 = 0x0F;
		msdelay(1000);}
	P1 = 0xFF;
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(display_msg7);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(display_msg8);
	P1 = P1 | 0x0F;
	msdelay(5000);
	b = P1;
	b = b & 0x0F;
	a = b;
	a = a << 4;
	a = a >> 4;
	lcd_cmd(0x01);
	P1 = 0x0F;
	msdelay(1000);
		flag = 0;
	for(n=0; n<5; n++){
		if(a == arr[n]){
			flag = 1; 
			index = n+1;
			index1 = index + '0';
			index1 = index1 << 4;}}
	if(flag == 1){
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(display_msg9);
	P1 = index1;
	msdelay(5000);}
	if(flag == 0){
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(display_msg10);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(display_msg11);
	msdelay(5000);}
		
}