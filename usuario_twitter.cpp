/****************************************************************************
 *
 * Implementacióbn clase UsuarioTwitter
 *
 * Esta clase implementa toda la operativa relativa a un usuario de la red
 * social 'Twitter', permitiendo la gestión de la lista de tweets,
 * usuarios seguidos (following) y usuarios seguidores (followers).
 *
 * Autor: Jose A. Jimenez
 * Fecha: Mon Mar 14 10:18:44 2016
 *
 * ---------------------------------------------------------------------
 *
 *
 *	NOTAS:
 *
 *		1. Suponemos datos en ficheros siempre correctos
 *		2. id_usuario siempre de una sola palabra. ej: carlos_babbage
 * *
 *
 ****************************************************************************/


#include "usuario_twitter.hpp"

#include <iostream>
#include <string>
#include <tr1/array>
#include <fstream>

using namespace std;
using namespace std::tr1;



namespace bblProgII{


/*
 * ------------------------- Implementación de la parte privada del modulo -------------------------------------------------------------
*/

    //------------------------------------------------------------------
    // MÉTODOS PRIVADOS:
    //
    // Busca a un usuario en la lista ordenada de usuarios. Si lo
    // encuentra, devuelve la posición de la lista donde está. Si no,
    // devuelve la posición donde debería estar según el orden de la
    // lista.
 	// EDIT: --------------- BUSQUEDA POR ORDEN LEXICOFRAFICO CRECIENTE-------
	// Devuelve: (0,100] si NO existe, [1001,1100] si existe
    unsigned UsuarioTwitter::buscar_usuario(const Usuarios &usuarios, const std::string &user) const{

        unsigned pos;
        unsigned i = 0;

        while (user < usuarios.listado[i] && i < usuarios.num_usuarios){

        	if (user != ""){		// Usuario encontrado (se comprueba en la siguiente ronda del bucle)

        		pos = i + 1002;       //Posicion como num_usuario

        	} else {

        		// No existe usuario, devuelve posicion de donde deberia ir
        		pos = i + 1;
        	}

        	i ++;
        }

        return pos;     // Devuelve posicion en num_usuarios (1, 2, 3...), no en usuarios.listado (0, 1, 2...)
    }

    // Inserta un usuario en la lista en la posición indicada
    // PRECONDICIÓN: el usuario cabe en la lista
    // PRECONDICIÓN: la posición es correcta
    // EDIT: ------------------- MOVER AL RESTO DE USUARIOS ----------------
    void UsuarioTwitter::insertar_usuario_pos(Usuarios &usuarios, unsigned pos, const std::string &usuario){

        //pos en orden de registro
        pos --;     // Si pos = 5 --> pos = 4

        // Si hay un usuario en su sitio, lo movemos a el y a los que hay despues
        if (pos <= usuarios.num_usuarios){      

        	for (unsigned i = 0; i < (usuarios.num_usuarios - pos); i ++){

        		// Movemos al ultimo usuario una posicion a la derecha del array
        		usuarios.listado[usuarios.num_usuarios - i] = usuarios.listado[usuarios.num_usuarios - i - 1];
        	}
        }

       	//Insertamos el usuario
        usuarios.listado[pos] = usuario;		        
    }

    // Elimina un usuario de una posición y, si es necesario, 
    // mueve al resto de usuarios para hacer correcta la lista
    // PRECONDICIÓN: la posición es correcta
    // EDIT: ------------------- MOVER AL RESO DE USUARIOS ----------------------
    void UsuarioTwitter::eliminar_usuario_pos(Usuarios &usuarios, unsigned pos){

    	//pos en orden de registro
    	pos --; 		// Si pos = 5 --> pos = 4;

   		//Eliminamos usuario
   		usuarios.listado[pos] = "";

   		//Cerramos el hueco
   		if (pos < usuarios.num_usuarios){

   		   for (unsigned i = 0; i < (usuarios.num_usuarios - pos); i++){

   		       usuarios.listado[pos + i] = usuarios.listado[pos + i + 1];
   		   }
        }
   	}



/*
 * ------------------------- Implementación de la parte pública del modulo -------------------------------------------------------------
*/


