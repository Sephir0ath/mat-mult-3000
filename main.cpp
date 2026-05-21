#include <iostream>
#include <vector>

#include "matrixmultiplication.cpp"

// NOTE: esto es solo para tener las definiciones en este archivo, ya que no estamos usando headers (.h/.hpp)
// matrix normalMatrixMultiplication(matrix A, matrix B);
// matrix matrixMultiplication(matrix A, matrix B);
// matrix hybridMatrixMultiplication(matrix A, matrix B, int n0);

void printMatrix(matrix M){
    for (int i = 0; i < (int)M.size(); i++){
        for (int j = 0; j < (int)M.size(); j++){
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char** argv){
	if (argc < 2){
		std::cout << "Error: no se especificó tamaño de matriz";
	    return 1;
    }

	int n = std::stoi(argv[1]);

    // TODO: idea es ver forma de proveer instancias correctas
    
	matrix matrixA(n, std::vector<int>(n, 0));
	matrix matrixB(n, std::vector<int>(n, 0));

	for (int i = 1; i < n+1; i++){
		for (int j = 1; j <n+1; j++){
			matrixA[i-1][j-1] = i + (i-1)*2;
			matrixB[i-1][j-1] = i; 
			 			 
		}
	}

    // Multiplicación normal
	matrix c = normalMatrixMultiplication(matrixA, matrixB);
    printMatrix(c);
    std::cout << std::endl;

    // Multiplicación Strassen
    matrix c2 = matrixMultiplication(matrixA, matrixB);
    printMatrix(c2);
    std::cout << std::endl;

    // Multiplicación híbrida
    int n0 = 64; // Tamaño umbral para usar el algoritmo normal en vez de Strassen
    matrix c3 = hybridMatrixMultiplication(matrixA, matrixB, n0);
    printMatrix(c3);
    std::cout << std::endl;

	return 0;
}
