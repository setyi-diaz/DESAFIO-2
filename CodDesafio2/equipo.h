#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <string>
#include <cstring>
#include <random>
using std::strlen;
using std::strncpy;
using std::string;

class Equipo
{
private:
    unsigned short ranking;
    char pais[25];
    char dt[20];
    char federacion[47];
    char confederacion[10];
    unsigned short golesAFavor;
    unsigned short golesEnContra;
    unsigned short partidosGanados;
    unsigned short partidosEmpatados;
    unsigned short partidosPerdidos;
    Jugador* convocados[26];
public:
    Equipo(unsigned short = 0, const char * const = "", const char * const = "", const char * const = "",
           const char * const = "", unsigned short = 0,unsigned short = 0, unsigned short = 0, unsigned short = 0,
           unsigned short = 0);

    const Equipo &operator=(const Equipo &);
    void elegirTitulares();

    unsigned short getRanking() const;
    void setRanking(unsigned short newRanking);
    const char* getPais() const;
    //void setPais();
    const char* getDt() const;
    //void setDt();
    const char* getFederacion() const;
    //void setFederacion();
    const char* getConfederacion() const;
    //void setConfederacion();
    unsigned short getGolesAFavor() const;
    void setGolesAFavor(unsigned short newGolesAFavor);
    unsigned short getGolesEnContra() const;
    void setGolesEnContra(unsigned short newGolesEnContra);
    unsigned short getPartidosGanados() const;
    void setPartidosGanados(unsigned short newPartidosGanados);
    unsigned short getPartidosEmpatados() const;
    void setPartidosEmpatados(unsigned short newPartidosEmpatados);
    unsigned short getPartidosPerdidos() const;
    void setPartidosPerdidos(unsigned short newPartidosPerdidos);
    Jugador* getConvocado(unsigned int i); //modificacion
    const Jugador* getConvocado(unsigned int i) const;  //solo lectura
};

#endif // EQUIPO_H
