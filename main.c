/*
 * GccApplication2.c
 *
 * Created: 2/7/2025 12:50:05 PM
 * Author : acooper1171
 */ 

#define F_CPU 16000000UL // 16MHz clock from the debug processor
#define BAUD 9600
#define BAUDRATE (F_CPU / (BAUD * 16UL) - 1)
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

void USART_Init(uint32_t baud_rate) {
	// Set baud rate (high and low)
	UBRR0H = (uint8_t)(baud_rate >> 8);
	UBRR0L = (uint8_t)baud_rate;
	// Enable receive and transfer on USART0
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// 8bit Data
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	// Disable parity
	UCSR0C &= ~((1 << UPM01) ^ (1 << UPM00));
	// 1bit Stop
	UCSR0C &= ~(1 << USBS0);
}

// Transmits a single piece of data
void USART_Transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
	{}
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

// Receives a single piece of data
uint8_t USART_Receive() {
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0))) {}
	/* Get and return received data from buffer */
	return UDR0;
}

// Transmits an array of data
void USART_Send(const char* str) {
	while (*str != '\0') {
		USART_Transmit(*str);
		str++;
	}
}


int main() {
	USART_Init(BAUDRATE);
	
	while (1) {
		USART_Send("1234567890\n");
		_delay_ms(600);
	}
	return 0;
}