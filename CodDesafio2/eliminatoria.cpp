#include "eliminatoria.h"
#include <iostream>
#include <random>

Eliminatoria::Eliminatoria(Equipo* ptrSelecciones){
    for (int i = 0; i < 12; ++i){
        grupos[i] = new Equipo* [4];
    }
    short int bombos[48];
    conformarBombos(bombos);
    conformarGrupos(ptrSelecciones,bombos);
}
Eliminatoria::~Eliminatoria() {
    for (int i = 0; i < 12; ++i){
        delete[] grupos[i];
    }
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
            break;
        }

        for (short int i = 0; i < 12; i++) {
            grupos[i][k] = &ptrSelecciones[ptrBombos[i + despl]];
        }
    }
    for(short int s = 0; s<12; s++){
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
void Eliminatoria::simularPartidos(){
    for(unsigned short i = 0; i < 4; i++){
        for(unsigned short j = i + 1; j < 4; j++){
            for(unsigned short k = 0; k < 3; k++){
                if(k == 0){
                    // partidoUno(grupos[0][i],grupos[0][j]).simularPartido();
                    // partidoDos(grupos[1][i],grupos[1][j]).simularPartido();
                    // partidoTres(grupos[2][i],grupos[2][j]).simularPartido();
                    // partidoCuatro(grupos[3][i],grupos[3][j]).simularPartido();
                }
                else if (k == 1){

                }
            }
        }
    }
}
void Eliminatoria::ordenar(unsigned short len){
    for (unsigned short i = 0; i < 12; i++){
        ordenarSubArreglo(0, len - 1, grupos[i]);
    }
}
void Eliminatoria::ordenarSubArreglo(unsigned short inferior, unsigned short superior,Equipo** ptr){
    if((superior - inferior) >= 1){
        unsigned short medio1 = (superior + inferior) / 2;
        unsigned short medio2 = medio1 + 1;

        ordenarSubArreglo(inferior,medio1,ptr);
        ordenarSubArreglo(medio2,superior,ptr);
        combinar(inferior, medio1, medio2, superior,ptr);
    }
}
void Eliminatoria::combinar(unsigned short izquirdo, unsigned short medio1, unsigned short medio2, unsigned short derecho,Equipo** ptr){
    unsigned short indiceIzq = izquirdo;
    unsigned short indiceDer = medio2;
    unsigned short indiceCombinado = izquirdo;
    unsigned short size = derecho - izquirdo + 1;
    Equipo** temp = new Equipo*[size];

    while( indiceIzq <= medio1 && indiceDer <= derecho){
        if (ptr[indiceIzq]->getPartidosGanados() <= ptr[indiceDer]->getPartidosGanados())
            temp[indiceCombinado++] = ptr[indiceIzq++];
        else
            temp[indiceCombinado++] = ptr[indiceDer++];
    }
    if(indiceIzq > medio1){
        while( indiceDer <= derecho){
            temp[indiceCombinado++] = ptr[indiceDer++];
        }
    }
    else{
        while(indiceIzq <= medio1){
            temp[indiceCombinado++] = ptr[indiceIzq++];
        }
    }
    for(unsigned short i = 0; i < size; i++){
        ptr[izquirdo + i] = temp[i];
    }
    delete[] temp;
}















