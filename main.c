#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

char playing_field[14][50];
char enemy_ships[14][16];
char s[3];                                      // a1
int remaining_enemy_ship = 20;
int remaining_my_ship = 20;

int main(void)
{
    init_field(playing_field);
    srand(time(NULL));

    placement_ships(playing_field, 4);          // Расстановка кораблей игрока
    for (int i = 0; i < 2; i++)
        placement_ships(playing_field, 3);
    for (int i = 0; i < 3; i++)
        placement_ships(playing_field, 2);
    for (int i = 0; i < 4; i++)
        placement_ships(playing_field, 1);

    e_placement_ships(enemy_ships, 4);          // Расстановка кораблей противника
    for (int i = 0; i < 2; i++)
        e_placement_ships(enemy_ships, 3);
    for (int i = 0; i < 3; i++)
        e_placement_ships(enemy_ships, 2);
    for (int i = 0; i < 4; i++)
        e_placement_ships(enemy_ships, 1);

    do
    {
        print_action(playing_field, act_fighting);
        print_remainging_enemy_ships(playing_field, &remaining_enemy_ship);
        print_remainging_my_ships(playing_field, &remaining_my_ship);
        print_field(playing_field);
        shooting(playing_field, enemy_ships, s, &remaining_enemy_ship);
        enemy_shooting(playing_field, enemy_ships, s, &remaining_my_ship);
        if (remaining_enemy_ship == 0 || remaining_my_ship == 0) {
            break;
        }
    } while(s[0] != 'k');
    
    if (remaining_enemy_ship == 0)
        print_action(playing_field, act_win);
    else
        print_action(playing_field, act_loss);
    print_remainging_enemy_ships(playing_field, &remaining_enemy_ship);
    print_remainging_my_ships(playing_field, &remaining_my_ship);
    print_field(playing_field);

    return 0;
}