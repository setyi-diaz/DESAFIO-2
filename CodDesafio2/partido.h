#ifndef PARTIDO_H
#define PARTIDO_H
#include "equipo.h"
#include <cmath>

class Partido
{
private:
    Equipo* equipo1;
    Equipo* equipo2;
    short int amarillasEq1[11];
    short int amarillasEq2[11];
    short int faltasEq1[11];
    short int faltasEq2[11];
public:
    Partido();
    void calcularGoles(unsigned short& ,unsigned short& );
    void calcularPosesion(double& posesion);
    void distribuirGoles(unsigned short& refGoles1,unsigned short& refGoles2);
    void distribuirAmarillas(double pPrimera = 0.06,double pSegunda = 0.0115);
    void distribuirFaltas(double p1 = 0.13,double p2 = 0.0275,double p3 = 0.007);
};

#endif // PARTIDO_H
