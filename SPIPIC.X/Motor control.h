/*
 * File:   Motor control.h
 * Author: Jorg
 *
 * Created on 15 december 2014, 14:20
 */

#ifndef MOTOR_CONTROL_H
#define	MOTOR_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

    void Motor_control_init(void);

    void PWM_init(void);
    void motor_start(char, int);
    void motor_stop(void);

    void stopper_init(void);

    void interrupt IOC_ISR(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_CONTROL_H */