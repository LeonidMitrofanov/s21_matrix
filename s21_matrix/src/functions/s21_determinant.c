#include "../s21_matrix.h"

/*
 * Вычисление определителя матрицы.
 *
 * @param A Матрица, для которой нужно вычислить определитель.
 * @param result Указатель на переменную, в которую будет записан вычисленный
 * определитель.
 * @return S21_OK (0), если вычисление прошло успешно;
 *         S21_ERROR (1), если входные данные некорректны или возникла ошибка
 * при выделении памяти; S21_CALC_ERROR (2), если матрица не квадратная.
 */
int s21_determinant(matrix_t *A, double *result) {
  if (!s21_is_valide_matrix(A) || result == NULL) return S21_ERROR;
  if (A->rows != A->columns) return S21_CALC_ERROR;

  int n = A->rows;
  if (n == 1) {
    *result = A->matrix[0][0];
    return S21_OK;
  } else if (n == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return S21_OK;
  } else {
    double det = 0.0;
    for (int j = 0; j < n; j++) {
      double minor;
      if (s21_minor(A, 0, j, &minor) != S21_OK) return S21_ERROR;
      det += (1 - 2 * (j % 2)) * A->matrix[0][j] * minor;
    }
    *result = det;
    return S21_OK;
  }
}
