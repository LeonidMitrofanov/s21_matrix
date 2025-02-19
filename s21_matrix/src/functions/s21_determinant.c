#include "../s21_matrix.h"

/*
 * Вычисляет определитель матрицы рекурсивно через разложение по минорам
 * (формула Лапласа).
 *
 * @param A Матрица, для которой нужно вычислить определитель.
 * @param result Указатель на переменную, в которую будет записан вычисленный
 * определитель.
 * @return S21_OK (0), если вычисление прошло успешно;
 *         S21_ERROR (1), если входные данные некорректны или возникла ошибка
 * при выделении памяти; S21_CALC_ERROR (2), если матрица не квадратная.
 */
int s21_determinant(matrix_t *A, double *result) {
  // Проверка валидности входных данных
  if (!s21_is_valide_matrix(A) || result == NULL) return S21_ERROR;

  // Проверка на квадратность матрицы
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
    // Разложение по первой строке
    for (int j = 0; j < n; j++) {
      matrix_t minor;
      // Создаем минор размером (n-1)x(n-1)
      if (s21_create_matrix(n - 1, n - 1, &minor) != S21_OK) return S21_ERROR;
      // Формируем минор, исключая 0-ю строку и j-й столбец.
      // Функция s21_minor должна заполнить матрицу minor соответствующими
      // элементами.
      if (s21_minor(A, &minor, 0, j) != S21_OK) {
        s21_remove_matrix(&minor);
        return S21_ERROR;
      }
      double minor_det = 0.0;
      int ret = s21_determinant(&minor, &minor_det);
      // Освобождаем память, выделенную под минорную матрицу
      s21_remove_matrix(&minor);
      if (ret != S21_OK) return ret;
      // Прибавляем вклад текущего элемента с учетом знака
      det += ((j % 2 == 0) ? 1.0 : -1.0) * A->matrix[0][j] * minor_det;
    }
    *result = det;
    return S21_OK;
  }
}
