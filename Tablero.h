#ifndef TABLERO_H
#define TABLERO_H

#include "Coordenada.h"
#include "Pieza.h"

class Tablero{
private:
    Pieza* casillas[8][8];
    void asignarCasilla(Pieza** casilla, Pieza* nuevaPieza);

public:
    Tablero();
    ~Tablero();

    void inicializar();
    void imprimir() const;

    Pieza* getPiezaEn(Coordenada c)const;
    bool hayPiezaEn(Coordenada c) const;
    bool esEnemiga(Coordenada c, bool colorPropio)const;
    bool moverPieza(Coordenada origen, Coordenada destino);
    bool caminoLibre(Coordenada origen, Coordenada destino) const;
    void colocarPieza(Pieza* pieza, Coordenada pos);
    Coordenada buscarRey(bool blanca) const;
    bool estaEnJaque(bool colorRey);
    void vaciarTablero();
    bool intentarEnroque(bool blancas, bool ladoRey);
};

#endif // TABLERO_H
