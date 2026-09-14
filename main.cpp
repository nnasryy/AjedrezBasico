#include <iostream>
#include "Tablero.h"
#include "RankingJugadores.h"
#include "HistorialMovimientos.h"
#include "Partida.h"
#include "Coordenada.h"
#include "EntradaSalida.h"
#include "ControladorJuego.h"
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
        EntradaSalida::mostrarMenuPrincipal();
        int opcionMenu = EntradaSalida::leerOpcionMenu(L"  Elige una opcion: ", 1, 4);

        if (opcionMenu == 1) {
            wstring nombreBlancas = EntradaSalida::leerUsername(L"\nUsername del Jugador 1 (Blancas): ");
            wstring nombreNegras  = EntradaSalida::leerUsername(L"Username del Jugador 2 (Negras): ");

            string nombreBStr(nombreBlancas.begin(), nombreBlancas.end());
            string nombreNStr(nombreNegras.begin(), nombreNegras.end());

            ranking.registrarJugador(nombreBStr);
            ranking.registrarJugador(nombreNStr);
            ranking.guardarEnArchivo("ranking.txt");

            string archivoPartida = EntradaSalida::pedirNombrePartidaUnico();

            Tablero tablero;
            tablero.inicializar();
            bool turnoBlanco = true;
            HistorialMovimientos historial;

            ControladorJuego juego(tablero, turnoBlanco, nombreBlancas, nombreNegras,
                                   historial, ranking, archivoPartida);
            juego.jugar();

        } else if (opcionMenu == 2) {
            HistorialMovimientos listado;
            Partida pTemp;
            pTemp.listarPartidas(listado);

            if (listado.getCantidad() == 0) {
                wcout << L"\n  > No hay partidas guardadas todavia.\n";
            } else {
                wcout << L"\nPartidas disponibles:\n";
                listado.imprimirHistorial();

                wstring nombreArchivoW = EntradaSalida::leerUsername(L"\nNombre de la partida a cargar (0 para cancelar): partida_");
                string nombreArchivo("partida_" + string(nombreArchivoW.begin(), nombreArchivoW.end()) + ".txt");
                if (nombreArchivoW == L"0") {
                    wcout << L"\n  > Operacion cancelada.\n";
                } else {
                    string nombreArchivo("partida_" + string(nombreArchivoW.begin(), nombreArchivoW.end()) + ".txt");

                    Tablero tablero;
                    Partida p;
                    HistorialMovimientos historial;
                    bool turnoBlanco;
                    string nombreBlancasStr, nombreNegrasStr;

                    if (p.cargarPartida(tablero, turnoBlanco, nombreBlancasStr, nombreNegrasStr, nombreArchivo)) {
                        wcout << L"\n  > Partida cargada.\n";
                        wstring nombreBlancasW(nombreBlancasStr.begin(), nombreBlancasStr.end());
                        wstring nombreNegrasW(nombreNegrasStr.begin(), nombreNegrasStr.end());

                        ControladorJuego juego(tablero, turnoBlanco, nombreBlancasW, nombreNegrasW,
                                               historial, ranking, nombreArchivo);
                        juego.jugar();
                    } else {
                        wcout << L"\n  > No se encontro una partida con ese nombre.\n";
                    }
                }
            }

        } else if (opcionMenu == 3) {
            ranking.ordenarPorVictorias();
            ranking.imprimirRanking();

        } else if (opcionMenu == 4) {
            salirPrograma = true;
        }
    }

    wcout << L"\nHasta pronto!\n";
    return 0;
}