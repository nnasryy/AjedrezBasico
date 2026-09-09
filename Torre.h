#ifndef TORRE_H
#define TORRE_H

#include "Pieza.h"

    class Torre : public Pieza{
    public:
     Torre(bool blanca, Coordenada pos);
        bool esMovimientoValido(Coordenada destino, Tablero &tablero)
         const override;
     char getTipo() const override;
};

#endif // TORRE_H
