#include <sstream>
#include <iostream>
#include "ModCargarActualizar.h"
using namespace std;

int main()
{
    Equipo* selecciones = nullptr;
    unsigned int cont = 0;
    try {
        selecciones = cargarEstadisticasSelecciones(cont);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
        delete [] selecciones;
        selecciones = nullptr;
        return 1;
    }

    if(selecciones != nullptr){
        selecciones[0].setPartidosEmpatados(3);
        selecciones[1].setPartidosEmpatados(3);
        selecciones[2].setPartidosEmpatados(3);
        selecciones[3].setPartidosEmpatados(3);
        selecciones[4].setPartidosEmpatados(3);
        selecciones[5].setPartidosEmpatados(3);
    }
    actualizarEstadisticasSelecciones(selecciones, cont);
    delete[] selecciones;
    selecciones = nullptr;
    return 0;
}
