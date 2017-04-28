/*
 * FIFO.h
 *
 *  Created on: 31 de mar de 2017
 *      Author: aluno
 */

#ifndef FIFO_H_
#define FIFO_H_

template < int Q_SIZE, typename T > // O tamanho da final é passado como parâmetro
						// EX: FIFO<8> _tx_fifo

class FIFO {
public:
	static const unsigned int FIFO_ERROR_EMPTY = -1;
	static const unsigned int FIFO_ERROR_FULL= -2;

	FIFO(){
		clear();
	}

	~FIFO(){}

	int push(T value){

		if(_length == Q_SIZE) {
			_tail = 0;
			return FIFO_ERROR_FULL;
		}else{
			if(_tail == Q_SIZE) {
				_tail = 0;
			} else {
				_buffer[_tail] = value;
				_tail++;
				_length ++;
			}
			return 0;

		}
	}
	T pop(){

		T returnval;

		if(_length == 0) return (T)FIFO_ERROR_EMPTY;

		returnval = _buffer[_head];

		if(_head == Q_SIZE-1) {
			_head =0;
		} else {

			_head++;
		}
		_length --;
		return returnval;

	}


	void clear(){
			_head = 0;
			_tail = 0;
			_length = 0;
			return;
	}

	int procura(T value){
		int i;
		for( i=_head; i< _tail; i++){
				if(value == _buffer[i])return i;
		}
		return -1;
	}

	bool exclui(T value){
		int i;
		T retorno;
		for(i =0; i<_length; i++){
			 retorno = pop();
			if(retorno != value){
				push(retorno);
			} else return true;

		}
		return false;

	}

	int size(){return _length;}
	int max_size(){return Q_SIZE;}

private:
	int _head,_tail, _length;
	T _buffer[Q_SIZE];
};

#endif /* FIFO_H_ */


