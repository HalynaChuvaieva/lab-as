#pragma once

#include <iostream>
#include "matrix.h"
#include <vector>
#include <sstream>
#include <limits>
#include "strassen.h"
#include "base_operations.h"
#include "gauss_jordan.h"

using namespace std;

Matrix increasing_the_matrix(const Matrix& current, int n, int rows, int columns)
{
	Matrix New(n, n);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			New(i, j) = current(i, j);
		}
	}

	return New;
}

int power_of_sq_matrix(int m, int k)
{
	int max = 0, power = 1;

	if (m > k)
	{
		max = m;
	}
	else
	{
		max = k;
	}

	while (power < max)
	{
		power = power * 2;
	}

	return power;
}

Matrix transposition(Matrix current_matrix, int rows, int columns)
{
	Matrix matrix_t(columns, rows);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			matrix_t(j, i) = current_matrix(i, j);
		}
	}

	return matrix_t;
}

vector<double> column_of_nums()//enter matrix data
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string line;
	vector<double> column;
	double num = 0;

	getline(cin, line);
	stringstream temp(line);

	while (temp >> num)
	{
		column.push_back(num);
	}

	return column;
}

Matrix create_matrix(int rows, int columns, vector<double> data_of_matrix)//vector to matrix
{
	Matrix current_matrix(rows, columns);

	int vec_iter = 0;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			current_matrix(i, j) = data_of_matrix[vec_iter++];
		}
	}

	return current_matrix;
}

Matrix linear_regression()
{
	int labels_rows, data_columns;

	cout << "Enter labels vector using space after each number\n";
	vector<double> nums_of_labels = column_of_nums();
	labels_rows = nums_of_labels.size();
	Matrix labels = create_matrix(labels_rows, 1, nums_of_labels);

	cout << "Enter data matrix using space after each number\n(the number of rows corresponds to the number of rows of the label vector)\n";
	vector<double> nums_of_data = column_of_nums();
	data_columns = nums_of_data.size() / nums_of_labels.size();
	Matrix data = create_matrix(labels_rows, data_columns, nums_of_data);

	Matrix data_t = transposition(data, labels_rows, data_columns);

	int sq_size_mtrx = power_of_sq_matrix(labels_rows, data_columns);
	/*labels_rows = sq_size_mtrx;
	data_columns = sq_size_mtrx;*/

	Matrix data_inc = increasing_the_matrix(data, sq_size_mtrx, labels_rows, data_columns);
	Matrix data_t_inc = increasing_the_matrix(data, sq_size_mtrx, data_columns, labels_rows);

	Matrix XtX = strassen(data_t_inc, data_inc, sq_size_mtrx);

	XtX = inverseMatrix(XtX);

	XtX = strassen(XtX, data_t_inc, sq_size_mtrx);

	sq_size_mtrx = power_of_sq_matrix(labels_rows, sq_size_mtrx);

	Matrix labels_inc = increasing_the_matrix(labels, sq_size_mtrx, labels_rows, 1);

	XtX = strassen(XtX, labels_inc, sq_size_mtrx);

	Matrix result(data_columns, 1);

	for (int i = 0; i < data_columns; ++i)
	{
		result(i, 0) = XtX(i, 0);
	}

	return result;
}

