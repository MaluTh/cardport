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

UART uart(
	19200,
	UART::DATABITS_8,
	UART::PARITY_ODD,
	UART::STOPBITS_2
);

GPIO led (111,GPIO::OUTPUT);
GPIO button (12, GPIO::INPUT);

void setup(){}

bool val_botao;

void loop(){
	val_botao= button.get();
	led.set(val_botao);
}

int main(){
	setup();
	while(true){
		loop();
	}
}





