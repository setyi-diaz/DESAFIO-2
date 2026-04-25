#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
private:
    unsigned short golesMarcados;
    unsigned short amarillas;
    unsigned short rojas;
    unsigned short faltas;
public:
    Jugador();
    unsigned short getGolesMarcados() const;
    void setGolesMarcados(unsigned short newGoles);
    unsigned short getAmarillas() const;
    void setAmarillas(unsigned short newAmarilla);
    unsigned short getRojas() const;
    void setRojas(unsigned short newRojas);
    unsigned short getFaltas() const;
    void setFaltas(unsigned short newFaltas);
};

#endif // JUGADOR_H
