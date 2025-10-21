#include <iostream>
#include <cmath>
#include <chrono>  // Для вимірювання часу
using namespace std;

#include "matrix.h"
#include "gauss_jordan.h"  
#include "lu_inverse.h"
#include "strassen.h"
#include "linear_regression.h"

int main()
{
    int choice;
    double **A = nullptr;
    double **B = nullptr;
    double **C = nullptr;
    int n = 0;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Enter size of matrixes\n";
        cout << "2. Enter elements of matrixes\n";
        cout << "3. Multiply matrixes with Strassen's algorithm\n";
        cout << "4. Show matrixes\n";
        cout << "5. DEMO: Find inverse matrix with Gauss-Jordan\n";
        cout << "6. DEMO: Find inverse matrix with LU decomposition\n";
        cout << "7. Building a linear regression from known data and labels\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter size: ";
            cin >> n;
            if (A)
                deleteMatrix(A, n);
            if (B)
                deleteMatrix(B, n);
            if (C)
                deleteMatrix(C, n);
            A = createMatrix(n);
            B = createMatrix(n);
            break;

        case 2:
            if (n == 0)
                cout << "Enter size at first!\n";
            else
            {
                inputMatrix(A, n, "A");
                inputMatrix(B, n, "B");
            }
            break;

        case 3:
            if (!A || !B)
                cout << "Enter matrixes at first!\n";
            else
            {
                C = strassen(A, B, n);
                cout << "Muliplication done.\n";
            }
            break;

        case 4:
            if (A)
                printMatrix(A, n, "A");
            if (B)
                printMatrix(B, n, "B");
            if (C)
                printMatrix(C, n, "C = A * B");
            break;
        case 5:
            {
                std::cout << "\n--- DEMONSTRATION OF GAUSS-JORDAN INVERSE METHOD ---\n";
                try {
                    Matrix A(3, 3);
                    A(0, 0) = 2; A(0, 1) = -1; A(0, 2) = 0;
                    A(1, 0) = -1; A(1, 1) = 2; A(1, 2) = -1;
                    A(2, 0) = 0; A(2, 1) = -1; A(2, 2) = 2;

                    A.print("A");
                    std::cout << "\n----------------------------------\n";

                    auto start = std::chrono::high_resolution_clock::now();
                    Matrix A_inv = inverseMatrix(A);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;

                    std::cout << "Inverse matrix found by Gauss-Jordan:" << std::endl;
                    A_inv.print("A_inv");
                    std::cout << "\nTime taken for inversion: " << duration.count() << " seconds" << std::endl;

                } catch (const std::exception& e) {
                    std::cerr << "Error during Gauss-Jordan test: " << e.what() << std::endl;
                }
                break;
            }
        case 6:
            {
                std::cout << "\n--- DEMONSTRATION OF LU INVERSE METHOD ---\n";
                try {
                    int n = 3;
                    double **A = createMatrix(n);
                    A[0][0] = 2; A[0][1] = -1; A[0][2] = 0;
                    A[1][0] = -1; A[1][1] = 2; A[1][2] = -1;
                    A[2][0] = 0; A[2][1] = -1; A[2][2] = 2;
            
                    printMatrix(A, n, "A");
            
                    auto start = std::chrono::high_resolution_clock::now();
                    double **A_inv = inverseLU(A, n);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
            
                    printMatrix(A_inv, n, "A_inv (via LU)");
                    std::cout << "\nTime taken: " << duration.count() << " seconds" << std::endl;
            
                    deleteMatrix(A, n);
                    deleteMatrix(A_inv, n);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error during LU test: " << e.what() << std::endl;
                }
                break;
            }
        case 7:
        {
                //add here
            break;
        }

        case 0:
            cout << "Exit\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    if (A)
        deleteMatrix(A, n);
    if (B)
        deleteMatrix(B, n);
    if (C)
        deleteMatrix(C, n);

    return 0;
}
