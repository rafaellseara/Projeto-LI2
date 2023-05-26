#include <ncurses.h>

#include "Menu.h"
#include "Guns.h"

/*
esta funçao troca as armas do jogadores
*/
void change_player_weapon(char c, Player *player1, Bullet *bullet_player1)
{
    // Se a gun no struct do jogador estiver 1->Punho 2->Pistola
    // Para Trocar Armas
    if (c == '1') // Trocar para soco
    {
        player1->gun = 1;
        bullet_player1->appearing = 0;
        bullet_player1->number = 0;
    }
    else if (c == '2') // Troca para pistola
    {
        player1->gun = 2;
    }
    else if (c == '3' && player1->gun_three_on == 1) // Troca para teleguiada
    {
        player1->gun = 3;
    }
}

void shot_fired(int direction, int player, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
{
    switch (direction)
    {
    case 1:
        if (player == 1)
        {
            if (player1->gun == 2)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 1; // para dar a direção da bala
                bullet_player1->number += 1;   // aumenta a contagem de balas no mapa
                player1->ammo--;
            }
            else if (player1->gun == 3)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 1; // para dar a direção da bala
                player1->ammo--;
            }
        }
        else
        {
            if (player2->gun == 2)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 1; // para dar a direção da bala
                bullet_player2->number += 1;   // aumenta a contagem de balas no mapa
                player2->ammo--;
            }
            else if (player2->gun == 3)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 1; // para dar a direção da bala
                player2->ammo--;
            }
        }
        break;
    case 2:
        if (player == 1)
        {
            if (player1->gun == 2)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 2; // para dar a direção da bala
                bullet_player1->number += 1;   // aumenta a contagem de balas no mapa
                player1->ammo--;
            }
            else if (player1->gun == 3)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 2; // para dar a direção da bala
                player1->ammo--;
            }
        }
        else
        {
            if (player2->gun == 2)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 2; // para dar a direção da bala
                bullet_player2->number += 1;   // aumenta a contagem de balas no mapa
                player2->ammo--;
            }
            else if (player2->gun == 3)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 2; // para dar a direção da bala
                player2->ammo--;
            }
        }
        break;
    case 3:
        if (player == 1)
        {
            if (player1->gun == 2)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 3; // para dar a direção da bala
                bullet_player1->number += 1;   // aumenta a contagem de balas no mapa
                player1->ammo--;
            }
            else if (player1->gun == 3)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 3; // para dar a direção da bala
                player1->ammo--;
            }
        }
        else
        {
            if (player2->gun == 2)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 3; // para dar a direção da bala
                bullet_player2->number += 1;   // aumenta a contagem de balas no mapa
                player2->ammo--;
            }
            else if (player2->gun == 3)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 3; // para dar a direção da bala
                player2->ammo--;
            }
        }
        break;
    case 4:
        if (player == 1)
        {
            if (player1->gun == 2)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 4; // para dar a direção da bala
                bullet_player1->number += 1;   // aumenta a contagem de balas no mapa
                player1->ammo--;
            }
            else if (player1->gun == 3)
            {
                bullet_player1->appearing = 1; // bala aparece
                bullet_player1->direction = 4; // para dar a direção da bala
                player1->ammo--;
            }
        }
        else
        {
            if (player2->gun == 2)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 4; // para dar a direção da bala
                bullet_player2->number += 1;   // aumenta a contagem de balas no mapa
                player2->ammo--;
            }
            else if (player2->gun == 3)
            {
                bullet_player2->appearing = 1; // bala aparece
                bullet_player2->direction = 4; // para dar a direção da bala
                player2->ammo--;
            }
        }
        break;
    }
}

