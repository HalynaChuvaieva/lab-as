#include <iostream>
#include <cmath>     // Для std::fabs
#include <stdexcept> // Для std::runtime_error

#include "matrix.h"
#include "gauss_jordan.h"
#include "base_operations.h"
#include "strassen.h"
#include "lu_inverse.h"

// Допоміжна функція для порівняння чисел з плаваючою комою.
bool areAlmostEqual(double a, double b)
{
    return std::fabs(a - b) < 1e-9;
}
bool compareMatrices(double **A, double **B, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!areAlmostEqual(A[i][j], B[i][j]))
                return false;
    return true;
}
void run_all_tests()
{
    bool all_tests_passed = true;
    int test_count = 0;
    int passed_count = 0;

    // --- Тест №1: Стандартна матриця 3x3 ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Inverting a standard 3x3 matrix...";
    {
        bool current_test_passed = true;
        Matrix A(3, 3);
        A(0, 0) = 2;
        A(0, 1) = -1;
        A(0, 2) = 0;
        A(1, 0) = -1;
        A(1, 1) = 2;
        A(1, 2) = -1;
        A(2, 0) = 0;
        A(2, 1) = -1;
        A(2, 2) = 2;

        Matrix expected_inv(3, 3);
        expected_inv(0, 0) = 0.75;
        expected_inv(0, 1) = 0.5;
        expected_inv(0, 2) = 0.25;
        expected_inv(1, 0) = 0.5;
        expected_inv(1, 1) = 1.0;
        expected_inv(1, 2) = 0.5;
        expected_inv(2, 0) = 0.25;
        expected_inv(2, 1) = 0.5;
        expected_inv(2, 2) = 0.75;

        Matrix actual_inv = inverseMatrix(A);

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (!areAlmostEqual(actual_inv(i, j), expected_inv(i, j)))
                {
                    current_test_passed = false;
                    break;
                }
            }
            if (!current_test_passed)
                break;
        }

        if (current_test_passed)
        {
            std::cout << " PASSED\n";
            passed_count++;
        }
        else
        {
            std::cout << " FAILED\n";
            all_tests_passed = false;
        }
    }

    // --- Тест №2: Спроба знайти обернену до виродженої матриці ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Handling a singular matrix...";
    {
        Matrix singular(2, 2);
        singular(0, 0) = 1;
        singular(0, 1) = 1;
        singular(1, 0) = 1;
        singular(1, 1) = 1;

        try
        {
            inverseMatrix(singular);
            // Якщо ми дійшли сюди, значить, виняток не був "кинутий" - це помилка
            std::cout << " FAILED (Exception was not thrown)\n";
            all_tests_passed = false;
        }
        catch (const std::runtime_error &e)
        {
            // Ми очікували саме на цей виняток, отже, все правильно
            std::cout << " PASSED\n";
            passed_count++;
        }
    }
    // --- Test #3: Strassen 2x2 multiplication ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Strassen 2x2 multiplication...";
    {
        bool current_test_passed = true;
        int n = 2;

        double **A = createMatrix(n);
        double **B = createMatrix(n);
        double **expected = createMatrix(n);

        A[0][0] = 1;
        A[0][1] = 2;
        A[1][0] = 3;
        A[1][1] = 4;

        B[0][0] = 5;
        B[0][1] = 6;
        B[1][0] = 7;
        B[1][1] = 8;

        expected[0][0] = 19;
        expected[0][1] = 22;
        expected[1][0] = 43;
        expected[1][1] = 50;

        double **C = strassen(A, B, n);

        if (!compareMatrices(C, expected, n))
            current_test_passed = false;

        deleteMatrix(A, n);
        deleteMatrix(B, n);
        deleteMatrix(expected, n);
        deleteMatrix(C, n);

        if (current_test_passed)
        {
            std::cout << " PASSED\n";
            passed_count++;
        }
        else
        {
            std::cout << " FAILED\n";
            all_tests_passed = false;
        }
    }

    // --- Test #4: Strassen identity matrix ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Strassen with identity matrix...";
    {
        bool current_test_passed = true;
        int n = 2;
        double **A = createMatrix(n);
        double **I = createMatrix(n);
        double **expected = createMatrix(n);

        A[0][0] = 3;
        A[0][1] = 4;
        A[1][0] = 5;
        A[1][1] = 6;

        I[0][0] = 1;
        I[0][1] = 0;
        I[1][0] = 0;
        I[1][1] = 1;

        expected[0][0] = 3;
        expected[0][1] = 4;
        expected[1][0] = 5;
        expected[1][1] = 6;

        double **C = strassen(A, I, n);

        if (!compareMatrices(C, expected, n))
            current_test_passed = false;

        deleteMatrix(A, n);
        deleteMatrix(I, n);
        deleteMatrix(expected, n);
        deleteMatrix(C, n);

        if (current_test_passed)
        {
            std::cout << " PASSED\n";
            passed_count++;
        }
        else
        {
            std::cout << " FAILED\n";
            all_tests_passed = false;
        }
    }

    // --- Test #5: Strassen zero matrix ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": Strassen with zero matrix...";
    {
        bool current_test_passed = true;
        int n = 2;
        double **A = createMatrix(n);
        double **B = createMatrix(n);
        double **expected = createMatrix(n);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                A[i][j] = B[i][j] = expected[i][j] = 0;

        double **C = strassen(A, B, n);

        if (!compareMatrices(C, expected, n))
            current_test_passed = false;

        deleteMatrix(A, n);
        deleteMatrix(B, n);
        deleteMatrix(expected, n);
        deleteMatrix(C, n);

        if (current_test_passed)
        {
            std::cout << " PASSED\n";
            passed_count++;
        }
        else
        {
            std::cout << " FAILED\n";
            all_tests_passed = false;
        }
    }

    //Test #3: LU inverse 3x3 
    test_count++;
    std::cout << "Running Test #" << test_count << ": LU inverse 3x3...";
    {
        bool current_test_passed = true;
        int n = 3;
        double **A = createMatrix(n);
        A[0][0] = 2;  A[0][1] = -1; A[0][2] = 0;
        A[1][0] = -1; A[1][1] = 2;  A[1][2] = -1;
        A[2][0] = 0;  A[2][1] = -1; A[2][2] = 2;

        double **expected = createMatrix(n);
        expected[0][0] = 0.75; expected[0][1] = 0.5;  expected[0][2] = 0.25;
        expected[1][0] = 0.5;  expected[1][1] = 1.0;  expected[1][2] = 0.5;
        expected[2][0] = 0.25; expected[2][1] = 0.5;  expected[2][2] = 0.75;

        double **A_inv = nullptr;
        try
        {
            A_inv = inverseLU(A, n);
            if (!compareMatrices(A_inv, expected, n))
                current_test_passed = false;
        }
        catch (const std::exception &e)
        {
            std::cerr << "\nError: " << e.what();
            current_test_passed = false;
        }

        deleteMatrix(A, n);
        deleteMatrix(expected, n);
        if (A_inv)
            deleteMatrix(A_inv, n);

        if (current_test_passed)
        {
            std::cout << " PASSED\n";
            passed_count++;
        }
        else
        {
            std::cout << " FAILED\n";
            all_tests_passed = false;
        }
    }

    // --- Test #7: LU inverse of singular matrix ---
    test_count++;
    std::cout << "Running Test #" << test_count << ": LU inverse singular matrix...";
    {
        bool current_test_passed = false;
        int n = 2;
        double **A = createMatrix(n);
        A[0][0] = 1; A[0][1] = 1;
        A[1][0] = 1; A[1][1] = 1;

        try
        {
            double **A_inv = inverseLU(A, n);
            deleteMatrix(A_inv, n);
            std::cout << " FAILED (exception not thrown)\n";
        }
        catch (const std::exception &)
        {
            std::cout << " PASSED\n";
            passed_count++;
            current_test_passed = true;
        }

        deleteMatrix(A, n);

        if (!current_test_passed)
            all_tests_passed = false;
    }

    // --- Фінальний результат ---
    std::cout << "\n----------------------------------------\n";
    std::cout << "Test results: " << passed_count << " / " << test_count << " passed.\n";
    if (all_tests_passed)
    {
        std::cout << "All tests completed successfully!\n";
    }
    else
    {
        std::cout << "Some tests failed.\n";
    }
}

int main()
{
    run_all_tests();
    return 0;
}
