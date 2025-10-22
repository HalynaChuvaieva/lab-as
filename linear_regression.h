
#include <cmath>  // for fabs
#include <algorithm>  // for swap
#include <iostream>
#include "matrix.h"
#include <vector>
#include <sstream>
#include <limits>
#include <stdio.h>
#include <cstdlib>
#include "strassen.h"
#include "lu_inverse.h"
#include "gauss_jordan.h"
//#include "base_operations.h"

#pragma once
using namespace std;


//Matrix arr_to_matrix_trim(double** A_raw, int rows, int cols)
//{
//	Matrix result(rows, cols); // создаём матрицу нужного размера
//
//	for (int i = 0; i < rows; ++i)
//	{
//		for (int j = 0; j < cols; ++j)
//		{
//			result(i, j) = A_raw[i][j]; // копируем только "полезные" элементы
//		}
//	}
//
//	return result;
//}
//
//
//Matrix increasing_the_matrix(const Matrix& current, int n, int rows, int columns)
//{
//	Matrix New(n, n);
//
//	for (int i = 0; i < rows; ++i)
//	{
//		for (int j = 0; j < columns; ++j)
//		{
//			New(i, j) = current(i, j);
//		}
//	}
//
//	return New;
//}
//
//int power_of_sq_matrix(int m, int k)
//{
//	int max = 0, power = 1;
//
//	if (m > k)
//	{
//		max = m;
//	}
//	else
//	{
//		max = k;
//	}
//
//	while (power < max)
//	{
//		power = power * 2;
//	}
//
//	return power;
//}
//
//Matrix transposition(const Matrix& current_matrix, int rows, int columns)
//{
//	Matrix matrix_t(columns, rows);
//
//	for (int i = 0; i < rows; ++i)
//	{
//		for (int j = 0; j < columns; ++j)
//		{
//			matrix_t(j, i) = current_matrix(i, j);
//		}
//	}
//
//	return matrix_t;
//}
//
//vector<double> column_of_nums()//enter matrix data
//{
//	string line;
//	vector<double> column;
//	double num = 0.0;
//
//	/*getline(cin, line);
//	stringstream temp(line);
//
//	while (temp >> num)
//	{
//		column.push_back(num);
//	}
//
//	return column;*/
//
//	// Просто читаємо повний рядок (не ігноруємо нічого заздалегідь)
//	if (!getline(cin, line)) {
//		// Якщо чтення не вдалося (EOF тощо), повертаємо порожній вектор
//		return column;
//	}
//
//	// Якщо рядок порожній (користувач просто натиснув Enter), пробуємо ще раз
//	while (line.size() == 0) {
//		if (!getline(cin, line)) return column;
//	}
//
//	stringstream temp(line);
//	while (temp >> num)
//	{
//		column.push_back(num);
//	}
//
//	return column;
//}
//
//Matrix create_matrix(int rows, int columns, vector<double> data_of_matrix)//vector to matrix
//{
//	Matrix current_matrix(rows, columns);
//
//	int vec_iter = 0;
//
//	for (int i = 0; i < rows; ++i)
//	{
//		for (int j = 0; j < columns; ++j)
//		{
//			current_matrix(i, j) = data_of_matrix[vec_iter++];
//		}
//	}
//
//	return current_matrix;
//}
//
//
//Matrix linear_rregression()
//{
//	int labels_rows, data_columns;
//
//	cout << "Enter labels vector using space after each number\n";
//	vector<double> nums_of_labels = column_of_nums();
//	labels_rows = nums_of_labels.size();
//	Matrix labels = create_matrix(labels_rows, 1, nums_of_labels);
//
//	cout << "Enter data matrix using space after each number\n(the number of rows corresponds to the number of rows of the label vector)\n";
//	vector<double> nums_of_data = column_of_nums();
//	data_columns = nums_of_data.size() / nums_of_labels.size();
//	Matrix data = create_matrix(labels_rows, data_columns, nums_of_data);
//
//	int size = power_of_sq_matrix(labels_rows, data_columns);
//	Matrix X_sq_m = increasing_the_matrix(data, size, labels_rows, data_columns);
//	cout << "1\n";
//
//	cout << "2\n";
//	Matrix Xt_m = transposition(X_sq_m, size, size);
//	cout << "3\n";
//
//	double** Xt = Xt_m.getData();
//	double** X = X_sq_m.getData();
//	cout << "4\n";
//	cout << "X before strassen:\n" << size << "\n";
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++)
//			cout << X[i][j] << "\t";
//		cout << "\n";
//	}
//
//	cout << "Xt before strassen:\n" << size << "\n";
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++)
//			cout << Xt[i][j] << "\t";
//		cout << "\n";
//	}
//	double** XtX = strassen(Xt, X, size);
//
//	cout << "5\n";
//
//	cout << "XtX before trim:\n" << size << "\n";
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++)
//			cout << XtX[i][j] << "\t";
//		cout << "\n";
//	}
//
//	//back to matrix
//	Matrix XtX_mat = arr_to_matrix_trim(XtX, data_columns, data_columns);
//	cout << "6\n";
//	//double** XtX_1 = inverseLU(XtX, size);
//	cout << "XtX before inverse:\n" << size <<"  "<< data_columns << "\n";
//	for (int i = 0; i < data_columns; i++) {
//		for (int j = 0; j < data_columns; j++)
//			cout << XtX_mat(i, j) << "\t";
//		cout << "\n";
//	}
//
//	cout << "here\n";
//
//	cout << "7\n";
//	//Matrix XtX_1_mat = inverseMatrix(XtX_mat);
//	
//	cout << "8\n";
//
//
//
//
//
//
//
//	//
//
//
//	////double** XtX_1 = XtX_1_mat.getData();
//	////cout << "6\n";
//	////Matrix Y_m = increasing_the_matrix(labels, size, labels_rows, 1);
//	////cout << "7\n";
//	////double** Y = Y_m.getData();
//	////double** XtY = strassen(Xt, Y, size);
//	////cout << "8\n";
//
//	//////double** result = strassen(temp_XtX_1, XtY, size);
//	////double** result = strassen(XtX_1, XtY, size);
//
//	Matrix w(data_columns, 1);
//
//	//for (int i = 0; i < data_columns; ++i)
//	//{
//	//	//w(i, 0) = result[i][0];  // беремо тільки перший стовпець
//	//	//cout << w(i, 0) << "\n";
//	//	cout << "bla\n";
//	//}
//
//	return w;
//}

