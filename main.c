/*
 * GccApplication2.c
 *
 * Created: 2/7/2025 12:50:05 PM
 * Author : acooper1171
 */ 

#define F_CPU 16000000UL // 16MHz clock from the debug processor
#define BAUD 9600
#define BAUDRATE ((F_CPU) / (BAUD*16UL)-1)
#include <avr/io.h>
#include <util/delay.h>

void UART_Init (void)
{
	UBRR0H = (BAUDRATE>>8); // shift the register right by 8 bits
	UBRR0L = BAUDRATE; // set baud rate
	UCSR0B|= (1<<TXEN0)|(1<<RXEN0); // enable receiver and transmitter
	UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // 8bit data format
}

void UART_Transmit (unsigned char data) {
	while (!( UCSR0A & (1<<UDRE0))); // wait while register is free
	UDR0 = data; // load data in the register
}
// function to receive data
unsigned char UART_Receive (void)
{
	while(!(UCSR0A) & (1<<RXC0)); // wait while data is being received
	return UDR0; // return 8-bit data
}

int main(void)
{
    const char* data = "1310748";
	UART_Init();
    while (1) 
    {
		for(int i = 0; i < 8; i++) {
			while(!(UCSR0A & UDRE0));
			UART_Transmit(data[i]);
		}
    }
}

