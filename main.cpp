#include <iostream>
#include "Tablero.h"
#include "RankingJugadores.h"
#include "HistorialMovimientos.h"
#include "Partida.h"
#include "Coordenada.h"
#include <cwctype>
#include <fstream>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#else
#include <locale>
#endif
using namespace std;


int leerCoordenada(const wstring &mensaje)
{
    int valor;

    while (true) {
        wcout << mensaje;
        wcin >> valor;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(1000, L'\n');
            wcout << L"Entrada invalida. Debes ingresar solo un numero.\n";
            continue;
        }

        if (valor == 0) {
            return -1;
        }

        if (valor < 1 || valor > 8) {
            wcout << L"El numero debe estar entre 1 y 8, o 0 para salir.\n";
            continue;
        }

        return valor - 1;
    }
}

int leerColumna(const wstring &mensaje)
{
    wchar_t letra;

    while (true) {
        wcout << mensaje;
        wcin >> letra;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(1000, L'\n');
            wcout << L"Entrada invalida. Ingresa una letra de la a a la h.\n";
            continue;
        }

        letra = towlower(letra);

        if (letra < L'a' || letra > L'h') {
            wcout << L"La columna debe estar entre a y h.\n";
            continue;
        }

        return letra - L'a';
    }
}

int leerOpcionMenu(const wstring &mensaje, int minimo, int maximo)
{
    int valor;

    while (true) {
        wcout << mensaje;
        wcin >> valor;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(1000, L'\n');
            wcout << L"Entrada invalida. Ingresa solo un numero.\n";
            continue;
        }

        if (valor < minimo || valor > maximo) {
            wcout << L"Opcion fuera de rango.\n";
            continue;
        }

        return valor;
    }
}

wstring leerNombre(const wstring &mensaje)
{
    wstring nombre;
    wcout << mensaje;
    wcin >> nombre;
    return nombre;
}
bool archivoExiste(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    return archivo.is_open(); // si se pudo abrir, es porque ya existe
}

string pedirNombrePartidaUnico()
{
    while (true) {
        wstring nombreW = leerNombre(L"Nombre para esta partida (debe ser unico): ");
        string nombre(nombreW.begin(), nombreW.end());
        string archivo = "partida_" + nombre + ".txt";

        if (archivoExiste(archivo)) {
            wcout << L"Ya existe una partida con ese nombre. Elige otro.\n";
            continue;
        }

        return archivo;
    }
}

wstring coordenadaATexto(Coordenada c)
{
    wchar_t columna = L'a' + c.columna;
    int fila = c.fila + 1;
    return wstring(1, columna) + to_wstring(fila);
}

