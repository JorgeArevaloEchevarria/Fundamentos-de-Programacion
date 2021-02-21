//Correo.cpp
#include"Correo.h"
#include<iostream>

using namespace std;

void correoNuevo(tCorreo &correo, string emisor){

	string cadena, cadenaAsunto;
	stringstream flujo;

	correo.fecha = time(0);
	correo.emisor=emisor;

	flujo << correo.emisor << '_' << correo.fecha;
	correo.id = flujo.str();

	cout << "De: " << correo.emisor << endl;
	cout << "Para: ";
	cin>>correo.destinatario;
	cin.sync();
	cout << "Asunto: " ;
	getline(cin, cadenaAsunto);
	correo.asunto = cadenaAsunto;
	cin.sync();
	

	cout<<endl;

	getline(cin, cadena);
	
	while (cadena != CENTINELA){
	
		correo.cuerpo += cadena;
		correo.cuerpo += SALTO;
		getline(cin, cadena);
	
	}
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){

	string cadena;
	stringstream flujo;

	correo.emisor=emisor;
	correo.fecha = time(0);

	flujo << correo.emisor << '_' << correo.fecha;
	correo.id = flujo.str();

	cout << "De: " << correo.emisor << endl;
	correo.destinatario=correoOriginal.emisor;
	cout << "Para: " << correo.destinatario << endl;
	correo.asunto= "Re:" + correoOriginal.asunto;
	cout <<correo.asunto<<endl;

	getline(cin, cadena);

	while (cadena != CENTINELA){

		correo.cuerpo += cadena;
		correo.cuerpo += SALTO;
		getline(cin, cadena);

	}
	correo.cuerpo += "------------------------------------    ";
	correo.cuerpo += SALTO;
	correo.cuerpo += "De: ";
	correo.cuerpo += correoOriginal.emisor;
	correo.cuerpo += SALTO;
	correo.cuerpo += "Para: ";
	correo.cuerpo += correoOriginal.destinatario;
	correo.cuerpo += SALTO;
	correo.cuerpo += "Asunto :";
	correo.cuerpo += correoOriginal.asunto;
	correo.cuerpo += SALTO;
	correo.cuerpo += SALTO;
	correo.cuerpo += correoOriginal.cuerpo;
	correo.cuerpo += SALTO;
	correo.cuerpo += "------------------------------------    ";

	cout << correo.cuerpo << endl;
}

string aCadena(const tCorreo &correo){

	stringstream flujo;
	
	flujo << "De: " << correo.emisor << "                   "<< mostrarFecha(correo.fecha) << endl;
	flujo << "Para: " << correo.destinatario << endl;
	flujo << "Asunto: " << correo.asunto << endl<<endl;
	flujo << correo.cuerpo << endl<<endl;

	return flujo.str();
}

string obtenerCabecera(const tCorreo &correo){

	stringstream flujo;

	flujo << correo.emisor << "           " << correo.asunto << "            " << mostrarSoloDia(correo.fecha) << endl;

	return flujo.str();

}

bool cargar(tCorreo &correo, ifstream &archivo){
	
	bool ok = true;
	string centinela,cuerpo, cadena;

	archivo >> correo.id;
	archivo>>correo.fecha;
	archivo>>correo.emisor;
	archivo>>correo.destinatario;
	cin.sync();
	getline(archivo, cadena);
	getline(archivo, correo.asunto);
	getline(archivo,cuerpo);
	
	while(cuerpo != CENTINELA){

		correo.cuerpo += cuerpo;
		correo.cuerpo += SALTO;
		getline(archivo,cuerpo);
		}
	

	return ok;

}

void guardar(const tCorreo &correo, ofstream& archivo){
	
	archivo << correo.id << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo << endl;
	archivo << CENTINELA<<endl;
}

string mostrarFecha(tFecha fecha){
	
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;
	resultado<<" ("<<ltm.tm_hour<< ":" <<ltm.tm_min<< ":" << ltm.tm_sec << ")";
	
	return resultado.str();
 }

string mostrarSoloDia(tFecha fecha){
	 
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;

	return resultado.str();

 }

bool operator<(const tCorreo &opIzq, const tCorreo &opDer){
	return (opIzq.asunto < opDer.asunto) || (opIzq.asunto == opDer.asunto && opIzq.fecha < opDer.fecha);
}