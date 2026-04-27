#include "jugador.h"

Jugador::Jugador(unsigned short cam,
                 unsigned short golesHist,
                 unsigned short minutos,
                 unsigned short tarAma,
                 unsigned short tarRoja,
                 unsigned short fal)
{
    camiseta = cam;

    // Los goles actuales del torneo empiezan en 0
    golesMarcados = 0;

    // Los goles historicos vienen del CSV
    golesMarcadosHist = golesHist;

    minutosJugados = minutos;
    amarillas = tarAma;
    rojas = tarRoja;
    faltas = fal;
}

unsigned short Jugador::getCamiseta() const
{
    return camiseta;
}

void Jugador::setCamiseta(unsigned short newCamiseta)
{
    camiseta = newCamiseta;
}

unsigned short Jugador::getGolesMarcados() const
{
    return golesMarcados;
}

void Jugador::setGolesMarcados(unsigned short newGoles)
{
    golesMarcados += newGoles;
}

unsigned short Jugador::getGolesMarcadosActual() const
{
    return golesMarcados;
}

void Jugador::setGolesMarcadosActual(unsigned short newGolesMarcadosActual)
{
    golesMarcados += newGolesMarcadosActual;
}

unsigned short Jugador::getGolesMarcadosHist() const
{
    return golesMarcadosHist;
}

void Jugador::setGolesMarcadosHist(unsigned short newGolesMarcadosHist)
{
    golesMarcadosHist = newGolesMarcadosHist;
}

unsigned short Jugador::getMinutosJugados() const
{
    return minutosJugados;
}

void Jugador::setMinutosJugados(unsigned short newMinutos)
{
    minutosJugados += newMinutos;
}

unsigned short Jugador::getAmarillas() const
{
    return amarillas;
}

void Jugador::setAmarillas(unsigned short newAmarilla)
{
    amarillas += newAmarilla;
}

unsigned short Jugador::getRojas() const
{
    return rojas;
}

void Jugador::setRojas(unsigned short newRojas)
{
    rojas += newRojas;
}

unsigned short Jugador::getFaltas() const
{
    return faltas;
}

void Jugador::setFaltas(unsigned short newFaltas)
{
    faltas += newFaltas;
}