#include "HistorialMovimientos.h"
#include <iostream>

using namespace std;

HistorialMovimientos::HistorialMovimientos()
{
    capacidad = 8;
    cantidad = 0;
    movimientos = new wstring[capacidad];
}

HistorialMovimientos::~HistorialMovimientos()
{
    delete[] movimientos;
}

void HistorialMovimientos::crecerSiNecesario()
{
    if (cantidad < capacidad) {
        return;
    }

    int nuevaCapacidad = capacidad + 5;
    wstring* nuevoArreglo = new wstring[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevoArreglo[i] = movimientos[i];
    }

    delete[] movimientos;
    movimientos = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

void HistorialMovimientos::registrarMovimiento(wstring descripcion)
{
    crecerSiNecesario();
    movimientos[cantidad] = descripcion;
    cantidad++;
}

void HistorialMovimientos::imprimirHistorial() const
{
    if (cantidad == 0) {
        wcout << L"Aun no se ha realizado ningun movimiento.\n";
        return;
    }

    wcout << L"--- Historial de movimientos ---\n";
    for (int i = 0; i < cantidad; i++) {
        wcout << (i + 1) << L". " << movimientos[i] << L"\n";
    }
}

int HistorialMovimientos::getCantidad() const
{
    return cantidad;
}

wstring HistorialMovimientos::obtenerMovimiento(int indice) const
{
    if (indice < 0 || indice >= cantidad) {
        return L"";
    }
    return movimientos[indice];
}

void HistorialMovimientos::limpiar()
{
    delete[] movimientos;
    capacidad = 8;
    cantidad = 0;
    movimientos = new wstring[capacidad];
}