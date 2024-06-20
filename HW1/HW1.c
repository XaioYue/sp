#include <stdio.h>
#include <stdlib.h>

// 轉置矩陣
void transpose(double *matrix, double *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
}

// 矩陣相加
void add(double *matrix1, double *matrix2, double *result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i * cols + j] = matrix1[i * cols + j] + matrix2[i * cols + j];
        }
    }
}

// 矩陣相乘
void multiply(double *matrix1, double *matrix2, double *result, int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

// 印出矩陣
void dump(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

// 改變矩陣形狀
void reshape(double *matrix, double *result, int old_rows, int old_cols, int new_rows, int new_cols) {
    if (old_rows * old_cols != new_rows * new_cols) {
        printf("Reshape error: Total elements must remain the same.\n");
        return;
    }
    for (int i = 0; i < old_rows * old_cols; i++) {
        result[i] = matrix[i];
    }
}

int main() {
    int rows1 = 2, cols1 = 3;
    double matrix1[] = {1, 2, 3, 4, 5, 6};
    
    int rows2 = 3, cols2 = 2;
    double matrix2[] = {7, 8, 9, 10, 11, 12};
    
    double result[6];

    printf("Matrix 1:\n");
    dump(matrix1, rows1, cols1);

    printf("Matrix 2:\n");
    dump(matrix2, rows2, cols2);

    // Transpose
    double transpose_result[6];
    transpose(matrix1, transpose_result, rows1, cols1);
    printf("Transpose of Matrix 1:\n");
    dump(transpose_result, cols1, rows1);

    // Add (assuming matrices are of same dimensions)
    double add_result[6];
    add(matrix1, matrix1, add_result, rows1, cols1); // Adding matrix1 to itself for demonstration
    printf("Addition of Matrix 1 and itself:\n");
    dump(add_result, rows1, cols1);

    // Multiply
    double multiply_result[4];
    multiply(matrix1, matrix2, multiply_result, rows1, cols1, cols2);
    printf("Multiplication of Matrix 1 and Matrix 2:\n");
    dump(multiply_result, rows1, cols2);

    // Reshape (optional)
    double reshape_result[6];
    reshape(matrix1, reshape_result, rows1, cols1, 3, 2);
    printf("Reshape of Matrix 1 to 3x2:\n");
    dump(reshape_result, 3, 2);

    return 0;
}
