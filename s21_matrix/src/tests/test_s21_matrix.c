#include "test_s21_matrix.h"

// ANSI escape codes for colors
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"

// Функция для выполнения тестового набора и подсветки ошибок
static int run_test_suite(Suite *test_suite) {
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = srunner_create(test_suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  // Подсветка вывода количества неудачных тестов
  if (number_failed > 0)
    printf(RED_COLOR "Failed tests: %d\n" RESET_COLOR, number_failed);

  srunner_free(sr);

  return number_failed;
}

int main(void) {
  int number_failed = 0;
  Suite *suite_array[] = {s21_create_matrix_suite(),
                          s21_remove_matrix_suite(),
                          s21_eq_matrix_suite(),
                          s21_sum_matrix_suite(),
                          s21_sub_matrix_suite(),
                          s21_mult_number_suite(),
                          s21_mult_matrix_suite(),
                          s21_transpose_suite(),
                          s21_minor_suite(),
                          s21_determinant_suite(),
                          s21_calc_complements_suite(),
                          s21_inverse_matrix_suite(),
                          NULL};

  for (size_t i = 0; suite_array[i]; ++i) {
    number_failed += run_test_suite(suite_array[i]);
  }

  // Подсветка финального результата
  if (number_failed > 0)
    printf(RED_COLOR "\nTEST SUITE FAILED: %d\n" RESET_COLOR, number_failed);
  else
    printf(GREEN_COLOR "\nTEST SUITE PASSED SUCCESSFULLY\n" RESET_COLOR);

  return (number_failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
