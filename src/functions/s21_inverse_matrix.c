#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (!s21_valid_matrix(A)) {
    status = ERR_INCORRECT_MATRIX;
    return status;
  }
  if (A->columns != A->rows) {
    status = ERR_CALCULATION;
  } else {
    double determinant = 0;
    status = s21_determinant(A, &determinant);
    if (determinant == 0) {
      status = ERR_CALCULATION;
      return status;
    }
    if (status == OK && A->rows == 1 && A->columns == 1) {
      if (s21_create_matrix(A->rows, A->columns, result) != OK) {
        status = ERR_INCORRECT_MATRIX;
      } else {
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      }
    }
    if (status == OK && A->rows > 1 && A->columns > 1) {
      matrix_t alg_dop = {0};
      status = s21_calc_complements(A, &alg_dop);
      if (status != OK) {
        return status;
      }
      status = s21_transpose(&alg_dop, result);
      if (status != OK) {
        return status;
      }
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] /= determinant;
        }
      }
      s21_remove_matrix(&alg_dop);
    }
  }
  return status;
}