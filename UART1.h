/*
 * UART.h
 *
 *  Created on: 15 de mar de 2017
 *      Author: arliones.hoeller
 */

#ifdef __AVR_ATmega2560__

#ifndef UART1_H_
#define UART1_H_

#include "Singleton.h"
#include "FIFO.h"

class UART1 : public Singleton<UART1> {
public:
	enum StopBits_t {
		STOPBITS_1 = 0,
		STOPBITS_2 = 1
	};

	enum ParityBits_t {
		PARITY_NONE = 0,
		PARITY_EVEN = 2,
		PARITY_ODD  = 3
	};

	enum DataBits_t {
		DATABITS_5 = 0,
		DATABITS_6 = 1,
		DATABITS_7 = 2,
		DATABITS_8 = 3,
		DATABITS_9 = 7
	};

	UART1(unsigned long br = 9600,
		DataBits_t db = DATABITS_8,
		ParityBits_t pr = PARITY_NONE,
		StopBits_t sb = STOPBITS_1);
	~UART1();

	bool has_data();

	void put(unsigned char data);
	unsigned char get();
	void puts(const char * str);

	static void rxc_isr_handler();
	static void udre_isr_handler();

private:
	unsigned long _baudrate;
	DataBits_t _databits;
	ParityBits_t _parity;
	StopBits_t _stopbits;

	typedef FIFO<16,char> UART_FIFO;
	UART_FIFO _rx_fifo;
	UART_FIFO _tx_fifo;
};

#endif /* UART1_H_ */

#endif /* __AVR_ATmega2560__ */
