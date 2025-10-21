#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "base_operations.h"
using namespace std;

// ------------------------------------------------------
// LU-розклад: A = L * U
// ------------------------------------------------------
void luDecompose(double **A, double **L, double **U, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Верхня трикутна частина (U)
        for (int k = i; k < n; k++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
                sum += (L[i][j] * U[j][k]);
            U[i][k] = A[i][k] - sum;
        }

        // Нижня трикутна частина (L)
        for (int k = i; k < n; k++)
        {
            if (i == k)
                L[i][i] = 1.0; // головна діагональ L — одиниці
            else
            {
                double sum = 0.0;
                for (int j = 0; j < i; j++)
                    sum += (L[k][j] * U[j][i]);

                if (fabs(U[i][i]) < 1e-12)
                    throw runtime_error("LU decomposition failed: zero pivot.");

                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

// ------------------------------------------------------
// Обчислення оберненої матриці через LU
// ------------------------------------------------------
double **inverseLU(double **A, int n)
{
    // Створюємо допоміжні матриці
    double **L = createMatrix(n);
    double **U = createMatrix(n);

    luDecompose(A, L, U, n);

    double **inv = createMatrix(n);

    // Перебираємо всі стовпці одиничної матриці
    for (int col = 0; col < n; col++)
    {
        // Формуємо одиничний стовпець e
        double *e = new double[n];
        for (int i = 0; i < n; i++)
            e[i] = (i == col) ? 1.0 : 0.0;

        // Розв’язуємо L * y = e (пряма підстановка)
        double *y = new double[n];
        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
                sum += L[i][j] * y[j];
            y[i] = e[i] - sum;
        }

        // Розв’язуємо U * x = y (зворотна підстановка)
        double *x = new double[n];
        for (int i = n - 1; i >= 0; i--)
        {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++)
                sum += U[i][j] * x[j];

            if (fabs(U[i][i]) < 1e-12)
                throw runtime_error("Matrix is singular — cannot invert.");

            x[i] = (y[i] - sum) / U[i][i];
        }

        // Записуємо стовпець результату
        for (int i = 0; i < n; i++)
            inv[i][col] = x[i];

        delete[] e;
        delete[] y;
        delete[] x;
    }

    deleteMatrix(L, n);
    deleteMatrix(U, n);

    return inv;
}
