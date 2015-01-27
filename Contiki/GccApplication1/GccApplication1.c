/*
 * GccApplication1.c
 *
 * Created: 13-11-2014 12:06:38
 *  Author: Martijn
 */ 



#include "contiki.h"

#include <avr/io.h>
#include <util/delay.h>

	

PROCESS(my_first_process, "Test proces");
AUTOSTART_PROCESSES(&my_first_process);


PROCESS_THREAD(my_first_process, ev, data)
{
PROCESS_BEGIN();
		
		while(1){
			printf("Hallo Lukas!");
		}
PROCESS_END();	
}
