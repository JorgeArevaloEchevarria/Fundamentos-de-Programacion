//Jorge Arévalo Echevarría 
//Eduardo Rodríguez de Castro Zaloña
//No hemos hecho la opcional
//Laboratorio 2

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<ctime>


using namespace std;

typedef int tCarta;

const int MAXCARTAS = 53;
const tCarta CENTINELA = 52;
const int CARTASPORPALO= 13;

typedef enum {picas,treboles,diamantes,corazones} tPalo;//enumerado que define los palos de las cartas

typedef enum {A,dos,tres,cuatro,cinco,seis,siete,ocho,nueve,diez,J,Q,K} tNumero;//enumerado que define el valor de las cartas

typedef tCarta tMazo[MAXCARTAS];

int menu();//función que muestra el menu por consola
void crearMazoVacio(tMazo mazo);//función que genera un mazo sin cartas
int cuantasEnMazo(const tMazo mazo);//devuelve en numero de cartas del mazo
tPalo darPalo(tCarta carta);//devuelve el palo de la carta
tNumero darNumero(tCarta carta);//devuelve el valor de la carta
void escribirCarta(tCarta carta);//muestra por pantalla la carta
void escribirMazo(const tMazo mazo);//muestra por pantalla el contenido del mazo
bool cargarMazo(tMazo mazo);//carga las cartas del archivo.txt al mazo
void opcionCargarMazo(tMazo mazo);//función que carga y enseña el mazo por pantalla
void barajarMazo(tMazo mazo);//cambia el orden de las cartas del mazo
void opcionBarajarMazo(tMazo mazo);//función que baraja y muestra el mazo barajado
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);//une dos mazos transformandolos en uno solo
void opcionUnirMazo(tMazo mazo);//función que muestra los mazos que va a unir y muestra el mazo unido
bool partirMazo(tMazo mazoOriginal,int cuantasCoger,tMazo mazoDestino);//divide el mazo en dos, por donde haya seleccionado el usuario
void cortarMazo(tMazo mazo, int cuantas);//parte del mazo con la funcion partir, y después vuelve a unir los mazos al revés de como los ha partido
void opcionCortarMazo(tMazo mazo);//función que muestra el mazo entero lo corta y muestra el resultado
void guardarMazo(const tMazo mazo);//escribe el mazo en un archivo.txt
tCarta cartaDePalo(char c, int n);//conversor que devuelve un tipo tCarta al introducirle un char y un int(como está en los txt)
string enumToPalo(tPalo palo);//conversor que devuelve una cadena introduciéndole un tipo tPalo(d=>diamantes)
string enumToNumero(tNumero numero);//conversor para facilitar la lectura de las cartas al usuario (1=>As)
char paloToChar(tPalo palo);//transforma el palo en un caractér para escribir en el archivo.txt
void repartirNegroRojo(const tMazo mazo,tMazo mazoNegro, tMazo mazoRojo);//mira el palo de la carta, y según sea el palo lo mete a mazoNegro o mazoRojo
void opcionSepararColor(tMazo mazo);//muestra la división que se ha producido antes entre el mazo rojo y negro
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);//mira el valor de la carta, y según sea el valor lo mete a mazoAltas o mazoBajas
void opcionSepararTamaño( tMazo mazo);//muestra la división que se ha producido antes entre el mazoAltas y mazoBajas
void repartirIntercalando(const tMazo mazo,int enCuantosMazos,int queMazoPido, tMazo mazoNuevo);//reparte el mazo segun los valores que le entren por parametro
void opcionIntercalada(tMazo mazo);//muestra la división de los mazos repartidos intercalando en tres mazos
void trucoTresMontones();
void trucoPosada();

