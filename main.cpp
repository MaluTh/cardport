/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */


#include <util/delay.h>
#include <avr/io.h>
//#include <avr/iom328p.h>
#include <stdio.h>
#include "UART.h"

char pin_led = 3;//bit que vai ser utilizado na aplicação
char pin_b = 4;
const unsigned char led_mask = (1 << pin_led);
const unsigned char button_mask = (1 << pin_b);
unsigned long tempo = 1000;

UART uart;

bool ler_pino(){
    return button_mask & PINB;
}

void setup() {
  // put your setup code here, to run once:
  DDRB = DDRB | button_mask; //saida
  DDRB = DDRB & ~button_mask; //entrada
  //usart_init();

}

void acende_led() {
    PORTB = PORTB | led_mask;
}

void apaga_led() {
    PORTB = PORTB &(~led_mask);
}

void loop() {
  // put your main code here, to run repeatedly:

	uart.put('a');
    if(ler_pino()){
    	//printf("ON\n");
        apaga_led();
    } else {
    	//printf("OFF\n");
        acende_led();
    }
}

int main(){

    setup();

    while(true) loop();

}






