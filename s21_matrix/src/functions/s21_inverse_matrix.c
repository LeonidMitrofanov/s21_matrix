#include "../s21_matrix.h"

// Вычисляет матрицу алгебраических дополнений
static int s21_calculate_complements(matrix_t *A, matrix_t *complement) {
  int ret = s21_create_matrix(A->rows, A->columns, complement);
  if (ret != S21_OK) return S21_ERROR;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor;
      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != S21_OK)
        return S21_ERROR;

      if (s21_minor(A, &minor, i, j) != S21_OK) {
        s21_remove_matrix(&minor);
        return S21_ERROR;
      }

      double minor_det;
      ret = s21_determinant(&minor, &minor_det);
      s21_remove_matrix(&minor);
      if (ret != S21_OK) return S21_ERROR;

      complement->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_det;
    }
  }
  return S21_OK;
}

// Делит матрицу на определитель
static void s21_divide_by_determinant(matrix_t *matrix, double det) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] /= det;
    }
  }
}

// Основная функция обратной матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_is_valide_matrix(A) || result == NULL || A->rows != A->columns) {
    return S21_ERROR;
  }

  double det;
  if (s21_determinant(A, &det) != S21_OK || det == 0) {
    return S21_CALC_ERROR;
  }

  if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1.0 / det;
    return S21_OK;
  }

  matrix_t complement, transpose_complement;
  if (s21_calculate_complements(A, &complement) != S21_OK) {
    return S21_ERROR;
  }

  if (s21_transpose(&complement, &transpose_complement) != S21_OK) {
    s21_remove_matrix(&complement);
    return S21_ERROR;
  }
  s21_remove_matrix(&complement);

  if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
    s21_remove_matrix(&transpose_complement);
    return S21_ERROR;
  }

  s21_divide_by_determinant(&transpose_complement, det);
  *result = transpose_complement;
  return S21_OK;
}
