#include "RankingJugadores.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

const char DELIMITADOR = '|';

RankingJugadores::RankingJugadores()
{
    capacidad = 4;
    cantidad = 0;
    jugadores = new Jugador[capacidad];
}

RankingJugadores::~RankingJugadores()
{
    delete[] jugadores;
}

void RankingJugadores::crecerSiNecesario()
{
    if (cantidad < capacidad) {
        return;
    }

    int nuevaCapacidad = capacidad * 2;
    Jugador* nuevoArreglo = new Jugador[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevoArreglo[i] = jugadores[i];
    }

    delete[] jugadores;
    jugadores = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

int RankingJugadores::buscarPosicionPorNombre(string nombre) const
{
    for (int i = 0; i < cantidad; i++) {
        if (jugadores[i].getNombre() == nombre) {
            return i;
        }
    }
    return -1;
}

void RankingJugadores::registrarJugador(string nombre)
{
    if (buscarPosicionPorNombre(nombre) != -1) {
        return;
    }

    crecerSiNecesario();
    jugadores[cantidad] = Jugador(nombre);
    cantidad++;
}

void RankingJugadores::cargarDesdeArchivo(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, vStr, dStr, eStr;

        getline(ss, nombre, DELIMITADOR);
        getline(ss, vStr, DELIMITADOR);
        getline(ss, dStr, DELIMITADOR);
        getline(ss, eStr, DELIMITADOR);

        crecerSiNecesario();
        jugadores[cantidad] = Jugador(nombre, stoi(vStr), stoi(dStr),stoi(eStr));
        cantidad++;
    }
    archivo.close();
}

void RankingJugadores::guardarEnArchivo(string nombreArchivo) const
{
    ofstream archivo(nombreArchivo); // trunca y reescribe todo, como ios::trunc

    for (int i = 0; i < cantidad; i++) {
        archivo << jugadores[i].getNombre() << DELIMITADOR
                << jugadores[i].getVictorias() << DELIMITADOR
                << jugadores[i].getDerrotas() << DELIMITADOR
                << jugadores[i].getEmpates() << "\n";
    }
    archivo.close();
}

void RankingJugadores::actualizarResultado(string nombre, char resultado)
{
    int pos = buscarPosicionPorNombre(nombre);
    if (pos == -1) {
        return;
    }

    if (resultado == 'V') jugadores[pos].registrarVictoria();
    else if (resultado == 'D') jugadores[pos].registrarDerrota();
    else if (resultado == 'E') jugadores[pos].registrarEmpate();

    guardarEnArchivo("ranking.txt"); // sincroniza con disco inmediatamente
}

bool RankingJugadores::eliminarJugador(string nombre)
{
    int pos = buscarPosicionPorNombre(nombre);
    if (pos == -1) {
        return false;
    }


    for (int i = pos; i < cantidad - 1; i++) {
        jugadores[i] = jugadores[i + 1];
    }
    cantidad--;

    guardarEnArchivo("ranking.txt");
    return true;
}

//Burbuja
void RankingJugadores::ordenarPorVictorias()
{
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - 1 - i; j++) {
            if (jugadores[j].getVictorias() < jugadores[j + 1].getVictorias()) {
                Jugador temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }
}

void RankingJugadores::imprimirRanking() const
{
    wcout << L"--- Ranking de Jugadores ---\n";
    for (int i = 0; i < cantidad; i++) {
        wcout << (i + 1) << L". " << jugadores[i].getNombre().c_str()
        << L" | V:" << jugadores[i].getVictorias()
        << L" D:" << jugadores[i].getDerrotas()
        << L" E:" << jugadores[i].getEmpates() << L"\n";
    }
}