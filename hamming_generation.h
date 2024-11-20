#ifndef HAMMING_GENERATION_H
#define HAMMING_GENERATION_H

#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include "utilities.h"

// Función para generar un código Hamming basado en los datos proporcionados
std::vector<bool> generateHammingCode(std::vector<bool> &data);

#endif // HAMMING_GENERATION_H