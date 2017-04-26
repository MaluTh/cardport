/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: arliones.hoeller
 */

#include <stdio.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "Cadastro.h"

UART uart(19200, UART::DATABITS_8, UART::PARITY_NONE, UART::STOPBITS_1);
GPIO led(11, GPIO::OUTPUT);
GPIO botao(12, GPIO::INPUT);
Timer timer(1000);
bool val_botao;
char message[8];
char a;



void setup() {
	sei();// habilitando configurações globais SÓ FAZ ISSO AQUI
}

void loop() {

	//c.procura(123456);

	/*sprintf(message, "\ntesta\n");
	uart.puts(message);
	a = uart.get();
	if(a != 0) uart.put(a);
	timer.delay(1000);*/
}

int main() {
	setup();
	Cadastro c;
	c.adiciona(123456);
	//c.adiciona(456);
	//c.adiciona(789);
	while (true)
		loop();

}



