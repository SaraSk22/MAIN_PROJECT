#include<LPC21XX.h>					   
#include"can.h"
#include"can_defines.h"
#include"defines.h"
#include"delay.h"
#define LED 0

int main(void)
{
	struct CAN_Frame rxFrame;
	s32 i;
	Init_CAN1();
	IODIR0|=255<<LED;
	delay_ms(1000);
	IOSET0=255<<LED;  
	while(1)
	{
		CAN1_Rx(&rxFrame);
		if(rxFrame.ID==10)
		{
		//IOCLR0=0X5A<<0;
			if(rxFrame.Data1=='L')
			{
				for(i=0;i<=7;i++)
				{
					IOCLR0=1<<i;
				   // IOPIN0=~(1<<i);
					delay_ms(100);
					IOSET0=1<<i;
					
				}
			}
			else if(rxFrame.Data1=='R')
			{
				for(i=7;i>=0;i--)
				{	  
					IOCLR0=1<<i;
				//	IOPIN0=~(1<<i);
					delay_ms(100);
					IOSET0=1<<i;
					
				}
			}
		}
	}
}
