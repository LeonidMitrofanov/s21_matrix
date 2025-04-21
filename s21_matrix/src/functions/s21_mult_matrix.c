#include "../s21_matrix.h"

/*
 * Умножение матриц.
 * @param A Первая матрица для умножения.
 * @param B Вторая матрица для умножения.
 * @param result Указатель на структуру для сохранения результата умножения.
 * @return Код ошибки (0 - успех, 1 - ошибка,
 * некорректная матрица, 2 - ошибка вычисления).
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_is_valide_matrix(A) || !s21_is_valide_matrix(B)) return S21_ERROR;
  if (A->columns != B->rows) return S21_CALC_ERROR;

  if (s21_create_matrix(A->rows, B->columns, result) == S21_ERROR)
    return S21_ERROR;

  for (int i = 0; i < result->rows; i++)
    for (int j = 0; j < result->columns; j++)
      for (int k = 0; k < A->columns; k++)
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];

  return S21_OK;
}