int main(){

	srand(time(NULL));//para que no genere siempre los mismos aleatorios(semilla)
	tMazo mazo;
	int op;
	crearMazoVacio(mazo);//El mazo interno con el que jugaremos,lo inicializamos(lo creamos vacio) y el usuario lo podrá variar a lo largo del juego
	cout << "Jugaremos con un mazo que debes cargar excepto para los dos trucos de magia!" << endl << endl;
	op = menu();

	while(op!=0) {
		switch(op){
	
			case 1: opcionCargarMazo(mazo);
					break;
			case 2: opcionBarajarMazo(mazo);
					break;
			case 3: opcionUnirMazo(mazo);
					break;
			case 4: opcionCortarMazo(mazo);
					break;
			case 5: guardarMazo(mazo);
					break;
			case 6: opcionSepararColor(mazo);
					break;
			case 7: opcionSepararTamaño(mazo);
					break;
			case 8: opcionIntercalada(mazo);
					break;
			case 9: trucoTresMontones();
					break;
			case 10: trucoPosada();
					break;
			default :  cout<<"La opcion introducida es erronea"<<endl;
		}
		op = menu();
	}
	
	return 0;

}

int menu(){
	
	int op;
	
	cout <<"1-Carga un mazo de cartas de fichero"<<endl;
	cout <<"2-Barajar mazo de cartas"<<endl;
	cout <<"3-Agregar un mazo"<<endl;
	cout <<"4-Cortar mazo"<<endl;
	cout <<"5-Guardar mazo de cartas en fichero"<<endl;
	cout <<"6-Separar en Rojas y Negras"<<endl;
	cout <<"7-Separar en Bajas y Altas"<< endl;
	cout <<"8-Repartir de manera intercalada en tres montones"<<endl;
	cout <<"9-Truco de los tres montones"<<endl;
	cout <<"10-Truco de la posada"<<endl;
	cout <<"0-Salir"<< endl;
	
	cout << "Introduce una opcion: ";
	cin >> op;
	cout << endl;

	while(op<0 || op>10){
	
		cout << "Opcion no valida!"<<endl<<endl;
		cout <<"1-Carga un mazo de cartas de fichero"<<endl;
		cout <<"2-Barajar mazo de cartas"<<endl;
		cout <<"3-Agregar un mazo"<<endl;
		cout <<"4-Cortar mazo"<<endl;
		cout <<"5-Guardar mazo de cartas en fichero"<<endl;
		cout <<"6-Separar en Rojas y Negras"<<endl;
		cout << "7-Separar en Bajas y Altas"<< endl;
		cout << "8-Repartir de manera intercalada en montones"<<endl;
		cout << "9-Truco de los tres montones"<<endl;
		cout << "10-Truco de la posada"<<endl;
		cout <<"0-Salir"<< endl;
	
		cout << "Introduce una opcion: ";
		cin >> op;
		cout << endl;
	}

	return op;
}

void crearMazoVacio(tMazo mazo){

	mazo[0] = CENTINELA;

}

int cuantasEnMazo(const tMazo mazo){

	int contador = 0;

	while(mazo[contador] != CENTINELA)//recorrerá todo el mazo hasta el centinela y devolverá el contador que tiene el número de cartas en el mazo
		contador++;

	return contador;
}

tPalo darPalo(tCarta carta){

	return tPalo(carta/CARTASPORPALO);//fórmula por el cual introducida el número de la carta, devolverá el palo en el enumerado

}

tNumero darNumero(tCarta carta){

	return tNumero(carta%CARTASPORPALO);//fórmula por el cual introducida el numero de la carta, devolvera el valor en el enumerado

}

void escribirCarta(tCarta carta){

	tPalo palo;
	tNumero numero;

	palo = darPalo(carta);
	numero = darNumero(carta);

	cout << enumToNumero(numero) << " de " << enumToPalo(palo) << endl;

}

void escribirMazo(const tMazo mazo){

	int contador = 0;

	while(mazo[contador] != CENTINELA && contador < MAXCARTAS){
		escribirCarta(mazo[contador]);
		contador++;
	}

}

bool cargarMazo(tMazo mazo){
	int n, contador=0;
	char c;
	string nombArch;
	ifstream archivo;
	bool mazoLleno;
	cout << "En que archivo se encuentra el mazo:";
	cin >> nombArch;
	archivo.open(nombArch);


	if(!archivo.is_open())
		mazoLleno=false;
	
	else{
		mazoLleno=true;
		archivo >> c;

		while(c != 'x' && contador < (MAXCARTAS-1)){//lee hasta que encuentre 'x' en el archivo o llegue a la posición 51 para poder poner el CENTINELA en la 52.
			archivo >> n;
			mazo[contador]=cartaDePalo(c,n);
			contador++;
			archivo >> c;
		}
		mazo[contador]=CENTINELA;

		archivo.close();
	}
	cout <<endl;
	return mazoLleno;
}
 
