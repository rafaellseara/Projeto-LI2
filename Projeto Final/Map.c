#include <stdlib.h>
#include <ncurses.h>

#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Guns.h"
#include "Mobs.h"



void do_create_map(int linhas, int colunas, Map mapa[][colunas], Flag flag, Game game)
{
    // criaçao do mapa

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            // caso esteja nas bordas é parede
            if (i == 0 || i == 1 || i == linhas - 1 || i == linhas - 2 || j == 0 || j == 1 || j == colunas - 1 || j == colunas - 2)
                mapa[i][j].visible_piece = '#';
            else
            {
                // usamos o %4 porque era o que ficava mais visualmente atrativo para o que queriamos
                if (rand() % 4 == 0 || rand() % 4 == 1)
                    mapa[i][j].visible_piece = '#';
                else
                    mapa[i][j].visible_piece = ' ';
            }
        }
    }
    // ciclo para implementar randomizaçao do mapa
    for (int i = 0; i < 10; i++)
    {
        do_concat_walls(linhas, colunas, mapa);
    }
    do_add_life(linhas, colunas, mapa);
    do_add_lake(linhas, colunas, mapa);
    do_add_ammo(linhas, colunas, mapa);
    do_add_lighthouse(linhas, colunas, mapa);
    do_insert_flag(linhas, colunas, mapa, flag, game);
}

void do_print_map(int linhas, int colunas, Map mapa[][colunas], int n)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            // adicionar a parede e atribui a cor à parede
            if ((mapa[i][j].visible_piece) == '#')
            {
                attron(COLOR_PAIR(n));
                mvaddch(i, j, mapa[i][j].visible_piece);
                attroff(COLOR_PAIR(n));
            }
            else if (mapa[i][j].visible_piece == '~')
            {
                attron(COLOR_PAIR(2));
                mvaddch(i, j, mapa[i][j].visible_piece);
                attroff(COLOR_PAIR(2));
            }
            else
            {
                mvaddch(i, j, mapa[i][j].visible_piece);
            }
        }
    }
}

void print_footer_single_player(Player player1)
{
    attron(COLOR_PAIR(4));
    mvprintw(0, 10, "Player1:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d", player1.hp, player1.score, player1.gun, player1.trapNumber, player1.ammo);
    attroff(COLOR_PAIR(4));
}
void print_footer_multi_player(int linhas, int colunas, Player player1, Player player2)
{
    attron(COLOR_PAIR(4));
    mvprintw(0, 10, "Player1:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d", player1.hp, player1.score, player1.gun, player1.trapNumber, player1.ammo);
    mvprintw(linhas - 1, colunas / 3 + colunas / 3 - 10, "Player2:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d", player2.hp, player2.score, player2.gun, player2.trapNumber, player2.ammo);
    attroff(COLOR_PAIR(4));
}
void print_footer_challenge(Player player1)
{
    attron(COLOR_PAIR(4));
    mvprintw(0, 10, "Player1:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d  Nightsticks: %d", player1.hp, player1.score, player1.gun, player1.trapNumber, player1.ammo, player1.nightstickNumber);
    attroff(COLOR_PAIR(4));
}


void do_destroy_wall(char last_direction_moved, int y, int x, int linhas, int colunas, Map mapa[][colunas])
{
    switch (last_direction_moved)
    {
    case 'w':
    case '8':
        if (mapa[y - 1][x].visible_piece == '#' && (y - 1) != 1)
            mapa[y - 1][x].visible_piece = ' ';
        break;
    case 's':
    case '2':
        if (mapa[y + 1][x].visible_piece == '#' && (y + 1) != (linhas - 1))
            mapa[y + 1][x].visible_piece = ' ';
        break;
    case 'a':
    case '4':
        if (mapa[y][x - 1].visible_piece == '#' && (x - 1) != 1)
            mapa[y][x - 1].visible_piece = ' ';
        break;
    case 'd':
    case '6':
        if (mapa[y][x + 1].visible_piece == '#' && (x + 1) != (colunas - 1))
            mapa[y][x + 1].visible_piece = ' ';
    default:
        break;
    }
    // a terceira condiçao serve para nao apagar as bordas
}

