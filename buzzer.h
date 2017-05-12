/*
 * buzzer.h
 *
 *  Created on: 12 de mai de 2017
 *      Author: aluno
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "Timer.h"

/*typedef unsigned long Hertz;
typedef unsigned long long Microseconds;
typedef unsigned long long Milliseconds;*/

class buzzer {

	buzzer();
	void aciona_buzzer(Hertz freq);

/*		buzzer(Hertz freq);
		~buzzer();
		Milliseconds b_millis();
		Microseconds b_micros();

		void b_delay(Milliseconds ms);
		void b_udelay(Microseconds us);

		static void b_isr_handler();

		static buzzer * b_self() { return __bsingelton; }

		void aciona_buzzer(Hertz freq);

	private:
		static buzzer * __bsingelton;
		static unsigned long long b_ticks;
		unsigned long long b_us_per_tick;
		Hertz b_freq;
		int b_ciclos;*/

	};


#endif /* BUZZER_H_ */
