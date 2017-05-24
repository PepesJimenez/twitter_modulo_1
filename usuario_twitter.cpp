/****************************************************************************
 * Clase UsuarioTwitter
 *
 * Esta clase implementa toda la operativa relativa a un usuario de la red
 * social 'Twitter', permitiendo la gestión de la lista de tweets,
 * usuarios seguidos (following) y usuarios seguidores (followers).
 *
 * Autor:
 * Fecha: Mon Mar 14 10:18:44 2016
 ****************************************************************************/

#include "usuario_twitter.hpp"
#include <iostream>
#include <string>
#include <tr1/array>
#include <fstream>

using namespace std;
using namespace std::tr1;

namespace bblProgII {

	/* ********** IMPLEMENTACION PARTE PÚBLICA ********** */

    // Constructor por defecto
    // Inicializar todos los datos vacíos.
    UsuarioTwitter::UsuarioTwitter() {

        id_usuario = "";

        for (unsigned i = 0; i < MAX_TWEETS; i++) { 

            tweets.listado[i].tweet = "";
            tweets.listado[i].fecha_hora.anyo    = 0;
            tweets.listado[i].fecha_hora.mes     = 0;
            tweets.listado[i].fecha_hora.dia     = 0;
            tweets.listado[i].fecha_hora.hora    = 0;
            tweets.listado[i].fecha_hora.minuto  = 0;
            tweets.listado[i].fecha_hora.segundo = 0;
        
        } // for (unsigned i = 0; i < MAX_TWEETS; i++)

        tweets.num_tweets = 0;

        for (unsigned i = 0; i < MAX_USUARIOS; i++) {

            siguiendo.listado[i] = "";
        
        } // (unsigned i = 0; i < MAX_USUARIOS; i++)

        siguiendo.num_usuarios = 0;

        for (unsigned i = 0; i < MAX_USUARIOS; i++) {

            seguidores.listado[i] = "";
        
        } // (unsigned i = 0; i < MAX_USUARIOS; i++)
       
        seguidores.num_usuarios = 0;

    } // UsuarioTwitter::UsuarioTwitter()


    // Constructor extendido.
    // Inicializa el idenfificador de usuario con el 'id' que se pasa
    // como parámetro. Las listas de usuarios y tweets están
    // vacías.
    UsuarioTwitter::UsuarioTwitter(const std::string &id) {

        id_usuario = id;

        for (unsigned i = 0; i < MAX_TWEETS; i++) { 
 
            tweets.listado[i].tweet = "";
            tweets.listado[i].fecha_hora.anyo    = 0;
            tweets.listado[i].fecha_hora.mes     = 0;
            tweets.listado[i].fecha_hora.dia     = 0;
            tweets.listado[i].fecha_hora.hora    = 0;
            tweets.listado[i].fecha_hora.minuto  = 0;
            tweets.listado[i].fecha_hora.segundo = 0;
 
        } // (unsigned i = 0; i < MAX_TWEETS; i++)

        tweets.num_tweets = 0;

        for (unsigned i = 0; i < MAX_USUARIOS; i++) {

            siguiendo.listado[i] = "";
        
        } // (unsigned i = 0; i < MAX_USUARIOS; i++)

        siguiendo.num_usuarios = 0;

        for (unsigned i = 0; i < MAX_USUARIOS; i++) {

            seguidores.listado[i] = "";
        
        } // (unsigned i = 0; i < MAX_USUARIOS; i++)

        seguidores.num_usuarios = 0;

    } // UsuarioTwitter::UsuarioTwitter(const std::string &id)


