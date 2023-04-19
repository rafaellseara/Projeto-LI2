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

typedef struct map
{
    char visiblePiece; // #, @, etc
    Player player;     // one player per map
    Mob mob[20];       // maximum 20 mobs per map
    int is_wall;       // if the position is a wall
} Map;

char map[50][100];
int y = 10;
int x = 10;
char piece_in_place; // variavel para guardar o caracter (ex. lago) para depois voltar a colocar quando o jogador sair

/*
esta funçao faz o update do mapa, sempre que o jogador se mexe 
falta completar esta funçao com o que acontece sempre que o jogador pisa lagos, etc
falta tambem modificar os valores de mapa[][].player.etc e das mobs
*/
void do_update_map(char c, int colunas, Map mapa[][colunas]) // tem de receber o mapa desta forma pois é 2D
{
    if (c == 'w' && mapa[y-1][x].visiblePiece != '#')
    {
        mapa[y][x].visiblePiece = ' ';
        //mvaddch(y, x, ' ');
        y--;
    }
    else if (c == 's' && mapa[y + 1][x].visiblePiece != '#')
    {
        mapa[y][x].visiblePiece = ' ';
        //mvaddch(y, x, ' ');
        y++;
    }
    else if (c == 'a' && mapa[y][x - 1].visiblePiece != '#')
    {
        mapa[y][x].visiblePiece = ' ';
        //mvaddch(y, x, ' ');
        x--;
    }
    else if (c == 'd' && mapa[y][x + 1].visiblePiece != '#')
    {
        mapa[y][x].visiblePiece = ' ';
        //mvaddch(y, x, ' ');
        x++;
    }
    mapa[y][x].visiblePiece = '@';
    //mvaddch(y, x, '@');
}
/*
esta funçao cria o mapa inicial
falta completar fazendo com que crie estruturas em condiçoes, juntas e nao apenas randomizadas
falta acrescentar lagos, muniçoes, etc
talvez colocar jogador implementado tambem aqui inicialmente (esta na main)
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
                mapa[i][j].visiblePiece = '#';
                map[i][j] = '#';
                //mvaddch(i, j, '#');
            }
            else
            {
                if (rand() % 5 == 0)
                {
                    mapa[i][j].is_wall = 1;
                    mapa[i][j].visiblePiece = '#';
                    map[i][j] = '#';
                    //mvaddch(i, j, '#');
                }
                else
                {
                    mapa[i][j].is_wall = 0;
                    mapa[i][j].visiblePiece = ' ';
                    map[i][j] = ' ';
                    //mvaddch(i, j, ' ');
                }
            }
        }
    }
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
            mvaddch(i,j,mapa[i][j].visiblePiece);
        }
        
    }
    
}
int main()
{
    char c;
    int linhas, colunas; // para definir o tamanho do mapa
    srand(time(NULL)); // funçao random com a seed do tempo para randomizar ainda mais

    initscr(); // iniciando o ecrã
    refresh();

    keypad(stdscr, 1); // ativa as keypads
    noecho();          // nao aparece input do utilizador
    curs_set(0);       // esconde o cursor

    getmaxyx(stdscr, linhas, colunas); // ve o maximo de linhas e colunas da janela do terminal

    Map mapa[linhas][colunas]; // iniciando um mapa

    do_create_map(linhas, colunas, mapa); // aqui criamos o mapa
    mapa[y][x].visiblePiece = '@'; // iniciamos o jogador aqui mas talvez colocar la em cima na create map, mais facil
    do_print_map(linhas, colunas, mapa); // imprimimos o mapa inicial
    while (c != 27) // este ciclo funciona como input do user pre historico, sai ao carregar no ESC = 27 ASCII (FAZER MENU)
    {
        c = getch(); // recebe o input do user (key pad nao está a funcionar ???)
        do_update_map(c, colunas, mapa); // aqui fazemos o update do mapa sempre que o utilizador prima uma tecla
        do_print_map(linhas,colunas,mapa); // imprimimos o mapa para o utilizador
    }

    getch(); // espera que o utilizador carregue numa tecla para nao sair abruptamente
    endwin();

    return 0;
}