#include <iostream>
#include <cmath>     // Для std::fabs
#include <stdexcept> // Для std::runtime_error

#include "matrix.h"
#include "gauss_jordan.h"

// Допоміжна функція для порівняння чисел з плаваючою комою.
bool areAlmostEqual(double a, double b) {
    return std::fabs(a - b) < 1e-9; 
}

void run_all_tests() {
    bool all_tests_passed = true;
    int test_count = 0;
    int passed_count = 0;

    // --- Тест №1: Стандартна матриця 3x3 ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Inverting a standard 3x3 matrix...";
    {
        bool current_test_passed = true;
        Matrix A(3, 3);
        A(0, 0) = 2; A(0, 1) = -1; A(0, 2) = 0;
        A(1, 0) = -1; A(1, 1) = 2; A(1, 2) = -1;
        A(2, 0) = 0; A(2, 1) = -1; A(2, 2) = 2;

        Matrix expected_inv(3, 3);
        expected_inv(0, 0) = 0.75; expected_inv(0, 1) = 0.5; expected_inv(0, 2) = 0.25;
        expected_inv(1, 0) = 0.5;  expected_inv(1, 1) = 1.0; expected_inv(1, 2) = 0.5;
        expected_inv(2, 0) = 0.25; expected_inv(2, 1) = 0.5; expected_inv(2, 2) = 0.75;

        Matrix actual_inv = inverseMatrix(A);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (!areAlmostEqual(actual_inv(i, j), expected_inv(i, j))) {
                    current_test_passed = false;
                    break;
                }
            }
            if (!current_test_passed) break;
        }

        if (current_test_passed) {
            std::cout << " PASSED\n";
            passed_count++;
        } else {
            std::cout << " FAILED\n";
            all_tests_passed = false;
        }
    }

    // --- Тест №2: Спроба знайти обернену до виродженої матриці ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Handling a singular matrix...";
    {
        Matrix singular(2, 2);
        singular(0, 0) = 1; singular(0, 1) = 1;
        singular(1, 0) = 1; singular(1, 1) = 1;

        try {
            inverseMatrix(singular);
            // Якщо ми дійшли сюди, значить, виняток не був "кинутий" - це помилка
            std::cout << " FAILED (Exception was not thrown)\n";
            all_tests_passed = false;
        } catch (const std::runtime_error& e) {
            // Ми очікували саме на цей виняток, отже, все правильно
            std::cout << " PASSED\n";
            passed_count++;
        }
    }
    
    // --- Фінальний результат ---
    std::cout << "\n----------------------------------------\n";
    std::cout << "Test results: " << passed_count << " / " << test_count << " passed.\n";
    if (all_tests_passed) {
        std::cout << "All tests completed successfully!\n";
    } else {
        std::cout << "Some tests failed.\n";
    }
}

int main() {
    run_all_tests();
    return 0;
}