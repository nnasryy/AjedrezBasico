#include "EntradaSalida.h"
#include <iostream>
#include <fstream>
#include <cwctype>
#include <limits>
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

int EntradaSalida::leerCoordenada(const wstring &mensaje)
{
    int valor;
    while (true) {
        wcout << mensaje;
        wcin >> valor;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"  > Entrada invalida. Debes ingresar solo un numero.\n";
            continue;
        }
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

        if (valor == 0) {
            return -1;
        }

        if (valor < 1 || valor > 8) {
            wcout << L"  > El numero debe estar entre 1 y 8.\n";
            continue;
        }

        return valor - 1;
    }
}
int EntradaSalida::leerColumna(const wstring &mensaje)
{
    wstring entrada;

    while (true) {
        wcout << mensaje;
        wcin >> entrada;

        if (entrada == L"0") {
            return -1;
        }

        if (entrada.length() != 1 || wcin.fail()) {
            wcin.clear();
            wcin.ignore(1000, L'\n');
            wcout << L"  > Entrada invalida. Ingresa una letra de la a a la h, o 0 para reiniciar.\n";
            continue;
        }

        wchar_t letra = towlower(entrada[0]);

        if (letra < L'a' || letra > L'h') {
            wcout << L"  > La columna debe estar entre a y h, o 0 para reiniciar.\n";
            continue;
        }

        return letra - L'a';
    }
}

int EntradaSalida::leerOpcionMenu(const wstring &mensaje, int minimo, int maximo)
{
    int valor;
    while (true) {
        wcout << mensaje;
        wcin >> valor;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"  > Entrada invalida. Ingresa solo un numero.\n";
            continue;
        }
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

        if (valor < minimo || valor > maximo) {
            wcout << L"  > Opcion fuera de rango.\n";
            continue;
        }

        return valor;
    }
}

bool EntradaSalida::esUsernameValido(const wstring &texto)
{
    if (texto.empty()) {
        return false;
    }

    for (wchar_t c : texto) {
        bool esLetra = iswalpha(c);
        bool esDigito = iswdigit(c);
        bool esPermitido = (c == L'_' || c == L'.');

        if (!esLetra && !esDigito && !esPermitido) {
            return false;
        }
    }
    return true;
}

wstring EntradaSalida::leerUsername(const wstring &mensaje)
{
    wstring username;
    while (true) {
        wcout << mensaje;
        wcin >> username;
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n'); // descarta cualquier resto (ej. segunda palabra)

        if (!esUsernameValido(username)) {
            wcout << L"  > Username invalido. Usa solo letras, numeros, '_' o '.'\n";
            continue;
        }
        return username;
    }
}

bool EntradaSalida::archivoExiste(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    return archivo.is_open();
}

string EntradaSalida::pedirNombrePartidaUnico()
{
    while (true) {
        wstring nombreW = leerUsername(L"Nombre para esta partida (debe ser unico): ");
        string nombre(nombreW.begin(), nombreW.end());
        string archivo = "partida_" + nombre + ".txt";

        if (archivoExiste(archivo)) {
            wcout << L"  > Ya existe una partida con ese nombre. Elige otro.\n";
            continue;
        }
        return archivo;
    }
}

wstring EntradaSalida::coordenadaATexto(Coordenada c)
{
    wchar_t columna = L'a' + c.columna;
    int fila = c.fila + 1;
    return wstring(1, columna) + to_wstring(fila);
}

void EntradaSalida::mostrarMenuPrincipal()
{
    wcout << L"\n";
    wcout << L"========================\n";
    wcout << L"     AJEDREZ BASICO\n";
    wcout << L"========================\n\n";
    wcout << L"  1. Nueva partida\n";
    wcout << L"  2. Cargar partida guardada\n";
    wcout << L"  3. Ver ranking de jugadores\n";
    wcout << L"  4. Salir\n\n";
}

void EntradaSalida::mostrarInstrucciones()
{
    wcout << L"\n";
    wcout << L"==============================================\n";
    wcout << L"              COMO JUGAR - AJEDREZ\n";
    wcout << L"==============================================\n\n";

    wcout << L"  MOVIMIENTOS BASICOS\n";
    wcout << L"  ------------------------------------------\n";
    wcout << L"  - Escribe 'm' para mover una pieza.\n";
    wcout << L"  - Indica fila y columna de origen, luego\n";
    wcout << L"    fila y columna de destino.\n";
    wcout << L"  - Filas: numeros del 1 al 8.\n";
    wcout << L"  - Columnas: letras de la a a la h.\n";
    wcout << L"  - Escribe 0 en cualquier momento para\n";
    wcout << L"    reiniciar o cancelar el movimiento.\n\n";

    wcout << L"  ENROQUE\n";
    wcout << L"  ------------------------------------------\n";
    wcout << L"  - Mueve tu Rey 2 casillas hacia una de tus\n";
    wcout << L"    Torres para enrocar automaticamente.\n";
    wcout << L"  - Enroque corto: hacia el lado mas cercano\n";
    wcout << L"    (ej. Rey de e1 a g1).\n";
    wcout << L"  - Enroque largo: hacia el lado mas lejano\n";
    wcout << L"    (ej. Rey de e1 a c1).\n";
    wcout << L"  - Solo funciona si ni el Rey ni esa Torre\n";
    wcout << L"    se han movido antes, el camino esta\n";
    wcout << L"    libre, y no estas en jaque.\n\n";

    wcout << L"  PROMOCION DE PEON\n";
    wcout << L"  ------------------------------------------\n";
    wcout << L"  - Al llegar a la ultima fila, el juego te\n";
    wcout << L"    preguntara a que pieza quieres coronar\n";
    wcout << L"    tu peon (Torre o Caballo).\n\n";

    wcout << L"  JAQUE\n";
    wcout << L"  ------------------------------------------\n";
    wcout << L"  - El juego detecta y avisa cuando tu Rey\n";
    wcout << L"    esta en jaque.\n";
    wcout << L"  - No se permite ningun movimiento que deje\n";
    wcout << L"    (o mantenga) a tu propio Rey en jaque.\n\n";

    wcout << L"  OTRAS OPCIONES\n";
    wcout << L"  ------------------------------------------\n";
    wcout << L"  - Escribe 'o' en vez de mover para ver el\n";
    wcout << L"    menu de opciones: guardar, ver historial,\n";
    wcout << L"    declarar empate o salir.\n";
    wcout << L"==============================================\n";

    esperarEnter();   // <-- un solo ENTER al final
    limpiarPantalla(); // limpia para que la partida empiece en pantalla limpia
}
void EntradaSalida::esperarEnter()
{
    wcout << L"\n  [ Presiona ENTER para continuar... ]";
    wcout.flush();

#ifdef _WIN32
    int tecla;
    do {
        tecla = _getwch();

        if (tecla == 0 || tecla == 0xE0) {
            _getwch();
            tecla = 0;
        }
    } while (tecla != L'\r');   // '\r' es lo que devuelve ENTER
#else
    wstring linea;
    getline(wcin, linea);
#endif

    wcout << L"\n";
}
void EntradaSalida::limpiarPantalla()
    {
    wcout << L"\033[2J\033[H";
}
