/*
 * File:   Motor control.c
 * Author: Jorg
 *
 * Created on 15 december 2014, 14:19
 *
 * These functions are used to operate the motor and respond to the stopper signal.
 * For this file, the following pins are used:
 * PWM output 1 - RC5 (CCP1/P1A)
 * PWM output 2 - RC4 (P1B)
 * Stopper input 1 - RB5
 * Stopper input 2 - RB7
 *
 * Note: Do NOT use the following pins as output in combination with this funtion:
 * RC3 & RC2
 */

#include "C:\Program Files (x86)\Microchip\xc8\v1.33\include\pic16f690.h"
#include "Motor control.h"

char limit_left, limit_right;//, test;

/*
 * Interrupt used to handle any IOC trigger from the stopper.
 * This function will stop the motor when the outter limit is reached.
 */
void interrupt IOC_ISR(void)
{
    if(((PORTB & 0x80) >> 7) == 1)
    {
        motor_stop();
        limit_left = 1;
    }
    else if(((PORTB & 0x20) >> 5) == 1)
    {
        motor_stop();
        limit_right = 1;
    }
    //motor_stop();
    //motor_start(1, 0x7F);
    // &= 0xFE;                                                             //Clear the IOC interrupt
    RABIF = 0;
}


/*
 * Initialises the registers used for motor control
 */
void Motor_control_init()
{
    PWM_init();
    stopper_init();
}

/*
 * Initialises all PWM related functionalities.
 * The result is a PWM output signal configured to drive a H-bridge with 2
 * seperate PWM outputs.
 */
void PWM_init()
{
    limit_left = 0;
    limit_right = 0;

    TRISC |= 0x30;                                                              //Disable RC4 and RC5 output driver
    PR2 = 0xFF;                                                                 //Set the PWM period
    CCP1CON = 0x4C;                                                             //Set PWM to full bridge forward output
    CCPR1L = 0x8F;                                                              //Set PMW pulse width
    PIR1 &= 0xFD;                                                               //Clear the TIRM2IF flag
    PWM1CON = 0x08;                                                             //Set PWM delay to ensure the PWM outputs do not overlap
    T2CON = 0x03;                                                               //Set timer 2 prescaler to 16
    T2CON |= 0x04;                                                              //Turn timer2 on
    while((PIR1 & 0x02) == 0){}                                                 //Wait until timer2 overflows
}

/*
 * Initialises all stopper related functionalities.
 * These will use IOC (Interrupt On Change) to detect whenever the motor has
 * reached its outter limit.
 */
void stopper_init()
{
    ANSEL = 0;          //Initialize A/D ports off
    ANSELH = 0;         //Initialize A/D ports off
    PORTB = 0x00;       //Clears PORTB port
    TRISB = 0xFF;       //Sets PORTB to all input

    IOCB5 = 1;          //Enabled RB5 Interrupt-On-Change
    IOCB7 = 1;          //Enabled RB7 Interrupt-On-Change
    RABIE = 1;
    RABIF = 0;
    GIE = 1;            //Enables Global Interrupts
}

/*
 * Start the motor in the direction specified by 'dir'.
 * Dir = 1 -> Forward (PWM output @ RC5/P1A)
 * Dir = 0 -> Backwards (PWM output @ RC4/P1B)
 * For all other values of Dir this function will default to forwards.
 */
void motor_start(char dir, int speed)
{
    TRISC |= 0x30;                                                              //Disable RC4 and RC5 output drivers
    CCPR1L = speed;                                                             //Set PWM duty cycle with 0x00 = 0%, 0x7F = 50% and 0xFF = 100% (linear increase)
    if(!dir && !limit_right)
    {
        CCP1CON |= 0x80;                                                        //Set P1B as PWM and leave P1A output disabled
        TRISC &= 0xEF;                                                          //Set RC4 output driver
    }
    else if(dir && !limit_left)
    {
        CCP1CON &= 0xBF;                                                        //Set P1A as PWM and leave P1B output disabled
        TRISC &= 0xDF;                                                          //Set RC5 output driver
    }
    else{}
}

/*
 * Stops all motor movement
 */
void motor_stop()
{
    CCPR1L = 0;                                                                 //Set PWM duty cycle to 0%
    TRISC |= 0x30;                                                              //Reset RC4 and RC5 output drivers
}