#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <vector>


// Función para introducir un error aleatorio en el código Hamming
void introduceRandomError(std::vector<bool> &hammingCode);

// Función para detectar y corregir un error en el código Hamming
int detectAndCorrectError(std::vector<bool> &hammingCode);

#endif // ERROR_HANDLING_H