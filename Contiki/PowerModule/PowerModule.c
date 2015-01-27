/*
 * PowerModule.c
 *
 * Created: 16-12-2014 16:47:00
 *  Author: Martijn
 */ 
#include "contiki.h"
#include "adc.h"
#include "spi.h"

#include "sys/mt.h"

#include "contiki-net.h"
#include "lib/random.h"
#include "sys/ctimer.h"
#include "contiki/core/net/uip.h"
#include "contiki/core/net/uip-ds6.h"
#include "contiki/core/net/uip-udp-packet.h"
#include "sys/ctimer.h"
#include <stdio.h>
#include <string.h>
#include "6lowpan/tcp_ip.h"


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 16000000

PROCESS(main_program, "The main process");
PROCESS(spi_program, "The SPI process");
PROCESS(adc_program, "The ADC process");
PROCESS(device_program, "The device process");


AUTOSTART_PROCESSES(&spi_program);

	
PROCESS_THREAD(main_program, ev, data)
{
	static struct etimer et;
	
PROCESS_BEGIN();

initSPI();
initMaster();

etimer_set(&et, (5*CLOCK_SECOND));

	transmitData(0x02); //write
	transmitData(0x0F); //to address 0x0F and up
	transmitData(0x17);
	
	
printf("Motor left\n");
PORTB |= 0x1;
PORTB &= ~(0x1);
fillStandardDataFrame(0, 0x00, 0x00);
setData(0, 1, 0xDD);
transmitBuffer(0, 0x3);


PORTB |= 0x1;
PORTB &= ~(0x1);

transmitData(0x02); //write
transmitData(0x0F); //to address 0x0F and up
transmitData(0x07);


PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
etimer_reset(&et);



printf("Motor stop\n");
PORTB |= 0x1;
PORTB &= ~(0x1);
fillStandardDataFrame(0, 0x00, 0x00);
setData(0, 1, 0xCC);
transmitBuffer(0, 0x3);
PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
etimer_reset(&et);


printf("Motor right\n");
PORTB |= 0x1;
PORTB &= ~(0x1);
fillStandardDataFrame(0, 0x00, 0x00);
setData(0, 1, 0xEE);
transmitBuffer(0, 0x3);
PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
etimer_reset(&et);


printf("Motor stop\n");
PORTB |= 0x1;
PORTB &= ~(0x1);
fillStandardDataFrame(0, 0x00, 0x00);
setData(0, 1, 0xCC);
transmitBuffer(0, 0x3);
PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
etimer_reset(&et);

PROCESS_END();
}
/*
{
	PROCESS_BEGIN();
	

	process_start(&spi_program, NULL);
	
	printf("klaar");
	
	PROCESS_END();
}

*/
PROCESS_THREAD(spi_program, ev, data)
{
	//static struct mt_thread alpha_thread;
	//static struct mt_thread count_thread;
	
	static struct etimer et;
	PROCESS_BEGIN();	
		
		initSPI();
		initMaster();

		etimer_set(&et, (5*CLOCK_SECOND));
		
		
			printf("Motor left\n");
			PORTB |= 0x1;
			PORTB &= ~(0x1);
			fillStandardDataFrame(0, 0x00, 0x00);
			setData(0, 1, 0xDD);
			transmitBuffer(0, 0x3);
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
			etimer_reset(&et);
			
			
			printf("Motor stop\n");
			PORTB |= 0x1;
			PORTB &= ~(0x1);
			fillStandardDataFrame(0, 0x00, 0x00);
			setData(0, 1, 0xCC);
			transmitBuffer(0, 0x3);
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
			etimer_reset(&et);
			
			
			printf("Motor right\n");
			PORTB |= 0x1;
			PORTB &= ~(0x1);
			fillStandardDataFrame(0, 0x00, 0x00);
			setData(0, 1, 0xEE);
			transmitBuffer(0, 0x3);
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
			etimer_reset(&et);
			
			
			printf("Motor stoop\n");
			PORTB |= 0x1;
			PORTB &= ~(0x1);
			fillStandardDataFrame(0, 0x00, 0x00);
			setData(0, 1, 0xCC);
			transmitBuffer(0, 0x3);
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
			etimer_reset(&et);
		
	PROCESS_END();
}

PROCESS_THREAD(device_program, ev, data)
{
	device *one, *two, *three, *four;
	process_event_t spi_event;
	
	static struct etimer periodic;
	static struct ctimer backoff_timer;
	
	PROCESS_BEGIN();
		PROCESS_PAUSE();
	
		if(!init_client()) PROCESS_EXIT();
		one =	create_device(1, "Current sensor",	"IconOne",	 2, "A",	"0", "220", 4, 1, 1);
		two =	create_device(2, "Relais",			"IconTwo",	 2, "ON",	"0", "1", 1, 1, 0);
		three = create_device(3, "Motor direction", "IconThree", 2, "DIR",	"0", "1", 1, 1, 0);
		four =	create_device(3, "Motor speed",		"IconFour",	 2, "SPD",	"0", "255", 3, 1, 0);
		add_device(one);
		add_device(two);
		add_device(three);
		add_device(four);
		print_device_list();
		etimer_set(&periodic, SEND_TIME);
		while(1) {
			PROCESS_YIELD();
			if(ev == tcpip_event) {
				tcpip_handler();
			}
			devs_init = are_devs_registered();
			if(etimer_expired(&periodic)) {
				etimer_reset(&periodic);
				if(client_init==FALSE){
					ctimer_set(&backoff_timer, SEND_TIME, initialize_client_on_server, NULL);
				}
				else if(devs_init==FALSE){
					ctimer_set(&backoff_timer, SEND_TIME, send_rpc_packet, NULL);
				}
				else{}
			}
		}
	PROCESS_END();
}



PROCESS_THREAD(adc_program, ev, data)
{
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
}
