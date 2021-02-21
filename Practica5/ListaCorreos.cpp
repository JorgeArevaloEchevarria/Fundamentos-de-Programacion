//ListaCorreos.cpp
#include"ListaCorreos.h"
#include"Correo.h"
#include<iostream>

using namespace std;

void inicializar(tListaCorreos &correos,int capInicial){

	correos.datoCorreo = new tCorreo[capInicial];
	correos.cont = 0;
	correos.capacidad = capInicial;

}

bool buscar(const tListaCorreos &correos, string id, int &pos){

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

	if (correos.cont == correos.capacidad)
		redimensionar(correos);


	int i = correos.cont;

	while ((i > 0) && (correo.id < correos.datoCorreo[i - 1].id)){

		correos.datoCorreo[i] = correos.datoCorreo[i - 1];
		i--;

	}

	correos.datoCorreo[i] = correo;
	correos.cont++;
	
	return ok;
}

bool cargar(tListaCorreos &correos, string dominio){

	bool ok = true;
	bool correcto = true;
	string arch;
	ifstream archivo;
	stringstream flujo;
	int n;

	flujo << dominio << ARCHIVO;
	arch = flujo.str();

	archivo.open(arch);
	
	if(!archivo.is_open())
		ok=false;
	else{ 
		archivo >> n;
		inicializar(correos,(n+10)-(n%10));
		
		for(int i = 0;i<n;i++){
			cargar(correos.datoCorreo[correos.cont],archivo);
			insertar(correos,correos.datoCorreo[correos.cont]);
		}

	archivo.close();
	}
	
	return ok;
}

void guardar(const tListaCorreos &correos, string dominio){

	ofstream archivo;
	stringstream flujo;
	string arch;

	flujo << dominio << ARCHIVO;
	arch = flujo.str();

	archivo.open(arch);

	archivo << correos.cont << endl;

	for(int i = 0; i < correos.cont; i++)
		guardar(correos.datoCorreo[i],archivo);

	archivo.close();

}

void ordenar_AF(tListaCorreos &correos){
	
	bool inter = true;
	int i = 0;

	while((i < correos.cont-1) && inter){
		inter = false;

		for (int j = correos.cont - 1; j > i; j--){
			if (correos.datoCorreo[j].asunto < correos.datoCorreo[j - 1].asunto){
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

void redimensionar(tListaCorreos &correos){
	
	correoPtr nuevoCorreo = new tCorreo[(correos.capacidad*3)/2+1];

	for(int i = 0;i < correos.cont;i++)
		nuevoCorreo[i] = correos.datoCorreo[i];
	
	correos.capacidad = (correos.capacidad*3)/2+1;

	delete[] correos.datoCorreo;

	correos.datoCorreo = nuevoCorreo;
}

void destruir(tListaCorreos &correos){

	delete[] correos.datoCorreo;

}



