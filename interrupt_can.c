#include<LPC21XX.h>
#include "types.h"
#include "interrupt.h"
#include "pin_connect_block.h"
#define PIN_FUNC4 3
#define EINT0_INPUT_PIN PIN_FUNC4
#define EINT0_PIN 1
#define EINT0_VIC_CHNO 14
#define PIN_FUNC4 3
#define EINT3_INPUT_PIN PIN_FUNC4
#define EINT3_PIN 20
#define EINT3_VIC_CHNO 17

void Init_ENT()
{
	cfgportpinFunc(0,1,EINT0_INPUT_PIN);
	cfgportpinFunc(0,20,EINT3_INPUT_PIN);
	VICIntEnable=1<<EINT0_VIC_CHNO;
	VICIntEnable=1<<EINT3_VIC_CHNO;
	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
	VICVectCntl1=(1<<5)|EINT3_VIC_CHNO;	
	VICVectAddr0=(u32)eint0_isr;
	VICVectAddr1=(u32)eint3_isr;
	EXTINT=0;
	EXTMODE=1<<0|1<<3;
	EXTPOLAR=0;
}
