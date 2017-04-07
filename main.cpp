/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: arliones.hoeller
 */

#include <stdio.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"

UART uart(19200, UART::DATABITS_8, UART::PARITY_NONE, UART::STOPBITS_1);
GPIO led(11, GPIO::OUTPUT);
GPIO botao(12, GPIO::INPUT);
Timer timer(1000);
bool val_botao;
char message[8];

void setup() {
	sei();// habilitando configurações globais SÓ FAZ ISSO AQUI
}

static const int MAX = 4;
typedef FIFO<MAX> MyFIFO;
MyFIFO fifo_test;

void loop() {
//	val_botao = botao.get();
//	led.set(val_botao);
//	timer.delay(1000);
//	sprintf(message, "%lu\n", timer.millis());
//	uart.puts(message);

	char x = 0, y = 0;

	uart.puts("Test 1: insert/remove 1.\r\n");
	fifo_test.clear();

	uart.puts("\t Push A. ");
	fifo_test.push('A');
	uart.puts(" => OK.\r\n");

	uart.puts("\t Pop: ");
	x = fifo_test.pop();
	uart.put(x);
	if(x == 'A') uart.puts(". => OK.\r\n");
	else uart.puts(". => NOK.\r\n");


	uart.puts("Test 2: insert/remove MAX.\r\n");
	fifo_test.clear();

	x = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("\t Push ");
		uart.put(x);
		uart.puts(". ");
		fifo_test.push(x);
		uart.puts(" => OK.\r\n");
		x++;
	}

	y = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("\t Pop: ");
		x = fifo_test.pop();
		uart.put(x);
		if(x == y) uart.puts(". => OK.\r\n");
		else uart.puts(". => NOK.\r\n");
		y++;
	}


	uart.puts("Test 3: remove from empty.\r\n");
	fifo_test.clear();

	for (int i = 0; i < MAX; i++) {
		uart.puts("\t Pop: ");
		x = fifo_test.pop();
		if(x == (char)MyFIFO::FIFO_ERROR_EMPTY) uart.puts(". => OK.\r\n");
		else uart.puts(". => NOK.\r\n");
	}

	uart.puts("Test 4: insert in full.\r\n");
	fifo_test.clear();

	x = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("\t Push ");
		uart.put(x);
		uart.puts(". ");
		fifo_test.push(x);
		uart.puts(" => OK.\r\n");
		x++;
	}

	uart.puts("\t Add extra item: ");
	x = fifo_test.push('X');
	if(x == (char)MyFIFO::FIFO_ERROR_FULL) uart.puts(". => OK.\r\n");
	else uart.puts(". => NOK.\r\n");

	y = 'A';
	for (int i = 0; i < MAX; i++) {
		uart.puts("\t Pop: ");
		x = fifo_test.pop();
		uart.put(x);
		if(x == y) uart.puts(". => OK.\r\n");
		else uart.puts(". => NOK.\r\n");
		y++;
	}

	timer.delay(10000);
}

int main() {
	setup();
	while (true)
		loop();
}




///*
// * main.cpp
// *
// *  Created on: 15 de mar de 2017
// *      Author: aluno
// */
//
//
//#include <util/delay.h>
//#include <avr/io.h>
//#include <stdio.h>
//#include "UART.h"
//#include "GPIO.h"
//#include "Timer.h"
//#include "FIFO.h"
//#include <avr/interrupt.h>
//
//UART uart(
//	19200,
//	UART::DATABITS_8,
//	UART::PARITY_NONE,
//	UART::STOPBITS_1
//);
//
//GPIO led (11,GPIO::OUTPUT);
//GPIO button (12, GPIO::INPUT);
//Timer timer(1000);
//FIFO<8> fila;
//
//char message[8];
//char a;
//
//void setup(){
//	sei();
//
//}
//
//bool val_botao;
//
//
//
//void loop(){
////	val_botao= button.get();
////	led.set(val_botao);
////	timer.delay(1000);
////	led.set(!val_botao);
////	timer.delay(1000);
////	sprintf(message,"%lu\n",timer.millis());
////	uart.puts(message);
////
//
////	fila.push('1');
////	fila.push('2');
////	fila.push('3');
////	a = fila.pop();
////	printf("%c\n",a);
////	uart.put(a);
//
//	//uart.put('a\n');
//
//}
//
//int main(){
//	setup();
//	int i = 0;
//
//	while(i != fila.max_size()){
//		fila.push(i);
//		i++;
//	}
//
//	while(fila.size() != 0){
//		a = fila.pop();
//		printf("%c\n",a);
//		uart.put(a);
//	}
//
////	while(true){
////		loop();
////	}
//
//
//}
//
//



