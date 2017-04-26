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

typedef	struct usuario{
		char nome[20];
		char sobrenome[20];
		char matricula[20];
		}User;

public:
	Cadastro(char nome, char sobrenome, char matricula);
	virtual ~Cadastro();
	void adiciona();
	void edita(User u);
	void exclui(char matricula);

private:

	char _matricula;
	char _nome;
	char _sobrenome;
	FIFO<64,User> _cadastrados;
};


#endif /* CADASTRO_H_ */
