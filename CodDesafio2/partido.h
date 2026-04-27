#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>

using std::setw;
using std::cout;
using std::endl;

class Partido
{
private:
    Equipo* equipo1;
    Equipo* equipo2;
    short int golesEq1;
    short int golesEq2;
    short int amarillasEq1[11];
    short int amarillasEq2[11];
    short int faltasEq1[11];
    short int faltasEq2[11];
    double posesion;

    char fechaPartido[11];
    char horaPartido[6];
    char sede[30];
    char arbitro1[20];
    char arbitro2[20];
    char arbitro3[20];
    bool prorroga;

    static std::mt19937 gen;

    void calcularGoles();
    void calcularPosesion();
    void distribuirGoles();
    void distribuirTarjetas(double pPrimera = 0.06, double pSegunda = 0.0115);
    void distribuirFaltas(double p1 = 0.13, double p2 = 0.0275, double p3 = 0.007);
    void copiarTexto(char destino[], unsigned short capacidad, const char* origen);
    void inicializarDatosAdministrativos();
    void reiniciarEstadisticasPartido();
    void sumarMinutosJugadores(unsigned short minutos);

public:
    Partido();
    Partido(Equipo* eq1, Equipo* eq2, short int gEq1, short int gEq2, short int amEq1[11], short int amEq2[11], short int fEq1[11],
            short int fEq2[11], double pos);

    void configurarDatosPartido(const char* nuevaSede = "nombreSede",
                                const char* nuevaHora = "00:00",
                                const char* nuevoArbitro1 = "codArbitro1",
                                const char* nuevoArbitro2 = "codArbitro2",
                                const char* nuevoArbitro3 = "codArbitro3");

    void simularPartido(Equipo*, Equipo*);
    void simularPartido();
    Equipo* simularPartido(Equipo* eq1, Equipo* eq2, unsigned short rankingEq1, unsigned short rankingEq2);
    void imprimirEstadisticasDelPartido();

    const char* getFechaPartido() const;
    const char* getHoraPartido() const;
    const char* getSede() const;
    bool fueProrroga() const;
};

#endif // PARTIDO_H
