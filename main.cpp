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
    
    double vectorB[matrixSize]; // vector for b
    double vectorC[matrixSize]; // vector for c
    double vectorX[matrixSize]; // vector for x, the answer
    double matrixA[matrixSize][matrixSize]; // matrix for A
    double matrixL[matrixSize][matrixSize]; // matrix for L
    double matrixU[matrixSize][matrixSize]; // matrix for U

    // - Step 2 -
    cout << "\nInput the coefficients of the n x n matrix A: \n";
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        cout << "a" << i+1 << j+1 << ": ";
        cin >> matrixA[i][j];
      }
    }
    
    // - Step 3 -
    cout << "\nInput the coefficients of the vector b: \n";
    for (int i = 0; i < matrixSize; i++) {
      cout << "b" << i+1 << ": ";
      cin >> vectorB[i];
    }

    // - Step 4 -
    // TODO: Guassian Elimination:
    // The Following algorith doesn't work if the diagonals are ever zero. 
    double coefficientM;
    for (int h = 0; h < matrixSize-1; h++) {
      for (int i = h+1; i < matrixSize; i++) {
        if (matrixA[h][h] != 0) {
          coefficientM = matrixA[i][h]/matrixA[h][h];
          matrixL[i][h] = coefficientM;
          for (int j = h; j < matrixSize; j++) {
            matrixA[i][j] = matrixA[i][j] - (coefficientM * matrixA[h][j]);
          }
        }
      }
    }
    // Testing Purposes : Outputs A post Guassian Elimination
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        cout << matrixA[i][j] << " ";
        matrixU[i][j] = matrixA[i][j];
      }
      cout << "\n";
    }
    
    // - Step 5 - Solve for the c vector using L and b.
    double sumProductC = 0;
    for(int i = 0; i < matrixSize; i++) { 
      // ^ Loops through every row
      if(i > 0) {
        for(int j = 0; j < i; j++) { 
        // ^ Loops through the columns where j < i
        sumProductC += (matrixL[i][j] * vectorC[j]); 
        // ^ Used to calculate ci which is based on all previous c values.
        }
      }
      vectorC[i] = vectorB[i] - sumProductC; 
      // ^ Finds ci using bi and all previous values of c with their corresponding multipliers in matrix L.
      sumProductC = 0;
    }
    
    // - Step 6 - Solve for the x vector using U and c.
    double sumProductX = 0;
    for(int i = matrixSize-1; i >= 0; i--) { 
      // ^ Loops through every row starting at the end
      if(i < matrixSize-1) {
        for(int j = matrixSize-1; j > i; j--) { 
          // ^ Loops through every column starting at the end where j > i
          sumProductX += vectorX[j] * matrixU[i][j]; 
          // ^ Used to calculate xi to fill in what was already found for i after the last one
        }
      }
      vectorX[i] = ( (vectorC[i] - sumProductX) / matrixU[i][i] ); 
      // ^ Finds xi by taking the sum of ci and the sumProductX for row i, then dividing the sum by Matrix value uii
      sumProductX = 0;
    }

    // - Step 7 - 
    cout << "\n The solution values of x for Ax = b: \n";
    for (int i = 0; i < matrixSize; i++) {
      cout << "x" << i+1 << ": " << vectorX[i];
    }
    
    // - Step 8 - 
    cout << "Input 1 to solve another matrix (any other value to exit): ";
    cin >> input;
    if (input == 1) {
      repeat = true;
    }
    else {
      repeat = false;
    }
  } // End Loop
} // End Main
