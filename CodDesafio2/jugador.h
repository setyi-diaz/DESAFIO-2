#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
private:
    unsigned short camiseta;

    // Goles actuales del torneo
    unsigned short golesMarcados;

    // Goles historicos leidos desde el CSV
    unsigned short golesMarcadosHist;

    unsigned short minutosJugados;
    unsigned short amarillas;
    unsigned short rojas;
    unsigned short faltas;

public:
    Jugador(unsigned short camiseta = 0,
            unsigned short golesHist = 0,
            unsigned short minutos = 0,
            unsigned short amarillas = 0,
            unsigned short rojas = 0,
            unsigned short faltas = 0);

    unsigned short getCamiseta() const;
    void setCamiseta(unsigned short newCamiseta);

    unsigned short getGolesMarcadosActual() const;
    void setGolesMarcadosActual(unsigned short newGolesMarcadosActual);

    unsigned short getGolesMarcadosHist() const;
    void setGolesMarcadosHist(unsigned short newGolesMarcadosHist);

    unsigned short getMinutosJugados() const;
    void setMinutosJugados(unsigned short newMinutos);

    unsigned short getAmarillas() const;
    void setAmarillas(unsigned short newAmarilla);

    unsigned short getRojas() const;
    void setRojas(unsigned short newRojas);

    unsigned short getFaltas() const;
    void setFaltas(unsigned short newFaltas);
};

#endif // JUGADOR_H
