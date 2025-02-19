#include "test_s21_matrix.h"

START_TEST(test_s21_remove_matrix_valid) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(test_s21_remove_matrix_null) {
  matrix_t matrix = {NULL, 0, 0};
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

Suite *s21_remove_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_remove_matrix\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_remove_matrix_valid);
  tcase_add_test(tc_core, test_s21_remove_matrix_null);
  suite_add_tcase(s, tc_core);

  return s;
}