void barajarMazo(tMazo mazo){

	 int n, m,aux,numCartas;
	 int contador=0;
	 numCartas = cuantasEnMazo(mazo);

	 while(contador<(numCartas*3)){
		
		 n=rand()%((numCartas-1));//genera un número aleatorio dentro del número de cartas
		 m=rand()%((numCartas-1));

		aux= mazo[n];
		mazo[n]=mazo[m];//ese aleatorio se intercambia la posición con el otro aleatorio
		mazo[m]=aux;

		contador++; 
	 }
}

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo){

	int cuantasOriginal,cuantasNuevo,contador=0;
	bool unir=true;

	cuantasOriginal = cuantasEnMazo(mazoOriginal);
	cuantasNuevo = cuantasEnMazo(nuevoMazo);
	

	if(cuantasNuevo+cuantasOriginal > 52){//mira si la unión de los mazos superaría el nuúmero máximo de cartas por mazo
		unir = false;
		cout << endl << "El tamaño del mazo se sobrepasa,no se pueden unir los mazos!" << endl;
	}
	while (unir && (contador < cuantasNuevo)){
	
		mazoOriginal[cuantasOriginal+contador] = nuevoMazo[contador];//introduce al final de mazo original el nuevo mazo
		contador++;
	}
	mazoOriginal[cuantasOriginal+contador] = CENTINELA;

	return unir;
}

bool partirMazo(tMazo mazoOriginal,int cuantasCoger,tMazo mazoDestino){

	int cuantasOriginal,contador = 0;
	bool partir = true;

	cuantasOriginal = cuantasEnMazo(mazoOriginal);

	if(cuantasOriginal < cuantasCoger)
		partir = false;

	while(partir && contador < cuantasOriginal){

		mazoDestino[contador] = mazoOriginal[contador];
		mazoOriginal[contador]= mazoOriginal[cuantasCoger+contador];
		contador++;	
	}
	mazoDestino[cuantasCoger]=CENTINELA;

	return partir;
}

void cortarMazo(tMazo mazo, int cuantas){

	bool partir;
	tMazo mazoDestino;

	partir = partirMazo(mazo,cuantas,mazoDestino);

	if(partir)
		unirMazos(mazo,mazoDestino);

}

void guardarMazo(const tMazo mazo){

	int contador= 0,n;
	ofstream archivo;
	tCarta carta;
	tPalo palo;
	tNumero numero;
	char c;
	string nombArch;

	cout << "Donde quieres guardar el mazo:";
	cin>> nombArch;

	archivo.open(nombArch);

	while(mazo[contador] != CENTINELA){
		
		carta = mazo[contador];
		palo = darPalo(carta);
		numero = darNumero(carta);
		c = paloToChar(palo);
		n = int(numero+1);

		archivo << c;
		archivo << " ";
		archivo << n;
		archivo << endl;
		contador++;
	
	}
	archivo << 'x';
	archivo.close();

}

tCarta cartaDePalo(char c, int n){
	
	tCarta carta;

	switch(c){
		
	case 'p': carta = tCarta(n-1);break;
	case 't': carta = tCarta(CARTASPORPALO + n-1);break;
	case 'd': carta = tCarta(2*CARTASPORPALO + n-1);break;
	case 'c': carta = tCarta(3*CARTASPORPALO + n-1);break;
	}

	return carta;

}

string enumToPalo(tPalo palo){
	
	string cadena;

	switch(palo){
	
	case picas:		cadena="picas";break;
	case treboles:	cadena="treboles";break;
	case diamantes:	cadena="diamantes";break;
	case corazones: cadena="corazones";break;	
	}
	
	return cadena;

}

string enumToNumero(tNumero numero){
	
	string cadena;

	switch(numero){
	
	case A:			cadena="As";break;
	case dos:		cadena="Dos";break;
	case tres:		cadena="Tres";break;
	case cuatro:	cadena="Cuatro";break;
	case cinco:		cadena="Cinco";break;
	case seis:		cadena="Seis";break;
	case siete:		cadena="Siete";break;
	case ocho:		cadena="Ocho";break;
	case nueve:		cadena="Nueve";break;
	case diez:		cadena="Diez";break;
	case J:			cadena="Jota";break;
	case Q:			cadena="Reina";break;
	case K:			cadena="Rey";break;

	}
	
	return cadena;

}

