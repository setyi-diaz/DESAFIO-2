#include <sstream>
#include <iostream>
#include "ModCargarActualizar.h"
#include "eliminatoria.h"
#include "fixture.h"
#include "ModContadorRecursos.h"
#include "fecha.h"

using namespace std;

int calcularPuntosEquipo(Equipo* equipo)
{
    if (equipo == nullptr) {
        return 0;
    }

    return equipo->getPartidosGanados() * 3 + equipo->getPartidosEmpatados();
}

int calcularDiferenciaGoles(Equipo* equipo)
{
    if (equipo == nullptr) {
        return 0;
    }

    return equipo->getGolesAFavorActual() - equipo->getGolesEnContra();
}

bool equipoTieneMejorRendimiento(Equipo* a, Equipo* b)
{
    if (a == nullptr) {
        return false;
    }

    if (b == nullptr) {
        return true;
    }

    int puntosA = calcularPuntosEquipo(a);
    int puntosB = calcularPuntosEquipo(b);

    if (puntosA != puntosB) {
        return puntosA > puntosB;
    }

    int diferenciaA = calcularDiferenciaGoles(a);
    int diferenciaB = calcularDiferenciaGoles(b);

    if (diferenciaA != diferenciaB) {
        return diferenciaA > diferenciaB;
    }

    if (a->getGolesAFavorActual() != b->getGolesAFavorActual()) {
        return a->getGolesAFavorActual() > b->getGolesAFavorActual();
    }

    return a->getPrioridadSorteo() > b->getPrioridadSorteo();
}

void copiarGruposParaFixture(Eliminatoria& faseDeGrupos, Equipo* gruposFixture[12][4])
{
    for (short i = 0; i < 12; i++) {
        ContadorRecursos::registrarIteracion();
        for (short j = 0; j < 4; j++) {
            ContadorRecursos::registrarIteracion();
            gruposFixture[i][j] = faseDeGrupos.grupos[i][j];
        }
    }
}

void calcularMejoresTerceros(Equipo* grupos[12][4], short int mejoresTerceros[8])
{
    short int indicesTerceros[12];

    for (short i = 0; i < 12; i++) {
        ContadorRecursos::registrarIteracion();
        indicesTerceros[i] = i;
    }

    for (short i = 0; i < 11; i++) {
        ContadorRecursos::registrarIteracion();
        for (short j = i + 1; j < 12; j++) {
            ContadorRecursos::registrarIteracion();
            Equipo* terceroActual = grupos[indicesTerceros[i]][2];
            Equipo* terceroComparar = grupos[indicesTerceros[j]][2];

            if (equipoTieneMejorRendimiento(terceroComparar, terceroActual)) {
                short int temp = indicesTerceros[i];
                indicesTerceros[i] = indicesTerceros[j];
                indicesTerceros[j] = temp;
            }
        }
    }

    for (short i = 0; i < 8; i++) {
        ContadorRecursos::registrarIteracion();
        mejoresTerceros[i] = indicesTerceros[i];
    }
}

void calcularPeoresSegundos(Equipo* grupos[12][4], short int peoresSegundos[4])
{
    short int indicesSegundos[12];

    for (short i = 0; i < 12; i++) {
        ContadorRecursos::registrarIteracion();
        indicesSegundos[i] = i;
    }

    for (short i = 0; i < 11; i++) {
        ContadorRecursos::registrarIteracion();
        for (short j = i + 1; j < 12; j++) {
            ContadorRecursos::registrarIteracion();
            Equipo* segundoActual = grupos[indicesSegundos[i]][1];
            Equipo* segundoComparar = grupos[indicesSegundos[j]][1];

            if (equipoTieneMejorRendimiento(segundoActual, segundoComparar)) {
                short int temp = indicesSegundos[i];
                indicesSegundos[i] = indicesSegundos[j];
                indicesSegundos[j] = temp;
            }
        }
    }

    for (short i = 0; i < 4; i++) {
        ContadorRecursos::registrarIteracion();
        peoresSegundos[i] = indicesSegundos[i];
    }
}

