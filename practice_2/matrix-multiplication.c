#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// Multiply matrixes
int** matrix_multiplication(int rows_a, int cols_a, int** A, int rows_b, int cols_b, int** B){
    int **returnMat = (int **)malloc(rows_a * sizeof(int *));
    for (int w = 0; w < rows_a; w++) {
        returnMat[w] = (int *)malloc(cols_b * sizeof(int));
    }
    int i,j,k, auxSum;
    #pragma omp parallel for private(i,j,k) shared(A,B,returnMat,rows_a,cols_b,rows_b) reduction(+: auxSum)
    for (i = 0; i < rows_a; i++){
        for (j = 0; j < cols_b; j++){
            auxSum = 0;
            for (k = 0; k < rows_b; k++){
                auxSum += (A[i][k] * B[k][j]);
            }
            returnMat[i][j] = auxSum;
        }
    }

    return returnMat;
}

// Function to generate a random matrix
int** generate_random_matrix(int row, int col){
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
    omp_set_num_threads(numThreads);
    int arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int arr2[3][2] ={{7,8},{9,10},{11,12}};
    int** matMul = matrix_multiplication(20,30,generate_random_matrix(20,30),30,20,generate_random_matrix(30,20));
    print_result(20,20,matMul);
}