void do_concat_walls(int linhas, int colunas, Map mapa[][colunas])
{
    // usamos mapa auxiliar pois se alterassemos imediatamente no mapa ia dar asneira pois nao funcionava da maneira que queremos
    char mapa_auxiliar[linhas][colunas];
    for (int i = 2; i < linhas - 2; i++)
    { // começa a 2 e acaba a -2 porque as bordas sao sempre paredes
        for (int j = 2; j < colunas - 2; j++)
        {
            if (count_walls_3x3(colunas, mapa, i, j) >= 5) // caso exista 5 paredes à volta da casa que estamos, ela vira parede
            {
                mapa_auxiliar[i][j] = '#';
            }
            else
            {
                mapa_auxiliar[i][j] = ' ';
            }
        }
    }
    // copia o mapa auxiliar para o mapa atual
    for (int i = 2; i < linhas - 2; i++)
    {
        for (int j = 2; j < colunas - 2; j++)
        {
            mapa[i][j].visible_piece = mapa_auxiliar[i][j];
        }
    }
}


void createlight(int posy, int posx, int colunas, int linhas, int z, Player player1)
{
    int paraolado = 0;
    int paracima = 0;
    int isLight = 0;
    int row = 0;
    int column = 0;
    /*
    Esta função testa cada quadrado do mapa vendo se pertence ou não há região onde é suposto haver luz
    */
    attron(COLOR_PAIR(z));
    if (player1.hp <= 100 && player1.hp > 80 && player1.usingNightStick == 1) // Caso o Player tenha entre 80 e 100 de vida e NightStick ligado
    {
        for (row = 0; row <= linhas - 1; row++) // Contador que inicia na primeira linha, testa tudo nessa linha, e depois passa para a proxima
        {
            column = 0;                   // para voltar ao primeiro quadrado da linha
            while (column <= colunas - 1) // Contador para ir avançando a coluna
            // a combinacao destes dois contadores faz com que se teste apenas um quadrado(ex: estamos na linha 0 e coluna 0 teste o primeiro quadrado de todos)
            {
                while (paraolado <= 14) // "tamanho da luz" na horizontal que queremos dar, neste caso queremos que apareçam 14 "quadrados" para os lados
                {
                    while (paracima <= 8) // "tamanho da luz" na vertical que queremos dar, neste caso queremos que apareçam 8 "quadrados" para cima
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        /*
                        Cada condição deste if equivale a um "quadrante" e testa se o quadrado que está a ser testado(segundo os contadores acima) não pertence à região que é suposto haver luz,utilizando um sistema de ver quadrados semelhante ao acima
                        Ou seja, por exemplo :
                        (!((row == (posy + paracima)) && (column == (posx + paraolado))))
                        Esta condição seleciona todos os quadrados dentro da área de 8 blocos para a direita e 8 blocos para cima e vai testando se o quadrado que está a ser testado não pertence a essa área
                        */
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1; // Caso o quadrado pertença à área delimitada pelas condições então temos de atriibuir-lhe o valor 1 a isLight para que este não conte como um quadrado onde é suposto colocar '?'
                            paracima++;  // Serve unicamente para finalizar o contador/teste
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0) // Caso não seja um quadrado onde é suposto haver luz nesse quadrado vai passar a existir um '?'
                {
                    mvaddch(row, column, '?');
                }
                // resetar variáveis para testar para o próximo quadrado
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 80 && player1.hp > 60 && player1.usingNightStick == 1)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 13)
                {
                    while (paracima <= 7)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 60 && player1.hp > 40 && player1.usingNightStick == 1)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 12)
                {
                    while (paracima <= 7)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 40 && player1.hp > 20 && player1.usingNightStick == 1)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 11)
                {
                    while (paracima <= 7)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 20 && player1.usingNightStick == 1)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 10)
                {
                    while (paracima <= 6)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 100 && player1.hp > 80 && player1.usingNightStick == 0)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 8)
                {
                    while (paracima <= 5)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 80 && player1.hp > 60 && player1.usingNightStick == 0)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 7)
                {
                    while (paracima <= 4)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 60 && player1.hp > 40 && player1.usingNightStick == 0)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 6)
                {
                    while (paracima <= 4)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 40 && player1.hp > 20 && player1.usingNightStick == 0)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 5)
                {
                    while (paracima <= 4)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    else if (player1.hp <= 20 && player1.usingNightStick == 0)
    {
        for (row = 0; row <= linhas - 1; row++)
        {
            column = 0;
            while (column <= colunas - 1)
            {
                while (paraolado <= 4)
                {
                    while (paracima <= 3)
                    {
                        if ((!((row == (posy + paracima)) && (column == (posx + paraolado)))) && (!((row == (posy + paracima)) && (column == (posx - paraolado)))) && (!((row == (posy - paracima)) && (column == (posx + paraolado)))) && (!((row == (posy - paracima)) && (column == (posx - paraolado)))))
                        {
                            paracima++;
                        }
                        else
                        {
                            isLight = 1;
                            paracima++;
                        }
                    }
                    paracima = 0;
                    paraolado++;
                }
                if (isLight == 0)
                {
                    mvaddch(row, column, '?');
                }
                paraolado = 0;
                paracima = 0;
                isLight = 0;
                column++;
            }
        }
    }
    attroff(COLOR_PAIR(z));
}

