#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  if (!s21_valid_matrix(A)) {
    status = ERR_INCORRECT_MATRIX;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      status = ERR_INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
          if (!isfinite(result->matrix[i][j])) {
            s21_remove_matrix(result);
            status = ERR_CALCULATION;
            return status;
          }
        }
      }
    }
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (!s21_valid_matrix(A) || !s21_valid_matrix(B)) {
    status = ERR_INCORRECT_MATRIX;
    return status;
  }
  if (A->columns != B->rows) {
    status = ERR_CALCULATION;
  } else {
    if (s21_create_matrix(A->rows, B->columns, result) != OK) {
      status = ERR_INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            if (!isfinite(result->matrix[i][j])) {
              status = ERR_CALCULATION;
              return status;
            }
          }
        }
      }
    }
  }
  return status;
}