#include"ListaUsuario.h"

void inicializar(tListaUsuarios &usuarios){

	usuarios.cont = 0;

}

bool buscarUsuario(const tListaUsuarios &usuarios, string id, int &posicion){

	int ini = 0, fin, mitad;
	bool encontrado = false;

	fin = usuarios.cont - 1;

	while ((ini <= fin) && !encontrado){

		mitad = (ini + fin) / 2;

		if (id < usuarios.usuario[mitad]->id)
			fin = mitad - 1;

		else if (usuarios.usuario[mitad]->id < id)
			ini = mitad + 1;

		else
			encontrado = true;
	}
	if (encontrado)
		posicion = mitad;
	else
		posicion = ini;

	return encontrado;

}

bool insertar(tListaUsuarios &usuarios, const tUsuario &usuario){

	bool ok = true;

	if (usuarios.cont >= MAX_USUARIOS)
		ok = false;//lista llena

	else{
		int i = usuarios.cont;

		while ((i > 0) && (usuario.id < usuarios.usuario[i - 1]->id)){

			usuarios.usuario[i] = usuarios.usuario[i - 1];
			i--;

		}
		usuarios.usuario[i] = new tUsuario(usuario);
		usuarios.cont++;
	}
	return ok;

}

bool cargar(tListaUsuarios &usuarios, string dominio){

	ifstream archivo;
	string arch;
	stringstream flujo;
	tUsuario user;

	bool ok = true;
	bool correcto = true;

	flujo << dominio << ARCHIVOU;
	arch = flujo.str();


	archivo.open(arch);

	if (!archivo.is_open())
		ok = false;

	else{

		inicializar(usuarios);

		while (usuarios.cont <= MAX_USUARIOS && correcto){

			correcto = cargar(user, archivo);
			if (correcto)
				insertar(usuarios, user);

		}
	}

	archivo.close();
	
	return ok;
}

void guardar(const tListaUsuarios &usuarios, string dominio){

	ofstream archivo;
	string arch;
	stringstream flujo;

	flujo << dominio << ARCHIVOU;
	arch = flujo.str();

	archivo.open(arch);

	for (int i = 0; i < usuarios.cont; i++)
		guardar(*usuarios.usuario[i], archivo);

	archivo << CENTINELA_FINAL;

	archivo.close();

}

void destruir(tListaUsuarios &lista){

	for(int i=0;i<lista.cont;i++){
		
		destruir(lista.usuario[i]->recibidos);
		destruir(lista.usuario[i]->enviados);
		delete lista.usuario[i];
	}
}