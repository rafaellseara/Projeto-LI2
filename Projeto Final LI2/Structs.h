#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct bullet
{
    int appearing; // Se está visível ou não
    int positionX;
    int positionY;
    int number;
    int direction;
} Bullet;

typedef struct game
{
    int game_over;
    char key_pressed;
    char is_flag_placed;
    int nightstick_time_of_usage;
    int maximum_nightstick_time;
} Game;

typedef struct scoreboard
{
    int counter;
    char nome[500][30];
    int score[500];
} Scoreboard;

typedef struct flag
{
    int positionX;
    int positionY;
    int temporary_positionX;
    int temporary_positionY;
} Flag;

typedef struct map
{
    char visible_piece;
} Map;

typedef struct player
{
    int id;   // number of player eg 1/2/3
    int gun;  // gun using at the moment eg 1- pistol; 2- sword, etc
    int ammo; // ammunition he has
    int positionX;
    int positionY;
    int hp;               // hit points, starts at 100 maybe, goes down to 0 to lose
    int trapNumber;       // number of bombs he has to use
    int nightstickNumber; // number of nightsticks
    int usingNightStick;
    int score;
    char character;
    char last_direction_moved;
} Player;

typedef struct mob
{
    int id;      // need to identify each mob to make sure who dies
    int showing; // if it's showing or not
    int positionX;
    int positionY;
    int mobType; // 1 for stupid, 2 for coward, 3 for smart, etc
    int hp;      // hit points, maybe start 200-500 and lower it from there
    int baseHp;
    int is_in_mob_view;
    int damaging_player;
    int quadrado_down;
    int quadrado_right;
    int quadrado_up;
    int quadrado_left;
} Mob;





#endif