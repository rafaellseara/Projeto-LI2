#ifndef MOBS_H
#define MOBS_H

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"




void mob_position(int quadrante, int linhas, int colunas, Map mapa[][colunas], int mob_positionX, int mob_positionY);

void update_mob(int index, int linhas, int colunas, Map mapa[][colunas], int mob_positionX, int mob_positionY, Mob *mobs);

/*
esta funçao calcula distâncias
*/
float calc_dist(int a, int b, int c, int d);
/*
esta funçao serve para ver se o Player está numa range de 10 do Mob devido a distancia nao estar a dar
*/
void mob_view(Player player1, Mob *mobs);
/*
esta funçao faz o movimento dos mobs
*/
void mob_movement(int colunas, Map mapa[][colunas], Player player1, Mob *mobs);
/*
Faz o Mob andar aos quadrados quando está longe
*/
void mob_movement_far(int colunas, Map mapa[][colunas], Mob *mobs);
/*
Mob ataca se tiver abeira do player
*/
void mob_attacks(Mob *mobs, Player player1);

void do_mob_apps(int colunas, Map mapa[][colunas], Player player1, Mob *mobs);

// estar num quadrado 5x5 vazio; id 1- 1º quadrante, etc;
// enquanto nao esta num quadrado
// while (position_is_not_valid)
int position_is_not_valid(int colunas, Map mapa[][colunas], int mob_positionX, int mob_positionY);
/*
inicializar mobs
*/
void initializeMobs(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, int mob_positionX, int mob_positionY);

void printMobs(Mob *mobs);

#endif