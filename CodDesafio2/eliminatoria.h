#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "partido.h"

class Eliminatoria
{
private:
    Equipo** grupos[12];
    void conformarBombos(short int* );
    void conformarGrupos(Equipo* ,short int* );
    bool validarConfederacion(Equipo* ptrSelecciones, short int* ptrBombos,short int grupo, short int bombo);

public:
    Eliminatoria(Equipo* refSelecciones);
    ~Eliminatoria();
    void imprimirGruposConformados();
};

#endif // ELIMINATORIA_H
