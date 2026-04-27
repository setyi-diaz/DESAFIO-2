#ifndef FECHA_H
#define FECHA_H

class Fecha
{
private:
    static short int dia;
    static short int mes;
    static short int anio;

    static bool esBisiesto();
    static short int diasDelMes();

public:
    static short int getDia();
    static short int getMes();
    static short int getAnio();

    static bool setFecha(short int nuevoDia, short int nuevoMes, short int nuevoAnio);

    static bool esValida();
    static void avanzarDia();
    static void avanzarDias(short int cantidadDias);
    static void imprimirFecha();

    // Copia la fecha actual en formato dd/mm/aaaa.
    // capacidad debe ser minimo 11 para incluir el caracter '\0'.
    static void copiarFecha(char destino[], short int capacidad);
};

#endif
