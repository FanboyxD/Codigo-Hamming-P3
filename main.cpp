#include <iostream>
#include <vector>
#include <string>
#include "hamming_generation.h"
#include "error_handling.h"

int main() {
    std::cout << "Introduce el mensaje binario (sin espacios): ";
    std::string input;
    std::cin >> input; // Lee el mensaje binario
    
    // Convierte el mensaje en un vector de booleanos
    std::vector<bool> data(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        data[i] = input[i] - '0';
    }
    
    // Genera el código Hamming, introduce un error y lo corrige
    std::vector<bool> hammingCode = generateHammingCode(data);
    introduceRandomError(hammingCode);
    detectAndCorrectError(hammingCode);
    
    return 0;
}