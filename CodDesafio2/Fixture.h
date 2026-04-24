#ifndef FIXTURE_H
#define FIXTURE_H

#include "equipo.h"

class Fixture {
private:
    Equipo** faseFixture;
    int cantidadActual;
    int ganadoresRegistrados;

    Equipo* perdedoresSemifinal[2];
    int cantidadPerdedoresSemifinal;

private:
    bool organizarR16();
    short int convertirConfederacionAIndice(const char* nombreConfederacion) const;
    const char* obtenerNombreConfederacionPorIndice(short int indice) const;

public:
    Fixture();
    Fixture(Equipo** equipos, int cantidad);

    void recibirEquiposFase(Equipo** equipos, int cantidad);

    bool organizarFixture();

    int getCantidadActual() const;
    int getCantidadPartidosActual() const;
    Equipo** getFaseFixture() const;

    bool obtenerParejaPartido(int numeroPartido, Equipo*& equipo1, Equipo*& equipo2) const;

    bool registrarGanadorPartido(int numeroPartido, Equipo* ganador);

    void registrarPerdedorSemifinal(Equipo* perdedor);
    bool obtenerParejaTercerPuesto(Equipo*& equipo1, Equipo*& equipo2) const;
    bool obtenerParejaFinal(Equipo*& equipo1, Equipo*& equipo2) const;

    int contarEquiposPorConfederacion(const char* nombreConfederacion) const;
    const char* obtenerConfederacionDominante(bool& hayEmpate, int& cantidadMaxima) const;

    const char* getNombreFaseActual() const;
};

#endif