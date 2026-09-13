#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "Tablero.h"

class Partida {
public:
    Partida();
    ~Partida();

    void guardarPartida(Tablero &tablero, bool turnoBlanco, string nombreBlancas, string nombreNegras, string nombreArchivo);
    bool cargarPartida(Tablero &tablero, bool &turnoBlanco, string &nombreBlancas, string &nombreNegras, string nombreArchivo);
    void listarPartidas();                                                              // Read (listado)
    bool eliminarPartida(string nombreArchivo);                                     // Delete
};

#endif //PARTTIDA_H
