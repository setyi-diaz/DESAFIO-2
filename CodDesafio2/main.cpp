#include <sstream>
#include <iostream>
#include "ModCargarActualizar.h"
#include "eliminatoria.h"
using namespace std;

int main()
{
    Equipo* selecciones = nullptr;
    unsigned short cont = 0;
    unsigned short indAnfitrion = 0;
    try {
        selecciones = cargarEstadisticasSelecciones(cont,indAnfitrion);
        cargarEstadisticasJugadores(selecciones,cont);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
        delete [] selecciones;
        selecciones = nullptr;
        return 1;
    }
    Eliminatoria faseDeGrupos(selecciones);
    faseDeGrupos.imprimirGruposConformados();
    faseDeGrupos.ordenarGrupos();
    faseDeGrupos.imprimirGruposConformados();

    faseDeGrupos.simularPartidos();
    faseDeGrupos.imprimirTablaDeClasificacion();
    actualizarEstadisticasSelecciones(selecciones, cont);
    delete[] selecciones;
    selecciones = nullptr;
    return 0;
}
