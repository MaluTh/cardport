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
char message[8];

void setup(){
	sei();

}

bool val_botao;


void loop(){
	val_botao= button.get();
	led.set(val_botao);
	sprintf(message,"%llu\n",timer.millis());
	uart.puts(message);
	//uart.put('a\n');

}

int main(){
	setup();
	while(true){
		loop();
	}
}





