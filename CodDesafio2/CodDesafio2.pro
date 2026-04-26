TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ModContadorRecursos.cpp \
        fecha.cpp \
        fixture.cpp \
        ModCargarActualizar.cpp \
        eliminatoria.cpp \
        equipo.cpp \
        jugador.cpp \
        main.cpp \
        partido.cpp

HEADERS += \
    ModContadorRecursos.h \
    fecha.h \
    fixture.h \
    ModCargarActualizar.h \
    eliminatoria.h \
    equipo.h \
    jugador.h \
    partido.h
