#include "../s21_matrix.h"

/*
 * Вычисление минора матрицы.
 * @param A - Исходная матрица.
 * @param row_to_esc Строка для исключения.
 * @param column_to_esc Столбец для исключения.
 * @param result Указатель на переменную, для сохранения минора.
 * @return Код ошибки (0 - успех;
 * 1 - ошибка, некорректная матрица;
 * 2 - ошибка вычисления).
 */
int s21_minor(matrix_t *A, int row_to_esc, int column_to_esc, double *result) {
  if (!s21_is_valide_matrix(A)) return S21_ERROR;

  matrix_t minor;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != S21_OK)
    return S21_ERROR;

  for (int i = 0, minor_i = 0; i < A->rows; i++) {
    if (i == row_to_esc) continue;
    for (int j = 0, minor_j = 0; j < A->columns; j++) {
      if (j == column_to_esc) continue;
      minor.matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }
  int flag = s21_determinant(&minor, result);
  s21_remove_matrix(&minor);
  if (flag != S21_OK) return flag;

  return S21_OK;
}
