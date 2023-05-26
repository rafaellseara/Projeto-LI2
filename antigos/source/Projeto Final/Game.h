#ifndef GAME_H
#define GAME_H



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


void do_check_nightstick(Game game, Player player1);
/*
funçao que tem todas as propriedades do jogo
*/
void main_game_single_player(char c, int linhas, int colunas, Map mapa[][colunas], Game game, Player player1, Player player2, Mob *mobs, Flag flag, Bullet bullet_player1, Bullet bullet_player2, int mob_positionX, int mob_positionY);
void main_game_multi_player(char c, int linhas, int colunas, Map mapa[][colunas], Game game, Player player1, Player player2, Flag flag, Mob *mobs, Bullet bullet_player1, Bullet bullet_player2);
void main_game_challenge(char c, int linhas, int colunas, Map mapa[][colunas], Flag flag, Game game, Player player1, Player player2, Mob *mobs, Bullet bullet_player1, Bullet bullet_player2, int mob_positionX, int mob_positionY);
/*
funçao que inicia o jogo
*/
void start_game_single_player(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Player player1, Player player2, int mob_positionX, int mob_positionY);
void start_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Player player1, Player player2);
void start_game_challenge(int linhas, int colunas, Map mapa[][colunas], Player player1, Player player2);

#endif