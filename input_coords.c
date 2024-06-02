#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void input_coords(char* s)          // Вводи координат с проверкой
{
    int good = 1;
    while (good)
    {
        scanf("%s", s);     // a1
        for (int i = 0; i < 2; i++) {
            if (s[0] >= 97 && s[0] <= 106 && s[1] >= 48 && s[1] <= 57 || s[0] == 107)
                good = 0;
            else
                good = 1;
        }
    }
}

void shooting(char(*playing_field)[50], char(*enemy_ships)[16], char* s, int* remaining_enemy_ship)        // Отображение выстрела
{
    input_coords(s);
    char row = s[0] - 95;
    char col = s[1] - 44;
    if (enemy_ships[row][col] != 'X')
        playing_field[row][col] = '*';
    else {
        playing_field[row][col] = '@';
        (*remaining_enemy_ship)--;
    }
}

void enemy_shooting(char(*playing_field)[50], char(*enemy_ships)[16], char* s, int* remaining_my_ship)        // Отображение выстрела противника
{
    srand(time(NULL));
    int row = rand() % 10 + 2;
    int col = rand() % 10 + 21;
    if (playing_field[row][col] != 'X' && playing_field[row][col] != '@' && playing_field[row][col] != '*')
        playing_field[row][col] = '*';
    else if (playing_field[row][col] == 'X') {
        playing_field[row][col] = '@';
        (*remaining_my_ship)--;
    }
    else if (playing_field[row][col] == '@' || playing_field[row][col] == '*') {
        int next = 1;
        while (next) {
            if (playing_field[row][col] == '@' || playing_field[row][col] == '*') {
                row = rand() % 10 + 2;
                col = rand() % 10 + 21;
            }
            else if (playing_field[row][col] == 'X') {
                playing_field[row][col] = '@';
                (*remaining_my_ship)--;
                next = 0;
            }
            else {
                playing_field[row][col] = '*';
                next = 0;
            }
        }
    }
}