void mostrarMenuPrincipal()
{
    wcout << L"\n=== AJEDREZ BASICO ===\n";
    wcout << L"1. Nueva partida\n";
    wcout << L"2. Cargar partida guardada\n";
    wcout << L"3. Ver ranking de jugadores\n";
    wcout << L"4. Salir\n";
}
void jugarPartida(Tablero &tablero, bool &turnoBlanco, wstring nombreBlancas, wstring nombreNegras,
                  HistorialMovimientos &historial, RankingJugadores &ranking, string archivoPartida)
{
    bool salirPartida = false;

    while (!salirPartida) {
        tablero.imprimir();

        wstring nombreTurno = turnoBlanco ? nombreBlancas : nombreNegras;
        wstring simboloTurno = turnoBlanco ? L"♔" : L"♚";
        wcout << L"\nTurno de " << nombreTurno << L" " << simboloTurno
              << L" (" << (turnoBlanco ? L"Blancas" : L"Negras") << L")\n";
        wcout << L"(ingresa 0 en la fila origen para ver opciones de partida)\n";

        int fo = leerCoordenada(L"Fila origen (1-8): ");

        if (fo == -1) {
            int opcion = leerOpcionMenu(
                L"\n1. Guardar partida\n2. Ver historial\n3. Declarar empate\n4. Salir\n5. Volver a jugar\n6. Hacer Enroque\nOpcion: ",
                1, 6);

            if (opcion == 1) {
                Partida p;
                string blancasStr(nombreBlancas.begin(), nombreBlancas.end());
                string negrasStr(nombreNegras.begin(), nombreNegras.end());
                p.guardarPartida(tablero, turnoBlanco, blancasStr, negrasStr, archivoPartida);
                wcout << L"Partida guardada.\n";
            } else if (opcion == 2) {
                historial.imprimirHistorial();
                wcout << L"\nPresiona Enter para continuar...";
                wcin.ignore();
                wcin.get();
            } else if (opcion == 3) {
                wcout << L"Partida terminada en empate.\n";
                string blancasStr(nombreBlancas.begin(), nombreBlancas.end());
                string negrasStr(nombreNegras.begin(), nombreNegras.end());
                ranking.actualizarResultado(blancasStr, 'E');
                ranking.actualizarResultado(negrasStr, 'E');
                ranking.guardarEnArchivo("ranking.txt");
                salirPartida = true;
            } else if (opcion == 4) {
                salirPartida = true;
            } else if (opcion == 6) { // "Enroque"
                int lado = leerOpcionMenu(L"1. Enroque corto (lado del Rey)\n2. Enroque largo (lado de la Dama)\nOpcion: ", 1, 2);
                bool exito = tablero.intentarEnroque(turnoBlanco, lado == 1);
                if (exito) {
                    wcout << L"Enroque realizado.\n";
                    turnoBlanco = !turnoBlanco;
                } else {
                    wcout << L"No se puede enrocar en este momento.\n";
                }
                continue;
            }
            continue; // siempre vuelve al inicio del ciclo tras manejar el submenú
        }

        // Este bloque ahora SÍ se ejecuta cuando fo es una fila válida (fuera del if anterior)
        int co = leerColumna(L"Columna origen (a-h): ");
        int fd = leerCoordenada(L"Fila destino (1-8): ");
        int cd = leerColumna(L"Columna destino (a-h): ");

        Coordenada origen(fo, co);
        Coordenada destino(fd, cd);

        Pieza* pieza = tablero.getPiezaEn(origen);
        if (pieza == nullptr || pieza->getEsBlanca() != turnoBlanco) {
            wcout << L"Movimiento invalido! Intenta de nuevo.\n";
            continue;
        }

        Pieza* piezaEnDestino = tablero.getPiezaEn(destino);
        bool seCapturoRey = (piezaEnDestino != nullptr && piezaEnDestino->getTipo() == 'R');
        bool huboCaptura = (piezaEnDestino != nullptr);

        if (tablero.moverPieza(origen, destino)) {
            wstring descripcion = (turnoBlanco ? L"Blancas: " : L"Negras: ")
            + coordenadaATexto(origen) + L" -> " + coordenadaATexto(destino)
                + (huboCaptura ? L" (captura)" : L"");
            historial.registrarMovimiento(descripcion);

            if (seCapturoRey) {
                wstring ganador = turnoBlanco ? nombreBlancas : nombreNegras;
                wcout << L"\n¡" << ganador << L" gano la partida capturando al Rey!\n";

                string ganadorStr(ganador.begin(), ganador.end());
                string perdedorStr = turnoBlanco
                                         ? string(nombreNegras.begin(), nombreNegras.end())
                                         : string(nombreBlancas.begin(), nombreBlancas.end());

                ranking.actualizarResultado(ganadorStr, 'V');
                ranking.actualizarResultado(perdedorStr, 'D');
                ranking.guardarEnArchivo("ranking.txt");

                salirPartida = true;
                continue;
            }

            turnoBlanco = !turnoBlanco;

            if (tablero.estaEnJaque(turnoBlanco)) {
                wcout << L"\n¡JAQUE al Rey " << (turnoBlanco ? L"Blanco" : L"Negro") << L"!\n";
            }
        } else {
            wcout << L"Movimiento invalido, intenta de nuevo.\n";
        }
    }
}
int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#else
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());
#endif

    RankingJugadores ranking;
    ranking.cargarDesdeArchivo("ranking.txt");

    bool salirPrograma = false;

    while (!salirPrograma) {
        mostrarMenuPrincipal();
        int opcionMenu = leerOpcionMenu(L"Elige una opcion: ", 1, 4);
        if (opcionMenu == 1) {
            wstring nombreBlancas = leerNombre(L"Nombre del Jugador 1 (Blancas): ");
            wstring nombreNegras  = leerNombre(L"Nombre del Jugador 2 (Negras): ");

            string nombreBStr(nombreBlancas.begin(), nombreBlancas.end());
            string nombreNStr(nombreNegras.begin(), nombreNegras.end());

            ranking.registrarJugador(nombreBStr);
            ranking.registrarJugador(nombreNStr);
            ranking.guardarEnArchivo("ranking.txt");

            string archivoPartida = pedirNombrePartidaUnico();

            Tablero tablero;
            tablero.inicializar();
            bool turnoBlanco = true;
            HistorialMovimientos historial;
            jugarPartida(tablero, turnoBlanco, nombreBlancas, nombreNegras, historial, ranking, archivoPartida);

        } else if (opcionMenu == 2) {
            wstring nombreArchivoW = leerNombre(L"Nombre de la partida a cargar: ");
            string nombreArchivo("partida_" + string(nombreArchivoW.begin(), nombreArchivoW.end()) + ".txt");

            Tablero tablero;
            Partida p;
            HistorialMovimientos historial;
            bool turnoBlanco;
            string nombreBlancasStr, nombreNegrasStr;

            if (p.cargarPartida(tablero, turnoBlanco, nombreBlancasStr, nombreNegrasStr, nombreArchivo)) {
                wcout << L"Partida cargada.\n";
                wstring nombreBlancasW(nombreBlancasStr.begin(), nombreBlancasStr.end());
                wstring nombreNegrasW(nombreNegrasStr.begin(), nombreNegrasStr.end());
                jugarPartida(tablero, turnoBlanco, nombreBlancasW, nombreNegrasW, historial, ranking, nombreArchivo);
            } else {
                wcout << L"No se encontro una partida con ese nombre.\n";
            }
        } else if (opcionMenu == 3) {
            ranking.ordenarPorVictorias();
            ranking.imprimirRanking();

        } else if (opcionMenu == 4) {
            salirPrograma = true;
        }
    }

    wcout << L"Hasta pronto!\n";
    return 0;
}
