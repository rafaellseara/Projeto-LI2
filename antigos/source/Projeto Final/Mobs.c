#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"



void mob_position(int quadrante, int linhas, int colunas, Map mapa[][colunas], int mob_positionX, int mob_positionY)
{
    switch (quadrante)
    {
    case 1:
        do
        {
            mob_positionX = rand() % colunas / 2 + colunas / 2;
            mob_positionY = rand() % linhas / 2;
        } while (position_is_not_valid(colunas, mapa, mob_positionX, mob_positionY));
        break;
    case 2:
        do
        {
            mob_positionX = rand() % colunas / 2;
            mob_positionY = rand() % linhas / 2;
        } while (position_is_not_valid(colunas, mapa, mob_positionX, mob_positionY));
        break;
    case 3:
        do
        {
            mob_positionX = rand() % colunas / 2;
            mob_positionY = rand() % linhas / 2 + linhas / 2;
        } while (position_is_not_valid(colunas, mapa, mob_positionX, mob_positionY));
        break;
    case 4:
        do
        {
            mob_positionX = rand() % colunas / 2 + colunas / 2;
            mob_positionY = rand() % linhas / 2 + linhas / 2;
        } while (position_is_not_valid(colunas, mapa, mob_positionX, mob_positionY));
        break;
    }
}

void update_mob(int index, int linhas, int colunas, Map mapa[][colunas], int mob_positionX, int mob_positionY, Mob *mobs)
{
    mobs[index].baseHp *= 1.05; // increase 5%
    mobs[index].hp = mobs[index].baseHp;
    mob_position(mobs[index].id, linhas, colunas, mapa, mob_positionX, mob_positionY);
    mobs[index].positionX = mob_positionX;
    mobs[index].positionY = mob_positionY;
}


float calc_dist(int a, int b, int c, int d)
{
    float dist = 0;
    dist = sqrt(((a - b) ^ 2) + ((c - d) ^ 2));
    return dist;
}

void mob_view(Player player1, Mob *mobs)
{
    for (int i = 0; i < 4; i++)
    {

        for (int coluna = 0; coluna <= 20; coluna++)
        {
            for (int linha = 0; linha <= 10; linha++)
            {
                if ((player1.positionX == (mobs[i].positionX + coluna) && player1.positionY == (mobs[i].positionY + linha)) || (player1.positionX == (mobs[i].positionX - coluna) && player1.positionY == (mobs[i].positionY + linha)) || (player1.positionX == (mobs[i].positionX + coluna) && player1.positionY == (mobs[i].positionY - linha)) || (player1.positionX == (mobs[i].positionX - coluna) && player1.positionY == (mobs[i].positionY - linha)))
                    mobs[i].is_in_mob_view = 1;
            }
        }
    }
}

