#include<LPC21XX.h>
#include "types.h"
#include "delay.h"
#include"lcd_defines.h"
void writeLCD(u8 byte)
{
	IOCLR0=1<<LCD_RW;
	IOPIN0=((IOPIN0&~(0XFF<<LCD_DATA))|(byte<<LCD_DATA));
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;
	delay_ms(2);
}
void cmdLCD(u8 cmd)
{
	IOCLR0=1<<LCD_RS;
	writeLCD(cmd);
}
void charLCD(u8 ascii)
{
	IOSET0=1<<LCD_RS;
	writeLCD(ascii);
}
void InitLCD(void)
{
	IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	delay_ms(15);
	cmdLCD(0X30);
	cmdLCD(0X30);
	cmdLCD(0X30);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(DSP_ON_CUR_OFF);
//	cmdLCD(CLEAR_LCD);
//	cmdLCD(SHIFT_CUR_RIGHT);
}
void strLCD(s8 *s)
{
	while(*s)
		charLCD(*s++);
}
void u32LCD(u32 n)
{
	s32 i=0;
	u8 digit[10];
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n>0)
		{
			digit[i]=(n%10)+48;
			n=n/10;
			i++;
		}
		for(--i;i>=0;i--)
		{
			charLCD(digit[i]);
		}
	}
}
void s32LCD(s32 n)
{
	if(n<0)
	{
		charLCD('-');
		n=-n;
	}
	u32LCD(n);
}
void f32LCD(f32 fnum,u8 ndp)
{
	s32 i;
	u32 n;
	if(fnum<0)
	{
		charLCD('-');
		fnum=-fnum;
	}
	n=fnum;
	u32LCD(n);
	charLCD('.');
	for(i=0;i<ndp;i++)
	{
		fnum=(fnum-n)*10;
		n=fnum;
		charLCD(n+48);
	}
}


