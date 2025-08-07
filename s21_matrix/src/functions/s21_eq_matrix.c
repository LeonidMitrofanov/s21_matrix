#include "../s21_matrix.h"

/*
 * Сравнение матриц на равенство.
 * @param A Первая матрица для сравнения.
 * @param B Вторая матрица для сравнения.
 * @return 1 - матрицы равны, 0 - матрицы не равны.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!s21_is_valide_matrix(A) || !s21_is_valide_matrix(B)) return FAILURE;
  if ((A->columns != B->columns) || (A->rows != B->rows)) return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}
