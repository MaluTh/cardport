/*
 * Cadastro.cpp
 *
 *  Created on: 19 de abr de 2017
 *      Author: aluno
 */

#include "Cadastro.h"

Cadastro::Cadastro() {

}

Cadastro::~Cadastro() {}

void Cadastro::adiciona(unsigned long long matricula){

	_cadastrados.push(matricula);

}

bool Cadastro::procura(unsigned long long matricula){

	int in = _cadastrados.procura(matricula);

	if(in<0) return false; //não esta na fila
	else return true;

/*
	if(in >= 0){
		return true; // permite entrada e acende led verde
	} else {
		return false; // acende led vermelho
	}*/


}

bool Cadastro::exclui(unsigned long long matricula){
	return _cadastrados.exclui(matricula);

}