void bullet_show(Game *game, Player *player1, Bullet *bullet_player1, Player *player2, Bullet *bullet_player2)
{
    if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 'w' && bullet_player1->number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 3 && player1->ammo > 0 && player1->last_direction_moved == 'w') // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 'a' && bullet_player1->number == 0)
    {
        shot_fired(2, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 3 && player1->ammo > 0 && player1->last_direction_moved == 'a')
    {
        shot_fired(2, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 's' && bullet_player1->number == 0)
    {
        shot_fired(3, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 3 && player1->ammo > 0 && player1->last_direction_moved == 's')
    {
        shot_fired(3, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 'd' && bullet_player1->number == 0)
    {
        shot_fired(4, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 3 && player1->ammo > 0 && player1->last_direction_moved == 'd')
    {
        shot_fired(4, 1, bullet_player1, bullet_player2, player1, player2);
    }
}
void bullet_show_multi_player(Game *game, Player *player1, Player *player2, Bullet *bullet_player1, Bullet *bullet_player2)
{
    if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 'w' && bullet_player1->number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 'a' && bullet_player1->number == 0)
    {
        shot_fired(2, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 's' && bullet_player1->number == 0)
    {
        shot_fired(3, 1, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == ' ' && player1->gun == 2 && player1->ammo > 0 && player1->last_direction_moved == 'd' && bullet_player1->number == 0)
    {
        shot_fired(4, 1, bullet_player1, bullet_player2, player1, player2);
    }
    if (game->key_pressed == '0' && player2->gun == 2 && player2->ammo > 0 && player2->last_direction_moved == '8' && bullet_player2->number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        shot_fired(1, 2, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == '0' && player2->gun == 2 && player2->ammo > 0 && player2->last_direction_moved == '4' && bullet_player2->number == 0)
    {
        shot_fired(2, 2, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == '0' && player2->gun == 2 && player2->ammo > 0 && player2->last_direction_moved == '2' && bullet_player2->number == 0)
    {
        shot_fired(3, 2, bullet_player1, bullet_player2, player1, player2);
    }
    else if (game->key_pressed == '0' && player2->gun == 2 && player2->ammo > 0 && player2->last_direction_moved == '6' && bullet_player2->number == 0)
    {
        shot_fired(4, 2, bullet_player1, bullet_player2, player1, player2);
    }
}

void bullet_position(Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
{
    if (bullet_player1->appearing == 0)
    {
        bullet_player1->positionX = player1->positionX;
        bullet_player1->positionY = player1->positionY;
    }
    if (bullet_player2->appearing == 0)
    {
        bullet_player2->positionX = player2->positionX;
        bullet_player2->positionY = player2->positionY;
    }
}

void bullet_collision(int colunas, Map mapa[][colunas], Bullet *bullet_player1, Bullet *bullet_player2)
{
    if (mapa[bullet_player1->positionY][bullet_player1->positionX].visible_piece == '#' || mapa[bullet_player1->positionY][bullet_player1->positionX].visible_piece == '!') // caso a posicão da bala seja igual à posicao de uma parede
    {
        bullet_player1->appearing = 0; // a bala desaparece
        bullet_player1->number = 0;    // Assim a contagem volta a zero
    }
    if (mapa[bullet_player2->positionY][bullet_player2->positionX].visible_piece == '#' || mapa[bullet_player2->positionY][bullet_player2->positionX].visible_piece == '!') // caso a posicão da bala seja igual à posicao de uma parede
    {
        bullet_player2->appearing = 0; // a bala desaparece
        bullet_player2->number = 0;    // Assim a contagem volta a zero
    }
}

void create_bullet(Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
{
    if (player1->gun == 2)
    {
        if (bullet_player1->number == 1 && bullet_player1->appearing == 1)
        {
            switch (bullet_player1->direction)
            {
            case 1:
                mvaddch(bullet_player1->positionY - 1, bullet_player1->positionX, '*');
                bullet_player1->positionY -= 1;
                break;
            case 2:
                mvaddch(bullet_player1->positionY, bullet_player1->positionX - 1, '*');
                bullet_player1->positionX -= 1;
                break;
            case 3:
                mvaddch(bullet_player1->positionY + 1, bullet_player1->positionX, '*');
                bullet_player1->positionY += 1;
                break;
            case 4:
                mvaddch(bullet_player1->positionY, bullet_player1->positionX + 1, '*');
                bullet_player1->positionX += 1;
                break;
            }
        }
    }
    else if (player1->gun == 3)
    {
        if (bullet_player1->appearing == 1)
        {
            switch (bullet_player1->direction)
            {
            case 1:
                mvaddch(bullet_player1->positionY - 1, bullet_player1->positionX, '*');
                bullet_player1->positionY -= 1;
                break;
            case 2:
                mvaddch(bullet_player1->positionY, bullet_player1->positionX - 1, '*');
                bullet_player1->positionX -= 1;
                break;
            case 3:
                mvaddch(bullet_player1->positionY + 1, bullet_player1->positionX, '*');
                bullet_player1->positionY += 1;
                break;
            case 4:
                mvaddch(bullet_player1->positionY, bullet_player1->positionX + 1, '*');
                bullet_player1->positionX += 1;
                break;
            }
        }
    }

    if (player2->gun == 2)
    {
        if (bullet_player2->number == 1 && bullet_player2->appearing == 1)
        {
            switch (bullet_player2->direction)
            {
            case 1:
                mvaddch(bullet_player2->positionY - 1, bullet_player2->positionX, 'x');
                bullet_player2->positionY -= 1;
                break;
            case 2:
                mvaddch(bullet_player2->positionY, bullet_player2->positionX - 1, 'x');
                bullet_player2->positionX -= 1;
                break;
            case 3:
                mvaddch(bullet_player2->positionY + 1, bullet_player2->positionX, 'x');
                bullet_player2->positionY += 1;
                break;
            case 4:
                mvaddch(bullet_player2->positionY, bullet_player2->positionX + 1, 'x');
                bullet_player2->positionX += 1;
                break;
            }
        }
    }
    else if (player2->gun == 3)
    {
        if (bullet_player2->appearing == 1)
        {
            switch (bullet_player2->direction)
            {
            case 1:
                mvaddch(bullet_player2->positionY - 1, bullet_player2->positionX, 'x');
                bullet_player2->positionY -= 1;
                break;
            case 2:
                mvaddch(bullet_player2->positionY, bullet_player2->positionX - 1, 'x');
                bullet_player2->positionX -= 1;
                break;
            case 3:
                mvaddch(bullet_player2->positionY + 1, bullet_player2->positionX, 'x');
                bullet_player2->positionY += 1;
                break;
            case 4:
                mvaddch(bullet_player2->positionY, bullet_player2->positionX + 1, 'x');
                bullet_player2->positionX += 1;
                break;
            }
        }
    }
}

int bullet_in_Y_mob_range(Bullet *bullet_player1, Mob *mobs, int i)
{
    if (bullet_player1->positionX == mobs[i].positionX && (bullet_player1->positionY == mobs[i].positionY || bullet_player1->positionY == mobs[i].positionY - 1 || bullet_player1->positionY == mobs[i].positionY + 1))
        return 1;
    else
        return 0;
}

int bullet_in_X_mob_range(Bullet *bullet_player1, Mob *mobs, int i)
{
    if (bullet_player1->positionY == mobs[i].positionY && (bullet_player1->positionX == mobs[i].positionX || bullet_player1->positionX == mobs[i].positionX - 1 || bullet_player1->positionX == mobs[i].positionX + 1))
        return 1;
    else
        return 0;
}

int bullet_in_vertical(Bullet *bullet_player1)
{
    return (bullet_player1->direction == 1 || bullet_player1->direction == 3 ? 1 : 0);
}

int bullet_in_horizontal(Bullet *bullet_player1)
{
    return (bullet_player1->direction == 2 || bullet_player1->direction == 4 ? 1 : 0);
}

void bullet_disappears(Bullet *bullet_player1)
{
    bullet_player1->appearing = 0; // a bala desaparece
    bullet_player1->number = 0;    // Assim a contagem volta a zero
}

void update_player_score_money(Player *player1)
{
    player1->score++;
    player1->money += 10;
}

int mob_is_dead(Mob *mobs, int i)
{
    return (mobs[i].hp <= 0 ? 1 : 0);
}

void bullet_hit_mobs(int linhas, int colunas, Map mapa[][colunas], Bullet *bullet_player1, Mob *mobs, Player *player1)
{
    for (int i = 0; i < 4; i++)
    {
        if (bullet_in_vertical(bullet_player1))
        {
            if (bullet_in_Y_mob_range(bullet_player1, mobs, i))
            {
                bullet_disappears(bullet_player1);
                mobs[i].hp -= 250;
                if (mob_is_dead(mobs, i));
                {
                    update_player_score_money(player1);
                    update_mob(i, linhas, colunas, mapa, mobs);
                }
            }
        }
        else if (bullet_in_horizontal(bullet_player1))
        {
            if (bullet_in_X_mob_range(bullet_player1, mobs, i))
            {
                bullet_disappears(bullet_player1);
                mobs[i].hp -= 250;
                if (mob_is_dead(mobs, i))
                {
                    update_player_score_money(player1);
                    update_mob(i, linhas, colunas, mapa, mobs);
                }
            }
        }
    }
}

int bullet_is_showing(Bullet *bullet_player1)
{
    return (bullet_player1->appearing == 1 ? 1 : 0);
}

int equal_bullet_to_player_position(Bullet *bullet, Player *player)
{
    return (bullet->positionX == player->positionX && bullet->positionY == player->positionY ? 1 : 0);
}

void bullet_hit_player(Player *player1, Player *player2, Bullet *bullet_player1, Bullet *bullet_player2)
{
    if (bullet_is_showing(bullet_player1) && equal_bullet_to_player_position(bullet_player1, player2))
    {
        bullet_disappears(bullet_player1);
        player2->hp -= 25;
    }
    if (bullet_is_showing(bullet_player1) && equal_bullet_to_player_position(bullet_player2, player1))
    {
        bullet_disappears(bullet_player2);
        player1->hp -= 25;
    }
}

void do_guns_aplications(int linhas, int colunas, Map mapa[][colunas], Game *game, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
{
    change_player_weapon(game->key_pressed, player1, bullet_player1);
    bullet_position(bullet_player1, bullet_player2, player1, player2);
    bullet_show(game, player1, bullet_player1, player2, bullet_player2);
    create_bullet(bullet_player1, bullet_player2, player1, player2);
    bullet_collision(colunas, mapa, bullet_player1, bullet_player2);
    do_player_punch(game, linhas, colunas, mapa, player1, mobs);
    bullet_hit_mobs(linhas, colunas, mapa, bullet_player1, mobs, player1);
}
void do_guns_aplications_multi_player(int linhas, int colunas, Map mapa[][colunas], Game *game, Mob *mobs, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
{
    bullet_position(bullet_player1, bullet_player2, player1, player2);
    bullet_show_multi_player(game, player1, player2, bullet_player1, bullet_player2);
    create_bullet(bullet_player1, bullet_player2, player1, player2);
    bullet_collision(colunas, mapa, bullet_player1, bullet_player2);
    do_player_punch(game, linhas, colunas, mapa, player1, mobs);
    bullet_hit_player(player1, player2, bullet_player1, bullet_player2);
}
