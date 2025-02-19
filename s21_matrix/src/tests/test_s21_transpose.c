#include "test_s21_matrix.h"

// Тест для транспонирования квадратной матрицы
START_TEST(test_s21_transpose_square_matrix) {
  matrix_t mat, result;
  s21_create_matrix(2, 2, &mat);

  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[1][0] = 3.0;
  mat.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_transpose(&mat, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], 3.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[1][1], 4.0);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для транспонирования прямоугольной матрицы (больше строк, чем столбцов)
START_TEST(test_s21_transpose_rectangular_matrix_more_rows) {
  matrix_t mat, result;
  s21_create_matrix(3, 2, &mat);

  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[1][0] = 3.0;
  mat.matrix[1][1] = 4.0;
  mat.matrix[2][0] = 5.0;
  mat.matrix[2][1] = 6.0;

  ck_assert_int_eq(s21_transpose(&mat, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], 3.0);
  ck_assert_double_eq(result.matrix[0][2], 5.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[1][1], 4.0);
  ck_assert_double_eq(result.matrix[1][2], 6.0);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для транспонирования прямоугольной матрицы (больше столбцов, чем строк)
START_TEST(test_s21_transpose_rectangular_matrix_more_columns) {
  matrix_t mat, result;
  s21_create_matrix(2, 3, &mat);

  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[0][2] = 3.0;
  mat.matrix[1][0] = 4.0;
  mat.matrix[1][1] = 5.0;
  mat.matrix[1][2] = 6.0;

  ck_assert_int_eq(s21_transpose(&mat, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[1][1], 5.0);
  ck_assert_double_eq(result.matrix[2][0], 3.0);
  ck_assert_double_eq(result.matrix[2][1], 6.0);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
}
END_TEST

// Тест на NULL указатель в матрице A
START_TEST(test_s21_transpose_null_pointer_A) {
  matrix_t result;
  ck_assert_int_eq(s21_transpose(NULL, &result), S21_ERROR);
}
END_TEST

// Тест на NULL указатель в результате result
START_TEST(test_s21_transpose_null_pointer_result) {
  matrix_t mat;
  s21_create_matrix(2, 2, &mat);
  ck_assert_int_eq(s21_transpose(&mat, NULL), S21_ERROR);
  s21_remove_matrix(&mat);
}
END_TEST

// Тест на пустую матрицу
START_TEST(test_s21_transpose_empty_matrix) {
  matrix_t mat = {0};
  matrix_t result;
  ck_assert_int_eq(s21_transpose(&mat, &result), S21_ERROR);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_transpose\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_transpose_square_matrix);
  tcase_add_test(tc_core, test_s21_transpose_rectangular_matrix_more_rows);
  tcase_add_test(tc_core, test_s21_transpose_rectangular_matrix_more_columns);
  tcase_add_test(tc_core, test_s21_transpose_null_pointer_A);
  tcase_add_test(tc_core, test_s21_transpose_null_pointer_result);
  tcase_add_test(tc_core, test_s21_transpose_empty_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}
