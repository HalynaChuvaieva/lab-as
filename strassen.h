#pragma once
#include <iostream>
#include <cmath>
using namespace std;

#include "base_operations.h"

double **strassen(double **A, double **B, int n)
{
    if (n == 1)
    {
        double **C = createMatrix(1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    double **A11 = createMatrix(k);
    double **A12 = createMatrix(k);
    double **A21 = createMatrix(k);
    double **A22 = createMatrix(k);
    double **B11 = createMatrix(k);
    double **B12 = createMatrix(k);
    double **B21 = createMatrix(k);
    double **B22 = createMatrix(k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    double **M1 = strassen(addMatrix(A11, A22, k), addMatrix(B11, B22, k), k);
    double **M2 = strassen(addMatrix(A21, A22, k), B11, k);
    double **M3 = strassen(A11, subMatrix(B12, B22, k), k);
    double **M4 = strassen(A22, subMatrix(B21, B11, k), k);
    double **M5 = strassen(addMatrix(A11, A12, k), B22, k);
    double **M6 = strassen(subMatrix(A21, A11, k), addMatrix(B11, B12, k), k);
    double **M7 = strassen(subMatrix(A12, A22, k), addMatrix(B21, B22, k), k);

    double **C11 = addMatrix(subMatrix(addMatrix(M1, M4, k), M5, k), M7, k);
    double **C12 = addMatrix(M3, M5, k);
    double **C21 = addMatrix(M2, M4, k);
    double **C22 = addMatrix(subMatrix(addMatrix(M1, M3, k), M2, k), M6, k);

    double **C = createMatrix(n);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    deleteMatrix(A11, k);
    deleteMatrix(A12, k);
    deleteMatrix(A21, k);
    deleteMatrix(A22, k);
    deleteMatrix(B11, k);
    deleteMatrix(B12, k);
    deleteMatrix(B21, k);
    deleteMatrix(B22, k);
    deleteMatrix(M1, k);
    deleteMatrix(M2, k);
    deleteMatrix(M3, k);
    deleteMatrix(M4, k);
    deleteMatrix(M5, k);
    deleteMatrix(M6, k);
    deleteMatrix(M7, k);
    deleteMatrix(C11, k);
    deleteMatrix(C12, k);
    deleteMatrix(C21, k);
    deleteMatrix(C22, k);

    return C;
}