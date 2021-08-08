/*
 * GccApplication4.c
 *
 * Created: 08/08/2021 11:33:23
 * Author : Juanjo
 */ 

#include <avr/io.h>
#include "ADC.h"
#include "SEOS.h"
#include "lcd.h"


int main(void)
{
	
	DDRB = 0x03;
	DIDR0= 0x01;
	ADC_init();	
	LCD_Init();
	SEOSTimer0Init();
			
    while (1) 
    {
		SEOSDispatcherTasks();
    }
}

