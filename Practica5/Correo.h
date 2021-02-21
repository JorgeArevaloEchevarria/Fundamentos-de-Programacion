//Correo.h
#ifndef CORREO_H
#define CORREO_H
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
#include<iomanip>

using namespace std;

const string CENTINELA = "X";
const char SALTO = '\n';
const string CENTINELA_FINAL = "XXX";
const string ARCHIVO = "_correos.txt";

typedef time_t tFecha;

typedef struct{
	
	string id;//concatenacion de emisor y fecha
	string emisor;	
	string destinatario;
	string asunto;
	string cuerpo;
	tFecha fecha;

}tCorreo;


void correoNuevo(tCorreo &correo, string emisor);
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor);
string aCadena(const tCorreo &correo);
string obtenerCabecera(const tCorreo &correo);
bool cargar(tCorreo &correo, ifstream& archivo);
void guardar(const tCorreo &correo, ofstream& archivo);
string mostrarFecha(tFecha fecha);
string mostrarSoloDia(tFecha fecha);
bool operator<(const tCorreo &opIzq, const tCorreo &opDer);

#endif