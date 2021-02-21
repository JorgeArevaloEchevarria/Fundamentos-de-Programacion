//Jorge Arevalo
//Eduardo Rodriguez de Castro

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<iomanip>
#include<conio.h>
#include<ctype.h>

using namespace std;

const int MAX_DIM = 4;
const int ANCHURA_CASILLA = 6;
const int ALTURA_CASILLA = 3;
const int META = 2048;
const bool MODOPRUEBA = false;


typedef int tTabla[MAX_DIM][MAX_DIM];

typedef enum tAccion { arriba, abajo, izquierda, derecha, salir, nada };

typedef struct{

	tTabla tablero;
	int dimVerdera;

}tTablero;

typedef struct {

	tTablero tableroAct;
	int ultPuntuacion;
	int total;
	int meta;

}tJuego;

void nuevaPartida(tJuego &juego);
void visualizar(const tJuego juego);
int	log2(int num);
bool cargar(tJuego & juego);
void filaSuperior(tTablero tablero);
void separadorFila(tTablero tablero);
void filaInferior(tTablero tablero);
void colorFondo(int	color);
void pintarFila(tTablero tablero,int fila);
tAccion leeAccion();//Aunque pedia que no se podia devolver el valor nada,nos parecia mas eficiente utilizarlo para cuando se introduzca una tecla no valida
void inclinaIzquierda(tJuego &juego);						 
void inclinaDerecha(tJuego &juego);							
void inclinaAbajo(tJuego &juego);//Al implementar combinaFichas en inclina hemos pasado por parametro juego
void inclinaArriba(tJuego &juego);//para poder actualizar las puntuaciones en las funciones
void inclinaTablero(tJuego &juego,tAccion accion);
bool tableroMeta(const tTablero& tablero,int meta);
bool tableroLleno(const	tTablero& tablero);
void nuevaFicha(tTablero& tablero);


int main(){

	colorFondo(0);
	srand(time(NULL));

	tJuego juego;
	tAccion accion;
	bool lleno=false,meta=false,esc=false;
	char letra;
	
	cout << "Quieres cargar una partida[s/n]: ";
	cin >> letra;

	letra = tolower(letra);//Por la posibilidad que pongan mayus. y el programa no las reconozca

	if(letra == 's')
		cargar(juego);
	else if(letra == 'n')
		nuevaPartida(juego);

	visualizar(juego);

	while(!esc && !lleno && !meta){

		juego.ultPuntuacion = 0;
		accion = leeAccion();

		if(accion == nada)
			visualizar(juego);
		else if(accion == salir)
			esc=true;
		else{
			inclinaTablero(juego,accion);
			meta = tableroMeta(juego.tableroAct,META);
			lleno = tableroLleno(juego.tableroAct);
			
			if(!meta && !lleno)//solamente añadiremos ficha si las busquedas de meta y lleno dan false
				nuevaFicha(juego.tableroAct);

			visualizar(juego);
		}
	}

	if(lleno)
		cout <<endl<< "El tablero esta lleno.No puedes seguir jugando!"<<endl;
	else if(meta)	
		cout <<endl<< "Enhorabuena,has ganado!" <<endl;

	return 0;
}

void nuevaPartida(tJuego &juego){

	for (int i = 0; i<MAX_DIM; i++)
		for (int j = 0; j<MAX_DIM; j++)
			juego.tableroAct.tablero[i][j] = 1;

	bool cuatro = false;
	int fila, columna, num;
	
	for (int n = 0; n < 2; n++){
		
		fila = rand() % 4;
		columna = rand() % 4;
		num = rand() % (101);//aleatorio entre 0 y 100 para % de q salga 2 o 4

		if (num <= 95 || cuatro)//95% el dos o que haya salido un cuatro ya que no puede empezar el juego con dos 4
			juego.tableroAct.tablero[fila][columna] = 2;

		else{
			cuatro = true;
			juego.tableroAct.tablero[fila][columna] = 4; 
		}
	}

	juego.tableroAct.dimVerdera = MAX_DIM;
	juego.meta = META;
	juego.total = 0;
	juego.ultPuntuacion = 0;

 }

