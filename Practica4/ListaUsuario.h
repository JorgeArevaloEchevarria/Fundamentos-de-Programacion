#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

#include"Usuario.h"

using namespace std;
const int MAX_USUARIOS = 100;

typedef struct{

	tUsuario usuario[MAX_USUARIOS];//lista usuarios
	int cont;

}tListaUsuarios;


bool buscarUsuario(const tListaUsuarios &usuarios, string id, int &posicion);//busca un usuario en la lista
void inicializar(tListaUsuarios &usuarios);//inicializa la lista
bool insertar(tListaUsuarios &usuarios, const tUsuario &usuario);//inserta un usuario en la lista
bool cargar(tListaUsuarios &usuarios, string dominio);//carga los usuarios del archivo
void guardar(const tListaUsuarios &usuarios, string dominio);//guarda los usuarios en el archivo


#endif