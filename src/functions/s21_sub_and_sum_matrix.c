#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (!s21_valid_matrix(A) || !s21_valid_matrix(B)) {
    status = ERR_INCORRECT_MATRIX;
    return status;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    status = ERR_CALCULATION;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      status = ERR_INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          if (!isfinite(result->matrix[i][j])) {
            status = ERR_CALCULATION;
            return status;
          }
        }
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (!s21_valid_matrix(A) || !s21_valid_matrix(B)) {
    status = ERR_INCORRECT_MATRIX;
    return status;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    status = ERR_CALCULATION;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      status = ERR_INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          if (!isfinite(result->matrix[i][j])) {
            status = ERR_CALCULATION;
            return status;
          }
        }
      }
    }
  }
  return status;
}