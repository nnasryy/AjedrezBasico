#ifndef PIEZA_H
#define PIEZA_H

#include "coordenada.h"
#include <string>

using namespace std;
class Tablero; // declaracion

class Pieza{
protected:
    bool esBlanca;
    Coordenada posicion;
    wstring simbolo; //Para guardar el caracter
    //Unicode ♔♜

public:
    Pieza(bool blanca, Coordenada pos, wstring simbolo);
    virtual ~Pieza(); //destructor virtual
    virtual char getTipo() const = 0; // 'R', 'T', 'P' o 'C'

    bool getEsBlanca() const;
    Coordenada getPosicion() const;
    wstring getSimbolo() const;
    void setPosicion(Coordenada nueva);

    virtual bool esMovimientoValido(
        Coordenada destino,
        Tablero &tablero)
        const = 0;
};

#endif // PIEZA_H
