/*
 * GccApplication1.c
 *
 * Created: 11/18/2014 11:40:00 AM
 *  Author: Jorg
 */ 

#include "contiki.h"
#include <avr/io.h>

int main(void)
{
    while(1)
    {
        asm("nop");
    }
}