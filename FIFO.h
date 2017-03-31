/*
 * FIFO.h
 *
 *  Created on: 31 de mar de 2017
 *      Author: aluno
 */

#ifndef FIFO_H_
#define FIFO_H_

template < int Q_SIZE > // O tamanho da final é passado como parâmetro
						// EX: FIFO<8> _tx_fifo

class FIFO {
public:
	FIFO(){
		_head = 0;
		_tail = 0;
	}

	~FIFO(){}

	void push(char value){
		if(((_tail+1)% Q_SIZE) == _head) return;

		_buffer[_tail] = value;

		if(_tail == Q_SIZE) _tail = 0;
		else _tail++;

	}
	char pop(){
		int returnval;
		if(_head == _tail) return 0;
		returnval = _buffer[_head];
		if(_head == Q_SIZE) _head =0;
		else _head++;

		return returnval;

	}

private:
	int _head,_tail;
	char _buffer[Q_SIZE];
};

#endif /* FIFO_H_ */