    // Constructor por defecto
    // Inicializar todos los datos vacíos.                  // ¿¿¿¿¿¿¿¿¿¿¿¿ ESTA BIEN ???????????
    UsuarioTwitter::UsuarioTwitter(){

        // ID usuario
        id_usuario = "";
        
        // Tweets

        tweets.num_tweets = 0;
        for (unsigned i = 0; i < MAX_TWEETS; i++){

            tweets.listado[i].tweet = "";

            tweets.listado[i].fecha_hora.anyo = 0;
            tweets.listado[i].fecha_hora.mes = 0;
            tweets.listado[i].fecha_hora.dia = 0;
            tweets.listado[i].fecha_hora.hora = 0,
            tweets.listado[i].fecha_hora.minuto = 0;
            tweets.listado[i].fecha_hora.segundo = 0;
        }

        // Lista de siguiendo y seguidores

        siguiendo.num_usuarios = 0;
        seguidores.num_usuarios = 0;

        for (unsigned i = 0; i < MAX_USUARIOS; i++){

            siguiendo.listado[i] = "";
            seguidores.listado[i] = "";
        }
    }                              

    // Constructor extendido.
    // Inicializa el idenfificador de usuario con el 'id' que se pasa
    // como parámetro. Las listas de usuarios y tweets están
    // vacías.
    UsuarioTwitter::UsuarioTwitter(const std::string &id){

        // ID usuario
        id_usuario = id;
        
        // Tweets
        tweets.num_tweets = 0;
        for (unsigned i = 0; i < MAX_TWEETS; i++){

            tweets.listado[i].tweet = "";

            tweets.listado[i].fecha_hora.anyo = 0;
            tweets.listado[i].fecha_hora.mes = 0;
            tweets.listado[i].fecha_hora.dia = 0;
            tweets.listado[i].fecha_hora.hora = 0,
            tweets.listado[i].fecha_hora.minuto = 0;
            tweets.listado[i].fecha_hora.segundo = 0;
        }

        // Lista de siguiendo y seguidores

        seguidores.num_usuarios = 0;
        siguiendo.num_usuarios = 0;

        for (unsigned i = 0; i < MAX_USUARIOS; i++){

            siguiendo.listado[i] = "";
            seguidores.listado[i] = "";
        }

    }

    // Constructor de copia
    UsuarioTwitter::UsuarioTwitter(const UsuarioTwitter &otro_usuario){     // Esta bien? (Otros lados, aparece al reves)

        // Copia de ID usuario
        id_usuario = otro_usuario.id_usuario;
        
        // Copia de tweets
        for (unsigned i = 0; i < otro_usuario.tweets.num_tweets; i++){

            tweets.listado[i].tweet = otro_usuario.tweets.listado[i].tweet;

            tweets.listado[i].fecha_hora.anyo = otro_usuario.tweets.listado[i].fecha_hora.anyo;
            tweets.listado[i].fecha_hora.mes = otro_usuario.tweets.listado[i].fecha_hora.mes;
            tweets.listado[i].fecha_hora.dia = otro_usuario.tweets.listado[i].fecha_hora.dia;
            tweets.listado[i].fecha_hora.hora = otro_usuario.tweets.listado[i].fecha_hora.hora;
            tweets.listado[i].fecha_hora.minuto = otro_usuario.tweets.listado[i].fecha_hora.minuto;
            tweets.listado[i].fecha_hora.segundo = otro_usuario.tweets.listado[i].fecha_hora.segundo;
        }

        tweets.num_tweets = otro_usuario.tweets.num_tweets;

        // Copia de listas siguiendo y seguidores
        for (unsigned i = 0; i < otro_usuario.siguiendo.num_usuarios || i < otro_usuario.seguidores.num_usuarios; i++){

            siguiendo.listado[i] = otro_usuario.siguiendo.listado[i];
            seguidores.listado[i] = otro_usuario.seguidores.listado[i];
        }
    }

