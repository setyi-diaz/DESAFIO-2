#include "jugador.h"

Jugador::Jugador(unsigned short Gol, unsigned short tarAma, unsigned short tarRoja, unsigned short fal){
    golesMarcados = Gol;
    amarillas = tarAma;
    rojas = tarRoja;
    faltas = fal;
}
unsigned short Jugador::getGolesMarcados() const{
    return golesMarcados;
}

void Jugador::setGolesMarcados(unsigned short newGoles){
    golesMarcados += newGoles;
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
