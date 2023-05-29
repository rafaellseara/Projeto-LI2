#ifndef PLAYER_H
#define PLAYER_H




/*
-- atribui as posiçoes aos jogadores
    a77399 - Fernando Pires
*/
void player1_position(int linhas, int colunas, Player *player1);
void player2_position(int linhas, int colunas, Player *player2);
/*
-- adiciona o jogador no ecra
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void do_add_player(int game_type, Player *player1, Player *player2);
/*
-- verifica a posiçao em que a mob se encontra em relaçao ao jogador
    a77399 - Fernando Pires
*/
int player_relation_to_mob(int movement, Mob *mobs, Player *player1);
/*
-- verifica se o movimento é valido (nao ha mobs, nem farol, nem paredes)
    a77399 - Fernando Pires
*/
int valid_player_movement(int movement, int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);

/*
-- ve se o Player está a um de distanica do mob
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void close_to_player(Player *player1, Mob *mobs);
/*
-- se a mob estiver a 1 de distancia do jogador pode dar murro
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void do_player_punch(Game *game, int linhas, int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);

/*
esta funçao faz o update do mapa, sempre que o jogador se mexe
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
    a104094 - Rafael Seara
*/
void do_update_map_single_player(int colunas, Map mapa[][colunas], int linhas, Game *game, Player *player1, Mob *mobs);
void do_update_map_multi_player(int colunas, Map mapa[][colunas], int linhas, Game *game, Player *player1, Player *player2);
/*
-- adiciona score ao player
    a77399 - Fernando Pires
*/
void do_add_score(int game_type, Flag *flag, Game *game, Player *player1, Player *player2);

/*
-- funçao relativas às estruturas que tiram e acrescentam vida/amunição
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void do_structure_aplications_single_player(int linhas, int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);
void do_structure_aplications_multi_player(int colunas, Map mapa[][colunas], Player *player1, Player *player2);

#endif