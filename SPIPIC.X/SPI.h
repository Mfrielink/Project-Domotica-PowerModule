/* 
 * File:   SPI.h
 * Author: Glennnn
 *
 * Created on 16 december 2014, 11:59
 */

#ifndef SPI_H
#define	SPI_H
/*
#define SSPSTAT (*(unsigned int *)0x94) //SYNC SERIAL PORT STATUS REGISTER
#define SSPCON (*(unsigned int *)0x14)  //SYNC SERIAL PORT CONTROL REGISTER
#define TRISB (*(unsigned int *)0x86)   //PORTB TRI-STATE REGISTER
#define TRISC (*(unsigned int *)0x87)   //PORTC TRI-STATE REGISTER
#define SSPBUF (*(unsigned int *)0x87)  //SSP Receive Buffer/Transmit Register
*/
#define CKEa    7
#define SSPENa  5
#define CKPa    5
#define CKEaa   6
#define SMPa    7
#define TRISB6a 6
#define TRISC6a 6
#define TRISC7a 7
#define SSPMa   0x0


void initSPI();
void initMaster();
void initSlave();
void transmitData(char data);
void fillStandardDataFrame(char buffer, char idH, char idL);
void setData(char buffer, char DLC, long databytes1, long databytes2);
void transmitBuffer(char buffer, char priority);
void readRegisters(char startAddress, int amountOfAddresses);

void readBuffer();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

