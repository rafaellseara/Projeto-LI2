#include <ncurses.h>
#include <stdlib.h>


#include "Menu.h"
#include "Game.h"



void do_check_nightstick(Game *game, Player *player1)
{
    // condiçao para verificar quantos passos deu com o nightstick on
    if (player1->usingNightStick == 1)
    {
        game->nightstick_time_of_usage++;
        if (game->nightstick_time_of_usage == game->maximum_nightstick_time)
        {
            player1->usingNightStick = 0;
            game->nightstick_time_of_usage = 0;
        }
    }
}


void main_game_single_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Player *player1, Player *player2, Mob *mobs, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2)
{
    while (game->game_over == 0)
    {
        if (player1->hp > 0)
        {
            cbreak();
            timeout(300);
            game->key_pressed = getch();
            do_structure_aplications_single_player(linhas, colunas, mapa, player1, mobs);
            do_update_map_single_player(colunas, mapa, linhas, game, player1, mobs); // aqui fazemos o update do mapa sempre que o utilizador prima uma tecla
            do_insert_flag(linhas, colunas, mapa, flag, game);           // inserir a flag
            do_add_score(1, flag, game, player1, player2);
            do_print_map(linhas, colunas, mapa); // imprimimos o mapa para o utilizador
            do_mob_apps(colunas, mapa, player1, mobs);
            do_guns_aplications(linhas, colunas, mapa, game, mobs, bullet_player1, bullet_player2, player1, player2);
            // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
            do_add_player(1, player1, player2);
            printMobs(mobs);
            print_footer_single_player(player1); // imprimir caracteristicas do jogo no canto
        }
        else
        {
            game->game_over = 1;
            clear();
            refresh();
            if (player1->score > 0)
                final_win(linhas, colunas, player1->score);
            if (player1->score == 0)
                final_0_score_win(linhas, colunas);
            player1->hp = 100;
            player1->trapNumber = 3;
            player1->ammo = 100;
            player1->score = 0;
            game->is_flag_placed = 0;
        }
    }
}
void main_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Player *player1, Player *player2, Flag *flag, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2)
{
    while (game->game_over == 0)
    {
        if (player1->hp > 0 && player2->hp > 0)
        {
            cbreak();
            timeout(200);
            game->key_pressed = getch();
            do_structure_aplications_multi_player(colunas, mapa, player1, player2);
            do_update_map_multi_player(colunas, mapa, linhas, game, player1, player2);
            do_add_score(2, flag, game, player1, player2);
            do_insert_flag(linhas, colunas, mapa, flag, game);
            do_print_map(linhas, colunas, mapa);
            do_guns_aplications_multi_player(linhas, colunas, mapa, game, mobs, bullet_player1, bullet_player2, player1, player2);
            do_add_player(2, player1, player2);
            print_footer_multi_player(linhas, colunas, player1, player2);
        }
        else
        {
            game->game_over = 1;
            clear();
            refresh();
            final_multiplayer_win(linhas, colunas, player1->hp, player2->hp);
            player1->hp = 100;
            player1->score = 0;
            player2->hp = 100;
            player2->score = 0;
            game->is_flag_placed = 0;
        }
    }
}
void main_game_challenge(int linhas, int colunas, Map mapa[][colunas], Flag *flag, Game *game, Player *player1, Player *player2, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2)
{
    while (game->game_over == 0)
    {
        if (player1->hp > 0)
        {
            cbreak();
            timeout(200);
            game->key_pressed = getch();
            do_structure_aplications_single_player(linhas, colunas, mapa, player1, mobs);
            do_update_map_single_player(colunas, mapa, linhas, game, player1, mobs);
            do_check_nightstick(game, player1);
            do_insert_flag(linhas, colunas, mapa, flag, game);
            do_add_score(1, flag, game, player1, player2);
            do_print_map(linhas, colunas, mapa);
            do_mob_apps(colunas, mapa, player1, mobs);
            printMobs(mobs);
            createlight(player1->positionY, player1->positionX, colunas, linhas, 3, player1);
            do_guns_aplications(linhas, colunas, mapa, game, mobs, bullet_player1, bullet_player2, player1, player2);
            do_add_player(1, player1, player2);
            print_footer_challenge(player1);
        }
        else
        {
            game->game_over = 1;
            clear();
            refresh();
            final_win_desafio(linhas, colunas, player1->score);
            player1->hp = 100;
            player1->score = 0;
            game->is_flag_placed = 0;
        }
    }
}

void start_game_single_player(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Player *player1, Player *player2)
{
    do_print_map(linhas, colunas, mapa); // imprimimos o mapa inicial
    // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
    player1_position(linhas, colunas, player1); // acertar a posiçao do jogador
    do_add_player(1, player1, player2);
    initializeMobs(linhas, colunas, mapa, mobs);
    printMobs(mobs);
    // imprimir caracteristicas do jogo no canto
    print_footer_single_player(player1);
}
void start_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Player *player1, Player *player2)
{
    do_print_map(linhas, colunas, mapa);
    player1_position(linhas, colunas, player1);
    player2_position(linhas, colunas, player2);
    do_add_player(2, player1, player2);
    print_footer_multi_player(linhas, colunas, player1, player2);
}
void start_game_challenge(int linhas, int colunas, Map mapa[][colunas], Player *player1, Player *player2, Mob *mobs)
{
    do_print_map(linhas, colunas, mapa);
    player1_position(linhas, colunas, player1);
    do_add_player(1, player1, player2);
    initializeMobs(linhas, colunas, mapa, mobs);
    printMobs(mobs);
    createlight(player1->positionY, player1->positionX, colunas, linhas, 3, player1);
    print_footer_challenge(player1);
}