    /* 
    // Operador de asignación (¡¡¡OPCIONAL!!!)
    UsuarioTwitter::UsuarioTwitter & operator=(const UsuarioTwitter &otro_usuario); 
    */

    // Destructor de la clase
    UsuarioTwitter::~UsuarioTwitter(){

        // ID usuario
        id_usuario = "";
        
        // Tweets
        for (unsigned i = 0; i < tweets.num_tweets; i++){

            tweets.listado[i].tweet = "";

            tweets.listado[i].fecha_hora.anyo = 0;
            tweets.listado[i].fecha_hora.mes = 0;
            tweets.listado[i].fecha_hora.dia = 0;
            tweets.listado[i].fecha_hora.hora = 0,
            tweets.listado[i].fecha_hora.minuto = 0;
            tweets.listado[i].fecha_hora.segundo = 0;
        }

        tweets.num_tweets = 0;

        // Lista de siguiendo y seguidores
        for (unsigned i = 0; i < siguiendo.num_usuarios || i < seguidores.num_usuarios; i++){

            siguiendo.listado[i] = "";
            seguidores.listado[i] = "";
        }

        siguiendo.num_usuarios = 0;
        seguidores.num_usuarios = 0;
    }

    //------------------------------------------------------------------
    // MÉTODOS DE CONSULTA

    // Devuelve el idenficador del usuario
    std::string UsuarioTwitter::obtener_id() const{

        return id_usuario;
    }

    // Devuelve la lista de seguidores
    void UsuarioTwitter::obtener_seguidores(Usuarios &lista_seg) const{

        for (unsigned i = 0; i < seguidores.num_usuarios; i ++){

        	lista_seg.listado[i] = seguidores.listado[i];
        }

        /*
        // Se igualan los arrays. NO SE PUEDE, FALTA IMPLEMENTAR OPERATOR=
        lista_seg = seguidores.listado;
        */
    }

    // Devuelve la lista de usuarios a los que se sigue
    void UsuarioTwitter::obtener_siguiendo(Usuarios &lista_sig) const{

        for (unsigned i = 0; i < siguiendo.num_usuarios; i ++){

            lista_sig.listado[i] = siguiendo.listado[i];
        }

        /*
        // Se igualan los arrays. NO SE PUEDE, FALTA IMPLEMENTAR OPERATOR=
        lista_sig = siguiendo.listado;
        */
    }

    // Devuelve la lista de tweets del usuario
    void UsuarioTwitter::obtener_tweets(Tweets &lista_tweets) const{

        for (unsigned i = 0; i < tweets.num_tweets; i ++){

            lista_tweets.listado[i] = tweets.listado[i];
        }

        /*
        // Se igualan los arrays. NO SE PUEDE, FALTA IMPLEMENTAR OPERATOR=
        lista_tweets = tweets.listado;
        */
    }

    // Indica si un determinado usuario es seguidor de este usuario
    bool UsuarioTwitter::me_sigue(const std::string &otro_usuario) const{

        bool encontrado = true;

        unsigned pos;
        pos = buscar_usuario(seguidores, otro_usuario);

        if (1 < pos && pos < 100){

            //Usuario no es seguidor
            encontrado  = false;
        }

        return encontrado;
    }

    // Indica si este usuario está siguiendo a otro
    bool UsuarioTwitter::estoy_siguiendo(const std::string &otro_usuario) const{
        
        bool encontrado = true;

        unsigned pos;
        pos = buscar_usuario(siguiendo, otro_usuario);

        if (1 < pos && pos < 100){

            //No sigue a usuario
            encontrado  = false;
        }

        return encontrado;
    }

    // Devuelve el número de seguidores
    unsigned UsuarioTwitter::num_seguidores() const{

        return seguidores.num_usuarios;
    }

    // Devuelve el número de usuarios a los que se sigue
    unsigned UsuarioTwitter::num_siguiendo() const{

        return siguiendo.num_usuarios;
    }

    // Devuelve el número de tweets del usuario
    unsigned UsuarioTwitter::num_tweets() const{

        return tweets.num_tweets;
    }

