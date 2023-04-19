#include<stdio.h>
#include<ncurses.h>

int main()
{
initscr();

//Removes Blinking From Cursor
curs_set(0);

//Hides User Input
noecho();

//To Be Able To Use Arrows
keypad(stdscr, 1);

//Input Of Player Movement 
int playerMovement;

//Initial Position & Coords
int y=20;  //Vertical
int x=80;   //Horizontal

//Player Representation
char player='@';

//For The Map
char createdMap[42][162]; // Map Size
int collumn=0; 
int row=0;

//Without This The Game Starts Blank And Only Appears After One Movement Is Applied//////////////////////
//MAP/////////////////////////////////////(REMEMBER: Y first and X second)
//Borders & Filling
while (row<=161)//Upper & Bottom Horizontal Line
{
   mvaddch(0,row,'#');
   mvaddch(41,row,'#');
   createdMap[0][row]='#';
   createdMap[41][row]='#';
   row++;
}
while (collumn<=41)//Left & Right Vertical Line
{
   mvaddch(collumn,0,'#');
   mvaddch(collumn,161,'#');
   createdMap[collumn][0]='#';
   createdMap[collumn][161]='#';
   collumn++;
}
for (collumn = 1; collumn <= 40; collumn++)
{
row=1;
while (row<=160)
{
   mvaddch(collumn,row,'.');
   createdMap[collumn][row]='.';
   row++;
}
}
//First Obstacle
for (row = 9; row <= 9; row++)
{
   mvaddch(10,row,'#');
   createdMap[10][row]='#';
}
for (row = 9; row <= 11; row++)
{
   mvaddch(9,row,'#');
   createdMap[9][row]='#';
}
for (row = 6; row <= 12; row++)
{
   mvaddch(8,row,'#');
   createdMap[8][row]='#';
}
for (row = 4; row <= 13; row++)
{
   mvaddch(7,row,'#');
   createdMap[7][row]='#';
}
for (row = 8; row <= 12; row++)
{
   mvaddch(6,row,'#');
   createdMap[6][row]='#';
}
for (row = 9; row <= 12; row++)
{
   mvaddch(5,row,'#');
   createdMap[5][row]='#';
}
for (row = 11; row <= 12; row++)
{
   mvaddch(4,row,'#');
   createdMap[4][row]='#';
}
///////////////////////////////////////////////
mvaddch(y,x,player);//Puts Player In Initial Position
////////////////////////////////////////////////////////////////////////////////////////////////////////

//Movement Function
while ((playerMovement = getch()) != 27) //While Player Movement Input Is Not ESC
{
//MAP/////////////////////////////////////
collumn=0;
row=0;
//Borders & Filling
while (row<=161)//Upper & Bottom Horizontal Line
{
   mvaddch(0,row,'#');
   mvaddch(41,row,'#');
   createdMap[0][row]='#';
   createdMap[41][row]='#';
   row++;
}
while (collumn<=41)//Left & Right Vertical Line
{
   mvaddch(collumn,0,'#');
   mvaddch(collumn,161,'#');
   createdMap[collumn][0]='#';
   createdMap[collumn][161]='#';
   collumn++;
}
for (collumn = 1; collumn <= 40; collumn++)
{
row=1;
while (row<=160)
{
   mvaddch(collumn,row,'.');
   createdMap[collumn][row]='.';
   row++;
}
}
//First Obstacle
for (row = 9; row <= 9; row++)
{
   mvaddch(10,row,'#');
   createdMap[10][row]='#';
}
for (row = 9; row <= 11; row++)
{
   mvaddch(9,row,'#');
   createdMap[9][row]='#';
}
for (row = 6; row <= 12; row++)
{
   mvaddch(8,row,'#');
   createdMap[8][row]='#';
}
for (row = 4; row <= 13; row++)
{
   mvaddch(7,row,'#');
   createdMap[7][row]='#';
}
for (row = 8; row <= 12; row++)
{
   mvaddch(6,row,'#');
   createdMap[6][row]='#';
}
for (row = 9; row <= 12; row++)
{
   mvaddch(5,row,'#');
   createdMap[5][row]='#';
}
for (row = 11; row <= 12; row++)
{
   mvaddch(4,row,'#');
   createdMap[4][row]='#';
}
///////////////////////////////////////////////
//Player Will Move According To The Arrow Pressed 
    if (playerMovement == KEY_UP) 
    {
        if ((createdMap[y-1][x])!='#') //To Prevent Player From Going Inside Walls/LightHouse
        {
            y--;
        }
    }
    else if (playerMovement == KEY_DOWN)
    {
       if ((createdMap[y+1][x])!='#')
        {
            y++;
        }
    }
    else if (playerMovement == KEY_LEFT)
    {
        if ((createdMap[y][x-1])!='#')
        {
            x--;
        }
    }
    else if (playerMovement == KEY_RIGHT)
    {
       if ((createdMap[y][x+1])!='#')
        {
            x++;
        }    
    }
mvaddch(y,x,player); //Updates The Player Position and The Map After Every Cycle
}

refresh();
endwin();
return 0;
}














