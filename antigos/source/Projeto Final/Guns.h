#ifndef GUNS_H
#define GUNS_H

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Mobs.h"



typedef struct bullet
{
    int appearing; // Se está visível ou não
    int positionX;
    int positionY;
    int number;
    int direction;
} Bullet;



void shot_fired(int direction, int player, Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2);
/*
esta funçao ativa a bullet_player1 e dá a sua direcao
*/
void bullet_show(int c, char player1_last_direction_moved, Player player1, Bullet bullet_player1, Player player2, Bullet bullet_player2);
void bullet_show_multi_player(int c, Player player1, Player player2, Bullet bullet_player1, Bullet bullet_player2);
/*
esta funçao dá posição (a posicao dela é igual à do jogador)
*/
void bullet_position(Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2);
/*
esta funçao faz a bala desaparecer quando colide com algo (a posicao dela é igual à do jogador)
*/
void bullet_collision(int colunas, Map mapa[][colunas], Bullet bullet_player1, Bullet bullet_player2);
/*
Esta função vai updatando e dando print à bala
*/
void create_bullet(Bullet bullet_player1, Bullet bullet_player2);

void bullet_hit_mobs(int linhas, int colunas, Map mapa[][colunas], Bullet bullet_player1, Mob *mobs, int mob_positionX, int mob_positionY);

void do_guns_aplications(char c, char player1_last_direction_moved, int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2, int mob_positionX, int mob_positionY);

void do_guns_aplications_multi_player(char c, int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2);

#endif