    // Imprime por pantalla la lista de seguidores
    // Si num_imprime == 0, imprime todos los seguidores. Si no,
    // se imprime el número de seguidores que se indica.
    // PRECONDICIÓN: num_imprime <= num_seguidores
    void UsuarioTwitter::imprimir_seguidores(unsigned num_imprime) const{

        unsigned impresiones;

        if (num_imprime == 0){

            impresiones = seguidores.num_usuarios;

        } else {

            impresiones = num_imprime;
        }

        //Imprimimos los seguidores por pantalla

        cout << "Seguidores de " << obtener_id() << ": " << endl;

        for (unsigned i = 0; i < impresiones; i++){

            cout << "\t" << i + 1 << ". " << seguidores.listado[i] << endl;
        }
    }

    // Imprime por pantalla la lista de usuarios a los que sigue
    // Si num_imprime == 0, imprime todos los usuarios a los que sigue.
    // Si no, imprime el número de usuarios que se indica.
    // PRECONDICIÓN: num_imprime <= num_siguiendo
    void UsuarioTwitter::imprimir_siguiendo(unsigned num_imprime) const{

        unsigned impresiones;

        if (num_imprime == 0){

            impresiones = siguiendo.num_usuarios;

        } else {

            impresiones = num_imprime;
        }

        //Imprimimos los seguidores por pantalla

        cout << "Siguiendo de " << obtener_id() << ": " << endl;
        
        for (unsigned i = 0; i < impresiones; i++){

            cout << "\t" << i + 1 << ". " << siguiendo.listado[i] << endl;
        }       
    }

    // Imprime por pantalla la lista de tweets
    // Si num_imprime == 0, imprime todos los tweets del usuario.
    // Si no, imprime el número de tweets que se indica.
    // PRECONDICIÓN: num_imprime <= num_tweets
    void UsuarioTwitter::imprimir_tweets(unsigned num_imprime) const{

        unsigned impresiones;

        if (num_imprime == 0){

            impresiones = MAX_USUARIOS;

        } else {

            impresiones = num_imprime;
        }

        //Imprimimos los tweets por pantalla

        cout << "Tweets de " << obtener_id() << ": " << endl;

        for (unsigned i = 0; i < impresiones; i++){

            cout << '\t' << i + 1 << tweets.listado[i].tweet << endl
                 << '\t' << tweets.listado[i].fecha_hora.hora << ":"
                         << tweets.listado[i].fecha_hora.minuto << ":"
                         << tweets.listado[i].fecha_hora.segundo << " "
                         << tweets.listado[i].fecha_hora.dia << "/"
                         << tweets.listado[i].fecha_hora.mes << "/"
                         << tweets.listado[i].fecha_hora.anyo << "\n\n";
        }
    }

    // Guarda en fichero la lista de seguidores
    void UsuarioTwitter::guardar_seguidores(const std::string &nom_fic, Resultado &res) const{

    	ofstream f_ent;
    	f_ent.open(nom_fic);		// Abrimos el fichero, eliminando cualquier dato que existiese antes

    	if (f_ent.fail()){

    		cout << "Error al abrir el archivo. " << endl;
    		res = FIC_ERROR;
    	
    	} else {

    		// Metemos en el archivo la lista de seguidores por lineas
    		for (unsigned i = 0; i < seguidores.num_usuarios; i++){

    			f_ent << seguidores.listado[i] << endl;
    		}

    		res = OK;
    	}

    	f_ent.close();		// Cerramos el fichero
    }

    // Guarda en fichero la lista de usuarios a los que sigue
    void UsuarioTwitter::guardar_siguiendo(const std::string &nom_fic, Resultado &res) const{

    	ofstream f_ent;
    	f_ent.open(nom_fic);		// Abrimos el fichero, eliminando cualquier dato que existiese antes

    	if (f_ent.fail()){

    		cout << "Error al abrir el archivo. " << endl;
    		res = FIC_ERROR;
    	
    	} else {

    		// Metemos en el archivo la lista de siguiendo por lineas
    		for (unsigned i = 0; i < siguiendo.num_usuarios; i++){

    			f_ent << siguiendo.listado[i] << endl;
    		}

    		res = OK;    		
    	}

    	f_ent.close();		// Cerramos el fichero
    }

