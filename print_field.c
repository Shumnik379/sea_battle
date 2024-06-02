#include <stdio.h>
#include <string.h>
#include "functions.h"

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

void init_placement_enemy_ships(char(*enemy_ships)[16])               // Создание поля для вражеского флота
{
    strncpy(enemy_ships[0], "    0123456789 ", 15);
    strncpy(enemy_ships[1], "   ############", 15);
    strncpy(enemy_ships[2], "a  #          #", 15);
    strncpy(enemy_ships[3], "b  #          #", 15);
    strncpy(enemy_ships[4], "c  #          #", 15);
    strncpy(enemy_ships[5], "d  #          #", 15);
    strncpy(enemy_ships[6], "e  #          #", 15);
    strncpy(enemy_ships[7], "f  #          #", 15);
    strncpy(enemy_ships[8], "g  #          #", 15);
    strncpy(enemy_ships[9], "h  #          #", 15);
    strncpy(enemy_ships[10], "i  #          #", 15);
    strncpy(enemy_ships[11], "j  #          #", 15);
    strncpy(enemy_ships[12], "   ############", 15);
    strncpy(enemy_ships[13], "      ENEMY    ", 15);
}

void clrscr(void)
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

void print_action(char(*playing_field)[50], ACT act)               // Сигнализация режима
{
    char action_11[] = "placement ";
    char action_12[] = "your ships";
    char action_21[] = "attack    ";
    char action_22[] = "the enemy ";
    char action_3[] = "   win    ";
    char action_4[] = "   loss   ";

    switch(act)
    {
        case act_placement:
            for (int i = 37; i < 47; i++) {
                playing_field[11][i] = action_11[i - 37];
                playing_field[12][i] = action_12[i - 37];
            }
            break;
        case act_fighting:
            for (int i = 37; i < 47; i++) {
                playing_field[11][i] = action_21[i - 37];
                playing_field[12][i] = action_22[i - 37];
                playing_field[13][i] = ' ';
            }
            break;
        case act_win:
            for (int i = 37; i < 47; i++) {
                playing_field[11][i] = ' ';
                playing_field[12][i] = action_3[i - 37];
                playing_field[13][i] = ' ';
            }
            break;
        case act_loss:
            for (int i = 37; i < 47; i++) {
                playing_field[11][i] = ' ';
                playing_field[12][i] = action_4[i - 37];
                playing_field[13][i] = ' ';
            }
            break;
    }
}

void print_type_ship(char(*playing_field)[50], MODEL_SHIP ship)               // Сигнализация типа корабля
{
    char ship_1[] = "x1";
    char ship_2[] = "x2";
    char ship_3[] = "x3";
    char ship_4[] = "x4";

    switch(ship)
    {
        case x1:
            for (int i = 41; i < 43; i++)
                playing_field[13][i] = ship_1[i - 41];
            break;
        case x2:
            for (int i = 41; i < 43; i++)
                playing_field[13][i] = ship_2[i - 41];
            break;
        case x3:
            for (int i = 41; i < 43; i++)
                playing_field[13][i] = ship_3[i - 41];
            break;
        case x4:
            for (int i = 41; i < 43; i++)
                playing_field[13][i] = ship_4[i - 41];
            break;
    }
}

void print_remainging_enemy_ships(char(*playing_field)[50], int* remaining_enemy_ship)
{
    char str[3];
    snprintf(str, sizeof(str), "%.2d", *remaining_enemy_ship);
    for (int i = 40; i < 42; i++)
        playing_field[8][i] = str[i - 40];
}

void print_remainging_my_ships(char(*playing_field)[50], int* remaining_my_ship)
{
    char str[3];
    snprintf(str, sizeof(str), "%.2d", *remaining_my_ship);
    for (int i = 40; i < 42; i++)
        playing_field[9][i] = str[i - 40];
}