#ifndef PIEZA_H
#define PIEZA_H

#include "Coordenada.h"
#include <string>

using namespace std;
class Tablero;

class Pieza{
protected:
    bool esBlanca;
    Coordenada posicion;
    wstring simbolo;
    bool seHaMovido = false;

public:
    Pieza(bool blanca, Coordenada pos, wstring simbolo);
    virtual ~Pieza();
    virtual char getTipo() const = 0;

    bool getEsBlanca() const;
    Coordenada getPosicion() const;
    wstring getSimbolo() const;
    void setPosicion(Coordenada nueva);
    bool getSeHaMovido() const;
    void marcarComoMovida();

    virtual bool esMovimientoValido(Coordenada destino, Tablero &tablero)
        const = 0;
};

#endif // PIEZA_H