    // Constructor de copia
    UsuarioTwitter::UsuarioTwitter(const UsuarioTwitter &otro_usuario) {

        // id_usuario
        id_usuario = otro_usuario.id_usuario;
    
        // Seguidores y siguiendo
        seguidores = otro_usuario.seguidores;
        siguiendo = otro_usuario.siguiendo;

        //Tweets
        tweets = otro_usuario.tweets;

    } // UsuarioTwitter::UsuarioTwitter(const UsuarioTwitter &otro_usuario)

/*
    // Operador de asignación (¡¡¡OPCIONAL!!!)
    UsuarioTwitter & operator=(const UsuarioTwitter &otro_usuario);
*/

    // Destructor de la clase
    UsuarioTwitter::~UsuarioTwitter() {

    } // UsuarioTwitter::~UsuarioTwitter()



    /* ---------- METODOS DE CONSULTA ---------- */

    // Devuelve el idenficador del usuario
    std::string UsuarioTwitter::obtener_id() const{

        return id_usuario;

    } // std::string UsuarioTwitter::obtener_id()


    // Devuelve la lista de usuarios que le siguen
    void UsuarioTwitter::obtener_seguidores(Usuarios &lista_seg) const {

        lista_seg.num_usuarios = 0;

        while (lista_seg.num_usuarios < seguidores.num_usuarios) {

            lista_seg.listado[lista_seg.num_usuarios] = seguidores.listado[lista_seg.num_usuarios];
            lista_seg.num_usuarios ++;

        } // (lista_seg.num_usuarios < seguidores.num_usuarios)

    } // void UsuarioTwitter::obtener_seguidores(Usuarios &lista_seg) const


    // Devuelve la lista de usuarios a los que sigue
    void UsuarioTwitter::obtener_siguiendo(Usuarios &lista_sig) const {

        lista_sig.num_usuarios = 0;

        while (lista_sig.num_usuarios < siguiendo.num_usuarios) {

            lista_sig.listado[lista_sig.num_usuarios] = siguiendo.listado[lista_sig.num_usuarios];
            lista_sig.num_usuarios ++;

        } // (lista_sig.num_usuarios < siguiendo.num_usuarios)

    } // void UsuarioTwitter::obtener_siguiendo(Usuarios &lista_sig) const


    // Devuelve la lista de tweets
    void UsuarioTwitter::obtener_tweets(Tweets &lista_tweets) const {

        lista_tweets.num_tweets = 0;

        while (lista_tweets.num_tweets < tweets.num_tweets) {

            lista_tweets.listado[lista_tweets.num_tweets] = tweets.listado[lista_tweets.num_tweets];
            lista_tweets.num_tweets ++;

        } // (lista_tweets.num_tweets < tweets.num_tweets)

    } // void UsuarioTwitter::obtener_tweets(Tweets &lista_tweets) const


    // Indica si un usuario es seguidor de este usuario
    bool UsuarioTwitter::me_sigue(const std::string &otro_usuario) const {

        unsigned pos = buscar_usuario(seguidores, otro_usuario);

        if (seguidores.listado[pos] == otro_usuario) {

            return true;

        } // if (seguidores.listado[pos] == otro_usuario)

        else {

            return false;
        
        } // else: if (seguidores.listado[pos] == otro_usuario)

    } // bool UsuarioTwitter::me_sigue(const std::string &otro_usuario) const


    // Indica si este usuario sigue a otro
    bool UsuarioTwitter::estoy_siguiendo(const std::string &otro_usuario) const {

        unsigned pos = buscar_usuario(siguiendo, otro_usuario);

        if (siguiendo.listado[pos] == otro_usuario) {

            return true;
        
        } // if (siguiendo.listado[pos] == otro_usuario)

        else {

            return false;

        } // else: if (siguiendo.listado[pos] == otro_usuario)

    } // bool UsuarioTwitter::estoy_siguiendo(const std::string &otro_usuario) const


    // Devuelve el numero de seguidores
    unsigned UsuarioTwitter::num_seguidores() const {

        return seguidores.num_usuarios;

    } // unsigned UsuarioTwitter::num_seguidores() const


