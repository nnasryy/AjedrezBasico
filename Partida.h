#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "Tablero.h"
#include "HistorialMovimientos.h"

class Partida {
public:
    Partida();
    ~Partida();

    void guardarPartida(Tablero &tablero, bool turnoBlanco, string nombreBlancas, string nombreNegras, string nombreArchivo);
    bool cargarPartida(Tablero &tablero, bool &turnoBlanco, string &nombreBlancas, string &nombreNegras, string nombreArchivo);
    void listarPartidas(HistorialMovimientos &listado);
    bool eliminarPartida(string nombreArchivo);
};

#endif //PARTTIDA_H
