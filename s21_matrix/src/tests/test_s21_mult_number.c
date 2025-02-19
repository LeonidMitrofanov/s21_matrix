#include "test_s21_matrix.h"

// Тесты для s21_mult_number

START_TEST(test_s21_mult_number_valid) {
  matrix_t mat, result;
  s21_create_matrix(2, 2, &mat);

  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[1][0] = 3.0;
  mat.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_mult_number(&mat, 2.0, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], 2.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 6.0);
  ck_assert_double_eq(result.matrix[1][1], 8.0);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_zero) {
  matrix_t mat, result;
  s21_create_matrix(2, 2, &mat);

  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[1][0] = 3.0;
  mat.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_mult_number(&mat, 0.0, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], 0.0);
  ck_assert_double_eq(result.matrix[0][1], 0.0);
  ck_assert_double_eq(result.matrix[1][0], 0.0);
  ck_assert_double_eq(result.matrix[1][1], 0.0);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_negative) {
  matrix_t mat, result;
  s21_create_matrix(2, 2, &mat);

  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = -2.0;
  mat.matrix[1][0] = 3.0;
  mat.matrix[1][1] = -4.0;

  ck_assert_int_eq(s21_mult_number(&mat, -2.0, &result), S21_OK);

  ck_assert_double_eq(result.matrix[0][0], -2.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], -6.0);
  ck_assert_double_eq(result.matrix[1][1], 8.0);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number_null_pointers) {
  matrix_t mat;
  s21_create_matrix(2, 2, &mat);

  ck_assert_int_eq(s21_mult_number(NULL, 2.0, NULL), S21_ERROR);
  ck_assert_int_eq(s21_mult_number(&mat, 2.0, NULL), S21_ERROR);
  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &mat), S21_ERROR);

  s21_remove_matrix(&mat);
}
END_TEST

Suite *s21_mult_number_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_mult_number\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_mult_number_valid);
  tcase_add_test(tc_core, test_s21_mult_number_zero);
  tcase_add_test(tc_core, test_s21_mult_number_negative);
  tcase_add_test(tc_core, test_s21_mult_number_null_pointers);
  suite_add_tcase(s, tc_core);

  return s;
}