void visualizar(const tJuego juego){
	
	if(!MODOPRUEBA)
		system("cls");

	cout << "Puntos ultima jugada: " << juego.ultPuntuacion << endl;
	cout << "Total: " << juego.total << endl;
	cout << "Meta: " << juego.meta << endl;

	filaSuperior(juego.tableroAct);
	for(int fila=0;fila<juego.tableroAct.dimVerdera;fila++){
		pintarFila(juego.tableroAct,fila);
		if(fila<juego.tableroAct.dimVerdera-1)
			separadorFila(juego.tableroAct);
		}
		filaInferior(juego.tableroAct);

	cout<< "Usa las teclas de flecha(Esc para salir)..." << endl;
}

int	log2(int num){

	int potencia=0;

	while(num!=1){
	
		num=num/2;
		potencia++;
	}
	return potencia;
}

bool cargar(tJuego & juego){

	bool cargar=true;
	ifstream archivo;
	string juegos;


	cout << "Donde se encuentra el juego: ";
	cin >> juegos;

	archivo.open(juegos);

	if (!archivo.is_open()){
		cout<<"No hay un juego guardado.Lo inicializaremos de forma aleatoria."<<endl;
		nuevaPartida(juego);
		cargar=false;

	}else{
	
		archivo>> juego.tableroAct.dimVerdera;

		if(MAX_DIM==juego.tableroAct.dimVerdera){
		
			for(int fila=0;fila<juego.tableroAct.dimVerdera;fila++)
				for(int columna=0;columna<juego.tableroAct.dimVerdera;columna++)
					archivo >> juego.tableroAct.tablero[fila][columna];

			archivo>>juego.total;
			archivo>>juego.meta;
			juego.ultPuntuacion=0;
		}
	}

	archivo.close();

	return cargar;
}

void filaSuperior(tTablero tablero){

	cout << char(218);

	for (int i = 0; i < tablero.dimVerdera; i++){

		if (i>0 && i < MAX_DIM)
			cout << char(194);

		for (int c = 0; c < ANCHURA_CASILLA; c++)
			cout << char(196);

	}
	cout << char(191) << endl;
	
}

void separadorFila(tTablero tablero){

	cout << char(195);

	for (int c = 0; c < tablero.dimVerdera; c++){

		if (c > 0 && c < MAX_DIM)
			cout << char(197);

		for (int i = 0; i < ANCHURA_CASILLA; i++)
			cout << char(196);
	
	} 
	cout << char(180) << endl;

}

void filaInferior(tTablero tablero){

	cout << char(192);

	for (int j = 0; j < tablero.dimVerdera; j++){

		if (j > 0 && j < MAX_DIM)
			cout << char(193);

		for (int i = 0; i < ANCHURA_CASILLA; i++)
			cout << char(196);

	}

	cout << char(217) << endl;
}

void colorFondo(int	color){
	HANDLE	handle	=	GetStdHandle(STD_OUTPUT_HANDLE);	
	SetConsoleTextAttribute(handle,	15	|	(color	<<	4));
}

