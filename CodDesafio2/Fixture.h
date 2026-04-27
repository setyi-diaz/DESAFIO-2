#ifndef FIXTURE_H
#define FIXTURE_H

#include "equipo.h"

class Fixture {
private:
    Equipo** faseFixture;
    Equipo* arregloFixtureInterno[32];

    int cantidadActual;
    int ganadoresRegistrados;

    Equipo* perdedoresSemifinal[2];
    int cantidadPerdedoresSemifinal;

private:
    bool filaValida(short int fila) const;
    bool validarFilasSinRepetir(const short int filas[], int cantidad) const;

    short int convertirConfederacionAIndice(const char* nombreConfederacion) const;
    const char* obtenerNombreConfederacionPorIndice(short int indice) const;

public:
    Fixture();

    bool organizarR16DesdeGrupos(
        Equipo* grupos[12][4],
        const short int mejoresTerceros[8],
        const short int peoresSegundos[4]
        );

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