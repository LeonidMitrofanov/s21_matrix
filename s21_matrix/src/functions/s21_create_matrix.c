#include "../s21_matrix.h"

/*
 * Создает матрицу с заданным числом строк и столбцов.
 * @param rows Количество строк.
 * @param columns Количество столбцов.
 * @param result Указатель на структуру, куда будет сохранена созданная матрица.
 * @return Код ошибки (0 - успех, 1 - ошибка).
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // Проверка на NULL
  if (result == NULL) return S21_ERROR;

  // Проверка на корректность размеров матрицы
  if (rows <= 0 || columns <= 0) return S21_ERROR;

  // Инициализация полей структуры matrix_t
  result->rows = rows;
  result->columns = columns;

  // Выделение памяти под массив указателей на строки
  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL) return S21_ERROR;

  // Выделение памяти под элементы матрицы (всех строк)
  result->matrix[0] = (double *)calloc(rows * columns, sizeof(double));
  if (result->matrix[0] == NULL) {
    free(result->matrix);
    result->matrix = NULL;
    return S21_ERROR;
  }

  // Привязка строк к элементам матрицы
  for (int i = 1; i < rows; i++)
    result->matrix[i] = result->matrix[0] + i * columns;

  return S21_OK;  // Возврат успешного кода
}