void pintarFila(tTablero tablero,int fila){
	for(int columna=0;columna<tablero.dimVerdera;columna++){
		cout << char(179);
		colorFondo(log2(tablero.tablero[fila][columna]));
		if(tablero.tablero[fila][columna] != 1){
			colorFondo(log2(tablero.tablero[fila][columna]));
			cout << setw(6);
			cout << "";
			colorFondo(0);
		}else
			cout << setw(7);
		
	}
	colorFondo(0);
	cout << char(179)<<endl;

	for(int columna=0;columna<tablero.dimVerdera;columna++){
		cout << char(179);
		if(tablero.tablero[fila][columna] != 1){
			
			colorFondo(log2(tablero.tablero[fila][columna]));
			cout << setw(6);
			cout << tablero.tablero[fila][columna];
			colorFondo(0);
		}else
			cout << setw(7);
	}
	cout << char(179) << endl;

	for(int columna=0;columna<tablero.dimVerdera;columna++){
		
		cout << char(179);
		if(tablero.tablero[fila][columna] != 1){
			colorFondo(log2(tablero.tablero[fila][columna]));
			cout << setw(6);
			cout << "";
			colorFondo(0);
		
		}else
			cout << setw(7);
	}
	colorFondo(0);
	cout << char(179)<<endl;
}

tAccion leeAccion(){

	int dir;
	tAccion accion;

	cin.sync();
	dir	=_getch(); 

	if(dir==0xe0){
		dir	=	_getch();
		if(dir==72)
			accion=arriba;
		else if(dir==80)
			accion=abajo;
		else if(dir==77)
			accion=derecha;
		else if(dir==75)
			accion=izquierda;

	}else if(dir==27)
		accion=salir;
	else
		accion=nada;

	return accion;
}

void inclinaIzquierda(tJuego &juego){

	int huecos;
	bool suma=false;

	for(int fila=0;fila<juego.tableroAct.dimVerdera;fila++){
		huecos=0;
		for(int columna=0;columna<juego.tableroAct.dimVerdera;columna++){
			if(juego.tableroAct.tablero[fila][columna] == 1)
				huecos++;
			else
				if(huecos>0){
					juego.tableroAct.tablero[fila][columna-huecos] = juego.tableroAct.tablero[fila][columna];///movimiento de fichas
					juego.tableroAct.tablero[fila][columna]=1;
				}

				if(juego.tableroAct.tablero[fila][columna-huecos-1] == juego.tableroAct.tablero[fila][columna-huecos] && (columna-huecos-1)>=0 && !suma ){

					juego.tableroAct.tablero[fila][columna-huecos-1] += juego.tableroAct.tablero[fila][columna-huecos];//suma de los valores 
					juego.tableroAct.tablero[fila][columna-huecos] = 1;//vaciamos y posteriormente añadiremos este hueco
					juego.ultPuntuacion += juego.tableroAct.tablero[fila][columna-huecos-1];//sumamos en la ult puntuacion el valor en esta vuelta
					huecos++;
					suma=true;
					
				}else
					suma=false;
		}
	
	}
	juego.total += juego.ultPuntuacion;//actualizamos la punt. total
}

void inclinaDerecha(tJuego &juego){

	int huecos;
	bool suma=false;

	for(int fila=0;fila<juego.tableroAct.dimVerdera;fila++){
		huecos=0;
		for(int columna=juego.tableroAct.dimVerdera-1;columna>=0;columna--){
			if(juego.tableroAct.tablero[fila][columna] == 1)
				huecos++;
			else
				if(huecos>0){
					juego.tableroAct.tablero[fila][columna+huecos] = juego.tableroAct.tablero[fila][columna];
					juego.tableroAct.tablero[fila][columna]=1;
				}	

				if(juego.tableroAct.tablero[fila][columna+huecos+1] == juego.tableroAct.tablero[fila][columna+huecos] && (columna+huecos+1)<= MAX_DIM-1 && !suma){

					juego.tableroAct.tablero[fila][columna+huecos+1] += juego.tableroAct.tablero[fila][columna+huecos];
					juego.tableroAct.tablero[fila][columna+huecos] = 1;
					juego.ultPuntuacion += juego.tableroAct.tablero[fila][columna+huecos+1];
					huecos++;
					suma = true;
				}else
					suma=false;
		}	
	}
	juego.total += juego.ultPuntuacion;
}

