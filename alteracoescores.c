// cores no menu, cenas do multiplayer e tal e no socreboard (este ainda n ta direito)


void scoreboard(int linhas, int colunas) 
{
    WINDOW *win_score = newwin(linhas - 2, colunas - 4, 1, 2);
    box(win_score, 0, 0);

    FILE *file_score;
    file_score = fopen("scoreboard_file.txt", "r");

    char name[100];
    int score;
    int i = 0;

    start_color(); // inicializa as cores
    init_pair(7, 19, 16);           // par de cores para a borda do menu com azul médio------ n ta a ser usada 
    init_pair(8, 19, 17);           // AZUL claro FUNDO E letras brancas
    init_pair(9, 17, 18);           // AZUL muito CLARO FUNDO E BORDA AZUL claro
    wbkgd(win_score, 16);            // define o fundo da janela como azul muito claro

    if (file_score != NULL)
    {
        while (fscanf(file_score, "%s %d", name, &score) != EOF)
        {
            if (i % 2 == 0)
            {
                wattron(win_score, COLOR_PAIR(8) | A_BOLD | A_REVERSE); // LETRA DO BOT SELECIONADA
                wbkgd(win_score, COLOR_PAIR(9));
                for (int j = 0; j < colunas - 6; j++)
                {
                    mvwprintw(win_score, i + 1, j + 1, " ");
                }
                mvwprintw(win_score, i + 1, 1, "%s", name);
                int nDigits = floor(log10(abs(score))) + 1;
                mvwprintw(win_score, i + 1, colunas - 5 - nDigits, "%d", score);
                wattron(win_score, COLOR_PAIR(8) | A_BOLD | A_REVERSE); // LETRA DO BOT SELECIONADA
                wbkgd(win_score, COLOR_PAIR(9));
            }
            else
            {
                mvwprintw(win_score, i + 1, 1, "%s", name);
                int nDigits = floor(log10(abs(score))) + 1;
                mvwprintw(win_score, i + 1, colunas - 5 - nDigits, "%d", score);
            }
            i++;
        }
    } 
    wattroff(win_score, COLOR_PAIR(9) | COLOR_PAIR(9) | A_BOLD | A_REVERSE);
    wbkgd(win_score, COLOR_PAIR(9) | A_NORMAL);

    fclose(file_score);
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
    init_pair(8, 19, 17); 
    wattron(win_jogo, COLOR_PAIR(8));
    box(win_jogo, 0, 0);
    wbkgd(win_jogo, COLOR_PAIR(7));         // box à volta da janela
    refresh();
    wrefresh(win_jogo);

    keypad(win_jogo, true); // ativa o keypad

    //opções do menu
    const char option1[30] = " - SINGLEPLAYER   ";
    const char option2[30] = " - MULTIPLAYER    ";
    int selected;
    int highlight = 0;
    int loop = 1; // variavel para o loop do jogo

    start_color(); // inicializa as cores
    init_pair(7, 19, 16);           // borda menu
    init_pair(8, 19, 17);           // AZUL MEDIO FUNDO DAS CORES E BRANCO LETRAS
    init_pair(9, 17, 18);           // AZUL CLARO FUNDO E BORDA AZUL MEDIO 
    wbkgd(win_jogo, 16);                 // define o fundo daa janela como azul

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
            if (i == highlight) {
                wattron(win_jogo, COLOR_PAIR(8) | A_BOLD | A_REVERSE); // LETRA DO BOT SELECIONADA
                wbkgd(win_jogo, COLOR_PAIR(9));
            }
            else {
                wattron(win_jogo, COLOR_PAIR(8)); // FUNDO DE QUANDO SELEC O BOTAO
                wbkgd(win_jogo, COLOR_PAIR(9));
            }
        
            switch (i)
            {
            case 0:
                mvwprintw(win_jogo, 8 + i, 10, option1);
                break;
            case 1:
                mvwprintw(win_jogo, 9 + i, 10, option2);
                break;
            }
            wattroff(win_jogo, COLOR_PAIR(9) | COLOR_PAIR(9) | A_BOLD | A_REVERSE);
            wbkgd(win_jogo, COLOR_PAIR(9) | A_NORMAL);
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
            loop = 0; }
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
    WINDOW *win = newwin(20, 40, start_y, start_x);  //  mudar algo no 20, 40 para o fundo ficar do tamanho do ecra
    wattron(win, COLOR_PAIR(8));
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(7));
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

    start_color(); // inicializa as cores
    init_pair(7, 19, 16);           // borda menu --------------------------------------------
    init_pair(8, 19, 17);           // AZUL MEDIO FUNDO DAS CORES E BRANCO LETRAS
    init_pair(9, 17, 18);           // AZUL CLARO FUNDO E BORDA AZUL MEDIO 
    wbkgd(win, 16);                 // define o fundo daa janela como azul


    /*
    Loop while que verifica a tecla que o utlizador clica e faz o highlight da opção desejada.
    Este tambem imprime todas as opções do menu para a janela.
    No entanto, não deixa o utilizador dar highlight em algo que não é suposto.
    Para concluir o loop acaba assim que o utilizador carregue na tecla enter para escolher a sua opção (loop = 0)
    */
    while (loop == 1)
    {
        box(win, 0, 0);
        // init_pair(8, 19, 17); 
        wborder(win, '\u2585', '\u2585', '\u2585', '\u2585', '+', '+', '+', '+');
        // wbkgd(win, COLOR_PAIR(8) | A_NORMAL);
        for (int i = 0; i < 5; i++)
        {
            if (i == highlight) {
                wattron(win, COLOR_PAIR(8) | A_BOLD | A_REVERSE); // LETRA DO BOT SELECIONADA
                wbkgd(win, COLOR_PAIR(9));
            }
            else {
                wattron(win, COLOR_PAIR(8)); // FUNDO DE QUANDO SELEC O BOTAO
                wbkgd(win, COLOR_PAIR(9));
            }

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
            wattroff(win, COLOR_PAIR(9) | COLOR_PAIR(9) | A_BOLD | A_REVERSE);
            wbkgd(win, COLOR_PAIR(9) | A_NORMAL);

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
            case 2: // Opção "MANUAL DE INSTRUCOES"  -----------------------------  FAZER 
                break;
            case 3: // Opção "SCOREBOARD!"
                while (true)
                {
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
    // cores para o menu 
    init_color(16, 21, 546, 994);   // azul médio
    init_color(17, 596, 795, 994);  // Azul claro
    init_color(18, 897, 943, 994);  // Azul claríssimo
    init_color(19, 994, 994, 994);
    /* init_pair(7, 16, 19);           // borda menu
    init_pair(8, 17, 19);           // fundo menu
    init_pair(9, 18, 19);           // bot selec menu */ //posso apagar pq acho q n ta aqui a fazer nada??????????????????????????
    menu(linhas, colunas, mapa);

    clear(); // faz clear no terminal

    endwin();

    return 0;
}
