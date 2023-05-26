#include <ncurses.h>

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"



void do_check_nightstick(Game game, Player player1)
{
    // condiçao para verificar quantos passos deu com o nightstick on
    if (player1.usingNightStick == 1)
    {
        game.nightstick_time_of_usage++;
        if (game.nightstick_time_of_usage == game.maximum_nightstick_time)
        {
            player1.usingNightStick = 0;
            game.nightstick_time_of_usage = 0;
        }
    }
}


void main_game_single_player(char c, int linhas, int colunas, Map mapa[][colunas], Game game, Player player1, Player player2, Mob *mobs, Flag flag, Bullet bullet_player1, Bullet bullet_player2, int mob_positionX, int mob_positionY)
{
    while (game.game_over == 0)
    {
        if (player1.hp > 0)
        {
            cbreak();
            timeout(200);
            c = getch();
            do_structure_aplications_single_player(colunas, mapa, player1);
            do_update_map_single_player(c, colunas, mapa, linhas, game, player1, mobs); // aqui fazemos o update do mapa sempre que o utilizador prima uma tecla
            do_insert_flag(linhas, colunas, mapa, flag, game);           // inserir a flag
            do_add_score(1, flag, game, player1, player2);
            do_print_map(linhas, colunas, mapa, 1); // imprimimos o mapa para o utilizador
            do_mob_apps(colunas, mapa, player1, mobs);
            do_guns_aplications(c, player1.last_direction_moved, linhas, colunas, mapa, mobs, bullet_player1, bullet_player2, player1, player2, mob_positionX, mob_positionY);
            // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
            do_add_player(1, player1, player2);
            printMobs(mobs);
            // tem de se ver
            // moveInSquare(top_left_corner_X, top_left_corner_Y, &mob_positionX, &mob_positionY, &direction);
            // mvaddch(mob_positionY, mob_positionX, '1');
            print_footer_single_player(player1); // imprimir caracteristicas do jogo no canto
        }
        else
        {
            game.game_over = 1;
            clear();
            refresh();
            if (player1.score > 0)
                final_win(linhas, colunas, player1.score);
            if (player1.score == 0)
                final_0_score_win(linhas, colunas);
            player1.hp = 100;
            player1.trapNumber = 3;
            player1.ammo = 100;
            player1.score = 0;
            game.is_flag_placed = 0;
        }
    }
}
void main_game_multi_player(char c, int linhas, int colunas, Map mapa[][colunas], Game game, Player player1, Player player2, Flag flag, Mob *mobs, Bullet bullet_player1, Bullet bullet_player2)
{
    while (game.game_over == 0)
    {
        if (player1.hp > 0 && player2.hp > 0)
        {
            cbreak();
            timeout(200);
            c = getch();
            do_structure_aplications_multi_player(colunas, mapa, player1, player2);
            do_update_map_multi_player(c, colunas, mapa, linhas, game, player1, player2);
            do_add_score(2, flag, game, player1, player2);
            do_insert_flag(linhas, colunas, mapa, flag, game);
            // aqui vamos inserir as mobs
            do_print_map(linhas, colunas, mapa, 1);
            do_guns_aplications_multi_player(c, linhas, colunas, mapa, mobs, bullet_player1, bullet_player2, player1, player2);
            do_add_player(2, player1, player2);
            print_footer_multi_player(linhas, colunas, player1, player2);
        }
        else
        {
            game.game_over = 1;
            clear();
            refresh();
            final_win(linhas, colunas, player1.score);
            player1.hp = 100;
            player1.score = 0;
            player2.hp = 100;
            player2.score = 0;
            game.is_flag_placed = 0;
        }
    }
}
void main_game_challenge(char c, int linhas, int colunas, Map mapa[][colunas], Flag flag, Game game, Player player1, Player player2, Mob *mobs, Bullet bullet_player1, Bullet bullet_player2, int mob_positionX, int mob_positionY)
{
    while (game.game_over == 0)
    {
        if (player1.hp > 0)
        {
            cbreak();
            timeout(200);
            c = getch();
            do_structure_aplications_single_player(colunas, mapa, player1);
            do_update_map_single_player(c, colunas, mapa, linhas, game, player1, mobs);
            do_check_nightstick(game, player1);
            do_insert_flag(linhas, colunas, mapa, flag, game);
            do_add_score(1, flag, game, player1, player2);
            // cenas das mobs
            do_print_map(linhas, colunas, mapa, 1);
            createlight(player1.positionY, player1.positionX, colunas, linhas, 3, player1);
            do_guns_aplications(c, player1.last_direction_moved, linhas, colunas, mapa, mobs, bullet_player1, bullet_player2, player1, player2, mob_positionX, mob_positionY);
            do_add_player(1, player1, player2);
            print_footer_challenge(player1);
        }
        else
        {
            game.game_over = 1;
            clear();
            refresh();
            final_win(linhas, colunas, player1.score);
            player1.hp = 100;
            player1.score = 0;
            game.is_flag_placed = 0;
        }
    }
}

void start_game_single_player(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Player player1, Player player2, int mob_positionX, int mob_positionY)
{
    do_print_map(linhas, colunas, mapa, 1); // imprimimos o mapa inicial
    // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
    player1_position(linhas, colunas, player1); // acertar a posiçao do jogador
    do_add_player(1, player1, player2);
    initializeMobs(linhas, colunas, mapa, mobs, mob_positionX, mob_positionY);
    printMobs(mobs);
    // imprimir caracteristicas do jogo no canto
    print_footer_single_player(player1);
}
void start_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Player player1, Player player2)
{
    do_print_map(linhas, colunas, mapa, 1);
    player1_position(linhas, colunas, player1);
    player2_position(linhas, colunas, player2);
    do_add_player(2, player1, player2);
    // falta imprimir aqui as mobs
    // falta imprimir aqui o footer
}
void start_game_challenge(int linhas, int colunas, Map mapa[][colunas], Player player1, Player player2)
{
    do_print_map(linhas, colunas, mapa, 1);
    player1_position(linhas, colunas, player1);
    do_add_player(1, player1, player2);
    createlight(player1.positionY, player1.positionX, colunas, linhas, 3, player1);
    print_footer_challenge(player1);
}



