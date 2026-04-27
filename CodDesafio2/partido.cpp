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
    golesEq1 = mu*pow(equipo1->getGolesAFavorHist()/mu,alpha)*pow(equipo2->getGolesEnContra()/mu,beta);
    golesEq2 = mu*pow(equipo2->getGolesAFavorHist()/mu,alpha)*pow(equipo1->getGolesEnContra()/mu,beta);

    equipo1->setGolesAFavorActual(golesEq1);
    equipo2->setGolesAFavorActual(golesEq2);

    equipo1->setGolesAFavorHist(golesEq1);
    equipo2->setGolesAFavorHist(golesEq2);

    equipo1->setGolesEnContra(golesEq2);
    equipo2->setGolesEnContra(golesEq1);
}
void Partido::calcularPosesion(){
    double termino1 = 1 / equipo1->getRanking();
    double termino2 = 1 / equipo2->getRanking();
    posesion = 100 * (termino1/(termino1 + termino2));
}
std::mt19937 Partido::gen(std::random_device{}());

void Partido::distribuirGoles(){
    std::uniform_int_distribution<> dis1(0, 10);
    std::uniform_int_distribution<> dis2(0, 10);

    for (short g1 = 0; g1 < golesEq1; ++g1) {
        Jugador* j = equipo1->getConvocado(dis1(gen));
        if (j != nullptr){
            j->setGolesMarcadosActual(1);
            j->setGolesMarcadosHist(1);
        }
    }
    for (short g2 = 0; g2 < golesEq2; ++g2) {
        Jugador* j = equipo2->getConvocado(dis2(gen));
        if (j != nullptr){
            j->setGolesMarcadosActual(1);
            j->setGolesMarcadosHist(1);
        }
    }
}
void Partido::distribuirTarjetas(double pPrimera,double pSegunda) {
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < 11; ++i) {
        Jugador* j = equipo1->getConvocado(i);
        if (j == nullptr) continue;

        if (amarillasEq1[i] == 0 && dis(gen) < pPrimera) {
            amarillasEq1[i] = 1;
            j->setAmarillas(1);
        }
        else if (amarillasEq1[i] == 1 && dis(gen) < pSegunda) {
            amarillasEq1[i] = 2;
            j->setAmarillas(1);
            j->setRojas(1);
        }
    }

    for (int i = 0; i < 11; ++i) {
        Jugador* j = equipo2->getConvocado(i);
        if (j == nullptr) continue;

        if (amarillasEq2[i] == 0 && dis(gen) < pPrimera) {
            amarillasEq2[i] = 1;
            j->setAmarillas(1);
        }
        else if (amarillasEq2[i] == 1 && dis(gen) < pSegunda) {
            amarillasEq2[i] = 2;
            j->setAmarillas(1);
            j->setRojas(1);
        }
    }
}
void Partido::distribuirFaltas(double p1,double p2,double p3) {
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < 11; ++i) {
        Jugador* j1 = equipo1->getConvocado(i);
        if (j1 == nullptr) continue;

        unsigned short estado = faltasEq1[i];
        if (estado == 0 && dis(gen) < p1){
            faltasEq1[i] = 1;
            j1->setFaltas(1);
        }
        else if (estado == 1 && dis(gen) < p2){
            faltasEq1[i] = 2;
            j1->setFaltas(1);
        }
        else if (estado == 2 && dis(gen) < p3){
            faltasEq1[i] = 3;
            j1->setFaltas(1);
        }
    }
    for (int i = 0; i < 11; ++i) {
        Jugador* j2 = equipo2->getConvocado(i);
        if (j2 == nullptr) continue;

        unsigned short estado = faltasEq2[i];
        if(estado == 0 && dis(gen) < p1) {
            faltasEq2[i] = 1;
            j2->setFaltas(1);
        }
        else if (estado == 1 && dis(gen) < p2) {
            faltasEq2[i] = 2;
            j2->setFaltas(1);
        }
        else if (estado == 2 && dis(gen) < p3) {
            faltasEq2[i] = 3;
            j2->setFaltas(1);
        }
    }
}
void Partido::simularPartido(Equipo* Eq1,Equipo* Eq2){
    if (Eq1 == nullptr || Eq2 == nullptr){
        cout<<"no se pudo simular el partido,punteros en nullptr\n";
        return;
    }
    equipo1 = Eq1;
    equipo2 = Eq2;

    calcularGoles();
    cout<<"calcularGoles\n";
    calcularPosesion();
    cout<<"calcularPosesion\n";
    equipo1->elegirTitulares();
    cout<<"elegirTitulares1\n";
    equipo2->elegirTitulares();
    cout<<"elegirTitulares2\n";
    distribuirGoles();
    cout<<"distribuirGoles\n";
    distribuirFaltas();
    cout<<"distribuirFaltas\n";
    distribuirTarjetas();
    cout<<"distribuirTarjetas\n";
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
