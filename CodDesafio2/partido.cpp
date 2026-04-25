#include "partido.h"

Partido::Partido() {
    amarillasEq1[11] = {0};
    amarillasEq2[11] = {0};
    faltasEq1[11] = {0};
    faltasEq2[11] = {0};
}
void Partido::calcularGoles(unsigned short& refGoles1,unsigned short& refGoles2){
    double mu = 1.35;
    double alpha = 0.6;
    double beta = 0.4;
    refGoles1 = mu*pow(equipo1->getGolesAFavor()/mu,alpha)*pow(equipo2->getGolesEnContra()/mu,beta);
    refGoles2 = mu*pow(equipo2->getGolesAFavor()/mu,alpha)*pow(equipo1->getGolesEnContra()/mu,beta);
}
void Partido::calcularPosesion(double& posesion){
    double termino1 = 1 / equipo1->getRanking();
    double termino2 = 1 / equipo2->getRanking();
    posesion = 100 * (termino1/(termino1 + termino2));
}
void Partido::distribuirGoles(unsigned short& refGoles1,unsigned short& refGoles2){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10);

    for (unsigned short g1 = 0; g1 < refGoles1; ++g1) {
        int jugador = dis(gen);
        equipo1->getConvocado(jugador)->setGolesMarcados(1);
    }
    for (unsigned g2 = 0; g2 < refGoles2; ++g2) {
        int jugador = dis(gen);
        equipo2->getConvocado(jugador)->setGolesMarcados(1);
    }
}
void Partido::distribuirAmarillas(double pPrimera,double pSegunda) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < 11; ++i) {
        if (amarillasEq1[i] == 0) {
            if (dis(gen) < pPrimera) {
                amarillasEq1[i] = 1;
                equipo1->getConvocado(i)->setAmarillas(1);
            }
        }
        else if (amarillasEq1[i] == 1) {
            if (dis(gen) < pSegunda) {
                amarillasEq1[i] = 2;
                equipo1->getConvocado(i)->setAmarillas(1);
                equipo1->getConvocado(i)->setRojas(1);
            }
        }
        if (amarillasEq2[i] == 0) {
            if (dis(gen) < pPrimera) {
                amarillasEq2[i] = 1;
                equipo2->getConvocado(i)->setAmarillas(1);
            }
        }
        else if (amarillasEq2[i] == 1) {
            if (dis(gen) < pSegunda) {
                amarillasEq2[i] = 2;
                equipo2->getConvocado(i)->setAmarillas(1);
                equipo2->getConvocado(i)->setRojas(1);
            }
        }
    }
}
void Partido::distribuirFaltas(double p1,double p2,double p3) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < 11; ++i) {
        if (faltasEq1[i] == 0 && dis(gen) < p1) {
            faltasEq1[i] = 1;
            equipo1->getConvocado(i)->setFaltas(1);
        }
        else if (faltasEq1[i] == 1 && dis(gen) < p2) {
            faltasEq1[i] = 2;
            equipo1->getConvocado(i)->setFaltas(1);
        }
        else if (faltasEq1[i] == 2 && dis(gen) < p3) {
            faltasEq1[i] = 3;
            equipo1->getConvocado(i)->setFaltas(1);
        }
        if (faltasEq2[i] == 0 && dis(gen) < p1) {
            faltasEq2[i] = 1;
            equipo2->getConvocado(i)->setFaltas(1);
        }
        else if (faltasEq2[i] == 1 && dis(gen) < p2) {
            faltasEq2[i] = 2;
            equipo2->getConvocado(i)->setFaltas(1);
        }
        else if (faltasEq2[i] == 2 && dis(gen) < p3) {
            faltasEq2[i] = 3;
            equipo2->getConvocado(i)->setFaltas(1);
        }
    }
}
