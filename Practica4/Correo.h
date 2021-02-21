//Correo.h
#ifndef CORREO_H
#define CORREO_H
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
#include<iomanip>

using namespace std;

const string CENTINELA = "X";//centinela para separar mensajes
const char SALTO = '\n';
const string CENTINELA_FINAL = "XXX";//centinela para el final del archivo
const string ARCHIVO = "_correos.txt";


typedef time_t tFecha;//variable para la fecha

typedef struct{
	
	string id;//concatenacion de emisor y fecha
	string emisor;	
	string destinatario;
	string asunto;
	string cuerpo;
	tFecha fecha;

}tCorreo;//struct de tCorreo


void correoNuevo(tCorreo &correo, string emisor);//crea una correo nuevo
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor);//concatena la contestacion del correo al correo
string aCadena(const tCorreo &correo);//muestra los parametros del correo
string obtenerCabecera(const tCorreo &correo);//muestra la cabecera de un correo
bool cargar(tCorreo &correo, ifstream& archivo);//carga los mensajes de un archivo
void guardar(const tCorreo &correo, ofstream& archivo);//guarda los mensajes en un archivo
string mostrarFecha(tFecha fecha);
string mostrarSoloDia(tFecha fecha);
bool operator<(const tCorreo &opIzq, const tCorreo &opDer);//para poder ordenar los correos por asunto

#endif