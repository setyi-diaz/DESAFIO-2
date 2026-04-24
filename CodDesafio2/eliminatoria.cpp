#include "eliminatoria.h"
#include <iostream>
#include <random>

Eliminatoria::Eliminatoria(Equipo* ptrSelecciones) {
    for (int i = 0; i < 12; ++i){
        grupos[i] = new Equipo* [4];
    }
    short int bombos[48];
    conformarBombos(bombos);
    conformarGrupos(ptrSelecciones,bombos);
}
void Eliminatoria::conformarBombos(short int* ptrBombos){

    for (short int i = 0; i<48; i++ ){
        ptrBombos[i] = i;
    }
}
void Eliminatoria::conformarGrupos(Equipo* ptrSelecciones, short int* ptrBombos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    short int temp;

    // se mezclan los equipos uniformemente en el arreglo bombos
    for (short int k = 0; k < 4; k++) {
        short int despl = k * 12;
        for (short int i = 11; i > 0; i--) {
            std::uniform_int_distribution<unsigned int> dist(0, i);
            unsigned int j = dist(gen);
            temp = ptrBombos[i + despl];
            ptrBombos[i + despl] = ptrBombos[j + despl];
            ptrBombos[j + despl] = temp;
        }
    }

    for (short int i = 0; i < 12; i++) {
        grupos[i][0] = &ptrSelecciones[ptrBombos[i]];
    }

    for (short int k = 1; k < 4; k++) {
        short int despl = k * 12;
        int maxReintentos = 1000;
        bool bomboValido = false;

        while (!bomboValido && maxReintentos-- > 0) {

            // Re-mezclar el bombo k completo
            for (short int i = 11; i > 0; i--) {
                std::uniform_int_distribution<unsigned int> dist(0, i);
                unsigned int j = dist(gen);
                temp = ptrBombos[i + despl];
                ptrBombos[i + despl] = ptrBombos[j + despl];
                ptrBombos[j + despl] = temp;
            }

            bomboValido = true;
            for (short int i = 0; i < 12; i++) {
                if (validarConfederacion(ptrSelecciones, ptrBombos, i, k)) {
                    bomboValido = false;
                    break;
                }
            }
        }

        if (!bomboValido) {
            std::cout << "ERROR: no se encontró permutación válida para bombo "
                      << k << " tras 1000 intentos\n";
            return;
        }

        for (short int i = 0; i < 12; i++) {
            grupos[i][k] = &ptrSelecciones[ptrBombos[i + despl]];
        }
    }
}
bool Eliminatoria::validarConfederacion(Equipo* ptrSelecciones, short int* ptrBombos,
                                short int grupo, short int bombo) {
    string confActual = (string)ptrSelecciones[ptrBombos[grupo + bombo * 12]]
                            .getConfederacion();

    short int contUEFA = 0;

    for (short int b = 0; b < bombo; b++) {
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
        std::cout<<"Grupo: "<<i<<std::endl;
        for (short j = 0; j<4; j++){
            std::cout<<"Seleccion: "<<(string)(grupos[i][j]->getPais())
                      <<"  confederacion: "<<(string)(grupos[i][j]->getConfederacion())<<std::endl;
        }
    }
}
Eliminatoria::~Eliminatoria() {
    for (int i = 0; i < 12; ++i){
        delete[] grupos[i];
    }
}



















