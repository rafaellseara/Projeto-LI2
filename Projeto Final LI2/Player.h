#ifndef PLAYER_H
#define PLAYER_H





void player1_position(int linhas, int colunas, Player *player1);
void player2_position(int linhas, int colunas, Player *player2);
void do_add_player(int game_type, Player *player1, Player *player2);
int player_relation_to_mob(int movement, Mob *mobs, Player *player1);
int valid_player_movement(int movement, int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);

/*
Ve se o Player esstá a um de distanica do mob
*/
void close_to_player(Player *player1, Mob *mobs);
// A direção do ataque está relacionada com o ultimo movimento do jogador
void do_player_punch(Game *game, int linhas, int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);

void do_update_map_single_player(int colunas, Map mapa[][colunas], int linhas, Game *game, Player *player1, Mob *mobs);
void do_update_map_multi_player(int colunas, Map mapa[][colunas], int linhas, Game *game, Player *player1, Player *player2);
void do_add_score(int game_type, Flag *flag, Game *game, Player *player1, Player *player2);

/*
funçao relativas às estruturas que tiram e acrescentam vida/amunição
*/
void do_structure_aplications_single_player(int colunas, Map mapa[][colunas], Player *player1);
void do_structure_aplications_multi_player(int colunas, Map mapa[][colunas], Player *player1, Player *player2);

#endif