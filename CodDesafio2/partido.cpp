#include "partido.h"
#include "fecha.h"
#include "ModContadorRecursos.h"

std::mt19937 Partido::gen(std::random_device{}());

Partido::Partido(): equipo1(nullptr), equipo2(nullptr), golesEq1(0), golesEq2(0), posesion(50.0), prorroga(false)
{
    inicializarDatosAdministrativos();
    reiniciarEstadisticasPartido();
}

Partido::Partido(Equipo* eq1, Equipo* eq2, short int gEq1, short int gEq2, short int amEq1[11], short int amEq2[11], short int fEq1[11],
                 short int fEq2[11], double pos): equipo1(eq1), equipo2(eq2), golesEq1(gEq1), golesEq2(gEq2), posesion(pos), prorroga(false)
{
    inicializarDatosAdministrativos();

    for (short int i = 0; i < 11; i++) {
        ContadorRecursos::registrarIteracion();
        amarillasEq1[i] = amEq1[i];
        amarillasEq2[i] = amEq2[i];
        faltasEq1[i]    = fEq1[i];
        faltasEq2[i]    = fEq2[i];
    }
}

void Partido::copiarTexto(char destino[], unsigned short capacidad, const char* origen)
{
    if (destino == nullptr || capacidad == 0) {
        return;
    }

    if (origen == nullptr) {
        destino[0] = '\0';
        return;
    }

    unsigned short i = 0;

    while (i + 1 < capacidad && origen[i] != '\0') {
        ContadorRecursos::registrarIteracion();
        destino[i] = origen[i];
        i++;
    }

    destino[i] = '\0';
}

void Partido::inicializarDatosAdministrativos()
{
    Fecha::copiarFecha(fechaPartido, 11);
    copiarTexto(horaPartido, 6, "00:00");
    copiarTexto(sede, 30, "nombreSede");
    copiarTexto(arbitro1, 20, "codArbitro1");
    copiarTexto(arbitro2, 20, "codArbitro2");
    copiarTexto(arbitro3, 20, "codArbitro3");
}

void Partido::reiniciarEstadisticasPartido()
{
    golesEq1 = 0;
    golesEq2 = 0;
    posesion = 50.0;
    prorroga = false;

    for (short int i = 0; i < 11; i++) {
        ContadorRecursos::registrarIteracion();
        amarillasEq1[i] = 0;
        amarillasEq2[i] = 0;
        faltasEq1[i] = 0;
        faltasEq2[i] = 0;
    }
}

void Partido::configurarDatosPartido(const char* nuevaSede,
                                     const char* nuevaHora,
                                     const char* nuevoArbitro1,
                                     const char* nuevoArbitro2,
                                     const char* nuevoArbitro3)
{
    Fecha::copiarFecha(fechaPartido, 11);
    copiarTexto(sede, 30, nuevaSede);
    copiarTexto(horaPartido, 6, nuevaHora);
    copiarTexto(arbitro1, 20, nuevoArbitro1);
    copiarTexto(arbitro2, 20, nuevoArbitro2);
    copiarTexto(arbitro3, 20, nuevoArbitro3);
}

void Partido::calcularGoles()
{
    double mu = 1.35;
    double alpha = 0.6;
    double beta = 0.4;

    golesEq1 = mu * pow(equipo1->getGolesAFavorHist() / mu, alpha) * pow(equipo2->getGolesEnContra() / mu, beta);
    golesEq2 = mu * pow(equipo2->getGolesAFavorHist() / mu, alpha) * pow(equipo1->getGolesEnContra() / mu, beta);

    equipo1->setGolesAFavorActual(golesEq1);
    equipo2->setGolesAFavorActual(golesEq2);

    equipo1->setGolesAFavorHist(golesEq1);
    equipo2->setGolesAFavorHist(golesEq2);

    equipo1->setGolesEnContra(golesEq2);
    equipo2->setGolesEnContra(golesEq1);
}

void Partido::calcularPosesion()
{
    if (equipo1 == nullptr || equipo2 == nullptr) {
        posesion = 50.0;
        return;
    }

    if (equipo1->getRanking() == 0 || equipo2->getRanking() == 0) {
        posesion = 50.0;
        return;
    }

    double termino1 = 1.0 / equipo1->getRanking();
    double termino2 = 1.0 / equipo2->getRanking();

    posesion = 100.0 * (termino1 / (termino1 + termino2));
}

