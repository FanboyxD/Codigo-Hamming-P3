#include "utilities.h"

#include <iostream>

void printDivider(int width) {
    std::cout << std::string(width, '-') << std::endl;
}

void printPositionHeaders(int length) {
    std::cout << "Pos |";
    for (int i = 1; i < length; i++) {
        std::cout << std::setw(3) << i; // Imprime las posiciones numeradas
    }
    std::cout << std::endl;
    printDivider(length * 3 + 5); // Imprime una línea divisoria
}

void printColorNumber(int num, std::string color) {
    std::cout << color << std::setw(3) << num << "\033[0m"; // "\033[0m" reinicia el color
}