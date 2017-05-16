/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: arliones.hoeller
 */

#include <stdio.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "UART1.h"
#include "GPIO.h"
#include "Timer.h"
#include "FIFO.h"
#include "Cadastro.h"
#include  "RDM6300.h"

UART uart(19200, UART::DATABITS_8, UART::PARITY_NONE, UART::STOPBITS_1);
UART1 rfid(9600, UART1::DATABITS_8, UART1::PARITY_NONE, UART1::STOPBITS_1);

RDM6300 leitor(rfid);

GPIO led_vermelho(11, GPIO::OUTPUT);
GPIO led_verde(9, GPIO::OUTPUT);
GPIO botao1(12, GPIO::INPUT); //Adicionar
GPIO botao2(13, GPIO::INPUT); //Abrir porta
GPIO botao3(7, GPIO::INPUT); //Remove
GPIO rele(10, GPIO::OUTPUT);
GPIO buzzer(8, GPIO::OUTPUT);

Timer timer(1000);
bool val_botao;
char message[8];
char a;

Cadastro c;

void setup() {
	sei();
	// habilitando configurações globais SÓ FAZ ISSO AQUI
	rele.set(1);
	botao1.set(0);
	botao2.set(0);
	botao3.set(0);
}

void loop() {

	if (botao1.get() == true) {
		//botao1.set(1);
		while (botao1.get() == true) {
			while (leitor.) {
				if(c.adiciona(rfid.get())==false){
					led_verde.set(1);
					timer.delay(1000);
					led_verde.set(0);
					uart.puts("Add!\n");
				}
				//botao1.set(0);
			}
		}
	}




	while (_serial->has_data()) {
	                parse(_serial->get());
	            }




	if (botao2.get() == true) {
		//botao2.set(1);
		while (botao2.get() == true) {
			rele.set(0);
			timer.delay(500);
			rele.set(1);
		}
		//botao2.set(0);

	}

	if (botao3.get() == true) {
		//botao3.set(1);
		while (botao3.get() == true) {
			if (rfid.has_data()) {

				if(c.exclui(rfid.get())==true){
					uart.puts("Excluido\n");
				}
				//botao3.set(0);

			}
		}
	}

	while (rfid.has_data() == true) {

		if (c.procura(rfid.get()) == true) {

			led_verde.set(1); // acende led verde
			timer.delay(1000);
			led_verde.set(0); //desliga led

			buzzer.set(1);
			rele.set(0); // aciona relé
			timer.delay(500);
			rele.set(1); // desliga relé
			buzzer.set(0);
			uart.puts("OK!\n");

			//timer.delay(1000);

		} else {

			led_vermelho.set(1);
			buzzer.set(1);
			timer.udelay(1000);
			led_vermelho.set(0);
			buzzer.set(0);
			uart.puts("NOK!\n");

		}

	}


	/*else {
		uart.puts("!\n");
	}*/

	/*	if (c.procura(789)) {

	 //acende led verde por x seg
	 //pulso relé
	 uart.puts("Encontrado!\n");

	 rele.set(1);
	 //while(2000>timer.delay(2000)){
	 buzzer.set(1);
	 buzzer.set(0);
	 //}
	 rele.set(0);

	 } else {
	 uart.puts("Invalido!\n");
	 //acende led vermelho por x seg
	 led_vermelho.set(1);
	 timer.delay(1000);
	 led_vermelho.set(0);
	 }
	 if (c.exclui(789))
	 uart.puts("Deletado\n");
	 //else uart.puts("Nao encontrado\n");
	 timer.delay(1000);*/

}

int main() {
	setup();

	while (true)
		loop();

}

