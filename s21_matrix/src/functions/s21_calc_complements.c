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

  // Для каждой позиции (i, j) вычисляем определитель минорной матрицы
  // итеративно.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix_t minor;
      if (s21_create_matrix(n - 1, n - 1, &minor) != S21_OK) return S21_ERROR;
      // Заполнение минорной матрицы без использования рекурсии
      int minor_row = 0;
      for (int row = 0; row < n; row++) {
        if (row == i) continue;
        int minor_col = 0;
        for (int col = 0; col < n; col++) {
          if (col == j) continue;
          minor.matrix[minor_row][minor_col] = A->matrix[row][col];
          minor_col++;
        }
        minor_row++;
      }
      double minor_det = 0.0;
      // Вместо рекурсии можно, например, применить метод Гаусса для вычисления
      // определителя минорной матрицы. Здесь предполагаем, что функция
      // s21_determinant уже реализована, даже если она рекурсивная.
      if (s21_determinant(&minor, &minor_det) != S21_OK) {
        s21_remove_matrix(&minor);
        return S21_ERROR;
      }
      result->matrix[i][j] = minor_det * (((i + j) % 2 == 0) ? 1.0 : -1.0);
      s21_remove_matrix(&minor);
    }
  }
  return S21_OK;
}
