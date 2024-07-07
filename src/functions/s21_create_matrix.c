#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (rows < 1 || columns < 1 || result == NULL) {
    status = ERR_INCORRECT_MATRIX;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      status = ERR_INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          status = ERR_INCORRECT_MATRIX;
          break;
        }
      }
    }
  }
  if (status == OK) {
    result->rows = rows;
    result->columns = columns;
  }
  return status;
}

int s21_valid_matrix(matrix_t *A) {
  return A != NULL && A->columns > 0 && A->rows > 0;
}

void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step) {
  if (A != NULL && A->matrix != NULL) {
    double value = start_value;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value;
        value += iteration_step;
      }
    }
  }
}