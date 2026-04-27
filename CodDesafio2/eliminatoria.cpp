#include "eliminatoria.h"
#include "fecha.h"
#include <iostream>
#include <random>
#include "ModContadorRecursos.h"

Eliminatoria::Eliminatoria(Equipo* ptrSelecciones){
    for (int i = 0; i < 12; ++i){
        ContadorRecursos::registrarIteracion();
        grupos[i] = new Equipo* [4];
        ContadorRecursos::reservarMemoria(grupos[i], 4);
    }
    short int bombos[48];
    conformarBombos(bombos);
    conformarGrupos(ptrSelecciones,bombos);
}
Eliminatoria::~Eliminatoria() {
    for (int i = 0; i < 12; ++i){
        ContadorRecursos::registrarIteracion();
        ContadorRecursos::liberarMemoria(grupos[i], 4);
        delete[] grupos[i];
    }
}
void Eliminatoria::conformarBombos(short int* ptrBombos){

    for (short int i = 0; i<48; i++ ){
        ContadorRecursos::registrarIteracion();
        ptrBombos[i] = i;
    }
}
void Eliminatoria::conformarGrupos(Equipo* ptrSelecciones, short int* ptrBombos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    short int temp;
    bool bomboValido = false;

    while(!bomboValido){
        ContadorRecursos::registrarIteracion();
        // se mezclan los equipos uniformemente en el arreglo bombos
        for (short int k = 0; k < 4; k++) {
            ContadorRecursos::registrarIteracion();
            short int despl = k * 12;
            for (short int i = 11; i > 0; i--) {
                ContadorRecursos::registrarIteracion();
                std::uniform_int_distribution<unsigned int> dist(0, i);
                unsigned int j = dist(gen);
                temp = ptrBombos[i + despl];
                ptrBombos[i + despl] = ptrBombos[j + despl];
                ptrBombos[j + despl] = temp;
            }
        }
        for (short int i = 0; i < 12; i++) {
            ContadorRecursos::registrarIteracion();
            grupos[i][0] = &ptrSelecciones[ptrBombos[i]];
        }

        for (short int k = 1; k < 4; k++) {
            ContadorRecursos::registrarIteracion();
            short int despl = k * 12;
            int maxReintentos = 1000;
            bomboValido = false;

            while (!bomboValido && maxReintentos-- > 0) {
                ContadorRecursos::registrarIteracion();

                // Re-mezclar el bombo k completo
                for (short int i = 11; i > 0; i--) {
                    ContadorRecursos::registrarIteracion();
                    std::uniform_int_distribution<unsigned int> dist(0, i);
                    unsigned int j = dist(gen);
                    temp = ptrBombos[i + despl];
                    ptrBombos[i + despl] = ptrBombos[j + despl];
                    ptrBombos[j + despl] = temp;
                }

                bomboValido = true;
                for (short int i = 0; i < 12; i++) {
                    ContadorRecursos::registrarIteracion();
                    if (validarConfederacion(ptrSelecciones, ptrBombos, i, k)) {
                        bomboValido = false;
                        break;
                    }
                }
            }

            if (!bomboValido) {
                std::cout << "ERROR: no se encontro permutacion valida para bombo "
                          << k << " tras 1000 intentos\n";
                break;
            }
            else{
                for (short int i = 0; i < 12; i++) {
                    ContadorRecursos::registrarIteracion();
                    grupos[i][k] = &ptrSelecciones[ptrBombos[i + despl]];
                }
            }
        }
    }
    for(short int s = 0; s<12; s++){
        ContadorRecursos::registrarIteracion();
        if((string)((*grupos[s][1]).getPais()) == "United States"){
            Equipo** temp = grupos[0];
            grupos[0] = grupos[s];
            grupos[s] = temp;
        }
    }
}
bool Eliminatoria::validarConfederacion(Equipo* ptrSelecciones, short int* ptrBombos,
                                short int grupo, short int bombo) {
    string confActual = (string)ptrSelecciones[ptrBombos[grupo + bombo * 12]]
                            .getConfederacion();

    short int contUEFA = 0;

    for (short int b = 0; b < bombo; b++) {
        ContadorRecursos::registrarIteracion();
        string confAnterior = (string)ptrSelecciones[ptrBombos[grupo + b * 12]]
                                  .getConfederacion();

        if (confActual == confAnterior) {
            if (confActual != "UEFA") {
                return true;
            }
            contUEFA++;
        }
    }

    if (confActual == "UEFA" && contUEFA >= 2) {
        return true;
    }

    return false;
}
void Eliminatoria::imprimirGruposConformados(){
    for (short i = 0; i<12; i++){
        ContadorRecursos::registrarIteracion();
        cout<<"Grupo: "<<i<<endl;
        for (short j = 0; j<4; j++){
            ContadorRecursos::registrarIteracion();
            cout<<"Seleccion: "<<(string)(grupos[i][j]->getPais())
                      <<"  confederacion: "<<(string)(grupos[i][j]->getConfederacion())<<endl;
        }
    }
}
void Eliminatoria::simularPartidos(){
    const unsigned short parejas[3][2][2] = {
        { {0, 1}, {2, 3} },
        { {0, 2}, {1, 3} },
        { {0, 3}, {1, 2} }
    };

    for (unsigned short jornada = 0; jornada < 3; jornada++) {
        ContadorRecursos::registrarIteracion();

        for (unsigned short g = 0; g < 12; g++) {
            ContadorRecursos::registrarIteracion();

            unsigned short diaOffset = (g / 2) + (jornada * 6);

            for (unsigned short p = 0; p < 2; p++) {
                ContadorRecursos::registrarIteracion();

                unsigned short indiceEq1 = parejas[jornada][p][0];
                unsigned short indiceEq2 = parejas[jornada][p][1];

                Fecha::setFecha(20, 6, 2026);
                Fecha::avanzarDias(diaOffset);

                Partido jogo;
                jogo.configurarDatosPartido();

                cout << "\nGrupo " << char('A' + g)
                     << " - Jornada " << jornada + 1
                     << " - Partido " << p + 1 << ": "
                     << grupos[g][indiceEq1]->getPais()
                     << " vs "
                     << grupos[g][indiceEq2]->getPais()
                     << "\n";

                jogo.simularPartido(grupos[g][indiceEq1], grupos[g][indiceEq2]);
                jogo.imprimirEstadisticasDelPartido();
            }
        }
    }
}
void Eliminatoria::ordenar(unsigned short len,Equipo** ptr){
    if (len > 1)
        ordenarSubArreglo(0, len - 1, ptr);
}
void Eliminatoria::ordenarSubArreglo(unsigned short inferior, unsigned short superior,Equipo** ptr){
    if(superior > inferior){
        unsigned short medio1 = (superior + inferior) / 2;
        unsigned short medio2 = medio1 + 1;

        ordenarSubArreglo(inferior,medio1,ptr);
        ordenarSubArreglo(medio2,superior,ptr);
        combinar(inferior, medio1, medio2, superior,ptr);
    }
}
bool Eliminatoria::criterioDeDesempate(Equipo* a, Equipo* b) {
    unsigned short puntosA = (a->getPartidosGanados() * 3) + a->getPartidosEmpatados();
    unsigned short puntosB = (b->getPartidosGanados() * 3) + b->getPartidosEmpatados();
    if (puntosA != puntosB)
        return puntosA > puntosB;

    short difA = a->getGolesAFavorActual() - a->getGolesEnContra();
    short difB = b->getGolesAFavorActual() - b->getGolesEnContra();
    if (difA != difB)
        return difA > difB;

    if (a->getGolesAFavorActual() != b->getGolesAFavorActual())
        return a->getGolesAFavorActual() > b->getGolesAFavorActual();

    return a->getPrioridadSorteo() > b->getPrioridadSorteo();
}
void Eliminatoria::combinar(unsigned short izquirdo, unsigned short medio1, unsigned short medio2, unsigned short derecho,Equipo** ptr){
    unsigned short indiceIzq = izquirdo;
    unsigned short indiceDer = medio2;
    unsigned short indiceCombinado = 0;
    unsigned short size = derecho - izquirdo + 1;
    Equipo** temp = new Equipo*[size];
    ContadorRecursos::reservarMemoria(temp, size);

    while( indiceIzq <= medio1 && indiceDer <= derecho){
        ContadorRecursos::registrarIteracion();
        if (criterioDeDesempate(ptr[indiceIzq],ptr[indiceDer]))
            temp[indiceCombinado++] = ptr[indiceIzq++];
        else
            temp[indiceCombinado++] = ptr[indiceDer++];
    }
    while (indiceIzq <= medio1) {
        ContadorRecursos::registrarIteracion();
        temp[indiceCombinado++] = ptr[indiceIzq++];
    }

    while (indiceDer <= derecho) {
        ContadorRecursos::registrarIteracion();
        temp[indiceCombinado++] = ptr[indiceDer++];
    }

    for(unsigned short i = 0; i < size; i++){
        ContadorRecursos::registrarIteracion();
        ptr[izquirdo + i] = temp[i];
    }
    ContadorRecursos::liberarMemoria(temp, size);
    delete[] temp;
}
void Eliminatoria::ordenarGrupos(){
    srand(time(nullptr));
    for (unsigned short i = 0; i < 12; i++) {
        ContadorRecursos::registrarIteracion();
        for (unsigned short j = 0; j < 4; j++) {
            ContadorRecursos::registrarIteracion();
            grupos[i][j]->setPrioridadSorteo(rand() % 1000);
        }
        ordenar(4, grupos[i]);
    }
}
void Eliminatoria::imprimirTablaDeClasificacion(){
    short difGoles;
    unsigned short partidosJugados;
    unsigned short puntos;

    for (short i = 0; i < 12; i++) {
        ContadorRecursos::registrarIteracion();
        cout << "\n||=======================================================||\n";
        cout << "||  GRUPO " << (char)('A' + i)
             << "                                              ||\n";
        cout << "||=======================================================||\n";
        cout << "|| " << left  << setw(22) << "SELECCION"
             << right << setw(5)  << "PJ"
             << setw(5)  << "PG"
             << setw(5)  << "PE"
             << setw(5)  << "PP"
             << setw(5)  << "DG"
             << setw(6)  << "PTS"
             << " ||\n";
        cout << "||=======================================================||\n";

        // Filas de equipos
        for (short j = 0; j < 4; j++) {
            ContadorRecursos::registrarIteracion();
            partidosJugados = grupos[i][j]->getPartidosGanados()
            + grupos[i][j]->getPartidosEmpatados()
                + grupos[i][j]->getPartidosPerdidos();

            difGoles = grupos[i][j]->getGolesAFavorActual()
                       - grupos[i][j]->getGolesEnContra();

            puntos = (grupos[i][j]->getPartidosGanados() * 3)
                     +  grupos[i][j]->getPartidosEmpatados();

            string posicion;
            switch(j) {
            case 0: posicion = "1."; break;
            case 1: posicion = "2."; break;
            case 2: posicion = "3."; break;
            case 3: posicion = "4."; break;
            }

            cout << "|| " << left  << setw(3)  << posicion
                 << left  << setw(19) << (string)grupos[i][j]->getPais()
                 << right << setw(5)  << partidosJugados
                 << setw(5)  << grupos[i][j]->getPartidosGanados()
                 << setw(5)  << grupos[i][j]->getPartidosEmpatados()
                 << setw(5)  << grupos[i][j]->getPartidosPerdidos()
                 << setw(5)  << difGoles
                 << setw(6)  << puntos
                 << " ||\n";
        }
        cout << "||=======================================================||\n";
    }
}