    // Guarda en fichero los tweets del usuario
    void UsuarioTwitter::guardar_tweets(const std::string &nom_fic, Resultado &res) const{

    	ofstream f_ent;
    	f_ent.open(nom_fic);		// Abrimos el fichero, eliminando cualquier dato que existiese antes

    	if (f_ent.fail()){

    		cout << "Error al abrir el archivo. " << endl;
    		res = FIC_ERROR;
    	
    	} else {

    		// Metemos en el archivo la lista de tweets por lineas
    		for (unsigned i = 0; i < tweets.num_tweets; i++){

    			//Fecha
    			f_ent << tweets.listado[i].fecha_hora.dia << " "
    			<< tweets.listado[i].fecha_hora.mes << " "
    			<< tweets.listado[i].fecha_hora.anyo << " "
    			<< tweets.listado[i].fecha_hora.hora << " "
    			<< tweets.listado[i].fecha_hora.minuto << " "
    			<< tweets.listado[i].fecha_hora.segundo << " "
    			//Tweet
    			<< tweets.listado[i].tweet

    			<< endl;
    		}

    		res = OK;    		
    	}

    	f_ent.close();		// Cerramos el fichero   	
    }

    // Guarda en fichero las listas de usuarios  y tweets
    void UsuarioTwitter::guardar_todo(const std::string &nom_fic_seguidores,
                      const std::string &nom_fic_siguiendo,
                      const std::string &nom_fic_tweets,
                      Resultado &res_seguidores,
                      Resultado &res_siguiendo,
                      Resultado &res_tweets) const{

    	// Guardar seguidores
    	guardar_seguidores(nom_fic_seguidores, res_seguidores);
    	// Guardar siguiendo
    	guardar_siguiendo(nom_fic_siguiendo, res_siguiendo);
    	// Guardar tweets
    	guardar_tweets(nom_fic_tweets, res_tweets);
    }

    //------------------------------------------------------------------
    // MÉTODOS DE ACTUALIZACIÓN

    // Modifica el identificador del usuario
    void UsuarioTwitter::establecer_id(const std::string &nuevo_id){

    	id_usuario = nuevo_id;
    }

    // Inserta un seguidor en la lista de seguidores.
    // Si el nuevo seguidor no existe, se inserta de manera ordenada
    // (orden lexicográfico creciente) y se devuelve 'OK' a través de
    // 'res'. Si ya existe el seguidor, no se inserta y se devuelve
    // 'YA_EXISTE' a través de 'res'. Si no, si la lista de seguidores está
    // llena, se devuelve 'LISTA_LLENA' a través de 'res'.
    void UsuarioTwitter::nuevo_seguidor(const std::string &nuevo, Resultado &res){
    	
    	if (seguidores.num_usuarios < MAX_USUARIOS){	

    		unsigned pos;
    		pos = buscar_usuario(seguidores, nuevo);

    		if (1 <= pos && pos <= 100){		//No existe el usuario

    			insertar_usuario_pos(seguidores, pos, nuevo);
    			res = OK;

    		} else {		// Existe el usuario

    			res = YA_EXISTE;
    		}

    	} else {		// Lista llena

    		res = LISTA_LLENA;
    	}
    }

    // Inserta un usuario en la lista de usuarios a los que sigue.
    // Si el nuevo usuario no existe, se inserta de manera ordenada
    // (orden lexicográfico creciente) y se devuelve 'OK' a través de
    // 'res'. Si ya existe el usuario, no se inserta y se devuelve
    // 'YA_EXISTE' a través de 'res'. Si no, si la lista de siguiendo está
    // llena, se devuelve 'LISTA_LLENA' a través de 'res'.
    void UsuarioTwitter::nuevo_siguiendo(const std::string &nuevo, Resultado &res){

    	if (siguiendo.num_usuarios < MAX_USUARIOS){	

    		unsigned pos;
    		pos = buscar_usuario(siguiendo, nuevo);

    		if (1 <= pos && pos <= 100){		//No existe el usuario

    			insertar_usuario_pos(siguiendo, pos, nuevo);
    			res = OK;

    		} else {		// Existe el usuario

    			res = YA_EXISTE;
    		}

    	} else {		// Lista llena

    		res = LISTA_LLENA;
    	}
    }

