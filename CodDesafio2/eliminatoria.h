#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "partido.h"

class Eliminatoria
{
private:
    Equipo** grupos[12];
    Partido partidoUno;
    Partido partidoDos;
    Partido partidoTres;
    Partido partidoCuatro;


    void conformarBombos(short int* );
    void conformarGrupos(Equipo* ,short int* );
    bool validarConfederacion(Equipo* ptrSelecciones, short int* ptrBombos,short int grupo, short int bombo);
    void ordenarSubArreglo(unsigned short , unsigned short ,Equipo** );
    bool esMayorOIgual(Equipo* a, Equipo* b);
    void combinar(unsigned short ,unsigned short ,unsigned short ,unsigned short ,Equipo** );
    void ordenar(unsigned short ,Equipo** ptr);

public:
    Eliminatoria(Equipo* );
    ~Eliminatoria();
    void imprimirGruposConformados();
    void simularPartidos();
    void ordenarGrupos();
};

#endif // ELIMINATORIA_H
