#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "matrixmultiplication.cpp"

// NOTE: esto es solo para tener las definiciones en este archivo, ya que no estamos usando headers (.h/.hpp)
// matrix normalMatrixMultiplication(matrix A, matrix B);
// matrix matrixMultiplication(matrix A, matrix B);
// matrix hybridMatrixMultiplication(matrix A, matrix B, int n0);

void printMatrix(matrix &M){
    for (int i = 0; i < (int)M.size(); i++){
        for (int j = 0; j < (int)M.size(); j++){
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void writeMatrixTofile(matrix &M, const std::string& filename){
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escritura: " + filename);
    }

    int n = (int)M.size();
    out << n << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) out << ' ';
            out << M[i][j];
        }
        out << "\n";
    }
}

bool compareMatrices(matrix& A, matrix& B){
    if (A.size() != B.size()) return false;
        
    int n = (int)A.size();

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (A[i][j] != B[i][j]) return false;
        }
    }
    return true;
}

int main(int argc, char** argv){
	if (argc < 2){
		std::cout << "Error: no se especificó tamaño de matriz";
	    return 1;
    }
    
    // no necesario por ahora
    // std::random_device rd;
    // std::mt19937 gen(rd()); // o dejar semilla fija := gen(42);
    // std::uniform_int_distribution<> dist(-1000, 1000);

	int n = std::stoi(argv[1]);

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
    
    // se leen las matrices de los archivos, se multiplican usando alg. clásico y Strassen y se comparan con la solución correcta
    for (int i = 1; i <= 10; i++){
        std::string filenameA = "instances/instanceA_" + std::to_string(i);
        std::string filenameB = "instances/instanceB_" + std::to_string(i);
        std::string filenameC = "solutions/instance_" + std::to_string(i);

        matrix A = readMatrixFromFile(filenameA);
        matrix B = readMatrixFromFile(filenameB);
        matrix C = readMatrixFromFile(filenameC); // solución correcta para verificar resultados

        if (A.size() != B.size() || A.size() != C.size()){
            std::cout << "Instancia " << i << ": Error - matrices con distintas dimensiones" << std::endl;
            continue;
        }

        matrix C_classic = normalMatrixMultiplication(A, B);
        matrix C_strassen = matrixMultiplication(A, B);
        
        bool are_equal_classic = compareMatrices(C, C_classic);
        bool are_equal_strassen = compareMatrices(C, C_strassen);

        std::cout << "Instancia " << i << ": ";
        if (are_equal_classic && are_equal_strassen){
            std::cout << "Correcto" << std::endl;
        } 
        else { 
            std::cout << "Incorrecto" << std::endl;
        }
    }


	return 0;
}
