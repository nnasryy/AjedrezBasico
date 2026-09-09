#include "Jugador.h"
Jugador::Jugador(string nombre, int v, int d, int e)
    : nombre(nombre), victorias(v), derrotas(d), empates(e)
{
}

string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getVictorias() const {
    return victorias;
}

int Jugador::getDerrotas() const {
    return derrotas;
}
int Jugador::getEmpates() const {
    return empates;
}
int Jugador::getPartidasJugadas() const {
    return victorias + derrotas + empates;
}

void Jugador::registrarVictoria() {
    victorias++;
}
void Jugador::registrarDerrota() {
    derrotas++;
}
void Jugador::registrarEmpate() {
    empates++;
}