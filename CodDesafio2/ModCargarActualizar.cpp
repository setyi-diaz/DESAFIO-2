#include "ModCargarActualizar.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

void cargarEstadisticasSelecciones(Equipo (&selecciones)[3]) {
    ifstream archivoSelecciones("prueba.txt", ios::in);
    if (!archivoSelecciones.is_open())
        throw std::runtime_error("No se pudo abrir el archivo");

    string lineaDescarte;

    // Saltar línea 1 (título) y línea 2 (cabecera)
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
    size_t len;

    for (short i = 0; i < 3; i++) {
        if (!getline(archivoSelecciones, linea)){
            cout<<"error en la lectura de una linea del archivo"<<endl;
            break;
        }

        ss.str(linea);
        ss.clear();

        getline(ss, temp, ';');
        ranking = (unsigned short)stoi(temp);
        // Leer campos de texto separados por ';'

        getline(ss, temp, ';'); len = temp.length();
        memcpy(pais, temp.c_str(), len + 1);

        getline(ss, temp, ';'); len = temp.length();
        memcpy(dt, temp.c_str(), len + 1);

        getline(ss, temp, ';'); len = temp.length();
        memcpy(federacion, temp.c_str(), len + 1);

        getline(ss, temp, ';'); len = temp.length();
        memcpy(confederacion, temp.c_str(), len + 1);

        // Leer campos numéricos separados por ';'
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

        // Crear y asignar al arreglo cada equipo
        selecciones[i] = Equipo(ranking, pais, dt, federacion, confederacion,
                                golesAFavor, golesEnContra, partidosGanados,
                                partidosEmpatados, partidosPerdidos);
    }
}
void actualizarEstadisticasSelecciones(Equipo (&selecciones)[3]){
    ofstream archivoSelecciones("prueba.txt", ios::out | ios::trunc);
    if (!archivoSelecciones.is_open())
        throw std::runtime_error("No se pudo abrir el archivo para escritura");

    // Escribir título y cabecera
    archivoSelecciones << "Selecciones clasificadas al Mundial de Fútbol 2026;;;;;;;;;\n";
    archivoSelecciones << "Ranking FIFA (1 abril 2026);País;Director técnico;"
                          "Federación de fútbol;Confederación;Goles a favor;"
                          "Goles en contra;Partidos ganados;Partidos empatados;"
                          "Partidos perdidos\n";
    for (short i = 0; i < 3; i++) {

        //temp es una referncia a un Equipo
        const Equipo& temp = selecciones[i];

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
