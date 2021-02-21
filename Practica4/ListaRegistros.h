#ifndef LISTAREGISTROS_H
#define LISTAREGISTROS_H

#include"Correo.h"
#include<iostream>

using namespace std;

const int MAX_REGS = 100;


typedef struct{
	
	string id;
	bool leido;

}tRegCorreo;//registro de un correo

typedef struct{

	tRegCorreo listaReg[MAX_REGS];
	int cont;

}tListaRegCorreo;//lista de registros


void inicializar(tListaRegCorreo &listaReg);//inicializa la lista
void cargar(tListaRegCorreo &listaReg, ifstream& archivo);//carga la lista del archivo
void guardar(const tListaRegCorreo &listaReg, ofstream& archivo);//guarda la lista en el archivo
bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro);//inserta en la lista
bool borrar(tListaRegCorreo &listaReg, string id);//borra los rregistros
bool correoLeido(tListaRegCorreo &listaReg, string id);//marca un correo como leido
int buscar(const tListaRegCorreo &listaReg, string id);//busca un registro
//void mostrar();
#endif