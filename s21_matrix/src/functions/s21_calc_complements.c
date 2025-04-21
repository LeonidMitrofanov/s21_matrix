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
  if (s21_create_matrix(n, n, result) != S21_OK) return S21_ERROR;

  double minor = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s21_minor(A, i, j, &minor) != S21_OK) {
        s21_remove_matrix(result);
        return S21_CALC_ERROR;
      }
      result->matrix[i][j] = (1 - 2 * ((i + j) % 2)) * minor;
    }
  }
  return S21_OK;
}
