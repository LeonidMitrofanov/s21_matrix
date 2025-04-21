#include "../s21_matrix.h"

/*
 * Создание матрицы с заданным числом строк и столбцов.
 * @param rows Количество строк.
 * @param columns Количество столбцов.
 * @param result Указатель на структуру, куда будет сохранена созданная матрица.
 * @return Код возврата (0 - успех, 1 - ошибка).
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL) return S21_ERROR;
  if (rows <= 0 || columns <= 0) return S21_ERROR;

  result->rows = rows;
  result->columns = columns;

  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) return S21_ERROR;

  result->matrix[0] = (double *)calloc(rows * columns, sizeof(double));
  if (result->matrix[0] == NULL) {
    free(result->matrix);
    result->matrix = NULL;
    return S21_ERROR;
  }

  for (int i = 1; i < rows; i++)
    result->matrix[i] = result->matrix[0] + i * columns;

  return S21_OK;
}
