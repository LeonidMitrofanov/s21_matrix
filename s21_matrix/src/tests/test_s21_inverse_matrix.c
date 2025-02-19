#include "test_s21_matrix.h"

START_TEST(test_s21_inverse_matrix_3x3) {
  matrix_t m, B, R;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &B);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;

  int status = s21_inverse_matrix(&m, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  ck_assert_int_eq(status, S21_OK);
  s21_remove_matrix(&m);
  s21_remove_matrix(&R);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_inverse_matrix_invalid_non_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_singular) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 2.0;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_invalid_null) {
  matrix_t *A = NULL, *result = NULL;

  int status = s21_inverse_matrix(A, result);

  ck_assert_int_eq(status, S21_ERROR);
}
END_TEST

START_TEST(test_s21_inverse_matrix_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.2, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_small_values) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1e-3;
  A.matrix[0][1] = 2e-3;
  A.matrix[1][0] = 3e-3;
  A.matrix[1][1] = 4e-3;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -2e3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 1e3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5e3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.5e3, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_inverse_matrix\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_inverse_matrix_3x3);
  tcase_add_test(tc_core, test_s21_inverse_matrix_invalid_non_square);
  tcase_add_test(tc_core, test_s21_inverse_matrix_singular);
  tcase_add_test(tc_core, test_s21_inverse_matrix_invalid_null);
  tcase_add_test(tc_core, test_s21_inverse_matrix_1x1);
  tcase_add_test(tc_core, test_s21_inverse_matrix_small_values);

  suite_add_tcase(s, tc_core);

  return s;
}
