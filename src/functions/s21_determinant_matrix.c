#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  if (!s21_valid_matrix(A)) {
    status = ERR_INCORRECT_MATRIX;
    return status;
  }
  if (A->columns != A->rows) {
    status = ERR_CALCULATION;
    return status;
  }
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->columns; i++) {
      if (A->matrix[i][0] != 0) {
        double minor_res = 0;
        matrix_t minor_matrix = {0};
        status = s21_minor_matrix(A, i, 0, &minor_matrix);
        if (status != OK) {
          return status;
        }
        status = s21_determinant(&minor_matrix, &minor_res);
        if (status != OK) {
          return status;
        }
        *result += A->matrix[i][0] * minor_res * pow(-1, i);
        s21_remove_matrix(&minor_matrix);
      }
    }
  }
  return status;
}