#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iomanip>

// Función para imprimir un separador de línea con el ancho especificado
void printDivider(int width);

// Función para imprimir encabezados de posiciones
void printPositionHeaders(int length);

// Función para imprimir un número con un color específico (ANSI escape codes)
void printColorNumber(int num, std::string color);

#endif // UTILITIES_H