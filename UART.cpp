/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

UART * UART::__singelton =0;

UART::UART(unsigned long  br, DataBits_t db, ParityBits_t pr, StopBits_t sb): _baudrate(br), _databits(db), _parity(pr), _stopbits(sb) {

	__singelton = this;

	UBRR0 = (F_CPU / (16ul * this->_baudrate))-1; //set baudrate

	//set databits
	if(_databits == DATABITS_9){

		UCSR0B = UCSR0B & ~(1 << TXB80);
		UCSR0B = UCSR0B & ~(1 << RXB80);
		UCSR0B = (UCSR0B & ~(1 << UCSZ02)) | (_databits << UCSZ02);
	}

	UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (_databits << UCSZ00);


	//set parity
	UCSR0C = (UCSR0C & ~(3 << UPM00)) | (_parity << UPM00); // 3 representa dois bits em binário.

	//STOP BIT
	UCSR0C = (UCSR0C & ~(1 << USBS0)) | (_stopbits << USBS0); // lê, modifica e salva

	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //liga tx e rx

	//Registrador UCSR0B

	UCSR0A = UCSR0A & ~(1 << TXC0);
	UCSR0A = UCSR0A & ~(1 << RXC0);

	UCSR0B = UCSR0B | (1 << RXCIE0);


}

void UART:: put(unsigned char data){


	// Coloca na fila de transmissão
	self()->_tx_fifo.push(data);

	UCSR0B = UCSR0B | (1 << UDRIE0);
}

unsigned char UART:: get(){

		if(self()->_rx_fifo.size()>0){
			return self()->_rx_fifo.pop();
		} else {
			self()->_rx_fifo.clear();
			return '\0';
		}

}

void UART:: puts(const char * str){

	while(*str != '\0'){
		put(*str);
		str++;
	}

}

void UART::rxc_handler(){
	//return receive data
	self()->_rx_fifo.push(UDR0);

}

void UART::txc_handler(){
	// Coloca dado da fila de transmissão no registrador

	if(self()->_tx_fifo.size() > 0){
		UDR0 = self()->_tx_fifo.pop();
	} else {
		UCSR0B = UCSR0B & ~(1 << UDRIE0);
		self()->_tx_fifo.clear();
	}

}
#ifdef __AVR_ATmega2560__
ISR(USART0_RX_vect)
#else
ISR(USART_RX_vect)
#endif
{
	UART::rxc_handler();
}

#ifdef __AVR_ATmega2560__
ISR(USART0_UDRE_vect)
#else
ISR(USART_UDRE_vect)
#endif
{ // monitora se o registrador esta vazio
	UART::txc_handler();
}


//UART::~UART() {}

