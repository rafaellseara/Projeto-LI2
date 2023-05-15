#include <ncurses.h>
#include <stdlib.h>

#include "Menu.h"


/*
função que organiza o scoreboard de forma decrescente
*/
void sort_scoreboard()
{
    FILE *file_score;                               // criação de um ficheito
    file_score = fopen("scoreboard_file.txt", "r"); // ficheiro ligado ao txt do scoreboard em mode de ler (r de reading)

    int score;
    char nome[30];
    int i = 0;

    /*
    Struct para a organização da scoreboard.
    Inclui uma lista com os nomes, uma lista com os score, e um conter.
    */
    Scoreboard sort_scoreboard;
    sort_scoreboard.counter = 0;

    if (file_score != NULL)
    { // caso o ficheiro seja null
        while (fscanf(file_score, "%s %d", nome, &score) != EOF)
        {                                          // enquanto que o ficheiro não chega ao final ele continua a pegar em nomes e scores
            strcpy(sort_scoreboard.nome[i], nome); // copia o nome da linha para a struct
            sort_scoreboard.score[i] = score;      // copia o score da linha para o struct
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
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (sort_scoreboard.score[j] < sort_scoreboard.score[j + 1])
            {
                // troca scores
                temp_score = sort_scoreboard.score[j];
                sort_scoreboard.score[j] = sort_scoreboard.score[j + 1];
                sort_scoreboard.score[j + 1] = temp_score;

                // troca nomes
                strcpy(temp_nome, sort_scoreboard.nome[j]);
                strcpy(sort_scoreboard.nome[j], sort_scoreboard.nome[j + 1]);
                strcpy(sort_scoreboard.nome[j + 1], temp_nome);
            }
        }
    }

    file_score = fopen("scoreboard_file.txt", "w"); // ficheiro ligado ao txt do scoreboard em mode de escrever (w de wright)

    if (file_score != NULL)                                                              // caso o ficheiro seja null
        fprintf(file_score, "%s %d", sort_scoreboard.nome[0], sort_scoreboard.score[0]); // imprime no ficheiro o nome e o score
    i = 1;
    sort_scoreboard.counter--;
    while (file_score != NULL && sort_scoreboard.counter != 0)
    {
        if (file_score != NULL)                                                                // caso o ficheiro seja null
            fprintf(file_score, "\n%s %d", sort_scoreboard.nome[i], sort_scoreboard.score[i]); // imprime no ficheiro o nome e o score
        i++;
        sort_scoreboard.counter--;
    }
    fclose(file_score); // fecha o ficheiro
}
void sort_scoreboard_desafio()
{
    FILE *file_score;                                       // criação de um ficheito
    file_score = fopen("scoreboard_file_desafio.txt", "r"); // ficheiro ligado ao txt do scoreboard em mode de ler (r de reading)

    int score;
    char nome[30];
    int i = 0;

    /*
    Struct para a organização da scoreboard.
    Inclui uma lista com os nomes, uma lista com os score, e um conter.
    */
    Scoreboard sort_scoreboard;
    sort_scoreboard.counter = 0;

    if (file_score != NULL)
    { // caso o ficheiro seja null
        while (fscanf(file_score, "%s %d", nome, &score) != EOF)
        {                                          // enquanto que o ficheiro não chega ao final ele continua a pegar em nomes e scores
            strcpy(sort_scoreboard.nome[i], nome); // copia o nome da linha para a struct
            sort_scoreboard.score[i] = score;      // copia o score da linha para o struct
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
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (sort_scoreboard.score[j] < sort_scoreboard.score[j + 1])
            {
                // troca scores
                temp_score = sort_scoreboard.score[j];
                sort_scoreboard.score[j] = sort_scoreboard.score[j + 1];
                sort_scoreboard.score[j + 1] = temp_score;

                // troca nomes
                strcpy(temp_nome, sort_scoreboard.nome[j]);
                strcpy(sort_scoreboard.nome[j], sort_scoreboard.nome[j + 1]);
                strcpy(sort_scoreboard.nome[j + 1], temp_nome);
            }
        }
    }

    file_score = fopen("scoreboard_file_desafio.txt", "w"); // ficheiro ligado ao txt do scoreboard em mode de escrever (w de wright)

    if (file_score != NULL)                                                              // caso o ficheiro seja null
        fprintf(file_score, "%s %d", sort_scoreboard.nome[0], sort_scoreboard.score[0]); // imprime no ficheiro o nome e o score
    i = 1;
    sort_scoreboard.counter--;
    while (file_score != NULL && sort_scoreboard.counter != 0)
    {
        if (file_score != NULL)                                                                // caso o ficheiro seja null
            fprintf(file_score, "\n%s %d", sort_scoreboard.nome[i], sort_scoreboard.score[i]); // imprime no ficheiro o nome e o score
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
    WINDOW *win_score = newwin(linhas - 2, colunas - 4, 1, 2); // criação da janela desejada
    box(win_score, 0, 0);                                      // box à volta da janela

    FILE *file_score;                               // criação de um ficheiro
    file_score = fopen("scoreboard_file.txt", "r"); // ficheiro ligado ao txt do scoreboard em mode de ler (r de reading)

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

    fclose(file_score); // fecha o ficheiro
    wrefresh(win_score);
}
void scoreboard_desafio(int linhas, int colunas)
{
    WINDOW *win_score = newwin(linhas - 2, colunas - 4, 1, 2); // criação da janela desejada
    box(win_score, 0, 0);                                      // box à volta da janela

    FILE *file_score;                                       // criação de um ficheiro
    file_score = fopen("scoreboard_file_desafio.txt", "r"); // ficheiro ligado ao txt do scoreboard em mode de ler (r de reading)

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
    fclose(file_score); // fecha o ficheiro
    wrefresh(win_score);
}
/*
Função que imprime a janela de escolha entre o multiplayer e singleplayer do jogo.
Assim que o utilizador escolhe uma das opções e carrega no enter a janela fecha.
*/
void multi_jogo_win(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Game *game, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
{
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20; // cordenadas iniciais
    WINDOW *win_jogo = newwin(20, 40, start_y, start_x);       // criação da janela desejada
    box(win_jogo, 0, 0);                                       // box à volta da janela
    refresh();
    wrefresh(win_jogo);

    int selected;
    int highlight = 0;
    int loop = 1; // variavel para o loop do jogo

    // opções do menu
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
                game->game_over = 0;
                //start_color();
                //init_color(88, 500, 500, 499);
                //init_pair(1, 88, 20);
                clear();
                refresh();                               
                // attron(COLOR_PAIR(1));
                // mvprintw(4,4, "TESTE");
                // attroff(COLOR_PAIR(1));
                do_create_map(linhas, colunas, mapa, flag, game);
                // mapa[1][1].visible_piece = '#';
                // mapa[3][1].visible_piece = '#';
                // attron(COLOR_PAIR(1));
                // mvprintw(5,4, "peça: %c", mapa[1][1].visible_piece);
                // mvprintw(6,4, "peça: %c",mapa[2][1].visible_piece);
                // mvprintw(7,4, "peça: %c",mapa[3][7].visible_piece);
                // attroff(COLOR_PAIR(1));
                start_game_single_player(linhas, colunas, mapa, mobs, player1, player2);   // iniciamos o jogo
                main_game_single_player(linhas, colunas, mapa, game, player1, player2, mobs, flag, bullet_player1, bullet_player2); // damos update ao jogo
                clear();
                refresh();
                loop = 0;
                break;
            case 1: // Opção "Multiplayer"
                game->game_over = 0;
                clear();
                refresh();
                do_create_map(linhas, colunas, mapa, flag, game);
                start_game_multi_player(linhas, colunas, mapa, player1, player2);                                                                                                  // iniciamos o jogo
                main_game_multi_player(linhas, colunas, mapa, game, player1, player2, flag, mobs, bullet_player1, bullet_player2); // damos update ao jogo
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
void multi_scoreboard_win(int linhas, int colunas)
{
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20; // cordenadas iniciais
    WINDOW *win_jogo = newwin(20, 40, start_y, start_x);       // criação da janela desejada
    box(win_jogo, 0, 0);                                       // box à volta da janela
    refresh();
    wrefresh(win_jogo);

    int selected;
    int highlight = 0;
    int loop = 1; // variavel para o loop do jogo

    // opções do menu
    const char option1[30] = " -  MODO NORMAL   ";
    const char option2[30] = " -  MODO DIFICIl  ";

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
            case 0: // Opção scoreboard "Singleplayer"
                clear();
                refresh();
                sort_scoreboard();
                while (true)
                {
                    scoreboard(linhas, colunas); // inicia o scoreboard, caso o utilizador carregue no esc -> sair para o menu principal
                    char selected = getch();
                    if (selected == 27)
                        break;
                }
                clear();
                refresh();
                break;
            case 1: // Opção scoreboard "Multiplayer"
                clear();
                refresh();
                sort_scoreboard_desafio();
                while (true)
                {
                    scoreboard_desafio(linhas, colunas); // inicia o scoreboard, caso o utilizador carregue no esc -> sair para o menu principal
                    char selected = getch();
                    if (selected == 27)
                        break;
                }
                clear();
                refresh();
                break;
            }
        }
        if (selected == 27)
            loop = 0;
    }
}