    // Devuelve el numero de usuarios a los que sigo
    unsigned UsuarioTwitter::num_siguiendo() const {

        return siguiendo.num_usuarios;
    
    } // unsigned UsuarioTwitter::num_siguiendo() const


    // Devuelve el numero de tweets
    unsigned UsuarioTwitter::num_tweets() const {

        return tweets.num_tweets;

    } // unsigned UsuarioTwitter::num_tweets () const


    // Imprime por pantalla la lista de seguidores
    // Si num_imprime == 0, imprime todos los seguidores. Si no,
    // se imprime el numero de seguidores que se indica.
    // PRECONDICION: num_imprime <= num_seguidores
    void UsuarioTwitter::imprimir_seguidores(unsigned num_imprime) const {

        unsigned impr = 0;

        if (num_imprime == 0) {

            impr = seguidores.num_usuarios;

        } // if (num_imprime == 0)

        else {

            impr = num_imprime;

        } // else: if (num_imprime == 0)


        cout << "Seguidores de: " << id_usuario << ": " << endl;

        for (unsigned i = 0; i < impr; i++) {

            cout << '\t' << i + 1 << ". " << seguidores.listado[i] << endl;

        } // for (unsigned i = 0; i < impr; i++)


    } // void UsuarioTwitter::imprimir_seguidores(unsigned num_imprime) const


    // Imprime por pantalla la lista de usuarios a los que sigue
    // Si num_imprime == 0, imprime todos los usuarios a los que sigue.
    // Si no, imprime el numero de usuarios que se indica.
    // PRECONDICION; num_imprime <= num_siguiendo
    void UsuarioTwitter::imprimir_siguiendo(unsigned num_imprime) const {

        unsigned impr = 0;

        if (num_imprime == 0) {

            impr = siguiendo.num_usuarios;

        } // if (num_imprime == 0)

        else {

            impr = num_imprime;

        } // else: if (num_imprime == 0)

        cout << id_usuario << " sigue a: " << endl;

        for (unsigned i = 0; i < impr; i++) {

            cout << '\t' << i + 1 << ". " << siguiendo.listado[i] << endl;

        } // for (unsigned i = 0; i < impr; i++)

    } // void UsuarioTwitter::imprimir_siguiendo(unsigned num_imprime) const


    // Imprime por pantalla la lista de tweets.
    // Si num_imprime == 0, imprime todos los tweets del usuario.
    // Si no, imrpime el numero de tweets que se indica.
    // PRECONDICION: num_imprime <= num_tweets
    void UsuarioTwitter::imprimir_tweets(unsigned num_imprime) const {

        unsigned impr;

        if (num_imprime == 0) {

            impr = tweets.num_tweets;

        } // if (num_imprime == 0)

        else {

            impr = num_imprime;

        } // else: if (num_imprime == 0)

        cout << "Tweets de " << id_usuario << ": " << endl;

        for (unsigned i = 0; i < impr; i++) {

            cout << '\t' << i + 1 << tweets.listado[i].tweet << endl
                 << '\t' << tweets.listado[i].fecha_hora.hora << ":"
                         << tweets.listado[i].fecha_hora.minuto << ":"
                         << tweets.listado[i].fecha_hora.segundo << " "
                         << tweets.listado[i].fecha_hora.dia << "/"
                         << tweets.listado[i].fecha_hora.mes << "/"
                         << tweets.listado[i].fecha_hora.anyo << "\n\n";

        } // for (unsigned i = 0; i < num_imprime; i++)

    } // void UsuarioTwitter::imprimir_tweets(unsigned num_imprime) const


