#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // Для usleep()
#include <time.h>
#include <math.h>

typedef int** SudokuGrid;

// Прототипы функций
SudokuGrid createGrid(int size);
void freeGrid(SudokuGrid grid, int size);
void printGrid(SudokuGrid grid, int size);
bool isSafe(SudokuGrid grid, int row, int col, int num, int size);
bool fillSudoku(SudokuGrid grid, int size);
bool solveSudoku(SudokuGrid grid, int size);
void userInput(SudokuGrid grid, int size);
void generateSudoku(SudokuGrid grid, int size);

// Функция для создания пустого поля заданного размера
SudokuGrid createGrid(int size) {
    SudokuGrid grid = (SudokuGrid)malloc(size * sizeof(int*)); 
    for (int i = 0; i < size; i++) {
        grid[i] = (int*)malloc(size * sizeof(int)); 
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0; // Инициализируем все ячейки нулями
        }
    }
    return grid;
}

// Функция для освобождения памяти, выделенной под поле
void freeGrid(SudokuGrid grid, int size) {
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

// Функция для вывода поля на экран
void printGrid(SudokuGrid grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == 0) {
                printf(" . ");
            } else {
                printf(" %d ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Функция для проверки, безопасно ли вставить число в ячейку
bool isSafe(SudokuGrid grid, int row, int col, int num, int size) {
    int boxSize = (int)sqrt(size);

    for (int x = 0; x < size; x++) { // Проверка строки и колонки
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Проверка подмассива
    for (int r = row - row % boxSize; r < row - row % boxSize + boxSize; r++) {
        for (int d = col - col % boxSize; d < col - col % boxSize + boxSize; d++) {
            if (grid[r][d] == num) {
                return false;
            }
        }
    }

    return true;
}

// Генерация случайного Судоку
bool fillSudoku(SudokuGrid grid, int size) {
    int row, col;

    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (grid[row][col] == 0) { // Если ячейка пустая
                for (int num = 1; num <= size; num++) { // Числа от 1 до size
                    int randomNum = rand() % size + 1; // Генерация случайного числа
                    if (isSafe(grid, row, col, randomNum, size)) {
                        grid[row][col] = randomNum; // Присваиваем число
                        if (fillSudoku(grid, size)) { // Рекурсивный вызов
                            return true;
                        }
                        grid[row][col] = 0; // Откат
                    }
                }
                return false; // Не удалось заполнить
            }
        }
    }
    return true; // успешно заполнено
}

// Функция для генерации Судоку с пустыми ячейками
void generateSudoku(SudokuGrid grid, int size) {
    fillSudoku(grid, size);
    
    // Удаляем случайные значения для создания пустых ячеек
    int cellsToRemove = size; 
    while (cellsToRemove > 0) {
        int row = rand() % size;
        int col = rand() % size;
        if (grid[row][col] != 0) {
            grid[row][col] = 0; // Очищаем ячейку
            cellsToRemove--;
        }
    }
}

// Рекурсивная функция для автоматического решения Судоку
bool solveSudoku(SudokuGrid grid, int size) {
    int row, col;

    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (grid[row][col] == 0) { // Если ячейка пустая
                for (int num = 1; num <= size; num++) {
                    if (isSafe(grid, row, col, num, size)) {
                        grid[row][col] = num; // Присваиваем число
                        printf("Текущая судока:\n");
                        printGrid(grid, size); // Показываем текущую доску
                        usleep(500000); // Пауза 0.5 секунды
                        
                        if (solveSudoku(grid, size)) {
                            return true;
                        }
                        grid[row][col] = 0; // Откат
                    }
                }
                return false; // Не удалось найти подходящее число
            }
        }
    }
    return true; // Все ячейки заполнены
}

// Функция для ввода пользовательского ввода
void userInput(SudokuGrid grid, int size) {
    printf("Введите ваши числа в формате (строка колонка число), 0 для выхода:\n");
    int row, col, num;
    while (true) {
        printf("Введите (строка, колонка, число): ");
        scanf("%d %d %d", &row, &col, &num);
        if (row == 0 && col == 0 && num == 0) break; // Выход
        if (row >= 1 && row <= size && col >= 1 && col <= size && num >= 1 && num <= size) {
            grid[row - 1][col - 1] = num; // Устанавливаем значение
            printf("Доска после вашего ввода:\n");
            printGrid(grid, size); // Показываем текущую доску
        } else {
            printf("Некорректный ввод.\n");
        }
    }
}

// Основная функция
int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    int size;

    // Запрос размера поля у пользователя
    do {
        printf("Введите размер поля Судоку (4 или 9): ");
        scanf("%d", &size);
    } while (size != 4 && size != 9); // Проверка на корректный ввод

    // Создаем пустое поле Судоку
    SudokuGrid grid = createGrid(size);

    // Генерация первоначального состояния поля
    generateSudoku(grid, size);
    printf("Сгенерированное поле Судоку:\n");
    printGrid(grid, size);

    int choice;
    printf("Выберите действие:\n1. Решить Судоку самостоятельно\n2. Автоматическое решение:\nВаш выбор: ");
    scanf("%d", &choice);

    if (choice == 1) {
        userInput(grid, size);
    } else if (choice == 2) {
        printf("Автоматическое решение:\n");
        if (solveSudoku(grid, size)) {
            printf("Решение найдено!\n");
            printGrid(grid, size);
        } else {
            printf("Решение не существует.\n");
        }
    } else {
        printf("Некорректный выбор.\n");
    }

    // Освобождение памяти
    freeGrid(grid, size);
    return 0;
}