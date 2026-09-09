#include "Rey.h"
#include "Tablero.h"

Rey::Rey(bool blanca, Coordenada pos)
    : Pieza(blanca, pos, blanca ? L"♔" : L"♚")
{
}

bool Rey::esMovimientoValido(Coordenada destino, Tablero &tablero) const
{
    if(!destino.esValida()){
        return false;
    }

    int difFila = destino.fila - posicion.fila;
    int difColumna = destino.columna - posicion.columna;

    if(abs(difFila) <=1 && abs(difColumna) <=1){
        return true;
    }

    return false;
}
char Rey::getTipo() const {
    return 'R';
}