char paloToChar(tPalo palo){

	char c;

	switch(palo){
	
	case picas:		c = 'p';break;
	case treboles:	c = 't';break;
	case diamantes:	c = 'd';break;
	case corazones:	c = 'c';break;

	}

	return c;
}

void repartirNegroRojo(const tMazo mazo,tMazo mazoNegro, tMazo mazoRojo){

	int contador=0,contadorRojo=0,contadorNegro=0;
	tCarta carta;
	tPalo palo;

	while(mazo[contador] != CENTINELA){
	
		carta = mazo[contador];
		palo= darPalo(carta);
		contador++;

		if(palo == picas || palo == treboles){
			mazoNegro[contadorNegro] = carta;
			contadorNegro++;
		}
		else{
			mazoRojo[contadorRojo] = carta;
			contadorRojo++;
		}
	}
	mazoNegro[contadorNegro]=CENTINELA;
	mazoRojo[contadorRojo]=CENTINELA;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas){
	
	int contador=0,contadorBajas=0,contadorAltas=0;
	tCarta carta;
	tNumero numero;

	while(mazo[contador] != CENTINELA){
	
		carta = mazo[contador];
		numero= darNumero(carta);
		contador++;

		if(numero >= 0 && numero <= 6){
			mazoBajas[contadorBajas] = carta;
			contadorBajas++;
		}
		else if(numero >6 && numero <= 12){
			mazoAltas[contadorAltas] = carta;
			contadorAltas++;
		}
	}
	mazoBajas[contadorBajas]=CENTINELA;
	mazoAltas[contadorAltas]=CENTINELA;
}

void repartirIntercalando(const tMazo mazo,int enCuantosMazos,int queMazoPido, tMazo mazoNuevo){
	
	int contadorNuevo=0,contador=0;
	int cuantas;
	cuantas = cuantasEnMazo(mazo);
	tCarta carta;

	for(int i=0;i<cuantas;i=i++){
	
		carta = mazo[i];

		if(i == (queMazoPido-1)+contador){
			mazoNuevo[contadorNuevo] = carta;
			contador = contador + enCuantosMazos;
			contadorNuevo++;
		}
	}
	mazoNuevo[contadorNuevo]= CENTINELA;
}

void trucoTresMontones(){

	int cuantas,queMazo;
	tMazo mazoOriginal, mazo1, mazo2, mazo3,mazoAux;
	crearMazoVacio(mazoAux);

	cargarMazo(mazoOriginal);
	cuantas = cuantasEnMazo(mazoOriginal);

	if (cuantas==21){

		barajarMazo(mazoOriginal);

		repartirIntercalando(mazoOriginal,3,1,mazo1);
		repartirIntercalando(mazoOriginal,3,2,mazo2);
		repartirIntercalando(mazoOriginal,3,3,mazo3);

		for(int i=0;i<2;i++){

			cout<<"Primer mazo:"<<endl;
			escribirMazo(mazo1);

			cout<<endl<<"Segundo mazo:"<<endl;
			escribirMazo(mazo2);

			cout<<endl<<"Tercer mazo:"<<endl;
			escribirMazo(mazo3);

			cout<<endl<<"Elige una carta y memorizala, pero solamente indica en que mazo esta (1,2,3)"<<endl;
			cout<<"En que mazo esta?: ";
			cin>>queMazo; 

			if(queMazo==1){

				unirMazos(mazoAux,mazo2);
				unirMazos(mazoAux,mazo1);
				unirMazos(mazoAux,mazo3);

				repartirIntercalando(mazoAux,3,1,mazo1);
				repartirIntercalando(mazoAux,3,2,mazo2);
				repartirIntercalando(mazoAux,3,3,mazo3);
		
			}

			if(queMazo==2){

				unirMazos(mazoAux,mazo1);
				unirMazos(mazoAux,mazo2);
				unirMazos(mazoAux,mazo3);

				repartirIntercalando(mazoAux,3,1,mazo1);
				repartirIntercalando(mazoAux,3,2,mazo2);
				repartirIntercalando(mazoAux,3,3,mazo3);
		
		
			}

			if(queMazo==3){
		
				unirMazos(mazoAux,mazo1);
				unirMazos(mazoAux,mazo3);
				unirMazos(mazoAux,mazo2);
			
				repartirIntercalando(mazoAux,3,1,mazo1);
				repartirIntercalando(mazoAux,3,2,mazo2);
				repartirIntercalando(mazoAux,3,3,mazo3);
		
		
			}
			crearMazoVacio(mazoAux);
		}
		
			cout<<"Primer mazo:"<<endl;
			escribirMazo(mazo1);

			cout<<endl<<"Segundo mazo:"<<endl;
			escribirMazo(mazo2);

			cout<<endl<<"Tercer mazo:"<<endl;
			escribirMazo(mazo3);

			cout<<endl<<"Elige una carta y memorizala, pero solamente indica en que mazo esta (1,2,3)"<<endl;
			cout<<"En que mazo esta?: ";
			cin>>queMazo; 

		if(queMazo==1){

			unirMazos(mazoAux,mazo2);
			unirMazos(mazoAux,mazo1);
			unirMazos(mazoAux,mazo3);

			cout <<endl<<"Tu carta es:"; 
			escribirCarta(mazoAux[10]);

		}
		else if(queMazo==2){

			unirMazos(mazoAux,mazo1);
			unirMazos(mazoAux,mazo2);
			unirMazos(mazoAux,mazo3);

			cout <<"Tu carta es:";
			escribirCarta(mazoAux[10]);

		}else{

			unirMazos(mazoAux,mazo1);
			unirMazos(mazoAux,mazo3);
			unirMazos(mazoAux,mazo2);
			
			cout <<"Tu carta es:";
			escribirCarta(mazoAux[10]);
		}
	}else
		cout << "El mazo que intentas cargar no es valido para el truco." << endl<<endl;
}

