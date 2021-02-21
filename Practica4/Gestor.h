#ifndef GESTOR_H
#define GESTOR_H

#include"ListaCorreos.h"
#include"ListaUsuario.h"
#include<iostream>

using namespace std;

const char ARROBA = '@';

typedef struct{

	string dominio;
	tListaUsuarios usuarios;
	tListaCorreos correos;
	int usuarioActivo;

}tGestor;


void inicializar(tGestor &gestor, string dominio);
bool arrancar(tGestor& gestor, string dominio);
void apagar(const tGestor &gestor);
bool crearCuenta(tGestor &gestor);
bool iniciarSesion(tGestor &gestor);
void leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg);
void enviarCorreo(tGestor& gestor, const tCorreo &correo);
void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg);
void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg);
void menuLeerCorreo(tGestor &gestor, const tCorreo &correoOriginal);
void menuBandejaEntrada(tGestor &gestor);
void menuBandejaSalida(tGestor &gestor);
int menuBandeja(tGestor &gestor,bool entrada);
void ejecutarMenuBandeja(tGestor &gestor, int &opcion, bool &entrada);

#endif