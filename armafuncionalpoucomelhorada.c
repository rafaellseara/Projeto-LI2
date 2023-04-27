#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

/*
    CASA LIFE E LAGO APARECEM NO MESMO SITIO - VERIFICAR
        talvez alterar a count walls 5x5 para receber o caracter que queremos procurar e assim podemos comparar
        com tudo e nao so com paredes
    QUANDO HP ESTIVER 0 TEM DE SAIR - APLICAR
*/

typedef struct player
{
    int id;   // number of player eg 1/2/3
    int gun;  // gun using at the moment eg 1- pistol; 2- sword, etc
    int ammo; // ammunition he has
    int positionX;
    int positionY;
    int hp;         // hit points, starts at 100 maybe, goes down to 0 to lose
    int trapNumber; // number of bombs he has to use
    int nightstickNumber; // number of nightsticks
    int usingNightStick;
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

typedef struct bullet
{
    int appearing; // Se está visível ou não
    int positionX;
    int positionY;
    int number;
    int direction;
} Bullet;

Player player1 = {1, 2, 10, 10, 10, 100, 3, 5, 0, 0};
Player player2 = {2, 2, 10, 20, 20, 100, 3, 5, 0, 0};
Flag flag = {0, 0};
Bullet bullet = {0, 0, 0, 0, 0};
Mob mob={1,0,0,0,0,100};
char piece_in_place = ' '; // variavel para guardar o caracter (ex. lago) para depois voltar a colocar quando o jogador sair
char last_direction_moved;
int is_flag_placed = 0;             // guardar se a flag está presente
int flag_positionX, flag_positionY; // posiçoes da flag para comparar e recoloca-la
int timeofUsage=0;
int timeofItems=30;


/*
esta funçao troca as armas do jogadores
*/
void playerweapons(int c)
{
//Se a gun no struct do jogador estiver 1->Punho 2->Pistola
//Para Trocar Armas
if (c == '1') // Trocar para soco
    {
    player1.gun=1;
    }
else if (c == '2') // Troca para pistola
    {
    player1.gun=2;
    }
}
/*
esta funçao usa o soco
*/
void playerpunch(int c, int linhas, int colunas, Map mapa[][colunas],char last_direction_moved)
//A direção do ataque está relacionada com o ultimo movimento do jogador
{
if (c == ' ' && player1.gun == 1 && last_direction_moved == 'w')  //Recebe o ultimo movimento e ataca nessa direção
    {
        // if(mobposition==y-1doPlayer) //Se houver um mob em cima do player dá lhe dano
        // {
        mob.hp -= 10; 
        // }
    }
else if (c == ' ' && player1.gun == 1 && last_direction_moved == 'a')
    {
        // if(mobposition==x-1doPlayer) //Se houver um mob a esquerda do player dá lhe dano
        // {
        mob.hp -= 10;
        // } 
    }
else if (c == ' ' && player1.gun == 1 && last_direction_moved == 'd')
    {
        // if(mobposition==x+1doPlayer) //Se houver um mob a direita do player dá lhe dano
        // {
        mob.hp -= 10;
        // } 
    }
else if (c == ' ' && player1.gun == 1 && last_direction_moved == 's')
    {
        // if(mobposition==y+1doPlayer) //Se houver um mob em baixo do player dá lhe dano
        // {
        mob.hp -= 10;
        // } 
    }
}
/*
esta funçao ativa a bullet e dá a sua direcao
*/
void bulletshow(int c,char last_direction_moved)
{
if (c == ' ' && player1.gun == 2 &&  player1.ammo>0 && last_direction_moved == 'w' && bullet.number==0) //Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento 
    {
    bullet.appearing=1; // bala aparece
    bullet.direction=1; //para dar a direção da bala
    bullet.number += 1; // aumenta a contagem de balas no mapa
    }
else if (c == ' ' && player1.gun == 2 &&  player1.ammo>0 && last_direction_moved == 'a' && bullet.number==0)
    {
    bullet.appearing=1;
    bullet.direction=2;
    bullet.number += 1;
    }
else if (c == ' ' && player1.gun == 2 &&  player1.ammo>0 && last_direction_moved == 's' && bullet.number==0)
    {
    bullet.appearing=1;
    bullet.direction=3;
    bullet.number += 1;
    }
else if (c == ' ' && player1.gun == 2 &&  player1.ammo>0 && last_direction_moved == 'd' && bullet.number==0)
    {
    bullet.appearing=1;
    bullet.direction=4;
    bullet.number += 1;
    }
}
/*
esta funçao dá posição (a posicao dela é igual à do jogador)
*/
void bullet_position()
{
if (bullet.appearing == 0)
            {
             bullet.positionX=player1.positionX;
             bullet.positionY=player1.positionY;
            }
}
/*
esta funçao faz a bala desaparecer quando colide com algo (a posicao dela é igual à do jogador)
*/
void bullet_collision(int linhas, int colunas, Map mapa[][colunas])
{
if (mapa[bullet.positionY][bullet.positionX].visible_piece =='#') //|| mapa[bullet.positionY][bullet.positionX].visible_piece == MOB) //caso a posicão da bala seja igual à posicao de uma parede ou mob
    {
    bullet.appearing=0; // a bala desaparece 
    bullet.number=0; // Assim a contagem volta a zero
    }
//else if  mapa[bullet.positionY][bullet.positionX].visible_piece == MOB)  mob.hp -= 15
}
/*
Esta função vai updatando e dando print à bala
*/
void createbullet(char c) //para confirmar se o erro era de estar dentro do update tambem substituir por um switch do bulletnumber
{
if (bullet.number==1 && bullet.appearing==1) // substituir por um switch /switch(bullet.direction)
        {
            switch (bullet.direction)
            {
            case  1: mvaddch(bullet.positionY - 1 ,bullet.positionX,'*');  bullet.positionY -=1; break;
            case  2: mvaddch(bullet.positionY ,bullet.positionX - 1,'*'); bullet.positionX -=1; break;
            case  3: mvaddch(bullet.positionY + 1 ,bullet.positionX,'*'); bullet.positionY +=1; break;
            case  4: mvaddch(bullet.positionY ,bullet.positionX + 1,'*'); bullet.positionX +=1; break;
            }        
        }
}
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
funçao relativas às estruturas que tiram e acrescentam vida/amunição
*/
void do_structure_aplications(int colunas, int linhas, Map mapa[][colunas])
{
    if (mapa[player1.positionY][player1.positionX].visible_piece == '~')
    {
        player1.hp -= 4;
    }
    else if (mapa[player1.positionY][player1.positionX].visible_piece == '+')
    {
        player1.hp += 2;
    }
    if (mapa[player1.positionY][player1.positionX].visible_piece == '-')
    {
        player1.ammo += 2;
    }
    if (mapa[player1.positionY][player1.positionX].visible_piece == '^')
    {
        player1.hp -= 20;
    }
}
/*
funçao da luz / escuridão
*/
void createlight(int posy, int posx, int colunas, int linhas,int z)
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
    if(player1.hp <= 100 && player1.hp > 80 && player1.usingNightStick==1) //Caso o Player tenha entre 80 e 100 de vida e NightStick ligado
    {
    for (row = 0; row <= linhas-1; row++) //Contador que inicia na primeira linha, testa tudo nessa linha, e depois passa para a proxima
    {
        column = 0; // para voltar ao primeiro quadrado da linha
        while (column <= colunas-1) //Contador para ir avançando a coluna 
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
                        paracima++; //Serve unicamente para finalizar o contador/teste 
                    }
                }
                paracima = 0; 
                paraolado++;
            }
            if (isLight == 0) // Caso não seja um quadrado onde é suposto haver luz nesse quadrado vai passar a existir um '?' 
            {
                mvaddch(row, column, '?');
            }
            //resetar variáveis para testar para o próximo quadrado
            paraolado = 0; 
            paracima = 0;
            isLight = 0;
            column++;
        }
    }
    }
    else if (player1.hp <= 80 && player1.hp > 60 && player1.usingNightStick==1)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 60 && player1.hp > 40 && player1.usingNightStick==1)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 40 && player1.hp > 20 && player1.usingNightStick==1)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 20 && player1.usingNightStick==1)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 100 && player1.hp > 80 && player1.usingNightStick==0)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 80 && player1.hp > 60 && player1.usingNightStick==0)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 60 && player1.hp > 40 && player1.usingNightStick==0)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 40 && player1.hp > 20 && player1.usingNightStick==0)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
    else if (player1.hp <= 20 && player1.usingNightStick==0)
    {
    for (row = 0; row <= linhas-1; row++)
    {
        column = 0;
        while (column <= colunas-1)
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
funçao que acrescenta casa de curar vida
*/
void do_add_life(int linhas, int colunas, Map mapa[][colunas])
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
                        mapa[i + index_linha][j + index_coluna].visible_piece = '+';
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
        flag_positionX = flag.positionX;
        flag_positionY = flag.positionY;
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
void do_update_map(char c, int colunas, Map mapa[][colunas], int linhas, Flag flag,int n) // tem de receber o mapa desta forma pois é 2D
{

    if (c == 'w' && mapa[player1.positionY - 1][player1.positionX].visible_piece != '#')
    {
        last_direction_moved = 'w';                                                        // guardar ultima direçao em que se moveu
        mapa[player1.positionY][player1.positionX].visible_piece = piece_in_place;         // atribuir o sitio onde esteve à peça que la estava
        if (mapa[player1.positionY - 1][player1.positionX].visible_piece != 'I')           // nao precisamos de recolocar a flag
            piece_in_place = mapa[player1.positionY - 1][player1.positionX].visible_piece; // atribuir a peça que la está para depois colocar de novo
        player1.positionY--;
        if (player1.positionX == flag_positionX && player1.positionY == flag_positionY)
        {
            player1.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
        if (player1.usingNightStick == 1)
        {
        timeofUsage++;
        if(timeofUsage == timeofItems)
        {
        player1.usingNightStick=0;
        timeofUsage=0;
        }
        }
        
    }
    else if (c == 's' && mapa[player1.positionY + 1][player1.positionX].visible_piece != '#')
    {
        last_direction_moved = 's';
        mapa[player1.positionY][player1.positionX].visible_piece = piece_in_place;         // atribuir o sitio onde esteve à peça que la estava
        if (mapa[player1.positionY + 1][player1.positionX].visible_piece != 'I')           // nao precisamos de recolocar a flag
            piece_in_place = mapa[player1.positionY + 1][player1.positionX].visible_piece; // atribuir a peça que la está para depois colocar de novo
        player1.positionY++;
        if (player1.positionX == flag_positionX && player1.positionY == flag_positionY)
        {
            player1.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
        if (player1.usingNightStick == 1)
        {
        timeofUsage++;
        if(timeofUsage == timeofItems)
        {
        player1.usingNightStick=0;
        timeofUsage=0;
        }
        }
    }
    else if (c == 'a' && mapa[player1.positionY][player1.positionX - 1].visible_piece != '#')
    {
        last_direction_moved = 'a';
        mapa[player1.positionY][player1.positionX].visible_piece = piece_in_place;         // atribuir o sitio onde esteve à peça que la estava
        if (mapa[player1.positionY][player1.positionX - 1].visible_piece != 'I')           // nao precisamos de recolocar a flag
            piece_in_place = mapa[player1.positionY][player1.positionX - 1].visible_piece; // atribuir a peça que la está para depois colocar de novo
        player1.positionX--;
        if (player1.positionX == flag_positionX && player1.positionY == flag_positionY)
        {
            player1.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
        if (player1.usingNightStick == 1)
        {
        timeofUsage++;
        if(timeofUsage == timeofItems)
        {
        player1.usingNightStick=0;
        timeofUsage=0;
        }
        }
    }
    else if (c == 'd' && mapa[player1.positionY][player1.positionX + 1].visible_piece != '#')
    {
        last_direction_moved = 'd';
        mapa[player1.positionY][player1.positionX].visible_piece = piece_in_place;         // atribuir o sitio onde esteve à peça que la estava
        if (mapa[player1.positionY][player1.positionX + 1].visible_piece != 'I')           // nao precisamos de recolocar a flag
            piece_in_place = mapa[player1.positionY][player1.positionX + 1].visible_piece; // atribuir a peça que la está para depois colocar de novo
        player1.positionX++;
        if (player1.positionX == flag_positionX && player1.positionY == flag_positionY)
        {
            player1.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
        if (player1.usingNightStick == 1)
        {
        timeofUsage++;
        if(timeofUsage == timeofItems)
        {
        player1.usingNightStick=0;
        timeofUsage=0;
        }
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
    else if (c == 'j')
    {
        do_add_life(linhas, colunas, mapa);
    }
    else if (c == 'e' && mapa[player1.positionY][player1.positionX+1].visible_piece == ' ' && player1.trapNumber>0)//colocar armadilhas no chao
    {
        mapa[player1.positionY][player1.positionX+1].visible_piece = '^';
        player1.trapNumber -= 1;   
    }
    else if (c == 'r' && mapa[player1.positionY][player1.positionX+1].visible_piece == ' ' && player1.nightstickNumber>0)//usar luz
    {
        player1.usingNightStick=1;
        player1.nightstickNumber -= 1;
    }
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
}
/*
esta funçao é muito simples e apenas imprime o mapa para o ecra do utilizador
*/
void do_print_map(int linhas, int colunas, Map mapa[][colunas],int n)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if ((mapa[i][j].visible_piece) == '#')
            {
            attron(COLOR_PAIR(n));    
            mvaddch(i, j, mapa[i][j].visible_piece);
            attroff(COLOR_PAIR(n));
            }
            else
            {
            mvaddch(i, j, mapa[i][j].visible_piece);   
            }
        }
    }
}
/*
esta funçao dá o score e hp
*/
void print_scoreetc(int linhas, int colunas, Map mapa[][colunas],int n)
{
// imprimir score e hp do jogador 1 no ecrã, canto inferior direito
    // caso o hp seja 100 tem uma posiçao
    // verifica tambem quantas casas tem o score para imprimir certo
    attron(COLOR_PAIR(n));
    if (player1.hp == 100)
    {
        mvprintw(linhas-1 , colunas - 7, "HP: %d", player1.hp);
        if (player1.score >= 0 && player1.score < 10)
        {
            mvprintw(linhas-1 , colunas - 17, "Score: %d", player1.score);
        }
        else if (player1.score >= 10 && player1.score < 100)
        {
            mvprintw(linhas-1 , colunas - 18, "Score: %d", player1.score);
        }
        else if (player1.score >= 100)
        {
            mvprintw(linhas-1 , colunas - 19, "Score: %d", player1.score);
        }
    }
    else if (player1.hp > 9 && player1.hp < 100)
    {
        mvprintw(linhas-1, colunas - 6, "HP: %d", player1.hp);
        if (player1.score >= 0 && player1.score < 10)
        {
            mvprintw(linhas-1 , colunas - 16, "Score: %d", player1.score);
        }
        else if (player1.score >= 10 && player1.score < 100)
        {
            mvprintw(linhas-1 , colunas - 17, "Score: %d", player1.score);
        }
        else if (player1.score >= 100)
        {
            mvprintw(linhas-1 , colunas - 18, "Score: %d", player1.score);
        }
    }
    else if (player1.hp < 10)
    {
        mvprintw(linhas-1 , colunas - 5, "HP: %d", player1.hp);
        if (player1.score >= 0 && player1.score < 10)
        {
            mvprintw(linhas-1 , colunas - 15, "Score: %d", player1.score);
        }
        else if (player1.score >= 10 && player1.score < 100)
        {
            mvprintw(linhas-1 , colunas - 16, "Score: %d", player1.score);
        }
        else if (player1.score >= 100)
        {
            mvprintw(linhas-1 , colunas - 17, "Score: %d", player1.score);
        }
    }
    attroff(COLOR_PAIR(n));
}
int main()
{
    char c;
    int linhas, colunas; // para definir o tamanho do mapa
    srand(time(NULL));   // funçao random com a seed do tempo para randomizar ainda mais

    initscr(); // iniciando o ecrã
    refresh();

    //para iniciar cores
    start_color();

    keypad(stdscr, true); // ativa as keypads
    noecho();             // nao aparece input do utilizador
    curs_set(0);          // esconde o cursor

    getmaxyx(stdscr, linhas, colunas); // ve o maximo de linhas e colunas da janela do terminal

    Map mapa[linhas][colunas]; // iniciando um mapa

    // cria uma janela inicial para que o menu.
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20;
    WINDOW *win = newwin(20, 40, start_y, start_x);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    keypad(win, true); // ativa as arcolumn keys

    // Estas são as opções do menu
    char option[2][30] = {"  COMECAR NOVO JOGO!  ",
                          "QUERO SER DESAFIADO :D"};
    int selected;
    int highlight = 0;

    //CORES PARA O MAPA (no init pair o segundo e para o caracter e o terceiro para o fundo)
    init_color(88,500,500,499); //cinzento claro
    init_color(12,0,0,255); //Azul
    init_color(13,0,0,140); //Azul Escuro
    init_color(14,500,400,0); //Amarelo 
    init_pair(1,88,88);//paredes
    init_pair(2,12,12);//lagos
    init_pair(3,13,13);//escuro
    init_pair(4,88,13);//score etc
    init_pair(5,14,14);//jogador
    //

    /*
    Loop while que verifica a tecla que o utlizador clica e faz o highlight da opção desejada.
    No entanto, não deixa o utilizador dar highlight em algo que não é suposto.
    Para concluir o loop acaba assim que o utilizador carregue na tecla enter para escolher a sua opção
    */
    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, 8 + i, 10, option[i]);
            wattroff(win, A_REVERSE);
        }
        selected = wgetch(win);

        switch (selected)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 2)
                highlight = 1;
            break;
        default:
            break;
        }

        if (selected == 10)
            break;
    }

    clear(); // faz clear no terminal

    do_create_map(linhas, colunas, mapa); // aqui criamos o mapa
    do_print_map(linhas, colunas, mapa,1);  // imprimimos o mapa inicial
    attron(COLOR_PAIR(5));
    mvaddch(player1.positionY, player1.positionX, '@');
    attroff(COLOR_PAIR(5));
    // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
    //createlight(player1.positionY, player1.positionX, colunas, linhas,3);
    print_scoreetc(linhas, colunas, mapa,4);

    while (c != 27) // este ciclo funciona como input do user pre historico, sai ao carregar no ESC = 27 ASCII (FAZER MENU)
    {
        c = getch(); // recebe o input do user (key pad nao está a funcionar ???)
        do_structure_aplications(colunas, linhas, mapa);
        
        do_update_map(c, colunas, mapa, linhas, flag,2); // aqui fazemos o update do mapa sempre que o utilizador prima uma tecla
        do_insert_flag(linhas, colunas, mapa, flag);   // inserir a flag
        do_print_map(linhas, colunas, mapa,1);           // imprimimos o mapa para o utilizador
        playerweapons(c);
        bullet_position();
        bulletshow(c,last_direction_moved);
        createbullet(c);
        bullet_collision(linhas, colunas, mapa);
        attron(COLOR_PAIR(5));
        mvaddch(player1.positionY, player1.positionX, '@');
        attroff(COLOR_PAIR(5));
        // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
        //createlight(player1.positionY, player1.positionX, colunas, linhas,3);
        print_scoreetc(linhas, colunas, mapa,4);
    }

    getch(); // espera que o utilizador carregue numa tecla para nao sair abruptamente
    endwin();

    return 0;
}