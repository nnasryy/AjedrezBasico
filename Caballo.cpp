#include "Caballo.h"
#include "Tablero.h"

Caballo::Caballo(bool blanca, Coordenada pos)
    : Pieza(blanca, pos, blanca ? L"♘" : L"♞")
{
}

bool Caballo::esMovimientoValido(Coordenada destino, Tablero &tablero) const
{
    if (!destino.esValida()) {
        return false;
    }

    int difFila = abs(destino.fila - posicion.fila);
    int difColumna = abs(destino.columna - posicion.columna);

    bool esFormaL = (difFila == 2 && difColumna == 1) || (difFila == 1 && difColumna == 2);
    if (!esFormaL) {
        return false;
    }

    if (tablero.hayPiezaEn(destino) && !tablero.esEnemiga(destino, esBlanca)) {
        return false;
    }

    return true;
}

char Caballo::getTipo() const {
    return 'C';
}