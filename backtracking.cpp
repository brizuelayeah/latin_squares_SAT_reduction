#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;



// Función que imprime un cuadrado latino "square" de tamaño "n" en un fichero de salida "outputFile"
void printLatinSquare(string square[100][100], int n, ofstream& outputFile) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            outputFile << square[i][j] << ' ';
        }
        outputFile << endl;
    }
}

// Función que determina si es seguro colocar un número "num" en un cuadrado latino "square" de tamaño "n"
// en base a la columna "col" y a la fila "row"
bool isSafe(string square[100][100], int row, int col, string num, int n) {

    for (int i = 0; i < n; ++i) {
        if (square[row][i] == num || square[i][col] == num) {
            return false;
        }
    }

    return true;
}

// Función que resuelve un cuadrado latino "square" de tamaño "n" siguiendo la estrategia de backtracking
bool solveLatinSquare(string square[100][100], int n, int row, int col) {
    if (row == n) {
        return true;
    }

    if (col == n) {
        return solveLatinSquare(square, n, row + 1, 0);
    }

    if (square[row][col] == "*") {
        for (int num = 1; num <= n; num++) {
            if (isSafe(square, row, col, to_string(num), n)) {
                square[row][col] = to_string(num);

                if (solveLatinSquare(square, n, row, col + 1)) {
                    return true;
                }

                square[row][col] = '*';  
            }
        }
    } else {
        return solveLatinSquare(square, n, row, col + 1);
    }

    return false;  
}

// Función que rellena una matriz de 100 x 100 "matrix" elementos leyendo el cuadrado latino de un
// fichero de entrada "filename"
void fillMatrixFromFile(const string& filename, string matrix[100][100]) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }


    string line;
    int row = 0;

    while (getline(inputFile, line) && row < 100) {
        size_t start = 0, end = 0;
        int col = 0;

        while (end != string::npos && col < 100) {
            end = line.find(' ', start);

            matrix[row][col] = line.substr(start, end - start);

            if (end != string::npos) {
                start = end + 1;
            }

            ++col;
        }

        ++row;
    }

    inputFile.close();
}

