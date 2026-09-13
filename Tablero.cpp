#include <iostream>
#include "Tablero.h"
#include "Rey.h"
#include "Torre.h"
#include "Peon.h"
#include "Caballo.h"

using namespace std;

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
    if (p == nullptr) return false;
    return p->getEsBlanca() != colorPropio;
}
//como parametro el struct que tiene fila y columna coordenada
//y evaluaremos el origen y el destino para saber si se puede mover
bool Tablero::moverPieza(Coordenada origen, Coordenada destino)
{
    Pieza* pieza = getPiezaEn(origen);
    if (pieza == nullptr) {
        return false;
    }
    if (!pieza->esMovimientoValido(destino, *this)) {
        return false;
    }
    asignarCasilla(&casillas[destino.fila][destino.columna], pieza);
    casillas[origen.fila][origen.columna] = nullptr;

    pieza->setPosicion(destino);
    pieza->marcarComoMovida();

    pieza->marcarComoMovida();
    if (pieza->getTipo() == 'P') {
        int filaFinal = pieza->getEsBlanca() ? 7 : 0;
        if (destino.fila == filaFinal) {
            bool color = pieza->getEsBlanca();
            delete casillas[destino.fila][destino.columna];
            casillas[destino.fila][destino.columna] = new Torre(color, destino);
        }
    }
    if (pieza->getTipo() == 'P') {
        int filaFinal = pieza->getEsBlanca() ? 7 : 0;
        if (destino.fila == filaFinal) {
            bool color = pieza->getEsBlanca();
            delete casillas[destino.fila][destino.columna];
            casillas[destino.fila][destino.columna] = new Torre(color, destino);
        }
    }
    return true;
}

void Tablero::asignarCasilla(Pieza** casilla, Pieza* nuevaPieza)
{
    if (*casilla != nullptr) {
        delete *casilla; // libera lo que había antes en esa casilla, si algo había
    }
    *casilla = nuevaPieza; // coloca la nueva pieza (o nullptr) en la casilla real
}


void Tablero::imprimir() const
{
    for (int f = 7; f >= 0; f--) {
        wcout << (f + 1) << L" ";
        for (int c = 0; c < 8; c++) {
            Pieza* p = casillas[f][c];
            if (p == nullptr) {
                cout<<" "<<endl;
                wcout << L". ";
            } else {
                wcout << p->getSimbolo() << L" ";
            }
        }
        wcout << endl;
    }
    wcout << L"  a b c d e f g h" << std::endl;
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

    while (!(actual == destino)) {
        if (hayPiezaEn(actual)) {
            return false;
        }
        actual = Coordenada(actual.fila + pasoFila, actual.columna + pasoColumna);
    }

    return true;
}
void Tablero::colocarPieza(Pieza* pieza, Coordenada pos)
{
    casillas[pos.fila][pos.columna] = pieza;
}
Coordenada Tablero::buscarRey(bool blanca) const
{
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            Pieza* p = casillas[f][c];
            if (p != nullptr && p->getEsBlanca() == blanca && p->getTipo() == 'R') {
                return Coordenada(f, c);
            }
        }
    }
    return Coordenada();
}

bool Tablero::estaEnJaque(bool colorRey)
{
    Coordenada posRey = buscarRey(colorRey);

    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            Pieza* p = casillas[f][c];

            if (p == nullptr) {
                continue;
            }

            if (p->getEsBlanca() == colorRey) {
                continue;
            }

            if (p->esMovimientoValido(posRey, *this)) {
                return true; // encontramos una amenaza real
            }
        }
    }

    return false; // ninguna pieza enemiga puede llegar hasta el Rey
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