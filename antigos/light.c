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

//Light Variables


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
//Obstacle
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

//LIGHT//
for (collumn = 0; collumn <= 41 ; collumn++)
{
row=0;
   while (row<=161)
   {
   //Chooses The Spots Within A Certain Radius
   if 
   ((!((collumn == y-1)&&(row == x))) && (!((collumn == y-2)&&(row == x))) && (!((collumn == y-3)&&(row == x))) && (!((collumn == y-4)&&(row == x)))   // Upper Vertical Line
   && (!((collumn == y+1)&&(row == x))) && (!((collumn == y+2)&&(row == x))) && (!((collumn == y+3)&&(row == x))) && (!((collumn == y+4)&&(row == x))) // Lower Vertical Line
   && (!((collumn == y)&&(row == x-1))) && (!((collumn == y)&&(row == x-2))) && (!((collumn == y)&&(row == x-3))) && (!((collumn == y)&&(row == x-4))) && (!((collumn == y)&&(row == x-5))) && (!((collumn == y)&&(row == x-6))) && (!((collumn == y)&&(row == x-7))) // Left Horizontal Line
   && (!((collumn == y)&&(row == x+1))) && (!((collumn == y)&&(row == x+2))) && (!((collumn == y)&&(row == x+3))) && (!((collumn == y)&&(row == x+4))) && (!((collumn == y)&&(row == x+5))) && (!((collumn == y)&&(row == x+6))) && (!((collumn == y)&&(row == x+7)))// Right Horizontal Line 
   && (!((collumn == y-1)&&(row == x-1))) && (!((collumn == y-1)&&(row == x-2))) && (!((collumn == y-1)&&(row == x-3))) && (!((collumn == y-1)&&(row == x-4))) && (!((collumn == y-1)&&(row == x-5))) && (!((collumn == y-1)&&(row == x-6))) //y-1 Left Horizontal Line
   && (!((collumn == y-1)&&(row == x+1))) && (!((collumn == y-1)&&(row == x+2))) && (!((collumn == y-1)&&(row == x+3))) && (!((collumn == y-1)&&(row == x+4))) && (!((collumn == y-1)&&(row == x+5))) && (!((collumn == y-1)&&(row == x+6))) //y-1 Right Horizontal Line
   && (!((collumn == y+1)&&(row == x-1))) && (!((collumn == y+1)&&(row == x-2))) && (!((collumn == y+1)&&(row == x-3))) && (!((collumn == y+1)&&(row == x-4))) && (!((collumn == y+1)&&(row == x-5))) && (!((collumn == y+1)&&(row == x-6))) //y+1 Left Horizontal Line
   && (!((collumn == y+1)&&(row == x+1))) && (!((collumn == y+1)&&(row == x+2))) && (!((collumn == y+1)&&(row == x+3))) && (!((collumn == y+1)&&(row == x+4))) && (!((collumn == y+1)&&(row == x+5))) && (!((collumn == y+1)&&(row == x+6)))//y+1 Right Horizontal Line
   && (!((collumn == y-2)&&(row == x-1))) && (!((collumn == y-2)&&(row == x-2))) && (!((collumn == y-2)&&(row == x-3))) && (!((collumn == y-2)&&(row == x-4))) && (!((collumn == y-2)&&(row == x-5))) //y-2 Left Horizontal Line
   && (!((collumn == y-2)&&(row == x+1))) && (!((collumn == y-2)&&(row == x+2))) && (!((collumn == y-2)&&(row == x+3))) && (!((collumn == y-2)&&(row == x+4))) && (!((collumn == y-2)&&(row == x+5)))//y-2 Right Horizontal Line
   && (!((collumn == y+2)&&(row == x-1))) && (!((collumn == y+2)&&(row == x-2))) && (!((collumn == y+2)&&(row == x-3))) && (!((collumn == y+2)&&(row == x-4))) && (!((collumn == y+2)&&(row == x-5)))//y+2 Left Horizontal Line
   && (!((collumn == y+2)&&(row == x+1))) && (!((collumn == y+2)&&(row == x+2))) && (!((collumn == y+2)&&(row == x+3))) && (!((collumn == y+2)&&(row == x+4))) && (!((collumn == y+2)&&(row == x+5))) //y+2 Right Horizontal Line
   && (!((collumn == y-3)&&(row == x-1))) && (!((collumn == y-3)&&(row == x-2))) && (!((collumn == y-3)&&(row == x-3))) && (!((collumn == y-3)&&(row == x-4)))//y-3 Left Horizontal Line
   && (!((collumn == y-3)&&(row == x+1))) && (!((collumn == y-3)&&(row == x+2))) && (!((collumn == y-3)&&(row == x+3))) && (!((collumn == y-3)&&(row == x+4)))//y-3 Right Horizontal Line
   && (!((collumn == y+3)&&(row == x-1))) && (!((collumn == y+3)&&(row == x-2))) && (!((collumn == y+3)&&(row == x-3))) && (!((collumn == y+3)&&(row == x-4)))//y+3 Left Horizontal Line
   && (!((collumn == y+3)&&(row == x+1))) && (!((collumn == y+3)&&(row == x+2))) && (!((collumn == y+3)&&(row == x+3))) && (!((collumn == y+3)&&(row == x+4))) //y+3 Right Horizontal Line
   && (!((collumn == y-4)&&(row == x-1))) && (!((collumn == y-4)&&(row == x-2))) //y-4 Left Horizontal Line
   && (!((collumn == y-4)&&(row == x+1))) && (!((collumn == y-4)&&(row == x+2))) //y-4 Right Horizontal Line
   && (!((collumn == y+4)&&(row == x-1))) && (!((collumn == y+4)&&(row == x-2))) //y+4 Left Horizontal Line
   && (!((collumn == y+4)&&(row == x+1))) && (!((collumn == y+4)&&(row == x+2)))//y+4 Right Horizontal Line
   )
   {
      mvaddch(collumn,row,'?'); 
   } 
   row++;
   }
}
/////////

