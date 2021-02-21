//listaCorreo.h
#ifndef LISTACORREOS_H
#define LISTACORREOS_H
#include"Correo.h"
#include<fstream>

const int MAX_CORREOS = 100;
typedef tCorreo *correoPtr;

typedef struct {

	correoPtr datoCorreo;
	int cont;
	int capacidad;

}tListaCorreos;

void inicializar(tListaCorreos &correos,int capInicial);
bool buscar(const tListaCorreos &correos, string id, int &pos);
bool insertar(tListaCorreos &correos, const tCorreo &correo);
bool cargar(tListaCorreos &correos, string dominio);
void guardar(const tListaCorreos &correos, string dominio);
void ordenar_AF(tListaCorreos &correos);
void redimensionar(tListaCorreos &correos);
void destruir(tListaCorreos &correos);
//void mostrar();

#endif