#ifndef HISTORIALMOVIMIENTOS_H
#define HISTORIALMOVIMIENTOS_H

using namespace std;

#include <string>

class HistorialMovimientos {
private:
    wstring* movimientos; // arreglo dinámico, mismo patrón que RankingJugadores
    int cantidad;
    int capacidad;

    void crecerSiNecesario();

public:
    HistorialMovimientos();
    ~HistorialMovimientos();

    void registrarMovimiento(wstring descripcion);
    void imprimirHistorial() const;
    void limpiar(); // para empezar una partida nueva sin arrastrar el historial anterior
};

#endif  // HISTORIALMOVIMIENTOS_H
