#ifndef LISTAREGISTROS_H
#define LISTAREGISTROS_H

#include"Correo.h"
#include<iostream>

using namespace std;

const int CAPINICIAL = 10;


typedef struct{
	
	string id;
	bool leido;

}tRegCorreo;

typedef tRegCorreo *regCorreoPtr;

typedef struct{

	regCorreoPtr listaReg;
	int cont;
	int capacidad;

}tListaRegCorreo;


void inicializar(tListaRegCorreo &listaReg, int capInicial);
void cargar(tListaRegCorreo &listaReg, ifstream& archivo);
void guardar(const tListaRegCorreo &listaReg, ofstream& archivo);
bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro);
bool borrar(tListaRegCorreo &listaReg, string id);
bool correoLeido(tListaRegCorreo &listaReg, string id);
int buscar(const tListaRegCorreo &listaReg, string id);
void redimensionar(tListaRegCorreo &reg);
void destruir(tListaRegCorreo &reg);
//void mostrar();
#endif