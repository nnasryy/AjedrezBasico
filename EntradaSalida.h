#ifndef ENTRADASALIDA_H
#define ENTRADASALIDA_H

#include <string>
#include "Coordenada.h"
using namespace std;

class EntradaSalida {
public:
    static int leerCoordenada(const wstring &mensaje);
    static int leerColumna(const wstring &mensaje);
    static int leerOpcionMenu(const wstring &mensaje, int minimo, int maximo);
    static wstring leerUsername(const wstring &mensaje);
    static bool esUsernameValido(const wstring &texto);
    static bool archivoExiste(string nombreArchivo);
    static string pedirNombrePartidaUnico();
    static wstring coordenadaATexto(Coordenada c);
    static void mostrarMenuPrincipal();
    static void mostrarInstrucciones();
};
#endif // ENTRADASALIDA_H
