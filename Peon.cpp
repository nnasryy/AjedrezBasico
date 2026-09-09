#include "Peon.h"

Peon::Peon(bool blanca, Coordenada pos)
    :Pieza(blanca, pos, blanca ? L"♙" : L"♟")
{
}

bool Peon::esMovimientoValido(Coordenada destino, Tablero &tablero)const
{
    if(!destino.esValida()){
        return false;
    }

    int direccion = esBlanca ? 1 : -1;

    int difFila = destino.fila - posicion.fila;
    int difColumna = destino.columna - posicion.columna;

    bool esCapturaDiagonal = (abs(difColumna)==1 && difFila == direccion);
    bool esAvanceRecto = (difColumna == 0 && difFila == direccion);

    if(esAvanceRecto){
        return true;
    }

    if(esCapturaDiagonal){
        return true;
    }
    return false;
}

char Peon::getTipo()const{
    return 'P';
}