    // Guarda en fichero la lista de seguidores
    void UsuarioTwitter::guardar_seguidores(const std::string &nom_fic, Resultado &res) const {

        ofstream f_ent;
        f_ent.open(nom_fic);

        if (f_ent.fail()) {

            cout << "Error al abrir el archivo." << endl;
            res = FIC_ERROR;

        } // if (f_ent.fail())

        else {

            for (unsigned i = 0; i < seguidores.num_usuarios; i++) {

                if (i == (seguidores.num_usuarios - 1)) {

                	f_ent << seguidores.listado[i];

                } // if (i == (seguidores.num_usuarios - 1))

                else {

                	f_ent << seguidores.listado[i] << endl;

                } // else: if (i == (seguidores.num_usuarios - 1))


            } // for (unsigned i = 0; i < seguidores.num_usuarios; i++)

            res = OK;

        } // else: if (f_ent.fail())

        f_ent.close();

    } // void UsuarioTwitter::guardar_seguidores(const std::string &nom_fic, Resultado &res) const


    // Guarda en fichero la lista de usuarios a los que sigue
    void UsuarioTwitter::guardar_siguiendo(const std::string &nom_fic, Resultado &res) const{

        ofstream f_ent;
        f_ent.open(nom_fic);

        if (f_ent.fail()) {

            cout << "Error al abrir el archivo." << endl;
            res = FIC_ERROR;

        } // if (f_ent.fail())

        else {

            for (unsigned i = 0; i < siguiendo.num_usuarios; i++) {

                if (i == (seguidores.num_usuarios - 1)) {

                	f_ent << siguiendo.listado[i];

                } // if (i == (siguiendo.num_usuarios - 1))

                else {

                	f_ent << siguiendo.listado[i] << endl;

                } // else: if (i == (siguiendo.num_usuarios - 1))


            } // for (unsigned i = 0; i < siguiendo.num_usuarios; i++)

            res = OK;

        } // else: if (f_ent.fail())

        f_ent.close();

    } // void UsuarioTwitter::guardar_siguiendo(const std::string &nom_fic, Resultado &res) const


    // Guarda en fichero los tweets del usuario
    void UsuarioTwitter::guardar_tweets(const std::string &nom_fic, Resultado &res) const {

        ofstream f_ent;
        f_ent.open(nom_fic);

        if (f_ent.fail()) {

            cout << "Error al abrir el archivo." << endl;
            res = FIC_ERROR;

        } // if (f_ent.fail())
        else {

            for (unsigned i = 0; i < tweets.num_tweets; i++) {

                f_ent << tweets.listado[i].fecha_hora.dia << " "
                	  << tweets.listado[i].fecha_hora.mes << " "
                	  << tweets.listado[i].fecha_hora.anyo << " "
                	  << tweets.listado[i].fecha_hora.hora << " "
                	  << tweets.listado[i].fecha_hora.minuto << " "
                	  << tweets.listado[i].fecha_hora.segundo << " "

                	  << tweets.listado[i].tweet;

                if (i == (tweets.num_tweets - 1)) {

                	f_ent << tweets.listado[i].tweet;

                } // if (i == (tweets.num_tweets - 1))

                else {

                	f_ent << tweets.listado[i].fecha_hora.dia << " "
                		  << tweets.listado[i].fecha_hora.mes << " "
               	 		  << tweets.listado[i].fecha_hora.anyo << " "
               	 		  << tweets.listado[i].fecha_hora.hora << " "
                		  << tweets.listado[i].fecha_hora.minuto << " "
               			  << tweets.listado[i].fecha_hora.segundo << " "

                		  << tweets.listado[i].tweet

                		  << endl;

                } // else: if (i == (tweets.num_tweets - 1))

            } // for (unsigned i = 0; i < tweets.num_tweets; i++)

            res = OK;

        } // else: if (f_ent.fail())

        f_ent.close();

    } // void UsuarioTwitter::guardar_tweets(const std::string &nom_fic, Resultado &res) const


