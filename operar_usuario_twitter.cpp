#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "usuario_twitter.hpp"

using namespace std;
using namespace bblProgII;

// Escribe el menú de opciones, lee la opción por teclado y la devuelve
char menu();

// Pulsar una tecla para continuar
void Seguir();

// Escribir resultado de operación por pantalla
void escribir_resultado(const Resultado res);


int main() {

  /*ALUMNO: declarar el objeto ada_lovelace, con identificador "ada_lovelace"*/
  UsuarioTwitter ada_lovelace("ada_lovelace");

  string id_usuario;
  Tweet tweet;
  char opcion, seguir;
  Resultado res_seg, res_sig, res_twt;
  time_t tSac; // instante actual
  tm tms;



  do {
    opcion = menu();

    switch (opcion) {

    case 'a':

      // cout << "Usuario con id: @" << /*ALUMNO: obtener id de ada_lovelace ...*/ << endl;
      cout << "Usuario con id: @" << ada_lovelace.obtener_id() << endl;
      Seguir();
      break;


    case 'b': 
      
      cout << "Introduzca el nombre del usuario a buscar: ";
      cin >> id_usuario; cin.ignore();
      // if (/*ALUMNO: id_usuario sigue a ada_lovelace*/)
      if (ada_lovelace.me_sigue(id_usuario)) {
        cout << "El usuario @" << id_usuario << " me está siguiendo." << endl;
      } else {
        cout << "El usuario @" << id_usuario << " NO me está siguiendo." << endl;
      }
      Seguir();
      break;


    case 'c': 

      cout << "Introduzca el nombre del usuario a buscar: ";
      cin >> id_usuario; cin.ignore();
      // if (/*ALUMNO: ada_lovelace sigue a id_usuario*/)
      if (ada_lovelace.estoy_siguiendo(id_usuario)) {
        cout << "Estoy siguiendo al usuario @" << id_usuario << endl;
      } else {
        cout << "NO estoy siguiendo al usuario @" << id_usuario << endl;
      }
      Seguir();
      break;


    case 'd': 

      cout << "ESTADÍSTICAS DEL USUARIO:" << endl;
      // cout << "Seguidores: " << /*ALUMNO: obtener seguidores de ada_lovelace*/ << endl;
      cout << "Seguidores: " << ada_lovelace.num_seguidores() << endl;
      // cout << "Siguiendo: " << /*ALUMNO: obtener usuarios a los que sigue ada_lovelace*/ << endl;
      cout << "Siguiendo: " << ada_lovelace.num_siguiendo() << endl;
      // cout << "Tweets: " << /*ALUMNO: obtener cuántos tweets tiene ada_lovelace*/ << endl;
      cout << "Tweets: " << ada_lovelace.num_tweets() << endl;
      Seguir();
      break;


    case 'e': 

      unsigned num_usuarios;
      // cout << "Tiene actualmente " << /*ALUMNO: obtener cuántos seguidores tiene ada_lovelace*/ << " seguidores "
      //      << " y está siguiendo a " << /*ALUMNO: obtener a cuántos sigue ada_lovelace*/ << " usuarios " << endl;
      cout << "Tiene actualmente " << ada_lovelace.num_seguidores() << " seguidores "
           << " y está siguiendo a " << ada_lovelace.num_siguiendo() << " usuarios " << endl;
      cout << "¿Número de usuarios a imprimir de ambas listas (0 -> todos): ";
      cin >> num_usuarios;
      cout << "Su lista de seguidores: " << endl;

      /*ALUMNO: escribir por pantalla los seguidores de ada_lovelace*/
      ada_lovelace.imprimir_seguidores(num_usuarios);

      cout << endl;
      cout << "Su lista de usuarios a los que sigue: " << endl;

      /*ALUMNO: escribir por pantalla la lista de usuarios a los que sigue ada_lovelace*/
      ada_lovelace.imprimir_siguiendo(num_usuarios);

      cout << endl;
      Seguir();
      break;


    case 'f': 

      unsigned num_tweets;
      // cout << "Tiene actualmente " << /*ALUMNO: consultar cuántos tweets tiene ada_lovelace*/ << " tweets..." << endl;
      cout << "Tiene actualmente " << ada_lovelace.num_tweets() << " tweets..." << endl;
      cout << "¿Número de tweets a imprimir (0 -> todos): ";
      cin >> num_tweets;
      cout << "Estos son sus últimos tweets:" << endl;

      /*ALUMNO: escribir por pantalla los tweets de ada_lovelace*/
      ada_lovelace.imprimir_tweets(num_tweets);

      Seguir(); 
      break;

    case 'g': 

      cout << "Se guardarán todos los datos a fichero..." << endl;
      cout << "¡Atención! Los datos de los ficheros se sobreescribirán." << endl;
      do {
        cout << "¿Desea continuar (s/n)?: ";
        cin.get(seguir); cin.ignore();
      } while (tolower(seguir) != 's' && tolower(seguir) != 'n');
      if (seguir == 's') {

        // id_usuario = /*ALUMNO: obtener el id de ada_lovelace*/;
        id_usuario = ada_lovelace.obtener_id();
        
        /*ALUMNO...*/
        cout << "Guardando la lista de seguidores..." << endl;

        /*ALUMNO: guardar en ada_lovelace.seg los seguidores de ada_lovelace*/
        ada_lovelace.guardar_seguidores("ada_lovelace.seg", res_seg);
        escribir_resultado(res_seg);

        cout << "Guardando la lista de usuarios a los que sigo..." << endl;
        
        /*ALUMNO: guardar en ada_lovelace.sig los seguidores a los que sigue ada_lovelace*/
        ada_lovelace.guardar_siguiendo("ada_lovelace.sig", res_sig);
        escribir_resultado(res_sig);

        cout << "Guardando la lista de tweets..." << endl;
        
        /*ALUMNO: guardar en ada_lovelace.twt los tweets de ada_lovelace*/
        ada_lovelace.guardar_tweets("ada_lovelace.twt", res_twt);
        escribir_resultado(res_twt);

      }
      Seguir();
      break;
    

    case 'h': 

      cout << "Introduzca el nuevo id del usuario: ";
      cin >> id_usuario; cin.ignore();

      /*ALUMNO: modificar el id de ada_lovelace*/
      ada_lovelace.establecer_id(id_usuario);

      // cout << "Nuevo id del usuario: " << /*ALUMNO: consultar el id de ada_lovelace*/ << endl;
      cout << "Nuevo id del usuario: " << ada_lovelace.obtener_id() << endl;

      Seguir();
      break;


    case 'i': 

      cout << "Introduzca un tweet (máximo 140 caracteres): ";
      getline(cin, tweet.tweet);

      // PARA OBTENER LA HORA DEL ORDENADOR: --------
      tSac = time(NULL); // instante actual
      tms = *localtime(&tSac);
      tweet.fecha_hora.dia = unsigned(tms.tm_mday);
      tweet.fecha_hora.mes = unsigned(tms.tm_mon + 1);
      tweet.fecha_hora.anyo = unsigned(tms.tm_year + 1900);
      tweet.fecha_hora.hora = unsigned(tms.tm_hour);
      tweet.fecha_hora.minuto = unsigned(tms.tm_min);
      tweet.fecha_hora.segundo = unsigned(tms.tm_sec);
      //----------------------------------------------

      /*ALUMNO: insertar un nuevo tweet en la lista de tweets de ada_lovelace*/
      ada_lovelace.nuevo_tweet(tweet, res_twt);

      escribir_resultado(res_twt);
      Seguir();
      break;


    case 'j': 

      cout << "Introduzca el nombre del usuario seguidor: ";
      cin >> id_usuario; cin.ignore();

      /*ALUMNO: insertar un nuevo seguidor en la lista de seguidores de ada_lovelace*/
      ada_lovelace.nuevo_seguidor(id_usuario, res_seg);

      escribir_resultado(res_seg);
      Seguir();
      break;


    case 'k': 

      cout << "Introduzca el nombre del usuario a seguir: ";
      cin >> id_usuario;  cin.ignore();

      /*ALUMNO: insertar un nuevo usuario en la lista de usuarios a los que sigue ada_lovelace*/
      ada_lovelace.nuevo_siguiendo(id_usuario, res_sig);

      escribir_resultado(res_sig);
      Seguir();
      break;


    case 'l': 

      cout << "Introzca el nombre del usuario seguidor a eliminar: ";
      cin >> id_usuario;  cin.ignore();

      /*ALUMNO: eliminar id_usuario de la lista de seguidores de ada_lovelace*/
      ada_lovelace.eliminar_seguidor(id_usuario, res_seg);

      escribir_resultado(res_seg);
      Seguir();
      break;


    case 'm': 

      cout << "Introzca el nombre del usuario a eliminar de la lista de usuarios a los que sigo: ";
      cin >> id_usuario;  cin.ignore();

      /*ALUMNO: eliminar id_usuario de la lista de siguiendo de ada_lovelace*/
      ada_lovelace.eliminar_siguiendo(id_usuario, res_sig);

      escribir_resultado(res_sig);
      Seguir();
      break;


    case 'n': 

      cout << "Se cargarán todos los datos desde fichero..." << endl;
      cout << "¡Atención! Sus datos actuales se borrarán." << endl;
      do {
        cout << "¿Desea continuar (s/n)?: ";
        cin.get(seguir); cin.ignore();
      } while (tolower(seguir) != 's' && tolower(seguir) != 'n');
      if (seguir == 's') {

        // id_usuario = /*ALUMNO: obtener id de ada_lovelace*/;
        id_usuario = ada_lovelace.obtener_id();

        /*ALUMNO: cargar todo (seguidores, siguiendo y tweets) de
        sus respectivos ficheros: ada_lovelace.seg, ada_lovelace.sig
        y ada_lovelace.twt*/

        cout << "Cargando la lista de seguidores..." << endl;
        ada_lovelace.cargar_seguidores("ada_lovelace.seg", res_seg);
        escribir_resultado(res_seg);
        cout << "Cargando la lista de usuarios a los que sigo..." << endl;
        ada_lovelace.cargar_siguiendo("ada_lovelace.sig", res_sig);
        escribir_resultado(res_sig);
        cout << "Cargando la lista de tweets..." << endl;
        ada_lovelace.cargar_tweets("ada_lovelace.twt", res_twt);
        escribir_resultado(res_twt);
      }
      Seguir();
      break;
    } // switch (opcion)
  } while (opcion != 'x');
}

