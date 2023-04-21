#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct player
{
    int id;   // number of player eg 1/2/3
    int gun;  // gun using at the moment eg 1- pistol; 2- sword, etc
    int ammo; // ammunition he has
    int positionX;
    int positionY;
    int hp;         // hit points, starts at 100 maybe, goes down to 0 to lose
    int bombNumber; // number of bombs he has to use
    int score;
} Player;

typedef struct mob
{
    int id;      // need to identify each mob to make sure who dies
    int gun;     // what gun they are carrying
    int showing; // if it's showing or not
    int positionX;
    int positionY;
    int mobType; // 1 for stupid, 2 for coward, 3 for smart, etc
    int hp;      // hit points, maybe start 200-500 and lower it from there
} Mob;

typedef struct flag
{
    int positionX;
    int positionY;
} Flag;

typedef struct map
{
    char visible_piece; // #, @, etc
    Player player;      // one player per map - isto é inutil acho
    Mob mob[20];        // maximum 20 mobs per map - isto tambem é inutil acho
    int is_wall;        // if the position is a wall
} Map;

Player player1 = {1, 2, 100, 10, 10, 100, 2, 0};
Player player2 = {2, 2, 100, 20, 20, 100, 2, 0};
Flag flag = {0, 0};
char piece_in_place; // variavel para guardar o caracter (ex. lago) para depois voltar a colocar quando o jogador sair
char last_direction_moved;
int is_flag_placed = 0; // guardar se a flag está presente

