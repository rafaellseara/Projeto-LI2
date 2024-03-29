#include <ncurses.h>

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"



void player1_position(int linhas, int colunas, Player player1)
{

    // inserir o jogador 1 à esquerda do farol
    int centerY = linhas / 2;
    int centerX = colunas / 2;
    player1.positionY = centerY;
    player1.positionX = centerX - 4;
}
void player2_position(int linhas, int colunas, Player player2)
{

    // inserir o jogador 1 à esquerda do farol
    int centerY = linhas / 2;
    int centerX = colunas / 2;
    player2.positionY = centerY;
    player2.positionX = centerX + 4;
}
void do_add_player(int game_type, Player player1, Player player2)
{
    if (game_type == 1)
    {
        attron(COLOR_PAIR(5));
        mvaddch(player1.positionY, player1.positionX, player1.character);
        attroff(COLOR_PAIR(5));
    }
    else
    {
        attron(COLOR_PAIR(5));
        mvaddch(player1.positionY, player1.positionX, player1.character);
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(6));
        mvaddch(player2.positionY, player2.positionX, player2.character);
        attroff(COLOR_PAIR(6));
    }
}
int player_relation_to_mob(int movement, Mob *mobs, Player player1)
{
    switch (movement)
    {
    case 1:
        for (int i = 0; i < 3; i++)
        {
            if (mobs[i].positionX == player1.positionX &&
                mobs[i].positionY == player1.positionY - 1)
                return 1;
        }
        break;
    case 2:
        for (int i = 0; i < 3; i++)
        {
            if (mobs[i].positionX == player1.positionX &&
                mobs[i].positionY == player1.positionY + 1)
                return 1;
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++)
        {
            if (mobs[i].positionX == player1.positionX - 1 &&
                mobs[i].positionY == player1.positionY)
                return 1;
        }
        break;
    case 4:
        for (int i = 0; i < 3; i++)
        {
            if (mobs[i].positionX == player1.positionX + 1 &&
                mobs[i].positionY == player1.positionY)
                return 1;
        }
        break;
    }
    return 0;
}
int valid_player_movement(int movement, int colunas, Map mapa[][colunas], Player player1, Mob *mobs)
{
    switch (movement)
    {
    case 1:
        if (mapa[player1.positionY - 1][player1.positionX].visible_piece != '#' &&
            mapa[player1.positionY - 1][player1.positionX].visible_piece != '!' &&
            player_relation_to_mob(movement, mobs, player1) == 0)
            return 1;
        else
            return 0;
        break;
    case 2:
        if (mapa[player1.positionY + 1][player1.positionX].visible_piece != '#' &&
            mapa[player1.positionY + 1][player1.positionX].visible_piece != '!' &&
            player_relation_to_mob(movement, mobs, player1) == 0)
            return 1;
        else
            return 0;
        break;
    case 3:
        if (mapa[player1.positionY][player1.positionX - 1].visible_piece != '#' &&
            mapa[player1.positionY][player1.positionX - 1].visible_piece != '!' &&
            player_relation_to_mob(movement, mobs, player1) == 0)
            return 1;
        else
            return 0;
        break;
    case 4:
        if (mapa[player1.positionY][player1.positionX + 1].visible_piece != '#' &&
            mapa[player1.positionY][player1.positionX + 1].visible_piece != '!' &&
            player_relation_to_mob(movement, mobs, player1) == 0)
            return 1;
        else
            return 0;
        break;
    }
    return 0;
}


void close_to_player(Player player1, Mob *mobs)
{
    for (int i = 0; i < 4; i++)
    {
        for (int coluna = player1.positionX - 1; coluna <= player1.positionX + 1; coluna++)
        {
            for (int linha = player1.positionY - 1; linha <= player1.positionY + 1; linha++)
            {
                if(mobs[i].positionX == coluna && mobs[i].positionY == linha)
                    mobs[i].damaging_player = 1;
            }
        }
    }
}

