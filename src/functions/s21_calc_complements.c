#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A->rows == 1 || A->columns == 1) {
    status = ERR_CALCULATION;
    return status;
  }
  if (!s21_valid_matrix(A)) {
    status = ERR_INCORRECT_MATRIX;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      status = ERR_INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows && status == OK; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor_matrix = {0};
          status = s21_minor_matrix(A, i, j, &minor_matrix);
          double determinant = 0;
          status = s21_determinant(&minor_matrix, &determinant);
          result->matrix[i][j] = determinant * pow(-1, i + j);
          s21_remove_matrix(&minor_matrix);
        }
      }
    }
  }
  return status;
}

int s21_minor_matrix(matrix_t *A, int i, int j, matrix_t *result) {
  int status = OK;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, result) != OK) {
    status = ERR_INCORRECT_MATRIX;
  } else {
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < A->columns; n++) {
        if (m == i || n == j) continue;
        if (m < i && n < j) {
          result->matrix[m][n] = A->matrix[m][n];
        } else if (m < i && n > j) {
          result->matrix[m][n - 1] = A->matrix[m][n];
        } else if (m > i && n < j) {
          result->matrix[m - 1][n] = A->matrix[m][n];
        } else if (m > i && n > j) {
          result->matrix[m - 1][n - 1] = A->matrix[m][n];
        }
      }
    }
  }
  return status;
}
