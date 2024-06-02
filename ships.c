#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*ПРИМЕЧАНИЯ

check_around - проверяет все соседние клетки вокруг заданной точки
vertical_placement - приращивает корабль в вертикальном направлении
horizontal_placement - приращивает корабль в горизонтальном направлении
placement_ships - размещает корабли на игровом поле

playing_field - игровое поле (с кораблями противника)
n - счётчик создания нужного количества палуб корабля
ships - количество палуб у корабля
k - коэффициет равный -1 или 1, задаёт направление, в котором будет удлиняться корабль (вправо от исходной точки или влево)
*/


// ENEMY

int e_check_around(char(*enemy_ships)[16], int row, int col)
{
    int res = 0;
    if (row - 1 >= 1 && row + 1 <= 12 && col - 1 >= 3 && col + 1 <= 14)
    {
        res = 1;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (enemy_ships[row - i][col - j] == 'X')
                    res *= 0;
            }
        }
    }
    
    return res;
}

void e_vertical_placement(char(*enemy_ships)[16], int* row, int* col, int n, int ships)
{
    while (enemy_ships[*row][*col] != 'X')
    {
        if (e_check_around(enemy_ships, *row, *col))
        {
            *row -= 1;        
            if (n < ships)
            {
                if (*row >= 2 && *row <= 11 && e_check_around(enemy_ships, *row, *col))
                {
                    n++;
                    e_vertical_placement(enemy_ships, row, col, n, ships);
                }
                else
                {
                    do {
                        *row = rand() % 10 + 2;
                        *col = rand() % 10 + 4;
                    } while (enemy_ships[*row][*col] == 'X');
                    n = 1;
                }
            }
            else if (n == ships)
            {
                *row = *row + ships;
                for (n = 0; n < ships; n++)
                {
                    enemy_ships[*row - n][*col] = 'X';                    
                }
                return;
            }
        }
        else
        {
            do {
                *row = rand() % 10 + 2;
                *col = rand() % 10 + 4;
            } while (enemy_ships[*row][*col] == 'X');
            n = 1;
        }
    }
}

void e_horizontal_placement(char(*enemy_ships)[16], int* row, int* col, int n, int ships)
{
    while (enemy_ships[*row][*col] != 'X')
    {
        if (e_check_around(enemy_ships, *row, *col))
        {
            *col -= 1;
            if (n < ships)
            {
                if (*col >= 4 && *col <= 13 && e_check_around(enemy_ships, *row, *col))
                {
                    n++;
                    e_horizontal_placement(enemy_ships, row, col, n, ships);
                }
                else
                {
                    do {
                        *row = rand() % 10 + 2;
                        *col = rand() % 10 + 4;
                    } while (enemy_ships[*row][*col] == 'X');
                    n = 1;
                }
            }
            else if (n == ships)
            {
                *col = *col + ships;
                for (n = 0; n < ships; n++)
                {
                    enemy_ships[*row][*col - n] = 'X';                    
                }
                return;
            }
        }
        else
        {
            do {
                *row = rand() % 10 + 2;
                *col = rand() % 10 + 4;
            } while (enemy_ships[*row][*col] == 'X');
            n = 1;
        }
    }
}

void e_placement_ships(char(*enemy_ships)[16], int ships)
{
    int row, col;
    do {
        row = rand() % 10 + 2;
        col = rand() % 10 + 4;
    } while (!e_check_around(enemy_ships, row, col));
    
    int choice = rand() % 2 + 1;
    int n = 1;
    switch(choice) {
        case 1: e_vertical_placement(enemy_ships, &row, &col, n, ships);
            break;
        case 2: e_horizontal_placement(enemy_ships, &row, &col, n, ships);
            break;
        default: printf("Oops!\n");
            break;
    }    
}

// YOU

int check_around(char(*playing_field)[50], int row, int col)
{
    int res = 0;
    if (row - 1 >= 1 && row + 1 <= 12 && col - 1 >= 20 && col + 1 <= 31)
    {                                                                          // -1:-1  -1:0  -1:1
        res = 1;                                               // [row:col] -> //  0:-1   0:0   0:1
        for (int i = -1; i < 2; i++)                                           //  1:-1   1:0   1:1
        {
            for (int j = -1; j < 2; j++)
            {
                if (playing_field[row - i][col - j] == 'X')
                    res *= 0;
            }
        }
    }
    
    return res;
}

void vertical_placement(char(*playing_field)[50], int* row, int* col, int n, int ships)
{
    while (playing_field[*row][*col] != 'X')                                    // 0  0  0
    {                                                          // row - 3 ->    // 0 -3  0
        if (check_around(playing_field, *row, *col))           // row - 2 ->    // 0 -2  0
        {                                                      // row - 1 ->    // 0 -1  0
            *row -= 1;                                         // row     ->    // 0  X  0
            if (n < ships)
            {
                if (*row >= 2 && check_around(playing_field, *row, *col))
                {
                    n++;
                    vertical_placement(playing_field, row, col, n, ships);
                }
                else
                {
                    do {
                        *row = rand() % 10 + 2;
                        *col = rand() % 10 + 21;
                    } while (playing_field[*row][*col] == 'X');
                    n = 1;
                }
            }
            else if (n == ships)
            {
                *row = *row + ships;
                for (n = 0; n < ships; n++)
                {
                    playing_field[*row - n][*col] = 'X';                    
                }
                return;
            }
        }
        else
        {
            do {
                *row = rand() % 10 + 2;
                *col = rand() % 10 + 21;
            } while (playing_field[*row][*col] == 'X');
            n = 1;
        }
    }
}

void horizontal_placement(char(*playing_field)[50], int* row, int* col, int n, int ships)
{
    while (playing_field[*row][*col] != 'X')
    {
        if (check_around(playing_field, *row, *col))
        {
            *col -= 1;
            if (n < ships)
            {
                if (*col >= 21 && check_around(playing_field, *row, *col))
                {
                    n++;
                    horizontal_placement(playing_field, row, col, n, ships);
                }
                else
                {
                    do {
                        *row = rand() % 10 + 2;
                        *col = rand() % 10 + 21;
                    } while (playing_field[*row][*col] == 'X');
                    n = 1;
                }
            }
            else if (n == ships)
            {
                *col = *col + ships;
                for (n = 0; n < ships; n++)
                {
                    playing_field[*row][*col - n] = 'X';                    
                }
                return;
            }
        }
        else
        {
            do {
                *row = rand() % 10 + 2;
                *col = rand() % 10 + 21;
            } while (playing_field[*row][*col] == 'X');
            n = 1;
        }
    }
}

void placement_ships(char(*playing_field)[50], int ships)
{
    int row, col;
    do {
        row = rand() % 10 + 2;
        col = rand() % 10 + 21;
    } while (!check_around(playing_field, row, col));
    
    int choice = rand() % 2 + 1;
    int n = 1;
    switch(choice) {
        case 1: vertical_placement(playing_field, &row, &col, n, ships);
            break;
        case 2: horizontal_placement(playing_field, &row, &col, n, ships);
            break;
        default: printf("Oops!\n");
            break;
    }    
}