void menu(int linhas, int colunas, Map mapa[][colunas], Mob *mobs, Game *game, Flag *flag, Bullet *bullet_player1, Bullet *bullet_player2, Player *player1, Player *player2)
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
            case 0:                                                                                                                                             // Opção "COMECAR NOVO JOGO!"
                multi_jogo_win(linhas, colunas, mapa, mobs, game, flag, bullet_player1, bullet_player2, player1, player2); // inicia a janela de singleplayer/multiplayer
                break;
            case 1: // Opção "QUERO SER DESAFIADO :D"
                game->game_over = 0;
                clear();
                refresh();
                do_create_map(linhas, colunas, mapa, flag, game);
                start_game_challenge(linhas, colunas, mapa, player1, player2);                                                                                                  // iniciamos o jogo
                main_game_challenge(linhas, colunas, mapa, flag, game, player1, player2, mobs, bullet_player1, bullet_player2); // damos update ao jogo
                clear();
                refresh();
                break;
            case 2: // Opção "MANUAL DE INSTRUCOES"
                break;
            case 3: // Opção "SCOREBOARD!"
                multi_scoreboard_win(linhas, colunas);
                clear();
                refresh();
                break;
            case 4:       // Opção "EXIT GAME"
                loop = 0; // para sair do loop
                break;
            }
        }
    }
}

