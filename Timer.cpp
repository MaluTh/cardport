/*
 * Timer.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long long Timer::_ticks = 0;
Timer * Timer::__singelton = 0;

Timer::Timer(Hertz freq) {

	int div = 0;


	__singelton = this;

	//lógica para selecionar div
	if(freq <= 15000){
		TCCR0B = 0x05; //div 1024
		div = 1024;
	}
	else if(freq <= 62000){
		TCCR0B = 0x04;// div por 256
		div = 256;
	}
	else if(freq <= 250000){
		TCCR0B = 0x03; //div por 64
		div = 64;
	}

	this->ciclos = (F_CPU/div)/(freq);

	TCNT0 = 0XFF - ciclos; // conta ate FF, da o overflow, e continua a contagem da onde parou
	this->_freq = freq;

	us_per_tick = 1000000/this->_freq;

	TCCR0A = 0x00;// Normal operation
	TIMSK0 = 0x01; // liga interrupção de overflow
}


Milliseconds Timer::millis(){

	return (micros()/1000);

}
Microseconds Timer::micros(){

	return us_per_tick * _ticks;

}

void Timer::delay(Milliseconds ms){

	udelay(ms*1000);

}
void Timer::udelay(Microseconds us){

	Microseconds aux = micros();
	while((micros()-aux) <= us);

}

void Timer::isr_handler(){
	TCNT0 = 0XFF - self()->ciclos; //inicia a contagem "la na frente"
	self()->_ticks++;
}

ISR (TIMER0_OVF_vect){// para monitorar o overflow
	Timer:: isr_handler();

}
