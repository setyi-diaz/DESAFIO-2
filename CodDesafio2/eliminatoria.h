#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "partido.h"
#include <iomanip>
using std::setw;
using std::left;
using std::right;

class Eliminatoria
{
private:
    Equipo** grupos[12];

    void conformarBombos(short int* );
    void conformarGrupos(Equipo* ,short int* );
    bool validarConfederacion(Equipo* ptrSelecciones, short int* ptrBombos,short int grupo, short int bombo);
    void ordenarSubArreglo(unsigned short , unsigned short ,Equipo** );
    bool criterioDeDesempate(Equipo* a, Equipo* b);
    void combinar(unsigned short ,unsigned short ,unsigned short ,unsigned short ,Equipo** );
    void ordenar(unsigned short ,Equipo** ptr);

public:
    Eliminatoria(Equipo* );
    ~Eliminatoria();
    void imprimirGruposConformados();
    void simularPartidos();
    void ordenarGrupos();
    void imprimirTablaDeClasificacion();
};

#endif // ELIMINATORIA_H
