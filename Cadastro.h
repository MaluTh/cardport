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
	~Cadastro();
	bool adiciona(unsigned long long matricula);
	bool procura(unsigned long long matricula);
	bool exclui(unsigned long long matricula);

private:
	FIFO<32,unsigned long long> _cadastrados;
};


#endif /* CADASTRO_H_ */
