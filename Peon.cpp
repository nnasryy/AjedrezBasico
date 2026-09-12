#include "Peon.h"
#include "Tablero.h"

Peon::Peon(bool blanca, Coordenada pos)
    :Pieza(blanca, pos, blanca ? L"♙" : L"♟")
{
}

bool Peon::esMovimientoValido(Coordenada destino, Tablero &tablero) const
{
    if (!destino.esValida()) {
        return false;
    }

    int direccion = esBlanca ? 1 : -1;
    int difFila = destino.fila - posicion.fila;
    int difColumna = destino.columna - posicion.columna;

    bool esAvanceRecto = (difColumna == 0 && difFila == direccion);
    bool esCapturaDiagonal = (abs(difColumna) == 1 && difFila == direccion);

    if (esAvanceRecto) {
        // el avance recto solo es válido si la casilla destino está vacía
        return !tablero.hayPiezaEn(destino);
    }

    if (esCapturaDiagonal) {
        // la diagonal solo es válida si hay una pieza ENEMIGA en el destino
        return tablero.esEnemiga(destino, esBlanca);
    }

    return false;
}

char Peon::getTipo()const{
    return 'P';
}