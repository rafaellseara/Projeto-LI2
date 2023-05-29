#ifndef MOBS_H
#define MOBS_H





/*
-- funçao que atribui a posiçao a mob
    a77399 - Fernando Pires
*/
void mob_position(int quadrante, int linhas, int colunas, Map mapa[][colunas]);

/*
-- funçao que faz todos os updates à mob depois de ela morrer
    a77399 - Fernando Pires
*/
void update_mob(int index, int linhas, int colunas, Map mapa[][colunas], Mob *mobs);

/*
-- esta funçao calcula distâncias
    a103998 - Pedro Teixeira
*/
float calc_dist(int a, int b, int c, int d);
/*
-- esta funçao serve para ver se o Player está numa range de 10 do Mob devido a distancia nao estar a dar
    a103998 - Pedro Teixeira
*/
void mob_view(Player *player1, Mob *mobs);
/*
-- esta funçao faz o movimento dos mobs
    a103998 - Pedro Teixeira
*/
void mob_movement(int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);
/*
-- faz o Mob andar aos quadrados quando está longe
    a103998 - Pedro Teixeira
*/
void mob_movement_far(int colunas, Map mapa[][colunas], Mob *mobs);
/*
-- mob ataca se tiver abeira do player
    a103998 - Pedro Teixeira
*/
void mob_attacks(Mob *mobs, Player *player1);

/*
-- funçao que junta todas as auxiliares
    a77399 - Fernando Pires
    a103998 - Pedro Teixeira
*/
void do_mob_apps(int colunas, Map mapa[][colunas], Player *player1, Mob *mobs);

/*
-- funçao que testa se a posiçao da mob é invalida
    a77399 - Fernando Pires
*/
int position_is_not_valid(int colunas, Map mapa[][colunas]);
/*
-- inicializar mobs
    a77399 - Fernando Pires
*/
void initializeMobs(int linhas, int colunas, Map mapa[][colunas], Mob *mobs);
/*
-- imprime os mobs no ecra
    a77399 - Fernando Pires
*/
void printMobs(Mob *mobs);

#endif