// Función que, en base a un tipo de prueba "tipo" y a un tamaño de cuadrado latino "n", mide el tiempo que 
// el solver que utiliza backtracking tarda en resolver el cuadrado latino en cuestión
void prueba_tipo_y_n_backtracking(int tipo, int n, string ficherosCuadradosVacios[5], string ficherosCuadradosRellenos25[5], 
string ficherosCuadradosRellenos50[5], string ficherosCuadradosRellenos75[5], string ficherosCuadradosEspecialesAsc[5], 
string ficherosCuadradosEspecialesDesc[5], string ficherosCuadradosImposiblesColumna[5], string ficherosCuadradosImposiblesFila[5],
string matrix[100][100], ofstream& cuadradoResuelto) {
    if (tipo == 1 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosVacios[0], matrix);
    }
    if (tipo == 1 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosVacios[1], matrix);
    }
    if (tipo == 1 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosVacios[2], matrix);
    }
    if (tipo == 1 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosVacios[3], matrix);
    }
    if (tipo == 1 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosVacios[4], matrix);
    }


    else if(tipo == 2 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosRellenos25[0], matrix);
    }
    else if(tipo == 2 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosRellenos25[1], matrix);
    }
    else if(tipo == 2 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosRellenos25[2], matrix);
    }
    else if(tipo == 2 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosRellenos25[3], matrix);
    }
    else if(tipo == 2 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosRellenos25[4], matrix);
    }



    else if(tipo == 3 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosRellenos50[0], matrix);
    }
    else if(tipo == 3 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosRellenos50[1], matrix);
    }
    else if(tipo == 3 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosRellenos50[2], matrix);
    }
    else if(tipo == 3 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosRellenos50[3], matrix);
    }
    else if(tipo == 3 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosRellenos50[4], matrix);
    }


    else if(tipo == 4 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosRellenos75[0], matrix);
    }
    else if(tipo == 4 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosRellenos75[1], matrix);
    }
    else if(tipo == 4 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosRellenos75[2], matrix);
    }
    else if(tipo == 4 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosRellenos75[3], matrix);
    }
    else if(tipo == 4 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosRellenos75[4], matrix);
    }


    else if(tipo == 5 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosEspecialesAsc[0], matrix);
    }
    else if(tipo == 5 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosEspecialesAsc[1], matrix);
    }
    else if(tipo == 5 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosEspecialesAsc[2], matrix);
    }
    else if(tipo == 5 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosEspecialesAsc[3], matrix);
    }
    else if(tipo == 5 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosEspecialesAsc[4], matrix);
    }



    else if(tipo == 6 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosEspecialesDesc[0], matrix);
    }
    else if(tipo == 6 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosEspecialesDesc[1], matrix);
    }
    else if(tipo == 6 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosEspecialesDesc[2], matrix);
    }
    else if(tipo == 6 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosEspecialesDesc[3], matrix);
    }
    else if(tipo == 6 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosEspecialesDesc[4], matrix);
    }



    else if(tipo == 7 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosImposiblesColumna[0], matrix);
    }
    else if(tipo == 7 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosImposiblesColumna[1], matrix);
    }
    else if(tipo == 7 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosImposiblesColumna[2], matrix);
    }
    else if(tipo == 7 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosImposiblesColumna[3], matrix);
    }
    else if(tipo == 7 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosImposiblesColumna[4], matrix);
    }



    else if(tipo == 8 && n == 3) {
        fillMatrixFromFile(ficherosCuadradosImposiblesFila[0], matrix);
    }
    else if(tipo == 8 && n == 9) {
        fillMatrixFromFile(ficherosCuadradosImposiblesFila[1], matrix);
    }
    else if(tipo == 8 && n == 15) {
        fillMatrixFromFile(ficherosCuadradosImposiblesFila[2], matrix);
    }
    else if(tipo == 8 && n == 25) {
        fillMatrixFromFile(ficherosCuadradosImposiblesFila[3], matrix);
    }
    else if(tipo == 8 && n == 50) {
        fillMatrixFromFile(ficherosCuadradosImposiblesFila[4], matrix);
    }
    else {
        cout << "Tipo de experimento o tamaño de cuadrado latino no valido" << endl;
        exit(0);
    }
    
    bool has_solution = false;
    auto start_time = std::chrono::high_resolution_clock::now();
    has_solution = solveLatinSquare(matrix, n, 0, 0);
    auto end_time = std::chrono::high_resolution_clock::now();
    double execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000.0;

    if (has_solution) {
        printLatinSquare(matrix, n, cuadradoResuelto);
        cout << "Latin square solved and written to cuadrado_resuelto.txt." << endl;
    }
    else {
        cout << "Error: Cuadrado latino imposible de resolver" << endl;
    }
    cout << "Execution time: " << execution_time;
    
}
    

