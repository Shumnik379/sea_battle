#ifndef FUNCTIONS_H_INCLUDE
#define FUNCTIONS_H_INCLUDE
#endif

typedef enum {act_placement = 1, act_fighting = 2, act_win = 3, act_loss = 4} ACT;
typedef enum {x1 = 1, x2 = 2, x3 = 3, x4 = 4} MODEL_SHIP;

void init_field(char(*playing_field)[50]);
void init_placement_enemy_ships(char(*enemy_ships)[16]);
void clrscr(void);
void print_field(char(*playing_field)[50]);
void print_action(char(*playing_field)[50], ACT act);
void print_type_ship(char(*playing_field)[50], MODEL_SHIP ship);
void print_remainging_enemy_ships(char(*playing_field)[50], int* remaining_enemy_ship);
void print_remainging_my_ships(char(*playing_field)[50], int* remaining_my_ship);

int e_check_around(char(*enemy_ships)[16], int row, int col);
void e_vertical_placement(char(*enemy_ships)[16], int* row, int* col, int n, int ships);
void e_horizontal_placement(char(*enemy_ships)[16], int* row, int* col, int n, int ships);
void e_placement_ships(char(*enemy_ships)[16], int ships);

int check_around(char(*playing_field)[50], int row, int col);
void vertical_placement(char(*playing_field)[50], int* row, int* col, int n, int ships);
void horizontal_placement(char(*playing_field)[50], int* row, int* col, int n, int ships);
void placement_ships(char(*playing_field)[50], int ships);

void input_coords(char* s);
void shooting(char(*playing_field)[50], char(*enemy_ships)[16], char* s, int* remaining_enemy_ship);
void enemy_shooting(char(*playing_field)[50], char(*enemy_ships)[16], char* s, int* remaining_my_ship);