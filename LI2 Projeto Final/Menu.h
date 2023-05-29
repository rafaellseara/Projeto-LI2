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
-- função que imprime a janela de pausa no ecrã assim que o utilizador pressiona na tecla p para pausar o jogo.
-- esta desaparece assim que o utilizador carrega na tecla enter.
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void pause_win(int linhas, int colunas);
/*
-- função que imprime a janela final do jogo de score > 0 no ecrã assim que o utilizado perde.
-- esta desaparece assim que o utilizador carrega na tecla enter depois de escolher o nome.
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void final_win(int linhas, int colunas, int score);
/*
-- função que imprime a janela final do jogo de score 0 no ecrã assim que o utilizado perde (hp = 0)
-- esta desaparece assim que o utilizador carrega na tecla enter.
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void final_0_score_win(int linhas, int colunas);
/*
-- comentar a funçao Rafael e Sara
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/

/*
-- funções que apresentam o scoreboard
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void sort_scoreboard();
void sort_scoreboard_desafio();
void scoreboard(int linhas, int colunas);
void scoreboard_desafio(int linhas, int colunas);

/*
-- funções que apresentam várias janelas
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void multi_jogo_win(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Game *game, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
void multi_scoreboard_win(int linhas, int colunas);
void final_win_desafio(int linhas, int colunas, int score);
void final_multiplayer_win(int linhas, int colunas, int player1_hp, int player2_hp);
void buy_menu_win(int linhas, int colunas, Player *player);
/*
Função do menu principal do jogo.
Imprime o menu assim que o jogo começa.
Contem uma variadade de opções, as quais podem ser todas acessadas.4
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void menu(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Game *game, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);

/*
-- função que imprime a janela de instruçoes no ecrã
-- esta desaparece assim que o utilizador carrega na tecla x.
    a104608 - Sara Silva
    a104094 - Rafael Seara
*/
void exibirManualInstrucoes(int linhas, int colunas);


#endif