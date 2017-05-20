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

using namespace std;
using namespace std::tr1;

namespace bblProgII {

	/* ********** IMPLEMENTACION PARTE PÚBLICA ********** */





	/* ********** IMPLEMENTACIÓN PARTE PRIVADA ********** */

	// Busca a un usuario en la lista ordenada de usuarios. Si lo
    // encuentra, devuelve la posición de la lista donde está. Si no,
    // devuelve la posición donde debería estar según el orden de la
    // lista.
    unsigned buscar_usuario(const Usuarios &usuarios, const std::string &user) const {

    	unsigned i = 1;

    	while ((i <= usuarios.num_usuarios) && (usuarios.listado[i] < user)) {

    		i++;

    	} // while ((i <= usuarios.num_usuarios) && (i < usuarios.num_usuarios))

    	return i;

    } // unsigned buscar_usuario() const

    // Inserta un usuario en la lista en la posición indicada
    // PRECONDICIÓN: el usuario cabe en la lista
    // PRECONDICIÓN: la posición es correcta
    void insertar_usuario_pos(Usuarios &usuarios, unsigned pos, const std::string &usuario) {

    	unsigned i = usuarios.num_usuarios;

    	while (pos < i) {								   		// Busca el lugar

    		listado[i] = listado[i - 1];
    		listado --;

    	} // while (pos < i)

    	listado[i] = usuario;									// Añade el usuario
    	listado.num_usuarios ++;

    } // insertar_usuario_pos()

    // Elimina un usuario de una posisición
    // PRECONDICIÓN: la posición es correcta
    void eliminar_usuario_pos(Usuarios &usuarios, unsigned pos) {


    } // eliminar_usuario_pos()


} // Fin namespace bblProgII