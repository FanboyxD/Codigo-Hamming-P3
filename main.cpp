#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

void printDivider(int width) {
    cout << string(width, '-') << endl;
}

void printPositionHeaders(int length) {
    cout << "Pos |";
    for(int i = 1; i < length; i++) {
        cout << setw(3) << i;
    }
    cout << endl;
    printDivider(length * 3 + 5);
}

void printColorNumber(int num, string color) {
    cout << color << setw(3) << num << "\033[0m";
}

vector<int> generateHammingCode(vector<int> &data) {
    auto start = high_resolution_clock::now(); // Inicio del temporizador
    
    int m = data.size();
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    
    vector<int> hammingCode(m + r + 1, 0);
    
    cout << "\nPROCESO DE GENERACIÓN DEL CÓDIGO HAMMING" << endl;
    cout << "Bits de datos (m): " << m << ", Bits de paridad (r): " << r << endl << endl;
    
    printPositionHeaders(hammingCode.size());
    cout << "Ini |";
    for(int i = 1; i < hammingCode.size(); i++) {
        if((i & (i - 1)) == 0) {
            cout << setw(3) << "P" << i;
        } else {
            cout << setw(3) << "_";
        }
    }
    cout << endl;
    
    int dataIndex = 0;
    cout << "Dat |";
    for(int i = 1; i < hammingCode.size(); i++) {
        if((i & (i - 1)) != 0) {
            hammingCode[i] = data[dataIndex++];
            cout << setw(3) << hammingCode[i];
        } else {
            cout << setw(3) << "P";
        }
    }
    cout << endl;
    
    for(int i = 0; i < r; i++) {
        int parityPos = pow(2, i);
        int parity = 0;
        
        cout << "P" << parityPos << "  |";
        for(int j = 1; j < hammingCode.size(); j++) {
            if(j & parityPos) {
                parity ^= hammingCode[j];
                if(hammingCode[j] == 0 || hammingCode[j] == 1) {
                    cout << setw(3) << hammingCode[j];
                } else {
                    cout << setw(3) << "_";
                }
            } else {
                cout << setw(3) << " ";
            }
        }
        hammingCode[parityPos] = parity;
        cout << " = " << parity << endl;
    }
    
    printDivider(hammingCode.size() * 3 + 5);
    cout << "Fin |";
    for(int i = 1; i < hammingCode.size(); i++) {
        cout << setw(3) << hammingCode[i];
    }
    cout << endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTiempo de generación del código Hamming: " << duration.count() << " microsegundos" << endl << endl;
    
    return hammingCode;
}

void introduceRandomError(vector<int> &hammingCode) {
    srand(time(0));
    int randomPos = rand() % (hammingCode.size() - 1) + 1;
    cout << "Introduciendo error en posición " << randomPos << ":" << endl;
    printPositionHeaders(hammingCode.size());
    
    cout << "Ori |";
    for(int i = 1; i < hammingCode.size(); i++) {
        cout << setw(3) << hammingCode[i];
    }
    cout << endl;
    
    hammingCode[randomPos] ^= 1;
    
    cout << "Err |";
    for(int i = 1; i < hammingCode.size(); i++) {
        if(i == randomPos) {
            printColorNumber(hammingCode[i], "\033[31m");
        } else {
            cout << setw(3) << hammingCode[i];
        }
    }
    cout << endl << endl;
}

int detectAndCorrectError(vector<int> &hammingCode) {
    auto start = high_resolution_clock::now(); // Inicio del temporizador
    
    int n = hammingCode.size();
    int errorPos = 0;
    
    cout << "PROCESO DE DETECCIÓN Y CORRECCIÓN DE ERROR" << endl;
    printPositionHeaders(n);
    
    cout << "Rec |";
    for(int i = 1; i < n; i++) {
        cout << setw(3) << hammingCode[i];
    }
    cout << endl;
    
    for(int i = 0; pow(2, i) < n; i++) {
        int parityPos = pow(2, i);
        int parity = 0;
        
        cout << "P" << parityPos << "  |";
        for(int j = 1; j < n; j++) {
            if(j & parityPos) {
                parity ^= hammingCode[j];
                cout << setw(3) << hammingCode[j];
            } else {
                cout << setw(3) << " ";
            }
        }
        if(parity != 0) {
            errorPos += parityPos;
            cout << " = 1 (Error)" << endl;
        } else {
            cout << " = 0 (OK)" << endl;
        }
    }
    
    if(errorPos != 0) {
        cout << "\nError detectado en posición " << errorPos << endl;
        hammingCode[errorPos] ^= 1;
        
        printDivider(n * 3 + 5);
        cout << "Cor |";
        for(int i = 1; i < n; i++) {
            if(i == errorPos) {
                printColorNumber(hammingCode[i], "\033[32m");
            } else {
                cout << setw(3) << hammingCode[i];
            }
        }
        cout << endl;
    } else {
        cout << "\nNo se detectaron errores" << endl;
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTiempo de detección y corrección: " << duration.count() << " microsegundos" << endl << endl;
    
    return errorPos;
}

int main() {
    cout << "Introduce el mensaje binario (sin espacios): ";
    string input;
    cin >> input;
    
    vector<int> data(input.size());
    for(size_t i = 0; i < input.size(); i++) {
        data[i] = input[i] - '0';
    }
    
    vector<int> hammingCode = generateHammingCode(data);
    introduceRandomError(hammingCode);
    detectAndCorrectError(hammingCode);
    
    return 0;
}
