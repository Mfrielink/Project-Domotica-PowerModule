/*
 * ADC.c
 *
 * Created: 16-12-2014 10:02:56
 *  Author: Jorg
 */ 

#include <avr/io.h>
#include "ADC.h"

void adc_init()
{
	ADMUX &= 0xE0;										//Set conversion channel to 0 (PF0)
	ADCSRA |= (1<<ADEN);								//Turn on ADC
	ADCSRA |= ((1<<ADPS2)+(1<<ADPS1)+(1<<ADPS0));		//16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= ((1<<REFS1)+(1<<REFS0));					//Set reference to internal 1.6V AREF
	ADMUX |= (1<<ADLAR);								//Turn on left adjust
}

uint16_t read_adc()
{
	ADCSRA |= (1<<ADSC);								//Starts a new conversion
	while((ADCSRA & (1<<ADSC))!=0);						//Wait until the conversion is done
	ADCSRA |= (1<<ADIF);								//Clear the interrupt									
	return ADCH;										//Returns the ADC value of the chosen channel
}

//Test functions
void adc_test_init()
{
	DDRE |= 0xFF;										//Set entire port E as output
	PORTE &= 0x00;										//Set entire port E to output low
}

void adc_test(uint16_t val)
{
	uint16_t i;
	uint16_t y = 1;
	uint16_t x = ((2^264)/8);									//Set LED resolution value
	for(i = 0; i < 8; i++)
	{
		if(i*x < val)
		{
			y = y << 1;
			y++;
		}
	}
	PORTE = y;
}