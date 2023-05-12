#include <ncurses.h>

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"


void shot_fired(int direction, int player, Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2)
{
    switch (direction)
    {
    case 1:
        if (player == 1)
        {
            bullet_player1.appearing = 1; // bala aparece
            bullet_player1.direction = 1; // para dar a direção da bala
            bullet_player1.number += 1;   // aumenta a contagem de balas no mapa
            player1.ammo--;
        }
        else
        {
            bullet_player2.appearing = 1;
            bullet_player2.direction = 1;
            bullet_player2.number += 1;
            player2.ammo--;
        }
        break;
    case 2:
        if (player == 1)
        {
            bullet_player1.appearing = 1;
            bullet_player1.direction = 2;
            bullet_player1.number += 1;
            player1.ammo--;
        }
        else
        {
            bullet_player2.appearing = 1;
            bullet_player2.direction = 2;
            bullet_player2.number += 1;
            player2.ammo--;
        }
        break;
    case 3:
        if (player == 1)
        {
            bullet_player1.appearing = 1;
            bullet_player1.direction = 3;
            bullet_player1.number += 1;
            player1.ammo--;
        }
        else
        {
            bullet_player2.appearing = 1;
            bullet_player2.direction = 3;
            bullet_player2.number += 1;
            player2.ammo--;
        }
        break;
    case 4:
        if (player == 1)
        {
            bullet_player1.appearing = 1;
            bullet_player1.direction = 4;
            bullet_player1.number += 1;
            player1.ammo--;
        }
        else
        {
            bullet_player2.appearing = 1;
            bullet_player2.direction = 4;
            bullet_player2.number += 1;
            player2.ammo--;
        }
        break;
    }
}

