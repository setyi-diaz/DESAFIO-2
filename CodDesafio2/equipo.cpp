#include "equipo.h"

Equipo::Equipo(unsigned short r, const  char* const p, const char* const d, const char* const f, const char* const c, unsigned short gf,
               unsigned short gc, unsigned short pg, unsigned short pe, unsigned short pp) {

    ranking = r;
    unsigned short len = strlen(p);
    len = ( len < 25 ? len : 24);
    strncpy(pais, p, len);
    pais[len] = '\0';

    len = strlen(d);
    len = ( len < 20 ? len : 19);
    strncpy(dt, d, len);
    dt[len] = '\0';

    len = strlen(f);
    len = ( len < 47 ? len : 46);
    strncpy(federacion, f, len);
    federacion[len] = '\0';

    len = strlen(c);
    len = ( len < 10 ? len : 9);
    strncpy(confederacion, c, len);
    confederacion[len] = '\0';

    golesAFavor = gf;
    golesEnContra = gc;
    partidosGanados = pg;
    partidosEmpatados = pe;
    partidosPerdidos = pp;
}
const Equipo& Equipo::operator=(const Equipo &derecha){
    if (&derecha != this){
        ranking = derecha.getRanking();
        strncpy(pais, derecha.getPais(), sizeof(pais) - 1);
        pais[sizeof(pais) - 1] = '\0';
        strncpy(dt, derecha.getDt(), sizeof(dt) - 1);
        dt[sizeof(dt) - 1] = '\0';
        strncpy(federacion, derecha.getFederacion(), sizeof(federacion) - 1);
        federacion[sizeof(federacion) - 1] = '\0';
        strncpy(confederacion, derecha.getConfederacion(), sizeof(confederacion) - 1);
        confederacion[sizeof(confederacion) - 1] = '\0';
        golesAFavor = derecha.getGolesAFavor();
        golesEnContra = derecha.getGolesEnContra();
        partidosGanados = derecha.getPartidosGanados();
        partidosEmpatados = derecha.getPartidosEmpatados();
        partidosPerdidos = derecha.getPartidosPerdidos();
    }
    return *this;
}
void Equipo::elegirTitulares(){
    std::random_device rd;
    std::mt19937 gen(rd());
    Jugador* temp;

    for (short int i = 27; i > 0; i--) {
        std::uniform_int_distribution<unsigned int> dist(0, i);
        unsigned int j = dist(gen);
        temp = convocados[i];
        convocados[i] = convocados[j];
        convocados[j] = temp;
    }
}
Jugador* Equipo::getConvocado(unsigned int i) {
    return convocados[i];
}

const Jugador* Equipo::getConvocado(unsigned int  i) const {
    return convocados[i];
}

const char* Equipo::getPais() const{
    return pais;
}
//void Equipo::setPais(unsigned char* newPais){}
const char* Equipo::getDt() const{
    return dt;
}
//void Equipo::setDt(unsigned char* newDt){}
const char* Equipo::getFederacion() const{
    return federacion;
}
//void Equipo::setFederacion(unsigned char* newFederacion){}
const char* Equipo::getConfederacion() const{
    return confederacion;
}
//void Equipo::setConfederacion(unsigned char* newConfederacion){}
unsigned short Equipo::getGolesAFavor() const
{
    return golesAFavor;
}

void Equipo::setGolesAFavor(unsigned short newGolesAFavor)
{
    golesAFavor = newGolesAFavor;
}

unsigned short Equipo::getGolesEnContra() const
{
    return golesEnContra;
}

void Equipo::setGolesEnContra(unsigned short newGolesEnContra)
{
    golesEnContra = newGolesEnContra;
}

unsigned short Equipo::getPartidosGanados() const
{
    return partidosGanados;
}

void Equipo::setPartidosGanados(unsigned short newPartidosGanados)
{
    partidosGanados = newPartidosGanados;
}

unsigned short Equipo::getPartidosEmpatados() const
{
    return partidosEmpatados;
}

void Equipo::setPartidosEmpatados(unsigned short newPartidosEmpatados)
{
    partidosEmpatados = newPartidosEmpatados;
}

unsigned short Equipo::getPartidosPerdidos() const
{
    return partidosPerdidos;
}

void Equipo::setPartidosPerdidos(unsigned short newPartidosPerdidos)
{
    partidosPerdidos = newPartidosPerdidos;
}

unsigned short Equipo::getRanking() const
{
    return ranking;
}

void Equipo::setRanking(unsigned short newRanking)
{
    ranking = newRanking;
}

