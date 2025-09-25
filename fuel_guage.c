#include<LPC21XX.h>
#include"adc_defines.h"
#include "adc.h"
#include"defines.h"
#include"can.h"
#include"can_defines.h"
#include "lcd.h"
#define min 0.309
#define max 1.932
u32 fuelval;
u32 fuel_percent;
u32 adcdval;
f32 eaR;
int main()
{
	struct CAN_Frame txFrame;
	Init_CAN1();
	Init_ADC();
	InitLCD();
	while(1)
	{
		  Read_ADC(0,&adcdval,&eaR);
		  fuel_percent=((eaR-min)/(max-min))*100;
		  cmdLCD(0x80);
		  f32LCD(eaR,3);
		  if(fuel_percent>100)
		  {
		  	fuel_percent=100;
		  }	
		  txFrame.ID=11;
		  txFrame.vbf.RTR=0;
	     	  txFrame.vbf.DLC=1;
		  txFrame.Data1=fuel_percent;
		  CAN1_Tx(txFrame);
	}
}