void do_add_lake(int linhas, int colunas, Map mapa[][colunas])
{
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;
    for (int i = linhas / 3; i < linhas - 2; i++)
    { // começa a 1/3 do mapa para nao ficar diretamente em cima mas mais no centro
        for (int j = colunas / 3; j < colunas - 2; j++)
        {
            if (count_walls_4x8(colunas, mapa, i, j) == 0 && count_walls_4x8(colunas, mapa, (i - 1), j) == 0 && count_walls_4x8(colunas, mapa, (i + 1), j) == 0)
            {
                for (index_linha = -2; index_linha < 2; index_linha++) // começa a -1 pois queremos o quadrado imediatamente acima e abaixo
                // queremos que vá apenas até ao indice 1 para ser o quadrado abaixo e ao lado
                {
                    for (index_coluna = -2; index_coluna < 6; index_coluna++)
                    {
                        mapa[i + index_linha][j + index_coluna].visible_piece = '~';
                    }
                }
                // terminar os ciclos pois senao enche o mapa de lagos
                i = linhas - 2;
                j = colunas - 2;
            }
        }
    }
}

void do_add_life(int linhas, int colunas, Map mapa[][colunas])
{
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;
    for (int i = linhas / 4; i < linhas - 2; i++)
    { // começa a 1/4 do mapa para nao ficar diretamente em cima mas mais no centro
        for (int j = colunas / 4; j < colunas - 2; j++)
        {
            if (count_walls_3x3(colunas, mapa, i, j) == 0 && count_walls_3x3(colunas, mapa, (i - 1), j) == 0 && count_walls_3x3(colunas, mapa, (i + 1), j) == 0)
            {
                for (index_linha = -1; index_linha < 2; index_linha++) // começa a -1 pois queremos o quadrado imediatamente acima e abaixo
                // queremos que vá apenas até ao indice 1 para ser o quadrado abaixo e ao lado
                {
                    for (index_coluna = -1; index_coluna < 2; index_coluna++)
                    {
                        mapa[i + index_linha][j + index_coluna].visible_piece = '+';
                    }
                }
                // terminar as variaveis
                i = linhas - 2;
                j = colunas - 2;
            }
        }
    }
}

void do_add_ammo(int linhas, int colunas, Map mapa[][colunas])
{
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;
    for (int i = 5; i < linhas - 2; i++)
    { // começa a 5 nas linhas para ficar em cima
        // começa a 3/4 do mapa nas colunas para ficar no canto direito
        for (int j = colunas / 2 + colunas / 4; j < colunas - 2; j++)
        {
            if (count_walls_3x3(colunas, mapa, i, j) == 0 && count_walls_3x3(colunas, mapa, (i - 1), j) == 0 && count_walls_3x3(colunas, mapa, (i + 1), j) == 0)
            {
                for (index_linha = -1; index_linha < 2; index_linha++) // começa a -1 pois queremos o quadrado imediatamente acima e abaixo
                // queremos que vá apenas até ao indice 1 para ser o quadrado abaixo e ao lado
                {
                    for (index_coluna = -1; index_coluna < 2; index_coluna++)
                    {
                        mapa[i + index_linha][j + index_coluna].visible_piece = '-';
                    }
                }
                // terminar as variaveis
                i = linhas - 2;
                j = colunas - 2;
            }
        }
    }
}

