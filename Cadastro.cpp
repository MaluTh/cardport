/*
 * Cadastro.cpp
 *
 *  Created on: 19 de abr de 2017
 *      Author: aluno
 */

#include "Cadastro.h"
#include <stdlib.h>     /* malloc, free, rand */

Cadastro::Cadastro(char nome, char sobrenome, char matricula) {

    User u;

    /*u =  malloc(sizeof(User));

    u.nome = nome;
    u.sobrenome = sobrenome;
    u.matricula = matricula;*/

    adiciona(u);

}

Cadastro::~Cadastro() {}

void Cadastro::adiciona(User u){
	//cria uma fila de struct e add nela

}
void Cadastro::exclui(char matricula){

}