int main() {

    ofstream cuadradoResuelto;
    cuadradoResuelto.open("cuadrado_resuelto.txt");
    
    string ficherosCuadradosVacios[5];

    string ficherosCuadradosRellenos25[5];

    string ficherosCuadradosRellenos50[5];

    string ficherosCuadradosRellenos75[5];

    string ficherosCuadradosEspecialesAsc[5];

    string ficherosCuadradosEspecialesDesc[5];

    string ficherosCuadradosImposiblesColumna[5];

    string ficherosCuadradosImposiblesFila[5];

    // Vectores estáticos con los nombres de los ficheros según el tipo de prueba
    ficherosCuadradosVacios[0] = "vacio_3n.txt";
    ficherosCuadradosVacios[1] = "vacio_9n.txt";
    ficherosCuadradosVacios[2] = "vacio_15n.txt";
    ficherosCuadradosVacios[3] = "vacio_25n.txt";
    ficherosCuadradosVacios[4] = "vacio_50n.txt";
    
    ficherosCuadradosRellenos25[0] = "relleno_25_3n.txt";
    ficherosCuadradosRellenos25[1] = "relleno_25_9n.txt";
    ficherosCuadradosRellenos25[2] = "relleno_25_15n.txt";
    ficherosCuadradosRellenos25[3] = "relleno_25_25n.txt";
    ficherosCuadradosRellenos25[4] = "relleno_25_50n.txt";

    ficherosCuadradosRellenos50[0] = "relleno_50_3n.txt";
    ficherosCuadradosRellenos50[1] = "relleno_50_9n.txt";
    ficherosCuadradosRellenos50[2] = "relleno_50_15n.txt";
    ficherosCuadradosRellenos50[3] = "relleno_50_25n.txt";
    ficherosCuadradosRellenos50[4] = "relleno_50_50n.txt";

    ficherosCuadradosRellenos75[0] = "relleno_75_3n.txt";
    ficherosCuadradosRellenos75[1] = "relleno_75_9n.txt";
    ficherosCuadradosRellenos75[2] = "relleno_75_15n.txt";
    ficherosCuadradosRellenos75[3] = "relleno_75_25n.txt";
    ficherosCuadradosRellenos75[4] = "relleno_75_50n.txt";

    ficherosCuadradosEspecialesAsc[0] = "especial_asc_3n.txt";
    ficherosCuadradosEspecialesAsc[1] = "especial_asc_9n.txt";
    ficherosCuadradosEspecialesAsc[2] = "especial_asc_15n.txt";
    ficherosCuadradosEspecialesAsc[3] = "especial_asc_25n.txt";
    ficherosCuadradosEspecialesAsc[4] = "especial_asc_50n.txt";

    ficherosCuadradosEspecialesDesc[0] = "especial_desc_3n.txt";
    ficherosCuadradosEspecialesDesc[1] = "especial_desc_9n.txt";
    ficherosCuadradosEspecialesDesc[2] = "especial_desc_15n.txt";
    ficherosCuadradosEspecialesDesc[3] = "especial_desc_25n.txt";
    ficherosCuadradosEspecialesDesc[4] = "especial_desc_50n.txt";

    ficherosCuadradosImposiblesColumna[0] = "imposible_columna_3n.txt";
    ficherosCuadradosImposiblesColumna[1] = "imposible_columna_9n.txt";
    ficherosCuadradosImposiblesColumna[2] = "imposible_columna_15n.txt";
    ficherosCuadradosImposiblesColumna[3] = "imposible_columna_25n.txt";
    ficherosCuadradosImposiblesColumna[4] = "imposible_columna_50n.txt";
    
    ficherosCuadradosImposiblesFila[0] = "imposible_fila_3n.txt";
    ficherosCuadradosImposiblesFila[1] = "imposible_fila_9n.txt";
    ficherosCuadradosImposiblesFila[2] = "imposible_fila_15n.txt";
    ficherosCuadradosImposiblesFila[3] = "imposible_fila_25n.txt";
    ficherosCuadradosImposiblesFila[4] = "imposible_fila_50n.txt";

    ofstream outputFile("cuadrado_resuelto.txt");

    int tipo_solver, tipo, n;

    cout << "Backtracking Latin Square solver" << endl;
    cout << "Introduzca el tipo de prueba del cuadrado a resolver: ";
    cin >> tipo;
    cout << "Introduzca el tamaño del cuadrado a resolver: ";
    cin >> n;

    string latinSquare[100][100];


    prueba_tipo_y_n_backtracking(tipo, n, ficherosCuadradosVacios, ficherosCuadradosRellenos25, ficherosCuadradosRellenos50, 
    ficherosCuadradosRellenos75, ficherosCuadradosEspecialesAsc, ficherosCuadradosEspecialesDesc, ficherosCuadradosImposiblesColumna, 
    ficherosCuadradosImposiblesFila, latinSquare, cuadradoResuelto);
   


    outputFile.close();

    return 0;
} 