//MAPA PEQUENO CONSTRUIDO À MÃO
/*
mvaddch(0,0,'#'); createdMap[0][0] ='#';
mvaddch(0,1,'#'); createdMap[0][1] ='#';
mvaddch(0,2,'#'); createdMap[0][2] ='#';
mvaddch(0,3,'#'); createdMap[0][3] ='#';
mvaddch(0,4,'#'); createdMap[0][4] ='#';
mvaddch(0,5,'#'); createdMap[0][5] ='#';
mvaddch(0,6,'#'); createdMap[0][6] ='#';
mvaddch(1,0,'#'); createdMap[1][0] ='#';
mvaddch(1,1,'.'); createdMap[1][1] ='.';
mvaddch(1,2,'.'); createdMap[1][2] ='.';
mvaddch(1,3,'.'); createdMap[1][3] ='.';
mvaddch(1,4,'.'); createdMap[1][4] ='.';
mvaddch(1,5,'#'); createdMap[1][5] ='#';
mvaddch(1,6,'#'); createdMap[1][6] ='#';
mvaddch(2,0,'#'); createdMap[2][0] ='#';
mvaddch(2,1,'.'); createdMap[2][1] ='.';
mvaddch(2,2,'!'); createdMap[2][2] ='.';
mvaddch(2,3,'.'); createdMap[2][3] ='.';
mvaddch(2,4,'#'); createdMap[2][4] ='#';
mvaddch(2,5,'#'); createdMap[2][5] ='#';
mvaddch(2,6,'#'); createdMap[2][6] ='#';
mvaddch(3,0,'#'); createdMap[3][0] ='#';
mvaddch(3,1,'.'); createdMap[3][1] ='.';
mvaddch(3,2,'.'); createdMap[3][2] ='.';
mvaddch(3,3,'.'); createdMap[3][3] ='.';
mvaddch(3,4,'.'); createdMap[3][4] ='.';
mvaddch(3,5,'.'); createdMap[3][5] ='.';
mvaddch(3,6,'#'); createdMap[3][6] ='#';
mvaddch(4,0,'#'); createdMap[4][0] ='#';
mvaddch(4,1,'.'); createdMap[4][1] ='.';
mvaddch(4,2,'~'); createdMap[4][2] ='~';
mvaddch(4,3,'.'); createdMap[4][3] ='.';
mvaddch(4,4,'.'); createdMap[4][4] ='.';
mvaddch(4,5,'.'); createdMap[4][5] ='.';
mvaddch(4,6,'#'); createdMap[4][6] ='#';
mvaddch(5,0,'#'); createdMap[5][0] ='#';
mvaddch(5,1,'.'); createdMap[5][1] ='.';
mvaddch(5,2,'~'); createdMap[5][2] ='~';
mvaddch(5,3,'~'); createdMap[5][3] ='~';
mvaddch(5,4,'~'); createdMap[5][4] ='~';
mvaddch(5,5,'~'); createdMap[5][5] ='~';
mvaddch(5,6,'#'); createdMap[5][6] ='#';
mvaddch(6,0,'#'); createdMap[6][0] ='#';
mvaddch(6,1,'#'); createdMap[6][1] ='#';
mvaddch(6,2,'#'); createdMap[6][2] ='#';
mvaddch(6,3,'#'); createdMap[6][3] ='#';
mvaddch(6,4,'#'); createdMap[6][4] ='#';
mvaddch(6,5,'#'); createdMap[6][5] ='#';
mvaddch(6,6,'#'); createdMap[6][6] ='#';
*/