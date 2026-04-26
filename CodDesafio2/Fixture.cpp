#include "fixture.h"
#include <cstring>

using std::strcmp;

Fixture::Fixture() {
    faseFixture = 0;
    cantidadActual = 0;
    ganadoresRegistrados = 0;

    for (int i = 0; i < 32; i++) {
        arregloFixtureInterno[i] = 0;
    }

    perdedoresSemifinal[0] = 0;
    perdedoresSemifinal[1] = 0;
    cantidadPerdedoresSemifinal = 0;
}

bool Fixture::filaValida(short int fila) const {
    return fila >= 0 && fila < 12;
}

bool Fixture::validarFilasSinRepetir(const short int filas[], int cantidad) const {
    if (filas == 0) {
        return false;
    }

    for (int i = 0; i < cantidad; i++) {
        if (!filaValida(filas[i])) {
            return false;
        }

        for (int j = i + 1; j < cantidad; j++) {
            if (filas[i] == filas[j]) {
                return false;
            }
        }
    }

    return true;
}

bool Fixture::organizarR16DesdeGrupos(
    Equipo* grupos[12][4],
    const short int mejoresTerceros[8],
    const short int peoresSegundos[4]
    ) {
    if (grupos == 0 || mejoresTerceros == 0 || peoresSegundos == 0) {
        return false;
    }

    if (!validarFilasSinRepetir(mejoresTerceros, 8)) {
        return false;
    }

    if (!validarFilasSinRepetir(peoresSegundos, 4)) {
        return false;
    }

    bool primeroUsado[12];
    bool segundoUsado[12];
    bool esPeorSegundo[12];

    for (int i = 0; i < 12; i++) {
        primeroUsado[i] = false;
        segundoUsado[i] = false;
        esPeorSegundo[i] = false;
    }

    for (int i = 0; i < 4; i++) {
        esPeorSegundo[peoresSegundos[i]] = true;
    }

    for (int i = 0; i < 32; i++) {
        arregloFixtureInterno[i] = 0;
    }

    int libre = 0;

    // 1) Ocho partidos: cabeza de grupo vs tercer puesto clasificado.
    for (int i = 0; i < 8; i++) {
        short int filaTercero = mejoresTerceros[i];

        if (!filaValida(filaTercero) || grupos[filaTercero][2] == 0) {
            return false;
        }

        short int filaPrimeroElegido = -1;

        for (short int filaPrimero = 0; filaPrimero < 12; filaPrimero++) {
            if (!primeroUsado[filaPrimero] &&
                filaPrimero != filaTercero &&
                grupos[filaPrimero][0] != 0) {
                filaPrimeroElegido = filaPrimero;
                break;
            }
        }

        if (filaPrimeroElegido == -1) {
            return false;
        }

        arregloFixtureInterno[libre] = grupos[filaPrimeroElegido][0];
        arregloFixtureInterno[libre + 1] = grupos[filaTercero][2];

        primeroUsado[filaPrimeroElegido] = true;
        libre += 2;
    }

    // 2) Cuatro partidos: cabezas de grupo restantes vs 4 peores segundos.
    for (int i = 0; i < 4; i++) {
        short int filaSegundo = peoresSegundos[i];

        if (!filaValida(filaSegundo) || grupos[filaSegundo][1] == 0) {
            return false;
        }

        short int filaPrimeroElegido = -1;

        for (short int filaPrimero = 0; filaPrimero < 12; filaPrimero++) {
            if (!primeroUsado[filaPrimero] &&
                filaPrimero != filaSegundo &&
                grupos[filaPrimero][0] != 0) {
                filaPrimeroElegido = filaPrimero;
                break;
            }
        }

        if (filaPrimeroElegido == -1) {
            return false;
        }

        arregloFixtureInterno[libre] = grupos[filaPrimeroElegido][0];
        arregloFixtureInterno[libre + 1] = grupos[filaSegundo][1];

        primeroUsado[filaPrimeroElegido] = true;
        libre += 2;
    }

    // 3) Los segundos restantes se enfrentan entre sí.
    while (libre < 32) {
        short int filaSegundo1 = -1;

        for (short int fila = 0; fila < 12; fila++) {
            if (!esPeorSegundo[fila] &&
                !segundoUsado[fila] &&
                grupos[fila][1] != 0) {
                filaSegundo1 = fila;
                break;
            }
        }

        if (filaSegundo1 == -1) {
            return false;
        }

        segundoUsado[filaSegundo1] = true;

        short int filaSegundo2 = -1;

        for (short int fila = 0; fila < 12; fila++) {
            if (!esPeorSegundo[fila] &&
                !segundoUsado[fila] &&
                fila != filaSegundo1 &&
                grupos[fila][1] != 0) {
                filaSegundo2 = fila;
                break;
            }
        }

        if (filaSegundo2 == -1) {
            return false;
        }

        segundoUsado[filaSegundo2] = true;

        arregloFixtureInterno[libre] = grupos[filaSegundo1][1];
        arregloFixtureInterno[libre + 1] = grupos[filaSegundo2][1];

        libre += 2;
    }

    faseFixture = arregloFixtureInterno;
    cantidadActual = 32;
    ganadoresRegistrados = 0;

    perdedoresSemifinal[0] = 0;
    perdedoresSemifinal[1] = 0;
    cantidadPerdedoresSemifinal = 0;

    return true;
}

