#include <iostream>
#include "Tablero.h"
#include "Rey.h"
#include "Torre.h"
#include "Peon.h"
#include "Caballo.h"

using namespace std;

Tablero::Tablero()
{

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

    casillas[0][0] = new Torre(true, Coordenada(0,0));
    casillas[0][7] = new Torre(true, Coordenada(0,7));
    casillas[7][0] = new Torre(false, Coordenada(7,0));
    casillas[7][7] = new Torre(false, Coordenada(7,7));


    casillas[0][1] = new Caballo(true, Coordenada(0,1));
    casillas[0][6] = new Caballo(true, Coordenada(0,6));
    casillas[7][1] = new Caballo(false, Coordenada(7,1));
    casillas[7][6] = new Caballo(false, Coordenada(7,6));


    casillas[0][4] = new Rey(true, Coordenada(0,4));
    casillas[7][4] = new Rey(false, Coordenada(7,4));


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

bool Tablero::moverPieza(Coordenada origen, Coordenada destino, char promocionElegida)
{
    Pieza* pieza = getPiezaEn(origen);

    if (pieza == nullptr) {
        return false;
    }

    if (!pieza->esMovimientoValido(destino, *this)) {
        return false;
    }
    if (Jaque(origen, destino)) {
        return false;
    }

    if (hayPiezaEn(destino)) {
        delete casillas[destino.fila][destino.columna];
        casillas[destino.fila][destino.columna] = nullptr;
    }

    casillas[destino.fila][destino.columna] = pieza;
    casillas[origen.fila][origen.columna] = nullptr;

    pieza->setPosicion(destino);
    pieza->marcarComoMovida();

    if (pieza->getTipo() == 'P') {
        int filaFinal = pieza->getEsBlanca() ? 7 : 0;

        if (destino.fila == filaFinal) {
            bool color = pieza->getEsBlanca();
            Pieza* nuevaPieza = nullptr;

            if (promocionElegida == 'C') {
                nuevaPieza = new Caballo(color, destino);
            } else {
                nuevaPieza = new Torre(color, destino);
            }

            delete casillas[destino.fila][destino.columna];
            casillas[destino.fila][destino.columna] = nuevaPieza;
        }
    }

    return true;
}

void Tablero::asignarCasilla(Pieza** casilla, Pieza* nuevaPieza)
{
    if (*casilla != nullptr) {
        delete *casilla;
    }
    *casilla = nuevaPieza;
}


void Tablero::imprimir() const
{
    for (int f = 7; f >= 0; f--) {
        wcout << (f + 1) << L" ";
        for (int c = 0; c < 8; c++) {
            bool esClara = (f + c) % 2 == 0;

            if (esClara) {
                wcout << L"\033[48;2;195;195;199m";
            } else {
                wcout << L"\033[48;2;94;93;94m";
            }
            wcout << L"\033[30m";

            Pieza* p = casillas[f][c];
            if (p == nullptr) {
                wcout << L"  ";
            } else {
                wcout << p->getSimbolo() << L" ";
            }

            wcout << L"\033[0m";
        }
        wcout << endl;
    }
    wcout << L"  a b c d e f g h" << endl;
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
                return true;
            }
        }
    }

    return false;
}

bool Tablero::Jaque(Coordenada origen, Coordenada destino)
{
    Pieza* piezaOrigen = casillas[origen.fila][origen.columna];
    Pieza* piezaDestino = casillas[destino.fila][destino.columna];
    bool colorPropio = piezaOrigen->getEsBlanca();

    casillas[destino.fila][destino.columna] = piezaOrigen;
    casillas[origen.fila][origen.columna] = nullptr;

    bool quedaEnJaque = estaEnJaque(colorPropio);

    casillas[origen.fila][origen.columna] = piezaOrigen;
    casillas[destino.fila][destino.columna] = piezaDestino;

    return quedaEnJaque;
}

bool Tablero::intentarEnroque(bool blancas, bool ladoRey)
{
    int fila = blancas ? 0 : 7;
    Coordenada posRey(fila, 4);
    Pieza* rey = getPiezaEn(posRey);

    if (rey == nullptr || rey->getTipo() != 'R' || rey->getSeHaMovido()) {
        return false;
    }

    int columnaTorre = ladoRey ? 7 : 0;
    Coordenada posTorre(fila, columnaTorre);
    Pieza* torre = getPiezaEn(posTorre);

    if (torre == nullptr || torre->getTipo() != 'T' || torre->getSeHaMovido()) {
        return false;
    }

    int paso = ladoRey ? 1 : -1;
    for (int c = 4 + paso; c != columnaTorre; c += paso) {
        if (hayPiezaEn(Coordenada(fila, c))) {
            return false;
        }
    }

    if (estaEnJaque(blancas)) {
        return false;
    }

    int columnaNuevaRey = ladoRey ? 6 : 2;
    int columnaNuevaTorre = ladoRey ? 5 : 3;

    casillas[fila][4] = nullptr;
    casillas[fila][columnaNuevaRey] = rey;
    rey->setPosicion(Coordenada(fila, columnaNuevaRey));
    rey->marcarComoMovida();

    casillas[fila][columnaTorre] = nullptr;
    casillas[fila][columnaNuevaTorre] = torre;
    torre->setPosicion(Coordenada(fila, columnaNuevaTorre));
    torre->marcarComoMovida();

    return true;
}
bool Tablero::esJaqueMate(bool colorRey)
{
    if (!estaEnJaque(colorRey)) {
        return false;
    }

    for (int f1 = 0; f1 < 8; f1++) {
        for (int c1 = 0; c1 < 8; c1++) {
            Pieza* pieza = casillas[f1][c1];
            if (pieza == nullptr || pieza->getEsBlanca() != colorRey) {
                continue;
            }

            Coordenada origen(f1, c1);

            for (int f2 = 0; f2 < 8; f2++) {
                for (int c2 = 0; c2 < 8; c2++) {
                    Coordenada destino(f2, c2);

                    if (pieza->esMovimientoValido(destino, *this)
                        && !Jaque(origen, destino)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
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