#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

class Jugador {
private:
    string nombre;
    int victorias;
    int derrotas;
    int empates;

public:
    Jugador(string nombre = "", int v = 0, int d = 0, int e = 0);

    string getNombre() const;
    int getVictorias() const;
    int getDerrotas() const;
    int getEmpates() const;
    int getPartidasJugadas() const;

    void registrarVictoria();
    void registrarDerrota();
    void registrarEmpate();
};

#endif // JUGADOR_H