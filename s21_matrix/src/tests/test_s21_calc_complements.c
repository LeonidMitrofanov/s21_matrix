#include "test_s21_matrix.h"

// Тест на корректность вычисления алгебраических дополнений для 3x3 матрицы
START_TEST(test_s21_calc_complements_valid_3x3) {
  matrix_t mat, result, expected;
  s21_create_matrix(3, 3, &mat);
  s21_create_matrix(3, 3, &expected);

  // Исходная матрица
  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[0][2] = 3.0;
  mat.matrix[1][0] = 0.0;
  mat.matrix[1][1] = 4.0;
  mat.matrix[1][2] = 2.0;
  mat.matrix[2][0] = 5.0;
  mat.matrix[2][1] = 2.0;
  mat.matrix[2][2] = 1.0;

  // Ожидаемый результат
  expected.matrix[0][0] = 0.0;
  expected.matrix[0][1] = 10.0;
  expected.matrix[0][2] = -20.0;
  expected.matrix[1][0] = 4.0;
  expected.matrix[1][1] = -14.0;
  expected.matrix[1][2] = 8.0;
  expected.matrix[2][0] = -8.0;
  expected.matrix[2][1] = -2.0;
  expected.matrix[2][2] = 4.0;

  ck_assert_int_eq(s21_calc_complements(&mat, &result), S21_OK);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на некорректные матрицы (NULL указатели)
START_TEST(test_s21_calc_complements_null_pointer) {
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(NULL, &result), S21_ERROR);
  ck_assert_int_eq(s21_calc_complements(&result, NULL), S21_ERROR);
}
END_TEST

// Тест на некорректную (не квадратную) матрицу
START_TEST(test_s21_calc_complements_non_square) {
  matrix_t mat, result;
  s21_create_matrix(2, 3, &mat);

  ck_assert_int_eq(s21_calc_complements(&mat, &result), S21_CALC_ERROR);

  s21_remove_matrix(&mat);
}
END_TEST

// Тест на вычисление алгебраических дополнений для 2x2 матрицы
START_TEST(test_s21_calc_complements_valid_2x2) {
  matrix_t mat, result, expected;
  s21_create_matrix(2, 2, &mat);
  s21_create_matrix(2, 2, &expected);

  // Исходная матрица
  mat.matrix[0][0] = 1.0;
  mat.matrix[0][1] = 2.0;
  mat.matrix[1][0] = 3.0;
  mat.matrix[1][1] = 4.0;

  // Ожидаемый результат
  expected.matrix[0][0] = 4.0;
  expected.matrix[0][1] = -3.0;
  expected.matrix[1][0] = -2.0;
  expected.matrix[1][1] = 1.0;

  ck_assert_int_eq(s21_calc_complements(&mat, &result), S21_OK);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// Тест на пустую матрицу (размеры матрицы не положительные)
START_TEST(test_s21_calc_complements_invalid_matrix) {
  matrix_t mat, result;
  mat.rows = 0;
  mat.columns = 0;
  mat.matrix = NULL;

  ck_assert_int_eq(s21_calc_complements(&mat, &result), S21_ERROR);
}
END_TEST

Suite *s21_calc_complements_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_calc_complements\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_calc_complements_valid_3x3);
  tcase_add_test(tc_core, test_s21_calc_complements_valid_2x2);
  tcase_add_test(tc_core, test_s21_calc_complements_null_pointer);
  tcase_add_test(tc_core, test_s21_calc_complements_non_square);
  tcase_add_test(tc_core, test_s21_calc_complements_invalid_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}