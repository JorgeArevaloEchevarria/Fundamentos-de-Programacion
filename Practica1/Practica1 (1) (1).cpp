#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>

using namespace std;

typedef enum {nadie, automata, persona}tJugador;
const int META = 31;


tJugador quienEmpieza();//elije quien empieza a jugar aleatoriamente, pudiendo ser automata o persona.
int digitoAleatorio();//genera un numero aleatorio entre 0 y 9.
int digitoPersona();//muestra la calculadora y pide un numero entre 0 y 9.
bool mismaFila(int ultimo, int nuevo);//comprueba si el numero introducido esta situado en la fila correcta.
bool mismaColumna(int ultimo, int nuevo);//comprueba si el numero introducido esta situado en la columna correcta.
bool digitoValido(int ultimo, int nuevo);//comprueba si el numero es valido respecto a las reglas del juego.
int digitoPersona(int ultimo);//pide un numero al usuario hasta que sea correcto respecto a las reglas del juego.
int digitoAutomata(int ultimo);//genera nuemero aleatorios hasta que sea correcto respecto las reglas del juego.
tJugador pasaCalculadora();//define el funcionamiento del juego, devolviendo al final de la partida al ganador.
int menu();//muestra las opciones que puedes elejir al empezar.
bool mostrar(string nombArch);//muestra de un archivo informacion sobre el juego.
bool actInforme(int jugadas, int ganadas, int abandonos);//guarda en un archivo de texto las sesiones, las partidas jugadas, las partidas ganadas y las partidas abandonadas.

int main(){

	string nombre;
	cout<<"\250Hola, como te llamas?"<<endl;
	getline(cin,nombre);
	cout<<"Buenas "<< nombre <<endl;

	srand(time(NULL));
	int op = menu();
	int jugadas = 0, ganadas = 0, abandonos = 0;
	tJugador ganador;

	while(op != 0){
		if(op == 1){
			ganador = pasaCalculadora();
			jugadas++;
			if (ganador == nadie)
				abandonos++;
			else if(ganador == automata){
					ganadas++;
					cout<<"Lo siento he ganado yo"<<endl;
			}
			else
				cout<<"Enhorabuena has ganado tu"<<endl;
		}else if (op==2)
			mostrar("versionPc.txt");
		cout << endl;
		op = menu();
	}
	actInforme(jugadas,ganadas,abandonos);

	return 0;

}


tJugador quienEmpieza(){
	
	tJugador jugador;
	int empieza;
	empieza = rand() % (1 + 1);//aleatorio entre 0 y 1 para elgir quien empieza
    
	if(empieza==1){
		jugador=persona;
		cout<<"Empiezas tu!"<<endl;
	}
	else{
		jugador=automata;
		cout<<"Empiezo yo!"<<endl;
	}
return jugador;
}

int digitoAleatorio(){

	int aleatorio;
	aleatorio = (rand() % 9) + 1;

	return aleatorio;

}

int digitoPersona(){

	int digito;
	cout << "	7	8	9" << endl;
	cout<<  "	4	5	6"<<endl;
	cout << "	1	2	3"<<endl;

	cout<<"Introduce un numero (0 para abandonar): ";
	cin>>digito;
	
	while(digito<0 || digito>9){
		
		cout<<"Error,tiene que ser un numero del 1 al 9."<<endl;
		cout << "	7	8	9" << endl;
		cout<<  "	4	5	6"<<endl;
		cout << "	1	2	3"<<endl;

		cout<<"Introduce un numero (0 para abandonar): ";
		cin>>digito;
	
	}

	return digito;

}

bool mismaFila(int ultimo, int nuevo){
	
	bool correctoFila;
	int filaUltimo, filaNuevo;

	filaUltimo = (ultimo-1)/3;
	filaNuevo = (nuevo-1)/3;
	
	if(filaUltimo==filaNuevo)
		correctoFila = true;
	else
		correctoFila = false;

	return correctoFila;

}


bool mismaColumna(int ultimo, int nuevo){
	
	bool correctoColumna;
	int columnaUltimo, columnaNuevo;

	columnaUltimo = (ultimo-1)%3;
	columnaNuevo = (nuevo-1)%3;
	
	if(columnaUltimo==columnaNuevo)
		correctoColumna = true;
	else
		correctoColumna = false;

	return correctoColumna;
	
}

