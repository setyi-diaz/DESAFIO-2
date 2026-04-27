#include "fecha.h"
#include <iostream>

using namespace std;

short int Fecha::dia = 1;
short int Fecha::mes = 1;
short int Fecha::anio = 2026;

short int Fecha::getDia()
{
    return dia;
}

short int Fecha::getMes()
{
    return mes;
}

short int Fecha::getAnio()
{
    return anio;
}

bool Fecha::setFecha(short int nuevoDia, short int nuevoMes, short int nuevoAnio)
{
    short int diaAnterior = dia;
    short int mesAnterior = mes;
    short int anioAnterior = anio;

    dia = nuevoDia;
    mes = nuevoMes;
    anio = nuevoAnio;

    if (!esValida()) {
        dia = diaAnterior;
        mes = mesAnterior;
        anio = anioAnterior;
        return false;
    }

    return true;
}

bool Fecha::esValida()
{
    if (anio < 1) {
        return false;
    }

    if (mes < 1 || mes > 12) {
        return false;
    }

    if (dia < 1 || dia > diasDelMes()) {
        return false;
    }

    return true;
}

void Fecha::avanzarDia()
{
    dia++;

    if (dia > diasDelMes()) {
        dia = 1;
        mes++;

        if (mes > 12) {
            mes = 1;
            anio++;
        }
    }
}

void Fecha::imprimirFecha()
{
    if (dia < 10) {
        cout << "0";
    }

    cout << dia << "/";

    if (mes < 10) {
        cout << "0";
    }

    cout << mes << "/" << anio;
}

bool Fecha::esBisiesto()
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

short int Fecha::diasDelMes()
{
    switch (mes) {
    case 1:
        return 31;

    case 2:
        if (esBisiesto()) {
            return 29;
        }
        return 28;

    case 3:
        return 31;

    case 4:
        return 30;

    case 5:
        return 31;

    case 6:
        return 30;

    case 7:
        return 31;

    case 8:
        return 31;

    case 9:
        return 30;

    case 10:
        return 31;

    case 11:
        return 30;

    case 12:
        return 31;

    default:
        return 0;
    }
}