void final_0_score_win(int linhas, int colunas)
{

    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20; // cordenadas iniciais
    WINDOW *win_final = newwin(20, 40, start_y, start_x);      // criação da janela desejada
    box(win_final, 0, 0);                                      // box à volta da janela

    wattron(win_final, A_BOLD); // atributo bold on
    mvwprintw(win_final, 7, 5, "       0 PONTOS? LOSER!      ");
    wattroff(win_final, A_BOLD); // atributo bold off
    mvwprintw(win_final, 9, 5, "COM ESSA PONTUACAO NEM MERCES");
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

void final_win(int linhas, int colunas, int score)
{
    noecho();
    int start_y = linhas / 2 - 10, start_x = colunas / 2 - 20; // cordenadas iniciais
    WINDOW *win_final = newwin(20, 40, start_y, start_x);      // criação da janela desejada
    box(win_final, 0, 0);                                      // box à volta da janela

    FILE *file_score;                               // criação de um ficheito
    file_score = fopen("scoreboard_file.txt", "a"); // ficheiro ligado ao txt do scoreboard em mode de escrever (a de append)

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

    /*
    loop que irá escrever o nome para o ecrã como tambem apagar se necessário
    */
    for (int i = 0; i < 28;) // maximo de 28 caracteres
    {
        char selected = getch();
        if ((selected == 10) && (nome[0] != ' ')) // se a tecla selecionda for o enter -> acaba o loop
        {
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

    if (file_score != NULL)                          // caso o ficheiro seja null
        fprintf(file_score, "\n%s %d", nome, score); // imprime no ficheiro o nome e o score
    fclose(file_score);                              // fecha o ficheiro
}

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

