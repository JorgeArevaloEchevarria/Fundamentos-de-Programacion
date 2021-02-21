#include"Gestor.h"


void inicializar(tGestor &gestor, string dominio){

	gestor.dominio = dominio;
	inicializar(gestor.usuarios);
	gestor.usuarioActivo = -1;

}

bool arrancar(tGestor& gestor, string dominio){

	bool ok;

	inicializar(gestor,dominio);

	ok = cargar(gestor.usuarios,dominio);

	if(ok && gestor.usuarios.cont>0)//si hemos podido cargar los usuarios cargaremos los correos sino ya devolveremos el error
		ok=cargar(gestor.correos,dominio);

	return ok;
}

void apagar(tGestor &gestor){

	guardar(gestor.usuarios,gestor.dominio);
	guardar(gestor.correos,gestor.dominio);
	destruir(gestor.correos);
	destruir(gestor.usuarios);
}

bool crearCuenta(tGestor &gestor){

	string iden,pass;
	tUsuario newUser;
	
	bool encontrado,ok=false,creado=false;
	int pos = 0;

	if (gestor.usuarios.cont < MAX_USUARIOS){
		cout << "Bienvenido al correo" << endl << endl;
		cout << "Introduzca su identificador de correo: ";
		cin >> iden;
		cout << endl << "Introduzca su contrasenia: ";
		cin >> pass;

		iden = iden + ARROBA + gestor.dominio;
	
		encontrado = buscarUsuario(gestor.usuarios,iden,pos);	

		if(encontrado)
			cout << endl << "El identificador que quieres utilizar ya esta en uso." << endl << endl;
		else{
			creado = true;
			inicializar(newUser,iden,pass);
			ok = insertar(gestor.usuarios,newUser);

			if(ok){
				buscarUsuario(gestor.usuarios,newUser.id,pos);
				gestor.usuarioActivo = pos;
			}else{
				cout<< "No se ha podido añadir el usuario." << endl << endl;
				creado = false;
			}
		}
	}
	return creado;

}

bool iniciarSesion(tGestor &gestor){

	string iden,pass;
	bool encontrado,ok=false,iniciado=false;
	int pos=0;

	cout << "Introduzca su identificador de correo: ";
	cin >> iden;
	cout << endl << "Introduzca su contrasenia: ";
	cin >> pass;

	iden = iden + ARROBA + gestor.dominio;

	encontrado = buscarUsuario(gestor.usuarios,iden,pos);

	if(!encontrado){
		cout << endl << "El identificador no se encuentra en la lista." << endl << endl;
		gestor.usuarioActivo = -1;
	}else{
		iniciado = true;
		ok = validarContrasenia(*gestor.usuarios.usuario[pos],iden,pass);

		if(ok)
			gestor.usuarioActivo = pos;
		else{
			gestor.usuarioActivo = -1;
			iniciado = false;
			cout << "Contraseña no valida." << endl << endl;
		}
	}

	return ok;

}

void leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg){

	int pos;
	bool encontrado;

	if(listaReg.cont > 0){

		cout << "Que correo quieres leer: ";
		cin >> pos;
		cout << endl;

		if(pos != 0)
			pos = listaReg.cont - pos;

		if(pos >= 0){
			correoLeido(listaReg,listaReg.listaReg[pos].id);
			encontrado = buscar(gestor.correos,listaReg.listaReg[pos].id,pos);//la pos de registro se modifica y pasa a ser pos de correos(buscar de listaCorreos)
			if(encontrado)
				menuLeerCorreo(gestor,gestor.correos.datoCorreo[pos]);
		}else
			cout << "En esta posicion no se encuentra ningun correo." << endl << endl;
		
	}else
		cout << "No existe ningun correo." << endl << endl;

}

void enviarCorreo(tGestor& gestor, const tCorreo &correo){

	bool ok,encontrado;
	int pos;
	tRegCorreo registroEmisor,registroReceptor;
	stringstream flujo;

	encontrado = buscarUsuario(gestor.usuarios, correo.destinatario,pos);

	if(gestor.correos.cont < MAX_CORREOS && encontrado){
		ok = insertar(gestor.correos,correo);

		if(ok){
			flujo << correo.emisor<< "_" << correo.fecha;
			registroEmisor.id = flujo.str();
			registroEmisor.leido = true;//si lo ha enviado,lo ha leido

			//flujo << correo.destinatario << "_" << correo.fecha;
			registroReceptor.id = flujo.str();
			registroReceptor.leido = false;

			insertar(gestor.usuarios.usuario[gestor.usuarioActivo]->enviados,registroEmisor);	
			insertar(gestor.usuarios.usuario[pos]->recibidos,registroReceptor);
			
		}
	}else
		cout << "No se ha podido enviar el correo" << endl;
}

void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg){

	int pos;
	int posCorreo;

	if(listaReg.cont > 0){
	
		cout << "Que correo quieres borrar: ";
		cin >> pos;
		cout << endl;

		while(pos < 0 || pos > listaReg.cont){

			cout << "Posicion erronea.Que correo quieres borrar: ";
			cin >> pos;
			cout << endl;
		}

		if (pos != 0)
			pos = listaReg.cont - pos; // transformamos a la posicion correcta
			
		if (buscar(gestor.correos, listaReg.listaReg[pos].id, posCorreo)){

			borrar(listaReg,gestor.correos.datoCorreo[posCorreo].id);
			cout << "Correo borrado." << endl << endl;
		}else
			cout << "En esa posicion no se encuentra ningun correo." << endl << endl;
	}else
		cout << "No hay correos en la lista." << endl;
		
}

