//pin_connect_block.c
#include<LPC21XX.h>
#include"types.h"
void cfgportpinFunc(u32 portNo,
					u32 pinNo,
					u32 pinFunc)
{
	if(portNo==0)
	{
		if(pinNo<16)
		{
			PINSEL0=((PINSEL0&~(pinFunc<<(pinNo*2)))|(pinFunc<<(pinNo*2)));
		}
		else if((pinNo>=16)&&(pinNo<32))
		{
			PINSEL1=((PINSEL1&~(pinFunc<<((pinNo%16)*2)))|(pinFunc<<((pinNo%16)*2)));
		}
	}
}

