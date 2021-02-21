//listaCorreo.h
#ifndef LISTACORREOS_H
#define LISTACORREOS_H
#include"Correo.h"
#include<fstream>

const int MAX_CORREOS = 100;

typedef struct {

	tCorreo datoCorreo[MAX_CORREOS];
	int cont;

}tListaCorreos;

void inicializar(tListaCorreos &correos);//inicializa la lista
bool buscar(const tListaCorreos &correos, string id, int &pos);//busca un correo en la lista de correos
bool insertar(tListaCorreos &correos, const tCorreo &correo);//inserta un correo en la lista correos
bool cargar(tListaCorreos &correos, string dominio);//carga del archivo en la lista correos
void guardar(const tListaCorreos &correos, string dominio);//guarda del archivo en la lista correos
void ordenar_AF(tListaCorreos &correos);//ordena los correos por el asunto y fecha
//void mostrar();

#endif