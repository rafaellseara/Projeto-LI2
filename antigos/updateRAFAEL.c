#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

/*
    Ter de refazer as cenas das balas para criar balas de cada jogador
        * para a do player 1
        - para o do player 2 (?)
    Criar uma janela de menu
        Player X ganhou o jogo, o Player Y vai ter de pagar o jantar
    Criar scoreboard para jogo facil e dificil
*/

typedef struct player
{
    int id;   // number of player eg 1/2/3
    int gun;  // gun using at the moment eg 1- pistol; 2- sword, etc
    int ammo; // ammunition he has
    int positionX;
    int positionY;
    int hp;               // hit points, starts at 100 maybe, goes down to 0 to lose
    int trapNumber;       // number of bombs he has to use
    int nightstickNumber; // number of nightsticks
    int usingNightStick;
    int score;
} Player;

typedef struct mob
{
    int id;      // need to identify each mob to make sure who dies
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

typedef struct scoreboard
{
    int counter;
    char nome[500][30];
    int score[500];
} Scoreboard;

Player player1 = {1, 2, 100, 10, 10, 100, 3, 5, 0, 0};
Player player2 = {2, 2, 100, 20, 20, 100, 3, 5, 0, 0};
Flag flag = {0, 0};
Bullet bullet = {0, 0, 0, 0, 0};
Mob mob = {1, 0, 0, 0, 1, 100};
char piece_in_place = ' '; // variavel para guardar o caracter (ex. lago) para depois voltar a colocar quando o jogador sair
char player1_last_direction_moved;
char player2_last_direction_moved;
char c;
char player1_character = '@';
char player2_character = '@';
int is_flag_placed = 0;             // guardar se a flag está presente
int flag_positionX, flag_positionY; // posiçoes da flag para comparar e recoloca-la
int time_of_usage = 0;
int maximum_nightstick_time = 30;
int game_over = 0;
int mob_positionX, mob_positionY;
int is_mob_placed = 0;

/*
esta funçao troca as armas do jogadores
*/
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
/*
esta funçao usa o soco
            TERMINAR - mob tem de estar acima do jogador
*/
void do_player_punch(int c, char player1_last_direction_moved)
// A direção do ataque está relacionada com o ultimo movimento do jogador
{
    if (c == ' ' && player1.gun == 1 && player1_last_direction_moved == 'w') // Recebe o ultimo movimento e ataca nessa direção
    {
        // if(mobposition==y-1doPlayer) //Se houver um mob em cima do player dá lhe dano
        // {
        mob.hp -= 10;
        // }
    }
    else if (c == ' ' && player1.gun == 1 && player1_last_direction_moved == 'a')
    {
        // if(mobposition==x-1doPlayer) //Se houver um mob a esquerda do player dá lhe dano
        // {
        mob.hp -= 10;
        // }
    }
    else if (c == ' ' && player1.gun == 1 && player1_last_direction_moved == 'd')
    {
        // if(mobposition==x+1doPlayer) //Se houver um mob a direita do player dá lhe dano
        // {
        mob.hp -= 10;
        // }
    }
    else if (c == ' ' && player1.gun == 1 && player1_last_direction_moved == 's')
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
void bulletshow(int c, char player1_last_direction_moved)
{
    if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 'w' && bullet.number == 0) // Caso haja munição e não haja mais balas no mapa a pistola ataca na direção do ultimo movimento
    {
        bullet.appearing = 1; // bala aparece
        bullet.direction = 1; // para dar a direção da bala
        bullet.number += 1;   // aumenta a contagem de balas no mapa
        player1.ammo--;
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 'a' && bullet.number == 0)
    {
        bullet.appearing = 1;
        bullet.direction = 2;
        bullet.number += 1;
        player1.ammo--;
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 's' && bullet.number == 0)
    {
        bullet.appearing = 1;
        bullet.direction = 3;
        bullet.number += 1;
        player1.ammo--;
    }
    else if (c == ' ' && player1.gun == 2 && player1.ammo > 0 && player1_last_direction_moved == 'd' && bullet.number == 0)
    {
        bullet.appearing = 1;
        bullet.direction = 4;
        bullet.number += 1;
        player1.ammo--;
    }
}
/*
esta funçao dá posição (a posicao dela é igual à do jogador)
*/
void bullet_position()
{
    if (bullet.appearing == 0)
    {
        bullet.positionX = player1.positionX;
        bullet.positionY = player1.positionY;
    }
}
/*
esta funçao faz a bala desaparecer quando colide com algo (a posicao dela é igual à do jogador)
*/
void bullet_collision(int colunas, Map mapa[][colunas])
{
    if (mapa[bullet.positionY][bullet.positionX].visible_piece == '#' || mapa[bullet.positionY][bullet.positionX].visible_piece == '!') //|| mapa[bullet.positionY][bullet.positionX].visible_piece == MOB) //caso a posicão da bala seja igual à posicao de uma parede ou mob
    {
        bullet.appearing = 0; // a bala desaparece
        bullet.number = 0;    // Assim a contagem volta a zero
    }
    // else if  mapa[bullet.positionY][bullet.positionX].visible_piece == MOB)  mob.hp -= 15
}
/*
Esta função vai updatando e dando print à bala
*/
void createbullet() // para confirmar se o erro era de estar dentro do update tambem substituir por um switch do bulletnumber
{
    if (bullet.number == 1 && bullet.appearing == 1) // substituir por um switch /switch(bullet.direction)
    {
        switch (bullet.direction)
        {
        case 1:
            mvaddch(bullet.positionY - 1, bullet.positionX, '*');
            bullet.positionY -= 1;
            break;
        case 2:
            mvaddch(bullet.positionY, bullet.positionX - 1, '*');
            bullet.positionX -= 1;
            break;
        case 3:
            mvaddch(bullet.positionY + 1, bullet.positionX, '*');
            bullet.positionY += 1;
            break;
        case 4:
            mvaddch(bullet.positionY, bullet.positionX + 1, '*');
            bullet.positionX += 1;
            break;
        }
    }
}

void do_guns_aplications(char c, char player1_last_direction_moved, int colunas, Map mapa[][colunas])
{
    change_player_weapon(c);
    bullet_position();
    bulletshow(c, player1_last_direction_moved);
    createbullet();
    bullet_collision(colunas, mapa);
    do_player_punch(c, player1_last_direction_moved);
    if (bullet.positionX == mob_positionX && bullet.positionY == mob_positionY)
    {
        bullet.appearing = 0; // a bala desaparece
        bullet.number = 0;    // Assim a contagem volta a zero
        mob.hp -= 50;
        if (mob.hp <= 0)
        {
            is_mob_placed = 0;
            mob.hp = 100;
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
aplicaçoes das mobs
*/
void do_mob_application(int linhas, int colunas, Map mapa[][colunas], Mob mob)
{
    // fazer enquanto a mob estiver out of bounds
    do
    {
        mob.positionX = rand() % (colunas - 2);
        mob.positionY = rand() % (linhas - 2); // -2 porque nao queremos as bordas
    } while (count_walls_3x3(colunas, mapa, mob.positionY, mob.positionX) > 0 && mapa[mob.positionY][mob.positionX].visible_piece != ' ');
    // mob estava a calhar dentro de lagos, etc
    if (is_mob_placed == 0) // caso nao haja mob ele insere-a e dá novas coordenadas à posição para checkar mais tarde
    {
        mob_positionX = mob.positionX;
        mob_positionY = mob.positionY;
        is_mob_placed = 1;
    }
}
/*
função que conta quantas paredes existem num quadrado 5x5 do mapa
*/
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
/*
funçao relativas às estruturas que tiram e acrescentam vida/amunição
*/
void do_structure_aplications_single_player(int colunas, Map mapa[][colunas])
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
void do_structure_aplications_multi_player(int colunas, Map mapa[][colunas])
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

/*
funçao da luz / escuridão
    ------------------360 LINHAS?------------------
*/
void createlight(int posy, int posx, int colunas, int linhas, int z)
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
/*
funçao que acrescenta um lago ao mapa
*/
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
/*
funçao que acrescenta casa de curar vida
*/
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
/*
funçao que acrescenta casa de aumentar muniçao
*/
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
/*
funçao que adiciona o farol
*/
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
/*
função que insere a flag no mapa
*/
void do_insert_flag(int linhas, int colunas, Map mapa[][colunas], Flag flag)
{
    // fazer enquanto a flag estiver out of bounds
    do
    {
        flag.positionX = rand() % (colunas - 2);
        flag.positionY = rand() % (linhas - 2); // -2 porque nao queremos as bordas
    } while (count_walls_3x3(colunas, mapa, flag.positionY, flag.positionX) > 0 && mapa[flag.positionY][flag.positionX].visible_piece != ' ');
    // flag estava a calhar dentro de lagos, etc
    if (is_flag_placed == 0) // caso nao haja flag ele insere-a e dá novas coordenadas à posição para checkar mais tarde
    {
        mapa[flag_positionY][flag_positionX].visible_piece = ' ';
        flag_positionX = flag.positionX;
        flag_positionY = flag.positionY;
        mapa[flag.positionY][flag.positionX].visible_piece = 'I';
        is_flag_placed = 1;
    }
}
/*
funçao que destroi uma parede na direçao onde se moveu pela ultima vez
*/
void do_destroy_wall(char player1_last_direction_moved, int y, int x, int linhas, int colunas, Map mapa[][colunas])
{
    // switch nao estava a funcionar, fiz com if e else
    // a terceira condiçao serve para nao apagar as bordas
    if (player1_last_direction_moved == 'w' && mapa[y - 1][x].visible_piece == '#' && (y - 1) != 1)
    {
        mapa[y - 1][x].visible_piece = ' ';
    }
    else if (player1_last_direction_moved == 's' && mapa[y + 1][x].visible_piece == '#' && (y + 1) != (linhas - 1))
    {
        mapa[y + 1][x].visible_piece = ' ';
    }
    else if (player1_last_direction_moved == 'a' && mapa[y][x - 1].visible_piece == '#' && (x - 1) != 1)
    {
        mapa[y][x - 1].visible_piece = ' ';
    }
    else if (player1_last_direction_moved == 'd' && mapa[y][x + 1].visible_piece == '#' && (x + 1) != (colunas - 1))
    {
        mapa[y][x + 1].visible_piece = ' ';
    }
}
/*
função que apoia a criação do mapa juntando paredes
*/
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

/*
Função que imprime a janela de pausa no ecrã assim que o utilizador pressiona na tecla p para pausar o jogo.
Esta desaparece assim que o utilizador carrega na tecla enter.
*/
void pause_win(int linhas, int colunas)
{
    int start_y = linhas / 2 - 15, start_x = colunas / 2 - 30; // cordenadas inicias
    WINDOW *win_pause = newwin(30, 60, start_y, start_x);      // criação da janela desejada
    box(win_pause, 0, 0);                                      // box à volta da janela
    refresh();
    wrefresh(win_pause);
    /*
    O processo seguinte imprime para o ecrã a msg que é necessária.
    Neste caso imprimime-se duas frases com o atributo de BOLD e uma frase com o atributo de REVERSE(cores reversas).
    */
    wattron(win_pause, A_BOLD); // atributo bold on
    mvwprintw(win_pause, 11, 12, "    O MENU DE PAUSA E PARA FRACOS    ");
    mvwprintw(win_pause, 13, 12, "CARREGA NO BOTAO ENTER PARA CONTINUAR");
    wattroff(win_pause, A_BOLD);   // atributo bold off
    wattron(win_pause, A_REVERSE); // atributo reverse on
    mvwprintw(win_pause, 17, 18, "        CONTINUAR        ");
    wattroff(win_pause, A_REVERSE); // atributo reverse off
    wrefresh(win_pause);
    // loop que espera pela tecla enter para continuar
    while (true)
    {
        char selected = getch();
        if (selected == 10)
            break;
    }
    wclear(win_pause);
    wrefresh(win_pause);
    refresh();
}

/*
esta funçao faz o update do mapa, sempre que o jogador se mexe
*/
void do_update_map_single_player(char c, int colunas, Map mapa[][colunas], int linhas) // tem de receber o mapa desta forma pois é 2D
{
    // transformar num switch??
    if (c == 'w' && mapa[player1.positionY - 1][player1.positionX].visible_piece != '#' && mapa[player1.positionY - 1][player1.positionX].visible_piece != '!')
    {
        player1_last_direction_moved = 'w'; // guardar ultima direçao em que se moveu
        player1.positionY--;
        player1_character = '^';
    }
    else if (c == 's' && mapa[player1.positionY + 1][player1.positionX].visible_piece != '#' && mapa[player1.positionY + 1][player1.positionX].visible_piece != '!')
    {
        player1_last_direction_moved = 's';
        player1.positionY++;
        player1_character = 'v';
    }
    else if (c == 'a' && mapa[player1.positionY][player1.positionX - 1].visible_piece != '#' && mapa[player1.positionY][player1.positionX - 1].visible_piece != '!')
    {
        player1_last_direction_moved = 'a';
        player1.positionX--;
        player1_character = '<';
    }
    else if (c == 'd' && mapa[player1.positionY][player1.positionX + 1].visible_piece != '#' && mapa[player1.positionY][player1.positionX + 1].visible_piece != '!')
    {
        player1_last_direction_moved = 'd';
        player1.positionX++;
        player1_character = '>';
    }
    else if (c == 'x') // destruir paredes
    {
        do_destroy_wall(player1_last_direction_moved, player1.positionY, player1.positionX, linhas, colunas, mapa);
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
        game_over = 1;
    }
}
void do_update_map_multi_player(char c, int colunas, Map mapa[][colunas], int linhas)
{
    switch (c)
    {
    case 'w':
        if (mapa[player1.positionY - 1][player1.positionX].visible_piece != '#' && mapa[player1.positionY - 1][player1.positionX].visible_piece != '!')
        {
            player1_last_direction_moved = 'w';
            player1.positionY--;
            player1_character = '^';
        }
        break;
    case 's':
        if (mapa[player1.positionY + 1][player1.positionX].visible_piece != '#' && mapa[player1.positionY + 1][player1.positionX].visible_piece != '!')
        {
            player1_last_direction_moved = 's';
            player1.positionY++;
            player1_character = 'v';
        }
        break;
    case 'a':
        if (mapa[player1.positionY][player1.positionX - 1].visible_piece != '#' && mapa[player1.positionY][player1.positionX - 1].visible_piece != '!')
        {
            player1_last_direction_moved = 'a';
            player1.positionX--;
            player1_character = '<';
        }
        break;
    case 'd':
        if (mapa[player1.positionY][player1.positionX + 1].visible_piece != '#' && mapa[player1.positionY][player1.positionX + 1].visible_piece != '!')
        {
            player1_last_direction_moved = 'd';
            player1.positionX++;
            player1_character = '>';
        }
        break;
    case '8':
        if (mapa[player2.positionY - 1][player2.positionX].visible_piece != '#' && mapa[player2.positionY - 1][player2.positionX].visible_piece != '!')
        {
            player2_last_direction_moved = '8';
            player2.positionY--;
            player2_character = '^';
        }
        break;
    case '2':
        if (mapa[player2.positionY + 1][player2.positionX].visible_piece != '#' && mapa[player2.positionY + 1][player2.positionX].visible_piece != '!')
        {
            player2_last_direction_moved = '2';
            player2.positionY++;
            player2_character = 'v';
        }
        break;
    case '4':
        if (mapa[player2.positionY][player2.positionX - 1].visible_piece != '#' && mapa[player2.positionY][player2.positionX - 1].visible_piece != '!')
        {
            player2_last_direction_moved = '4';
            player2.positionX--;
            player2_character = '<';
        }
        break;
    case '6':
        if (mapa[player2.positionY][player2.positionX + 1].visible_piece != '#' && mapa[player2.positionY][player2.positionX + 1].visible_piece != '!')
        {
            player2_last_direction_moved = 'd';
            player2.positionX++;
            player2_character = '>';
        }
        break;
    case 'x':
        do_destroy_wall(player1_last_direction_moved, player1.positionY, player1.positionX, linhas, colunas, mapa);
        break;
    case 'e':
        if (mapa[player1.positionY][player1.positionX + 1].visible_piece == ' ' && player1.trapNumber > 0)
        {
            mapa[player1.positionY][player1.positionX + 1].visible_piece = '^';
            player1.trapNumber -= 1;
        }
        break;
    case '5':
        do_destroy_wall(player2_last_direction_moved, player2.positionY, player2.positionX, linhas, colunas, mapa);
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
        game_over = 1;
        break;
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
            // caso esteja nas bordas é parede
            if (i == 0 || i == 1 || i == linhas - 1 || i == linhas - 2 || j == 0 || j == 1 || j == colunas - 1 || j == colunas - 2)
            {
                mapa[i][j].is_wall = 1;
                mapa[i][j].visible_piece = '#';
            }
            else
            {
                // usamos o %4 porque era o que ficava mais visualmente atrativo para o que queriamos
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
    // ciclo para implementar randomizaçao do mapa
    for (int i = 0; i < 10; i++)
    {
        do_concat_walls(linhas, colunas, mapa);
    }
    do_add_life(linhas, colunas, mapa);
    do_add_lake(linhas, colunas, mapa);
    do_add_ammo(linhas, colunas, mapa);
    do_add_lighthouse(linhas, colunas, mapa);
    do_insert_flag(linhas, colunas, mapa, flag);
    do_mob_application(linhas, colunas, mapa, mob);
}
/*
esta funçao é muito simples e apenas imprime o mapa para o ecra do utilizador
*/
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
/*
esta funçao dá o score e hp
*/
void print_footer_single_player()
{
    attron(COLOR_PAIR(4));
    mvprintw(0, 10, "Player1:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d", player1.hp, player1.score, player1.gun, player1.trapNumber, player1.ammo);
    attroff(COLOR_PAIR(4));
}
void print_footer_multi_player(int linhas, int colunas)
{
    attron(COLOR_PAIR(4));
    mvprintw(0, 10, "Player1:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d", player1.hp, player1.score, player1.gun, player1.trapNumber, player1.ammo);
    mvprintw(linhas - 1, colunas / 3 + colunas / 3, "Player2:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d", player2.hp, player2.score, player2.gun, player2.trapNumber, player2.ammo);
    attroff(COLOR_PAIR(4));
}
void print_footer_challenge()
{
    attron(COLOR_PAIR(4));
    mvprintw(0, 10, "Player1:    HP: %d  Score: %d  Gun: %d  Traps: %d  Ammo: %d  Nightsticks: %d", player1.hp, player1.score, player1.gun, player1.trapNumber, player1.ammo, player1.nightstickNumber);
    attroff(COLOR_PAIR(4));
}
/*
funçao que determina a posiçao do jogador no canto superior esquerdo do ecra
*/
void player1_position(int linhas, int colunas)
{

    // inserir o jogador 1 à esquerda do farol
    int centerY = linhas / 2;
    int centerX = colunas / 2;
    player1.positionY = centerY;
    player1.positionX = centerX - 4;
}
void player2_position(int linhas, int colunas)
{

    // inserir o jogador 1 à esquerda do farol
    int centerY = linhas / 2;
    int centerX = colunas / 2;
    player2.positionY = centerY;
    player2.positionX = centerX + 4;
}
void do_add_player(int game_type)
{
    if (game_type == 1)
    {
        attron(COLOR_PAIR(5));
        mvaddch(player1.positionY, player1.positionX, player1_character);
        attroff(COLOR_PAIR(5));
    }
    else
    {
        attron(COLOR_PAIR(5));
        mvaddch(player1.positionY, player1.positionX, player1_character);
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(6));
        mvaddch(player2.positionY, player2.positionX, player2_character);
        attroff(COLOR_PAIR(6));
    }
}

void do_add_score(int game_type)
{
    if (game_type == 1)
    {
        if (player1.positionX == flag_positionX && player1.positionY == flag_positionY)
        {
            player1.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
    }
    else
    {
        if (player1.positionX == flag_positionX && player1.positionY == flag_positionY)
        {
            player1.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
        if (player2.positionX == flag_positionX && player2.positionY == flag_positionY)
        {
            player2.score++;    // incrementar 1 ao score
            is_flag_placed = 0; // dar reset a flag
        }
    }
}
void do_check_nightstick()
{
    // condiçao para verificar quantos passos deu com o nightstick on
    if (player1.usingNightStick == 1)
    {
        time_of_usage++;
        if (time_of_usage == maximum_nightstick_time)
        {
            player1.usingNightStick = 0;
            time_of_usage = 0;
        }
    }
}
/*
Função que imprime a janela final do jogo de score 0 no ecrã assim que o utilizado perde (hp = 0)
Esta desaparece assim que o utilizador carrega na tecla enter.
*/
void final_0_score_win(int linhas, int colunas){

    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20;  // cordenadas iniciais
    WINDOW *win_final = newwin(20, 40, start_y, start_x);       // criação da janela desejada
    box(win_final, 0, 0);                                       // box à volta da janela

    wattron(win_final, A_BOLD);  // atributo bold on
    mvwprintw(win_final,  7, 5, "       0 PONTOS? LOSER!      ");
    wattroff(win_final, A_BOLD);  // atributo bold off
    mvwprintw(win_final,  9, 5, "COM ESSA PONTUACAO NEM MERCES"); 
    mvwprintw(win_final, 10, 5, "    IR PARA O SCOREBOARD!    ");
    wrefresh(win_final);

    wattron(win_final, A_REVERSE); // atributo reverse on
    mvwprintw(win_final, 13, 8, "        CONTINUAR        ");
    wattroff(win_final, A_REVERSE); // atributo reverse off
    wrefresh(win_final);
    // loop que espera pela tecla enter para continuar
    while (true)
    {
        char selected = getch();
        if (selected == 10)
            break;
    }
    wclear(win_final);
    wrefresh(win_final);
    refresh();
}
/*
Função que imprime a janela final do jogo de score > 0 no ecrã assim que o utilizado perde.
Esta desaparece assim que o utilizador carrega na tecla enter depois de escolher o nome.
*/
void final_win(int linhas, int colunas, int score)
{
    noecho();
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20;  // cordenadas iniciais
    WINDOW *win_final = newwin(20, 40, start_y, start_x);       // criação da janela desejada
    box(win_final, 0, 0);                                       // box à volta da janela

    FILE *file_score;                                           // criação de um ficheito
    file_score = fopen("scoreboard_file.txt", "a");             // ficheiro ligado ao txt do scoreboard em mode de escrever (a de append)

    char nome[28] = {0};
    nome[0] = ' ';

    wattron(win_final, A_BOLD); // atributo bold on
    mvwprintw(win_final, 6, 17, "LOSER!");
    wattroff(win_final, A_BOLD); // atributo bold off
    mvwprintw(win_final, 8, 7, "A TUA PONTUACAO FOI DE %d", score);
    mvwprintw(win_final, 10, 8, "NOME PARA O SCOREBOARD:");
    wrefresh(win_final);

    WINDOW *win_nome = newwin(3, 30, start_y + 12, start_x + 5); // criação da janela para escrever o nome
    box(win_nome, 0, 0);                                         // box à volta da janela
    move(start_y + 13, start_x + 6);                             // move a escrita do nome para o sitio desejado
    wrefresh(win_nome);

    int check = 0; // variavel para sair da janela

    /*
    loop que irá escrever o nome para o ecrã como tambem apagar se necessário
    */
    for (int i = 0; i < 28;)  //maximo de 28 caracteres
    {
        char selected = getch();
        if ((selected == 10) && (nome[0] != ' ')) // se a tecla selecionda for o enter -> acaba o loop
        {
            check = 1;
            break;
        }
        else if (i < 27 && isprint(selected) && !isspace(selected)) // se a tecla selecionada estiver dentro dos parametros -> escreve a no ecra
        {
            nome[i] = selected;
            mvwprintw(win_nome, 1, i + 1, "%c", selected);
            wrefresh(win_nome);
            i++;
        }
        else if ((selected == 127) && (i > 0)) // se a tecla for o backspace -> apaga o ultimo caracter e volta uma casa atras
        {
            i--;
            nome[i] = ' ';
            mvwaddch(win_nome, 1, i + 1, ' ');
            wmove(win_nome, 1, i + 1);
            wrefresh(win_nome);
        }
    }

    wrefresh(win_nome);

    if (file_score != NULL) // caso o ficheiro seja null
        fprintf(file_score, "\n%s %d", nome, score);  // imprime no ficheiro o nome e o score
    fclose(file_score); // fecha o ficheiro
}
/*
funçao que tem todas as propriedades do jogo
*/
void main_game_single_player(char c, int linhas, int colunas, Map mapa[][colunas])
{
    while (game_over == 0)
    {
        if (player1.hp > 0)
        {
            cbreak();
            timeout(200);
            c = getch();
            do_structure_aplications_single_player(colunas, mapa);
            do_update_map_single_player(c, colunas, mapa, linhas); // aqui fazemos o update do mapa sempre que o utilizador prima uma tecla
            do_insert_flag(linhas, colunas, mapa, flag);           // inserir a flag
            do_add_score(1);
            do_mob_application(linhas, colunas, mapa, mob);
            do_print_map(linhas, colunas, mapa, 1); // imprimimos o mapa para o utilizador
            do_guns_aplications(c, player1_last_direction_moved, colunas, mapa);
            // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
            do_add_player(1);
            mvaddch(mob_positionY, mob_positionX, '1');
            print_footer_single_player(); // imprimir caracteristicas do jogo no canto
        }
        else
        {
            game_over = 1;
            clear();
            refresh();
            if (player1.score > 0) final_win(linhas, colunas, player1.score);
            if (player1.score == 0) final_0_score_win(linhas, colunas);
            player1.hp = 100;
            player1.trapNumber = 3;
            player1.ammo = 100;
            player1.score = 0;
            is_flag_placed = 0;
            piece_in_place = ' ';
        }
    }
}
void main_game_multi_player(char c, int linhas, int colunas, Map mapa[][colunas])
{   
    while (game_over == 0)
    {
        if (player1.hp > 0 && player2.hp > 0)
        {
            cbreak();
            timeout(200);
            c = getch();
            do_structure_aplications_multi_player(colunas, mapa);
            do_update_map_multi_player(c, colunas, mapa, linhas);
            do_add_score(2);
            do_insert_flag(linhas, colunas, mapa, flag);
            // aqui vamos inserir as mobs
            do_print_map(linhas, colunas, mapa, 1);
            do_guns_aplications(c, player1_last_direction_moved, colunas, mapa);
            do_add_player(2);
            print_footer_multi_player(linhas, colunas);
        }
        else
        {
            game_over = 1;
            clear();
            refresh();
            final_win(linhas, colunas, player1.score);
            player1.hp = 100;
            player1.score = 0;
            player2.hp = 100;
            player2.score = 0;
            is_flag_placed = 0;
            piece_in_place = ' ';
        }
    }
}
void main_game_challenge(char c, int linhas, int colunas, Map mapa[][colunas])
{
    while (game_over == 0)
    {
        if (player1.hp > 0)
        {
            cbreak();
            timeout(200);
            c = getch();
            do_structure_aplications_single_player(colunas, mapa);
            do_update_map_single_player(c, colunas, mapa, linhas);
            do_check_nightstick();
            do_insert_flag(linhas, colunas, mapa, flag);          
            do_add_score(1);
            // cenas das mobs
            do_print_map(linhas, colunas, mapa, 1);
            createlight(player1.positionY,player1.positionX,colunas, linhas, 3);
            do_guns_aplications(c, player1_last_direction_moved, colunas, mapa);
            do_add_player(1);
            print_footer_challenge();
        }
        else
        {
            game_over = 1;
            clear();
            refresh();
            final_win(linhas, colunas, player1.score);
            player1.hp = 100;
            player1.score = 0;
            is_flag_placed = 0;
            piece_in_place = ' ';
        }
    }
}
/*
funçao que inicia o jogo
*/
void start_game_single_player(int linhas, int colunas, Map mapa[][colunas])
{
    do_print_map(linhas, colunas, mapa, 1); // imprimimos o mapa inicial
    // adicionamos aqui o jogador para termos o mapa com as posiçoes de lagos e assim nao sobrepostas
    player1_position(linhas, colunas); // acertar a posiçao do jogador
    do_add_player(1);
    mvaddch(mob_positionY, mob_positionX, '1');
    // imprimir caracteristicas do jogo no canto
    print_footer_single_player();
}
void start_game_multi_player(int linhas, int colunas, Map mapa[][colunas])
{
    do_print_map(linhas, colunas, mapa, 1);
    player1_position(linhas, colunas);
    player2_position(linhas, colunas);
    do_add_player(2);
    // falta imprimir aqui as mobs
    // falta imprimir aqui o footer
}
void start_game_challenge(int linhas, int colunas, Map mapa[][colunas])
{
    do_print_map(linhas, colunas, mapa, 1);
    player1_position(linhas, colunas);
    do_add_player(1);
    createlight(player1.positionY,player1.positionX,colunas, linhas, 3);
    print_footer_challenge();
}
/*
função que organiza o scoreboard de forma decrescente
*/
void sort_scoreboard ()
{
    FILE *file_score;                                // criação de um ficheito
    file_score = fopen("scoreboard_file.txt", "r");  // ficheiro ligado ao txt do scoreboard em mode de ler (r de reading)

    int score;
    char nome[30];
    int i = 0;

    /*
    Struct para a organização da scoreboard. 
    Inclui uma lista com os nomes, uma lista com os score, e um conter.
    */
    Scoreboard sort_scoreboard;
    sort_scoreboard.counter = 0;

    if (file_score != NULL){  // caso o ficheiro seja null
        while (fscanf(file_score, "%s %d", nome, &score) != EOF){ // enquanto que o ficheiro não chega ao final ele continua a pegar em nomes e scores
            strcpy(sort_scoreboard.nome[i],nome); // copia o nome da linha para a struct
            sort_scoreboard.score[i] = score; // copia o score da linha para o struct
            sort_scoreboard.counter++;
            i++;         
        }
    }
    fclose(file_score); // fecha o ficheiro

    int n = sort_scoreboard.counter;
    int j, temp_score;
    char temp_nome[30];

    /*
    Loop simples que utiliza o metodo de buble sort para ordenar a struct de maneira decrescente
    */
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (sort_scoreboard.score[j] < sort_scoreboard.score[j+1])
            {
                // troca scores
                temp_score = sort_scoreboard.score[j];
                sort_scoreboard.score[j] = sort_scoreboard.score[j+1];
                sort_scoreboard.score[j+1] = temp_score;
            
                // troca nomes
                strcpy(temp_nome, sort_scoreboard.nome[j]);
                strcpy(sort_scoreboard.nome[j], sort_scoreboard.nome[j+1]);
                strcpy(sort_scoreboard.nome[j+1], temp_nome);
            }
        }
    }

    file_score = fopen("scoreboard_file.txt", "w"); // ficheiro ligado ao txt do scoreboard em mode de escrever (w de wright)

    if (file_score != NULL) // caso o ficheiro seja null
        fprintf(file_score, "%s %d", sort_scoreboard.nome[0], sort_scoreboard.score[0]);  // imprime no ficheiro o nome e o score
    i = 1;
    sort_scoreboard.counter--;
    while (file_score != NULL && sort_scoreboard.counter != 0){ 
        if (file_score != NULL) // caso o ficheiro seja null
            fprintf(file_score, "\n%s %d", sort_scoreboard.nome[i], sort_scoreboard.score[i]);  // imprime no ficheiro o nome e o score
        i++;
        sort_scoreboard.counter--;
    }
    fclose(file_score); // fecha o ficheiro
}
/*
função que vai buscar os dados do scoreboard e imprime os no ecrã
*/
void scoreboard(int linhas, int colunas)
{
    WINDOW *win_score = newwin(linhas - 2, colunas - 4, 1, 2);     // criação da janela desejada
    box(win_score, 0, 0);                                          // box à volta da janela

    FILE *file_score;                                              // criação de um ficheiro
    file_score = fopen("scoreboard_file.txt", "r");                // ficheiro ligado ao txt do scoreboard em mode de ler (r de reading)

    char name[100];
    int score;
    int i = 0;
    int counter = 1;

    /*
    loop que imprime linha a linha o nome e o score
    */
    if (file_score != NULL)
    {
        while (fscanf(file_score, "%s %d", name, &score) != EOF)
        {
            if (i % 2 == 0)
            {
                wattron(win_score, A_REVERSE);
                for (int j = 0; j < colunas - 6; j++)
                {
                    mvwprintw(win_score, i + 1, j + 1, " ");
                }
                mvwprintw(win_score, i + 1, 1, "%d %s", counter, name);
                counter++;
                int nDigits = floor(log10(abs(score))) + 1;
                mvwprintw(win_score, i + 1, colunas - 5 - nDigits, "%d", score);
                wattroff(win_score, A_REVERSE);
            }
            else
            {
                mvwprintw(win_score, i + 1, 1, "%d %s", counter, name);
                counter++;
                int nDigits = floor(log10(abs(score))) + 1;
                mvwprintw(win_score, i + 1, colunas - 5 - nDigits, "%d", score);
            }
            i++;
        }
    }

    fclose(file_score);   // fecha o ficheiro
    wrefresh(win_score);
}
/*
Função que imprime a janela de escolha entre o multiplayer e singleplayer do jogo.
Assim que o utilizador escolhe uma das opções e carrega no enter a janela fecha. 
*/
void multi_jogo_win(int linhas, int colunas, Map mapa[][colunas])
{
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20; // cordenadas iniciais
    WINDOW *win_jogo = newwin(20, 40, start_y, start_x);       // criação da janela desejada
    box(win_jogo, 0, 0);                                       // box à volta da janela
    refresh();
    wrefresh(win_jogo);

    int selected;
    int highlight = 0;
    int loop = 1; // variavel para o loop do jogo

    //opções do menu
    const char option1[30] = " - SINGLEPLAYER   ";
    const char option2[30] = " - MULTIPLAYER    ";

    keypad(win_jogo, true); // ativa o keypad
    /*
    Loop while que verifica a tecla que o utlizador clica e faz o highlight da opção desejada.
    Este tambem imprime todas as opções do menu para a janela.
    No entanto, não deixa o utilizador dar highlight em algo que não é suposto.
    Para concluir o loop acaba assim que o utilizador carregue na tecla enter para escolher a sua opção (loop = 0)
    */
    while (loop == 1)
    {
        box(win_jogo, 0, 0);
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
                wattron(win_jogo, A_REVERSE);
            switch (i)
            {
            case 0:
                mvwprintw(win_jogo, 8 + i, 10, option1);
                break;
            case 1:
                mvwprintw(win_jogo, 9 + i, 10, option2);
                break;
            }
            wattroff(win_jogo, A_REVERSE);
        }

        selected = wgetch(win_jogo); // tecla premida

        switch (selected) // switch para dar highlight na opção correta escolhida pelo jogador, não o deixa sair das opções pretendidas
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
        }

        if (selected == 10)
        {
            switch (highlight)
            {
            case 0: // Opção "Singleplayer"
                game_over = 0;
                clear();
                refresh();
                do_create_map(linhas, colunas, mapa);
                start_game_single_player(linhas, colunas, mapa);   // iniciamos o jogo
                main_game_single_player(c, linhas, colunas, mapa); // damos update ao jogo
                clear();
                refresh();
                loop = 0;
                break;
            case 1: // Opção "Multiplayer"
                game_over = 0;
                clear();
                refresh();
                do_create_map(linhas, colunas, mapa);
                start_game_multi_player(linhas, colunas, mapa);   // iniciamos o jogo
                main_game_multi_player(c, linhas, colunas, mapa); // damos update ao jogo
                clear();
                refresh();
                loop = 0;
                break;
            }
        }
        if (selected == 27)
            loop = 0;
    }
}
/*
Função do menu principal do jogo.
Imprime o menu assim que o jogo começa.
Contem uma variadade de opções, as quais podem ser todas acessadas.
*/
void menu(int linhas, int colunas, Map mapa[][colunas])
{

    // cria uma janela inicial para que o menu.
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20;
    WINDOW *win = newwin(20, 40, start_y, start_x);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    keypad(win, true); // ativa as arrow keys

    // Estas são as opções do menu
    const char option1[30] = "  COMECAR NOVO JOGO!  ";
    const char option2[30] = "QUERO SER DESAFIADO :D";
    const char option3[30] = " MANUAL DE INSTRUCOES ";
    const char option4[30] = "     SCOREBOARD!      ";
    const char option5[30] = "      EXIT GAME       ";
    int selected;
    int highlight = 0;
    int loop = 1; // variavel para o loop do jogo

    /*
    Loop while que verifica a tecla que o utlizador clica e faz o highlight da opção desejada.
    Este tambem imprime todas as opções do menu para a janela.
    No entanto, não deixa o utilizador dar highlight em algo que não é suposto.
    Para concluir o loop acaba assim que o utilizador carregue na tecla enter para escolher a sua opção (loop = 0)
    */
    while (loop == 1)
    {
        box(win, 0, 0);
        for (int i = 0; i < 5; i++)
        {
            if (i == highlight)
                wattron(win, A_REVERSE);
            switch (i)
            {
            case 0:
                mvwprintw(win, 7 + i, 10, option1);
                break;
            case 1:
                mvwprintw(win, 7 + i, 10, option2);
                break;
            case 2:
                mvwprintw(win, 7 + i, 10, option3);
                break;
            case 3:
                mvwprintw(win, 7 + i, 10, option4);
                break;
            case 4:
                mvwprintw(win, 7 + i, 10, option5);
                break;
            }
            wattroff(win, A_REVERSE);
        }
        selected = wgetch(win); // tecla premida

        switch (selected) // switch para dar highlight na opção correta escolhida pelo jogador, não o deixa sair das opções pretendidas
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 5)
                highlight = 4;
            break;
        }

        if (selected == 10)
        {
            switch (highlight)
            {
            case 0:                                    // Opção "COMECAR NOVO JOGO!"
                multi_jogo_win(linhas, colunas, mapa); // inicia a janela de singleplayer/multiplayer
                break;
            case 1: // Opção "QUERO SER DESAFIADO :D"
                game_over = 0;
                clear();
                refresh();
                do_create_map(linhas, colunas, mapa);
                start_game_challenge(linhas, colunas, mapa);   // iniciamos o jogo
                main_game_challenge(c, linhas, colunas, mapa); // damos update ao jogo
                clear();
                refresh();
                break;
            case 2: // Opção "MANUAL DE INSTRUCOES"
                break;
            case 3: // Opção "SCOREBOARD!"
                while (true)
                {
                    sort_scoreboard();
                    scoreboard(linhas, colunas); // inicia o scoreboard, caso o utilizador carregue no esc -> sair para o menu principal
                    int selected = getch();
                    if (selected == 27)
                        break;
                }
                clear();
                refresh();
                break;
                break;
            case 4:       // Opção "EXIT GAME"
                loop = 0; // para sair do loop
                break;
            }
        }
    }
}
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
    //start_color();

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
