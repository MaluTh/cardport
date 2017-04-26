/*
 * Cadastro.cpp
 *
 *  Created on: 19 de abr de 2017
 *      Author: aluno
 */

#include "Cadastro.h"
#include <stdlib.h>     /* malloc, free, rand */

Cadastro::Cadastro(char nome, char sobrenome, char matricula) {

    _nome = nome;
    _sobrenome = sobrenome;
    _matricula = matricula;
    adiciona();

}

Cadastro::~Cadastro() {}

void Cadastro::adiciona(){


	User * u = new User();
	/*
	strncpy(mike.name, guest_name, 19);
	mike.name[19] = 0; // ensure termination*/
	/*
	u->nome =_nome;
	u->sobrenome = _sobrenome;
	u->matricula = _matricula;*/

	//_cadastrados.push(u);
	//cria uma fila de struct e add nela

}

void Cadastro:: edita(User u){


}
void Cadastro::exclui(char matricula){

}