mvaddch(y,x,player);//Puts Player In Initial Position

//Movement Function
while ((playerMovement = getch()) != 27) //While Player Movement Input Is Not ESC
{
//MAP///////////////////////////////////////////////////////////////////
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
//Obstacle
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

////////////////////////////////////////////////////////////////////////
    if (playerMovement == KEY_UP) 
    {
        if (((createdMap[y-1][x])=='.') || ((createdMap[y-1][x])=='~')) //To Prevent Player From Going Inside Walls/LightHouse
        {
            y--;
        }
    }
    else if (playerMovement == KEY_DOWN)
    {
       if (((createdMap[y+1][x])=='.') || ((createdMap[y+1][x])=='~'))
        {
            y++;
        }
    }
    else if (playerMovement == KEY_LEFT)
    {
        if (((createdMap[y][x-1])=='.') || ((createdMap[x-1][x])=='~'))
        {
            x--;
        }
    }
    else if (playerMovement == KEY_RIGHT)
    {
       if (((createdMap[y][x+1])=='.') || ((createdMap[y][x+1])=='~'))
        {
            x++;
        }    
    }
//LIGHT//
for (collumn = 0; collumn <= 41 ; collumn++)
{
row=0;
   while (row<=161)
   {
   //Chooses The Spots Within A Certain Radius
   if 
   ((!((collumn == y-1)&&(row == x))) && (!((collumn == y-2)&&(row == x))) && (!((collumn == y-3)&&(row == x))) && (!((collumn == y-4)&&(row == x)))   // Upper Vertical Line
   && (!((collumn == y+1)&&(row == x))) && (!((collumn == y+2)&&(row == x))) && (!((collumn == y+3)&&(row == x))) && (!((collumn == y+4)&&(row == x))) // Lower Vertical Line
   && (!((collumn == y)&&(row == x-1))) && (!((collumn == y)&&(row == x-2))) && (!((collumn == y)&&(row == x-3))) && (!((collumn == y)&&(row == x-4))) && (!((collumn == y)&&(row == x-5))) && (!((collumn == y)&&(row == x-6))) && (!((collumn == y)&&(row == x-7))) // Left Horizontal Line
   && (!((collumn == y)&&(row == x+1))) && (!((collumn == y)&&(row == x+2))) && (!((collumn == y)&&(row == x+3))) && (!((collumn == y)&&(row == x+4))) && (!((collumn == y)&&(row == x+5))) && (!((collumn == y)&&(row == x+6))) && (!((collumn == y)&&(row == x+7)))// Right Horizontal Line 
   && (!((collumn == y-1)&&(row == x-1))) && (!((collumn == y-1)&&(row == x-2))) && (!((collumn == y-1)&&(row == x-3))) && (!((collumn == y-1)&&(row == x-4))) && (!((collumn == y-1)&&(row == x-5))) && (!((collumn == y-1)&&(row == x-6))) //y-1 Left Horizontal Line
   && (!((collumn == y-1)&&(row == x+1))) && (!((collumn == y-1)&&(row == x+2))) && (!((collumn == y-1)&&(row == x+3))) && (!((collumn == y-1)&&(row == x+4))) && (!((collumn == y-1)&&(row == x+5))) && (!((collumn == y-1)&&(row == x+6))) //y-1 Right Horizontal Line
   && (!((collumn == y+1)&&(row == x-1))) && (!((collumn == y+1)&&(row == x-2))) && (!((collumn == y+1)&&(row == x-3))) && (!((collumn == y+1)&&(row == x-4))) && (!((collumn == y+1)&&(row == x-5))) && (!((collumn == y+1)&&(row == x-6))) //y+1 Left Horizontal Line
   && (!((collumn == y+1)&&(row == x+1))) && (!((collumn == y+1)&&(row == x+2))) && (!((collumn == y+1)&&(row == x+3))) && (!((collumn == y+1)&&(row == x+4))) && (!((collumn == y+1)&&(row == x+5))) && (!((collumn == y+1)&&(row == x+6)))//y+1 Right Horizontal Line
   && (!((collumn == y-2)&&(row == x-1))) && (!((collumn == y-2)&&(row == x-2))) && (!((collumn == y-2)&&(row == x-3))) && (!((collumn == y-2)&&(row == x-4))) && (!((collumn == y-2)&&(row == x-5))) //y-2 Left Horizontal Line
   && (!((collumn == y-2)&&(row == x+1))) && (!((collumn == y-2)&&(row == x+2))) && (!((collumn == y-2)&&(row == x+3))) && (!((collumn == y-2)&&(row == x+4))) && (!((collumn == y-2)&&(row == x+5)))//y-2 Right Horizontal Line
   && (!((collumn == y+2)&&(row == x-1))) && (!((collumn == y+2)&&(row == x-2))) && (!((collumn == y+2)&&(row == x-3))) && (!((collumn == y+2)&&(row == x-4))) && (!((collumn == y+2)&&(row == x-5)))//y+2 Left Horizontal Line
   && (!((collumn == y+2)&&(row == x+1))) && (!((collumn == y+2)&&(row == x+2))) && (!((collumn == y+2)&&(row == x+3))) && (!((collumn == y+2)&&(row == x+4))) && (!((collumn == y+2)&&(row == x+5))) //y+2 Right Horizontal Line
   && (!((collumn == y-3)&&(row == x-1))) && (!((collumn == y-3)&&(row == x-2))) && (!((collumn == y-3)&&(row == x-3))) && (!((collumn == y-3)&&(row == x-4)))//y-3 Left Horizontal Line
   && (!((collumn == y-3)&&(row == x+1))) && (!((collumn == y-3)&&(row == x+2))) && (!((collumn == y-3)&&(row == x+3))) && (!((collumn == y-3)&&(row == x+4)))//y-3 Right Horizontal Line
   && (!((collumn == y+3)&&(row == x-1))) && (!((collumn == y+3)&&(row == x-2))) && (!((collumn == y+3)&&(row == x-3))) && (!((collumn == y+3)&&(row == x-4)))//y+3 Left Horizontal Line
   && (!((collumn == y+3)&&(row == x+1))) && (!((collumn == y+3)&&(row == x+2))) && (!((collumn == y+3)&&(row == x+3))) && (!((collumn == y+3)&&(row == x+4))) //y+3 Right Horizontal Line
   && (!((collumn == y-4)&&(row == x-1))) && (!((collumn == y-4)&&(row == x-2))) //y-4 Left Horizontal Line
   && (!((collumn == y-4)&&(row == x+1))) && (!((collumn == y-4)&&(row == x+2))) //y-4 Right Horizontal Line
   && (!((collumn == y+4)&&(row == x-1))) && (!((collumn == y+4)&&(row == x-2))) //y+4 Left Horizontal Line
   && (!((collumn == y+4)&&(row == x+1))) && (!((collumn == y+4)&&(row == x+2)))//y+4 Right Horizontal Line
   )
   {
      mvaddch(collumn,row,'?'); 
   } 
   row++;
   }
}
/////////
mvaddch(y,x,player); //Updates The Player Position and The Map After Every Cycle
}

refresh();
endwin();
return 0;
}







