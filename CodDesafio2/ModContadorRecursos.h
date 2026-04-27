#ifndef MODCONTADORRECURSOS_H
#define MODCONTADORRECURSOS_H

#include <cstddef>

namespace ContadorRecursos {

// Funciones internas del módulo.
// Estas reciben bytes directamente y son usadas por las funciones genéricas.
void sumarBytes(std::size_t bytes);
void restarBytes(std::size_t bytes);

// Cuenta una iteración.
// Se debe llamar dentro de los ciclos importantes.
void registrarIteracion();

// Muestra el resumen final de recursos.
void mostrarResumen();

// Reserva memoria para una variable normal, objeto o arreglo estático.
// int x;
// char c;
// int arreglo[10];
// ContadorRecursos::reservarMemoria(x);
// ContadorRecursos::reservarMemoria(c);
// ContadorRecursos::reservarMemoria(arreglo);
template <typename T>
void reservarMemoria(const T& dato) {
    (void)dato;
    sumarBytes(sizeof(dato));
}

// Libera memoria para una variable normal, objeto o arreglo estático.
// No hace delete. Solo resta del contador.
template <typename T>
void liberarMemoria(const T& dato) {
    (void)dato;
    restarBytes(sizeof(dato));
}

// Reserva memoria para un arreglo dinámico creado con new[].
// int* arreglo = new int[10];
// ContadorRecursos::reservarMemoria(arreglo, 10);
template <typename T>
void reservarMemoria(T* arreglo, std::size_t cantidad) {
    (void)arreglo;
    sumarBytes(sizeof(T) * cantidad);
}

// Libera memoria del contador para un arreglo dinámico creado con new[].
// No hace delete[]. Solo resta del contador.
// delete[] arreglo;
// ContadorRecursos::liberarMemoria(arreglo, 10);
template <typename T>
void liberarMemoria(T* arreglo, std::size_t cantidad) {
    (void)arreglo;
    restarBytes(sizeof(T) * cantidad);
}
}

#endif