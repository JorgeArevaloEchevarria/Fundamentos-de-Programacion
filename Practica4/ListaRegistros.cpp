#include"ListaRegistros.h"


void inicializar(tListaRegCorreo &listaReg){

	listaReg.cont = 0;	//inicializa la lista
}

void cargar(tListaRegCorreo &listaReg, ifstream& archivo){

	inicializar(listaReg); 

	archivo >> listaReg.cont;//lee cuantos registros hay en el archivo

	for(int i=0;i<listaReg.cont;i++){

		archivo >> listaReg.listaReg[i].id;
		archivo >> listaReg.listaReg[i].leido;
	}
}

void guardar(const tListaRegCorreo &listaReg, ofstream& archivo){

	archivo << listaReg.cont << endl;

	for(int i=0;i<listaReg.cont;i++){//guarda los registros q  hay en la lista

		archivo << listaReg.listaReg[i].id;
		archivo << "  " << listaReg.listaReg[i].leido;
		archivo << endl;
	}

}

bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro){

	bool ok;

	if(listaReg.cont >= MAX_REGS)//mira si la lista esta llena
		ok = false;
	else{
		listaReg.listaReg[listaReg.cont] = registro;//añade el registro
		listaReg.cont++;
		ok=true;
	}

	return ok;

}

int buscar(const tListaRegCorreo &listaReg, string id){

	bool encontrado = false;
	int pos = 0;
	
	while(pos<=listaReg.cont && !encontrado){
	
		if(listaReg.listaReg[pos].id == id)//busqueda a traves del id
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
			listaReg.listaReg[i] = listaReg.listaReg[i+1];//borra registros de la lista
		
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
	
		listaReg.listaReg[pos].leido = true;//pone el correo como leido
		ok=true;
	}

	return ok;
}