//adc_test.c
#include<LPC21XX.h>
#include"types.h"
#include"delay.h"
#include"pin_connect_block.h"
//clockdefines
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADC_CLK 3000000
#define CLKDIV ((PCLK/ADC_CLK)-1)
//ADCR sfr defines
#define CLKDIV_BITS 8
#define PDN_BIT 21
#define ADC_START_CONV_BIT 24
//ADDR sfr defines
#define ADCDVAL_BITS 6
#define DONE_BIT 31
void Init_ADC(void)
{
	//cfg p0.27 to 0.30 as ADC analog input pins
	//cfgportpinFunc(0,27,1);
	//cfgportpinFunc(0,28,1);
	//cfgportpinFunc(0,29,1);
	//cfgportpinFunc(0,30,1);
	//cfg ADCR sfr
	//ADCR&=0XFFFFFF00;
	ADCR=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
}
u32 adcDval;
f32 eAR;
void Read_ADC(u8 chno,u32 *adcDval,f32 *eAR)
{
	ADCR&=0XFFFFFF00;
	ADCR|=1<<chno;
	ADCR|=1<<ADC_START_CONV_BIT;
	delay_us(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<ADC_START_CONV_BIT);
	*adcDval=((ADDR>>ADCDVAL_BITS)&1023);
	*eAR=(3.3/1023)*(*adcDval);
//	return eAR;
}
