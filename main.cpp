#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Función para imprimir un separador de línea con el ancho especificado
void printDivider(int width) {
    cout << string(width, '-') << endl;
}

// Función para imprimir encabezados de posiciones
void printPositionHeaders(int length) {
    cout << "Pos |";
    for (int i = 1; i < length; i++) {
        cout << setw(3) << i; // Imprime las posiciones numeradas
    }
    cout << endl;
    printDivider(length * 3 + 5); // Imprime una línea divisoria
}

// Función para imprimir un número con un color específico (ANSI escape codes)
void printColorNumber(int num, string color) {
    cout << color << setw(3) << num << "\033[0m"; // "\033[0m" reinicia el color
}

// Función para generar un código Hamming basado en los datos proporcionados
vector<bool> generateHammingCode(vector<bool> &data) {
    auto start = high_resolution_clock::now(); // Inicio del temporizador
    
    int m = data.size(); // Número de bits de datos
    int r = 0; // Número de bits de paridad
    
    // Calcula el número de bits de paridad necesarios
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    
    vector<bool> hammingCode(m + r + 1, 0); // Inicializa el código Hamming con ceros
    
    // Información inicial
    cout << "\nPROCESO DE GENERACIÓN DEL CÓDIGO HAMMING" << endl;
    cout << "Bits de datos (m): " << m << ", Bits de paridad (r): " << r << endl << endl;
    
    printPositionHeaders(hammingCode.size()); // Imprime encabezados de posiciones
    
    // Inicializa las posiciones de paridad
    cout << "Ini |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if ((i & (i - 1)) == 0) { // Verifica si la posición es una potencia de 2
            cout << setw(3) << "P" << i; // Marca como bit de paridad
        } else {
            cout << setw(3) << "_"; // Marca como posición de datos
        }
    }
    cout << endl;
    
    // Llena los bits de datos en las posiciones no reservadas para bits de paridad
    int dataIndex = 0;
    cout << "Dat |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if ((i & (i - 1)) != 0) { // No es una potencia de 2
            hammingCode[i] = data[dataIndex++];
            cout << setw(3) << hammingCode[i];
        } else {
            cout << setw(3) << "P";
        }
    }
    cout << endl;
    
    // Calcula los bits de paridad
    for (int i = 0; i < r; i++) {
        int parityPos = pow(2, i); // Posición del bit de paridad
        int parity = 0; // Valor de paridad inicializado en 0
        
        cout << "P" << parityPos << "  |";
        for (int j = 1; j < hammingCode.size(); j++) {
            if (j & parityPos) { // Verifica si la posición contribuye al bit de paridad
                parity ^= hammingCode[j]; // Calcula XOR
                cout << setw(3) << hammingCode[j];
            } else {
                cout << setw(3) << " ";
            }
        }
        hammingCode[parityPos] = parity; // Asigna el valor de paridad
        cout << " = " << parity << endl;
    }
    
    // Imprime el código Hamming final
    printDivider(hammingCode.size() * 3 + 5);
    cout << "Fin |";
    for (int i = 1; i < hammingCode.size(); i++) {
        cout << setw(3) << hammingCode[i];
    }
    cout << endl;
    
    auto stop = high_resolution_clock::now(); // Fin del temporizador
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTiempo de generación del código Hamming: " << duration.count() << " microsegundos" << endl << endl;
    
    return hammingCode;
}

// Función para introducir un error aleatorio en el código Hamming
void introduceRandomError(vector<bool> &hammingCode) {
    srand(time(0)); // Inicializa el generador de números aleatorios
    int randomPos = rand() % (hammingCode.size() - 1) + 1; // Genera una posición aleatoria
    cout << "Introduciendo error en posición " << randomPos << ":" << endl;
    printPositionHeaders(hammingCode.size());
    
    cout << "Ori |";
    for (int i = 1; i < hammingCode.size(); i++) {
        cout << setw(3) << hammingCode[i];
    }
    cout << endl;
    
    hammingCode[randomPos] = !hammingCode[randomPos]; // Invierte el bit en la posición aleatoria
    
    cout << "Err |";
    for (int i = 1; i < hammingCode.size(); i++) {
        if (i == randomPos) {
            printColorNumber(hammingCode[i], "\033[31m"); // Imprime el bit cambiado en rojo
        } else {
            cout << setw(3) << hammingCode[i];
        }
    }
    cout << endl << endl;
}

// Función para detectar y corregir un error en el código Hamming
int detectAndCorrectError(vector<bool> &hammingCode) {
    auto start = high_resolution_clock::now(); // Inicio del temporizador
    
    int n = hammingCode.size();
    int errorPos = 0; // Posición del error inicializada en 0
    
    cout << "PROCESO DE DETECCIÓN Y CORRECCIÓN DE ERROR" << endl;
    printPositionHeaders(n);
    
    cout << "Rec |";
    for (int i = 1; i < n; i++) {
        cout << setw(3) << hammingCode[i];
    }
    cout << endl;
    
    // Verifica cada bit de paridad
    for (int i = 0; pow(2, i) < n; i++) {
        int parityPos = pow(2, i);
        int parity = 0;
        
        cout << "P" << parityPos << "  |";
        for (int j = 1; j < n; j++) {
            if (j & parityPos) { // Contribuye al bit de paridad
                parity ^= hammingCode[j];
                cout << setw(3) << hammingCode[j];
            } else {
                cout << setw(3) << " ";
            }
        }
        if (parity != 0) {
            errorPos += parityPos; // Calcula la posición del error
            cout << " = 1 (Error)" << endl;
        } else {
            cout << " = 0 (OK)" << endl;
        }
    }
    
    // Corrige el error si se detectó
    if (errorPos != 0) {
        cout << "\nError detectado en posición " << errorPos << endl;
        hammingCode[errorPos] = !hammingCode[errorPos]; // Corrige el bit
        
        printDivider(n * 3 + 5);
        cout << "Cor |";
        for (int i = 1; i < n; i++) {
            if (i == errorPos) {
                printColorNumber(hammingCode[i], "\033[32m"); // Imprime el bit corregido en verde
            } else {
                cout << setw(3) << hammingCode[i];
            }
        }
        cout << endl;
    } else {
        cout << "\nNo se detectaron errores" << endl;
    }
    
    auto stop = high_resolution_clock::now(); // Fin del temporizador
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTiempo de detección y corrección: " << duration.count() << " microsegundos" << endl << endl;
    
    return errorPos;
}

// Función principal
int main() {
    cout << "Introduce el mensaje binario (sin espacios): ";
    string input;
    cin >> input; // Lee el mensaje binario
    
    // Convierte el mensaje en un vector de enteros
    vector<bool> data(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        data[i] = input[i] - '0';
    }
    
    // Genera el código Hamming, introduce un error y lo corrige
    vector<bool> hammingCode = generateHammingCode(data);
    introduceRandomError(hammingCode);
    detectAndCorrectError(hammingCode);
    
    return 0;
}