// Функция освобождения памяти, выделенной под матрицу


double** trimMatrix(double** A, int m, int n, int size) {
	// Создаем новую матрицу m×n
	double** trimmed = new double* [m];
	for (int i = 0; i < m; ++i)
		trimmed[i] = new double[n];

	// Копируем только нужную часть
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			trimmed[i][j] = A[i][j];

	return trimmed;
}

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

	// Выделяем новую квадратную матрицу
	double** square = new double* [size];
	for (int i = 0; i < size; ++i)
		square[i] = new double[size];

	// Копируем элементы исходной матрицы и заполняем остальное нулями
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

	// Виділення пам’яті для матриці A (m × n)
	double** X = new double* [n];
	for (int i = 0; i < n; ++i)
		X[i] = new double[m];

	cout << "Enter elements of X (" << n << "x" << m << "):\n";
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> X[i][j];

	// Виділення пам’яті для матриці B (n × 1)
	double** Y = new double* [n];
	for (int i = 0; i < n; ++i)
		Y[i] = new double[1];

	cout << "Enter elements of Y (" << n << "x1):\n";
	for (int i = 0; i < n; ++i)
		cin >> Y[i][0];

	// Вивід для перевірки
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

	cout << "\nsq matrix " << newSize << "x" << newSize << ":\n";
	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j)
			cout << sq_X[i][j] << " ";
		cout << endl;
	}

	double** sq_X_t = transposeCopy(sq_X, newSize);

	cout << "\ntransposed X^T:\n";
	for (int i = 0; i < newSize; i++) {
		for (int j = 0; j < newSize; j++)
			cout << sq_X_t[i][j] << " ";
		cout << endl;
	}

	double** X_t_X = strassen(sq_X_t, sq_X, newSize);
	cout << "\ntransposed X^T * X:\n";
	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j)
			cout << X_t_X[i][j] << " ";
		cout << endl;
	}

	double** X_t_X_sq = createMatrix(m);
	
	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			X_t_X_sq[i][j] = X_t_X[i][j];

	cout << "\nsq X^T * X:\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j)
			cout << X_t_X_sq[i][j] << " ";
		cout << endl;
	}
	
	/*double** trimmed = trimMatrix(X_t_X, m, m, newSize);
	cout << "\ntrimmed X^T * X:\n";
	for (int i = 0; i < m; ++i) 
	{
		for (int j = 0; j < m; ++j)
			cout << trimmed[i][j] << " ";
		cout << endl;
	}*/

	cout << newSize << "size======== m " << m << " === n " << n << endl;

	//double** sq_Y = makeSquare(Y, n, m);
	int size = nextPowerOfTwo(max(m, n));

	// Выделяем новую квадратную матрицу
	double** square = new double* [size];
	for (int i = 0; i < size; ++i)
		square[i] = new double[size];

	// Копируем элементы исходной матрицы и заполняем остальное нулями
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (i < n && j < 1)
				square[i][j] = Y[i][j];
			else
				square[i][j] = 0.0;
		}
	}
	//int newSize_y = nextPowerOfTwo(max(n, m));

	double** sq_Y = square;

	cout << "\nsq matrix " << size << "x" << size << ":\n";
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <size; ++j)
			cout << sq_Y[i][j] << " ";
		cout << endl;
	}

	double** X_t_Y = strassen(sq_X_t, sq_Y, size);

	cout << "\n X^T * Y:\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j)
			cout << X_t_Y[i][j] << " ";
		cout << endl;
	}
	//I NEED INVERSE I NEED INVERSE
	
	////int ySize = nextPowerOfTwo(max(n, m));

	//int size = nextPowerOfTwo(max(m, n));

	//// Выделяем новую квадратную матрицу
	//double** square = new double* [size];
	//for (int i = 0; i < size; ++i)
	//	sq_Y[i] = new double[size];

	//// Копируем элементы исходной матрицы и заполняем остальное нулями
	//for (int i = 0; i < size; ++i) {
	//	for (int j = 0; j < size; ++j) {
	//		if (i < n && j < n)
	//			sq_Y[i][j] = Y[i][j];
	//		else
	//			sq_Y[i][j] = 0.0;
	//	}
	//}




	////double** sq_Y = makeSquare(Y, n, 1);
	//////int newSize = nextPowerOfTwo(max(n, m));

	//cout << "\nsq matrix Y" << n << "x" << n << ":\n";
	//for (int i = 0; i < n; ++i) {
	//	for (int j = 0; j < n; ++j)
	//		cout << Y[i][j] << " ";
	//	cout << endl;
	//}
	/////*double** sq_Y = makeSquare(Y, n, 1);
	////int ySize = nextPowerOfTwo(max(n, 1));*/

	////double** sq_Y = createMatrix(m);
	////for (int i = 0; i < n; i++)
	////	for (int j = 0; j < n; j++)
	////		sq_Y[i][j] = Y[i][j];

	//cout << "\nsq matrix Y" << size << "x" << size << ":\n";
	//for (int i = 0; i < size; ++i) {
	//	for (int j = 0; j < size; ++j)
	//		cout << sq_Y[i][j] << " ";
	//	cout << endl;
	//}

	//double** X_t_sq_tmp = createMatrix(m);


	//for (int i = 0; i < m; i++)
	//	for (int j = 0; j < m; j++)
	//		X_t_sq_tmp[i][j] = sq_X_t[i][j];

	//cout << "\nsq X^T :\n";
	//for (int i = 0; i < m; ++i) {
	//	for (int j = 0; j < m; ++j)
	//		cout << X_t_sq_tmp[i][j] << " ";
	//	cout << endl;
	//}


	//cout << "\nsq X^T * X:\n";
	//for (int i = 0; i < m; ++i) {
	//	for (int j = 0; j < m; ++j)
	//		cout << X_t_X_sq[i][j] << " ";
	//	cout << endl;
	//}


	//double** X_t_Y = strassen(X_t_sq_tmp, sq_Y, m);
	//cout << "\n X^T * Y:\n";
	//for (int i = 0; i < m; ++i) {
	//	for (int j = 0; j < m; ++j)
	//		cout << X_t_Y[i][j] << " ";
	//	cout << endl;
	//}


	// Звільнення пам’яті
	for (int i = 0; i < m; ++i) {
		//delete[] trimmed[i];
		delete[] X_t_X_sq[i];
		//delete[] X_t_sq_tmp[i];
		//delete[] inv[i];
	}
		
	//delete[] trimmed;
    //delete[] inv;
    delete[] X_t_X_sq;
    //delete[] X_t_sq_tmp;

	for (int i = 0; i < n; ++i) {
		delete[] Y[i];
		delete[] X[i];
	}

	delete[] Y;
	delete[] X;

	for (int i = 0; i < newSize; ++i) {
		delete[] sq_X[i];
		delete[] sq_X_t[i];
		delete[] X_t_X[i];
	}

	delete[] sq_X;
	delete[] sq_X_t;
	delete[] X_t_X;

	for (int i = 0; i < m; ++i) {
		delete[] sq_Y[i];
		//delete[] X_t_Y[i];
	
	}

	delete[] sq_Y;
	//delete[] X_t_Y;
	delete[] Y;
}

