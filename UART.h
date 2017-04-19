/*
 * UART.h
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_
#include <avr/interrupt.h>

#include "FIFO.h"

class UART {
public:
	enum StopBits_t {
		STOPBITS_1 = 0,
		STOPBITS_2 = 1
	};

	enum ParityBits_t {
		PARITY_NONE = 0,
		PARITY_EVEN = 2,
		PARITY_ODD = 3
	};

	enum DataBits_t {
		DATABITS_5 = 0,
		DATABITS_6 = 1,
		DATABITS_7 = 2,
		DATABITS_8 = 3,
		DATABITS_9 = 7
	};

	UART(
			unsigned long br = 19200,
			DataBits_t db = DATABITS_8,
			ParityBits_t pr = PARITY_NONE,
			StopBits_t sb = STOPBITS_1
	);
	//virtual ~UART();

	void put(unsigned char data);
	unsigned char get();
	void puts(const char * str);
	static void rxc_handler();
	static void txc_handler();
	static UART * self() { return __singelton; }

private:
	static UART * __singelton;
	unsigned long  _baudrate;
	DataBits_t _databits;
	ParityBits_t _parity;
	StopBits_t _stopbits;

	FIFO<8,char> _tx_fifo;
	FIFO<32,char> _rx_fifo;
};

#endif /* UART_H_ */
