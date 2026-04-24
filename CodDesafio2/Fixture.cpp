#include "Fixture.h"
#include <cstring>

using std::strcmp;

Fixture::Fixture() {
    faseFixture = 0;
    cantidadActual = 0;
    ganadoresRegistrados = 0;

    perdedoresSemifinal[0] = 0;
    perdedoresSemifinal[1] = 0;
    cantidadPerdedoresSemifinal = 0;
}

Fixture::Fixture(Equipo** equipos, int cantidad) {
    faseFixture = equipos;
    cantidadActual = cantidad;
    ganadoresRegistrados = 0;

    perdedoresSemifinal[0] = 0;
    perdedoresSemifinal[1] = 0;
    cantidadPerdedoresSemifinal = 0;
}

void Fixture::recibirEquiposFase(Equipo** equipos, int cantidad) {
    faseFixture = equipos;
    cantidadActual = cantidad;
    ganadoresRegistrados = 0;

    perdedoresSemifinal[0] = 0;
    perdedoresSemifinal[1] = 0;
    cantidadPerdedoresSemifinal = 0;
}

bool Fixture::organizarR16() {
    if (faseFixture == 0 || cantidadActual != 32) {
        return false;
    }

    // Copia temporal del arreglo de punteros.
    // referencia[0..11]  -> 12 primeros
    // referencia[12..23] -> 12 segundos
    // referencia[24..31] -> 8 mejores terceros
    Equipo* referencia[32];
    for (int i = 0; i < 32; i++) {
        referencia[i] = faseFixture[i];
    }

    int libre = 0;

    // 1) Ocho partidos: primero vs tercero
    for (int partido = 0; partido < 8; partido++) {
        int idxPrimero = -1;
        for (int i = 0; i <= 11; i++) {
            if (referencia[i] != 0) {
                idxPrimero = i;
                break;
            }
        }

        if (idxPrimero == -1) {
            return false;
        }

        Equipo* primero = referencia[idxPrimero];

        int idxTercero = -1;
        for (int i = 24; i <= 31; i++) {
            if (referencia[i] != 0 && referencia[i]->getGrupo() != primero->getGrupo()) {
                idxTercero = i;
                break;
            }
        }

        if (idxTercero == -1) {
            return false;
        }

        faseFixture[libre] = primero;
        faseFixture[libre + 1] = referencia[idxTercero];

        referencia[idxPrimero] = 0;
        referencia[idxTercero] = 0;

        libre += 2;
    }

    // 2) Cuatro partidos: primero vs peor segundo
    // Los cuatro peores segundos vienen en 20..23
    for (int partido = 0; partido < 4; partido++) {
        int idxPrimero = -1;
        for (int i = 0; i <= 11; i++) {
            if (referencia[i] != 0) {
                idxPrimero = i;
                break;
            }
        }

        if (idxPrimero == -1) {
            return false;
        }

        Equipo* primero = referencia[idxPrimero];

        int idxSegundo = -1;
        for (int i = 20; i <= 23; i++) {
            if (referencia[i] != 0 && referencia[i]->getGrupo() != primero->getGrupo()) {
                idxSegundo = i;
                break;
            }
        }

        if (idxSegundo == -1) {
            return false;
        }

        faseFixture[libre] = primero;
        faseFixture[libre + 1] = referencia[idxSegundo];

        referencia[idxPrimero] = 0;
        referencia[idxSegundo] = 0;

        libre += 2;
    }

    // 3) Cuatro partidos: segundo vs segundo
    while (libre < 32) {
        int idxSegundo1 = -1;
        for (int i = 12; i <= 23; i++) {
            if (referencia[i] != 0) {
                idxSegundo1 = i;
                break;
            }
        }

        if (idxSegundo1 == -1) {
            return false;
        }

        Equipo* segundo1 = referencia[idxSegundo1];
        referencia[idxSegundo1] = 0;

        int idxSegundo2 = -1;
        for (int i = 12; i <= 23; i++) {
            if (referencia[i] != 0 && referencia[i]->getGrupo() != segundo1->getGrupo()) {
                idxSegundo2 = i;
                break;
            }
        }

        if (idxSegundo2 == -1) {
            return false;
        }

        faseFixture[libre] = segundo1;
        faseFixture[libre + 1] = referencia[idxSegundo2];

        referencia[idxSegundo2] = 0;

        libre += 2;
    }

    return true;
}

bool Fixture::organizarFixture() {
    if (faseFixture == 0 || cantidadActual < 2) {
        return false;
    }

    if (cantidadActual == 32) {
        ganadoresRegistrados = 0;
        return organizarR16();
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

    // Esta versión asume que los partidos se resuelven en orden:
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
    if (cantidadPerdedoresSemifinal < 2) {
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
    return "DESCONOCIDA";
}