    // Guarda en fichero las listas de siguiendo, seguidores y tweets
    void UsuarioTwitter::guardar_todo(const std::string &nom_fic_seguidores,
                        const std::string &nom_fic_siguiendo, 
                        const std::string &nom_fic_tweets,
                        Resultado &res_seguidores,
                        Resultado &res_siguiendo,
                        Resultado &res_tweets) const {

        guardar_seguidores(nom_fic_seguidores, res_seguidores);
        guardar_siguiendo(nom_fic_siguiendo, res_siguiendo);
        guardar_tweets(nom_fic_tweets, res_tweets);

    } // void UsuarioTwitter::guardar_todo(const std::string &nom_fic_seguidores,
      //                    const std::string &nom_fic_siguiendo, 
      //                    const std::string &nom_fic_tweets,
      //                    Resultado &res_seguidores,
      //                    Resultado &res_siguiendo,
      //                    Resultado &res_tweets) const



    /* ---------- METODOS DE ACTUALIZACION ---------- */

    // Modifica el identificador del usuario
    void UsuarioTwitter::establecer_id(const std::string &nuevo_id) {

        id_usuario = nuevo_id;

    } // void UsuarioTwitter::establecer_id(const std::string &nuevo_id)


    // Inserta un seguidor en la lista de seguidores.
    // Si el nuevo seguidor no existe, se inserta de manera ordenada
    // (orden lexicografico creciente) y se devuelve 'OK' a traves de 
    // 'res'. Si ya existe el seguidor, no se inserta y se devuelve 
    // 'YA_EXISTE' a traves de 'res'. Si no, si la lista de seguidores
    // esta llena, se devuelve 'LISTA_LLENA' a traves de 'res'.
    void UsuarioTwitter::nuevo_seguidor(const std::string &nuevo, Resultado &res) {

        if (seguidores.num_usuarios < MAX_USUARIOS) {

            unsigned pos = buscar_usuario(seguidores, nuevo);

            if (seguidores.listado[pos] == nuevo) {

                // Existe usuario
                res = YA_EXISTE;

            } // if (seguidores.lisato[pos] == nuevo)

            else {

                // No existe, se añade a la lista
                insertar_usuario_pos(seguidores, pos, nuevo);
                res = OK;

            } // else: if (seguidores.lisato[pos] == nuevo)

        } // if (seguidores. num_usuarios < MAX_USUARIOS)

        else {

            // Lista completa
            res = LISTA_LLENA;

        } // else: if (seguidores. num_usuarios < MAX_USUARIOS)

    } // void UsuarioTwitter::nuevo_seguidor(const std::string &nuevo, Resultado &res)


    // Inserta un usuario en la lista de usuarios a los que sigue.
    // SI el nuevo usuario no existe, se inserta de maneda ordenada
    // (orden lexicografico creciente) y se devuelve 'OK' a traves de 
    // 'res'. Si ya existe el usuario, no se inserta y se devuelve 
    // 'YA_EXISTE' a traves de 'res'. Si no, si la lista de siguiendo
    // esta llena, se devuelve 'LISTA_LLENA' a traves de 'res'.
    void UsuarioTwitter::nuevo_siguiendo(const std::string &nuevo, Resultado &res) {

        if (siguiendo.num_usuarios < MAX_USUARIOS) {

            unsigned pos = buscar_usuario(siguiendo, nuevo);

            if (siguiendo.listado[pos] == nuevo) {

                // Existe usuario
                res = YA_EXISTE;

            } // if (siguiendo.listado[pos] == nuevo)

            else {

                // No existe, se añade a la lista
                insertar_usuario_pos(siguiendo, pos, nuevo);
                res = OK;

            } // else: if (siguiendo.listado[pos] == nuevo)

        } // if (siguiendo.num_usuarios < MAX_USUARIOS)

        else {

            // Lista llena
            res = LISTA_LLENA;

        } // else: if (siguiendo.num_usuarios < MAX_USUARIOS)

    } // void UsuarioTwitter::nuevo_siguiendo(const std::string &nuevo, Resultado &res)


