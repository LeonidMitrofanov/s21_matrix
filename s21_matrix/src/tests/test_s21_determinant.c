#include "test_s21_matrix.h"

START_TEST(test_s21_determinant_2x2) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 1.0;

  ck_assert_int_eq(s21_determinant(&A, &result), S21_OK);
  ck_assert_double_eq_tol(result, -10, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  double determinant;
  int status = s21_determinant(&A, &determinant);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(determinant, 1.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_invalid_non_square) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);

  double determinant;
  int status = s21_determinant(&A, &determinant);

  ck_assert_int_eq(status, S21_CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_singular_matrix) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 3.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;

  double determinant;
  int status = s21_determinant(&A, &determinant);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(determinant, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_invalid_null) {
  double determinant;
  int status = s21_determinant(NULL, &determinant);

  ck_assert_int_eq(status, S21_ERROR);
}
END_TEST

START_TEST(test_s21_determinant_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  double determinant;
  int status = s21_determinant(&A, &determinant);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(determinant, 5.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_small_diagonal) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1e-10;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 2e-10;
  A.matrix[1][1] = 1e-10;
  A.matrix[1][2] = 2e-10;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 1e-10;

  double determinant;
  int status = s21_determinant(&A, &determinant);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(determinant, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_singular_with_zero_in_U) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 0.0;

  double determinant;
  int status = s21_determinant(&A, &determinant);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(determinant, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_determinant\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_determinant_2x2);
  tcase_add_test(tc_core, test_s21_determinant_3x3);
  tcase_add_test(tc_core, test_s21_determinant_invalid_non_square);
  tcase_add_test(tc_core, test_s21_determinant_singular_matrix);
  tcase_add_test(tc_core, test_s21_determinant_invalid_null);
  tcase_add_test(tc_core, test_s21_determinant_1x1);
  tcase_add_test(tc_core, test_s21_determinant_small_diagonal);
  tcase_add_test(tc_core, test_s21_determinant_singular_with_zero_in_U);

  suite_add_tcase(s, tc_core);

  return s;
}