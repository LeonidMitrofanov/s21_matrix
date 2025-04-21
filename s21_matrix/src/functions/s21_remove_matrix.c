#include "../s21_matrix.h"

/*
 * Освобождение памяти.
 * @param A Указатель на структуру матрицы, которую нужно очистить.
 */
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      if (A->matrix[0] != NULL) {
        free(A->matrix[0]);
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
  }
}