void trucoPosada(){

	tMazo mazoOriginal,mazo1,mazo2,mazo3,mazo4,mazoAux;
	int cuantas;
	
	cargarMazo(mazoOriginal);
	crearMazoVacio(mazoAux);
				
	repartirIntercalando(mazoOriginal,4,1,mazo1);
	repartirIntercalando(mazoOriginal,4,2,mazo2);
	repartirIntercalando(mazoOriginal,4,3,mazo3);
	repartirIntercalando(mazoOriginal,4,4,mazo4);


	cout<<"Primer mazo:"<<endl;
	escribirMazo(mazo1);

	cout<<endl<<"Segundo mazo:"<<endl;
	escribirMazo(mazo2);

	cout<<endl<<"Tercer mazo:"<<endl;
	escribirMazo(mazo3);

	cout << endl << "Cuarto mazo:" << endl;
	escribirMazo(mazo4);


	unirMazos(mazoAux,mazo1);
	unirMazos(mazoAux,mazo2);
	unirMazos(mazoAux,mazo3);
	unirMazos(mazoAux,mazo4);

	cout << "Elige en que carta quieres cortar el mazo: ";
	cin >> cuantas;

	cortarMazo(mazoAux,cuantas);

	repartirIntercalando(mazoAux,4,1,mazo1);
	repartirIntercalando(mazoAux,4,2,mazo2);
	repartirIntercalando(mazoAux,4,3,mazo3);
	repartirIntercalando(mazoAux,4,4,mazo4);

	cout<<"Primer mazo:"<<endl;
	escribirMazo(mazo1);

	cout<<endl<<"Segundo mazo:"<<endl;
	escribirMazo(mazo2);

	cout<<endl<<"Tercer mazo:"<<endl;
	escribirMazo(mazo3);

	cout << endl << "Cuarto mazo:" << endl;
	escribirMazo(mazo4);

}

void opcionCargarMazo(tMazo mazo){

	bool cargar;

	cargar = cargarMazo(mazo);

	if(cargar)
		escribirMazo(mazo);
	else
		cout << "No se ha podido cargar el mazo" << endl;

	cout<<endl;
}

void opcionBarajarMazo(tMazo mazo){
	
	if(mazo[0]!=CENTINELA){//Comprobamos que no nos entre un mazo vacio antes de barajar y mostramos el mensaje al usuario de que está vacío.

		escribirMazo(mazo);
		cout << endl;
		barajarMazo(mazo);
		cout << endl << "El mazo barajado:" << endl << endl;
		escribirMazo(mazo);
		cout << endl;

	}else
		cout << "El mazo esta vacio!Para ciertas opciones necesitas cargar un mazo!" << endl<<endl;

}