void mob_movement(int colunas, Map mapa[][colunas], Player player1, Mob *mobs)
{
    for (int i = 0; i < 4; i++)
    {

        float distanciaUmParaCima = calc_dist(mobs[i].positionY - 1, player1.positionY, mobs[i].positionX, player1.positionX);
        float distanciaUmParaBaixo = calc_dist(mobs[i].positionY + 1, player1.positionY, mobs[i].positionX, player1.positionX);
        float distanciaUmParaDireita = calc_dist(mobs[i].positionY, player1.positionY, mobs[i].positionX + 1, player1.positionX);
        float distanciaUmParaEsquerda = calc_dist(mobs[i].positionY, player1.positionY, mobs[i].positionX - 1, player1.positionX);

        if ((mobs[i].is_in_mob_view == 1) && (mobs[i].damaging_player == 0))
        {
            if (player1.positionX < mobs[i].positionX) // Se o Player tiver à esquerda do Mob
            {
                if (player1.positionY > mobs[i].positionY) // Se o Player tiver abaixo do mob
                {
                    // Ve qual compensa mais: Andar para a Esquerda ou para Baixo
                    if (distanciaUmParaEsquerda <= distanciaUmParaBaixo)
                    {
                        if (mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '!')
                            mobs[i].positionX -= 1; // Caso a esquerda nao  seja parede ele anda para a esquerda
                        else if (mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY += 1;
                    }
                    else
                    {
                        if (mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY += 1;
                        else if (mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '!')
                            mobs[i].positionX -= 1;
                    }
                }
                else if (player1.positionY < mobs[i].positionY) // Se o Player tiver acima do mob
                {
                    // Ve qual compensa mais: Andar para a Esquerda ou para Cima
                    if (distanciaUmParaEsquerda <= distanciaUmParaCima)
                    {
                        if (mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '!')
                            mobs[i].positionX -= 1;
                        else if (mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY -= 1;
                    }
                    else
                    {
                        if (mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY -= 1;
                        else if (mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '!')
                            mobs[i].positionX -= 1;
                    }
                }
                else // Se o Player Tiver na mesma linha do Mob
                {
                    if (mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '!')
                        mobs[i].positionX -= 1;
                }
            }
            else if (player1.positionX > mobs[i].positionX) // Se o Player tiver à direita do Mob
            {
                if (player1.positionY > mobs[i].positionY) // Se o Player tiver abaixo do mob
                {
                    // Ve qual compensa mais: Andar para a Direita ou para Baixo
                    if (distanciaUmParaDireita <= distanciaUmParaBaixo)
                    {
                        if (mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '!')
                            mobs[i].positionX += 1;
                        else if (mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY += 1;
                    }
                    else
                    {
                        if (mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY += 1;
                        else if (mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '!')
                            mobs[i].positionX += 1;
                    }
                }
                else if (player1.positionY < mobs[i].positionY) // Se o Player tiver acima do mob
                {
                    // Ve qual compensa mais: Andar para a Direita ou para Cima
                    if (distanciaUmParaDireita <= distanciaUmParaCima)
                    {
                        if (mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '!')
                            mobs[i].positionX += 1;
                        else if (mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY -= 1;
                    }
                    else
                    {
                        if (mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '!')
                            mobs[i].positionY -= 1;
                        else if (mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '!')
                            mobs[i].positionX += 1;
                    }
                }
                else // Se o Player Tiver na mesma linha do Mob
                {
                    if (mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '#' && mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '!')
                        mobs[i].positionX += 1;
                }
            }
            else // Se o Player estiver na mesma coluna do Player
            {
                if (player1.positionY < mobs[i].positionY)
                {
                    if (mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '!')
                        mobs[i].positionY -= 1;
                }
                else if (player1.positionY > mobs[i].positionY)
                {
                    if (mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '#' && mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '!')
                        mobs[i].positionY += 1;
                }
            }
            mobs[i].is_in_mob_view = 0;
            mobs[i].damaging_player = 0;
        }
    }
}

void mob_movement_far(int colunas, Map mapa[][colunas], Mob *mobs)
{
    for (int i = 0; i < 4; i++)
    {

        if ((mobs[i].is_in_mob_view == 0))
        {
            if (mobs[i].quadrado_down < 4)
            {
                if (mapa[mobs[i].positionY + 1][mobs[i].positionX].visible_piece != '#')
                {
                    mobs[i].positionY += 1;
                    mobs[i].quadrado_down++;
                }
                else
                    mobs[i].quadrado_down++;
            }
            else if (mobs[i].quadrado_right < 5)
            {
                if (mapa[mobs[i].positionY][mobs[i].positionX + 1].visible_piece != '#')
                {
                    mobs[i].positionX += 1;
                    mobs[i].quadrado_right++;
                }
                else
                    mobs[i].quadrado_right++;
            }
            else if (mobs[i].quadrado_up < 4)
            {
                if (mapa[mobs[i].positionY - 1][mobs[i].positionX].visible_piece != '#')
                {
                    mobs[i].positionY -= 1;
                    mobs[i].quadrado_up++;
                }
                else
                    mobs[i].quadrado_up++;
            }
            else if (mobs[i].quadrado_left < 5)
            {
                if (mapa[mobs[i].positionY][mobs[i].positionX - 1].visible_piece != '#')
                {
                    mobs[i].positionX -= 1;
                    mobs[i].quadrado_left++;
                }
                else
                    mobs[i].quadrado_left++;
            }
            else
            {
                mobs[i].quadrado_down = 0;
                mobs[i].quadrado_right = 0;
                mobs[i].quadrado_up = 0;
                mobs[i].quadrado_left = 0;
            }
        }
    }
}

void mob_attacks(Mob *mobs, Player player1)
{
    for (int i = 0; i < 4; i++)
    {

        if (mobs[i].damaging_player == 1)
        {
            player1.hp -= 5;
            mobs[i].damaging_player = 0;
        }
    }
}

void do_mob_apps(int colunas, Map mapa[][colunas], Player player1, Mob *mobs)
{
    mob_view(player1, mobs);
    close_to_player(player1, mobs);
    mob_movement_far(colunas, mapa, mobs);
    mob_movement(colunas, mapa, player1, mobs);
    mob_attacks(mobs, player1);
}


int position_is_not_valid(int colunas, Map mapa[][colunas], int mob_positionX, int mob_positionY)
{
    if (count_walls_5x5(colunas, mapa, mob_positionY, mob_positionX) > 0 || mapa[mob_positionY][mob_positionX].visible_piece != ' ')
        return 1;
    else
        return 0;
}

void initializeMobs(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, int mob_positionX, int mob_positionY)
{
    for (int i = 0; i < 4; i++)
    {
        mobs[i].id = i + 1;
        mobs[i].showing = 0;
        mobs[i].baseHp = 250;
        mobs[i].hp = 250;
        mobs[i].damaging_player = 0;
        mobs[i].is_in_mob_view = 0;
        mobs[i].quadrado_down = 0;
        mobs[i].quadrado_left = 0;
        mobs[i].quadrado_right = 0;
        mobs[i].quadrado_up = 0;
        mob_position(i + 1, linhas, colunas, mapa, mob_positionX, mob_positionY);
        mobs[i].positionX = mob_positionX;
        mobs[i].positionY = mob_positionY;
    }
}

void printMobs(Mob *mobs)
{
    for (int i = 0; i < 4; i++)
    {
        mvaddch(mobs[i].positionY, mobs[i].positionX, '1');
    }
}
