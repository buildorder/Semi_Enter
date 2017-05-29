/*
 * Semi_Enter.c
 *
 * Created: 2017-05-29 오후 8:42:29
 * Author : kms014
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "easy_usart.h"

#define E_INT_1 0b00000100
#define E_INT_2 0b00001000

void setup()
{
	// Set global interrupt enable
	sei();
	
	// Only rising edge
	EICRA =	0b00001111;
	
	// Enable external interrupt request
	EIMSK = 0x03;
	
}

int main(void)
{
	setup();
	
	easy_uart_setup(BAUD_RATE_9600, F_CPU);

    while (1);
}

ISR(_VECTOR(1))
{
	cli();
	_delay_ms(40);
	if (PIND & E_INT_1)
		printf("INT0\n");
	sei();
}

ISR(_VECTOR(2))
{
	cli();
	_delay_ms(40);
	if (PIND & E_INT_2)
		printf("INT1\n");
	sei();
}