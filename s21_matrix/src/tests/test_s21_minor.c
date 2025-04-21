#include "test_s21_matrix.h"

START_TEST(test_s21_minor_valid) {
  matrix_t A;
  double minor;
  s21_create_matrix(3, 3, &A);

  // Заполнение матрицы A
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_minor(&A, 1, 1, &minor), S21_OK);
  ck_assert_double_eq(minor, -12.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_minor_invalid_matrix) {
  matrix_t A;
  double minor;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;

  ck_assert_int_eq(s21_minor(&A, 0, 0, &minor), S21_ERROR);
}
END_TEST

START_TEST(test_s21_minor_single_element_matrix) {
  matrix_t A;
  double minor;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 42.0;

  ck_assert_int_eq(s21_minor(&A, 0, 0, &minor), S21_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_minor_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_minor\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_minor_valid);
  tcase_add_test(tc_core, test_s21_minor_invalid_matrix);
  tcase_add_test(tc_core, test_s21_minor_single_element_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}
