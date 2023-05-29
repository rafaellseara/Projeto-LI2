#ifndef GAME_H
#define GAME_H



/*
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void do_check_nightstick(Game *game, Player *player1);

/* 
-- dar reset as variaveis do player
    a77399 - Fernando Pires
*/
void reset_player(Player *player1);

/*
-- mandar para janela do scoreboard
    a77399 - Fernando Pires
*/ 
void go_to_scoreboard_win(Player *player1, int linhas, int colunas);

/*
-- verificar se o jogador está vivo
    a77399 - Fernando Pires
*/
int player_is_alive(Player *player1);

/*
-- verificar que o jogo ainda nao acabou
    a77399 - Fernando Pires
*/
int game_is_not_over(Game *game);

/*
-- funçao que tem todas as propriedades do jogo
    a77399 - Fernando Pires
*/
void main_game_single_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Player *player1, Player *player2, Mob *mobs, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2);
void main_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Player *player1, Player *player2, Flag *flag, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2);
void main_game_challenge(int linhas, int colunas, Map mapa[][colunas], Flag *flag, Game *game, Player *player1, Player *player2, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2);
/*
-- funçao que inicia o jogo
    a77399 - Fernando Pires
*/
void start_game_single_player(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Player *player1, Player *player2);
void start_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Player *player1, Player *player2);
void start_game_challenge(int linhas, int colunas, Map mapa[][colunas], Player *player1, Player *player2, Mob *mobs);

#endif