    // Inserta un nuevo tweet al final de la lista de tweets. 
    // Si la lista de tweets esta llena, se devuelve 'LISTA_LLENA' 
    // a traves de 'res'. Si no, se devuelve 'OK'. La longitud maxima
    // del tweet es 140 caracteres, por lo que si el texto del tweet 
    // tiene mas de 140 caracteres, los caracteres sobrantes por el final
    // se eliminaran.
    void UsuarioTwitter::nuevo_tweet(const Tweet &nuevo, Resultado &res) {

        if (tweets.num_tweets < MAX_TWEETS) {

            // Recortamos el tweet si pasa los 140 caracteres
            if (140 < (nuevo.tweet).size()) {

                tweets.listado[tweets.num_tweets].tweet = (nuevo.tweet).substr(0, 140);

            } // if (140 < (unsigned ((nuevo.tweet).size())))

            else {

                tweets.listado[tweets.num_tweets].tweet = nuevo.tweet;

            } // else: if (140 < (unsigned ((nuevo.tweet).size())))

            tweets.listado[tweets.num_tweets].fecha_hora = nuevo.fecha_hora;
            tweets.num_tweets ++;
            res = OK;

        } // if (tweets.num_tweets < MAX_TWEETS)

        else {

            res = LISTA_LLENA;

        } // else: if (tweets.num_tweets < MAX_TWEETS)

    }


    // Elimina a un usuario de la lista de seguidores.
    // Si el usuario existe, se elimina y se devuelve 'OK' a traves de 
    // 'res'. Si no existe, se devuelve 'NO_EXISTE'
    void UsuarioTwitter::eliminar_seguidor(const std::string &usuario, Resultado &res) {

        unsigned pos = buscar_usuario(seguidores, usuario);

        if (seguidores.listado[pos] == usuario) {

            eliminar_usuario_pos(seguidores, pos);
            res = OK;

        } // if (seguidores.listado[pos] == usuario)

        else {

            res = NO_EXISTE;

        } // else: if (seguidores.listado[pos] == usuario)

    } // void UsuarioTwitter::eliminar_seguidor(const std::string &usuario, Resultado &res)


    // Elimina a un usuario de la lista de usuarios a los que sigue.
    // Si el usuario existe, se elimina y se devuelve 'OK' a traves de 
    // 'res'. Si no existe el usuario, se devuelve 'NO_EXISTE' a traves
    // de 'res'
    void UsuarioTwitter::eliminar_siguiendo(const std::string &usuario, Resultado &res) {

        unsigned pos = buscar_usuario(siguiendo, usuario);

        if (siguiendo.listado[pos] == usuario) {

            eliminar_usuario_pos(siguiendo, pos);
            res = OK;

        } // if (siguiendo.listado[pos] == usuario)

        else {

            res = NO_EXISTE;

        } // else: if (siguiendo.listado[pos] == usuario)

    } // void UsuarioTwitter::eliminar_siguiendo(const std::string &usuario, Resultado &res)
    

    // Carga desde fichero la lista de seguidores eliminando los 
    // seguidores actuales. Si el fichero se ha leido correctamente
    // y los usuarios caben en la lista, se devuelve 'OK' a traves 
    // de 'res'. En caso contrario, se devuelve 'FIC_ERROR' o 
    // 'LISTA_LLENA' respectivamente (aunque se inserten solo los 
    // usuarios que caben en la lista).
    void UsuarioTwitter::cargar_seguidores(const std::string &nom_fic, Resultado &res) {

    	ifstream flujo_fic;
    	flujo_fic.open(nom_fic);
    	
    	if (!flujo_fic.fail()) {				// ¿Error al abrir el archivo?

    		res = OK;
    		seguidores.num_usuarios = 0;

    		if (!flujo_fic.eof()) {				// ¿Archivo vacio?

    			while (!flujo_fic.eof() && (seguidores.num_usuarios < MAX_USUARIOS)) {

    				getline(flujo_fic, seguidores.listado[seguidores.num_usuarios]);
    				seguidores.num_usuarios ++;

    			} // while (!flujo_fic.eof() && (seguidores.num_usuarios < MAX_USUARIOS))

    			if (!flujo_fic.eof() && (seguidores.num_usuarios == MAX_USUARIOS)) {

    				res = LISTA_LLENA;

    			} // if (!flujo_fic.eof() && (seguidores.num_usuarios == MAX_USUARIOS))

    		} // if (!flujo_fic.eof())

    	} // if (flujo_fic.fail())

    	else {

    		res = FIC_ERROR;

    	} // else: if (flujo_fic.fail())

    	flujo_fic.close();

    } // void UsuarioTwitter::cargar_seguidores(const std::string &nom_fic, Resultado &res)


