/*
 * SPIGlenn.c
 *
 * Created: 24-11-2014 13:38:24
 *  Author: Glennnn
 */ 


#include <avr/io.h>
#include "SPI.h"
//#define F_CPU 16000000

int main(void)
{
	initSPI();
	initMaster();
	//initSlave();
	//readRegisters(0x2A, 1);
	
	//transmitData(0x02); //write
	//transmitData(0x2B); //to address 0x0F and up
	//transmitData(0x1F);
	
	
	
	fillStandardDataFrame(0, 0x00, 0x00);
	setData(0, 1, 0xDD);
	transmitBuffer(0, 0x3);

	PORTB |= 0x1;
	PORTB &= ~(0x1);

	transmitData(0x02); //write
	transmitData(0x0F); //to address 0x0F and up
	transmitData(0x07);
	
	//readRegisters(0x30, 15);
/*
	PORTB |= 0x1;
	PORTB &= ~(0x1);
	transmitData(0x02);
	transmitData(0x2B);
	transmitData(0x04);
*/
	while(1)
	{
        //TODO:: Please write your application code 
    }
}