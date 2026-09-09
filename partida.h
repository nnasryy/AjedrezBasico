#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "Tablero.h"

using namespace std;

class Partida {
public:
    Partida();
    ~Partida();

    void guardarPartida(Tablero &tablero, bool turnoBlanco, string nombreArchivo); // Create/Update
    bool cargarPartida(Tablero &tablero, bool &turnoBlanco, string nombreArchivo);  // Read
    void listarPartidas();                                                              // Read (listado)
    bool eliminarPartida(std::string nombreArchivo);                                     // Delete
};
#endif // PARTIDA_H
