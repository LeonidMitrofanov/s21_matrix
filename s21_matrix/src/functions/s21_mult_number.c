#include "../s21_matrix.h"

/*
 * Умножает матрицу на скалярное значение.
 * @param A Матрица для умножения.
 * @param number Скалярное значение для умножения.
 * @param result Указатель на структуру для сохранения результата умножения.
 * @return Код ошибки (0 - успех;
 * 1 - ошибка, некорректная матрица;
 * 2 - ошибка вычисления).
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // Проверка на корректность матрицы и результата
  if (!s21_is_valide_matrix(A)) return S21_ERROR;

  // Инициализация result
  if (s21_create_matrix(A->rows, A->columns, result) == S21_ERROR)
    return S21_ERROR;

  // Умножение каждого элемента матрицы на число
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;

  return S21_OK;
}
