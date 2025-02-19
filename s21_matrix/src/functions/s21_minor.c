#include "../s21_matrix.h"

/*
 * Вычисление минора функции.
 * @param A - Исходная матрица.
 * @param row_to_esc Строка для исключения.
 * @param column_to_esc Столбец для исключения.
 * @param minor Указатель на структуру для сохранения результата.
 * @return Код ошибки (0 - успех;
 * 1 - ошибка, некорректная матрица;
 * 2 - ошибка вычисления).
 */
int s21_minor(matrix_t *A, matrix_t *minor, int row_to_esc, int column_to_esc) {
  // Проверка на корректность матрицы и результата
  if (!s21_is_valide_matrix(A)) return S21_ERROR;

  // Инициализация minor
  if (s21_create_matrix(A->rows - 1, A->columns - 1, minor) != S21_OK)
    return S21_ERROR;

  for (int i = 0, minor_i = 0; i < A->rows; i++) {
    if (i == row_to_esc) {
      continue;
    }
    for (int j = 0, minor_j = 0; j < A->columns; j++) {
      if (j == column_to_esc) continue;

      minor->matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }

  return S21_OK;
}
