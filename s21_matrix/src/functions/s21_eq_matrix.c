#include "../s21_matrix.h"

/*
 * Сравнивает две матрицы на равенство.
 * @param A Первая матрица для сравнения.
 * @param B Вторая матрица для сравнения.
 * @return 1 - матрицы равны, 0 - матрицы не равны.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // Проверка матриц на корректность
  if (!s21_is_valide_matrix(A) || !s21_is_valide_matrix(B)) return FAILURE;

  // Проверка на соответствие размеров
  if (A->columns != B->columns || A->rows != B->rows) return FAILURE;

  // Сравнение элементов матриц
  if (memcmp(A->matrix[0], B->matrix[0],
             A->rows * A->columns * sizeof(double)) != 0)
    return FAILURE;

  return SUCCESS;
}