bool digitoValido(int ultimo, int nuevo){
	
	bool digitoValido;

	if((mismaFila(ultimo,nuevo) || mismaColumna(ultimo,nuevo) ) && ultimo != nuevo)
		digitoValido = true;
	else
		digitoValido = false;

	return digitoValido;
}

int digitoPersona(int ultimo){
	
	int nuevo;
	nuevo = digitoPersona();

	while(nuevo!=0 && !digitoValido(ultimo,nuevo)){
		cout << "Error numero no valido" << endl;
		nuevo = digitoPersona();
	}

	return nuevo;
}

int digitoAutomata(int ultimo){

	int nuevo;
	nuevo = digitoAleatorio();

	while(!digitoValido(ultimo,nuevo))
		nuevo = digitoAleatorio();	


	return nuevo;
}

tJugador pasaCalculadora(){

	tJugador turno,ganador;
	turno = quienEmpieza();
	int suma,ultimo;
	suma = 0;
	
	
	if(turno == automata){
		ultimo = digitoAleatorio();
		cout << "Yo pongo: " << ultimo << endl;
		suma = suma + ultimo;
		turno = persona;
		}
		
	else {
		ultimo = digitoPersona();
		suma = suma + ultimo;
		turno = automata;
		}
	 
	cout << "SUMA:" << suma<< endl;
	
	while (suma < META && ultimo != 0){
		
			if (turno == automata){
			
				ultimo = digitoAutomata(ultimo);
				cout << "Yo pongo: " << ultimo << endl;
				suma = suma + ultimo;
				turno = persona;

			}else{
				
				ultimo = digitoPersona(ultimo);
				suma = suma + ultimo;
				turno = automata;
			
			 }

		cout << "SUMA:" << suma<< endl;
	}


	if (suma >= META && turno == persona)
		ganador = persona;
	else if (suma >= META && turno == automata)
		ganador = automata;
	else
		ganador = nadie;

	
	return ganador;

}

int menu(){

	int op;

	cout << "Introduzca una opcion" << endl << endl;
	cout << "1 - Jugar" << endl;
	cout << "2 - Acerca del juego" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opcion: ";
	cin >> op;
	cout << endl;

		while (op<0 || op>2) {
						
			cout << "Numero no valido" << endl;
			cout << "Introduzca una opcion" << endl << endl;
			cout << "1 - Jugar" << endl;
			cout << "2 - Acerca del juego" << endl;
			cout << "0 - Salir" << endl;
			cout << "Opcion: ";
			cin >> op;
			cout << endl;
		}

	return op;

}

bool mostrar(string nombArch){

	ifstream archivo;
	bool archivoAbierto;
	char n;
	archivo.open(nombArch);

	if (archivo.is_open()){
		archivoAbierto = true;
		archivo.get(n);

		while(!archivo.fail()){

			cout << n;
			archivo.get(n);
		}	
	}else{
	
		archivoAbierto = false;
		cout << "El archivo no se ha podido abrir" << endl;
	}

	archivo.close();
	
	return archivoAbierto;	
}

bool actInforme(int jugadas, int ganadas, int abandonos){

	ifstream archivo;
	ofstream archivo2;
	int jug=0,gan=0,aband=0,sesiones = 1;
	bool archivoAbierto = false;
	archivo.open("informePC.txt");

	if(archivo.is_open()){
		archivo >> sesiones;
		archivo >> jug;
		archivo >> gan;
		archivo >> aband;
		archivo.close();
		
		sesiones++;
		jug = jug + jugadas;
		gan = gan + ganadas;
		aband = aband + abandonos;

		archivo2.open("informePC.txt");
		archivo2 << sesiones << endl;
		archivo2 << jug << endl;
		archivo2 << gan << endl;
		archivo2 << aband << endl;
		archivo2.close();
		archivoAbierto = true;
	}else{	
		archivo2.open("informePC.txt");
		archivo2 << sesiones << endl;
		archivo2 << jugadas << endl;
		archivo2 << ganadas << endl;
		archivo2 << abandonos << endl;
		archivo2.close();
	}
	return archivoAbierto;
}



			
