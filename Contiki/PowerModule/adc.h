/*
 * ADC.h
 *
 * Created: 16-12-2014 10:04:35
 *  Author: Jorg
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);					//Function to initialize/configure the ADC
uint16_t read_adc(void);				//Function to read MUX5
double calculateVoltage(int numbOfBits);	//Function to calculate the measured voltage
void printDouble(double x);

void adc_test_init();
void adc_test(uint16_t);

#endif /* ADC_H_ */