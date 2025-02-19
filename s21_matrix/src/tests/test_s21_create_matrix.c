#include "test_s21_matrix.h"

// Тест успешного создания матрицы
START_TEST(test_create_matrix_success) {
  matrix_t mat;
  int result = s21_create_matrix(3, 4, &mat);
  ck_assert_int_eq(result, S21_OK);
  ck_assert_ptr_nonnull(mat.matrix);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 4);

  // Проверяем, что все элементы инициализированы
  for (int i = 0; i < mat.rows; i++) {
    for (int j = 0; j < mat.columns; j++) {
      ck_assert_double_eq(mat.matrix[i][j], 0.0);
    }
  }

  // Освобождаем память после теста
  s21_remove_matrix(&mat);
}
END_TEST

// Тест создания матрицы с отрицательным числом строк
START_TEST(test_create_matrix_negative_rows) {
  matrix_t mat;
  int result = s21_create_matrix(-1, 4, &mat);
  ck_assert_int_eq(result, S21_ERROR);
}
END_TEST

// Тест создания матрицы с отрицательным числом столбцов
START_TEST(test_create_matrix_negative_columns) {
  matrix_t mat;
  int result = s21_create_matrix(3, -4, &mat);
  ck_assert_int_eq(result, S21_ERROR);
}
END_TEST

// Тест создания матрицы с нулевым указателем на структуру
START_TEST(test_create_matrix_null_pointer) {
  int result = s21_create_matrix(3, 4, NULL);
  ck_assert_int_eq(result, S21_ERROR);
}
END_TEST

// Тест ошибки выделения памяти (большая матрица)
START_TEST(test_create_matrix_memory_allocation_failure) {
  matrix_t mat;
  int result = s21_create_matrix(1000000, 1000000, &mat);
  ck_assert_int_eq(result, S21_ERROR);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[45ms21_create_matrix\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_matrix_success);
  tcase_add_test(tc_core, test_create_matrix_negative_rows);
  tcase_add_test(tc_core, test_create_matrix_negative_columns);
  tcase_add_test(tc_core, test_create_matrix_null_pointer);
  tcase_add_test(tc_core, test_create_matrix_memory_allocation_failure);
  suite_add_tcase(s, tc_core);

  return s;
}
