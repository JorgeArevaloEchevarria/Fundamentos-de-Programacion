//Usuario.h
#ifndef USUARIO_H
#define USUARIO_H
#include"ListaRegistros.h"
#include"Correo.h"

using namespace std;

const string ARCHIVOU = "_usuarios.txt";

typedef struct{

	string id;
	string contrasenia;
	tListaRegCorreo recibidos;
	tListaRegCorreo enviados;

}tUsuario;


void inicializar(tUsuario &usuario, string id, string contrasenia);
bool validarContrasenia(const tUsuario &usuario, string id, string contrasenia);
bool cargar(tUsuario &usuario, ifstream &archivo);
void guardar(const tUsuario &usuario, ofstream &archivo);

#endif