#include"Usuario.h"


void inicializar(tUsuario &usuario, string id, string contrasenia){

	usuario.id = id;//crea un nuevo usuario
	usuario.contrasenia = contrasenia;
	usuario.enviados.cont = 0;
	usuario.recibidos.cont = 0;

}

bool validarContrasenia(const tUsuario &usuario, string id, string contrasenia){

	bool correcto = false;

	if (id == usuario.id)
		if (contrasenia == usuario.contrasenia)//comprueba la contraseña del usuario
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

		cargar(usuario.recibidos, archivo);//carga la lista de mensajes recibidos
		cargar(usuario.enviados, archivo);//carga la lista de mensajes enviados
	}

	return ok;
}

void guardar(const tUsuario &usuario, ofstream &archivo){

	archivo << usuario.id << endl;
	archivo << usuario.contrasenia << endl;
	guardar(usuario.recibidos, archivo);
	guardar(usuario.enviados, archivo);

}



	