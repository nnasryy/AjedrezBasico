#include <iostream>
#include "Tablero.h"
#include "Rey.h"
#include "Torre.h"
#include "Peon.h"
#include "Caballo.h"


Tablero::Tablero()
{
    //crear las casillas vacias
    for(int f=0; f < 8; f++){
        for(int c=0; c < 8; c++){
            casillas[f][c]=nullptr;
        }
    }

}

Tablero::~Tablero()
{
    for(int f=0; f<8;f++){
        for(int c = 0; c<8; c++){
            delete casillas[f][c];
        }
    }
}
void Tablero::inicializar()
{
    // Torres
    casillas[0][0] = new Torre(true, Coordenada(0,0));
    casillas[0][7] = new Torre(true, Coordenada(0,7));
    casillas[7][0] = new Torre(false, Coordenada(7,0));
    casillas[7][7] = new Torre(false, Coordenada(7,7));

    // Caballos
    casillas[0][1] = new Caballo(true, Coordenada(0,1));
    casillas[0][6] = new Caballo(true, Coordenada(0,6));
    casillas[7][1] = new Caballo(false, Coordenada(7,1));
    casillas[7][6] = new Caballo(false, Coordenada(7,6));

    // Reyes
    casillas[0][4] = new Rey(true, Coordenada(0,4));
    casillas[7][4] = new Rey(false, Coordenada(7,4));

    // Peones
    for (int c = 0; c < 8; c++) {
        casillas[1][c] = new Peon(true, Coordenada(1,c));
        casillas[6][c] = new Peon(false, Coordenada(6,c));
    }
}
Pieza* Tablero::getPiezaEn(Coordenada c) const
{
    if (!c.esValida()) return nullptr;
    return casillas[c.fila][c.columna];
}

bool Tablero::hayPiezaEn(Coordenada c) const
{
    return getPiezaEn(c) != nullptr;
}

bool Tablero::esEnemiga(Coordenada c, bool colorPropio) const
{
    Pieza* p = getPiezaEn(c);
    if (p == nullptr) return false; // casilla vacía no es "enemiga"
    return p->getEsBlanca() != colorPropio;
}

bool Tablero::moverPieza(Coordenada origen, Coordenada destino)
{
    Pieza* pieza = getPiezaEn(origen);

    if (pieza == nullptr) {
        return false; // no hay pieza en el origen
    }

    if (!pieza->esMovimientoValido(destino, *this)) {
        return false; // el movimiento no es valido
    }

    // si hay pieza enemiga en destino, se "captura" (se libera su memoria)
    if (hayPiezaEn(destino)) {
        delete casillas[destino.fila][destino.columna];
    }

    // mover el puntero de la casilla origen a la casilla destino
    casillas[destino.fila][destino.columna] = pieza;
    casillas[origen.fila][origen.columna] = nullptr;

    pieza->setPosicion(destino); // muy importante: actualizar la posición interna

    return true;
}

void Tablero::imprimir() const
{
    for (int f = 7; f >= 0; f--) {
        std::wcout << (f + 1) << L" ";
        for (int c = 0; c < 8; c++) {
            Pieza* p = casillas[f][c];
            if (p == nullptr) {
                std::wcout << L". ";
            } else {
                std::wcout << p->getSimbolo() << L" "; // <-- cambia esta línea temporalmente
            }
        }
        std::wcout << std::endl;
    }
    std::wcout << L"  1 2 3 4 5 6 7 8" << std::endl;
}

bool Tablero::caminoLibre(Coordenada origen, Coordenada destino) const
{
    int difFila = destino.fila - origen.fila;
    int difColumna = destino.columna - origen.columna;

    int pasoFila = 0;
    if (difFila > 0) pasoFila = 1;
    else if (difFila < 0) pasoFila = -1;

    int pasoColumna = 0;
    if (difColumna > 0) pasoColumna = 1;
    else if (difColumna < 0) pasoColumna = -1;

    Coordenada actual(origen.fila + pasoFila, origen.columna + pasoColumna);

    // avanza casilla por casilla hasta llegar justo antes del destino
    while (!(actual == destino)) {
        if (hayPiezaEn(actual)) {
            return false; // hay algo bloqueando el camino
        }
        actual = Coordenada(actual.fila + pasoFila, actual.columna + pasoColumna);
    }

    return true; // no encontró obstáculos en el camino
}
void Tablero::colocarPieza(Pieza* pieza, Coordenada pos)
{
    casillas[pos.fila][pos.columna] = pieza;
}

void Tablero::vaciarTablero()
{
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            delete casillas[f][c];
            casillas[f][c] = nullptr;
        }
    }
}