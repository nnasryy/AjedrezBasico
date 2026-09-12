#include "Partida.h"
#include "Rey.h"
#include "Torre.h"
#include "Peon.h"
#include "Caballo.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

using namespace std;

Partida::Partida() {}
Partida::~Partida() {}

void Partida::guardarPartida(Tablero &tablero, bool turnoBlanco, string nombreArchivo)
{
    ofstream archivo(nombreArchivo);

    archivo << (turnoBlanco ? "BLANCAS" : "NEGRAS") << "\n";

    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            Pieza* p = tablero.getPiezaEn(Coordenada(f, c));
            if (p != nullptr) {
                archivo << p->getTipo() << ";"
                        << (p->getEsBlanca() ? "B" : "N") << ";"
                        << f << ";" << c << "\n";
            }
        }
    }

    archivo.close();
}

bool Partida::cargarPartida(Tablero &tablero, bool &turnoBlanco, string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    tablero.vaciarTablero();

    string linea;
    getline(archivo, linea);
    turnoBlanco = (linea == "BLANCAS");

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string tipo, color, filaStr, colStr;

        getline(ss, tipo, ';');
        getline(ss, color, ';');
        getline(ss, filaStr, ';');
        getline(ss, colStr, ';');

        int f = stoi(filaStr);
        int c = stoi(colStr);
        bool blanca = (color == "B");
        Coordenada pos(f, c);

        Pieza* nueva = nullptr;
        if (tipo == "R") nueva = new Rey(blanca, pos);
        else if (tipo == "T") nueva = new Torre(blanca, pos);
        else if (tipo == "P") nueva = new Peon(blanca, pos);
        else if (tipo == "C") nueva = new Caballo(blanca, pos);

        if (nueva != nullptr) {
            tablero.colocarPieza(nueva, pos);
        }
    }

    archivo.close();
    return true;
}

void Partida::listarPartidas()
{
    wcout << L"Partidas guardadas:\n";
    for (const auto &entrada : filesystem::directory_iterator(".")) {
        if (entrada.path().extension() == ".txt") {
            wcout << L" - " << entrada.path().filename().wstring() << L"\n";
        }
    }
}

bool Partida::eliminarPartida(std::string nombreArchivo)
{
    return std::filesystem::remove(nombreArchivo);
}