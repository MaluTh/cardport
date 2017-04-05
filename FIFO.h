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
	static const unsigned int FIFO_ERROR_EMPTY = -1;
	static const unsigned int FIFO_ERROR_FULL= -2;

	FIFO(){
		_head = 0;
		_tail = 0;
		_length = 0;

	}

	~FIFO(){}

	int push(char value){

		if(_length == Q_SIZE) {
			_tail = 0;
			return FIFO_ERROR_FULL;
		}else{
			 _tail ++;
			 int pos = _tail-1;
			_buffer[pos] = value;
			_length ++;
			return pos;
		}
	}
	char pop(){
		int returnval;
		if(_length == 0) return FIFO_ERROR_EMPTY;
		returnval = _buffer[_head];

		if(_head == Q_SIZE) {
			_head =0;
		} else {
			_head++;
		}
		_length --;
		return returnval;

	}

	int size(){return _length;}
	int max_size(){return Q_SIZE;}

private:
	int _head,_tail, _length;
	char _buffer[Q_SIZE];
};

#endif /* FIFO_H_ */
