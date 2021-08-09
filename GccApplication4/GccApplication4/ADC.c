/*
 * CFile1.c
 *
 * Created: 08/08/2021 11:33:51
 *  Author: Juanjo
 */ 

#include "ADC.h"


volatile unsigned short sensor; /* numero positivo de 16 bits (rango de 0 a 65535)
que indica el valor leido por el sensor */

volatile unsigned short temp = 0; /* numero positivo de 16 bits
(rango de 0 a 65535) que indica el valor de la temperatura multiplicado por 10 */


void ADC_init()
{
	ADMUX= 0b00000000; // Vref=AVCC, bit justificados a derecho, ADC0/PC0 pin de lectura

	// Divisor de frecuencia = 128 -> 16000KHz/128 = 125 KHz 
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
}

int ADC_GetData()
{	
	// Encendemos el ADC
	ADCSRA |= (1<<ADEN);
	_delay_us(10);	// Esperamos a que caliente

	// Mandamos el muestreo
	ADCSRA |= (1<<ADSC);

	// Esperamos a que muestree, leyendo el flag
	while( !(ADCSRA & (1<<ADIF)) );
	ADCSRA |= (1<<ADIF);	// Reiniciamos el flag

	// Apagamos el ADC
	ADCSRA &=~ (1<<ADEN);

	return ADC; //Retornamos el valor del registro ADC 
}

void ADC_Update(){
	sensor = ADC_GetData(); //Leo el valor del registro de ADC0
	temp = (sensor * 5000UL / 1024UL); //Valor de voltaje medido se obtiene mediante la ecucacion Vmedido = (sensor * 5000mV) / 2^10
	if (temp > 240)
	{
		PORTB = (0b00000001);
	}
	else
	{
		if (temp < 170)
		{
			PORTB = (0b00000010);			
		}
		else
		{
			PORTB = 0b00000000;
		}
	}		
}

