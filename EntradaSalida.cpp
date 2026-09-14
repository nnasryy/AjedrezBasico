#include "EntradaSalida.h"
#include <iostream>
#include <fstream>
#include <cwctype>
#include <limits>


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

        if (valor < 1 || valor > 8) {
            wcout << L"  > El numero debe estar entre 1 y 8.\n";
            continue;
        }

        return valor - 1;
    }
}

int EntradaSalida::leerColumna(const wstring &mensaje)
{
    wchar_t letra;
    while (true) {
        wcout << mensaje;
        wcin >> letra;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"  > Entrada invalida. Ingresa una letra de la a a la h.\n";
            continue;
        }
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

        letra = towlower(letra);

        if (letra < L'a' || letra > L'h') {
            wcout << L"  > La columna debe estar entre a y h.\n";
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
    wcout << L"------------------------------------------\n";
    wcout << L"  COMO JUGAR\n";
    wcout << L"------------------------------------------\n";
    wcout << L"  - Para mover: indica fila y columna de\n";
    wcout << L"    origen, luego fila y columna de destino.\n";
    wcout << L"  - Filas: numeros del 1 al 8.\n";
    wcout << L"  - Columnas: letras de la a a la h.\n";
    wcout << L"  - Para enrocar: mueve tu Rey 2 casillas\n";
    wcout << L"    hacia una de tus Torres.\n";
    wcout << L"  - Escribe 'o' en vez de mover para ver\n";
    wcout << L"    las opciones de la partida.\n";
    wcout << L"------------------------------------------\n\n";
}