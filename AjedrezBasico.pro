TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Caballo.cpp \
        ControladorJuego.cpp \
        Coordenada.cpp \
        EntradaSalida.cpp \
        HistorialMovimientos.cpp \
        Partida.cpp \
        Peon.cpp \
        Pieza.cpp \
        RankingJugadores.cpp \
        Rey.cpp \
        Tablero.cpp \
        Torre.cpp \
        jugador.cpp \
        main.cpp

HEADERS += \
    Caballo.h \
    ControladorJuego.h \
    Coordenada.h \
    EntradaSalida.h \
    HistorialMovimientos.h \
    Partida.h \
    Peon.h \
    Pieza.h \
    RankingJugadores.h \
    Rey.h \
    Tablero.h \
    Torre.h \
    jugador.h
