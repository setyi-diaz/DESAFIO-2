#include "ModContadorRecursos.h"
#include <iostream>

namespace ContadorRecursos {

static std::size_t memoriaActual = 0;
static std::size_t memoriaMaxima = 0;
static unsigned int iteracionesTotales = 0;

void sumarBytes(std::size_t bytes) {
    memoriaActual += bytes;

    if (memoriaActual > memoriaMaxima) {
        memoriaMaxima = memoriaActual;
    }
}

void restarBytes(std::size_t bytes) {
    if (bytes <= memoriaActual) {
        memoriaActual -= bytes;
    } else {
        memoriaActual = 0;
    }
}

void registrarIteracion() {
    iteracionesTotales++;
}

void mostrarResumen() {
    std::cout << std::endl;
    std::cout << "===== RESUMEN DE RECURSOS =====" << std::endl;
    std::cout << "Memoria actual usada: " << memoriaActual << " bytes" << std::endl;
    std::cout << "Memoria maxima usada: " << memoriaMaxima << " bytes" << std::endl;
    std::cout << "Iteraciones totales: " << iteracionesTotales << std::endl;
    std::cout << "================================" << std::endl;
}
}