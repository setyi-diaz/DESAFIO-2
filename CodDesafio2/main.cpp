#include <sstream>
#include <iostream>
#include "ModCargarActualizar.h"
using namespace std;

int main()
{
    Equipo selecciones[3];
    try {
        cargarEstadisticasSelecciones(selecciones);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
        return 1;
    }
    selecciones[0].setPartidosEmpatados(2);
    selecciones[1].setPartidosEmpatados(2);
    selecciones[2].setPartidosEmpatados(2);
    actualizarEstadisticasSelecciones(selecciones);

    return 0;
}
