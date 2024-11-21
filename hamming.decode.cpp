#include <chrono>

#include "hamming_decode.h"
#include <cmath>
#include <iostream>

#include "utilities.h"

std::vector<bool> decodeHammingCode(const std::vector<bool>& hammingCode) {
    auto start = std::chrono::high_resolution_clock::now(); // Inicio del temporizador

    int n = hammingCode.size() - 1; // Tamaño del código Hamming (sin contar posición 0)
    int r = 0; // Número de bits de paridad

    // Calcula el número de bits de paridad
    while (std::pow(2, r) < n + 1) {
        r++;
    }

    int m = n - r; // Número de bits de datos
    std::vector<bool> decodedData(m); // Vector para almacenar los datos decodificados

    std::cout << "\nPROCESO DE DECODIFICACIÓN DEL CÓDIGO HAMMING" << std::endl;
    std::cout << "Bits totales: " << n << ", Bits de paridad (r): " << r << ", Bits de datos (m): " << m << std::endl << std::endl;

    printPositionHeaders(hammingCode.size());

    // Muestra el código Hamming recibido
    std::cout << "Ham |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if ((i & (i - 1)) == 0) { // Es bit de paridad
            printColorNumber(hammingCode[i], "\033[34m"); // Azul para bits de paridad
        } else {
            std::cout << std::setw(3) << hammingCode[i];
        }
    }
    std::cout << std::endl;

    // Extrae los bits de datos
    int dataIndex = 0;
    std::cout << "Dec |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if ((i & (i - 1)) != 0) { // No es una potencia de 2 (no es bit de paridad)
            decodedData[dataIndex++] = hammingCode[i];
            printColorNumber(hammingCode[i], "\033[32m"); // Verde para bits de datos
        } else {
            std::cout << std::setw(3) << "P";
        }
    }
    std::cout << std::endl;

    auto stop = std::chrono::high_resolution_clock::now(); // Fin del temporizador
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nTiempo de decodificación: " << duration.count() << " microsegundos" << std::endl << std::endl;

    return decodedData;
}