void imprimirParejasFixture(Fixture& fixture)
{
    Fecha::setFecha(10, 7, 2026);
    char fechaFixture[11];
    Fecha::copiarFecha(fechaFixture, 11);

    cout << "\n============================================\n";
    cout << "FASE: " << fixture.getNombreFaseActual() << "\n";
    cout << "============================================\n";

    int totalPartidos = fixture.getCantidadPartidosActual();

    for (int i = 0; i < totalPartidos; i++) {
        ContadorRecursos::registrarIteracion();
        Equipo* equipo1 = nullptr;
        Equipo* equipo2 = nullptr;

        if (fixture.obtenerParejaPartido(i, equipo1, equipo2)) {
            cout << "Partido " << i + 1 << ": "
                 << equipo1->getPais() << " vs "
                 << equipo2->getPais()
                 << " | Fecha: " << fechaFixture
                 << " | Hora: 00:00"
                 << " | Sede: nombreSede" << "\n";
        }
    }
}

void simularTercerPuesto(Fixture& fixture)
{
    Equipo* equipo1 = nullptr;
    Equipo* equipo2 = nullptr;

    if (!fixture.obtenerParejaTercerPuesto(equipo1, equipo2)) {
        return;
    }

    Fecha::setFecha(10, 7, 2026);
    char fechaFixture[11];
    Fecha::copiarFecha(fechaFixture, 11);

    cout << "\n============================================\n";
    cout << "TERCER PUESTO\n";
    cout << "============================================\n";

    cout << equipo1->getPais() << " vs " << equipo2->getPais()
         << " | Fecha: " << fechaFixture
         << " | Hora: 00:00"
         << " | Sede: nombreSede" << "\n";

    Partido partido;
    partido.configurarDatosPartido();

    Equipo* ganador = partido.simularPartido(
        equipo1,
        equipo2,
        equipo1->getRanking(),
        equipo2->getRanking()
        );

    partido.imprimirEstadisticasDelPartido();

    if (ganador != nullptr) {
        cout << "Ganador tercer puesto: " << ganador->getPais() << "\n";
    }
}

void simularFaseFixture(Fixture& fixture)
{
    const char* nombreFase = fixture.getNombreFaseActual();
    int totalPartidos = fixture.getCantidadPartidosActual();

    Fecha::setFecha(10, 7, 2026);
    char fechaFixture[11];
    Fecha::copiarFecha(fechaFixture, 11);

    cout << "\n============================================\n";
    cout << "SIMULANDO " << nombreFase << "\n";
    cout << "============================================\n";

    for (int i = 0; i < totalPartidos; i++) {
        ContadorRecursos::registrarIteracion();
        Equipo* equipo1 = nullptr;
        Equipo* equipo2 = nullptr;

        if (!fixture.obtenerParejaPartido(i, equipo1, equipo2)) {
            cout << "No se pudo obtener el partido " << i + 1 << ".\n";
            continue;
        }

        Fecha::setFecha(10, 7, 2026);

        cout << "\n" << nombreFase << " - Partido " << i + 1 << ": "
             << equipo1->getPais() << " vs "
             << equipo2->getPais()
             << " | Fecha: " << fechaFixture
             << " | Hora: 00:00"
             << " | Sede: nombreSede" << "\n";

        Partido partido;
        partido.configurarDatosPartido();

        Equipo* ganador = partido.simularPartido(
            equipo1,
            equipo2,
            equipo1->getRanking(),
            equipo2->getRanking()
            );

        partido.imprimirEstadisticasDelPartido();

        if (ganador == nullptr) {
            cout << "No se pudo definir ganador.\n";
            continue;
        }

        Equipo* perdedor = nullptr;

        if (ganador == equipo1) {
            perdedor = equipo2;
        }
        else {
            perdedor = equipo1;
        }

        if (fixture.getCantidadActual() == 4) {
            fixture.registrarPerdedorSemifinal(perdedor);
        }

        if (fixture.registrarGanadorPartido(i, ganador)) {
            cout << "Ganador: " << ganador->getPais() << "\n";
        }
        else {
            cout << "No se pudo registrar el ganador del partido " << i + 1 << ".\n";
        }
    }
}



