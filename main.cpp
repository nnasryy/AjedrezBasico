#include <iostream>
#include "Tablero.h"
#include "RankingJugadores.h"
#include "HistorialMovimientos.h"
#include "Partida.h"
#include "Coordenada.h"

#ifdef _WIN32
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
wstring coordenadaATexto(Coordenada c)
{
    wchar_t columna = L'a' + c.columna; // 0->a, 1->b, ..., 7->h
    int fila = c.fila + 1;              // 0->1, 1->2, ..., 7->8
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
                  HistorialMovimientos &historial)
{
    bool salirPartida = false;

    while (!salirPartida) {
        tablero.imprimir();

        wstring nombreTurno = turnoBlanco ? nombreBlancas : nombreNegras;
        wcout << L"\nTurno de " << nombreTurno
              << L" (" << (turnoBlanco ? L"Blancas" : L"Negras") << L")\n";
        wcout << L"(ingresa 0 en la fila origen para ver opciones de partida)\n";

        int fo = leerCoordenada(L"Fila origen (1-8): ");

        if (fo == -1) {
            int opcion = leerOpcionMenu(
                L"\n1. Guardar partida\n2. Ver historial\n3. Salir\n4. Volver a jugar\nOpcion: ",
                1, 4);

            if (opcion == 1) {
                Partida p;
                p.guardarPartida(tablero, turnoBlanco, "partida_guardada.txt");
                wcout << L"Partida guardada.\n";
                continue;
            } else if (opcion == 2) {
                historial.imprimirHistorial();
                wcout << L"\nPresiona Enter para continuar...";
                wcin.ignore();
                wcin.get();
                continue;
            } else if (opcion == 3) {
                salirPartida = true;
                continue;
            } else {
                continue;
            }
        }

        int co = leerCoordenada(L"Columna origen (1-8): ");
        int fd = leerCoordenada(L"Fila destino (1-8): ");
        int cd = leerCoordenada(L"Columna destino (1-8): ");

        Coordenada origen(fo, co);
        Coordenada destino(fd, cd);

        Pieza* pieza = tablero.getPiezaEn(origen);
        if (pieza == nullptr || pieza->getEsBlanca() != turnoBlanco) {
            wcout << L"Movimiento invalido! Intenta de nuevo.\n";
            continue;
        }

        bool huboCaptura = tablero.hayPiezaEn(destino);

        if (tablero.moverPieza(origen, destino)) {
            wstring descripcion = (turnoBlanco ? L"Blancas: " : L"Negras: ")
            + coordenadaATexto(origen) + L" -> " + coordenadaATexto(destino)
                + (huboCaptura ? L" (captura)" : L"");
            historial.registrarMovimiento(descripcion);

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

            Tablero tablero;
            tablero.inicializar();
            bool turnoBlanco = true;
            HistorialMovimientos historial;
            jugarPartida(tablero, turnoBlanco, nombreBlancas, nombreNegras, historial);

        } else if (opcionMenu == 2) {
            Tablero tablero;
            Partida p;
            HistorialMovimientos historial;
            bool turnoBlanco;
            if (p.cargarPartida(tablero, turnoBlanco, "partida_guardada.txt")) {
                wcout << L"Partida cargada.\n";
                jugarPartida(tablero, turnoBlanco, L"Blancas", L"Negras", historial);
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