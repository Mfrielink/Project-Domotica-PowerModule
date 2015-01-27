/*
 * SPI.h
 *
 * Created: 24-11-2014 13:40:18
 *  Author: Glennnn
 */ 


#ifndef SPI_H_
#define SPI_H_

//#define PRR0 (*(unsigned int *)0x64) //Power Reduction Register0
//#define SPDR (*(unsigned int *)0x2E) //SPI Data Register
//#define SPSR (*(unsigned int *)0x2D) //SPI Status Register
//#define SPCR (*(unsigned int *)0x2C) //SPI Control Register
//#define DDRB (*(unsigned int *)0x04) //Port B Data Direction Register

#define PRSPI 2 //Power Reduction SPI bit
#define MSTR  4 //Master/Slave Mode Select
#define SPE   6 //SPI Enable
#define SPR0  0 //SPI Clo\ck Rate Select 0
#define SPIF  7 //SPI Interrupt Flag

//Data Direction bits
#define DD_SS	0
#define DD_SCK  1
#define DD_MOSI 2
#define DD_MISO 3

void initSPI();
void initMaster();
void initSlave();
void transmitData(char data);
void fillStandardDataFrame(char buffer, char idH, char idL);
void setData(char buffer, char DLC, long long databytes);
void transmitBuffer(char buffer, char priority);
void readRegisters(char startAddress, int amountOfAddresses);
char receiveData();
void testMotor();

#endif /* SPI_H_ */
