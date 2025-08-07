#include "../s21_matrix.h"

/*
 * Вычисление матрицы алгебраических дополнений.
 * @param A Квадратная матрица, для которой нужно вычислить алгебраические
 * дополнения.
 * @param result Указатель на структуру для сохранения результата вычисления.
 * @return Код ошибки (0 - успех;
 * 1 - ошибка, некорректная матрица;
 * 2 - ошибка вычисления).
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_is_valide_matrix(A) || result == NULL) return S21_ERROR;
  if (A->rows != A->columns) return S21_CALC_ERROR;

  int n = A->rows;
  if (n == 1) {
    if (s21_create_matrix(1, 1, result) != S21_OK) return S21_ERROR;
    result->matrix[0][0] = 1.0;
    return S21_OK;
  }
  s21_create_matrix(n, n, result);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double minor = 0.0;
      int status = s21_minor(A, i, j, &minor);
      if (status != S21_OK) {
        s21_remove_matrix(result);
        return S21_CALC_ERROR;
      }
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result->matrix[i][j] = sign * minor;
    }
  }
  return S21_OK;
}
