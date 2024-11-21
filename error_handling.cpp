#include "error_handling.h"

#include <chrono>
#include <cmath>
#include <iostream>

#include "utilities.h"

void introduceRandomError(std::vector<bool> &hammingCode) {
    std::srand(std::time(0)); // Inicializa el generador de números aleatorios
    int randomPos = std::rand() % (hammingCode.size() - 1) + 1; // Genera una posición aleatoria
    std::cout << "Introduciendo error en posición " << randomPos << ":" << std::endl;
    printPositionHeaders(hammingCode.size());
    
    std::cout << "Ori |";
    for (int i = 1; i < hammingCode.size(); i++) {
        std::cout << std::setw(3) << hammingCode[i];
    }
    std::cout << std::endl;
    
    hammingCode[randomPos] = !hammingCode[randomPos]; // Invierte el bit en la posición aleatoria
    
    std::cout << "Err |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if (i == randomPos) {
            printColorNumber(hammingCode[i], "\033[31m"); // Imprime el bit cambiado en rojo
        } else {
            std::cout << std::setw(3) << hammingCode[i];
        }
    }
    std::cout << std::endl << std::endl;
}

int detectAndCorrectError(std::vector<bool> &hammingCode) {
    auto start = std::chrono::high_resolution_clock::now(); // Inicio del temporizador
    
    int n = hammingCode.size();
    int errorPos = 0; // Posición del error inicializada en 0
    
    std::cout << "PROCESO DE DETECCIÓN Y CORRECCIÓN DE ERROR" << std::endl;
    printPositionHeaders(n);
    
    std::cout << "Rec |";
    for (int i = 1; i < n; i++) {
        std::cout << std::setw(3) << hammingCode[i];
    }
    std::cout << std::endl;
    
    // Verifica cada bit de paridad
    for (int i = 0; std::pow(2, i) < n; i++) {
        int parityPos = std::pow(2, i);
        int parity = 0;
        
        std::cout << "P" << parityPos << "  |";
        for (int j = 1; j < n; j++) {
            if (j & parityPos) { // Contribuye al bit de paridad
                parity ^= hammingCode[j];
                std::cout << std::setw(3) << hammingCode[j];
            } else {
                std::cout << std::setw(3) << " ";
            }
        }
        if (parity != 0) {
            errorPos += parityPos; // Calcula la posición del error
            std::cout << " = 1 (Error)" << std::endl;
        } else {
            std::cout << " = 0 (OK)" << std::endl;
        }
    }
    
    // Corrige el error si se detectó
    if (errorPos != 0) {
        std::cout << "\nError detectado en posición " << errorPos << std::endl;
        hammingCode[errorPos] = !hammingCode[errorPos]; // Corrige el bit
        
        printDivider(n * 3 + 5);
        std::cout << "Cor |";
        for (int i = 1; i < n; i++) {
            if (i == errorPos) {
                printColorNumber(hammingCode[i], "\033[32m"); // Imprime el bit corregido en verde
            } else {
                std::cout << std::setw(3) << hammingCode[i];
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "\nNo se detectaron errores" << std::endl;
    }
    
    auto stop = std::chrono::high_resolution_clock::now(); // Fin del temporizador
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nTiempo de detección y corrección: " << duration.count() << " microsegundos" << std::endl << std::endl;
    
    return errorPos;
}