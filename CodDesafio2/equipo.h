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
    unsigned short golesAFavorActual;
    unsigned short golesAFavorHist;
    unsigned short golesEnContra;
    unsigned short partidosGanados;
    unsigned short partidosEmpatados;
    unsigned short partidosPerdidos;
    short int prioridadSorteo;
    Jugador* convocados[26];
public:
    Equipo(unsigned short = 0, const char * const = "", const char * const = "", const char * const = "",
           const char * const = "", unsigned short = 0, unsigned short = 0, unsigned short = 0, unsigned short = 0,
           unsigned short = 0, unsigned short = 0);
    ~Equipo();

    const Equipo &operator=(const Equipo &);
    void elegirTitulares();

    unsigned short getRanking() const;
    void setRanking(unsigned short newRanking);
    const char* getPais() const;
    const char* getDt() const;
    const char* getFederacion() const;
    const char* getConfederacion() const;
    unsigned short getGolesEnContra() const;
    void setGolesEnContra(unsigned short newGolesEnContra);
    unsigned short getPartidosGanados() const;
    void setPartidosGanados(unsigned short newPartidosGanados);
    unsigned short getPartidosEmpatados() const;
    void setPartidosEmpatados(unsigned short newPartidosEmpatados);
    unsigned short getPartidosPerdidos() const;
    void setPartidosPerdidos(unsigned short newPartidosPerdidos);

    Jugador* getConvocado(unsigned int i);              // modificacion
    const Jugador* getConvocado(unsigned int i) const;  // solo lectura
    void setConvocado(unsigned int i, Jugador* jugador);

    short getPrioridadSorteo() const;
    void setPrioridadSorteo(short newPrioridadSorteo);

    unsigned short getGolesAFavorActual() const;
    void setGolesAFavorActual(unsigned short newGolesAFavorActual);

    unsigned short getGolesAFavorHist() const;
    void setGolesAFavorHist(unsigned short newGolesAFavorHist);
};

#endif // EQUIPO_H
