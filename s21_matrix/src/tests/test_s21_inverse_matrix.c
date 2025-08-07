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
  ck_assert_int_eq(status, S21_CALC_ERROR);
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

START_TEST(test_s21_inverse_matrix_identity) {
  matrix_t A, result, I;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &I);

  // Создаем единичную матрицу
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
      I.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &I), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&I);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2x2) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  expected.matrix[0][0] = 0.6;
  expected.matrix[0][1] = -0.7;
  expected.matrix[1][0] = -0.2;
  expected.matrix[1][1] = 0.4;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_inverse_matrix_4x4) {
  matrix_t A, result, expected;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &expected);

  double src[4][4] = {{2, 1, 0, 0}, {3, 2, 0, 0}, {1, 1, 3, 4}, {2, -1, 2, 3}};
  double inv[4][4] = {
      {2, -1, 0, 0}, {-3, 2, 0, 0}, {31, -19, 3, -4}, {-23, 14, -2, 3}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = src[i][j];
      expected.matrix[i][j] = inv[i][j];
    }
  }

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_inverse_matrix_large_values) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1e10;
  A.matrix[0][1] = 2e10;
  A.matrix[1][0] = 3e10;
  A.matrix[1][1] = 4e10;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -2e-10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 1e-10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5e-10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.5e-10, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_near_singular) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.00001;  // Детерминант = 0.00001

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 400001, 0.1);
  ck_assert_double_eq_tol(result.matrix[0][1], -200000, 0.1);
  ck_assert_double_eq_tol(result.matrix[1][0], -200000, 0.1);
  ck_assert_double_eq_tol(result.matrix[1][1], 100000, 0.1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_zero_row) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, S21_CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_precision) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  // Матрица с числами, требующими высокой точности
  A.matrix[0][0] = 0.123456789;
  A.matrix[0][1] = 0.987654321;
  A.matrix[1][0] = -1.23456789;
  A.matrix[1][1] = 4.87654321;

  int status = s21_inverse_matrix(&A, &result);
  matrix_t check;
  s21_mult_matrix(&A, &result, &check);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_double_eq_tol(check.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(check.matrix[0][1], 0.0, 1e-7);
  ck_assert_double_eq_tol(check.matrix[1][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(check.matrix[1][1], 1.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_s21_inverse_matrix_rectangular) {
  matrix_t A, result;
  s21_create_matrix(3, 5, &A);
  double values[3][5] = {{1.00, 2.00, 3.00, 3.00, 2.00},
                         {5.00, 6.00, 7.00, 8.00, 9.00},
                         {10.00, 12.00, 13.00, 13.00, 12.00}};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = values[i][j];
    }
  }
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, S21_CALC_ERROR);
  s21_remove_matrix(&A);
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
  tcase_add_test(tc_core, test_s21_inverse_matrix_identity);
  tcase_add_test(tc_core, test_s21_inverse_matrix_2x2);
  tcase_add_test(tc_core, test_s21_inverse_matrix_4x4);
  tcase_add_test(tc_core, test_s21_inverse_matrix_large_values);
  tcase_add_test(tc_core, test_s21_inverse_matrix_near_singular);
  tcase_add_test(tc_core, test_s21_inverse_matrix_zero_row);
  tcase_add_test(tc_core, test_s21_inverse_matrix_precision);
  tcase_add_test(tc_core, test_s21_inverse_matrix_rectangular);

  suite_add_tcase(s, tc_core);

  return s;
}
