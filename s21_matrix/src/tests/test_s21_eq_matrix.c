#include "test_s21_matrix.h"

START_TEST(test_s21_eq_matrix_null_pointers) {
  matrix_t mat;
  s21_create_matrix(2, 2, &mat);
  ck_assert_int_eq(s21_eq_matrix(NULL, &mat), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&mat, NULL), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_s21_eq_matrix_null_data) {
  matrix_t mat1, mat2;
  s21_create_matrix(2, 2, &mat1);
  mat2.matrix = NULL;
  ck_assert_int_eq(s21_eq_matrix(&mat1, &mat2), FAILURE);
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_s21_eq_matrix_different_sizes) {
  matrix_t mat1, mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(3, 2, &mat2);
  ck_assert_int_eq(s21_eq_matrix(&mat1, &mat2), FAILURE);
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_eq_matrix_different_elements) {
  matrix_t mat1, mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);

  mat1.matrix[0][0] = 1.0;
  mat2.matrix[0][0] = 2.0;

  ck_assert_int_eq(s21_eq_matrix(&mat1, &mat2), FAILURE);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_eq_matrix_equal_matrices) {
  matrix_t mat1, mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);

  mat1.matrix[0][0] = mat2.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = mat2.matrix[0][1] = 2.0;
  mat1.matrix[1][0] = mat2.matrix[1][0] = 3.0;
  mat1.matrix[1][1] = mat2.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&mat1, &mat2), SUCCESS);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_eq_matrix_ivalide_size_matrix) {
  matrix_t mat1, mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);

  mat1.columns = -1;

  ck_assert_int_eq(s21_eq_matrix(&mat1, &mat2), FAILURE);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_s21_eq_matrix_ivalide_poiner) {
  matrix_t mat1, mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);

  mat1.matrix = NULL;

  ck_assert_int_eq(s21_eq_matrix(&mat1, &mat2), FAILURE);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

Suite *s21_eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_eq_matrix\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_eq_matrix_null_pointers);
  tcase_add_test(tc_core, test_s21_eq_matrix_null_data);
  tcase_add_test(tc_core, test_s21_eq_matrix_different_sizes);
  tcase_add_test(tc_core, test_s21_eq_matrix_different_elements);
  tcase_add_test(tc_core, test_s21_eq_matrix_equal_matrices);
  tcase_add_test(tc_core, test_s21_eq_matrix_ivalide_size_matrix);
  tcase_add_test(tc_core, test_s21_eq_matrix_ivalide_poiner);
  suite_add_tcase(s, tc_core);

  return s;
}
