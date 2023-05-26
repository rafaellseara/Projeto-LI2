#ifndef MAP_H
#define MAP_H





/*
função que apoia a criação do mapa juntando paredes
*/
void do_concat_walls(int linhas, int colunas, Map mapa[][colunas]);
/*
esta funçao cria o mapa inicial
falta completar fazendo com que crie estruturas em condiçoes, juntas e nao apenas randomizadas - feito
falta acrescentar lagos, muniçoes, etc
*/
void do_create_map(int linhas, int colunas, Map mapa[][colunas], Flag *flag, Game *game);
/*
esta funçao é muito simples e apenas imprime o mapa para o ecra do utilizador
*/
void do_print_map(int linhas, int colunas, Map mapa[][colunas]);

void print_footer_single_player(Player *player1);
void print_footer_multi_player(int linhas, int colunas, Player *player1, Player *player2);
void print_footer_challenge(Player *player1);

/*
funçao que destroi uma parede na direçao onde se moveu pela ultima vez
*/
void do_destroy_wall(char last_direction_moved, int y, int x, int linhas, int colunas, Map mapa[][colunas]);


/*
funçao da luz / escuridão
    ------------------360 LINHAS?------------------
*/
void createlight(int posy, int posx, int colunas, int linhas, int z, Player *player1);
/*
funçao que acrescenta um lago ao mapa
*/
void do_add_lake(int linhas, int colunas, Map mapa[][colunas]);
/*
funçao que acrescenta casa de curar vida
*/
void do_add_life(int linhas, int colunas, Map mapa[][colunas]);
/*
funçao que acrescenta casa de aumentar muniçao
*/
void do_add_ammo(int linhas, int colunas, Map mapa[][colunas]);
/*
funçao que adiciona o farol
*/
void do_add_lighthouse(int linhas, int colunas, Map mapa[][colunas]);

/*
função que conta quantas paredes existem num quadrado 3x3 do mapa
*/
int count_walls_3x3(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual);
/*
função que conta quantas paredes existem num quadrado 5x5 do mapa
*/
int count_walls_5x5(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual);
/*
função que conta quantas paredes existem num quadrado 5x5 do mapa
*/
int count_walls_4x8(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual);
/*
função que insere a flag no mapa
*/
void do_insert_flag(int linhas, int colunas, Map mapa[][colunas], Flag *flag, Game *game);

#endif