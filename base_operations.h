#pragma once
#include <iostream>
#include <cmath>
using namespace std;

double **createMatrix(int n)
{
    double **m = new double *[n];
    for (int i = 0; i < n; i++)
        m[i] = new double[n]();
    return m;
}

void deleteMatrix(double **m, int n)
{
    for (int i = 0; i < n; i++)
        delete[] m[i];
    delete[] m;
}

void inputMatrix(double **m, int n, const string &name)
{
    cout << "Введіть елементи матриці " << name << " (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> m[i][j];
}

void printMatrix(double **m, int n, const string &name)
{
    cout << "Матриця " << name << ":\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << "\t";
        cout << endl;
    }
}

double **addMatrix(double **A, double **B, int n)
{
    double **C = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

double **subMatrix(double **A, double **B, int n)
{
    double **C = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}