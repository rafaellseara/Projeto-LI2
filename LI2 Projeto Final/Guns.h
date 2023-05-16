#ifndef GUNS_H
#define GUNS_H



void change_player_weapon(char c, Player *player1);

void shot_fired(int direction, int player, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
/*
esta funçao ativa a bullet_player1 e dá a sua direcao
*/
void bullet_show(Game *game, Player *player1, Bullet *bullet_player1, Player *player2, Bullet *bullet_player2);
void bullet_show_multi_player(Game *game, Player *player1, Player *player2, Bullet *bullet_player1, Bullet *bullet_player2);
/*
esta funçao dá posição (a posicao dela é igual à do jogador)
*/
void bullet_position(Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
/*
esta funçao faz a bala desaparecer quando colide com algo (a posicao dela é igual à do jogador)
*/
void bullet_collision(int colunas, Map mapa[][colunas], Bullet *bullet_player1, Bullet *bullet_player2);
/*
Esta função vai updatando e dando print à bala
*/
void create_bullet(Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);

void bullet_hit_mobs(int linhas, int colunas, Map mapa[][colunas], Bullet *bullet_player1, Mob *mobs, Player *player1);

void bullet_hit_player(Player *player1, Player *player2, Bullet *bullet_player1, Bullet *bullet_player2);

void do_guns_aplications(int linhas, int colunas, Map mapa[][colunas], Game *game, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);

void do_guns_aplications_multi_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);

#endif