void Partido::distribuirGoles()
{
    std::uniform_int_distribution<> dis1(0, 10);
    std::uniform_int_distribution<> dis2(0, 10);

    for (short g1 = 0; g1 < golesEq1; ++g1) {
        ContadorRecursos::registrarIteracion();
        Jugador* j = equipo1->getConvocado(dis1(gen));
        if (j != nullptr) {
            j->setGolesMarcadosActual(1);
            j->setGolesMarcadosHist(1);
        }
    }

    for (short g2 = 0; g2 < golesEq2; ++g2) {
        ContadorRecursos::registrarIteracion();
        Jugador* j = equipo2->getConvocado(dis2(gen));
        if (j != nullptr) {
            j->setGolesMarcadosActual(1);
            j->setGolesMarcadosHist(1);
        }
    }
}

void Partido::distribuirTarjetas(double pPrimera, double pSegunda)
{
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < 11; ++i) {
        ContadorRecursos::registrarIteracion();
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
        ContadorRecursos::registrarIteracion();
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

void Partido::distribuirFaltas(double p1, double p2, double p3)
{
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < 11; ++i) {
        ContadorRecursos::registrarIteracion();
        Jugador* j1 = equipo1->getConvocado(i);
        if (j1 == nullptr) continue;

        unsigned short estado = faltasEq1[i];
        if (estado == 0 && dis(gen) < p1) {
            faltasEq1[i] = 1;
            j1->setFaltas(1);
        }
        else if (estado == 1 && dis(gen) < p2) {
            faltasEq1[i] = 2;
            j1->setFaltas(1);
        }
        else if (estado == 2 && dis(gen) < p3) {
            faltasEq1[i] = 3;
            j1->setFaltas(1);
        }
    }

    for (int i = 0; i < 11; ++i) {
        ContadorRecursos::registrarIteracion();
        Jugador* j2 = equipo2->getConvocado(i);
        if (j2 == nullptr) continue;

        unsigned short estado = faltasEq2[i];
        if (estado == 0 && dis(gen) < p1) {
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

void Partido::sumarMinutosJugadores(unsigned short minutos)
{
    for (unsigned short i = 0; i < 11; i++) {
        ContadorRecursos::registrarIteracion();

        Jugador* j1 = equipo1->getConvocado(i);
        if (j1 != nullptr) {
            j1->setMinutosJugados(minutos);
        }

        Jugador* j2 = equipo2->getConvocado(i);
        if (j2 != nullptr) {
            j2->setMinutosJugados(minutos);
        }
    }
}

void Partido::simularPartido(Equipo* Eq1, Equipo* Eq2)
{
    if (Eq1 == nullptr || Eq2 == nullptr) {
        cout << "No se pudo simular el partido, punteros en nullptr\n";
        return;
    }

    equipo1 = Eq1;
    equipo2 = Eq2;
    reiniciarEstadisticasPartido();

    calcularGoles();
    calcularPosesion();

    equipo1->elegirTitulares();
    equipo2->elegirTitulares();

    distribuirGoles();
    distribuirFaltas();
    distribuirTarjetas();
    sumarMinutosJugadores(90);
}

void Partido::simularPartido()
{
    simularPartido(equipo1, equipo2);
}

Equipo* Partido::simularPartido(Equipo* eq1, Equipo* eq2, unsigned short rankingEq1, unsigned short rankingEq2)
{
    if (eq1 == nullptr || eq2 == nullptr) {
        return nullptr;
    }

    equipo1 = eq1;
    equipo2 = eq2;
    reiniciarEstadisticasPartido();

    calcularGoles();
    calcularPosesion();

    equipo1->elegirTitulares();
    equipo2->elegirTitulares();

    distribuirGoles();
    distribuirFaltas();
    distribuirTarjetas();

    if (golesEq1 > golesEq2) {
        sumarMinutosJugadores(90);
        return equipo1;
    }

    if (golesEq2 > golesEq1) {
        sumarMinutosJugadores(90);
        return equipo2;
    }

    prorroga = true;

    // Desempate por ranking FIFA: menor ranking significa mejor ubicacion.
    if (rankingEq1 < rankingEq2) {
        golesEq1++;
        equipo1->setGolesAFavorActual(1);
        equipo1->setGolesAFavorHist(1);
        equipo2->setGolesEnContra(1);

        Jugador* jugadorDesempate = equipo1->getConvocado(0);
        if (jugadorDesempate != nullptr) {
            jugadorDesempate->setGolesMarcadosActual(1);
            jugadorDesempate->setGolesMarcadosHist(1);
        }

        sumarMinutosJugadores(120);
        return equipo1;
    }

    golesEq2++;
    equipo2->setGolesAFavorActual(1);
    equipo2->setGolesAFavorHist(1);
    equipo1->setGolesEnContra(1);

    Jugador* jugadorDesempate = equipo2->getConvocado(0);
    if (jugadorDesempate != nullptr) {
        jugadorDesempate->setGolesMarcadosActual(1);
        jugadorDesempate->setGolesMarcadosHist(1);
    }

    sumarMinutosJugadores(120);
    return equipo2;
}

void Partido::imprimirEstadisticasDelPartido()
{
    if (equipo1 == nullptr || equipo2 == nullptr) {
        cout << "No hay equipos asignados para imprimir estadisticas.\n";
        return;
    }

    unsigned short totalFaltasEq1 = 0;
    unsigned short totalFaltasEq2 = 0;
    unsigned short totalAmarillasEq1 = 0;
    unsigned short totalAmarillasEq2 = 0;
    unsigned short totalRojasEq1 = 0;
    unsigned short totalRojasEq2 = 0;

    for (unsigned short i = 0; i < 11; i++) {
        ContadorRecursos::registrarIteracion();
        totalFaltasEq1 += faltasEq1[i];
        totalFaltasEq2 += faltasEq2[i];

        totalAmarillasEq1 += amarillasEq1[i];
        totalAmarillasEq2 += amarillasEq2[i];

        if (amarillasEq1[i] == 2) {
            totalRojasEq1++;
        }

        if (amarillasEq2[i] == 2) {
            totalRojasEq2++;
        }
    }

    cout << "\n";
    cout << "====================================================\n";
    cout << "              ESTADISTICAS DEL PARTIDO              \n";
    cout << "====================================================\n";
    cout << "Fecha: " << fechaPartido << "   Hora: " << horaPartido << "\n";
    cout << "Sede: " << sede << "\n";
    cout << "Arbitros: " << arbitro1 << ", " << arbitro2 << ", " << arbitro3 << "\n";
    cout << "Prorroga: " << (prorroga ? "Si" : "No") << "\n";
    cout << "----------------------------------------------------\n";

    cout << std::left << std::setw(18) << "Estadistica"
         << std::right << std::setw(15) << equipo1->getPais()
         << std::right << std::setw(15) << equipo2->getPais()
         << endl;

    cout << "----------------------------------------------------\n";

    cout << std::left << std::setw(18) << "Marcador"
         << std::right << std::setw(15) << golesEq1
         << std::right << std::setw(15) << golesEq2
         << endl;

    cout << std::left << std::setw(18) << "Posesion"
         << std::right << std::setw(14) << std::fixed << std::setprecision(2) << posesion << "%"
         << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (100.0 - posesion) << "%"
         << endl;

    cout << std::left << std::setw(18) << "Faltas"
         << std::right << std::setw(15) << totalFaltasEq1
         << std::right << std::setw(15) << totalFaltasEq2
         << endl;

    cout << std::left << std::setw(18) << "Amarillas"
         << std::right << std::setw(15) << totalAmarillasEq1
         << std::right << std::setw(15) << totalAmarillasEq2
         << endl;

    cout << std::left << std::setw(18) << "Rojas"
         << std::right << std::setw(15) << totalRojasEq1
         << std::right << std::setw(15) << totalRojasEq2
         << endl;

    cout << "====================================================\n\n";
}

const char* Partido::getFechaPartido() const
{
    return fechaPartido;
}

const char* Partido::getHoraPartido() const
{
    return horaPartido;
}

const char* Partido::getSede() const
{
    return sede;
}

bool Partido::fueProrroga() const
{
    return prorroga;
}
