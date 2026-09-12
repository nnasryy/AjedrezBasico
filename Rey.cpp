#include "Rey.h"
#include "Tablero.h"

Rey::Rey(bool blanca, Coordenada pos)
    : Pieza(blanca, pos, blanca ? L"♔" : L"♚")
{
}

bool Rey::esMovimientoValido(Coordenada destino, Tablero &tablero) const
{
    if (!destino.esValida()) {
        return false;
    }

    int difFila = destino.fila - posicion.fila;
    int difColumna = destino.columna - posicion.columna;

    if (abs(difFila) <= 1 && abs(difColumna) <= 1) {
        // no puede capturar una pieza de su propio color
        if (tablero.hayPiezaEn(destino) && !tablero.esEnemiga(destino, esBlanca)) {
            return false;
        }
        return true;
    }

    return false;
}

char Rey::getTipo() const {
    return 'R';
}