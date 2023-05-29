#ifndef GUNS_H
#define GUNS_H


/*
-- esta funçao troca as armas do jogadores
    a103998 - Pedro Teixeira
*/
void change_player_weapon(char c, Player *player1, Bullet *bullet_player1);
/*
-- esta funçao faz o disparo da arma
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void shot_fired(int direction, int player, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
/*
-- esta funçao serve para mostrar a bala
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void bullet_show(Game *game, Player *player1, Bullet *bullet_player1, Player *player2, Bullet *bullet_player2);
void bullet_show_multi_player(Game *game, Player *player1, Player *player2, Bullet *bullet_player1, Bullet *bullet_player2);
/*
-- esta funçao dá posição (a posicao dela é igual à do jogador)
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void bullet_position(Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
/*
-- esta funçao faz a bala desaparecer quando colide com algo (a posicao dela é igual à do jogador)
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void bullet_collision(int colunas, Map mapa[][colunas], Bullet *bullet_player1, Bullet *bullet_player2);
/*
-- esta função vai updatando e dando print à bala
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void create_bullet(Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
/*
-- funçoes auxiliares
    a77399 - Fernando Pires
*/
int bullet_in_Y_mob_range(Bullet *bullet_player1, Mob *mobs, int i);
int bullet_in_X_mob_range(Bullet *bullet_player1, Mob *mobs, int i);
int bullet_in_vertical(Bullet *bullet_player1);
int bullet_in_horizontal(Bullet *bullet_player1);
void bullet_disappears(Bullet *bullet_player1);
void update_player_score_money(Player *player1);
int mob_is_dead(Mob *mobs, int i);

/*
-- esta funçao faz coisas quando a bala atinge mobs
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void bullet_hit_mobs(int linhas, int colunas, Map mapa[][colunas], Bullet *bullet_player1, Mob *mobs, Player *player1);
/*
-- funçoes auxiliares
    a77399 - Fernando Pires
*/
int bullet_is_showing(Bullet *bullet_player1);
int equal_bullet_to_player_position(Bullet *bullet, Player *player);
/*
-- esta funçao faz coisas quando a bala atinge os players
    a77399 - Fernando Pires
*/
void bullet_hit_player(Player *player1, Player *player2, Bullet *bullet_player1, Bullet *bullet_player2);

/*
-- estas funções juntam todas as principais 
    a77399 - Fernando Pires
*/
void do_guns_aplications(int linhas, int colunas, Map mapa[][colunas], Game *game, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);
void do_guns_aplications_multi_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2);

#endif