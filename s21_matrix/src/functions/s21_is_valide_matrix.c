#include "../s21_matrix.h"

/*
 * Проверка корректности структуры матрицы.
 *
 * @param A Указатель на структуру матрицы, которую нужно проверить.
 * @return Код состояния (1 - матрица корректна, 0 - матрица некорректна).
 */
int s21_is_valide_matrix(matrix_t *A) {
  if (A == NULL) return FAILURE;
  if (A->matrix == NULL) return FAILURE;
  if (A->rows <= 0 || A->columns <= 0) return FAILURE;

  return SUCCESS;
}