char menu() {
  char opcion;

  system("clear"); // Limpiamos la pantalla

  do {
    cout << "MENÚ DE OPCIONES (elija una opción y pulse <enter>):" << endl << endl;
    cout << "a -> Obtener id del usuario" << endl;
    cout << "b -> Consultar si un usuario me sigue" << endl;
    cout << "c -> Consultar si estoy siguiendo a un usuario" << endl;
    cout << "d -> Imprimir mis estadísticas (seguidores, siguiendo, etc.)" << endl;
    cout << "e -> Imprimir mi lista de seguidores y usuarios a los que sigo" << endl;
    cout << "f -> Imprimir mi lista de tweets" << endl;
    cout << "g -> Guardar todos mis datos en fichero (seguidores, tweets, etc.)" << endl;
    cout << "h -> Modificar el id de mi usuario" << endl;
    cout << "i -> Insertar un nuevo tweet" << endl;
    cout << "j -> Insertar un nuevo seguidor en mi lista de seguidores" << endl;
    cout << "k -> Insertar un nuevo usuario en mi lista de usuarios a los que sigo" << endl;
    cout << "l -> Eliminar un usuario de mi lista de seguidores" << endl;
    cout << "m -> Eliminar un usuario de mi lista de usuarios a los que sigo" << endl;
    cout << "n -> Cargar todos los datos desde disco (se borran los actuales)" << endl;
    cout << "x -> SALIR DEL PROGRAMA" << endl;

    cin.get(opcion); cin.ignore(); opcion = char(tolower(int(opcion)));
  } while ((opcion < 'a' || opcion > 'n') && (opcion != 'x'));

  return opcion;
}

void Seguir() {
  char tecla;

  cout << endl << "Pulse una tecla y <enter> para continuar..." << endl;
  cin >> tecla; cin.ignore();
}


void escribir_resultado(const Resultado res) {
  switch (res) {
  case OK: cout << "Operación realizada correctamente." << std::endl;
    break;
  case LISTA_LLENA: cout << "Operación NO realizada: lista llena." << std::endl;
    break;
  case YA_EXISTE: cout << "Operación NO realizada: el elemento ya existe" << std::endl;
    break;
  case NO_EXISTE: cout << "Operación NO realizada: el elemento no existe" << std::endl;
    break;
  case FIC_ERROR: cout << "Error en la apertura de fichero" << std::endl;
  }
}