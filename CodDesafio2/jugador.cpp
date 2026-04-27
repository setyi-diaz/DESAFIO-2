#include "jugador.h"

Jugador::Jugador(unsigned short GolsActual,unsigned short GolsHist, unsigned short tarAma, unsigned short tarRoja, unsigned short fal){
    golesMarcadosActual = GolsActual;
    golesMarcadosHist = GolsHist;
    amarillas = tarAma;
    rojas = tarRoja;
    faltas = fal;
}
unsigned short Jugador::getGolesMarcadosHist() const{
    return golesMarcadosHist;
}

void Jugador::setGolesMarcadosHist(unsigned short newGolesMarcadosHist){
    golesMarcadosHist += newGolesMarcadosHist;
}
unsigned short Jugador::getGolesMarcadosActual() const{
    return golesMarcadosActual;
}

void Jugador::setGolesMarcadosActual(unsigned short newGolesMarcadosActual){
    golesMarcadosActual += newGolesMarcadosActual;
}
unsigned short Jugador::getAmarillas() const{
    return amarillas;
}

void Jugador::setAmarillas(unsigned short newAmarilla){
    amarillas += newAmarilla;
}
unsigned short Jugador::getRojas() const{
    return rojas;
}

void Jugador::setRojas(unsigned short newRojas){
    rojas += newRojas;
}
unsigned short Jugador::getFaltas() const{
    return faltas;
}

void Jugador::setFaltas(unsigned short newFaltas){
    faltas += newFaltas;
}
