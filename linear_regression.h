
#include <cmath>  // for fabs
#include <algorithm>  // for swap
#include <iostream>
#include <iomanip>
#include "matrix.h"
#include <vector>
#include <sstream>
#include <limits>
#include <chrono>
#include <stdio.h>
#include <cstdlib>
#include "strassen.h"
#include "lu_inverse.h"
#include "gauss_jordan.h"
//#include "base_operations.h"

#pragma once
using namespace std;


double** transposeCopy(double** A, int n) 
{
	
	double** T = new double* [n];
	for (int i = 0; i < n; ++i)
		T[i] = new double[n];

	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T[j][i] = A[i][j];

	return T;
}

int nextPowerOfTwo(int n) {
	int power = 1;
	while (power < n)
		power *= 2;
	return power;
}


double** makeSquare(double** A, int m, int n) {
	int size = nextPowerOfTwo(max(m, n));

	
	double** square = new double* [size];
	for (int i = 0; i < size; ++i)
		square[i] = new double[size];

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (i < m && j < n)
				square[i][j] = A[i][j];
			else
				square[i][j] = 0.0;
		}
	}

	return square;
}

void linear_regression()
{
	
	int m, n;

	cout << "Enter size of X (n m): ";
	cin >> n >> m;


	double** X = new double* [n];
	for (int i = 0; i < n; ++i)
		X[i] = new double[m];

	cout << "Enter elements of X (" << n << "x" << m << "):\n";
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> X[i][j];

	double** Y = new double* [n];
	for (int i = 0; i < n; ++i)
		Y[i] = new double[1];

	cout << "Enter elements of Y (" << n << "x1):\n";
	for (int i = 0; i < n; ++i)
		cin >> Y[i][0];


	auto start = chrono::high_resolution_clock::now();

	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	cout << "\nMatrix X:\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			cout << X[i][j] << " ";
		cout << endl;
	}

	cout << "\nMatrix Y:\n";
	for (int i = 0; i < n; ++i)
		cout << Y[i][0] << endl;

	double** sq_X = makeSquare(X, n, m);
	int newSize = nextPowerOfTwo(max(n, m));


	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	/*cout << "\nsq matrix " << newSize << "x" << newSize << ":\n";
	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j)
			cout << sq_X[i][j] << " ";
		cout << endl;
	}*/

	double** sq_X_t = transposeCopy(sq_X, newSize);

	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	cout << "\nX^T:\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << sq_X_t[i][j] << " ";
		cout << endl;
	}


	double** X_t_X = strassen(sq_X_t, sq_X, newSize);
	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	cout << "\nX^T * X:\n";
	for (int i = 0; i < max(n, m); ++i) {
		for (int j = 0; j < max(n, m); ++j)
			cout << X_t_X[i][j] << " ";
		cout << endl;
	}

	double** X_t_X_sq = createMatrix(m);
	
	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			X_t_X_sq[i][j] = X_t_X[i][j];


	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	/*cout << "\nsq X^T * X:\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j)
			cout << X_t_X_sq[i][j] << " ";
		cout << endl;
	}*/
	
	
	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	//cout << newSize << "size======== m " << m << " === n " << n << endl;

	int size = nextPowerOfTwo(max(m, n));


	double** square = new double* [newSize];
	for (int i = 0; i < newSize; ++i)
		square[i] = new double[newSize];

	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j) {
			if (i < n && j < 1)
				square[i][j] = Y[i][j];
			else
				square[i][j] = 0.0;
		}
	}

	double** sq_Y = square;


	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	/*cout << "\nsq matrix " << size << "x" << size << ":\n";
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <size; ++j)
			cout << sq_Y[i][j] << " ";
		cout << endl;
	}*/

	double** X_t_Y = strassen(sq_X_t, sq_Y, newSize);

	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	cout << "\nX^T * Y:\n";
	for (int i = 0; i < max(n, m); ++i) {
		for (int j = 0; j < max(n, m); ++j)
			cout << X_t_Y[i][j] << " ";
		cout << endl;
	}

	Matrix XtX_m(m, m);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j)
		{
			XtX_m(i, j) = X_t_X_sq[i][j];
		}
				
	}

	Matrix INV = inverseMatrix(XtX_m);
	double** inverse = new double* [m];

	for (int i = 0; i < m; i++)
	{
		inverse[i] = new double[m];
	}

	//int maxi = max(n, m);
	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	cout << "\n(X^t * X)^(-1):\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j)
		{
			cout << fixed << setprecision(3) << INV(i, j) << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j)
		{
			inverse[i][j] = INV(i, j);
		}
	}

	double** inv_sq = new double* [newSize];

	for (int i = 0; i < newSize; ++i)
	{
		inv_sq[i] = new double[newSize];
	}

	for (int i = 0; i < newSize; ++i)
	{
		for (int j = 0; j < newSize; ++j) 
		{
			if (i < m && j < m)
				inv_sq[i][j] = inverse[i][j];
			else
				inv_sq[i][j] = 0.0;
		}
	}

	//UNCOM IF YOU NEED TO PRINT EVERY STEP
	/*cout << "\n INV sq:\n";
	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j)
		{
			cout << inv_sq[i][j] << " ";
		}
		cout << endl;
	}*/
	

	double** result = strassen(inv_sq, X_t_Y, newSize);

	auto end = chrono::high_resolution_clock::now();

	cout << "\nresult:\n";
	for (int i = 0; i < m; ++i) 
	{
		cout << fixed << setprecision(3) << result[i][0] << " ";
		cout << endl;
	}

	chrono::duration<double> duration = end - start;
	cout << "\nTime taken for linear regression: " << duration.count() << " seconds" << endl;

	
	for (int i = 0; i < n; ++i) delete[] X[i];
	delete[] X;

	
	for (int i = 0; i < n; ++i) delete[] Y[i];
	delete[] Y;

	
	for (int i = 0; i < newSize; ++i) delete[] sq_X[i];
	delete[] sq_X;

	
	for (int i = 0; i < newSize; ++i) delete[] sq_X_t[i];
	delete[] sq_X_t;

	
	for (int i = 0; i < newSize; ++i) delete[] X_t_X[i];
	delete[] X_t_X;

	
	for (int i = 0; i < m; ++i) delete[] X_t_X_sq[i];
	delete[] X_t_X_sq;

	
	for (int i = 0; i < newSize; ++i) delete[] sq_Y[i];
	delete[] sq_Y;

	
	for (int i = 0; i < newSize; ++i) delete[] X_t_Y[i];
	delete[] X_t_Y;

	
	for (int i = 0; i < m; ++i) delete[] inverse[i];
	delete[] inverse;

	
	for (int i = 0; i < newSize; ++i) delete[] inv_sq[i];
	delete[] inv_sq;

	
	for (int i = 0; i < newSize; ++i) delete[] result[i];
	delete[] result;

	return;
}

