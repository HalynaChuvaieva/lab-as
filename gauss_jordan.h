#ifndef GAUSS_JORDAN_H
#define GAUSS_JORDAN_H

#include "matrix.h"
#include <stdexcept>
#include <cmath> // для fabs

// Функція для знаходження оберненої матриці методом Гауса-Жордана
// Повертає нову матрицю, яка є оберненою до 'A'
Matrix inverseMatrix(const Matrix& A) {
    if (A.getRows() != A.getCols()) {
        throw std::invalid_argument("Matrix must be square to find an inverse.");
    }

    int n = A.getRows();
    // Створюємо розширену матрицю [A | I], де I - одинична матриця
    Matrix augmented(n, 2 * n);

    // Копіюємо матрицю A в ліву частину розширеної матриці
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented(i, j) = A(i, j);
        }
        // Створюємо одиничну матрицю в правій частині
        augmented(i, i + n) = 1.0;
    }

    // Прямий хід (приведення до верхньої трикутної матриці)
    for (int i = 0; i < n; ++i) {
        // Пошук головного елемента для уникнення ділення на нуль
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::fabs(augmented(j, i)) > std::fabs(augmented(pivot, i))) {
                pivot = j;
            }
        }

        // Обмін рядків
        for (int k = 0; k < 2 * n; ++k) {
            std::swap(augmented(i, k), augmented(pivot, k));
        }

        // Перевірка на сингулярність (виродженість)
        if (std::fabs(augmented(i, i)) < 1e-9) { // 1e-9 - мала величина для порівняння з нулем
            throw std::runtime_error("Matrix is singular and cannot be inverted.");
        }
        
        // Ділення рядка на головний елемент
        double divisor = augmented(i, i);
        for (int j = i; j < 2 * n; ++j) {
            augmented(i, j) /= divisor;
        }

        // Обнулення елементів під головним елементом
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double multiplier = augmented(j, i);
                for (int k = 0; k < 2 * n; ++k) {
                    augmented(j, k) -= multiplier * augmented(i, k);
                }
            }
        }
    }

    // Створюємо матрицю для результату
    Matrix result(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result(i, j) = augmented(i, j + n);
        }
    }

    return result;
}


#endif // GAUSS_JORDAN_H