#include "../s21_matrix.h"

/*
 * Сложение матриц.
 * @param A Первая матрица для сложения.
 * @param B Вторая матрица для сложения.
 * @param result Указатель на структуру для сохранения результата сложения.
 * @return Код ошибки (0 - успех; 1 - ошибка,
 * некорректная матрица; 2 - ошибка вычисления).
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_is_valide_matrix(A) || !s21_is_valide_matrix(B)) return S21_ERROR;
  if (A->columns != B->columns || A->rows != B->rows) return S21_CALC_ERROR;

  if (s21_create_matrix(A->rows, A->columns, result) == S21_ERROR)
    return S21_ERROR;

  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

  return S21_OK;
}
