#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef int** SudokuBoard;

typedef enum {
    SUDOKU_4x4 = 4,
    SUDOKU_9x9 = 9
} SudokuSize;

SudokuBoard createBoard(int size);
void freeBoard(SudokuBoard board, int size);
void printBoard(SudokuBoard board, int size);
bool isValid(SudokuBoard board, int size, int row, int col, int num);
bool solveSudoku(SudokuBoard board, int size);
void initSudoku(SudokuBoard board, int size);
int chooseSize();
bool generateSudoku(SudokuBoard board, int size);
void removeNumbers(SudokuBoard board, int size, int removeCount);
void interactiveSolve(SudokuBoard board, int size);

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int sizeChoice = chooseSize(); // Выбор размерности
    SudokuBoard board = createBoard(sizeChoice); // Создание доски

    // Генерация Судоку
    if (generateSudoku(board, sizeChoice)) {
        printf("Сгенерированное Судоку:\n");
        printBoard(board, sizeChoice);
    } else {
        printf("Не удалось сгенерировать Судоку.\n");
        freeBoard(board, sizeChoice);
        return 0;
    }

    // Удаление некоторых чисел для получения неполного Судоку
    int removeCount = sizeChoice == 4 ? 2 : 40; // Количество чисел для удаления (настраиваемое)
    removeNumbers(board, sizeChoice, removeCount);
    printf("Судоку после удаления чисел:\n");
    printBoard(board, sizeChoice);

    // Выбор режима решения
    int mode;
    printf("Выберите режим решения:\n1. Автоматическое решение\n2. Ручное решение\n");
    scanf("%d", &mode);

    if (mode == 1) {
        if (solveSudoku(board, sizeChoice)) {
            printf("Решение:\n");
            printBoard(board, sizeChoice);
        } else {
            printf("Решение невозможно.\n");
        }
    } else if (mode == 2) {
        interactiveSolve(board, sizeChoice);
    } else {
        printf("Некорректный выбор!\n");
    }

    freeBoard(board, sizeChoice); // Освобождение памяти
    return 0;
}

SudokuBoard createBoard(int size) {
    SudokuBoard board = (SudokuBoard)malloc(size * sizeof(int*)); // Выделение памяти для строк
    for (int i = 0; i < size; i++) {
        board[i] = (int*)malloc(size * sizeof(int)); // Выделение памяти для каждого ряда
    }
    return board;
}

void freeBoard(SudokuBoard board, int size) {
    for (int i = 0; i < size; i++) {
        free(board[i]); // Освобождение памяти для каждой строки
    }
    free(board); // Освобождение памяти для массива строк
}

void printBoard(SudokuBoard board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                printf(". "); // Печатаем точку для пустых ячеек
            } else {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

bool isValid(SudokuBoard board, int size, int row, int col, int num) {
    for (int x = 0; x < size; x++) {
        if (board[row][x] == num || board[x][col] == num) {
            return false; // Проверка на дублирование в строках и столбцах
        }
    }
    int boxSize = (int)sqrt(size);
    int boxRowStart = row - row % boxSize;
    int boxColStart = col - col % boxSize;
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (board[i + boxRowStart][j + boxColStart] == num) {
                return false; // Проверка на дублирование в квадрате
            }
        }
    }
    return true;
}

bool solveSudoku(SudokuBoard board, int size) {
    int row, col;
    bool foundEmpty = false;

    // Найти пустую ячейку
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (board[row][col] == 0) { // Ячейка пустая
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) break;
    }

    if (!foundEmpty) {
        return true; // Если нет пустой ячейки, Судоку решено
    }

    for (int num = 1; num <= size; num++) { // Проверка от 1 до размера
        if (isValid(board, size, row, col, num)) {
            board[row][col] = num; // Назначаем число
            if (solveSudoku(board, size)) {
                return true; // Рекурсивное решение
            }
            board[row][col] = 0; // Возврат к пустому значению (откат)
        }
    }
    return false; // Нет решения
}

void initSudoku(SudokuBoard board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0; // Заполнение пустым значением
        }
    }
}

int chooseSize() {
    int choice;
    do {
        printf("Выберите размерность Судоку (4 или 9): ");
        scanf("%d", &choice);
    } while (choice != 4 && choice != 9);
    return choice;
}

bool generateSudoku(SudokuBoard board, int size) {
    initSudoku(board, size);

    for (int num = 1; num <= size; num++) {
        int placed = 0;
        while (placed < size) {
            int row = rand() % size;
            int col = rand() % size;
            if (isValid(board, size, row, col, num)) {
                board[row][col] = num;
                placed++;
            }
        }
    }
    return true; // Возвращаем true, если Судоку заполнено
}

void removeNumbers(SudokuBoard board, int size, int removeCount) {
    int count = 0;
    while (count < removeCount) {
        int row = rand() % size;
        int col = rand() % size;
        if (board[row][col] != 0) {
            board[row][col] = 0; // Удаление числа
            count++;
        }
    }
}

void interactiveSolve(SudokuBoard board, int size) {
    int row, col, num;
    while (true) {
        printf("Введите координаты ячейки (строка, столбец) и число (0 для выхода): ");
        scanf("%d %d %d", &row, &col, &num);

        if (num == 0) {
            printf("Выход из программы.\n");
            break;
        }
        
        if (row < 0 || row >= size || col < 0 || col >= size || num < 1 || num > size) {
            printf("Некорректный ввод, попробуйте снова.\n");
            continue;
        }

        if (isValid(board, size, row, col, num)) {
            board[row][col] = num; // Ввод пользователя
            printBoard(board, size); // Печать текущего состояния
            if (solveSudoku(board, size)) {
                printf("Судоку успешно решено!\n");
            }
        } else {
            printf("Это число нельзя вставить в ячейку [%d][%d].\n", row, col);
        }
    }
}