#ifndef RANKINGJUGADORES_H
#define RANKINGJUGADORES_H

#include "Jugador.h"
#include <string>
using namespace std;

class RankingJugadores {
private:
    Jugador* jugadores;
    int cantidad;
    int capacidad;

    void crecerSiNecesario();
    int buscarPosicionPorNombre(string nombre) const;

public:
    RankingJugadores();
    ~RankingJugadores();

    void registrarJugador(string nombre);
    void cargarDesdeArchivo(string nombreArchivo);
    void guardarEnArchivo(string nombreArchivo) const;
    void actualizarResultado(string nombre, char resultado);
    bool eliminarJugador(string nombre);

    void ordenarPorVictorias();
    void imprimirRanking() const;
};

#endif // RANKINGJUGADORES_H
