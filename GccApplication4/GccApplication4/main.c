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
	
	DDRB = 0x03; //Seteo a PB0 y PB1 como pin de salida
	DIDR0= 0x01; //Seteo ADC0 como pin de lectura
	ADC_init();	//Inicializo el ADC
	LCD_Init(); //Inicializo el LCD
	SEOSTimer0Init(); //Inicializo el atendedor de interrupciones
			
    while (1) 
    {
		SEOSDispatcherTasks();
    }
}

