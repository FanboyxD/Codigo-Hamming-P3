#include <iostream>
#include <vector>
#include <string>
#include "hamming_generation.h"
#include "error_handling.h"
#include "hamming_decode.h"

int main() {
    std::cout << "Introduce el mensaje binario (sin espacios): ";
    std::string input;
    std::cin >> input; // Lee el mensaje binario

    // Convierte el mensaje en un vector de booleanos
    std::vector<bool> data(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        data[i] = input[i] - '0';
    }

    // Genera el código Hamming
    std::vector<bool> hammingCode = generateHammingCode(data);

    // Introduce un error aleatorio
    introduceRandomError(hammingCode);

    // Detecta y corrige el error
    detectAndCorrectError(hammingCode);

    // Decodifica el mensaje
    std::vector<bool> decodedData = decodeHammingCode(hammingCode);

    // Verifica si el mensaje decodificado coincide con el original
    bool isEqual = (data == decodedData);
    std::cout << "Verificación de decodificación: " << (isEqual ? "EXITOSA" : "FALLIDA") << std::endl;

    // Muestra el mensaje original y el decodificado
    std::cout << "Mensaje original:   ";
    for (bool bit : data) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Mensaje decodificado: ";
    for (bool bit : decodedData) {
        std::cout << bit;
    }
    std::cout << std::endl;
    
    return 0;
}