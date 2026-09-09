#include "Pieza.h"

Pieza::Pieza(bool blanca, Coordenada pos, std::wstring simbolo)
    :esBlanca(blanca), posicion(pos), simbolo(simbolo)
{
}

Pieza::~Pieza()
{

}

bool Pieza::getEsBlanca() const
{
    return esBlanca;
}

Coordenada Pieza::getPosicion() const
{
    return posicion;
}

std::wstring Pieza::getSimbolo() const
{
    return simbolo;
}

void Pieza::setPosicion(Coordenada nueva)
{
    posicion = nueva;
}