#include <chrono>
#include <vector>

#include "hamming_generation.h"

std::vector<bool> generateHammingCode(std::vector<bool> &data) {
    auto start = std::chrono::high_resolution_clock::now(); // Inicio del temporizador
    
    int m = data.size(); // Número de bits de datos
    int r = 0; // Número de bits de paridad
    
    // Calcula el número de bits de paridad necesarios
    while (std::pow(2, r) < m + r + 1) {
        r++;
    }
    
    std::vector<bool> hammingCode(m + r + 1, 0); // Inicializa el código Hamming con ceros
    
    // Información inicial
    std::cout << "\nPROCESO DE GENERACIÓN DEL CÓDIGO HAMMING" << std::endl;
    std::cout << "Bits de datos (m): " << m << ", Bits de paridad (r): " << r << std::endl << std::endl;
    
    printPositionHeaders(hammingCode.size()); // Imprime encabezados de posiciones
    
    // Inicializa las posiciones de paridad
    std::cout << "Ini |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if ((i & (i - 1)) == 0) { // Verifica si la posición es una potencia de 2
            std::cout << std::setw(3) << "P" << i; // Marca como bit de paridad
        } else {
            std::cout << std::setw(3) << "_"; // Marca como posición de datos
        }
    }
    std::cout << std::endl;
    
    // Llena los bits de datos en las posiciones no reservadas para bits de paridad
    int dataIndex = 0;
    std::cout << "Dat |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if ((i & (i - 1)) != 0) { // No es una potencia de 2
            hammingCode[i] = data[dataIndex++];
            std::cout << std::setw(3) << hammingCode[i];
        } else {
            std::cout << std::setw(3) << "P";
        }
    }
    std::cout << std::endl;
    
    // Calcula los bits de paridad
    for (int i = 0; i < r; i++) {
        int parityPos = std::pow(2, i); // Posición del bit de paridad
        int parity = 0; // Valor de paridad inicializado en 0
        
        std::cout << "P" << parityPos << "  |";
        for (int j = 1; j < hammingCode.size(); j++) {
            if (j & parityPos) { // Verifica si la posición contribuye al bit de paridad
                parity ^= hammingCode[j]; // Calcula XOR
                std::cout << std::setw(3) << hammingCode[j];
            } else {
                std::cout << std::setw(3) << " ";
            }
        }
        hammingCode[parityPos] = parity; // Asigna el valor de paridad
        std::cout << " = " << parity << std::endl;
    }
    
    // Imprime el código Hamming final
    printDivider(hammingCode.size() * 3 + 5);
    std::cout << "Fin |";
    for (int i = 1; i < hammingCode.size(); i++) {
        std::cout << std::setw(3) << hammingCode[i];
    }
    std::cout << std::endl;
    
    auto stop = std::chrono::high_resolution_clock::now(); // Fin del temporizador
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nTiempo de generación del código Hamming: " << duration.count() << " microsegundos" << std::endl << std::endl;
    
    return hammingCode;
}