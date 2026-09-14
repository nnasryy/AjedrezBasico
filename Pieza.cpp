#include "Pieza.h"
using namespace std;

Pieza::Pieza(bool blanca, Coordenada pos, wstring simbolo)
    :esBlanca(blanca), posicion(pos), simbolo(simbolo), seHaMovido(false)
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

wstring Pieza::getSimbolo() const
{
    return simbolo;
}

void Pieza::setPosicion(Coordenada nueva)
{
    posicion = nueva;
}
bool Pieza::getSeHaMovido() const {
    return seHaMovido;
}
void Pieza::marcarComoMovida() {
    seHaMovido = true;
}