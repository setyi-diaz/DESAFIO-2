#include "ModCargarActualizar.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

Equipo* cargarEstadisticasSelecciones(unsigned short& contRef, unsigned short& refIndAnf) {
    ifstream archivoSelecciones("prueba.csv", ios::in);
    if (!archivoSelecciones.is_open())
        throw std::runtime_error("No se pudo abrir el archivo");

    string lineaDescarte;
    getline(archivoSelecciones, lineaDescarte);
    getline(archivoSelecciones, lineaDescarte);

    unsigned short ranking;
    char pais[25]={'\0'};
    char dt[20]={'\0'};
    char federacion[47]={'\0'};
    char confederacion[10]={'\0'};
    unsigned short golesAFavor;
    unsigned short golesEnContra;
    unsigned short partidosGanados;
    unsigned short partidosEmpatados;
    unsigned short partidosPerdidos;

    string linea, temp;
    linea.reserve(120);
    stringstream ss;

    while(getline(archivoSelecciones,linea))
        contRef++;

    archivoSelecciones.clear();
    archivoSelecciones.seekg(0, ios::beg);

    getline(archivoSelecciones, lineaDescarte);
    getline(archivoSelecciones, lineaDescarte);

    Equipo* selecciones = new Equipo [contRef];
    for (unsigned short i = 0; i < contRef; i++) {
        if (!getline(archivoSelecciones, linea)){
            cout<<"error en la lectura de una linea: "<<i<<endl;
            delete [] selecciones;
            selecciones = nullptr;
            break;
        }
        ss.str(linea);
        ss.clear();

        getline(ss, temp, ';');
        ranking = (unsigned short)stoi(temp);

        getline(ss, temp, ';');
        strncpy(pais, temp.c_str(), sizeof(pais) - 1);
        pais[sizeof(pais) - 1] = '\0';

        getline(ss, temp, ';');
        strncpy(dt, temp.c_str(), sizeof(dt) - 1);
        dt[sizeof(dt) - 1] = '\0';

        getline(ss, temp, ';');
        strncpy(federacion, temp.c_str(), sizeof(federacion) - 1);
        federacion[sizeof(federacion) - 1] = '\0';

        getline(ss, temp, ';');
        strncpy(confederacion, temp.c_str(), sizeof(confederacion) - 1);
        confederacion[sizeof(confederacion) - 1] = '\0';

        getline(ss, temp, ';');
        golesAFavor = (unsigned short)stoi(temp);
        getline(ss, temp, ';');
        golesEnContra = (unsigned short)stoi(temp);
        getline(ss, temp, ';');
        partidosGanados = (unsigned short)stoi(temp);
        getline(ss, temp, ';');
        partidosEmpatados = (unsigned short)stoi(temp);
        getline(ss, temp);
        partidosPerdidos = (unsigned short)stoi(temp);

        selecciones[i] = Equipo(ranking, pais, dt, federacion, confederacion,
                                golesAFavor, golesEnContra, partidosGanados,
                                partidosEmpatados, partidosPerdidos);
        if((string)pais == "United States") refIndAnf = i;
    }
    return selecciones;
}
void actualizarEstadisticasSelecciones(Equipo* selecciones, unsigned short& contRef){
    ofstream archivoSelecciones("prueba.csv", ios::out | ios::trunc);
    if (!archivoSelecciones.is_open())
        throw std::runtime_error("No se pudo abrir el archivo para escritura");

    // Escribir título y cabecera
    archivoSelecciones << "Selecciones clasificadas al Mundial de Fútbol 2026;;;;;;;;;\n";
    archivoSelecciones << "Ranking FIFA (1 abril 2026);País;Director técnico;"
                          "Federación de fútbol;Confederación;Goles a favor;"
                          "Goles en contra;Partidos ganados;Partidos empatados;"
                          "Partidos perdidos\n";
    for (unsigned short i = 0; i < contRef; i++) {
        if (selecciones == nullptr) {
            cout << "selecciones es nullptr\n";
        }
        //temp es una referencia a un Equipo
        const Equipo& temp = selecciones[i];

        cout<<temp.getRanking()<<endl;
        archivoSelecciones
            << temp.getRanking()          << ';'
            << (string)temp.getPais()             << ';'
            << (string)temp.getDt()               << ';'
            << (string)temp.getFederacion()       << ';'
            << (string)temp.getConfederacion()    << ';'
            << temp.getGolesAFavor()      << ';'
            << temp.getGolesEnContra()    << ';'
            << temp.getPartidosGanados()  << ';'
            << temp.getPartidosEmpatados()<< ';'
            << temp.getPartidosPerdidos() << '\n';
    }
}
