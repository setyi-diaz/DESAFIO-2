#ifndef MODCARGARACTUALIZAR_H
#define MODCARGARACTUALIZAR_H

#include "equipo.h"

Equipo* cargarEstadisticasSelecciones(unsigned short& ,unsigned short&);
void actualizarEstadisticasSelecciones(Equipo* , unsigned short&);

void cargarEstadisticasJugadores(Equipo* selecciones, unsigned short& contRef);
void actualizarEstadisticasJugadores(Equipo* selecciones, unsigned short& contRef);

#endif // MODCARGARACTUALIZAR_H