    // Carga desde fichero la lista de usuarios a los que se sigue,
    // eliminando lo usuarios actuales. Si el fichero se ha leido 
    // correctamente y los usuarios caben en la lista, se devuelve
    // 'OK' a traves de 'res'. En caso contrario, se devuelve 
    // 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertanç
    // solo los usuarios que caben en la lista).
    void UsuarioTwitter::cargar_siguiendo(const std::string &nom_fic, Resultado &res) {

    	ifstream flujo_fic;
    	flujo_fic.open(nom_fic);

    	if (!flujo_fic.fail()) {						// ¿Error al abrir el archivo?

    		res = OK;
    		siguiendo.num_usuarios = 0;

    		if (!flujo_fic.eof()) {						// ¿Archivo vacio?

    			while (!flujo_fic.eof() && (siguiendo.num_usuarios < MAX_USUARIOS)) {

    				getline(flujo_fic, siguiendo.listado[siguiendo.num_usuarios]);
    				siguiendo.num_usuarios ++;

    			} // while (!flujo_fic.eof() && (siguiendo.num_usuarios < MAX_USUARIOS))

    			if (!flujo_fic.eof() && (siguiendo.num_usuarios == MAX_USUARIOS)) {

    				res = LISTA_LLENA;

    			} // if (!flujo_fic.eof() && (siguiendo.num_usuarios == MAX_USUARIOS))

    		} // if (!flujo_fic.eof())

    	} // if (!flujo_fic.fail())

    	else {

    		res = FIC_ERROR;

    	} // else: if (!flujo_fic.fail())

    	flujo_fic.close();

    } // void UsuarioTwitter::cargar_siguiendo(const std::string &nim_fic, Resultado &res)


    // Carga desde fichero la lista de tweets del usuario,
    // eliminando los tweets actuales. Si el fichero se ha leido
    // correctamente y los tweets caben en la lista, se devuelve
    // 'OK' a traves de 'res'. En caso contrario, se devuelve 
    // 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
    // solo los tweets qeu caben en la lista).
    void UsuarioTwitter::cargar_tweets(const std::string &nom_fic, Resultado &res) {

    	ifstream flujo_fic;
    	flujo_fic.open(nom_fic);

    	if (!flujo_fic.fail()) {						// ¿Error al abrir el archivo?

    		res = OK;
    		tweets.num_tweets = 0;

    		if (!flujo_fic.eof()) {						// ¿Archivo vacio?

    			while (!flujo_fic.eof() && (tweets.num_tweets < MAX_TWEETS)) {

    				flujo_fic >> tweets.listado[tweets.num_tweets].fecha_hora.dia;
    				flujo_fic >> tweets.listado[tweets.num_tweets].fecha_hora.mes;
    				flujo_fic >> tweets.listado[tweets.num_tweets].fecha_hora.anyo;
    				flujo_fic >> tweets.listado[tweets.num_tweets].fecha_hora.hora;
    				flujo_fic >> tweets.listado[tweets.num_tweets].fecha_hora.minuto;
    				flujo_fic >> tweets.listado[tweets.num_tweets].fecha_hora.segundo;
    				getline(flujo_fic, tweets.listado[tweets.num_tweets].tweet);

    				tweets.num_tweets ++;

    			} // while (!flujo_fic.eof() && (tweets.num_tweets < MAX_TWEETS))

    			if (!flujo_fic.eof() && (tweets.num_tweets == MAX_TWEETS)) {

    				res = LISTA_LLENA;

    			} // if (!flujo_fic.eof() && (tweets.num_tweets == MAX_TWEETS))

    		} // if (!flujo_fic.eof())

    	} // f (!flujo_fic.fail())

    	else {

    		res = FIC_ERROR;

    	} // else: if (!flujo_fic.fail())

    	flujo_fic.close();

    } // void UsuarioTwitter::cargar_tweets(const std::string &nom_fic, Resultado &res)


