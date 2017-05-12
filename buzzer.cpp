/*
 * buzzer.cpp
 *
 *  Created on: 12 de mai de 2017
 *      Author: aluno
 */

#include "buzzer.h"

#include <avr/io.h>
#include <avr/interrupt.h>


buzzer::buzzer(){}

void buzzer::aciona_buzzer(Hertz freq){
	Timer t(freq);


	t.delay(1000);

}




/*
unsigned long long buzzer::b_ticks = 0;
buzzer * buzzer::__bsingelton = 0;

buzzer::buzzer(Hertz freq) {

	int div = 0;


	__bsingelton = this;

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

	this->b_ciclos = (F_CPU/div)/(freq);

	TCNT0 = 0XFF - b_ciclos; // conta ate FF, da o overflow, e continua a contagem da onde parou
	this->b_freq = freq;

	b_us_per_tick = 1000000/this->b_freq;

	TCCR0A = 0x00;// Normal operation
	TIMSK0 = 0x01; // liga interrupção de overflow
}


Milliseconds buzzer::b_millis(){

	return (b_micros()/1000);

}
Microseconds buzzer::b_micros(){

	return b_us_per_tick * b_ticks;

}

void buzzer::b_delay(Milliseconds ms){

	b_udelay(ms*1000);

}
void buzzer::b_udelay(Microseconds us){

	Microseconds aux = b_micros();
	while((b_micros()-aux) <= us);

}

void buzzer::b_isr_handler(){
	TCNT0 = 0XFF - b_self()->b_ciclos; //inicia a contagem "la na frente"
	b_self()->b_ticks++;
}

ISR (buzzer0_OVF_vect){// para monitorar o overflow
	buzzer:: b_isr_handler();

}*/