bool Fixture::organizarFixture() {
    if (faseFixture == 0 || cantidadActual < 2) {
        return false;
    }

    ganadoresRegistrados = 0;
    return true;
}

int Fixture::getCantidadActual() const {
    return cantidadActual;
}

int Fixture::getCantidadPartidosActual() const {
    return cantidadActual / 2;
}

Equipo** Fixture::getFaseFixture() const {
    return faseFixture;
}

bool Fixture::obtenerParejaPartido(int numeroPartido, Equipo*& equipo1, Equipo*& equipo2) const {
    equipo1 = 0;
    equipo2 = 0;

    if (faseFixture == 0 || numeroPartido < 0 || numeroPartido >= getCantidadPartidosActual()) {
        return false;
    }

    int pos = numeroPartido * 2;
    equipo1 = faseFixture[pos];
    equipo2 = faseFixture[pos + 1];

    return (equipo1 != 0 && equipo2 != 0);
}

bool Fixture::registrarGanadorPartido(int numeroPartido, Equipo* ganador) {
    if (faseFixture == 0 || ganador == 0) {
        return false;
    }

    int totalPartidos = cantidadActual / 2;

    // Esta version asume que los partidos se resuelven en orden:
    // 0, 1, 2, 3, ...
    if (numeroPartido != ganadoresRegistrados) {
        return false;
    }

    if (numeroPartido < 0 || numeroPartido >= totalPartidos) {
        return false;
    }

    int pos = numeroPartido * 2;
    Equipo* equipo1 = faseFixture[pos];
    Equipo* equipo2 = faseFixture[pos + 1];

    if (ganador != equipo1 && ganador != equipo2) {
        return false;
    }

    // Guarda directamente el ganador al inicio del mismo arreglo.
    faseFixture[ganadoresRegistrados] = ganador;
    ganadoresRegistrados++;

    // Cuando ya se registraron todos los ganadores de la fase,
    // la fase siguiente queda compactada al inicio del arreglo.
    if (ganadoresRegistrados == totalPartidos) {
        cantidadActual = ganadoresRegistrados;
        ganadoresRegistrados = 0;
    }

    return true;
}

void Fixture::registrarPerdedorSemifinal(Equipo* perdedor) {
    if (cantidadActual == 4 && cantidadPerdedoresSemifinal < 2) {
        perdedoresSemifinal[cantidadPerdedoresSemifinal] = perdedor;
        cantidadPerdedoresSemifinal++;
    }
}