void opcionUnirMazo(tMazo mazo){

	tMazo mazo2;
	bool unir;

	cout << "Uniremos el mazo utilizado y otro que cargaremos ahora." << endl;
	cargarMazo(mazo2);

	cout<<"Nuestro mazo interno: " << endl << endl;
	escribirMazo(mazo);

	if(mazo[0]==CENTINELA)
		cout << "Esta vacio." << endl;
	
	cout << endl << "El mazo que le deseamos unir:" << endl << endl;
	escribirMazo(mazo2);
	unir = unirMazos(mazo,mazo2);

	if(unir){//Nos aseguramos que los dos mazos que intentamos unir no sobrepasen el tamaño y si es así , mostramos.

		cout << endl << "El mazo unido:" << endl << endl;
		escribirMazo(mazo);
		cout << endl;
	}
}


void opcionCortarMazo(tMazo mazo){

	int cuantas;
	tMazo mazoDestino;

	if(mazo[0]!=CENTINELA){//Comprobamos que no nos entre un mazo vacío antes de partir el mazo,mostramos el mensaje al usuario.

		cout<< endl;
		escribirMazo(mazo);
		cout << "Por donde quieres cortar el mazo: ";
		cin >> cuantas;
		cout << endl;

		partirMazo(mazo,cuantas,mazoDestino);

		cout << "El mazo cortado:" << endl<<endl;
		escribirMazo(mazo);
		cout << endl;

	}else
		cout << "El mazo esta vacio!Para ciertas opciones necesitas cargar un mazo!" << endl<<endl;

}

void opcionSepararColor(tMazo mazo){

	tMazo mazoNegro,mazoRojo;

	if(mazo[0]!=CENTINELA){//Comprobamos que no nos entre un mazo vacío,ya que al no tener elementos no separariamos nada,mostramos el mensaje al usuario.

		cout << "El mazo entero:" << endl<<endl;
		escribirMazo(mazo);

		repartirNegroRojo(mazo,mazoNegro,mazoRojo);

		cout <<endl<< "El mazo negro: " << endl;
		escribirMazo(mazoNegro);

		cout << endl << "El mazo rojo: " << endl;
		escribirMazo(mazoRojo);
		cout << endl;

	}else
		cout << "El mazo esta vacio!Para ciertas opciones necesitas cargar un mazo!" << endl << endl;
}

void opcionSepararTamaño( tMazo mazo){

	tMazo mazoAltas,mazoBajas;

	if(mazo[0]!=CENTINELA){//Mismo procedimiento que la opción de separar en colores.

		cout << "El mazo entero:" << endl<<endl;
		escribirMazo(mazo);

		repartirNegroRojo(mazo,mazoAltas,mazoBajas);

		cout << endl<< "El mazo de las cartas altas: " << endl;
		escribirMazo(mazoAltas);

		cout << endl << "El mazo de las cartas bajas: " << endl;
		escribirMazo(mazoBajas);
		cout << endl;
	}else
		cout << "El mazo esta vacio!Para ciertas opciones necesitas cargar un mazo!"<<endl<<endl;
}

void opcionIntercalada(tMazo mazo){

	tMazo mazo1,mazo2,mazo3;
	
	if(mazo[0]!=CENTINELA){//Comprobamos si el mazo esta vacío y si es así,mostramos el mensaje al usuario.

		cout << "El mazo original:"<< endl<< endl;
		escribirMazo(mazo);

		repartirIntercalando(mazo,3,1,mazo1);
		repartirIntercalando(mazo,3,2,mazo2);
		repartirIntercalando(mazo,3,3,mazo3);

		cout << endl << "El primero:"<< endl;
		escribirMazo(mazo1);

		cout <<endl<< "El segundo:"<< endl;
		escribirMazo(mazo2);

		cout <<endl<< "El tercero:"<< endl;
		escribirMazo(mazo3);
		cout << endl;

	}else
		cout <<"El mazo esta vacio!Para ciertas opciones necesitas cargar un mazo!"<< endl << endl;
}