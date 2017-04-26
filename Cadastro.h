/*
 * Cadastro.h
 *
 *  Created on: 19 de abr de 2017
 *      Author: aluno
 */

#ifndef CADASTRO_H_
#define CADASTRO_H_

#include "FIFO.h"

class Cadastro {

public:

	Cadastro();
	virtual ~Cadastro();
	void adiciona(unsigned long matricula);
	bool procura(unsigned long matricula);
	bool exclui(unsigned long matricula);

private:
	FIFO<64,unsigned long> _cadastrados;
};


#endif /* CADASTRO_H_ */
