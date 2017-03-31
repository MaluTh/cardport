/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>

UART::UART(unsigned long  br, DataBits_t db, ParityBits_t pr, StopBits_t sb): _baudrate(br), _databits(db), _parity(pr), _stopbits(sb) {

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

	//set stopbits
	//unsigned char reg = UCSR0C; //read
	//reg = (reg & ~(1 << USBS0)) | (_stopbits << USBS0); //modify
	//UCSR0C = reg; // update

	UCSR0C = (UCSR0C & ~(1 << USBS0)) | (_stopbits << USBS0); // lê, modifica e salva

	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //liga tx e rx
}

void UART:: put(unsigned char data){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) ); // vai dando shift e mandando byte a byte pela serial
	/* Put data into buffer, sends the data */
	UDR0 = data; //envai o dado depois que o registrador estiver vazio
}

unsigned char UART:: get(){

	//wait until data is received
	while ( ! (UCSR0A & (1<<RXC0))) ;

	return UDR0; //return receive data
}

void UART:: puts(char * str){

	while(*str != '\0'){
		put(*str);
		str++;
	}


}



/*UART::~UART() {
	// TODO Auto-generated destructor stub
}*/

