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
GPIO botao1(12, GPIO::INPUT); //Adicionar
GPIO botao2(13, GPIO::INPUT); //Abrir porta
GPIO botao3(7, GPIO::INPUT); //Remove
GPIO rele(10, GPIO::OUTPUT);
GPIO buzzer(8, GPIO::OUTPUT);

Timer timer(1000);
bool val_botao;
char message[8];
char a;
//unsigned long long adm = '00279176774866';


Cadastro c;

void setup() {
	sei();
	// habilitando configurações globais SÓ FAZ ISSO AQUI

	rele.set(1);
	botao1.set(0);
	botao2.set(0);
	botao3.set(0);
	//c.adiciona(adm);
}

void loop() {

	if (botao1.get() == true) {
		while (botao1.get() == true) {
			if(leitor.read()!= 0){
				//if(leitor.get_current_id()==adm){
					//uart.puts("ADM: Passe novo ID\n");
					if(c.procura(leitor.get_current_id())==false){
						c.adiciona(leitor.get_current_id());
						led_verde.set(1);
						timer.delay(1000);
						led_verde.set(0);
						uart.puts("ADM: Adicionado!\n");
					}
				/*}else{
					uart.puts("Administrador NOK\n");
				}*/
			}
		}
		leitor.set_current_id();
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
			if (leitor.read()!=0) {
				//if(leitor.get_current_id()== adm){
					if(c.exclui(leitor.get_current_id())==true /*&& leitor.get_current_id()!=adm*/){
						uart.puts("ADM: Excluido\n");
						leitor.set_current_id();
					}
				/*} else {
					uart.puts("Não permitido excluir\n");
				}*/
			}
		}
	}



	if (leitor.read() != 0) {

		if (c.procura(leitor.get_current_id()) == true) {

			led_verde.set(1); // acende led verde
			timer.delay(1000);
			led_verde.set(0); //desliga led
			rele.set(0); // aciona relé
			timer.delay(500);
			rele.set(1); // desliga relé
			uart.puts("OK!\n");
			int i = 0;
			while(i != 10000){
			 buzzer.set(1);
			 buzzer.set(0);
			 i++;
			}


			//timer.delay(1000);

		} else {

			led_vermelho.set(1);
			buzzer.set(1);
			timer.udelay(1000);
			led_vermelho.set(0);
			buzzer.set(0);
			uart.puts("NOK!\n");

		}
		leitor.set_current_id();

	}




}

int main() {
	setup();

	while (true)
		loop();

}

