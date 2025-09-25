#include<LPC21XX.h>
#include"lcd.h"
#include"lcd_defines.h"
#include"can.h"
#include"can_defines.h"
#include"delay.h"
#include"interrupt.h"
#include"i2cc_defines.h"
#include"i2cc.h"
#include"pin_connect_block.h"
#define PIN_FUNC4 3
#define EINT0_INPUT_PIN PIN_FUNC4
#define EINT0_PIN 1
#define EINT0_VIC_CHNO 14
#define PIN_FUNC4 3
#define EINT3_INPUT_PIN PIN_FUNC4
#define EINT3_PIN 20
#define EINT3_VIC_CHNO 17
#define threshold 20

void eint0_isr(void) __irq;
void eint3_isr(void) __irq;	  

void Init_MMA7660(void);
u8 read_MMA7660(u8 reg);


volatile s8 x,y,z;
volatile u8 flag=0;
volatile u8 leftflag=0;
volatile u8 rightflag=0;
volatile u32 fuelper;

int main()
{
	
	struct CAN_Frame rxFrame,txFrame;
	PINSEL0=((PINSEL0&~(3<<2))|(3<<2));
	PINSEL1=((PINSEL1&~(3<<((20%16)*2)))|(3<<((20%16)*2)));
	cfgportpinFunc(0,1,EINT0_INPUT_PIN);
	cfgportpinFunc(0,20,EINT3_INPUT_PIN);
	InitLCD();
	Init_CAN1();
	Init_i2c();
  Init_MMA7660();
	txFrame.ID=10;
	txFrame.vbf.RTR=0;
	txFrame.vbf.DLC=1;

	VICIntSelect=0;
	VICIntEnable=1<<EINT0_VIC_CHNO;
	VICIntEnable|=1<<EINT3_VIC_CHNO;
	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;		
	VICVectAddr0=(u32)eint0_isr;

	VICVectCntl1=(1<<5)|EINT3_VIC_CHNO;
	VICVectAddr1=(u32)eint3_isr;
	EXTINT=0;
	EXTMODE=1<<0|1<<3;
	EXTPOLAR=0;
	//IODIR0|=1<<7;
	while(1)
	{
		if(((C1GSR>>0)&1))
		{
			CAN1_Rx(&rxFrame);
			if((rxFrame.ID==11)&&(rxFrame.vbf.DLC>=1))
			{

	       		fuelper=rxFrame.Data1;
						cmdLCD(GOTO_LINE1_POS0);
						strLCD("Fuel:");
						strLCD("     ");
						cmdLCD(GOTO_LINE1_POS0+6);
						u32LCD(fuelper);
						charLCD(0x25);
			}
		}
		x=read_MMA7660(0x00);
		y=read_MMA7660(0x01);
		z=read_MMA7660(0x02);	
		if(leftflag)
		{
			txFrame.Data1='L';
			CAN1_Tx(txFrame);
			cmdLCD(GOTO_LINE1_POS0+11);
			charLCD('L');
			delay_ms(200);     
		}
		else if(rightflag)
		{
			txFrame.Data1='R';
			CAN1_Tx(txFrame);
			cmdLCD(GOTO_LINE1_POS0+11);
			charLCD('R');
			delay_ms(200);     
		}
		else
		{
				leftflag=0;
				rightflag=0;
				//cmdLCD(GOTO_LINE1_POS0+11);
				//strLCD("    ");
		} 
/*		x=read_MMA7660(0x00);
		y=read_MMA7660(0x01);
		z=read_MMA7660(0x02);			 */
		if((x<(-threshold))||(x>threshold)||
			 (y<(-threshold))||(y>threshold)||
			 (z<(-threshold))||(z>threshold)||(z<(-25)))
		{
		  cmdLCD(GOTO_LINE2_POS0);
			strLCD("           ");
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("AIRBAGOPEN");
		}
		else
		{
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("           ");
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("SAFE");
		}	
		delay_ms(500);
	}		

}  	  		
void eint0_isr(void) __irq
{
	leftflag=!leftflag;
	rightflag=0;
	EXTINT=1<<0;
	VICVectAddr=0;
}
void eint3_isr(void) __irq
{
	rightflag=!rightflag;
	leftflag=0;
	EXTINT=1<<3;
	VICVectAddr=0;
}

void Init_MMA7660()
{
	i2c_start();
	i2c_write(0x98); //MMA7660 slave address + write mode
	i2c_write(0x07); // main buffer address
	i2c_write(0x01); // on/off mode
	i2c_stop();
//	delay_ms(10);
}

u8 read_MMA7660(u8 reg)
{
	u8 data;
	i2c_start();
	i2c_write(0x98);
	i2c_write(reg);
	i2c_restart();
	i2c_write(0x99); //slave address + read mode
	data=i2c_nack();
	if(data>31)
	{
		data=data-64;
	}
	i2c_stop();
	delay_ms(10);
  return data;
}
                                                                                                                                         