#include <iostream>
using namespace std;

int main() {
    bool repeat = true;
    int input;
    while (repeat) {
        // - Step 1 -
        int matrixSize;
        cout << "Input the size of the n x n matrix (must be a whole number >= 2): ";
        cin >> matrixSize; // Requests the size of the matrix before initiallizing the matrices.

        double* vectorB = new double[matrixSize]; // vector for b
        double* vectorC = new double[matrixSize]; // vector for c
        double* vectorX = new double[matrixSize]; // vector for x, the answer
        // matrix for A
        double** matrixA = new double*[matrixSize]; 
        for (int i = 0; i < matrixSize; i++) { matrixA[i] = new double[matrixSize]; }
        // matrix for L
        double** matrixL = new double* [matrixSize];
        for (int i = 0; i < matrixSize; i++) { matrixL[i] = new double[matrixSize]; }
        // matrix for U
        double** matrixU = new double* [matrixSize];
        for (int i = 0; i < matrixSize; i++) { matrixU[i] = new double[matrixSize]; }

        // - Step 2 -
        cout << "\nInput the coefficients of the n x n matrix A: \n";
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cout << "a" << i + 1 << j + 1 << ": ";
                cin >> matrixA[i][j];
            }
        }

        // - Step 3 -
        cout << "\nInput the coefficients of the vector b: \n";
        for (int i = 0; i < matrixSize; i++) {
            cout << "b" << i + 1 << ": ";
            cin >> vectorB[i];
        }

        // - Step 3.5 -
        // Check user input to make sure solution exists
        bool exists = true;
        double coefficientSum;
        for (int i = 0; i < matrixSize; i++) {
            coefficientSum = 0;
            for (int j = 0; j < matrixSize; j++) {
                coefficientSum += matrixA[i][j];
            }
            if (coefficientSum == 0 && vectorB[i] != 0)
                exists = false;
        }
        if (!exists) {
            cout << "\nThe system entered has no solution." << endl;
            return 0;
        }
        

        // - Step 4 -
        // TODO: Guassian Elimination:
        // The Following algorith doesn't work if the diagonals are ever zero. 
        double coefficientM;
        for (int h = 0; h < matrixSize - 1; h++) {
            for (int i = h + 1; i < matrixSize; i++) {
                if (matrixA[h][h] != 0) {
                    coefficientM = matrixA[i][h] / matrixA[h][h];
                    matrixL[i][h] = coefficientM;
                    for (int j = h; j < matrixSize; j++) {
                        matrixA[i][j] = matrixA[i][j] - (coefficientM * matrixA[h][j]);
                    }
                }
            }
        }

        // - Step 4.5 -
        // Check echelon form of matrix A for unique solution
        bool unique = true;
        for (int i = 0; i < matrixSize; i++) {
            if (matrixA[i][i] == 0)
                unique = false;
        }
        if (!unique) {
            cout << "\nSystem has infinitely many solutions or requires row swapping." << endl;
            return 0;
        }

        /* The following 3 nested for loops are for testing purposes:
           First Nested loop: Outputs Matrix A post Guassian Elimination
           Also, Sets Matrix U equal to Matrix A (Important!)
           Adds the missing 1 or 0 values to Matrix L when i = j or i < j, respectively (Important!)
        */
        cout << "\nMatrix A: \n";
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                if (i == j) {
                    matrixL[i][j] = 1;
                }
                else if (i < j) {
                    matrixL[i][j] = 0;
                }
                cout << matrixA[i][j] << " ";
                matrixU[i][j] = matrixA[i][j];
            }
            cout << "\n";
        }
        cout << "\nMatrix L: \n";
        // Outputs Matrix L
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cout << matrixL[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\nMatrix U: \n";
        // Outputs Matrix U
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cout << matrixU[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";

        // - Step 5 - Solve for the c vector using L and b.
        double sumProductC = 0;
        for (int i = 0; i < matrixSize; i++) {
            // ^ Loops through every row
            if (i > 0) {
                for (int j = 0; j < i; j++) {
                    // ^ Loops through the columns where j < i
                    sumProductC += (matrixL[i][j] * vectorC[j]);
                    // ^ Used to calculate ci which is based on all previous c values.
                }
            }
            vectorC[i] = vectorB[i] - sumProductC;
            // ^ Finds ci using bi and all previous values of c with their corresponding multipliers in matrix L.
            sumProductC = 0;
        }

        // output vector C to check
        cout << "\nVector C: \n";
        for (int i = 0; i < matrixSize; i++) {
            cout << vectorC[i] << "\n";
        }

        // - Step 6 - Solve for the x vector using U and c.
        double sumProductX = 0;
        for (int i = matrixSize - 1; i >= 0; i--) {
            // ^ Loops through every row starting at the end
            if (i < matrixSize - 1) {
                for (int j = matrixSize - 1; j > i; j--) {
                    // ^ Loops through every column starting at the end where j > i
                    sumProductX += vectorX[j] * matrixU[i][j];
                    // ^ Used to calculate xi to fill in what was already found for i after the last one
                }
            }
            if (matrixU[i][i] != 0) {
                vectorX[i] = ((vectorC[i] - sumProductX) / matrixU[i][i]);
            }
            else {
                vectorX[i] = 0;
            }
            // ^ Finds xi by taking the sum of ci and the sumProductX for row i, then dividing the sum by Matrix value uii
            sumProductX = 0;
        }

        // - Step 7 - 
        cout << "\n The solution values of x for Ax = b: \n";
        for (int i = 0; i < matrixSize; i++) {
            cout << " x" << i + 1 << ": " << vectorX[i];
        }

        // - Step 8 - 
        cout << "\nInput 1 to solve another matrix (any other value to exit): ";
        cin >> input;
        if (input == 1) {
            repeat = true;
        }
        else {
            repeat = false;
        }
    } // End Loop
} // End Main
