TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Caballo.cpp \
        Coordenada.cpp \
        Peon.cpp \
        Pieza.cpp \
        Rey.cpp \
        Tablero.cpp \
        Torre.cpp \
        jugador.cpp \
        main.cpp \
        partida.cpp \
        rankingjugadores.cpp

HEADERS += \
    Caballo.h \
    Coordenada.h \
    Peon.h \
    Pieza.h \
    Rey.h \
    Tablero.h \
    Torre.h \
    jugador.h \
    partida.h \
    rankingjugadores.h