void do_add_lighthouse(int linhas, int colunas, Map mapa[][colunas])
{
    int centerX = colunas / 2;
    int centerY = linhas / 2;
    // insere o farol no centro do ecra
    for (int i = centerY - 3; i < centerY + 4; i++)
    {
        for (int j = centerX - 4; j < centerX + 5; j++)
        {
            // garantir que tem pelo menos 2 espaços para jogador passar entre farois e paredes
            if (i == centerY - 3 || i == centerY - 2 || i == centerY + 2 || i == centerY + 3 ||
                j == centerX - 4 || j == centerX - 3 || j == centerX + 3 || j == centerX + 4)
                mapa[i][j].visible_piece = ' ';
            else
                mapa[i][j].visible_piece = '!';
        }
    }
}

int count_walls_3x3(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual)
{
    int counter = 0; // conta quantas paredes existem
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;

    for (index_linha = -1; index_linha < 2; index_linha++) // começa a -1 pois queremos o quadrado imediatamente acima e abaixo
    // queremos que vá apenas até ao indice 1 para ser o quadrado abaixo e ao lado
    {
        for (index_coluna = -1; index_coluna < 2; index_coluna++)
        {
            if (mapa[linha_atual + index_linha][coluna_atual + index_coluna].visible_piece == '#')
            {
                counter++;
            }
        }
    }
    return counter;
}

int count_walls_5x5(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual)
{
    int counter = 0; // conta quantas paredes existem
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;

    for (index_linha = -2; index_linha < 3; index_linha++) // começa a -1 pois queremos o quadrado imediatamente acima e abaixo
    // queremos que vá apenas até ao indice 1 para ser o quadrado abaixo e ao lado
    {
        for (index_coluna = -2; index_coluna < 3; index_coluna++)
        {
            if (mapa[linha_atual + index_linha][coluna_atual + index_coluna].visible_piece == '#')
                counter++;
        }
    }
    return counter;
}

int count_walls_4x8(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual)
{
    int counter = 0; // conta quantas paredes existem
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;

    for (index_linha = -2; index_linha < 2; index_linha++) // começa a -2 pois queremos os quadrados imediatamente acima e abaixo
    // queremos que vá apenas até ao indice 3 para ser os quadrados abaixo e ao lado
    {
        for (index_coluna = -2; index_coluna < 6; index_coluna++)
        {
            if (mapa[linha_atual + index_linha][coluna_atual + index_coluna].visible_piece == '#')
            {
                counter++;
            }
        }
    }
    return counter;
}

void do_insert_flag(int linhas, int colunas, Map mapa[][colunas], Flag flag, Game game)
{
    // fazer enquanto a flag estiver out of bounds
    do
    {
        flag.positionX = rand() % (colunas - 2);
        flag.positionY = rand() % (linhas - 2); // -2 porque nao queremos as bordas
    } while (count_walls_3x3(colunas, mapa, flag.temporary_positionY, flag.temporary_positionX) > 0 || mapa[flag.temporary_positionY][flag.temporary_positionX].visible_piece != ' ');
    // flag estava a calhar dentro de lagos, etc
    if (game.is_flag_placed == 0) // caso nao haja flag ele insere-a e dá novas coordenadas à posição para checkar mais tarde
    {
        mapa[flag.positionY][flag.positionX].visible_piece = ' ';
        flag.positionX = flag.temporary_positionX;
        flag.positionY = flag.temporary_positionY;
        mapa[flag.positionY][flag.positionX].visible_piece = 'I';
        game.is_flag_placed = 1;
    }
}
