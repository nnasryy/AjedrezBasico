#include <iostream>
#include "Tablero.h"
#include "rankingjugadores.h"
#include "partida.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
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

wstring leerNombre(const wstring &mensaje)
{
    wstring nombre;
    wcout << mensaje;
    wcin.ignore(1000, L'\n'); // descarta cualquier salto de línea pendiente del input anterior
    getline(wcin, nombre);
    return nombre;
}

void mostrarMenuPrincipal()
{
    wcout << L"\n=== AJEDREZ BASICO ===\n";
    wcout << L"1. Nueva partida\n";
    wcout << L"2. Cargar partida guardada\n";
    wcout << L"3. Ver ranking de jugadores\n";
    wcout << L"4. Salir\n";
    wcout << L"Elige una opcion: ";
}

void jugarPartida(Tablero &tablero, bool &turnoBlanco, wstring nombreBlancas, wstring nombreNegras)
{
    bool salirPartida = false;

    while (!salirPartida) {
        tablero.imprimir();

        wstring nombreTurno = turnoBlanco ? nombreBlancas : nombreNegras;
        wcout << L"\nTurno de " << (turnoBlanco ? L"Blancas" : L"Negras")
              << L" (" << nombreTurno << L")\n";
        wcout << L"(ingresa 0 en la fila origen para ver opciones de partida)\n";

        int fo = leerCoordenada(L"Fila origen (1-8): ");

        if (fo == -1) {
            wcout << L"\n1. Guardar y continuar\n2. Guardar y salir al menu\n3. Salir sin guardar\n4. Volver a jugar\nOpcion: ";
            int opcion;
            wcin >> opcion;

            if (opcion == 1) {
                Partida p;
                p.guardarPartida(tablero, turnoBlanco, "partida_guardada.txt");
                wcout << L"Partida guardada.\n";
                continue;
            } else if (opcion == 2) {
                Partida p;
                p.guardarPartida(tablero, turnoBlanco, "partida_guardada.txt");
                salirPartida = true;
                continue;
            } else if (opcion == 3) {
                salirPartida = true;
                continue;
            } else {
                continue; // opción 4 o cualquier otra: vuelve a jugar
            }
        }

        int co = leerCoordenada(L"Columna origen (1-8): ");
        int fd = leerCoordenada(L"Fila destino (1-8): ");
        int cd = leerCoordenada(L"Columna destino (1-8): ");

        Coordenada origen(fo, co);
        Coordenada destino(fd, cd);

        Pieza* pieza = tablero.getPiezaEn(origen);
        if (pieza == nullptr || pieza->getEsBlanca() != turnoBlanco) {
            wcout << L"Movimiento invalido: no es tu pieza o casilla vacia.\n";
            continue;
        }

        if (tablero.moverPieza(origen, destino)) {
            turnoBlanco = !turnoBlanco;
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
#endif

    RankingJugadores ranking;
    ranking.cargarDesdeArchivo("ranking.txt");

    bool salirPrograma = false;

    while (!salirPrograma) {
        mostrarMenuPrincipal();
        int opcionMenu;
        wcin >> opcionMenu;

        if (opcionMenu == 1) {
            wstring nombreBlancas = leerNombre(L"Nombre del Jugador 1 (Blancas): ");
            wstring nombreNegras  = leerNombre(L"Nombre del Jugador 2 (Negras): ");

            // convertir a string simple para RankingJugadores (que guarda std::string)
            string nombreBStr(nombreBlancas.begin(), nombreBlancas.end());
            string nombreNStr(nombreNegras.begin(), nombreNegras.end());
            ranking.registrarJugador(nombreBStr);
            ranking.registrarJugador(nombreNStr);

            Tablero tablero;
            tablero.inicializar();
            bool turnoBlanco = true;
            jugarPartida(tablero, turnoBlanco, nombreBlancas, nombreNegras);

        } else if (opcionMenu == 2) {
            Tablero tablero;
            Partida p;
            bool turnoBlanco;
            if (p.cargarPartida(tablero, turnoBlanco, "partida_guardada.txt")) {
                wcout << L"Partida cargada.\n";
                jugarPartida(tablero, turnoBlanco, L"Blancas", L"Negras"); // nombres genéricos al cargar
            } else {
                wcout << L"No hay partida guardada.\n";
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