    // Carga desde gichero las listas de usuarios y tweets. Si cada fichero
    // se ha leido correctamente y los usuarios/tweets caben en la lista 
    // correspondiente, se devuelve 'OK' a traves del parametro 'res_*'
    // correspondiente. En caso contrario, se devuelve 'FIC_ERROR' o 
    // 'LISTA_LLENA', respectivamente (aunque se insertan solo los 
    // usuarios/tweets que caben en la lista correspondiente).
    void UsuarioTwitter::cargar_todo(const std::string &nom_fic_seguidores,
    					const std::string &nom_fic_siguiendo,
    					const std::string &nom_fic_tweets,
    					Resultado &res_seguidores,
    					Resultado &res_siguiendo,
    					Resultado &res_tweets) {

    	cargar_seguidores(nom_fic_seguidores, res_seguidores);
    	cargar_siguiendo(nom_fic_siguiendo, res_siguiendo);
    	cargar_tweets(nom_fic_tweets, res_tweets);

    } // void UsuarioTwitter::cargar_todo(const std::string &nom_fic_seguidores,
      //     			const std::string &nom_fic_siguiendo,
      //				cosnt std::string &nom_fic_tweets,
      //    			Resultado &res_seguidores,
      //				Resultado &res_siguiendo,
      //				Resultado &res_tweets)



	/* ********** IMPLEMENTACIÓN PARTE PRIVADA ********** */

	// Busca a un usuario en la lista ordenada de usuarios. Si lo
    // encuentra, devuelve la posición de la lista donde está. Si no,
    // devuelve la posición donde debería estar según el orden de la
    // lista.
    unsigned UsuarioTwitter::buscar_usuario(const Usuarios &usuarios, const std::string &user) const {

    	unsigned i = 0;

    	while ((usuarios.listado[i] < user) && (i < usuarios.num_usuarios)) {

    		i++;

    	} // while ((usuarios.listado[i] < user) && (i <= usuarios.num_usuarios))

    	return i;

    } // unsigned buscar_usuario() const

    // Inserta un usuario en la lista en la posición indicada
    // PRECONDICIÓN: el usuario cabe en la lista
    // PRECONDICIÓN: la posición es correcta
    void UsuarioTwitter::insertar_usuario_pos(Usuarios &usuarios, unsigned pos, const std::string &usuario) {

    	unsigned i = usuarios.num_usuarios;

    	while (pos < i) {								   		// Busca el lugar

    		usuarios.listado[i] = usuarios.listado[i - 1];
    		i --;

    	} // while (pos < i)

    	usuarios.listado[i] = usuario;							// Añade el usuario
    	usuarios.num_usuarios ++;

    } // insertar_usuario_pos()

    // Elimina un usuario de una posisición
    // PRECONDICIÓN: la posición es correcta
    void UsuarioTwitter::eliminar_usuario_pos(Usuarios &usuarios, unsigned pos) {

    	unsigned i = pos;

    	while (i < usuarios.num_usuarios) {

    		usuarios.listado[i] = usuarios.listado[i + 1];
    		i++;

    	} // while ()

    	usuarios.num_usuarios --;

    } // eliminar_usuario_pos()

} // Fin namespace bblProgII