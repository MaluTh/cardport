/*
 * Timer.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#include "Timer.h"
#include<avr/io.h>
#include<avr/interrupt.h>

unsigned long long Timer::_ticks = 0;



Timer::Timer(Hertz freq) {

	TCCR0A = 0x00;// Normal operation
	TCCR0B= 0x05;// div por 1024
	TIMSK0 = 0x01; // liga interrupção de overflow
	TCNT0 = 0XF0; // conta ate FF, da o overflos, e continua a contagem da onde parou
	this->_freq = freq;
}


Milliseconds Timer::millis(){
	//versão errada (verificar freq e transformar ticks em mili)

	return _ticks;
}
Microseconds Timer::micros(){

}

void Timer::delay(Milliseconds ms){

}
void Timer::udelay(Microseconds us){

}

void Timer::isr_handler(){
	TCNT0 = 0XF0; //inicia a contagem "la na frente"
	_ticks++;
}

ISR (TIMER0_OVF_vect){
	Timer:: isr_handler();

}
