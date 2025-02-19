#include "test_s21_matrix.h"

START_TEST(test_s21_sub_matrix_valid) {
  matrix_t mat1, mat2, result;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);

  mat1.matrix[0][0] = 8.0;
  mat1.matrix[0][1] = 7.0;
  mat1.matrix[1][0] = 6.0;
  mat1.matrix[1][1] = 5.0;

  mat2.matrix[0][0] = 1.0;
  mat2.matrix[0][1] = 2.0;
  mat2.matrix[1][0] = 3.0;
  mat2.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_sub_matrix(&mat1, &mat2, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], 7.0);
  ck_assert_double_eq(result.matrix[0][1], 5.0);
  ck_assert_double_eq(result.matrix[1][0], 3.0);
  ck_assert_double_eq(result.matrix[1][1], 1.0);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_sub_matrix_diff_sizes) {
  matrix_t mat1, mat2, result;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(3, 2, &mat2);

  ck_assert_int_eq(s21_sub_matrix(&mat1, &mat2, &result), S21_CALC_ERROR);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_sub_matrix_null_pointers) {
  matrix_t mat1, result;
  s21_create_matrix(2, 2, &mat1);

  ck_assert_int_eq(s21_sub_matrix(NULL, &mat1, &result), S21_ERROR);
  ck_assert_int_eq(s21_sub_matrix(&mat1, NULL, &result), S21_ERROR);
  ck_assert_int_eq(s21_sub_matrix(&mat1, &mat1, NULL), S21_ERROR);

  s21_remove_matrix(&mat1);
}
END_TEST

Suite *s21_sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_sub_matrix\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sub_matrix_valid);
  tcase_add_test(tc_core, test_s21_sub_matrix_diff_sizes);
  tcase_add_test(tc_core, test_s21_sub_matrix_null_pointers);
  suite_add_tcase(s, tc_core);

  return s;
}