void imprimirMaximoGoleadorEquipo(const Equipo* equipo)
{
    if (equipo == nullptr) {
        cout << "No se pudo imprimir el goleador del campeon.\n";
        return;
    }

    unsigned short mayorCantidadGoles = 0;

    for (unsigned short i = 0; i < 26; i++) {
        ContadorRecursos::registrarIteracion();
        const Jugador* jugador = equipo->getConvocado(i);

        if (jugador != nullptr && jugador->getGolesMarcadosActual() > mayorCantidadGoles) {
            mayorCantidadGoles = jugador->getGolesMarcadosActual();
        }
    }

    cout << "\nMaximo goleador del equipo campeon (" << equipo->getPais() << "):\n";

    if (mayorCantidadGoles == 0) {
        cout << "Ningun jugador del equipo campeon marco goles en la copa.\n";
        return;
    }

    for (unsigned short i = 0; i < 26; i++) {
        ContadorRecursos::registrarIteracion();
        const Jugador* jugador = equipo->getConvocado(i);

        if (jugador != nullptr && jugador->getGolesMarcadosActual() == mayorCantidadGoles) {
            cout << "  Camiseta " << jugador->getCamiseta()
                 << " | Goles en la copa: " << jugador->getGolesMarcadosActual()
                 << " | Goles historicos actualizados: " << jugador->getGolesMarcadosHist()
                 << "\n";
        }
    }
}

void intentarInsertarEntreTresMayores(const Jugador* jugador,
                                      const Equipo* equipo,
                                      const Jugador* mejoresJugadores[3],
                                      const Equipo* mejoresEquipos[3])
{
    if (jugador == nullptr || equipo == nullptr) {
        return;
    }

    unsigned short golesJugador = jugador->getGolesMarcadosActual();

    if (golesJugador == 0) {
        return;
    }

    for (short pos = 0; pos < 3; pos++) {
        ContadorRecursos::registrarIteracion();

        if (mejoresJugadores[pos] == nullptr ||
            golesJugador > mejoresJugadores[pos]->getGolesMarcadosActual()) {

            for (short mover = 2; mover > pos; mover--) {
                ContadorRecursos::registrarIteracion();
                mejoresJugadores[mover] = mejoresJugadores[mover - 1];
                mejoresEquipos[mover] = mejoresEquipos[mover - 1];
            }

            mejoresJugadores[pos] = jugador;
            mejoresEquipos[pos] = equipo;
            return;
        }
    }
}

void imprimirTresMayoresGoleadoresTorneo(Equipo* selecciones, unsigned short cantidadSelecciones)
{
    const Jugador* mejoresJugadores[3] = { nullptr, nullptr, nullptr };
    const Equipo* mejoresEquipos[3] = { nullptr, nullptr, nullptr };

    if (selecciones == nullptr) {
        cout << "No se pudieron calcular los goleadores del torneo.\n";
        return;
    }

    for (unsigned short i = 0; i < cantidadSelecciones; i++) {
        ContadorRecursos::registrarIteracion();

        for (unsigned short j = 0; j < 26; j++) {
            ContadorRecursos::registrarIteracion();
            const Jugador* jugador = selecciones[i].getConvocado(j);
            intentarInsertarEntreTresMayores(jugador, &selecciones[i], mejoresJugadores, mejoresEquipos);
        }
    }

    cout << "\nTres mayores goleadores de toda la copa mundial:\n";

    bool hayGoleadores = false;

    for (unsigned short i = 0; i < 3; i++) {
        ContadorRecursos::registrarIteracion();

        if (mejoresJugadores[i] != nullptr && mejoresEquipos[i] != nullptr) {
            hayGoleadores = true;
            cout << "  " << i + 1 << ". "
                 << mejoresEquipos[i]->getPais()
                 << " | Camiseta " << mejoresJugadores[i]->getCamiseta()
                 << " | Goles en la copa: " << mejoresJugadores[i]->getGolesMarcadosActual()
                 << " | Goles historicos actualizados: " << mejoresJugadores[i]->getGolesMarcadosHist()
                 << "\n";
        }
    }

    if (!hayGoleadores) {
        cout << "No hubo jugadores con goles registrados en la copa.\n";
    }
}

