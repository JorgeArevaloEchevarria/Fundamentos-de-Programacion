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

}tUsuario;//usuario


void inicializar(tUsuario &usuario, string id, string contrasenia); //inicializa el usuario
bool validarContrasenia(const tUsuario &usuario, string id, string contrasenia);//valida la contraseña del usuraio
bool cargar(tUsuario &usuario, ifstream &archivo);//carga datos de los usuarios
void guardar(const tUsuario &usuario, ofstream &archivo);//guarda los datos de un usuario

#endif