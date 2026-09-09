#ifndef PEON_H
#define PEON_H

#include "Pieza.h"

class Peon : public Pieza
{
public:
    Peon(bool blanca, Coordenada pos);
    bool esMovimientoValido(Coordenada destino, Tablero &tablero) const override;
    char getTipo() const override;
};

#endif // PEON_H
