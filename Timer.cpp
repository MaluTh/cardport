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

int div = 0;

Timer::Timer(Hertz freq) {

	TCCR0A = 0x00;// Normal operation
	TIMSK0 = 0x01; // liga interrupção de overflow

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
}


Milliseconds Timer::millis(){
	//versão errada (verificar freq e transformar ticks em mili)
	unsigned long long periodo;
	unsigned long long periodo_clock;
	unsigned long long milis;

	periodo = 1/float(this->_freq);
	periodo_clock = 1/ciclos;
	milis = float(periodo/periodo_clock) - 1;

	return milis * _ticks;
	//return _ticks;
}
Microseconds Timer::micros(){
	return millis()/1000;
}

void Timer::delay(Milliseconds ms){

	Milliseconds aux = millis();
	while(millis()<(aux+ms));

}
void Timer::udelay(Microseconds us){

}

void Timer::isr_handler(){
	TCNT0 = 0XF0; //inicia a contagem "la na frente"
	_ticks++;
}

ISR (TIMER0_OVF_vect){// para monitorar o overflow
	Timer:: isr_handler();

}