void inclinaAbajo(tJuego &juego){

	int huecos;
	bool suma=false;

	for(int columna=0;columna<juego.tableroAct.dimVerdera;columna++){
		huecos=0;
	
		for(int fila=juego.tableroAct.dimVerdera-1;fila>=0;fila--){
			if(juego.tableroAct.tablero[fila][columna] == 1)
				huecos++;
			else
				if(huecos>0){
					juego.tableroAct.tablero[fila+huecos][columna] = juego.tableroAct.tablero[fila][columna];
					juego.tableroAct.tablero[fila][columna]=1;
				}	

				if(juego.tableroAct.tablero[fila+huecos+1][columna] == juego.tableroAct.tablero[fila+huecos][columna] && (fila+huecos+1)<=MAX_DIM-1 && !suma){

					juego.tableroAct.tablero[fila+huecos+1][columna] += juego.tableroAct.tablero[fila+huecos][columna];
					juego.tableroAct.tablero[fila+huecos][columna] = 1;
					juego.ultPuntuacion += juego.tableroAct.tablero[fila+huecos+1][columna];
					huecos++;
					suma=true;
					
				}else 
					suma=false;

		}	
	}
	juego.total += juego.ultPuntuacion;
}

void inclinaArriba(tJuego &juego){

	int huecos;
	bool suma=false;

	for(int columna=0;columna<juego.tableroAct.dimVerdera;columna++){
		huecos=0;
		for(int fila=0;fila<juego.tableroAct.dimVerdera;fila++){
			if(juego.tableroAct.tablero[fila][columna] == 1)
				huecos++;
			else
				if(huecos>0){
					juego.tableroAct.tablero[fila-huecos][columna] = juego.tableroAct.tablero[fila][columna];
					juego.tableroAct.tablero[fila][columna]=1;
				}

				if(juego.tableroAct.tablero[fila-huecos-1][columna] == juego.tableroAct.tablero[fila-huecos][columna] && (fila-huecos-1)>=0 && !suma){

					juego.tableroAct.tablero[fila-huecos-1][columna] += juego.tableroAct.tablero[fila-huecos][columna];
					juego.tableroAct.tablero[fila-huecos][columna] = 1;
					juego.ultPuntuacion += juego.tableroAct.tablero[fila-huecos-1][columna];
					huecos++;
					suma=true;

				}else
					suma=false;
		}	
	}
	juego.total += juego.ultPuntuacion;
}

void inclinaTablero(tJuego& juego,tAccion accion){

	if(accion == izquierda)
		inclinaIzquierda(juego);
	else if(accion == derecha)
		inclinaDerecha(juego);
	else if(accion == abajo)
		inclinaAbajo(juego);
	else if(accion == arriba)
		inclinaArriba(juego);
}

bool tableroMeta(const tTablero& tablero,int meta){
	int fila=0,columna;
	bool metas=false;

	while(fila<tablero.dimVerdera && !metas){
		columna=0;
		while(columna<tablero.dimVerdera && !metas){
		
			if(tablero.tablero[fila][columna] == meta)
				metas=true;
			else
				columna++;
		}	
		fila++;
	}

	return metas;
}

bool tableroLleno(const	tTablero& tablero){

	bool lleno=true;
	int fila=0,columna;

	while(fila<tablero.dimVerdera && lleno){
		columna=0;
		while(columna<tablero.dimVerdera && lleno){
			
			if(tablero.tablero[fila][columna] == 1)
				lleno=false;
			else
				columna++;
		}

		fila++;
	}

	return lleno;
}

void nuevaFicha(tTablero& tablero){
	
	int fila,columna,num;
	bool libre=false;
		
		while(!libre){
			fila = rand() % 4;
			columna = rand() % 4;
			if(tablero.tablero[fila][columna] == 1)
				libre=true; 
		}

		num = rand() % (101);

		if (num <= 95)
			tablero.tablero[fila][columna] = 2;

		else
			tablero.tablero[fila][columna] = 4; 
}