#include <stdio.h>
#include <string.h>     // strncpy()
#include <stdlib.h>     // srand(), rand()
#include <time.h>       // time()

// Создание и вывод в консоль игрового поля

void init_field(char(*playing_field)[50])               // Создание игрового поля
{
    strncpy(playing_field[0], "    0123456789       0123456789                  ", 49);
    strncpy(playing_field[1], "   ############     ############     enemy ships:", 49);
    strncpy(playing_field[2], "a  #          #  a  #          #        XXXX - 1 ", 49);
    strncpy(playing_field[3], "b  #          #  b  #          #         XXX - 2 ", 49);
    strncpy(playing_field[4], "c  #          #  c  #          #          XX - 3 ", 49);
    strncpy(playing_field[5], "d  #          #  d  #          #           X - 4 ", 49);
    strncpy(playing_field[6], "e  #          #  e  #          #                 ", 49);
    strncpy(playing_field[7], "f  #          #  f  #          #     remaining:  ", 49);
    strncpy(playing_field[8], "g  #          #  g  #          #     -:    ships ", 49);
    strncpy(playing_field[9], "h  #          #  h  #          #     +:    ships ", 49);
    strncpy(playing_field[10], "i  #          #  i  #          #                 ", 49);
    strncpy(playing_field[11], "j  #          #  j  #          #                 ", 49);
    strncpy(playing_field[12], "   ############     ############                 ", 49);
    strncpy(playing_field[13], "      ENEMY             YOU                      ", 49);

    for (int i = 0; i < 14; i++)
        playing_field[i][49] = '\0';
}

void clrscr(void)                                       // Очистка экрана
{
    printf("\033[2J");      // очищает (сдвигает) полностью экран
    printf("\033[0;0f");    // перемещает курсор в верхний левый угол
}

void print_field(char(*playing_field)[50])              // Отрисовка игрового поля в консоли
{
    clrscr();
    for (int i = 0; i < 14; i++)
        puts(playing_field[i]);
}

// Расстановка кораблей противника (ENEMY)

int e_check_around(char(*playing_field)[50], int row, int col)  // Проверка всех соседних клеток вокруг заданной
{
    int res = 0;
    if (row - 1 >= 1 && row + 1 <= 12 && col - 1 >= 3 && col + 1 <= 14)
    {
        res = 1;
        for (int i = -1; i < 2; i++)
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

void e_vertical_placement(char(*playing_field)[50], int* row, int* col, int n, int ships)   // Создание кораблей в вертикальном направлении
{
    while (playing_field[*row][*col] != 'X')
    {
        if (e_check_around(playing_field, *row, *col))
        {
            *row -= 1;        
            if (n < ships)
            {
                if (*row >= 2 && *row <= 11 && e_check_around(playing_field, *row, *col))
                {
                    n++;
                    e_vertical_placement(playing_field, row, col, n, ships);
                }
                else
                {
                    do {
                        *row = rand() % 10 + 2;
                        *col = rand() % 10 + 4;
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
                *col = rand() % 10 + 4;
            } while (playing_field[*row][*col] == 'X');
            n = 1;
        }
    }
}

void e_horizontal_placement(char(*playing_field)[50], int* row, int* col, int n, int ships)   // Создание кораблей в горизонтальном направлении
{
    while (playing_field[*row][*col] != 'X')
    {
        if (e_check_around(playing_field, *row, *col))
        {
            *col -= 1;
            if (n < ships)
            {
                if (*col >= 4 && *col <= 13 && e_check_around(playing_field, *row, *col))
                {
                    n++;
                    e_horizontal_placement(playing_field, row, col, n, ships);
                }
                else
                {
                    do {
                        *row = rand() % 10 + 2;
                        *col = rand() % 10 + 4;
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
                *col = rand() % 10 + 4;
            } while (playing_field[*row][*col] == 'X');
            n = 1;
        }
    }
}

void e_placement_ships(char(*playing_field)[50], int ships)     // Размещение кораблей на поле противника
{
    int row, col;
    do {
        row = rand() % 10 + 2;
        col = rand() % 10 + 4;
    } while (!e_check_around(playing_field, row, col));
    
    int choice = rand() % 2 + 1;
    int n = 1;
    switch(choice) {
        case 1: e_vertical_placement(playing_field, &row, &col, n, ships);
            break;
        case 2: e_horizontal_placement(playing_field, &row, &col, n, ships);
            break;
        default: printf("Oops!\n");
            break;
    }    
}

// Расстановка кораблей игрока (YOU)

int check_around(char(*playing_field)[50], int row, int col)  // Проверка всех соседних клеток вокруг заданной
{
    int res = 0;
    if (row - 1 >= 1 && row + 1 <= 12 && col - 1 >= 20 && col + 1 <= 31)
    {
        res = 1;
        for (int i = -1; i < 2; i++)
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

void vertical_placement(char(*playing_field)[50], int* row, int* col, int n, int ships)   // Создание кораблей в вертикальном направлении
{
    while (playing_field[*row][*col] != 'X')
    {
        if (check_around(playing_field, *row, *col))
        {
            *row -= 1;        
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

void horizontal_placement(char(*playing_field)[50], int* row, int* col, int n, int ships)   // Создание кораблей в горизонтальном направлении
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

void placement_ships(char(*playing_field)[50], int ships)     // Размещение кораблей на поле игрока
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



int main(void)
{
    char playing_field[14][50];
    init_field(playing_field);
    srand(time(NULL));

    placement_ships(playing_field, 4);              // Расстановка кораблей игрока
    for (int i = 0; i < 2; i++)
        placement_ships(playing_field, 3);
    for (int i = 0; i < 3; i++)
        placement_ships(playing_field, 2);
    for (int i = 0; i < 4; i++)
        placement_ships(playing_field, 1);

    e_placement_ships(playing_field, 4);            // Расстановка кораблей противника
    for (int i = 0; i < 2; i++)
        e_placement_ships(playing_field, 3);
    for (int i = 0; i < 3; i++)
        e_placement_ships(playing_field, 2);
    for (int i = 0; i < 4; i++)
        e_placement_ships(playing_field, 1);

    print_field(playing_field);                     // Вывод игрового поля в консоль

    return 0;
}