/*
função que conta quantas paredes existem num quadrado 3x3 do mapa
*/
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
/*
função que conta quantas paredes existem num quadrado 5x5 do mapa
*/
int count_walls_5x5(int colunas, Map mapa[][colunas], int linha_atual, int coluna_atual)
{
    int counter = 0; // conta quantas paredes existem
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;

    for (index_linha = -2; index_linha < 3; index_linha++) // começa a -2 pois queremos os quadrados imediatamente acima e abaixo
    // queremos que vá apenas até ao indice 3 para ser os quadrados abaixo e ao lado
    {
        for (index_coluna = -2; index_coluna < 3; index_coluna++)
        {
            if (mapa[linha_atual + index_linha][coluna_atual + index_coluna].visible_piece == '#')
            {
                counter++;
            }
        }
    }
    return counter;
}
/*
funçao que acrescenta um lago ao mapa
*/
void do_add_lake(int linhas, int colunas, Map mapa[][colunas])
{
    int index_linha; // para simplificar codigo, serve de indice para o ciclo que iremos fazer
    int index_coluna;
    for (int i = linhas / 3; i < linhas - 2; i++)
    {
        for (int j = colunas / 3; j < colunas - 2; j++)
        {
            if (count_walls_5x5(colunas, mapa, i, j) == 0 && count_walls_5x5(colunas, mapa, (i - 1), j) == 0 && count_walls_5x5(colunas, mapa, (i + 1), j) == 0)
            {
                for (index_linha = -2; index_linha < 3; index_linha++) // começa a -1 pois queremos o quadrado imediatamente acima e abaixo
                // queremos que vá apenas até ao indice 1 para ser o quadrado abaixo e ao lado
                {
                    for (index_coluna = -2; index_coluna < 3; index_coluna++)
                    {
                        mapa[i + index_linha][j + index_coluna].visible_piece = '~';
                    }
                }
                i = linhas - 2;
                j = colunas - 2;
            }
        }
    }
}
/*
funçao que testa se o mapa é valido - fazer??
*/
/*
função que insere a flag no mapa -- a dar mal, check later
*/
void do_insert_flag(int linhas, int colunas, Map mapa[][colunas], Flag flag)
{
    // fazer enquanto a flag estiver out of bounds
    do
    {
        flag.positionX = rand() % (colunas - 2); // +3 porque nao queremos o zero e as bordas
        flag.positionY = rand() % (linhas - 2);  // -2 porque nao queremos as bordas
    } while (count_walls_3x3(colunas, mapa, flag.positionY, flag.positionX) > 0);

    if (is_flag_placed == 0)
    {
        mapa[flag.positionY][flag.positionX].visible_piece = 'I';
        is_flag_placed = 1;
    }
}
/*
funçao que destroi uma parede na direçao onde se moveu pela ultima vez
*/
void do_destroy_wall(char last_direction_moved, int y, int x, int linhas, int colunas, Map mapa[][colunas])
{
    // switch nao estava a funcionar, fiz com if e else
    // a terceira condiçao serve para nao apagar as bordas
    if (last_direction_moved == 'w' && mapa[y - 1][x].visible_piece == '#' && (y - 1) != 1)
    {
        mapa[y - 1][x].visible_piece = ' ';
    }
    else if (last_direction_moved == 's' && mapa[y + 1][x].visible_piece == '#' && (y + 1) != (linhas - 1))
    {
        mapa[y + 1][x].visible_piece = ' ';
    }
    else if (last_direction_moved == 'a' && mapa[y][x - 1].visible_piece == '#' && (x - 1) != 1)
    {
        mapa[y][x - 1].visible_piece = ' ';
    }
    else if (last_direction_moved == 'd' && mapa[y][x + 1].visible_piece == '#' && (x + 1) != (colunas - 1))
    {
        mapa[y][x + 1].visible_piece = ' ';
    }
}
/*
função que apoia a criação do mapa juntando paredes
*/
void do_concat_walls(int linhas, int colunas, Map mapa[][colunas])
{
    char mapa_auxiliar[linhas][colunas];
    for (int i = 2; i < linhas - 2; i++)
    {
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
    for (int i = 2; i < linhas - 2; i++)
    {
        for (int j = 2; j < colunas - 2; j++)
        {
            mapa[i][j].visible_piece = mapa_auxiliar[i][j];
        }
    }
}
/*
esta funçao faz o update do mapa, sempre que o jogador se mexe
falta completar esta funçao com o que acontece sempre que o jogador pisa lagos, etc
falta tambem modificar os valores de mapa[][].player.etc e das mobs
*/
void do_update_map(char c, int colunas, Map mapa[][colunas], int linhas, Flag flag) // tem de receber o mapa desta forma pois é 2D
{

    if (c == 'w' && mapa[player1.positionY - 1][player1.positionX].visible_piece != '#')
    {
        last_direction_moved = 'w';
        mapa[player1.positionY][player1.positionX].visible_piece = ' ';
        player1.positionY--;
        if (player1.positionX == flag.positionX && player1.positionY == flag.positionY)
        {
            is_flag_placed = 0; // dar reset a flag
        }
    }
    else if (c == 's' && mapa[player1.positionY + 1][player1.positionX].visible_piece != '#')
    {
        last_direction_moved = 's';
        mapa[player1.positionY][player1.positionX].visible_piece = ' ';
        player1.positionY++;
        if (player1.positionX == flag.positionX && player1.positionY == flag.positionY)
        {
            is_flag_placed = 0; // dar reset a flag
        }
    }
    else if (c == 'a' && mapa[player1.positionY][player1.positionX - 1].visible_piece != '#')
    {
        last_direction_moved = 'a';
        mapa[player1.positionY][player1.positionX].visible_piece = ' ';
        player1.positionX--;
        if (player1.positionX == flag.positionX && player1.positionY == flag.positionY)
        {
            is_flag_placed = 0; // dar reset a flag
        }
    }
    else if (c == 'd' && mapa[player1.positionY][player1.positionX + 1].visible_piece != '#')
    {
        last_direction_moved = 'd';
        mapa[player1.positionY][player1.positionX].visible_piece = ' ';
        player1.positionX++;
        if (player1.positionX == flag.positionX && player1.positionY == flag.positionY)
        {
            is_flag_placed = 0; // dar reset a flag
        }
    }
    else if (c == 'b') // isto é para alterar e meter no create map
    {
        do_concat_walls(linhas, colunas, mapa);
        is_flag_placed = 0; // para testar, depois tirar
    }
    else if (c == 'l') // isto é para alterar e meter no create map
    {
        do_add_lake(linhas, colunas, mapa);
    }
    else if (c == 'x') // para manter, destruir paredes
    {
        do_destroy_wall(last_direction_moved, player1.positionY, player1.positionX, linhas, colunas, mapa);
    }
    mapa[player1.positionY][player1.positionX].visible_piece = '@';
}
/*
esta funçao cria o mapa inicial
falta completar fazendo com que crie estruturas em condiçoes, juntas e nao apenas randomizadas - feito
falta acrescentar lagos, muniçoes, etc
*/
void do_create_map(int linhas, int colunas, Map mapa[][colunas])
{
    // criaçao do mapa

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (i == 0 || i == 1 || i == linhas - 1 || i == linhas - 2 || j == 0 || j == 1 || j == colunas - 1 || j == colunas - 2)
            {
                mapa[i][j].is_wall = 1;
                mapa[i][j].visible_piece = '#';
            }
            else
            {
                if (rand() % 4 == 0 || rand() % 4 == 1)
                {
                    mapa[i][j].is_wall = 1;
                    mapa[i][j].visible_piece = '#';
                }
                else
                {
                    mapa[i][j].is_wall = 0;
                    mapa[i][j].visible_piece = ' ';
                }
            }
        }
    }
    // // ciclo para implementar randomizaçao do mapa
    // for (int i = 0; i < 3; i++)
    // {
    //     do_concat_walls(linhas, colunas, mapa);
    // }
    mapa[player1.positionY][player1.positionX].visible_piece = '@'; // iniciamos o jogador aqui
}
/*
esta funçao é muito simples e apenas imprime o mapa para o ecra do utilizador
*/
void do_print_map(int linhas, int colunas, Map mapa[][colunas])
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            mvaddch(i, j, mapa[i][j].visible_piece);
        }
    }
}
int main()
{
    char c;
    int linhas, colunas; // para definir o tamanho do mapa
    srand(time(NULL));   // funçao random com a seed do tempo para randomizar ainda mais

    initscr(); // iniciando o ecrã
    refresh();

    keypad(stdscr, true); // ativa as keypads
    noecho();             // nao aparece input do utilizador
    curs_set(0);          // esconde o cursor

    getmaxyx(stdscr, linhas, colunas); // ve o maximo de linhas e colunas da janela do terminal

    Map mapa[linhas][colunas]; // iniciando um mapa

    do_create_map(linhas, colunas, mapa); // aqui criamos o mapa
    do_print_map(linhas, colunas, mapa);  // imprimimos o mapa inicial
    while (c != 27)                       // este ciclo funciona como input do user pre historico, sai ao carregar no ESC = 27 ASCII (FAZER MENU)
    {
        c = getch();                                 // recebe o input do user (key pad nao está a funcionar ???)
        do_update_map(c, colunas, mapa, linhas, flag);     // aqui fazemos o update do mapa sempre que o utilizador prima uma tecla
        do_insert_flag(linhas, colunas, mapa, flag); // inserir a flag
        do_print_map(linhas, colunas, mapa);         // imprimimos o mapa para o utilizador
    }

    getch(); // espera que o utilizador carregue numa tecla para nao sair abruptamente
    endwin();

    return 0;
}