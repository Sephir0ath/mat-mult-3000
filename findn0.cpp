#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "matrixmultiplication.cpp"

/*
Función para la búsqueda del mejor n_0 del Algoritmo Híbrido.
Retorna un .csv con el promedio de los tiempos (ms) de ejecución por cada n_0.
runs:= cantidad de ejecuciones por n_0.
 */

int main(int argc, char *argv[]) {
    std::string output_filename = argv[1];
    int n = std::stoi(argv[2]);
    int runs = 64;

    std::random_device rd;
    std::mt19937_64 rng(rd());
    
    std::ofstream file(output_filename);
    file << "n0,tiempo_promedio_ms" << std::endl;

    std::cout << "---  Buscando n_0 con n = " << n << " ---" << std::endl;

    matrix A = generateRandomMatrix(n, rng);
    matrix B = generateRandomMatrix(n, rng);

    for (int n0 = 2; n0 <= n; n0 *= 2) {
        double tiempo_acumulado = 0;

        std::cout << "Usando n0 = " << n0 << "... " << std::flush;

        for (int i = 0; i < runs; i++) {
            auto inicio = std::chrono::high_resolution_clock::now();
            
            matrix C = hybridMatrixMultiplication(A, B, n0);
            
            auto fin = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double, std::milli> duracion = fin - inicio;
            tiempo_acumulado += duracion.count();
        }

        double promedio = tiempo_acumulado / runs;
        
        file << n0 << "," << promedio << std::endl;
        
        std::cout << "t mean: " << promedio << " ms" << std::endl;
    }

    file.close();
    std::cout << "--- Done" << output_filename << " ---" << std::endl;

    return 0;
}