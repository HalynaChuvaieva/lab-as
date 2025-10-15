#include <iostream>
#include <cmath>
using namespace std;

#include "strassen.h"

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
