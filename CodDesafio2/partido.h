#ifndef PARTIDO_H
#define PARTIDO_H
#include "equipo.h"
#include <cmath>
#include <iostream>
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

    void calcularGoles();
    void calcularPosesion();
    void distribuirGoles();
    void distribuirTarjetas(double pPrimera = 0.06,double pSegunda = 0.0115);
    void distribuirFaltas(double p1 = 0.13,double p2 = 0.0275,double p3 = 0.007);

public:
    Partido();
    Partido(Equipo* eq1, Equipo* eq2,short int gEq1, short int gEq2,short int amEq1[11], short int amEq2[11],short int fEq1[11],
            short int fEq2[11],double pos);
    void simularPartido();
    void imprimirEstadisticasDelPartido();
};

#endif // PARTIDO_H
