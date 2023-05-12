#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"
#include "Game.h"
#include "Menu.h"

/*
    Criar uma janela de menu
        Player X ganhou o jogo, o Player Y vai ter de pagar o jantar
    Falta modo desafio enviar score para scoreboard certo
    Criar janela items?
    Modular o projeto
    Atualizar git direitinho
    Som
    Manual de instruçoes
    Mobs
    Cores bonitas
    Fazer um make file
*/

/*
// tem de se ver
int direction = 0;
int top_left_corner_X = 0;
int top_left_corner_Y = 0;
// tem de se ver
void moveInSquare(int x, int y, int *currentX, int *currentY, int *direction)
{
    if (*direction == 0)
    { // se estiver indo para a direita
        if (*currentX < x + 4)
        {
            *currentX += 1; // move para a direita
        }
        else
        {
            *direction = 1; // muda de direção
        }
    }
    else if (*direction == 1)
    { // se estiver indo para baixo
        if (*currentY < y + 4)
        {
            *currentY += 1; // move para baixo
        }
        else
        {
            *direction = 2; // muda de direção
        }
    }
    else if (*direction == 2)
    { // se estiver indo para a esquerda
        if (*currentX > x)
        {
            *currentX -= 1; // move para a esquerda
        }
        else
        {
            *direction = 3; // muda de direção
        }
    }
    else if (*direction == 3)
    { // se estiver indo para cima
        if (*currentY > y)
        {
            *currentY -= 1; // move para cima
        }
        else
        {
            *direction = 0; // muda de direção
        }
    }
}




esta funçao troca as armas do jogadores -- VERIFICAR TECLAS

void change_player_weapon(char c)
{
    // Se a gun no struct do jogador estiver 1->Punho 2->Pistola
    // Para Trocar Armas
    if (c == '1') // Trocar para soco
    {
        player1.gun = 1;
    }
    else if (c == '2') // Troca para pistola
    {
        player1.gun = 2;
    }
}
*/

/*
Função main: esta é a função que irá tratar de toda a composição do jogo, desde o input do utilizador até ao detalhe mais pequeno
*/
int main()
{
    int linhas, colunas; // para definir o tamanho do mapa
    srand(time(NULL));   // funçao random com a seed do tempo para randomizar ainda mais

    initscr(); // iniciando o ecrã
    refresh();

    // para iniciar cores
    start_color();

    keypad(stdscr, true); // ativa as keypads
    noecho();             // nao aparece input do utilizador
    curs_set(0);          // esconde o cursor

    getmaxyx(stdscr, linhas, colunas); // ve o maximo de linhas e colunas da janela do terminal

    Map mapa[linhas][colunas]; // iniciando um mapa

    // CORES PARA O MAPA (no init pair o segundo e para o caracter e o terceiro para o fundo)
    init_color(88, 500, 500, 499); // cinzento claro
    init_color(12, 0, 0, 255);     // Azul
    init_color(13, 0, 0, 140);     // Azul Escuro
    init_color(14, 500, 400, 0);   // Amarelo
    init_color(15, 0, 225, 200);   // Azul Claro
    init_pair(1, 88, 88);          // paredes
    init_pair(2, 12, 15);          // lagos
    init_pair(3, 13, 13);          // escuro
    init_pair(4, 88, 13);          // score etc
    init_pair(5, 2, 14);           // jogador1
    init_pair(6, 14, 2);           // jogador2

    menu(linhas, colunas, mapa);

    clear(); // faz clear no terminal

    endwin();

    return 0;
}