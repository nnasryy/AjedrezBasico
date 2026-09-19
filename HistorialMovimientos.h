#ifndef HISTORIALMOVIMIENTOS_H
#define HISTORIALMOVIMIENTOS_H

using namespace std;

#include <string>

class HistorialMovimientos {
private:
    wstring* movimientos;
    int cantidad;
    int capacidad;

    void crecerSiNecesario();

public:
    HistorialMovimientos();
    ~HistorialMovimientos();

    void registrarMovimiento(wstring descripcion);
    void imprimirHistorial() const;
    int getCantidad() const;
    wstring obtenerMovimiento(int indice) const;
    void limpiar();
};

#endif  // HISTORIALMOVIMIENTOS_H
