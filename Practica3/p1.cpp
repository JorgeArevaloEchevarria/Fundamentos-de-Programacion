#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>


using namespace std;

const int MAX_DIM = 4;


typedef int tTablero[MAX_DIM][MAX_DIM];

typedef enum tAccion { arriba, abajo, izquierda, derecha, salir, nada };

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

int main(){


	return 0;
}


void nuevaPartida(tJuego &juego){

	for (int i=0;i<MAX_DIM;i++)
		for (int j=0;j<MAX_DIM;j++)
			juego.tableroAct[i][j] = 1;

	bool cuatro = false;
	int fila, columna, num;
	srand(NULL);

	for (int n = 0; n < 2; n++){

		fila = rand() % 4;
		columna = rand() % 4;
		num = rand() % (101);//aleatorio entre 0 y 100 para % de q salga 2 o 4

		if (num <= 95 || cuatro)
			juego.tableroAct[fila][columna] = 2;

		else{
			cuatro = true;
			juego.tableroAct[fila][columna] = 4;
		}
	}
}

void visualizar(const tJuego juego){

	cout << "Puntos ultima jugada: " << juego.ultPuntuacion << endl;
	cout << "Total: " << juego.total << endl;
	cout << "Meta: " << juego.meta << endl;

	//mostrarTablero()

}

int	log2(int num){


}

bool cargar(tJuego & juego){

	ifstream archivo;
	archivo.is_open();
	if(archivo.fail()){
	
	
	}





}