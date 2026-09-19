#ifndef COORDENADA_H
#define COORDENADA_H

struct Coordenada{
    int fila;
    int columna;

    Coordenada(int f = -1, int c = -1): fila(f), columna(c){}

    bool esValida() const{
        return fila >= 0 && fila < 8 && columna >= 0 && columna < 8;
    }

    bool operator==(const Coordenada &otra) const{
        return fila == otra.fila && columna == otra.columna;
    }

};

#endif // COORDENADA_H