void bullet_show(int c, char player1_last_direction_moved, Player player1, Bullet bullet_player1, Player player2, Bullet bullet_player2)
{
    if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 'w' && bullet_player1.number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 'a' && bullet_player1.number == 0)
    {
        shot_fired(2, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 's' && bullet_player1.number == 0)
    {
        shot_fired(3, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 'd' && bullet_player1.number == 0)
    {
        shot_fired(4, 1, bullet_player1, bullet_player2, player1, player2);
    }
}
void bullet_show_multi_player(int c, Player player1, Player player2, Bullet bullet_player1, Bullet bullet_player2)
{
    if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1.last_direction_moved == 'w' && bullet_player1.number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1.last_direction_moved == 'a' && bullet_player1.number == 0)
    {
        shot_fired(2, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1.last_direction_moved == 's' && bullet_player1.number == 0)
    {
        shot_fired(3, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1.last_direction_moved == 'd' && bullet_player1.number == 0)
    {
        shot_fired(4, 1, bullet_player1, bullet_player2, player1, player2);
    }
    if (c == '0' && player2.gun == 2 && player2.ammo > 0 && player2.last_direction_moved == '8' && bullet_player2.number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 2, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == '0' && player2.gun == 2 && player2.ammo > 0 && player2.last_direction_moved == '4' && bullet_player2.number == 0)
    {
        shot_fired(2, 2, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == '0' && player2.gun == 2 && player2.ammo > 0 && player2.last_direction_moved == '2' && bullet_player2.number == 0)
    {
        shot_fired(3, 2, bullet_player1, bullet_player2, player1, player2);
    }
    else if (c == '0' && player2.gun == 2 && player2.ammo > 0 && player2.last_direction_moved == '6' && bullet_player2.number == 0)
    {
        shot_fired(4, 2, bullet_player1, bullet_player2, player1, player2);
    }
}

void bullet_position(Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2)
{
    if (bullet_player1.appearing == 0)
    {
        bullet_player1.positionX = player1.positionX;
        bullet_player1.positionY = player1.positionY;
    }
    if (bullet_player2.appearing == 0)
    {
        bullet_player2.positionX = player2.positionX;
        bullet_player2.positionY = player2.positionY;
    }
}

void bullet_collision(int colunas, Map mapa[][colunas], Bullet bullet_player1, Bullet bullet_player2)
{
    if (mapa[bullet_player1.positionY][bullet_player1.positionX].visible_piece == '#' || mapa[bullet_player1.positionY][bullet_player1.positionX].visible_piece == '!') // caso a posicão da bala seja igual à posicao de uma parede
    {
        bullet_player1.appearing = 0; // a bala desaparece
        bullet_player1.number = 0;    // Assim a contagem volta a zero
    }
    if (mapa[bullet_player2.positionY][bullet_player2.positionX].visible_piece == '#' || mapa[bullet_player2.positionY][bullet_player2.positionX].visible_piece == '!') // caso a posicão da bala seja igual à posicao de uma parede
    {
        bullet_player2.appearing = 0; // a bala desaparece
        bullet_player2.number = 0;    // Assim a contagem volta a zero
    }
}

void create_bullet(Bullet bullet_player1, Bullet bullet_player2)
{
    if (bullet_player1.number == 1 && bullet_player1.appearing == 1)
    {
        switch (bullet_player1.direction)
        {
        case 1:
            mvaddch(bullet_player1.positionY - 1, bullet_player1.positionX, '*');
            bullet_player1.positionY -= 1;
            break;
        case 2:
            mvaddch(bullet_player1.positionY, bullet_player1.positionX - 1, '*');
            bullet_player1.positionX -= 1;
            break;
        case 3:
            mvaddch(bullet_player1.positionY + 1, bullet_player1.positionX, '*');
            bullet_player1.positionY += 1;
            break;
        case 4:
            mvaddch(bullet_player1.positionY, bullet_player1.positionX + 1, '*');
            bullet_player1.positionX += 1;
            break;
        }
    }
    if (bullet_player2.number == 1 && bullet_player2.appearing == 1)
    {
        switch (bullet_player2.direction)
        {
        case 1:
            mvaddch(bullet_player2.positionY - 1, bullet_player2.positionX, 'x');
            bullet_player2.positionY -= 1;
            break;
        case 2:
            mvaddch(bullet_player2.positionY, bullet_player2.positionX - 1, 'x');
            bullet_player2.positionX -= 1;
            break;
        case 3:
            mvaddch(bullet_player2.positionY + 1, bullet_player2.positionX, 'x');
            bullet_player2.positionY += 1;
            break;
        case 4:
            mvaddch(bullet_player2.positionY, bullet_player2.positionX + 1, 'x');
            bullet_player2.positionX += 1;
            break;
        }
    }
}
void bullet_hit_mobs(int linhas, int colunas, Map mapa[][colunas], Bullet bullet_player1, Mob *mobs, int mob_positionX, int mob_positionY)
{
    for (int i = 0; i < 4; i++)
    {
        if (bullet_player1.positionX == mobs[i].positionX && bullet_player1.positionY == mobs[i].positionY)
        {
            bullet_player1.appearing = 0; // a bala desaparece
            bullet_player1.number = 0;    // Assim a contagem volta a zero
            mobs[i].hp -= 50;
            if (mobs[i].hp <= 0)
            {
                //meter a update mobs
                mobs[i].baseHp *= 1.05; // increase 5%
                mobs[i].hp = mobs[i].baseHp;
                mob_position(mobs[i].id, linhas, colunas, mapa, mob_positionX, mob_positionY);
                mobs[i].positionX = mob_positionX;
                mobs[i].positionY = mob_positionY;
            }
        }
    }
}

void do_guns_aplications(char c, char player1_last_direction_moved, int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2, int mob_positionX, int mob_positionY)
{
    //change_player_weapon(c);
    bullet_position(bullet_player1, bullet_player2, player1, player2);
    bullet_show(c, player1_last_direction_moved, player1, bullet_player1, player2, bullet_player2);
    create_bullet(bullet_player1, bullet_player2);
    bullet_collision(colunas, mapa, bullet_player1, bullet_player2);
    do_player_punch(c, linhas, colunas, mapa, player1, mobs);
    bullet_hit_mobs(linhas, colunas, mapa, bullet_player1, mobs, mob_positionX, mob_positionY);
}
void do_guns_aplications_multi_player(char c, int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Bullet bullet_player1, Bullet bullet_player2, Player player1, Player player2)
{
    //change_player_weapon(c);
    bullet_position(bullet_player1, bullet_player2, player1, player2);
    bullet_show_multi_player(c, player1, player2, bullet_player1, bullet_player2);
    create_bullet(bullet_player1, bullet_player2);
    bullet_collision(colunas, mapa, bullet_player1, bullet_player2);
    do_player_punch(c, linhas, colunas, mapa, player1, mobs);
}
