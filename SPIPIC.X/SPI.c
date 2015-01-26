#include "SPI.h"
#include "C:\Program Files (x86)\Microchip\xc8\v1.33\include\pic16f690.h"
#include "Motor control.h"

int i = 0;
char byte = 0x00;

void initSPI()
{
    SSPCON &= ~(1 << CKPa);  //Idle state for clock is a low level
    SSPSTAT &= ~(1 << SMPa); //Input data sampled at middle of data output time
    SSPSTAT |= (1 << CKEaa); //Data transmitted on rising edge of SCK
}

void initMaster()
{
    SSPCON &= ~(0xF);         //Set SPI Master mode, clock = Fosc/4
    SSPCON &= ~(1 << SSPENa); //Clear enable bit
    SSPCON |= (1 << SSPENa);  //Set enable bit
    TRISC &= ~(1 << TRISC7a); //Set SDO as output
    TRISB &= ~(1 << TRISB6a); //Set SCK as output
    TRISC &= ~(1 << TRISC6a); //Set SS as input
}

void initSlave()
{
    SSPCON &= ~(0xF);         //Clear SSPM bits
    SSPCON |= 0x5;            //Set Slave mode, Clock = SCK, SS pin control
                              //disabled, SS can be used as I/O pin
    SSPCON &= ~(1 << SSPENa); //Clear enable bit
    SSPCON |= (1 << SSPENa);  //Set enable bit
    TRISC &= ~(1 << TRISC7a); //Set SDO as output
    TRISB |= (1 << TRISB6a);  //Set SCK as input
    TRISC |= (1 << TRISC6a);  //Set SS as input
}

void transmitData(char data)
{
    SSPBUF = data;
}

void fillStandardDataFrame(char buffer, char idH, char idL)
{
    PORTC |= 0x40;
    PORTC &= ~(0x40);

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

void setData(char buffer, char DLC, long databytes1, long databytes2)
{
    i = 0;
    PORTC |= 0x40;
    PORTC &= ~(0x40);
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
    while (i < DLC && i < 4)
    {
        byte = (databytes1 & 0xFF); //give "byte" the value of the last 8 bits of "databytes"
        transmitData(byte);         //set byte
        databytes1 >>= 8;           //shift to next byte
        i++;
    }
    while (i < DLC && i >= 4)
    {
        byte = (databytes2 & 0xFF); //give "byte" the value of the last 8 bits of "databytes"
        transmitData(byte);         //set byte
        databytes2 >>= 8;           //shift to next byte
        i++;
    }
}

void transmitBuffer(char buffer, char priority)
{
    byte = (0x8 | priority);
    PORTC |= 0x40;
    PORTC &= ~(0x40);
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
    PORTC |= 0x40;
    PORTC &= ~(0x40);

    transmitData(0x03);
    transmitData(startAddress);
    while(i < amountOfAddresses)
    {
        transmitData(0x00);
        i++;
    }
}

void readBuffer()
{
    PORTC |= 0x40;
    PORTC &= ~(0x40);
    transmitData(0x02); //write
    transmitData(0x2C);
    transmitData(0x00);

    readRegisters(0x66, 1);

//    PORTC |= 0x40;
//    PORTC &= ~(0x40);
//    transmitData(0x03); //read
//    transmitData(0x66); //rec buff0 dbyte0
//    transmitData(0x00);

    if (SSPBUF == 0xDD)
    {
        motor_start(1, 0x01);
    }

    if (SSPBUF == 0xEE)
    {
        motor_start(0, 0x7F);
    }
}

