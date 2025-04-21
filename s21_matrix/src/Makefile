# Компилятор и флаги
CC := gcc
CFLAGS := -std=c11 #-Wall -Werror -Wextra
CHECK_FLAGS := -lcheck -lm
GCOV_FLAGS := --coverage
FORMAT_PATH := ../materials/linters/.clang-format

# Директории
SRC_DIR := .
FUNC_DIR := $(SRC_DIR)/functions
OBJ_DIR := $(SRC_DIR)/objects
TEST_DIR := $(SRC_DIR)/tests
COV_REPORT_DIR := $(SRC_DIR)/coverage_report

# Имя статической библиотеки
LIB_NAME := s21_matrix.a

SRC_FILES := $(wildcard $(FUNC_DIR)/*.c)
OBJ_FILES := $(patsubst $(FUNC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(FUNC_DIR)/*.c))

TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_EXEC := test_suite

# Файлы для форматирования
TO_FORMAT_FILES := $(SRC_FILES) $(TEST_FILES)  $(wildcard $(SRC_DIR)/*.h) $(wildcard $(TEST_DIR)/*.h)

# Компиляция библиотеки
$(LIB_NAME): $(OBJ_FILES)
	@ar rcs $@ $^

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(FUNC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция тестов
$(TEST_EXEC): $(LIB_NAME) $(TEST_FILES)
	@$(CC) $(CFLAGS) $(TEST_FILES) $(LIB_NAME) $(CHECK_FLAGS) -o $(TEST_EXEC)

# Запуск тестов
test: $(TEST_EXEC)
	@./$(TEST_EXEC)

# Генерация отчета покрытия кода в HTML-формате
gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: clean $(LIB_NAME) test
	@mkdir -p $(COV_REPORT_DIR)
	@gcov -b -c $(OBJ_FILES)
	@lcov --capture --directory . --output-file $(COV_REPORT_DIR)/coverage.info
	@genhtml $(COV_REPORT_DIR)/coverage.info --output-directory $(COV_REPORT_DIR)
	@rm -f *.gcda *.gcno *.gcov
	@echo "Отчет покрытия кода сгенерирован в директории $(COV_REPORT_DIR)"
	open $(COV_REPORT_DIR)/index.html

# Очистка артефактов сборки
clean:
	@rm -rf $(OBJ_DIR) $(LIB_NAME) $(TEST_EXEC) coverage_report *.gcda *.gcno *.gcov

# Очистка тестов
clean_tests:
	@rm -f $(TEST_EXEC)

# Сборка всего
all: clean $(LIB_NAME)

# Форматирование кода
format: check-style
	@echo "Форматирование исходного кода с помощью clang-format..."
	@clang-format -i -style=file:$(FORMAT_PATH) $(TO_FORMAT_FILES)

# Проверка стиля кода
check-style:
	@echo "Проверка стиля кода с помощью clang-format..."
	@clang-format -n -style=file:$(FORMAT_PATH) $(TO_FORMAT_FILES)

# Указание целей, которые не являются файлами
.PHONY: all clean clean_tests test gcov_report format check-style
