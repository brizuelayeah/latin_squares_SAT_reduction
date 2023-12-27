#include "minisat/core/Solver.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace Minisat;



// Función main principal
int main(){

    // Se muestra el mensaje por pantalla de que se está ejecutando el programa
    cout << "Se esta ejecutando el programa" << endl;
    
    // Se solicita al usuario que introduzca un valor de n, que será el tamaño del Latin Square
    int n;
    cout << "Introduzca un valor de n: ";
    cin >> n;

    string fichero_prueba;
    cout << "Introduzca el nombre del fichero .txt que desea probar: ";
    cin >> fichero_prueba;

    // Vector de booleanos LatinSquare para la creación de las cláusulas
    vector<vector<vector<Lit>>> LatinSquare(n, vector<vector<Lit>>(n, vector<Lit>(n)));

    // Se crea el solver
    Solver solver;
    // BUCLE QUE CREA LAS VARIABLES BOOLEANAS VACÍAS (SE NECESITARÁ DESPUÉS)
    // Se crean las variables booleanas para el Latin Square vacias de tamaño n x n
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k =0; k < n; k++){
                LatinSquare[i][j][k] = mkLit(solver.newVar());
            }
        }
    }

    // Se abre el archivo de prueba

    string fich = "../" + fichero_prueba;
    
    ifstream inputFile(fich);
    // Se comprueba que el archivo se ha abierto correctamente
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    } 

    // Si se puede abrir el fichero se procede a leerlo
    string cadena;
    // Bucle para leer la matriz desde el archivo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::string value;
            inputFile >> value;

            // Verificar si la cadena contiene '*'
            if (value.find('*') == std::string::npos) {
                // Convertir la cadena a un número entero
                int num;
                std::stringstream(value) >> num;

                //std::cout << "num: " << num << std::endl;
                solver.addClause(LatinSquare[i][j][num - 1]);
            }
        }
    }
    auto start_time = std::chrono::high_resolution_clock::now();
    // BUCLE QUE PARA CADA CELDA AÑADE LA CLÁUSULA DE QUE SOLO PUEDE TENER UN VALOR
    // Se añaden las claúsulas de restricción de que cada celda debe tener un valor y solo uno
    for(int i = 0; i<n; i++){ // Recorre cada fila
        for(int j = 0; j<n; j++){ // Recorre todas las columnas
            // Para cada celda se añade la cláusula de que solo puede tener un valor en esa celda
            for(int k = 0; k<n; k++){
                for(int l = k+1; l<n; l++){
                    solver.addClause(~LatinSquare[i][j][k], ~LatinSquare[i][j][l]);
                }
            }
        }
    }

    // BUCLE QUE GARANTIZA QUE CADA FILA TENGA EXACTAMENTE UN VALOR
    // Bucle que garantiza que cada fila contenga exactamente un valor en cada columna
    for(int i = 0; i<n; i++){       // Recorre cada fila
        for(int k = 0; k<n; k++){   // Recorre todos los valores
            vec<Lit> aux;
            for(int j = 0; j<n; j++){ // Para cada columna se añade un valor
                aux.push(LatinSquare[i][j][k]); 
            }
            solver.addClause(aux);
        }
    }

    // BUCLE QUE GARANTIZA QUE CADA VALOR APAREZCA EXACTAMENTE UNA VEZ EN CADA FILA
    // Bucle que recorre cada fila comprobando que cada columna no tenga el mismo valor
    for(int i = 0; i<n; i++){       // Recorre cada fila
        for(int j_1 = 0; j_1<n; j_1++){  // Recorre todas las columnas
            for(int j_2 = (j_1+1); j_2<n; j_2++){ // Recorre todas las columnas una posición por delante
                for(int k = 0; k<n; k++){ // Recorre todos los valores
                    solver.addClause(~LatinSquare[i][j_1][k], ~LatinSquare[i][j_2][k]);
                }
            }
        }
    }

    // BUCLE QUE GARANTIZA QUE CADA COLUMNA TENGA EXACTAMENTE UN VALOR
    // Bucle que garantiza que cada columna contenga exactamente un valor en cada fila
    for(int j = 0; j<n; j++){       // Recorre cada columna
        for(int k = 0; k<n; k++){   // Recorre todos los valores
            vec<Lit> aux;
            for(int i = 0; i<n; i++){ // Para cada fila se añade un valor
                aux.push(LatinSquare[i][j][k]); 
            }
            solver.addClause(aux);
        }
    }

    // BUCLE QUE GARANTIZA QUE CADA VALOR APAREZCA EXACTAMENTE UNA VEZ EN CADA COLUMNA
    // Bucle que recorre cada columna comprobando que cada fila no tenga el mismo valor
    for(int j = 0; j<n; j++){       // Recorre cada columna
        for(int i_1 = 0; i_1<n; i_1++){  // Recorre todas las filas 
            for(int i_2 = (i_1+1); i_2<n; i_2++){ // Recorre todas las filas una posición por delante
                for(int k = 0; k<n; k++){ // Recorre todos los valores
                    solver.addClause(~LatinSquare[i_1][j][k], ~LatinSquare[i_2][j][k]);
                }
            }
        }
    }

    // Una vez se tienen todas las cláusulas se resuelve el problema
    bool resuelto = solver.solve();
    auto end_time = std::chrono::high_resolution_clock::now();
    double execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000.0;

    // Si se ha resuelto el problema se imprime la solución
    if(resuelto){
        cout << "Se ha resuelto el Latin Square con SAT:" << endl;
        cout << "Execution time: " << execution_time << endl;
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                for(int k = 0; k<n; k++){
                    if(solver.modelValue(LatinSquare[i][j][k]) == l_True){
                        cout << k+1 << " ";
                    }
                }
            }
            cout << endl;
        }
    } else {
        cout << "No se ha podido resolver el Latin Square con SAT" << endl;
        cout << "Execution time: " << execution_time;
    }

    return 0;
}