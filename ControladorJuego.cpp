#include "ControladorJuego.h"
#include "EntradaSalida.h"
#include "Partida.h"
#include <iostream>
#include <cwctype>
#include <cmath>

using namespace std;

ControladorJuego::ControladorJuego(Tablero &t, bool &turno, wstring nb, wstring nn,
                                   HistorialMovimientos &h, RankingJugadores &r, string archivo)
    : tablero(t), turnoBlanco(turno), nombreBlancas(nb), nombreNegras(nn),
    historial(h), ranking(r), archivoPartida(archivo), salirPartida(false)
{
}

void ControladorJuego::guardarPartidaActual()
{
    Partida p;
    string blancasStr(nombreBlancas.begin(), nombreBlancas.end());
    string negrasStr(nombreNegras.begin(), nombreNegras.end());
    p.guardarPartida(tablero, turnoBlanco, blancasStr, negrasStr, archivoPartida);
}

void ControladorJuego::mostrarEstadoPartida()
{
    wcout << L"\n";
    wcout << L"Capturadas (Blancas): ";
    if (capturadasBlancas.getCantidad() == 0) {
        wcout << L"ninguna";
    } else {
        for (int i = 0; i < capturadasBlancas.getCantidad(); i++) {
            wcout << capturadasBlancas.obtenerMovimiento(i) << L" ";
        }
    }
    wcout << L"\n";

    wcout << L"Capturadas (Negras): ";
    if (capturadasNegras.getCantidad() == 0) {
        wcout << L"ninguna";
    } else {
        for (int i = 0; i < capturadasNegras.getCantidad(); i++) {
            wcout << capturadasNegras.obtenerMovimiento(i) << L" ";
        }
    }
    wcout << L"\n\n";

    tablero.imprimir();

    wstring nombreTurno = turnoBlanco ? nombreBlancas : nombreNegras;
    wstring simboloTurno = turnoBlanco ? L"♔" : L"♚";
    wcout << L"\n------------------------------------------\n";
    wcout << L"  Turno de " << nombreTurno << L" " << simboloTurno
          << L" (" << (turnoBlanco ? L"Blancas" : L"Negras") << L")\n";
    wcout << L"------------------------------------------\n";
}

void ControladorJuego::manejarSubmenu()
{
    wcout << L"\n";
    wcout << L"========================\n";
    wcout << L"   OPCIONES DE PARTIDA\n";
    wcout << L"========================\n\n";
    int opcion = EntradaSalida::leerOpcionMenu(
        L"  1. Guardar partida\n  2. Guardar y salir\n  3. Ver historial\n"
        L"  4. Declarar empate\n  5. Salir sin guardar\n  6. Volver a jugar\n\n  Opcion: ",
        1, 6);

    if (opcion == 1) {
        guardarPartidaActual();
        wcout << L"\n  > Partida guardada.\n";
    } else if (opcion == 2) {
        guardarPartidaActual();
        wcout << L"\n  > Partida guardada. Hasta pronto.\n";
        salirPartida = true;
    } else if (opcion == 3) {
        wcout << L"\n--- Historial de movimientos ---\n";
        historial.imprimirHistorial();
        wcout << L"\nPresiona Enter para continuar...";
        wcin.get();
    } else if (opcion == 4) {
        wcout << L"\n  > Partida terminada en empate.\n";
        string blancasStr(nombreBlancas.begin(), nombreBlancas.end());
        string negrasStr(nombreNegras.begin(), nombreNegras.end());
        ranking.actualizarResultado(blancasStr, 'E');
        ranking.actualizarResultado(negrasStr, 'E');
        ranking.guardarEnArchivo("ranking.txt");
        salirPartida = true;
    } else if (opcion == 5) {
        salirPartida = true;
    }
    // opcion 6: solo vuelve a jugar
}

bool ControladorJuego::intentarEnroque(Coordenada origen, Coordenada destino)
{
    Pieza* pieza = tablero.getPiezaEn(origen);

    if (pieza == nullptr || pieza->getTipo() != 'R') {
        return false;
    }

    if (abs(destino.columna - origen.columna) != 2) {
        return false;
    }

    bool ladoRey = (destino.columna > origen.columna);
    bool exito = tablero.intentarEnroque(turnoBlanco, ladoRey);

    if (exito) {
        wcout << L"\n  > Enroque realizado.\n";
        turnoBlanco = !turnoBlanco;
    } else {
        wcout << L"\n  > No se puede enrocar en este momento.\n";
    }

    return true;
}

