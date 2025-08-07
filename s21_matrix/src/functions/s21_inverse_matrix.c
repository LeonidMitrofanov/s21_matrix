#include "../s21_matrix.h"

/*
 * Вычисление обратной матрицы.
 * @param A Указатель на исходную квадратную матрицу.
 * @param result Указатель на структуру для сохранения обратной матрицы.
 * @return Код ошибки (0 - успех;
 * 1 - ошибка, некорректная матрица;
 * 2 - ошибка вычисления).
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_is_valide_matrix(A) || result == NULL) return S21_ERROR;
  if (A->rows != A->columns) return S21_CALC_ERROR;

  double det = 0.0;
  if (s21_determinant(A, &det) != S21_OK) return S21_CALC_ERROR;
  if (det == 0) return S21_CALC_ERROR;
  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) != S21_OK) return S21_ERROR;
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return S21_OK;
  }

  matrix_t complements;
  s21_calc_complements(A, &complements);
  matrix_t transposed;
  s21_transpose(&complements, &transposed);

  int status = s21_mult_number(&transposed, 1.0 / det, result);
  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);

  return status;
}