bool Fixture::obtenerParejaTercerPuesto(Equipo*& equipo1, Equipo*& equipo2) const {
    equipo1 = 0;
    equipo2 = 0;

    if (cantidadPerdedoresSemifinal < 2) {
        return false;
    }

    equipo1 = perdedoresSemifinal[0];
    equipo2 = perdedoresSemifinal[1];
    return true;
}

bool Fixture::obtenerParejaFinal(Equipo*& equipo1, Equipo*& equipo2) const {
    equipo1 = 0;
    equipo2 = 0;

    if (faseFixture == 0 || cantidadActual != 2) {
        return false;
    }

    equipo1 = faseFixture[0];
    equipo2 = faseFixture[1];
    return true;
}

short int Fixture::convertirConfederacionAIndice(const char* nombreConfederacion) const {
    if (nombreConfederacion == 0) return -1;
    if (strcmp(nombreConfederacion, "AFC") == 0) return 0;
    if (strcmp(nombreConfederacion, "CAF") == 0) return 1;
    if (strcmp(nombreConfederacion, "CONCACAF") == 0) return 2;
    if (strcmp(nombreConfederacion, "CONMEBOL") == 0) return 3;
    if (strcmp(nombreConfederacion, "OFC") == 0) return 4;
    if (strcmp(nombreConfederacion, "UEFA") == 0) return 5;
    return -1;
}

const char* Fixture::obtenerNombreConfederacionPorIndice(short int indice) const {
    switch (indice) {
    case 0: return "AFC";
    case 1: return "CAF";
    case 2: return "CONCACAF";
    case 3: return "CONMEBOL";
    case 4: return "OFC";
    case 5: return "UEFA";
    default: return "DESCONOCIDA";
    }
}

int Fixture::contarEquiposPorConfederacion(const char* nombreConfederacion) const {
    if (faseFixture == 0 || nombreConfederacion == 0) {
        return 0;
    }

    int contador = 0;

    for (int i = 0; i < cantidadActual; i++) {
        if (faseFixture[i] != 0) {
            if (strcmp(faseFixture[i]->getConfederacion(), nombreConfederacion) == 0) {
                contador++;
            }
        }
    }

    return contador;
}

const char* Fixture::obtenerConfederacionDominante(bool& hayEmpate, int& cantidadMaxima) const {
    hayEmpate = false;
    cantidadMaxima = 0;

    const int TOTAL_CONFEDERACIONES = 6;
    int conteo[TOTAL_CONFEDERACIONES];

    for (int i = 0; i < TOTAL_CONFEDERACIONES; i++) {
        conteo[i] = 0;
    }

    for (int i = 0; i < cantidadActual; i++) {
        if (faseFixture[i] != 0) {
            short int indice = convertirConfederacionAIndice(faseFixture[i]->getConfederacion());

            if (indice >= 0 && indice < TOTAL_CONFEDERACIONES) {
                conteo[indice]++;
            }
        }
    }

    short int dominante = -1;

    for (short int i = 0; i < TOTAL_CONFEDERACIONES; i++) {
        if (conteo[i] > cantidadMaxima) {
            cantidadMaxima = conteo[i];
            dominante = i;
            hayEmpate = false;
        }
        else if (conteo[i] == cantidadMaxima && conteo[i] != 0) {
            hayEmpate = true;
        }
    }

    return obtenerNombreConfederacionPorIndice(dominante);
}

const char* Fixture::getNombreFaseActual() const {
    if (cantidadActual == 32) return "R16";
    if (cantidadActual == 16) return "R8";
    if (cantidadActual == 8)  return "QF";
    if (cantidadActual == 4)  return "SF";
    if (cantidadActual == 2)  return "FINAL";
    if (cantidadActual == 1)  return "CAMPEON";
    return "DESCONOCIDA";
}