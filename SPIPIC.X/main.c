/* 
 * File:   main.c
 * Author: Glennnn
 *
 * Created on 16 december 2014, 11:30
 */


#include <stdio.h>
#include <stdlib.h>
#include "C:\Program Files (x86)\Microchip\xc8\v1.33\include\pic16f690.h"
#include "SPI.h"
#include "Motor control.h"

int main(int argc, char** argv) {
    initSPI();
    //initSlave();
    Motor_control_init();
    
    initMaster();

    PORTC |= 0x40;
    PORTC &= ~(0x40);
    transmitData(0x02); //write
    transmitData(0x60); //to address 0x0F and up
    transmitData(0x60); //masks/filters off, receive any msg

    PORTC |= 0x40;
    PORTC &= ~(0x40);
    transmitData(0x02); //write
    transmitData(0x0F); //to address 0x0F and up
    transmitData(0x07);

    
//    fillStandardDataFrame(0, 0x00, 0x00);
//    setData(0, 1, 0xBB, 0x00);
//    transmitBuffer(0, 0x3);

    while(1)
    {
        readBuffer();
    }
    return (EXIT_SUCCESS);
}





 