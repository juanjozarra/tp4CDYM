/*
 * CFile1.c
 *
 * Created: 08/08/2021 11:34:23
 *  Author: Juanjo
 */ 

#include "SEOS.h"
#include "ADC.h"
#include "lcd.h"
#include <avr/interrupt.h>

static unsigned char ADC_Flag=1;
static unsigned char LCD_Flag=0;

void SEOSSChedulerTasks();


void SEOSTimer0Init(){
	OCR0A = 156; //Valor con el cual comparar
	TCCR0A = (1<<WGM01);// = 0b00000010; Modo CTC
	TCCR0B = (1<<CS02)|(1<<CS00); // = 0b00000101; clk/1024 (From Prescaler) 16MHz/1024 =  15625 Hz
	TIMSK0 = (1<<OCIE0A); // Habilita el comparador. T=156/15625 Hz = 9.984ms ~= 10 ms
	sei();
}


void SEOSDispatcherTasks(){
	if(ADC_Flag){
		ADC_Update();
		ADC_Flag = 0;
	}
	if(LCD_Flag){
		LCD_Update();
		LCD_Flag = 0;
	}
}


ISR(TIMER0_COMPA_vect){
	SEOSSChedulerTasks();
}

void SEOSSChedulerTasks(){
	static char adcCont=0, lcdCount=0;
	
	if(++adcCont==50)
	{
		ADC_Flag = 1;
		adcCont=0;
	}
	if(++lcdCount==50){
		LCD_Flag=1;
		lcdCount=0;
	}
}

