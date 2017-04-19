/*
 * GPIO.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */
#include <avr/io.h>

#include "GPIO.h"

GPIO::GPIO(int pin, PortDirection_t dir) {

	if(pin<=7 && pin>=0){
		// 0-7 D
		_ddr = &DDRD;
		_port = &PORTD;
		_pin = &PIND;
	} else if (pin<=13 && pin>=8) {
		//8-13 B
		pin = pin-8;
		_ddr = &DDRB;
		_port = &PORTB;
		_pin = &PINB;
	} else {
		//porta C
		 pin = pin-14;
		_ddr = &DDRC;
		_port = &PORTC;
		_pin = &PINC;
	}

	_mask = (1 << pin);

	if(dir ==INPUT){
		 *_ddr = *_ddr &(~_mask);
	} else {
		 *_ddr = *_ddr | _mask;
	}

}

GPIO::~GPIO() {}


 bool GPIO::get(){
	 //ler pin
	 return (*_pin) & _mask;
 }


 void GPIO::set(bool val){
	 //escrever na port
	 if(val==true){
		 *_port = *_port | _mask;
	 } else {
		 *_port = *_port &(~_mask);
	 }
}
