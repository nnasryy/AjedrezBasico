#ifndef REY_H
#define REY_H

#include "Pieza.h"

class Rey : public Pieza
{
public:
    Rey(bool blanca, Coordenada pos);
    bool esMovimientoValido(Coordenada destino, Tablero &tablero)const override;
    char getTipo() const override;
};

#endif // REY_H
