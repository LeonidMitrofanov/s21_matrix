#include "test_s21_matrix.h"

START_TEST(test_s21_mult_matrix_valid) {
  matrix_t mat1, mat2, result;
  s21_create_matrix(2, 3, &mat1);  // Матрица 2x3
  s21_create_matrix(3, 2, &mat2);  // Матрица 3x2

  // Заполнение матрицы mat1
  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[0][2] = 3.0;
  mat1.matrix[1][0] = 4.0;
  mat1.matrix[1][1] = 5.0;
  mat1.matrix[1][2] = 6.0;

  // Заполнение матрицы mat2
  mat2.matrix[0][0] = 7.0;
  mat2.matrix[0][1] = 8.0;
  mat2.matrix[1][0] = 9.0;
  mat2.matrix[1][1] = 10.0;
  mat2.matrix[2][0] = 11.0;
  mat2.matrix[2][1] = 12.0;

  ck_assert_int_eq(s21_mult_matrix(&mat1, &mat2, &result), S21_OK);

  // Ожидаемый результат матрицы 2x2
  ck_assert_double_eq(result.matrix[0][0], 58.0);   // 1*7 + 2*9 + 3*11 = 58
  ck_assert_double_eq(result.matrix[0][1], 64.0);   // 1*8 + 2*10 + 3*12 = 64
  ck_assert_double_eq(result.matrix[1][0], 139.0);  // 4*7 + 5*9 + 6*11 = 139
  ck_assert_double_eq(result.matrix[1][1], 154.0);  // 4*8 + 5*10 + 6*12 = 154

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_incompatible_sizes) {
  matrix_t mat1, mat2, result;
  s21_create_matrix(2, 3, &mat1);  // Матрица 2x3
  s21_create_matrix(4, 2, &mat2);  // Матрица 4x2

  ck_assert_int_eq(s21_mult_matrix(&mat1, &mat2, &result), S21_CALC_ERROR);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_mult_matrix_null_pointers) {
  matrix_t mat1, mat2, result;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);

  ck_assert_int_eq(s21_mult_matrix(NULL, &mat2, &result), S21_ERROR);
  ck_assert_int_eq(s21_mult_matrix(&mat1, NULL, &result), S21_ERROR);
  ck_assert_int_eq(s21_mult_matrix(&mat1, &mat2, NULL), S21_ERROR);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_mult_matrix_zero_matrix) {
  matrix_t mat1, mat2, result;
  s21_create_matrix(2, 2, &mat1);  // Матрица 2x2
  s21_create_matrix(2, 2, &mat2);  // Матрица 2x2

  // Заполнение mat1 ненулевыми значениями
  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[1][0] = 3.0;
  mat1.matrix[1][1] = 4.0;

  // Заполнение mat2 нулями
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat2.matrix[i][j] = 0.0;
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&mat1, &mat2, &result), S21_OK);

  // Ожидаемый результат — матрица 2x2 с нулями
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  ck_assert_double_eq(result.matrix[0][1], 0.0);
  ck_assert_double_eq(result.matrix[1][0], 0.0);
  ck_assert_double_eq(result.matrix[1][1], 0.0);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_mult_matrix\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_mult_matrix_valid);
  tcase_add_test(tc_core, test_s21_mult_matrix_incompatible_sizes);
  tcase_add_test(tc_core, test_s21_mult_matrix_null_pointers);
  tcase_add_test(tc_core, test_s21_mult_matrix_zero_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}