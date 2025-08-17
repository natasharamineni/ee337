#include <at89c5131.h>
#include "lcd.h"

code unsigned char display_msg1[]=" Enter Password ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]="Correct Password";						//Display msg on 2nd line of lcd
code unsigned char display_msg3[]=" Access Granted ";
code unsigned char display_msg4[]=" Wrong Password ";						//Display msg on 2nd line of lcd
code unsigned char display_msg5[]=" Access Denied  ";

code unsigned char pswd[8] = "15A8*D6#";
unsigned char entry[8];
code unsigned char lookuptable[4][4] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
int i,m; 
int j=0;
int k=0;
int l=1;
unsigned char a, b, inp;
int row, column;
int incorrect=0;
unsigned char key[8];

void main()
{
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(display_msg1);
	lcd_cmd(0xC0);
	msdelay(4);

	for(i=0;i<8; i++)
	{	
		j=0;
		k=0;
		l=1;
		P3 = 0x0F;
		while(k==0)
		{  
			while(j==0)
			{
				P3 = 0x0F;
				a = P3 & 0x0F;	
				if(a == 0x0F){j = 1;}  //if columns are high then no key pressed so get out of loop
			}

			while(l==1)
			{
				P3 = 0x0F;
				a = P3 & 0x0F;
				if(a != 0x0F){l=0;} // if columns are high then no key pressed so check again
			}

			msdelay(20); //debounce
			P3 = 0x0F;
			a = P3 & 0x0F;
			if(a != 0x0F){k=1;} //if columns are high then check again
		}
		P3 = 0x0F;
		a = P3;
		P3 = 0xF0;
		b = P3;
		if(a == 0x07){column = 0;}
		if(a == 0x0B){column = 1;}
		if(a == 0x0D){column = 2;}
		if(a == 0x0E){column = 3;}
		if(b == 0x70){row = 3;}
		if(b == 0xB0){row = 2;}
		if(b == 0xD0){row = 1;}
		if(b == 0xE0){row = 0;}
		inp = lookuptable[row][column];
		key[i] = inp;
		lcd_write_char(inp);
	}
	lcd_cmd(0x01);
	for(m=0; m<8; m++)
	{if(key[m] != pswd[m]){incorrect=1;}}
	if(incorrect==1)
		{
			lcd_cmd(0x80);
			msdelay(4);
			lcd_write_string(display_msg4);
			lcd_cmd(0xC0);
			msdelay(4);
			lcd_write_string(display_msg5);
		}
	if(incorrect==0)
		{
			lcd_cmd(0x80);
			msdelay(4);
			lcd_write_string(display_msg2);
			lcd_cmd(0xC0);
			msdelay(4);
			lcd_write_string(display_msg3);
		}
		while(1);
}