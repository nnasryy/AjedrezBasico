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

const char DELIMITADOR = ';';

Partida::Partida() {}
Partida::~Partida() {}

void Partida::guardarPartida(Tablero &tablero, bool turnoBlanco, string nombreBlancas, string nombreNegras, string nombreArchivo)
{
    ofstream archivo(nombreArchivo);

    // primera linea: nombres y turno, usando el mismo delimitador que las piezas
    archivo << nombreBlancas << DELIMITADOR << nombreNegras << DELIMITADOR
            << (turnoBlanco ? "BLANCAS" : "NEGRAS") << "\n";

    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            Pieza* p = tablero.getPiezaEn(Coordenada(f, c));
            if (p != nullptr) {
                archivo << p->getTipo() << DELIMITADOR
                        << (p->getEsBlanca() ? "B" : "N") << DELIMITADOR
                        << f << DELIMITADOR << c << "\n";
            }
        }
    }

    archivo.close();
}

bool Partida::cargarPartida(Tablero &tablero, bool &turnoBlanco, string &nombreBlancas, string &nombreNegras, string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    tablero.vaciarTablero();

    string primeraLinea;
    if (!getline(archivo, primeraLinea)) {
        return false;
    }

    stringstream encabezado(primeraLinea);
    string turnoStr;

    getline(encabezado, nombreBlancas, DELIMITADOR);
    getline(encabezado, nombreNegras, DELIMITADOR);
    getline(encabezado, turnoStr, DELIMITADOR);

    if (nombreBlancas.empty() || nombreNegras.empty() || turnoStr.empty()) {
        return false; // encabezado corrupto o incompleto
    }

    turnoBlanco = (turnoStr == "BLANCAS");

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string tipo, color, filaStr, colStr;

        getline(ss, tipo, DELIMITADOR);
        getline(ss, color, DELIMITADOR);
        getline(ss, filaStr, DELIMITADOR);
        getline(ss, colStr, DELIMITADOR);

        if (tipo.empty() || filaStr.empty() || colStr.empty()) continue;

        try {
            int f = stoi(filaStr);
            int c = stoi(colStr);
            if (f < 0 || f > 7 || c < 0 || c > 7) continue;

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
        } catch (const exception &e) {
            continue;
        }
    }

    archivo.close();
    return true;
}

void Partida::listarPartidas(HistorialMovimientos &listado)
{
    for (const auto &entrada : filesystem::directory_iterator(".")) {
        if (!entrada.is_regular_file()) {
            continue;
        }

        string nombreArchivo = entrada.path().filename().string();

        bool empiezaConPartida = (nombreArchivo.rfind("partida_", 0) == 0);
        bool terminaEnTxt = (entrada.path().extension() == ".txt");

        if (empiezaConPartida && terminaEnTxt) {
            wstring wnombre(nombreArchivo.begin(), nombreArchivo.end());
            listado.registrarMovimiento(wnombre);
        }
    }
}

bool Partida::eliminarPartida(string nombreArchivo)
{
    return filesystem::remove(nombreArchivo);
}