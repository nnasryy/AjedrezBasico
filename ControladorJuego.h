#ifndef CONTROLADORJUEGO_H
#define CONTROLADORJUEGO_H

#include "Tablero.h"
#include "HistorialMovimientos.h"
#include "RankingJugadores.h"
#include <string>

using namespace std;

class ControladorJuego {
private:
    Tablero &tablero;
    bool &turnoBlanco;
    wstring nombreBlancas;
    wstring nombreNegras;
    HistorialMovimientos &historial;
    RankingJugadores &ranking;
    string archivoPartida;
    HistorialMovimientos capturadasBlancas;
    HistorialMovimientos capturadasNegras;
    bool salirPartida;

    void mostrarEstadoPartida();
    void manejarSubmenu();
    void realizarMovimiento();
    bool intentarEnroque(Coordenada origen, Coordenada destino);
    void guardarPartidaActual();


public:
    ControladorJuego(Tablero &t, bool &turno, std::wstring nb, std::wstring nn,
                     HistorialMovimientos &h, RankingJugadores &r, std::string archivo);
    void jugar();
};

#endif