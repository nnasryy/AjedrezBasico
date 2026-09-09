#include "Torre.h"
#include "Tablero.h"

Torre::Torre(bool blanca, Coordenada pos)
    :Pieza(blanca, pos, blanca ? L"♖" : L"♜")
{
}

bool Torre::esMovimientoValido(Coordenada destino, Tablero &tablero) const
{
    if (!destino.esValida()) {
        return false;
    }

    bool mismaFila = (destino.fila == posicion.fila);
    bool mismaColumna = (destino.columna == posicion.columna);
    bool esLineaRecta = (mismaFila && !mismaColumna) || (!mismaFila && mismaColumna);
    if (!esLineaRecta) {
        return false;
    }

    if (!tablero.caminoLibre(posicion, destino)) {
        return false; // hay una pieza bloqueando el camino
    }

    if (tablero.hayPiezaEn(destino) && tablero.getPiezaEn(destino)->getEsBlanca() == esBlanca) {
        return false; // no puedes capturar tu propia pieza
    }

    return true;
}

char Torre::getTipo()const{
    return 'T';
}