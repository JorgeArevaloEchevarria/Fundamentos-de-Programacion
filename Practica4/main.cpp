//Jorge Arevalo Echevarria
//Eduardo Rodriguez de Castro
//Bibliotecas
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "gestor.h"

int menu(string dominio);


int main(){

	string dominio;
	int opcion = 1, op = 0;
	bool comienzo = false, ok=false, entrada = true; //Empieza siempre mostrando la bandeja de entrada
	tGestor gestor;
	dominio = "fdimail.com";//por defecto metemos este dominio
	
	comienzo = arrancar(gestor, dominio);

	if (comienzo){
		while (opcion != 0 && !ok){
			opcion = menu(dominio);

			switch (opcion) {
			case 0:
				//Salir de la aplicacion
				cout << "Hasta luego. " << endl;
				apagar(gestor);
				break;
			case 1:
				//Inicio de sesion
				
				ok = iniciarSesion(gestor);

				if (ok){
					entrada = true;
					do{
						op = menuBandeja(gestor, entrada);
						ejecutarMenuBandeja(gestor, op, entrada);
					} while (op != 0);
				}
				break;
			case 2:
				//Creacion de una cuenta
				ok = crearCuenta(gestor);
				if (ok){
					entrada = true;
					do {
						op = menuBandeja(gestor, entrada);
						ejecutarMenuBandeja(gestor, op, entrada);
					} while (op != 0);
				}
				else {
					cout << "No caben más usuarios en el dominio." << endl << endl;
				}
				break;
			}
		} //while (op != 0 || !ok);
	} 
	
	apagar(gestor);

	system("pause");

	return 0;
}

int menu(string dominio){
	int opcion;

	do {
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "-           Bienvenido al gestor de correo de " << dominio << "                     -" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "Elija la opcion deseada:" << endl
			<< "1- Acceder a mi cuenta de correo" << endl
			<< "2- Crear cuenta de correo" << endl << endl
			<< "0- Salir" << endl
			<< "Opcion -> ";
		cin >> opcion;

		if (opcion > 2 || opcion < 0) {
			cout << "Opcion incorrecta. Seleccione otra vez." << endl;
		}

	} while (opcion > 2 || opcion < 0);

	return opcion;
}
