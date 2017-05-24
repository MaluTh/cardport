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

RDM6300<UART1> leitor(&rfid);

GPIO led_vermelho(11, GPIO::OUTPUT);
GPIO led_verde(9, GPIO::OUTPUT);
GPIO botao1(12, GPIO::INPUT); //Adicionar usuário
GPIO botao2(13, GPIO::INPUT); //Abrir porta por dentro
GPIO botao3(7, GPIO::INPUT); //Remover usuário
GPIO rele(10, GPIO::OUTPUT);
GPIO buzzer(8, GPIO::OUTPUT);

Timer timer(1000);
unsigned long long adm = 279176785051;
bool admin = false;
Cadastro c;


void aciona_buzzer(int time) {

	int i = 0;
	while (i != time) {
		buzzer.set(1);
		buzzer.set(0);
		i++;
	}
}

void acesso_negado() {

	led_vermelho.set(1);
	timer.delay(1000);
	aciona_buzzer(5000);
	timer.delay(500);
	aciona_buzzer(5000);
	led_vermelho.set(0);
	leitor.set_current_id();

}

void acesso_permitido() {

	led_verde.set(1);
	timer.delay(1000);
	aciona_buzzer(10000);
	led_verde.set(0);
	leitor.set_current_id();
}

bool verifica_adm() {
	if (leitor.read() != 0) {

		if (leitor.get_current_id() == adm) {
			admin = true;
			acesso_permitido();
			uart.puts("ADM: Passe novo ID\n");
		}
	}
	return admin;
}

void setup() {
	sei();

	rele.set(1);
	botao1.set(0);
	botao2.set(0);
	botao3.set(0);
	c.adiciona(adm);
}

void loop() {

	if (botao1.get() == true) {

		while (botao1.get()) {

			if (verifica_adm()) {

				if (leitor.read() != 0) {
					if (c.procura(leitor.get_current_id()) == false) {
						c.adiciona(leitor.get_current_id());
						acesso_permitido();
						uart.puts("ADM: Adicionado!\n");
						admin = false;
					}
				}
			}
		}
	}

	if (botao2.get() == true) {

		while (botao2.get() == true) {
			rele.set(0);
			timer.delay(500);
			rele.set(1);
		}

	}

	if (botao3.get() == true) {

		while (botao3.get() == true) {

			if (verifica_adm()) {
				if (leitor.read() != 0 && leitor.get_current_id() != adm) {

					if (c.exclui(leitor.get_current_id())) {
						acesso_permitido();
						uart.puts("ADM: Usuario Removido\n");
					} else {
						acesso_negado();
						uart.puts("ADM: Nao removeu\n");

					}
				}
			}
		}
		admin = false;
	}

	if (leitor.read() != 0) {

		if (c.procura(leitor.get_current_id()) == true) {

			acesso_permitido();
			rele.set(0);
			timer.delay(500);
			rele.set(1);
			uart.puts("OK!\n");

		} else {

			acesso_negado();
			uart.puts("NOK!\n");

		}
	}
}

int main() {
	setup();

	while (true)
		loop();

}

