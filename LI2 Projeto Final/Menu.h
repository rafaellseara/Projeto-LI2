#ifndef MENU_H
#define MENU_H

#include "Structs.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"

#include <string.h>
#include <math.h>
#include <ctype.h>

/*
Função que imprime a janela de pausa no ecrã assim que o utilizador pressiona na tecla p para pausar o jogo.
Esta desaparece assim que o utilizador carrega na tecla enter.
*/
void pause_win(int linhas, int colunas);
/*
Função que imprime a janela final do jogo de score > 0 no ecrã assim que o utilizado perde.
Esta desaparece assim que o utilizador carrega na tecla enter depois de escolher o nome.
*/
void final_win(int linhas, int colunas, int score);
/*
Função que imprime a janela final do jogo de score 0 no ecrã assim que o utilizado perde (hp = 0)
Esta desaparece assim que o utilizador carrega na tecla enter.
*/
void final_0_score_win(int linhas, int colunas);

void buy_menu_win(int linhas, int colunas, Player *player);

void sort_scoreboard();
void sort_scoreboard_desafio();
void scoreboard(int linhas, int colunas);
void scoreboard_desafio(int linhas, int colunas);
void multi_jogo_win(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Game *game, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
void multi_scoreboard_win(int linhas, int colunas);

/*
Função do menu principal do jogo.
Imprime o menu assim que o jogo começa.
Contem uma variadade de opções, as quais podem ser todas acessadas.
*/
void menu(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Game *game, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);

void final_win_desafio(int linhas, int colunas, int score);

void final_multiplayer_win(int linhas, int colunas, int player1_hp, int player2_hp);




#endif