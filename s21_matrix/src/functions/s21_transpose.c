#include "../s21_matrix.h"

/*
 * Транспонирует матрицу.
 * @param A Матрица для транспонирования.
 * @param result Указатель на структуру для сохранения транспонированной
 * матрицы.
 * @return Код ошибки (0 - успех; 1 - ошибка,
 * некорректная матрица; 2 - ошибка вычисления).
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  // Проверка на корректность матрицы и результата
  if (!s21_is_valide_matrix(A)) return S21_ERROR;

  // Инициализация result
  if (s21_create_matrix(A->columns, A->rows, result) == S21_ERROR)
    return S21_ERROR;

  for (int i = 0; i < result->rows; i++)
    for (int j = 0; j < result->columns; j++)
      result->matrix[i][j] = A->matrix[j][i];

  return S21_OK;
}
