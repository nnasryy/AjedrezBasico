#ifndef RANKINGJUGADORES_H
#define RANKINGJUGADORES_H

#include "Jugador.h"
#include <string>
using namespace std;

class RankingJugadores {
private:
    Jugador* jugadores;   // arreglo dinámico (nuestro "vector" manual)
    int cantidad;         // cuántos jugadores hay realmente
    int capacidad;        // cuánto espacio hay reservado

    void crecerSiNecesario(); // duplica el arreglo si se llena
    int buscarPosicionPorNombre(string nombre) const;

public:
    RankingJugadores();
    ~RankingJugadores();

    void registrarJugador(string nombre);              // Create
    void cargarDesdeArchivo(string nombreArchivo);      // Read (al iniciar)
    void guardarEnArchivo(string nombreArchivo) const;  // persistencia
    void actualizarResultado(string nombre, char resultado); // Update ('V','D','E')
    bool eliminarJugador(string nombre);                // Delete

    void ordenarPorVictorias(); // Burbuja
    void imprimirRanking() const;
};

#endif // RANKINGJUGADORES_H