void do_player_punch(char c, int linhas, int colunas, Map mapa[][colunas], Player player1, Mob *mobs, int mob_positionX, int mob_positionY)
{

    if (player1.gun != 1 || c != ' ')
    {
        return;
    }
    for (int i = 0; i < 4; i++)
    {

        for (int current_Y = player1.positionY - 1; current_Y <= player1.positionY + 1; current_Y++)
        {
            for (int current_X = player1.positionX - 1; current_X <= player1.positionX + 1; current_X++)
            {
                if (mobs[i].positionX == current_X && mobs[i].positionY == current_Y)
                {
                    mobs[i].hp -= 25;
                    if (mobs[i].hp <= 0)
                    {
                        update_mob(i, linhas, colunas, mapa, mob_positionX, mob_positionY, mobs);
                    }
                }
            }
        }
    }
}

/*
esta funçao faz o update do mapa, sempre que o jogador se mexe
*/
void do_update_map_single_player(char c, int colunas, Map mapa[][colunas], int linhas, Game game, Player player1, Mob *mobs) // tem de receber o mapa desta forma pois é 2D
{
    // transformar num switch??
    if (c == 'w' && valid_player_movement(1, colunas, mapa, player1, mobs) == 1)
    {
        player1.last_direction_moved = 'w'; // guardar ultima direçao em que se moveu
        player1.positionY--;
        player1.character = '^';
    }
    else if (c == 's' && valid_player_movement(2, colunas, mapa, player1, mobs) == 1)
    {
        player1.last_direction_moved = 's';
        player1.positionY++;
        player1.character = 'v';
    }
    else if (c == 'a' && valid_player_movement(3, colunas, mapa, player1, mobs) == 1)
    {
        player1.last_direction_moved = 'a';
        player1.positionX--;
        player1.character = '<';
    }
    else if (c == 'd' && valid_player_movement(4, colunas, mapa, player1, mobs) == 1)
    {
        player1.last_direction_moved = 'd';
        player1.positionX++;
        player1.character = '>';
    }
    else if (c == 'x') // destruir paredes
    {
        do_destroy_wall(player1.last_direction_moved, player1.positionY, player1.positionX, linhas, colunas, mapa);
    }
    else if (c == 'e' && mapa[player1.positionY][player1.positionX + 1].visible_piece == ' ' && player1.trapNumber > 0) // colocar armadilhas no chao
    {
        mapa[player1.positionY][player1.positionX + 1].visible_piece = '^';
        player1.trapNumber -= 1;
    }
    else if (c == 'r' && mapa[player1.positionY][player1.positionX + 1].visible_piece == ' ' && player1.nightstickNumber > 0) // usar luz
    {
        player1.usingNightStick = 1;
        player1.nightstickNumber -= 1;
    }
    else if (c == 'p')
    {
        pause_win(linhas, colunas);
    }
    else if (c == 27)
    {
        game.game_over = 1;
    }
}
void do_update_map_multi_player(char c, int colunas, Map mapa[][colunas], int linhas, Game game, Player player1, Player player2)
{
    switch (c)
    {
    case 'w':
        if (mapa[player1.positionY - 1][player1.positionX].visible_piece != '#' && mapa[player1.positionY - 1][player1.positionX].visible_piece != '!')
        {
            player1.last_direction_moved = 'w';
            player1.positionY--;
            player1.character = '^';
        }
        break;
    case 's':
        if (mapa[player1.positionY + 1][player1.positionX].visible_piece != '#' && mapa[player1.positionY + 1][player1.positionX].visible_piece != '!')
        {
            player1.last_direction_moved = 's';
            player1.positionY++;
            player1.character = 'v';
        }
        break;
    case 'a':
        if (mapa[player1.positionY][player1.positionX - 1].visible_piece != '#' && mapa[player1.positionY][player1.positionX - 1].visible_piece != '!')
        {
            player1.last_direction_moved = 'a';
            player1.positionX--;
            player1.character = '<';
        }
        break;
    case 'd':
        if (mapa[player1.positionY][player1.positionX + 1].visible_piece != '#' && mapa[player1.positionY][player1.positionX + 1].visible_piece != '!')
        {
            player1.last_direction_moved = 'd';
            player1.positionX++;
            player1.character = '>';
        }
        break;
    case '8':
        if (mapa[player2.positionY - 1][player2.positionX].visible_piece != '#' && mapa[player2.positionY - 1][player2.positionX].visible_piece != '!')
        {
            player2.last_direction_moved = '8';
            player2.positionY--;
            player2.character = '^';
        }
        break;
    case '2':
        if (mapa[player2.positionY + 1][player2.positionX].visible_piece != '#' && mapa[player2.positionY + 1][player2.positionX].visible_piece != '!')
        {
            player2.last_direction_moved = '2';
            player2.positionY++;
            player2.character = 'v';
        }
        break;
    case '4':
        if (mapa[player2.positionY][player2.positionX - 1].visible_piece != '#' && mapa[player2.positionY][player2.positionX - 1].visible_piece != '!')
        {
            player2.last_direction_moved = '4';
            player2.positionX--;
            player2.character = '<';
        }
        break;
    case '6':
        if (mapa[player2.positionY][player2.positionX + 1].visible_piece != '#' && mapa[player2.positionY][player2.positionX + 1].visible_piece != '!')
        {
            player2.last_direction_moved = '6';
            player2.positionX++;
            player2.character = '>';
        }
        break;
    case 'x':
        do_destroy_wall(player1.last_direction_moved, player1.positionY, player1.positionX, linhas, colunas, mapa);
        break;
    case 'e':
        if (mapa[player1.positionY][player1.positionX + 1].visible_piece == ' ' && player1.trapNumber > 0)
        {
            mapa[player1.positionY][player1.positionX + 1].visible_piece = '^';
            player1.trapNumber -= 1;
        }
        break;
    case '5':
        do_destroy_wall(player2.last_direction_moved, player2.positionY, player2.positionX, linhas, colunas, mapa);
        break;
    case '7':
        if (mapa[player2.positionY][player2.positionX + 1].visible_piece == ' ' && player2.trapNumber > 0)
        {
            mapa[player2.positionY][player2.positionX + 1].visible_piece = '^';
            player2.trapNumber -= 1;
        }
        break;
    case 'p':
        pause_win(linhas, colunas);
        break;
    case 27:
        game.game_over = 1;
        break;
    }
}

