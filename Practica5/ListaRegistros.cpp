#include"ListaRegistros.h"


void inicializar(tListaRegCorreo &listaReg, int capInicial){

	listaReg.listaReg = new tRegCorreo[capInicial];
	listaReg.capacidad = capInicial;
	listaReg.cont = 0;
}

void cargar(tListaRegCorreo &listaReg, ifstream& archivo){

	int n;

	archivo >> n;

	inicializar(listaReg,(n+10)-(n%10)); 

	listaReg.cont = n;

	for(int i=0;i<listaReg.cont;i++){

		archivo >> listaReg.listaReg[i].id;
		archivo >> listaReg.listaReg[i].leido;
	}
}

void guardar(const tListaRegCorreo &listaReg, ofstream& archivo){

	archivo << listaReg.cont << endl;

	for(int i=0;i<listaReg.cont;i++){

		archivo << listaReg.listaReg[i].id;
		archivo << "  " << listaReg.listaReg[i].leido;
		archivo << endl;
	}

}

bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro){

	bool ok = true;

	if(listaReg.cont == listaReg.capacidad)
		redimensionar(listaReg);

	listaReg.listaReg[listaReg.cont] = registro;
	listaReg.cont++;

	return ok;

}

int buscar(const tListaRegCorreo &listaReg, string id){

	bool encontrado = false;
	int pos = 0;
	
	while(pos<=listaReg.cont && !encontrado){
	
		if(listaReg.listaReg[pos].id == id)
			encontrado=true;
		else
			pos++;

	}

	if(!encontrado)
		pos=-1;

	return pos;

}

bool borrar(tListaRegCorreo &listaReg, string id){
	
	int pos;
	bool ok;

	pos = buscar(listaReg,id);

	if(pos == -1)
		ok = false;
	else{
		for(int i = pos; i < listaReg.cont;i++)
			listaReg.listaReg[i] = listaReg.listaReg[i+1];
		
		listaReg.cont--;
		ok=true;
	
	}

	return ok;
}

bool correoLeido(tListaRegCorreo &listaReg, string id){

	int pos;
	bool ok;

	pos = buscar(listaReg,id);

	if(pos == -1)
		ok=false;
	else{
	
		listaReg.listaReg[pos].leido = true;
		ok=true;
	}

	return ok;
}

void redimensionar(tListaRegCorreo &reg){
	
	regCorreoPtr nuevoReg = new tRegCorreo[(reg.capacidad*3)/2+1];

	for(int i = 0;i < reg.cont;i++)
		nuevoReg[i] = reg.listaReg[i];
	
	reg.capacidad = (reg.capacidad*3)/2+1;

	delete[] reg.listaReg;

	reg.listaReg = nuevoReg;
}

void destruir(tListaRegCorreo &reg){

	delete[] reg.listaReg;

}