void imprimirInformeGoleadores(Equipo* selecciones,
                               unsigned short cantidadSelecciones,
                               const Equipo* campeon)
{
    cout << "\n============================================\n";
    cout << "ESTADISTICAS DE GOLEADORES DEL TORNEO\n";
    cout << "============================================\n";

    imprimirMaximoGoleadorEquipo(campeon);
    imprimirTresMayoresGoleadoresTorneo(selecciones, cantidadSelecciones);

    cout << "============================================\n";
}
void liberarSelecciones(Equipo*& selecciones, unsigned short cantidad)
{
    if (selecciones != nullptr) {
        delete[] selecciones;
        ContadorRecursos::liberarMemoria(selecciones, cantidad);
        selecciones = nullptr;
    }
}

int main()
{
    Equipo* selecciones = nullptr;
    unsigned short cont = 0;
    unsigned short indAnfitrion = 0;
    bool huboError = false;

    try {
        selecciones = cargarEstadisticasSelecciones(cont, indAnfitrion);
        cargarEstadisticasJugadores(selecciones, cont);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
        liberarSelecciones(selecciones, cont);
        ContadorRecursos::mostrarResumen();
        return 1;
    }

    {
        Eliminatoria faseDeGrupos(selecciones);
        faseDeGrupos.imprimirGruposConformados();
        faseDeGrupos.ordenarGrupos();
        faseDeGrupos.imprimirGruposConformados();

        faseDeGrupos.simularPartidos();

        // Esto es necesario para que R16 se arme con los grupos ya ordenados
        // despues de jugar la fase de grupos.
        faseDeGrupos.ordenarGrupos();

        faseDeGrupos.imprimirTablaDeClasificacion();

        Equipo* gruposFixture[12][4];
        short int mejoresTerceros[8];
        short int peoresSegundos[4];

        copiarGruposParaFixture(faseDeGrupos, gruposFixture);
        calcularMejoresTerceros(gruposFixture, mejoresTerceros);
        calcularPeoresSegundos(gruposFixture, peoresSegundos);

        Fixture fixture;

        if (!fixture.organizarR16DesdeGrupos(gruposFixture, mejoresTerceros, peoresSegundos)) {
            cout << "\nNo se pudo organizar el R16.\n";
            huboError = true;
        }
        else {
            while (fixture.getCantidadActual() > 1) {
                ContadorRecursos::registrarIteracion();
                imprimirParejasFixture(fixture);

                if (fixture.getCantidadActual() == 2) {
                    simularTercerPuesto(fixture);
                }

                simularFaseFixture(fixture);
            }

            Equipo** faseFinal = fixture.getFaseFixture();

            if (faseFinal != nullptr && faseFinal[0] != nullptr) {
                Equipo* campeon = faseFinal[0];

                cout << "\n============================================\n";
                cout << "CAMPEON DEL TORNEO: " << campeon->getPais() << "\n";
                cout << "============================================\n";

                imprimirInformeGoleadores(selecciones, cont, campeon);
            }
        }
    }

    actualizarEstadisticasSelecciones(selecciones, cont);
    actualizarEstadisticasJugadores(selecciones, cont);

    liberarSelecciones(selecciones, cont);
    ContadorRecursos::mostrarResumen();

    return huboError ? 1 : 0;
}