void do_add_score(int game_type, Flag flag, Game game, Player player1, Player player2)
{
    if (game_type == 1)
    {
        if (player1.positionX == flag.positionX && player1.positionY == flag.positionY)
        {
            player1.score++;    // incrementar 1 ao score
            game.is_flag_placed = 0; // dar reset a flag
        }
    }
    else
    {
        if (player1.positionX == flag.positionX && player1.positionY == flag.positionY)
        {
            player1.score++;    // incrementar 1 ao score
            game.is_flag_placed = 0; // dar reset a flag
        }
        if (player2.positionX == flag.positionX && player2.positionY == flag.positionY)
        {
            player2.score++;    // incrementar 1 ao score
            game.is_flag_placed = 0; // dar reset a flag
        }
    }
}

/*
funçao relativas às estruturas que tiram e acrescentam vida/amunição
*/
void do_structure_aplications_single_player(int colunas, Map mapa[][colunas], Player player1)
{
    if (mapa[player1.positionY][player1.positionX].visible_piece == '~')
        player1.hp -= 4; // -4 no lago
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '+' && player1.hp < 99)
        player1.hp += 2; // +2 na vida
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '-' && player1.ammo < 99)
        player1.ammo += 2; // +2 na muniçao
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '^')
        player1.hp -= 20; // -20 na armadilha
}
void do_structure_aplications_multi_player(int colunas, Map mapa[][colunas], Player player1, Player player2)
{
    if (mapa[player1.positionY][player1.positionX].visible_piece == '~')
        player1.hp -= 4;
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '+' && player1.hp < 99)
        player1.hp += 2;
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '-' && player1.ammo < 99)
        player1.ammo += 2;
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '^')
        player1.hp -= 20;
    if (mapa[player2.positionY][player2.positionX].visible_piece == '~')
        player2.hp -= 4;
    else if (mapa[player2.positionY][player2.positionX].visible_piece == '+' && player2.hp < 99)
        player2.hp += 2;
    else if (mapa[player2.positionY][player2.positionX].visible_piece == '-' && player2.ammo < 99)
        player2.ammo += 2;
    else if (mapa[player2.positionY][player2.positionX].visible_piece == '^')
        player2.hp -= 20;
}




