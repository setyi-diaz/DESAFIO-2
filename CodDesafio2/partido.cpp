#include "partido.h"
Partido::Partido(): equipo1(nullptr),equipo2(nullptr),golesEq1(0),golesEq2(0),posesion(50.0){
    for (short int i = 0; i < 11; i++) {
        amarillasEq1[i] = 0;
        amarillasEq2[i] = 0;
        faltasEq1[i]    = 0;
        faltasEq2[i]    = 0;
    }
}
Partido::Partido(Equipo* eq1, Equipo* eq2,short int gEq1, short int gEq2,short int amEq1[11], short int amEq2[11],short int fEq1[11],
                 short int fEq2[11],double pos): equipo1(eq1),equipo2(eq2),golesEq1(gEq1),golesEq2(gEq2),posesion(pos)
{
    for (short int i = 0; i < 11; i++) {
        amarillasEq1[i] = amEq1[i];
        amarillasEq2[i] = amEq2[i];
        faltasEq1[i]    = fEq1[i];
        faltasEq2[i]    = fEq2[i];
    }
}
void Partido::calcularGoles(){
    double mu = 1.35;
    double alpha = 0.6;
    double beta = 0.4;
    golesEq1 = mu*pow(equipo1->getGolesAFavor()/mu,alpha)*pow(equipo2->getGolesEnContra()/mu,beta);
    golesEq2 = mu*pow(equipo2->getGolesAFavor()/mu,alpha)*pow(equipo1->getGolesEnContra()/mu,beta);
}
void Partido::calcularPosesion(){
    double termino1 = 1 / equipo1->getRanking();
    double termino2 = 1 / equipo2->getRanking();
    posesion = 100 * (termino1/(termino1 + termino2));
}
void Partido::distribuirGoles(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10);

    for (unsigned short g1 = 0; g1 < golesEq1; ++g1) {
        int jugador = dis(gen);
        equipo1->getConvocado(jugador)->setGolesMarcados(1);
    }
    for (unsigned g2 = 0; g2 < golesEq2; ++g2) {
        int jugador = dis(gen);
        equipo2->getConvocado(jugador)->setGolesMarcados(1);
    }
}
void Partido::distribuirTarjetas(double pPrimera,double pSegunda) {
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
void Partido::simularPartido(){
    calcularGoles();
    calcularPosesion();
    equipo1->elegirTitulares();
    equipo2->elegirTitulares();
    distribuirGoles();
    distribuirFaltas();
    distribuirTarjetas();
}
void Partido::imprimirEstadisticasDelPartido(){
    unsigned short totalFaltasEq1 = 0;
    unsigned short totalFaltasEq2 = 0;
    unsigned short totalAmarillasEq1 = 0;
    unsigned short totalAmarillasEq2 = 0;
    unsigned short totalRojasEq1 = 0;
    unsigned short totalRojasEq2 = 0;
    cout<<"Equipo: "<<(string)(equipo1->getPais())<<"     "<<"vs"<<"    "<<"Equipo: "<<(string)(equipo2->getPais())<<endl;
    cout<<golesEq1<<"        "<<"marcador"<<"         "<<golesEq2<<endl;
    cout<<posesion<<"%        "<<"posesion"<<"        "<<(100.0 - posesion)<<"%"<<endl;
    for (unsigned short i = 0; i < 11; i++){
        totalFaltasEq1 += faltasEq1[i];
        totalFaltasEq2 += faltasEq2[i];
        totalAmarillasEq1 += amarillasEq1[i];
        if (amarillasEq1[i] == 2){
            totalRojasEq1 ++;
        }
        totalAmarillasEq2 += amarillasEq2[i];
        if (amarillasEq2[i] == 2){
            totalRojasEq2 ++;
        }
    }
    cout<<totalFaltasEq1<<"    "<<"faltas"<<"    "<<totalFaltasEq2<<endl;
    cout<<totalAmarillasEq1<<"    "<<"amarillas"<<"   "<<totalAmarillasEq2<<endl;
    cout<<totalRojasEq1<<"    "<<"rojas"<<"   "<<totalRojasEq2;
}