void ControladorJuego::realizarMovimiento()
{
    int fo = EntradaSalida::leerCoordenada(L"Fila origen (1-8): ");
    int co = EntradaSalida::leerColumna(L"Columna origen (a-h): ");
    int fd = EntradaSalida::leerCoordenada(L"Fila destino (1-8): ");
    int cd = EntradaSalida::leerColumna(L"Columna destino (a-h): ");

    Coordenada origen(fo, co);
    Coordenada destino(fd, cd);

    if (intentarEnroque(origen, destino)) {
        return;
    }

    Pieza* pieza = tablero.getPiezaEn(origen);
    if (pieza == nullptr || pieza->getEsBlanca() != turnoBlanco) {
        wcout << L"\n  > Movimiento invalido: no es tu pieza o casilla vacia.\n";
        return;
    }

    char promocion = 'T';
    bool esPeonLlegandoAlFinal = (pieza->getTipo() == 'P'
                                  && ((pieza->getEsBlanca() && destino.fila == 7)
                                      || (!pieza->getEsBlanca() && destino.fila == 0)));

    if (esPeonLlegandoAlFinal) {
        int eleccion = EntradaSalida::leerOpcionMenu(
            L"\n  Tu peon corona. Elige:\n  1. Torre\n  2. Caballo\n\n  Opcion: ", 1, 2);
        promocion = (eleccion == 2) ? 'C' : 'T';
    }

    Pieza* piezaEnDestino = tablero.getPiezaEn(destino);
    bool seCapturoRey = (piezaEnDestino != nullptr && piezaEnDestino->getTipo() == 'R');
    bool huboCaptura = (piezaEnDestino != nullptr);
    wstring simboloCapturado = huboCaptura ? piezaEnDestino->getSimbolo() : L"";

    if (tablero.moverPieza(origen, destino, promocion)) {
        wstring descripcion = (turnoBlanco ? L"Blancas: " : L"Negras: ")
        + EntradaSalida::coordenadaATexto(origen) + L" -> "
            + EntradaSalida::coordenadaATexto(destino)
            + (huboCaptura ? L" (captura)" : L"");
        historial.registrarMovimiento(descripcion);

        if (huboCaptura) {
            if (turnoBlanco) {
                capturadasNegras.registrarMovimiento(simboloCapturado);
            } else {
                capturadasBlancas.registrarMovimiento(simboloCapturado);
            }
        }

        if (seCapturoRey) {
            wstring ganador = turnoBlanco ? nombreBlancas : nombreNegras;
            wcout << L"\n  > ¡" << ganador << L" gano la partida capturando al Rey!\n";

            string ganadorStr(ganador.begin(), ganador.end());
            string perdedorStr = turnoBlanco
                                     ? string(nombreNegras.begin(), nombreNegras.end())
                                     : string(nombreBlancas.begin(), nombreBlancas.end());

            ranking.actualizarResultado(ganadorStr, 'V');
            ranking.actualizarResultado(perdedorStr, 'D');
            ranking.guardarEnArchivo("ranking.txt");

            salirPartida = true;
            return;
        }

        turnoBlanco = !turnoBlanco;

        if (tablero.estaEnJaque(turnoBlanco)) {
            wcout << L"\n  > ¡JAQUE al Rey " << (turnoBlanco ? L"Blanco" : L"Negro") << L"!\n";
        }
    } else {
        wcout << L"\n  > Movimiento invalido, intenta de nuevo.\n";
    }
}

void ControladorJuego::jugar()
{
    EntradaSalida::mostrarInstrucciones();

    while (!salirPartida) {
        mostrarEstadoPartida();

        wchar_t respuesta;
        bool entradaValida = false;

        while (!entradaValida) {
            wcout << L"  Escribe 'm' para mover, 'o' para opciones: ";
            wcin >> respuesta;
            respuesta = towlower(respuesta);

            if (respuesta == L'm' || respuesta == L'o') {
                entradaValida = true;
            } else {
                wcout << L"  > Opcion no reconocida. Intenta de nuevo.\n";
            }
        }

        if (respuesta == L'o') {
            manejarSubmenu();
        } else {
            realizarMovimiento();
        }
    }
}