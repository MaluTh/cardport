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
UART uart(
	19200,
	UART::DATABITS_8,
	UART::PARITY_ODD,
	UART::STOPBITS_2
);

GPIO led (5,GPIO::OUTPUT);
GPIO button (6, GPIO::INPUT);
Timer timer(1000);

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





