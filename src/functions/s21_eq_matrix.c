#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (!s21_valid_matrix(A) || !s21_valid_matrix(B) || A->rows != B->rows ||
      A->columns != B->columns) {
    status = FAILURE;
    return status;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if ((fabs(A->matrix[i][j] - B->matrix[i][j])) >= 1e-7) {
        status = FAILURE;
        return status;
      }
    }
  }
  return status;
}