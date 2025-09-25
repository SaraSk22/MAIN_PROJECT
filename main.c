#include "types.h"
#include "adc.h"
#include "adc_defines.h"
#include "uart0.h"
#include "delay.h"

f32 aR0,aR1;

int main(void) 
{	
	Init_UART0();
  Init_ADC();
	
	while(1) 
	{
    aR0=Read_ADC(CH0);
		UART0_Tx_str("Voltage: ");
		UART0_Tx_float(aR0,3);
		UART0_Tx_str("\r\n");
		
		aR1=Read_ADC(CH1);
		UART0_Tx_str("Temp: ");
		UART0_Tx_int(aR1*100);
		UART0_Tx_str("\r\n");
		delay_ms(1000);

		
	}
}
