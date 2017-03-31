/*
 * Timer.h
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned long Hertz;
typedef unsigned long long Microseconds;
typedef unsigned long long Milliseconds;


class Timer {
public:

	Timer(Hertz freq);
	Milliseconds millis();
	Microseconds micros();

	void delay(Milliseconds ms);
	void udelay(Microseconds us);

	static void isr_handler();

	static Timer * self() { return __singelton; }

private:
	static Timer * __singelton;
	static unsigned long long _ticks;
	unsigned long long us_per_tick;
	Hertz _freq;
	int ciclos;
};

#endif /* TIMER_H_ */
