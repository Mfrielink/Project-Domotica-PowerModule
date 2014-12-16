/*
 * Domotica.c
 *
 * Created: 3-7-2014 12:00:57
 *  Author: Jorg
 */ 


#include <avr/io.h>
#include "Domotica.h"
#include "ADC.h"

int main(void)
{
	//uint16_t test0, test1 = 0;
	PWM_init();
	adc_init();
	adc_test_init();
    while(1)
    {
		adc_test(read_adc());
		
		/* Test functions
		test0 = ADCL;
		PORTE = ADCL;
		test1 = ADCH;
		PORTE = ADCH;
		test1 = ADCH;
		PORTE = 0x55;
		*/
		
		/*
		test1++;
		adc_test(test0);
		if(test1 == 6000)
		{
			test0++;
			test1 = 0;	
		}
		if(test0 == (2^10))
			test0 = 0;
		*/
    }
}

void PWM_init()
{
	DDRB |= (1 << DDB7);								//Set pin B7 to output
	OCR0A = 128;										//Set duty cycle to 50%
	TCCR0A |= (1 << COM0A1);							//Set OC0A (Pin B7) operation to non-inverted PWM mode
	TCCR0A |= (1 << WGM01) + (1 << WGM00);				//Set operation to PWM, Phase correct with TOP = 0xFF
	TCCR0B |= (1 << CS01);								//Set operation to PWM with top = OCRA and clkIO/8 (from prescaler)		
}