    // Inserta un nuevo tweet al final de la lista de tweets. Si la lista de
    // tweets está llena, se devuelve 'LISTA_LLENA' a través de 'res'. Si no,
    // se devuelve 'OK'. La longitud máxima del tweet es 140 caracteres, por
    // lo que si el texto del tweet tiene más de 140 caracteres, los
    // caracteres sobrantes por el final se eliminarán.
    void UsuarioTwitter::nuevo_tweet(const Tweet &nuevo, Resultado &res){

    	if (tweets.num_tweets < MAX_TWEETS){	

    		//Aseguramos que el tweet sea de 140 caracteres
    		if ((unsigned((nuevo.tweet).size())) > 140){

                string recorte;

                // Recortamos el tweet
    			recorte = (nuevo.tweet).substr(0, 140);
    		}

    		//Metemos el tweet en la lista
    		tweets.listado[tweets.num_tweets] = nuevo;

    		res = OK;

    	} else {		// Lista llena

    		res = LISTA_LLENA;
    	}
    }

    // Elimina a un usuario de la lista de seguidores
    // Si el usuario existe, se elimina y se devuelve 'OK' a través de
    // 'res'. Si no existe el usuario, se devuelve 'NO_EXISTE' a través
    // de 'res'.
    void UsuarioTwitter::eliminar_seguidor(const std::string &usuario, Resultado &res){

    	//Comprobamos que el usuario está en la lista
    	unsigned pos;
    	pos = buscar_usuario(seguidores, usuario);

    	if (1001 <= pos && pos <= 1100){		// Existe usuario

    		eliminar_usuario_pos(seguidores, pos);

    		res = OK;

    	} else {		// No existe

    		res = NO_EXISTE;
    	}
    }

    // Elimina a un usuario de la lista de usuarios a los que sigue
    // Si el usuario existe, se elimina y se devuelve 'OK' a través de
    // 'res'. Si no existe el usuario, se devuelve 'NO_EXISTE' a través
    // de 'res'.
    void UsuarioTwitter::eliminar_siguiendo(const std::string &usuario, Resultado &res){

    	//Comprobamos que el usuario esta en la lista
    	unsigned pos;
    	pos = buscar_usuario(siguiendo, usuario);

    	if (1001 <= pos && pos <= 1100){

    		eliminar_usuario_pos(siguiendo, pos);

    		res = OK;
    	
    	} else {

    		res = NO_EXISTE;
    	}
    }

    // Carga desde fichero la lista de seguidores,
    // eliminando los seguidores actuales. Si el fichero se ha leído
    // correctamente y los usuarios caben en la lista, se devuelve
    // 'OK' a través de 'res'. En caso contrario, se devuelve
    // 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
    // solo los usuarios que caben en la lista).
    void UsuarioTwitter::cargar_seguidores(const std::string &nom_fic, Resultado &res){		// COMPROBAR OPTIMIZACION

    	ifstream f_ent;
        f_ent.open(nom_fic);     // Abrimos el fichero de seguidores
        
        if (f_ent.fail()){

        	res = FIC_ERROR;

            cout << "Error al abrir el archivo de seguidores" << endl;

        } else {

            unsigned i = 0;
            bool fin_lista = false;

            res = OK; 		//Predeterminamos para ahorrar acciones en bucle

            //Mete seguidores mientras que no llegue el fin del fichero y haya huecos
            while (!f_ent.eof() && !fin_lista){

            	if (i < seguidores.num_usuarios){

                	f_ent >> seguidores.listado[i];
                	seguidores.num_usuarios = i + 1;

                	i++;

                } else {

                	res = LISTA_LLENA;
                	fin_lista = true; 		// Salida del bucle
                }
            }
        }

        f_ent.close();          // Cerramos el fichero de seguidores
    }

