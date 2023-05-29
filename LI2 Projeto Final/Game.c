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


void reset_player(Player *player1)
{
    player1->hp = 100;
    player1->trapNumber = 3;
    player1->ammo = 100;
    player1->score = 0;
    player1->gun_three_on = 0;
    player1->last_direction_moved = 'w';
    player1->character = '@';
    player1->aspirineNumber = 0;
    player1->money = 0;
    player1->usingNightStick = 0;
    player1->nightstickNumber = 5;
}


void go_to_scoreboard_win(Player *player1, int linhas, int colunas)
{
    if (player1->score > 0)
        final_win(linhas, colunas, player1->score);
    if (player1->score == 0)
        final_0_score_win(linhas, colunas);
}


int player_is_alive(Player *player1)
{
    return (player1->hp > 0 ? 1 : 0);
}

int game_is_not_over(Game *game)
{
    return (game->game_over == 0 ? 1 : 0);
}

void main_game_single_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Player *player1, Player *player2, Mob *mobs, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2)
{
    while (game_is_not_over(game))
    {
        if (player_is_alive(player1))
        {
            cbreak();
            timeout(300);
            game->key_pressed = getch();
            do_structure_aplications_single_player(linhas, colunas, mapa, player1, mobs);
            do_update_map_single_player(colunas, mapa, linhas, game, player1, mobs); 
            do_insert_flag(linhas, colunas, mapa, flag, game);                      
            do_add_score(1, flag, game, player1, player2);
            do_print_map(linhas, colunas, mapa); 
            do_mob_apps(colunas, mapa, player1, mobs);
            do_guns_aplications(linhas, colunas, mapa, game, mobs, bullet_player1, bullet_player2, player1, player2);
            do_add_player(1, player1, player2);
            printMobs(mobs);
            print_footer_single_player(player1);
        }
        else
        {
            game->game_over = 1;
            clear();
            refresh();
            go_to_scoreboard_win(player1, linhas, colunas);
            game->is_flag_placed = 0;
        }
    }
}
void main_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Player *player1, Player *player2, Flag *flag, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2)
{
    while (game_is_not_over(game))
    {
        if (player_is_alive(player1) && player_is_alive(player2))
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
            game->is_flag_placed = 0;
        }
    }
}
void main_game_challenge(int linhas, int colunas, Map mapa[][colunas], Flag *flag, Game *game, Player *player1, Player *player2, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2)
{
    while (game_is_not_over(game))
    {
        if (player_is_alive(player1))
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
            create_light_lighthouse(linhas, colunas, mapa, mobs);
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
            game->is_flag_placed = 0;
        }
    }
}

void start_game_single_player(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Player *player1, Player *player2)
{
    do_print_map(linhas, colunas, mapa); 
    reset_player(player1);
    player1_position(linhas, colunas, player1);
    do_add_player(1, player1, player2);
    initializeMobs(linhas, colunas, mapa, mobs);
    printMobs(mobs);
    print_footer_single_player(player1);
}
void start_game_multi_player(int linhas, int colunas, Map mapa[][colunas], Player *player1, Player *player2)
{
    do_print_map(linhas, colunas, mapa);
    reset_player(player1);
    reset_player(player2);
    player1_position(linhas, colunas, player1);
    player2_position(linhas, colunas, player2);
    do_add_player(2, player1, player2);
    print_footer_multi_player(linhas, colunas, player1, player2);
}
void start_game_challenge(int linhas, int colunas, Map mapa[][colunas], Player *player1, Player *player2, Mob *mobs)
{
    do_print_map(linhas, colunas, mapa);
    reset_player(player1);
    player1_position(linhas, colunas, player1);
    do_add_player(1, player1, player2);
    initializeMobs(linhas, colunas, mapa, mobs);
    printMobs(mobs);
    createlight(player1->positionY, player1->positionX, colunas, linhas, 3, player1);
    create_light_lighthouse(linhas, colunas, mapa, mobs);
    print_footer_challenge(player1);
}
