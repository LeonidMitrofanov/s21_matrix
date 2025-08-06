#include "../s21_matrix.h"

/*
 * Вычисление обратной матрицы.
 * @param A Указатель на исходную квадратную матрицу.
 * @param result Указатель на структуру для сохранения обратной матрицы.
 * @return Код ошибки (0 - успех;
 * 1 - ошибка, некорректная матрица;
 * 2 - ошибка вычисления).
 */
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

  char error_flag = 0;
  matrix_t complement, transpose_complement;
  error_flag += s21_calc_complements(A, &complement) != S21_OK;
  error_flag += s21_transpose(&complement, &transpose_complement) != S21_OK;
  s21_remove_matrix(&complement);
  error_flag += s21_create_matrix(A->rows, A->columns, result) != S21_OK;

  if (error_flag) {
    s21_remove_matrix(&transpose_complement);
    return S21_ERROR;
  }

  s21_mult_number(&transpose_complement, 1. / det, result);
  return S21_OK;
}
