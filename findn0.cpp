#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "matrixmultiplication.cpp"

int main(int argc, char *argv[]) {
    std::string output_filename = argv[1];
    int n = std::stoi(argv[2]);
    int runs = 5;

    std::random_device rd;
    std::mt19937_64 rng(rd());
    
    std::ofstream file(output_filename);
    file << "n0,tiempo_promedio_ns" << std::endl;

    std::cout << "---  Buscando n_0 con n:= " << n << " ---" << std::endl;

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
        
        std::cout << "t mean: " << promedio << " ns" << std::endl;
    }

    file.close();
    std::cout << "--- Done" << output_filename << " ---" << std::endl;

    return 0;
}