# Судоку

Это лабораторная работа №1 для игры в Судоку на языке C. 
Программа позволяет пользователю решать Судоку самостоятельно или автоматически с помощью алгоритма брутфорса. 
Генерация Судоку осуществляется с пустыми ячейками, чтоб пользователь мог их заполнить.

## Описание

- **Генерация Судоку**: Создается поле с пустыми ячейками, оставляя пользователю возможность вводить свои значения.
- **Решение**: Пользователь может решить Судоку самостоятельно или позволить программе решить его автоматически, с выводом текущего состояния доски на каждом шаге.
- **Интерфейс**: Работает в терминале, прост в использовании. Пользователи могут вводить свои числа в формате (строка, колонка, число).

## Установка

1. Убедитесь, что у вас установлен компилятор C (например, GCC).
2. Скопируйте репозиторий:
```
bash
git clone https://github.com/ваше_имя_пользователя/Sudoku-.git

cd Sudoku-
```
3. Скомпилируйте код:
```
bash
gcc -o sudoku sudoku.c -lm
```
## Использование

Запустите программу:
```
bash
./sudoku
```
## Функции

- `createGrid(size)`: Создает пустую сетку Судоку заданного размера.
- `printGrid(grid, size)`: Выводит текущее состояние сетки на экран.
- `isSafe(grid, row, col, num, size)`: Проверяет, безопасно ли вставить число в ячейку.
- `fillSudoku(grid, size)`: Заполняет Судоку случайными числами.
- `solveSudoku(grid, size)`: Решает Судоку, выводя текущее состояние доски на каждом шаге.
- `userInput(grid, size)`: Позволяет пользователю вводить значения в пустые ячейки.
