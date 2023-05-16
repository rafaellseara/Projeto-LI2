#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "Menu.h"

// fiz o player, o map, o guns, o mobs, o game, o menu

// CONTINUA A DAR ERROS ARANDOABDBASLKDNASJDNLASKND+ASDJASNLDKAS

// menu funciona bem mas nao começa o jogo
// wtf is goin on

int main()
{
    int linhas, colunas; // para definir o tamanho do mapa
    Mob mobs[4];
    Game game = {0, 'j', 0, 0, 30};
    Flag flag = {0, 0, 0, 0};
    Bullet bullet_player1 = {0, 0, 0, 0, 0};
    Bullet bullet_player2 = {0, 0, 0, 0, 0};
    Player player1 = {1, 2, 100, 10, 10, 100, 3, 5, 0, 0, 0, 0, '@', 'w', 0};
    Player player2 = {2, 2, 100, 20, 20, 100, 3, 5, 0, 0, 0, 0, '@', '8', 0};

    srand(time(NULL)); // funçao random com a seed do tempo para randomizar ainda mais

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
    init_color(16, 21, 546, 994);  // Azul claro
    init_color(17, 198, 50, 0);    // Castanho
    init_color(18, 596, 0, 0);     // Castanho claro
    init_color(19, 994,994,994);   // nao é bem para usar porque é preto
    init_color(20, 994, 994, 0);   // Amarelo
    init_color(21, 994, 774, 0);   // Amarelo Torrado
    init_color(22, 994, 0, 0);     // Vermelho vivo

    init_color(23, 101, 546, 994); // azul mais escuro dos 3
    init_color(24, 596, 795, 994); // azul medio
    init_color(25, 897, 943, 994); // azul claro
    init_pair(1, 88, 88);  // paredes
    init_pair(2, 16, 16);  // lagos
    init_pair(3, 13, 13);  // escuro
    init_pair(4, 88, 13);  // score etc
    init_pair(5, 2, 14);   // jogador1
    init_pair(6, 14, 2);   // jogador2
    init_pair(7, 23, 19);           // par de cores para a borda do menu com azul médio
    init_pair(8, 19, 24);           // AZUL claro FUNDO E letras brancas
    init_pair(9, 19, 25);           // AZUL muito CLARO FUNDO E BORDA AZUL claro
    init_pair(10, 21, 20); // flag
    init_pair(11, 22, 22); // mobs
    init_pair(12, 17, 18); // ammo
    init_pair(13, 18, 17); // vida

    menu(linhas, colunas, mapa, mobs, &game, &flag, &bullet_player1, &bullet_player2, &player1, &player2);

    clear(); // faz clear no terminal

    endwin();

    return 0;
}