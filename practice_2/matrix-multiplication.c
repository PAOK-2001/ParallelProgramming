// Matrix Multiplication 
// Pablo Agustín Ortega Kral A00344664
// 05/11/2022
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// Multiply matrixes
int** matrix_multiplication(int rows_a, int cols_a, int** A, int rows_b, int cols_b, int** B){
    //Creating memory location to store return matrix.
    int **returnMat = (int **)malloc(rows_a * sizeof(int *));
    for (int w = 0; w < rows_a; w++) {
        returnMat[w] = (int *)malloc(cols_b * sizeof(int));
    }
    // Auxiliary variables used in matrix computation
    int i,j,k, auxSum;
    #pragma omp parallel for private(i,j,k) shared(A,B,returnMat,rows_a,cols_b,rows_b) reduction(+: auxSum)
    for (i = 0; i < rows_a; i++){
        for (j = 0; j < cols_b; j++){
            auxSum = 0;
            for (k = 0; k < rows_b; k++){
                //Iterate both matrixes multiplying each row of A by each column of B
                auxSum += (A[i][k] * B[k][j]); //Temp value where reduction is performed.
            }
            returnMat[i][j] = auxSum;
        }
    }

    return returnMat;
}

// Function to generate a random matrix
int** generate_random_matrix(int row, int col){
    //Allocate memory space 
    int **returnMat = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        returnMat[i] = (int *)malloc(col * sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            returnMat[i][j] = rand() % 10;
        }
    }

    return returnMat;
}

// Function to convert statically allocated matrixes to dynamically allocated.
int**static2malloc(int row, int col, int mat[row][col]){
    int **returnMat = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        returnMat[i] = (int *)malloc(col * sizeof(int));
    }

    //Copy value from statical matrix to malloc pointer
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            returnMat[i][j] = mat[i][j];
            int r = returnMat[i][j];
        }
    }
    return returnMat;
};


void print_result(int rows, int cols, int** matrix2print){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ",matrix2print[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char* argv[]){ 
    int numThreads = strtol(argv[1], NULL, 10);
    int mSize = strtol(argv[2], NULL, 10);
    int doPrint = strtol(argv[3], NULL, 10);

    if(numThreads >1){
        omp_set_num_threads(numThreads);
    }else{
        omp_set_num_threads(1);
    }
    int** matMul = matrix_multiplication(mSize,mSize,generate_random_matrix(mSize,mSize),mSize,mSize,generate_random_matrix(mSize,mSize));
    if(doPrint == 1){
        print_result(mSize,mSize,matMul);
    }
}

 /*Validation test case
    int arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int arr2[3][2] ={{7,8},{9,10},{11,12}};
    int ** matMul = matrix_multiplication(2,3,static2malloc(2,3,arr1),3,2,static2malloc(3,2,arr2));
    if(doPrint == 1){
        print_result(2,2,matMul);
    }
 */