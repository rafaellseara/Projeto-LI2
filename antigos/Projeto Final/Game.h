#ifndef GAME_H
#define GAME_H


#include "Structs.h"
#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"

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