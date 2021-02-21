#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

#include"Usuario.h"

using namespace std;
const int MAX_USUARIOS = 50;
typedef tUsuario *UsuarioPtr;

typedef struct{

	UsuarioPtr usuario[MAX_USUARIOS];
	int cont;

}tListaUsuarios;


bool buscarUsuario(const tListaUsuarios &usuarios, string id, int &posicion);
void inicializar(tListaUsuarios &usuarios);
bool insertar(tListaUsuarios &usuarios, const tUsuario &usuario);
bool cargar(tListaUsuarios &usuarios, string dominio);
void guardar(const tListaUsuarios &usuarios, string dominio);
void destruir(tListaUsuarios &lista);

#endif