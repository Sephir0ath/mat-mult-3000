#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

typedef std::vector<std::vector<int>> matrix;

matrix sum(const matrix &A, const matrix &B){
	int n = A.size();
    matrix res(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

matrix sub(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix res(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

// Algoritmo Normal
matrix normalMatrixMultiplication(const matrix &A, const matrix &B){
    int n = A.size();

    matrix C(n, std::vector<int>(n, 0));

	for (int i = 0; i < (int)A.size(); i++){
		for (int j = 0; j < (int)A.size(); j++){
			for (int k = 0; k < (int)A.size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }		
		}
	}

	return C;
}

// generar matrices aleatorias
matrix generateRandomMatrix(int n, std::mt19937_64 &rng) {
    matrix M(n, std::vector<int>(n));
    std::uniform_int_distribution<int> dist(1, 99); 
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = dist(rng);
        }
    }
    return M;
}

matrix generateDiagonalMatrix(int n, std::mt19937_64 &rng){
    matrix M(n, std::vector<int>(n));
    std::uniform_int_distribution<int> dist(1, 99);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                M[i][j] = dist(rng);
            }
            else{
                M[i][j] = 0;
            }
        }
    }
    return M;
}

matrix generateTriangularMatrix(int n, std::mt19937_64 &rng){
    matrix M(n, std::vector<int>(n));
    std::uniform_int_distribution<int> dist(1, 99);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j){
                   M[i][j] = dist(rng);
               }
        }
    }
    return M;

}

// Algoritmo Divide and conquer 
matrix matrixMultiplication(const matrix &A, const matrix &B){
	int n = A.size();

	// Caso base: matriz 1x1
	if (n == 1){
		return {{A[0][0] * B[0][0]}};
	}

	// Inicializar A y B y dividir en 4 subcuadrantes
	int k = n / 2;
	matrix a11(k, std::vector<int>(k)), a12(k, std::vector<int>(k)),
	a21(k, std::vector<int>(k)), a22(k, std::vector<int>(k)),
	b11(k, std::vector<int>(k)), b12(k, std::vector<int>(k)),
	b21(k, std::vector<int>(k)), b22(k, std::vector<int>(k));

	for (int i = 0; i < k; i++) {
    	for (int j = 0; j < k; j++) {
        	a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];
 
            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
		}
	}

	// Calcular las 7 matrices.
	matrix m1 = matrixMultiplication(sum(a11, a22), sum(b11, b22));
    matrix m2 = matrixMultiplication(sum(a21, a22), b11);
    matrix m3 = matrixMultiplication(a11, sub(b12, b22));
    matrix m4 = matrixMultiplication(a22, sub(b21, b11));
    matrix m5 = matrixMultiplication(sum(a11, a12), b22);
    matrix m6 = matrixMultiplication(sub(a21, a11), sum(b11, b12));
    matrix m7 = matrixMultiplication(sub(a12, a22), sum(b21, b22));

    // Hacer los calculos de la matriz resulantes
    matrix c11 = sum(sub(sum(m1, m4), m5), m7);
    matrix c12 = sum(m3, m5);
    matrix c21 = sum(m2, m4);
    matrix c22 = sum(sub(sum(m1, m3), m2), m6);

	matrix C(n, std::vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = c11[i][j];
            C[i][j + k] = c12[i][j];
            C[i + k][j] = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
	
    return C;
}

// Algoritmo híbrido
matrix hybridMatrixMultiplication(const matrix &A, const matrix &B, int n0){
    int n = A.size();
    
    if (n <= n0) {
        return normalMatrixMultiplication(A, B);
    }
    
    // Inicializar A y B y dividir en 4 subcuadrantes
	int k = n / 2;
	matrix a11(k, std::vector<int>(k)), a12(k, std::vector<int>(k)),
	a21(k, std::vector<int>(k)), a22(k, std::vector<int>(k)),
	b11(k, std::vector<int>(k)), b12(k, std::vector<int>(k)),
	b21(k, std::vector<int>(k)), b22(k, std::vector<int>(k));

	for (int i = 0; i < k; i++) {
    	for (int j = 0; j < k; j++) {
        	a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];
 
            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
		}
	}

	// Calcular las 7 matrices (usando alg. híbrido)
    matrix m1 = hybridMatrixMultiplication(sum(a11, a22), sum(b11, b22), n0);
    matrix m2 = hybridMatrixMultiplication(sum(a21, a22), b11, n0);
    matrix m3 = hybridMatrixMultiplication(a11, sub(b12, b22), n0);
    matrix m4 = hybridMatrixMultiplication(a22, sub(b21, b11), n0);
    matrix m5 = hybridMatrixMultiplication(sum(a11, a12), b22, n0);
    matrix m6 = hybridMatrixMultiplication(sub(a21, a11), sum(b11, b12), n0);
    matrix m7 = hybridMatrixMultiplication(sub(a12, a22), sum(b21, b22), n0);

    // Hacer los calculos de la matriz resulantes
    matrix c11 = sum(sub(sum(m1, m4), m5), m7);
    matrix c12 = sum(m3, m5);
    matrix c21 = sum(m2, m4);
    matrix c22 = sum(sub(sum(m1, m3), m2), m6);

	matrix C(n, std::vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = c11[i][j];
            C[i][j + k] = c12[i][j];
            C[i + k][j] = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
	
    return C;
}

matrix readMatrixFromFile(const std::string& filename){
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Error abriendo archivo: " + filename);
    }
    int n;
    if (!(in >> n) || n < 0) {
        throw std::runtime_error("Error en formato. Se espera n al inicio: " + filename);
    }
    matrix M(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(in >> M[i][j])) {
                throw std::runtime_error("Error en formato. Faltan elementos: " + filename);
            }
        }
    }
    return M;
}
