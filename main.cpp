/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */


#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include <avr/interrupt.h>

UART uart(
	19200,
	UART::DATABITS_8,
	UART::PARITY_NONE,
	UART::STOPBITS_1
);

GPIO led (11,GPIO::OUTPUT);
GPIO button (12, GPIO::INPUT);
Timer timer(1000);
FIFO<8> fila;

char message[8];
char a;

void setup(){
	sei();

}

bool val_botao;



void loop(){
//	val_botao= button.get();
//	led.set(val_botao);
//	timer.delay(1000);
//	led.set(!val_botao);
//	timer.delay(1000);
//	sprintf(message,"%lu\n",timer.millis());
//	uart.puts(message);

	fila.push('1');
	fila.push('2');
	fila.push('3');
	a = fila.pop();
	printf("%c\n",a);
	uart.put(a);

	//uart.put('a\n');

}

int main(){
	setup();
	while(true){
		loop();
	}

}





