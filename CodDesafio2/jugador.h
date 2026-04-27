#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
private:
    unsigned short golesMarcadosActual;
    unsigned short golesMarcadosHist;
    unsigned short amarillas;
    unsigned short rojas;
    unsigned short faltas;
public:
    Jugador(unsigned short = 0,unsigned short = 0,unsigned short = 0,unsigned short = 0,unsigned short = 0);
    unsigned short getAmarillas() const;
    void setAmarillas(unsigned short newAmarilla);
    unsigned short getRojas() const;
    void setRojas(unsigned short newRojas);
    unsigned short getFaltas() const;
    void setFaltas(unsigned short newFaltas);
    unsigned short getGolesMarcadosActual() const;
    void setGolesMarcadosActual(unsigned short newGolesMarcadosActual);
    unsigned short getGolesMarcadosHist() const;
    void setGolesMarcadosHist(unsigned short newGolesMarcadosHist);
};

#endif // JUGADOR_H
