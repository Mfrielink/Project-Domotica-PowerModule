/*
 * PowerModule.c
 *
 * Created: 16-12-2014 16:47:00
 *  Author: Martijn
 */ 
#include "contiki.h"
#include "adc.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000

PROCESS(main_program, "Test process");
AUTOSTART_PROCESSES(&main_program);


PROCESS_THREAD(main_program, ev, data)
{
	PROCESS_BEGIN();	
		
		/*
			SPI code here
		*/
		
	PROCESS_END();
}



/*	Test code for ADC-thread

	static struct etimer et;
	PROCESS_BEGIN();

	uint16_t temp;
	adc_init();
	adc_test_init();

	etimer_set(&et, CLOCK_SECOND);
		   
	while(1)
	{
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	
		etimer_reset(&et);
		
		printDouble(calculateVoltage(read_adc()));
	}
	PROCESS_END();
		
*/