void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg){
	
	int pos;
	tListaCorreos listaAux;

	inicializar(listaAux,10);

	for(int i = 0;i<listaReg.cont;i++){
		if(!listaReg.listaReg[i].leido){
			correoLeido(listaReg,listaReg.listaReg[i].id);
			buscar(gestor.correos, listaReg.listaReg[i].id, pos);
			insertar(listaAux,gestor.correos.datoCorreo[pos]);
		}
	}
	ordenar_AF(listaAux);

	for(int i = 0; i < listaAux.cont;i++)
		cout << aCadena(listaAux.datoCorreo[i]);

	if(listaAux.cont == 0)
		cout << "No hay mensajes sin leer." << endl << endl;

}

void menuLeerCorreo(tGestor &gestor, const tCorreo &correoOriginal){

	tCorreo correoC;
	int op;

	cout << aCadena(correoOriginal);

	cout << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "Elija una opcion: " << endl;
	cout << " 1- Contestar correo" << endl;
	cout << " 0- Volver a la bandeja" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Introduzca una opcion: ";
	cin >> op;


	switch(op){
	
	case 0:
			break;
	case 1:
			correoContestacion(correoOriginal,correoC,correoOriginal.destinatario);
			enviarCorreo(gestor,correoC);
			break;
	}
}

void menuBandejaEntrada(tGestor &gestor){
		
	string aux;
	int pos;
	tListaRegCorreo recibidos;

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << " ------------------------------ BANDEJA DE ENTRADA --------------------------- " << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "L N EMISOR " << setw(30) << " ASUNTO " << setw(30) << " FECHA " << endl << endl;

	recibidos = gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos;

	if (recibidos.cont > 0) {
		for (int i = recibidos.cont - 1; i >= 0; i--){ 
			aux = recibidos.listaReg[i].id;
			buscar(gestor.correos, aux, pos);
			
			if (!recibidos.listaReg[i].leido)
				cout << "* ";
			else 
				cout << "  ";
				

			cout << recibidos.cont - i << " ";
			cout << obtenerCabecera(gestor.correos.datoCorreo[pos]);
		}
	} 
	else 
		cout << "Bandeja de entrada vacia." << endl;	
}

void menuBandejaSalida(tGestor &gestor){

	tListaRegCorreo enviados;
	string aux;
	int pos;

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << " ------------------------------ BANDEJA DE SALIDA --------------------------- " << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "L N EMISOR " << setw(30) << " ASUNTO " << setw(30) << " FECHA " << endl << endl;

	enviados = gestor.usuarios.usuario[gestor.usuarioActivo]->enviados;

	if (enviados.cont > 0) {
		for (int i = enviados.cont - 1; i >= 0; i--){
			aux = enviados.listaReg[i].id;
			buscar(gestor.correos, aux, pos);

			if (!enviados.listaReg[i].leido)
				cout << "* ";
		
			else 
				cout << "  ";
			
			cout << enviados.cont - i << " ";
			cout << obtenerCabecera(gestor.correos.datoCorreo[pos]);
		}
	} 
	else 
		cout << "Bandeja de salida vacia." << endl;
}

int menuBandeja(tGestor &gestor,bool entrada){

	int opcion;

	cout << "Correo de " << gestor.usuarios.usuario[gestor.usuarioActivo]->id<< endl << endl;

	if(entrada)
		menuBandejaEntrada(gestor);//en caso de entrada muestro la respectiva bandeja
	else
		menuBandejaSalida(gestor);//muestro bandeja de salida

	//Menu 

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Elija una opcion: " << endl
		<< "  1- Leer correo" << endl
		<< "  2- Enviar correo" << endl
		<< "  3- Borrar correo" << endl
		<< "  4- Ver bandeja de ";

	if (entrada == true)
		cout << "salida" << endl;
	
	else 
		cout << "entrada" << endl;
	
	cout << "  5- Lectura rapida de correos sin leer" << endl
		<< "  0- Cerrar sesion" << endl
		<< "-------------------------------------------------------------------------------" << endl;

	// Comprobacion de seleccion de opcion
	do {
		cout << "Introduzca una opcion: ";
		cin >> opcion;

		if (opcion < 0 || opcion > 5)
			cout << "Opcion incorrecta. " << endl;
		
	} while (opcion < 0 || opcion > 5);

	//Mensaje de salida
	if (opcion == 0)
		cout << "Saliendo de " << gestor.usuarios.usuario[gestor.usuarioActivo]->id << endl;
	

	return opcion;
}

void ejecutarMenuBandeja(tGestor &gestor, int &opcion, bool &entrada){

	tCorreo correo;

	switch (opcion) {
	case 0:
		break;
	case 1:
		if (entrada)
			leerCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos);
		else
			leerCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->enviados);
		break;
	case 2:
		correoNuevo(correo, gestor.usuarios.usuario[gestor.usuarioActivo]->id);
		enviarCorreo(gestor, correo);
		break;
	case 3:
		if (entrada)
			borrarCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos);
		else {
			borrarCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->enviados);
		}
		break;
	case 4: 
		if (entrada) {
			entrada = false;
			opcion = menuBandeja(gestor, entrada);
			if (opcion != 0)
				ejecutarMenuBandeja(gestor, opcion, entrada);
		}
		else {
			entrada = true;
			opcion = menuBandeja(gestor, entrada);
			if (opcion != 0)
				ejecutarMenuBandeja(gestor, opcion, entrada);
		}
		break;
	case 5:
		if (entrada)
			lecturaRapida(gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->recibidos);
		else 
			lecturaRapida(gestor, gestor.usuarios.usuario[gestor.usuarioActivo]->enviados);
		
		break;
	}
}