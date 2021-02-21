#include"Usuario.h"


void inicializar(tUsuario &usuario, string id, string contrasenia){

	usuario.id = id;
	usuario.contrasenia = contrasenia;
	inicializar(usuario.enviados,10);
	inicializar(usuario.recibidos,10);

}

bool validarContrasenia(const tUsuario &usuario, string id, string contrasenia){

	bool correcto = false;

	if (id == usuario.id)
		if (contrasenia == usuario.contrasenia)
			correcto = true;
	
	return correcto;
}

bool cargar(tUsuario &usuario, ifstream &archivo){
	
	bool ok=true;
	string primero;

	archivo >> primero;	

	if(primero == CENTINELA_FINAL)
		ok=false;
	else{
		usuario.id = primero;
		archivo >> usuario.contrasenia;

		cargar(usuario.recibidos, archivo);
		cargar(usuario.enviados, archivo);
	}

	return ok;
}

void guardar(const tUsuario &usuario, ofstream &archivo){

	archivo << usuario.id << endl;
	archivo << usuario.contrasenia << endl;
	guardar(usuario.recibidos, archivo);
	guardar(usuario.enviados, archivo);

}

