#ifndef CABALLO_H
#define CABALLO_H

#include "Pieza.h"

class Caballo : public Pieza
{
public:
    Caballo(bool blanca, Coordenada pos);
    bool esMovimientoValido(Coordenada destino, Tablero &tablero) const override;
    char getTipo() const override;
};

#endif // CABALLO_H