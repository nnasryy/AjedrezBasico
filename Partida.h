#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "Tablero.h"

class Partida {
public:
    Partida();
    ~Partida();

    void guardarPartida(Tablero &tablero, bool turnoBlanco, std::string nombreArchivo); // Create/Update
    bool cargarPartida(Tablero &tablero, bool &turnoBlanco, std::string nombreArchivo);  // Read
    void listarPartidas();                                                              // Read (listado)
    bool eliminarPartida(std::string nombreArchivo);                                     // Delete
};

#endif //PARTTIDA_H
