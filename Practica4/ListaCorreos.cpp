//ListaCorreos.cpp
#include"ListaCorreos.h"
#include"Correo.h"
#include<iostream>

using namespace std;

void inicializar(tListaCorreos &correos){

	correos.cont = 0;//contador de la lista a 0
	
}

bool buscar(const tListaCorreos &correos, string id, int &pos){//busqueda binaria

		int ini = 0, fin, mitad;
		bool encontrado = false;

		fin = correos.cont - 1;

		while((ini <= fin) && !encontrado){

			mitad = (ini + fin) / 2;

			if (id < correos.datoCorreo[mitad].id)
				fin = mitad-1;

			else if (correos.datoCorreo[mitad].id < id)
				ini = mitad + 1;

			else 
				encontrado = true;
		}
		if (encontrado) 
			pos = mitad;
		else 
			pos = ini;

return encontrado;

}

bool insertar(tListaCorreos &correos, const tCorreo &correo){
		
	bool ok = true;
	tCorreo correoAux;
	correoAux = correo;

	if (correos.cont == MAX_CORREOS){

		ok = false;//lista llena
		cout << "La lista de correos esta llena, no se ha podido enviar el mensaje.";

	}
	else{
		int i = correos.cont;

		while ((i > 0) && (correo.id < correos.datoCorreo[i - 1].id)){

			correos.datoCorreo[i] = correos.datoCorreo[i - 1];//desplaza los elementos de la lista para insertar
			i--;

		}
		correos.datoCorreo[i] = correoAux;
		correos.cont++;
	}
	return ok;
}

bool cargar(tListaCorreos &correos, string dominio){

	bool ok = true;
	bool correcto = true;
	string arch;
	ifstream archivo;
	stringstream flujo;

	flujo << dominio << ARCHIVO;//nombre del archivo
	arch = flujo.str();

	archivo.open(arch);
	
	if(!archivo.is_open())
		ok=false;
	else{
		inicializar(correos);//inicialza para cargar
		
		while (correos.cont <= MAX_CORREOS && correcto){

			correcto = cargar(correos.datoCorreo[correos.cont],archivo);//carga los correos llamando a cargar de correo

			if (correcto)
				insertar(correos,correos.datoCorreo[correos.cont]);//inserta el correo

		}
	}

	archivo.close();

	return ok;
}

void guardar(const tListaCorreos &correos, string dominio){

	ofstream archivo;
	stringstream flujo;
	string arch;

	flujo << dominio << ARCHIVO;//nombre archivo
	arch = flujo.str();

	archivo.open(arch);

	for(int i = 0; i < correos.cont; i++)
		guardar(correos.datoCorreo[i],archivo);//va guardando los correos
	
	archivo << CENTINELA_FINAL;

	archivo.close();

}

void ordenar_AF(tListaCorreos &correos){
	
	bool inter = true;
	int i = 0;

	while((i < correos.cont-1) && inter){
		inter = false;

		for (int j = correos.cont - 1; j > i; j--){
			if (correos.datoCorreo[j].asunto < correos.datoCorreo[j - 1].asunto){//va ordenando segun el asunto
				tCorreo tmp;
				tmp = correos.datoCorreo[j];
				correos.datoCorreo[j] = correos.datoCorreo[j-1];
				correos.datoCorreo[j-1] = tmp;
				inter = true;
			}
		}

		if(inter)
			i++;
	}
}