    // Carga desde fichero la lista de usuarios a los que se sigue,
    // eliminando los usuarios seguidos actuales. Si el fichero se ha leído
    // correctamente y los usuarios caben en la lista, se devuelve
    // 'OK' a través de 'res'. En caso contrario, se devuelve
    // 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
    // solo los usuarios que caben en la lista).
    void UsuarioTwitter::cargar_siguiendo(const std::string &nom_fic, Resultado &res){		// COMPROBAR OPTIMIZACION

    	ifstream f_ent;
        f_ent.open(nom_fic);     // Abrimos el fichero de siguiendo
        
        if (f_ent.fail()){

        	res = FIC_ERROR;

            cout << "Error al abrir el archivo de siguiendo" << endl;

        } else {

            unsigned i = 0;
            bool fin_lista = false;

            res = OK; 		//Predeterminamos para ahorrar acciones en bucle

            //Mete siguiendo mientras que no llegue el fin del fichero y haya huecos
            while (!f_ent.eof() && !fin_lista){

            	if (i < siguiendo.num_usuarios){

                	f_ent >> siguiendo.listado[i];
                	siguiendo.num_usuarios = i + 1;

                	i++;

                } else {

                	res = LISTA_LLENA;
                	fin_lista = true; 		// Salida del bucle
                }
            }
        }

        f_ent.close();          // Cerramos el fichero de siguiendo
    }

    // Carga desde fichero la lista de tweets del usuario,
    // eliminando los tweets actuales. Si el fichero se ha leído
    // correctamente y los tweets caben en la lista, se devuelve
    // 'OK' a través de 'res'. En caso contrario, se devuelve
    // 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
    // solo los tweets que caben en la lista).
    void UsuarioTwitter::cargar_tweets(const std::string &nom_fic, Resultado &res){ 	// COMPROBAR **********************

    	ifstream f_ent;
        f_ent.open(nom_fic);     // Abrimos el fichero de tweets
        
        if (f_ent.fail()){

            cout << "Error al abrir el archivo de tweets" << endl;

        } else {

            unsigned i = 0;
            bool fin_lista = false;

            res = OK; 		//Predeterminamos para ahorrar acciones en bucle

            // Obtenemos los tweets
            while (!f_ent.eof() && !fin_lista){

            	if (i < tweets.num_tweets){

                	// dia mes anyo hora minuto segundo
                	f_ent >> tweets.listado[i].fecha_hora.dia;
                	f_ent >> tweets.listado[i].fecha_hora.mes;
                	f_ent >> tweets.listado[i].fecha_hora.anyo;
                	f_ent >> tweets.listado[i].fecha_hora.hora;
                	f_ent >> tweets.listado[i].fecha_hora.minuto;
                	f_ent >> tweets.listado[i].fecha_hora.segundo;
                	// Tweet
                	getline(f_ent, tweets.listado[i].tweet);

                	i++;

                } else{

                	res = LISTA_LLENA;
                	fin_lista = true; 		// Salida del bucle
                } 
            }
        }

        f_ent.close();          // Cerramos el fichero de tweets
    }


    // Carga desde fichero las listas de usuarios y tweets. Si cada fichero se ha leído
    // correctamente y los usuarios/tweets caben en la lista correspondiente, se devuelve
    // 'OK' a través del parámetro 'res_*' correspondiente. En caso contrario, se devuelve
    // 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
    // solo los usuarios/tweets que caben en la lista correspondiente).
    void UsuarioTwitter::cargar_todo(const std::string &nom_fic_seguidores,
                     const std::string &nom_fic_siguiendo,
                     const std::string &nom_fic_tweets,
                     Resultado & res_seguidores,
                     Resultado & res_siguiendo,
                     Resultado & res_tweets){

    	cargar_seguidores(nom_fic_seguidores, res_seguidores);
    	cargar_siguiendo(nom_fic_siguiendo, res_siguiendo);
    	cargar_tweets(nom_fic_tweets, res_tweets);
    }

};       // FIN namespace bblProgII