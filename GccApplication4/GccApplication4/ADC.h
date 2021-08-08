/*
 * IncFile1.h
 *
 * Created: 08/08/2021 11:34:06
 *  Author: Juanjo
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>

void ADC_init();
int ADC_GetData();
void ADC_Update();


#endif 