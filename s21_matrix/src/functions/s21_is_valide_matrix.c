#include "../s21_matrix.h"

/*
 * Проверяет корректность структуры матрицы.
 *
 * @param A Указатель на структуру матрицы, которую нужно проверить.
 * @return Код состояния (1 - матрица корректна, 0 - матрица некорректна).
 */
int s21_is_valide_matrix(matrix_t *A) {
  // Проверка на NULL
  if (A == NULL) return FAILURE;

  // Проверка на NULL в матрицах
  if (A->matrix == NULL) return FAILURE;

  // Проверка на корректность размеров матрицы
  if (A->rows <= 0 || A->columns <= 0) return FAILURE;

  return SUCCESS;
}