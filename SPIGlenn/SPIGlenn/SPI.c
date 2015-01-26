/*
 * SPI.c
 *
 * Created: 24-11-2014 13:38:42
 *  Author: Glennnn
 */ 
#include <avr/io.h>
#include "SPI.h"

int i = 0;
char byte = 0x00;

void initSPI()
{
	PRR0 &= !(1 << PRSPI); //PRSPI must be set to 0 to enable SPI module
}

void initMaster()
{
	SPCR |= (1<<MSTR);
	DDRB |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS); //Set MOSI, SCK and SS as output
	DDRB &= ~((1<<DD_MISO));					 //Set MISO as input						 				 
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);		 //Enable SPI and Master Mode, set clock rate as fck/16
}

void initSlave()
{
	DDRB |= (1<<DD_MISO);					  //Set MISO as output 
	DDRB &= ~((1<<DD_MOSI)|(DD_SCK)|(DD_SS)); //Set MOSI, SCK and SS as input
	SPCR |= (1<<SPE);						  //Enable SPI
	SPCR &= ~(1<<MSTR);						  //Enable Slave Mode
}

void transmitData(char data)
{
	SPDR = data;				//Put the byte that is going to be send in the Data Register
	while(!(SPSR & (1<<SPIF))); //Wait for the transmission to be complete
}

void fillStandardDataFrame(char buffer, char idH, char idL)
{
	PORTB |= 0x1;
	PORTB &= ~(0x1);

	if (buffer == 0)
	{
		transmitData(0x40); //load buffer 0
	}
	if (buffer == 1)
	{
		transmitData(0x42); //load buffer 1
	}
	if (buffer == 2)
	{
		transmitData(0x44); //load buffer 2
	}
	transmitData(idH);	//TXB0SIDH Identifier High
	transmitData(idL);	//TXB0SIDL Identifier Low
}

void setData(char buffer, char DLC, long long databytes)
{
	i = 0;
	PORTB |= 0x1;
	PORTB &= ~(0x1);
	transmitData(0x02); //write
	if (buffer == 0)
	{
		transmitData(0x35); //load buffer 0
	}
	if (buffer == 1)
	{
		transmitData(0x45); //load buffer 1
	}
	if (buffer == 2)
	{
		transmitData(0x55); //load buffer 2
	}
	
	transmitData(DLC); //TXB0DLC set data length
	while (i < DLC)
	{
		byte = (databytes & 0xFF); //give "byte" the value of the last 8 bits of "databytes" 
		transmitData(byte);		   //set byte
		databytes >>= 8;		   //shift to next byte
		i++;
	}
}

void transmitBuffer(char buffer, char priority)
{
	byte = (0x8 | priority);
	PORTB |= 0x1;
	PORTB &= ~(0x1);	
	transmitData(0x02);
	
	if (buffer == 0)
	{
		transmitData(0x30); //fill buffer 0
		transmitData(byte);
	}
	if (buffer == 1)
	{
		transmitData(0x40); //fill buffer 1
		transmitData(byte);	
	}
	if (buffer == 2)
	{
		transmitData(0x50); //fill buffer 2
		transmitData(byte);		
	}
}

void readRegisters(char startAddress, int amountOfAddresses)
{
	i = 0;
	PORTB |= 0x1;
	PORTB &= ~(0x1);
		
	transmitData(0x03);
	transmitData(startAddress);
	while(i < amountOfAddresses)
	{
		transmitData(0x00);
		i++;
	}
	
}

char receiveData()
{
	while(!(SPSR & (1<<SPIF))); //Wait for the reception to be complete
	return SPDR;				//Return the Data Register
}