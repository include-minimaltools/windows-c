

#include <stdio.h>
#include <bmp256.h>

#include <conio.h>
#include <Registro.H>
/**/
#include <Windows.h>
/**
#include <mouse.h>
/**/
#define flag  11
#define cover 10
#define mine  9
#define eight 8
#define seven 7
#define six   6
#define five  5
#define four  4
#define three 3
#define two   2
#define one   1
#define none  0

#define lose   3
#define win    2
#define inGame 1
#define pause  0

#define duration 33

#define true  1
#define false 0

#define mineunseen -1
#define unseen      0
#define seen        1

typedef struct Minesweeper_Attributes
{
    int isMenuActive;
    int isMenuPainting;
    int x, y;
    int mineLimit;
    int width;
    int high;
    int status;
    int visible;
    int map[20][20];
    int show[20][20];
    int flags[20][20];
} MinesweeperAttributes;

typedef struct Form_Windows
{
    int visible;
}FormWindowsAttributes;

void showcell(int Row, int Column, int x_init, int y_init,int Mode);
void Desktop(void);
void remap(void);
void newgame(int x, int y);
void loadgame(void);
void formMinesweeper(int x, int y);
void icon(int x, int y, char *name);
void MainEvent(void);
void eventMinesweeper(int x, int y, int click);
void formWindow(void);

MinesweeperAttributes minesweeper;
FormWindowsAttributes windowhome;

int i,j;
void main()
{
    TurnOn();
    Desktop();
    minesweeper.x     = 0;
    minesweeper.y     = 0;
    minesweeper.width = 20;
    minesweeper.high  = 5;
    minesweeper.mineLimit = 13;
    /**/
    MainEvent();
    /**/
    getch();
    
}

void newgame(int x, int y)
{
    mocultar();
    for(i = 0; i < minesweeper.high; i++)  for(j = 0; j < minesweeper.width; j++)
        showcell(i,j,15+x,120+y,cover);

    setfillstyle(SOLID_FILL,YELLOW);
    setlinestyle(SOLID_LINE,0,1);
    setcolor(BLACK);
    fillellipse(14+ (21*minesweeper.width)/2 + x,74+y,11,11);
    circle(14+ (21*minesweeper.width)/2 + x,74+y,11);
    arc(14+ (21*minesweeper.width)/2 + x,74+y,200,340,6);
    setfillstyle(SOLID_FILL,BLACK);
    fillellipse(10+ (21*minesweeper.width)/2 + x,71+y,1,1);
    fillellipse(18+ (21*minesweeper.width)/2 + x,71+y,1,1);
    mver();

    remap();
    minesweeper.status = inGame;
}

void remap(void)
{
    int value,mineCount=1;

    for (i = 0; i < 20; i++) for (j = 0; j < 20; j++)
    {
        minesweeper.map[i][j]=0;
        minesweeper.show[i][j]=0;
        minesweeper.flags[i][j]=0;
    }
    for (i = 0; i < minesweeper.high; i++) for (j = 0; j < minesweeper.width; j++)
    {
        value = 0;
        value += rand() % 4;
        if(mineCount <= minesweeper.mineLimit && value == 1)
        {
            minesweeper.map[i][j]  = mine;
            minesweeper.show[i][j] = mineunseen;
            mineCount++;
            
            if (j > 0)
                minesweeper.map[i][j-1]   = minesweeper.map[i][j-1]   == mine ? mine :  minesweeper.map[i][j-1]   + 1;

            if (j < minesweeper.width-1)
                minesweeper.map[i][j+1]   = minesweeper.map[i][j+1]   == mine ? mine :  minesweeper.map[i][j+1]   + 1;

            if (i > 0 && j > 0)
                minesweeper.map[i-1][j-1] = minesweeper.map[i-1][j-1] == mine ? mine :  minesweeper.map[i-1][j-1] + 1;

            if (i > 0)
                minesweeper.map[i-1][j]   = minesweeper.map[i-1][j]   == mine ? mine :  minesweeper.map[i-1][j]   + 1;

            if (i > 0 && j < minesweeper.width-1)
                minesweeper.map[i-1][j+1] = minesweeper.map[i-1][j+1] == mine ? mine :  minesweeper.map[i-1][j+1] + 1;

            if (i < minesweeper.high-1 && j > 0)
                minesweeper.map[i+1][j-1] = minesweeper.map[i+1][j-1] == mine ? mine :  minesweeper.map[i+1][j-1] + 1;

            if (i < minesweeper.high-1)
                minesweeper.map[i+1][j]   = minesweeper.map[i+1][j]   == mine ? mine :  minesweeper.map[i+1][j]   + 1;

            if (i < minesweeper.high-1 && j < minesweeper.width-1)
                minesweeper.map[i+1][j+1] = minesweeper.map[i+1][j+1] == mine ? mine :  minesweeper.map[i+1][j+1] + 1;
        }
    }
}

void loadgame(void)
{
    mocultar();
    for (i = 0; i < minesweeper.high; i++) for (j = 0; j < minesweeper.width; j++)
    {
        if(minesweeper.flags[i][j]==true)
            showcell(i,j,minesweeper.x+15,minesweeper.y+120,flag);
        else if(minesweeper.show[i][j]==seen && minesweeper.flags[i][j]==false)
            showcell(i,j,minesweeper.x+15,minesweeper.y+120,minesweeper.map[i][j]);
        else
            showcell(i,j,minesweeper.x+15,minesweeper.y+120,cover);
    }
    setfillstyle(SOLID_FILL,YELLOW);
    setlinestyle(SOLID_LINE,0,1);
    setcolor(BLACK);
    fillellipse(14+ (21*minesweeper.width)/2 + minesweeper.x,74+minesweeper.y,11,11);
    circle(14+ (21*minesweeper.width)/2 + minesweeper.x,74+minesweeper.y,11);
    arc(14+ (21*minesweeper.width)/2 + minesweeper.x,74+minesweeper.y,200,340,6);
    setfillstyle(SOLID_FILL,BLACK);
    fillellipse(10+ (21*minesweeper.width)/2 + minesweeper.x,71+minesweeper.y,1,1);
    fillellipse(18+ (21*minesweeper.width)/2 + minesweeper.x,71+minesweeper.y,1,1);
    mver();
}

void eventMinesweeper(int x, int y, int click)
{
    int exposed = 0, row = -1, column = -1, xPast, yPast;

    if(mclick()== 1 && mxpos(1)>9+(21*minesweeper.width)+x && mypos(1)>5+y && mxpos(1) < 24+x+(21*minesweeper.width) && mypos(1) < 20+y)
    {
        minesweeper.visible=false;
        minesweeper.status =pause;
        mocultar();
        setfillstyle(SOLID_FILL,BLACK);
        bar(0+x, 0+y, 29+(21*minesweeper.width)+x, 134+(21*minesweeper.high)+y);
        mver();
        return;
    }
    /**/
    if(mclick()==1 && mxpos(1)>2+x && mypos(1)>2+y && mxpos(1)<27+(21*minesweeper.width)+x && mypos(1)<24+y)
    {
        xPast = mxpos(1);
        yPast = mypos(1);
        do 
        {
            
            if((xPast != mxpos(1) || yPast != mypos(1)))
            {
                mocultar();
                setfillstyle(SOLID_FILL,BLACK);
                bar(0+minesweeper.x, 0+minesweeper.y, 29+(21*minesweeper.width)+minesweeper.x, 134+(21*minesweeper.high)+minesweeper.y);
                minesweeper.x += (mxpos(1) - xPast);
                minesweeper.y += (mypos(1) - yPast);
                formMinesweeper(minesweeper.x,minesweeper.y);
                mver();

                xPast = mxpos(1);
                yPast = mypos(1);
            }
        }
        while (mclick()==1);
        loadgame();
        return;
    }
    /**/
    

    if(minesweeper.status==inGame)
    {
        for(i = 0; i < minesweeper.width; i++)
            if (mxpos(1) > (i*21)+15+x && mxpos(1) < (i*21)+36+x)
                column = i;

    
        for(i = 0; i < minesweeper.high; i++)
            if (mypos(1) > (i*21)+120+y && mypos(1) < (i*21)+141+y)
                row = i;
    }
    
    while(mclick()!=0);

    if(minesweeper.status == inGame && column != -1 && row != -1)
    {
        mocultar();
        if(click==1 && minesweeper.flags[row][column]==false)
            showcell(row,column,x+15,y+120,minesweeper.map[row][column]);
        else if (click==2 && minesweeper.show[row][column]!=seen)
            showcell(row,column,x+15,y+120,flag);
        mver();

        for(i = 0; i < minesweeper.high; i++) for (j = 0; j < minesweeper.width; j++) if (minesweeper.show[i][j] == seen || minesweeper.show[i][j] == mineunseen)
            exposed++;

        if (exposed == (minesweeper.width * minesweeper.high) || minesweeper.status==win)
        {
            setfillstyle(SOLID_FILL,YELLOW);
            setlinestyle(SOLID_LINE,0,1);
            setcolor(BLACK);
            fillellipse(14+ (21*minesweeper.width)/2 + x,74+y,11,11);
            circle(14+ (21*minesweeper.width)/2 + x,74+y,11);
            line(5+ (21*minesweeper.width)/2 + x,69+y,23+ (21*minesweeper.width)/2 + x,69+y);
            line(6+ (21*minesweeper.width)/2 + x,70+y,12+ (21*minesweeper.width)/2 + x,70+y);
            line(16+ (21*minesweeper.width)/2 + x,70+y,22+ (21*minesweeper.width)/2 + x,70+y);
            line(7+ (21*minesweeper.width)/2 + x,71+y,11+ (21*minesweeper.width)/2 + x,71+y);
            line(17+ (21*minesweeper.width)/2 + x,71+y,21+ (21*minesweeper.width)/2 + x,71+y);
            line(8+ (21*minesweeper.width)/2 + x,72+y,10+ (21*minesweeper.width)/2 + x,72+y);
            line(17+ (21*minesweeper.width)/2 + x,72+y,20+ (21*minesweeper.width)/2 + x,72+y);
            arc(14+ (21*minesweeper.width)/2 + x,74+y,200,340,6);

            while(mclick()==0);
            newgame(minesweeper.x,minesweeper.y);
            while(mclick()==1);
        }
        if(minesweeper.status == lose)
        {
            setfillstyle(SOLID_FILL,YELLOW);
            setlinestyle(SOLID_LINE,0,1);
            setcolor(BLACK);
            fillellipse(14+ (21*minesweeper.width)/2 + x,74+y,11,11);
            circle(14+ (21*minesweeper.width)/2 + x,74+y,11);
            line(8+ (21*minesweeper.width)/2 + x,69+y,12+ (21*minesweeper.width)/2 + x,73+y);
            line(12+ (21*minesweeper.width)/2 + x,69+y,8+ (21*minesweeper.width)/2 + x,73+y);
            line(16+(21*minesweeper.width)/2 + x,69+y,20+ (21*minesweeper.width)/2 + x,73+y);
            line(20+ (21*minesweeper.width)/2 + x,69+y,16+ (21*minesweeper.width)/2 + x,73+y);
            arc(14 + (21*minesweeper.width)/2 + x,82+y,20,160,6);
            
            
            while(mclick()==0);
            newgame(minesweeper.x,minesweeper.y);
            while(mclick()==1);
        }
    }
}

void autoshow(int Row, int Column, int x, int y,int number)
{
    int mines=0;

    if (Column > 0                                                      && minesweeper.flags[Row][Column-1]   == true) mines++;

    if (Column < minesweeper.width-1                                    && minesweeper.flags[Row][Column+1]   == true) mines++;
        
    if (Row > 0                         && Column > 0                   && minesweeper.flags[Row-1][Column-1] == true) mines++;

    if (Row > 0                                                         && minesweeper.flags[Row-1][Column]   == true) mines++;

    if (Row > 0                         && Column < minesweeper.width-1 && minesweeper.flags[Row-1][Column+1] == true) mines++;
    
    if (Row < minesweeper.high-1        && Column > 0                   && minesweeper.flags[Row+1][Column-1] == true) mines++;
    
    if (Row < minesweeper.high-1                                        && minesweeper.flags[Row+1][Column]   == true) mines++;

    if (Row < minesweeper.high-1        && Column < minesweeper.width-1 && minesweeper.flags[Row+1][Column+1] == true) mines++;

    if(mines >= number)
    {
        if (Column > 0                                      && minesweeper.show[Row][Column-1 ]!= seen   && minesweeper.flags[Row][Column-1]==false)
        {
            minesweeper.show[Row][Column-1]=seen;
            showcell(Row,Column-1,x,y,minesweeper.map[Row][Column-1]);
        }
        if (Column < minesweeper.width-1                    && minesweeper.show[Row][Column+1] != seen   && minesweeper.flags[Row][Column+1]==false)
        {
            minesweeper.show[Row][Column+1]=seen;
            showcell(Row,Column+1,x,y,minesweeper.map[Row][Column+1]);
        }
        if (Row > 0 && Column > 0               && minesweeper.show[Row-1][Column-1] != seen && minesweeper.flags[Row-1][Column-1]==false)
        {
            minesweeper.show[Row-1][Column-1]=seen;
            showcell(Row-1,Column-1,x,y,minesweeper.map[Row-1][Column-1]);
        }
        if (Row > 0                             && minesweeper.show[Row-1][Column] != seen   && minesweeper.flags[Row-1][Column]==false)
        {
            minesweeper.show[Row-1][Column]=seen;
            showcell(Row-1,Column,x,y,minesweeper.map[Row-1][Column]);
        }
        if (Row > 0 && Column < minesweeper.width-1         && minesweeper.show[Row-1][Column+1] != seen && minesweeper.flags[Row-1][Column+1]==false)
        {
            minesweeper.show[Row-1][Column+1]=seen;
            showcell(Row-1,Column+1,x,y,minesweeper.map[Row-1][Column+1]);
        }
        if (Row < minesweeper.high-1 && Column > 0          && minesweeper.show[Row+1][Column-1] != seen && minesweeper.flags[Row+1][Column-1]==false)
        {
            minesweeper.show[Row+1][Column-1]=seen;
            showcell(Row+1,Column-1,x,y,minesweeper.map[Row+1][Column-1]);
        }
        if (Row < minesweeper.high-1                        && minesweeper.show[Row+1][Column] != seen   && minesweeper.flags[Row+1][Column]==false)
        {
            minesweeper.show[Row+1][Column]=seen;
            showcell(Row+1,Column,x,y,minesweeper.map[Row+1][Column]);
        }
        if (Row < minesweeper.high-1 && Column < minesweeper.width-1    && minesweeper.show[Row+1][Column+1] != seen && minesweeper.flags[Row+1][Column+1]==false)
        {
            minesweeper.show[Row+1][Column+1]=seen;
            showcell(Row+1,Column+1,x,y,minesweeper.map[Row+1][Column+1]);/**/
        }
    }
}

void showcell(int Row, int Column, int x_init, int y_init,int Mode)
{
    int x, y, exposed;
    x = x_init + (Column * 21);
    y = y_init + (Row    * 21);

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(0+x,0+y, 19+x,19+y);
    

    switch (Mode)
    {
        case eight:
        case seven:
        case six:
            setfillstyle(SOLID_FILL,BLACK);
            bar(8 +x,   3 +y,   11+x,   16+y);
            bar(3 +x,   8 +y,   16+x,   11+y);

            minesweeper.show[Row][Column]=seen;
            autoshow(Row,Column,x_init,y_init,Mode);
            break;

        case five:
            setfillstyle(SOLID_FILL,YELLOW);
            setcolor(YELLOW);    
            bar(15+x,   4 +y,   5 +x,   5 +y);
            bar(4 +x,   5 +y,   6 +x,   9 +y);
            bar(5 +x,   9 +y,   14+x,   10+y);
            bar(13+x,   10+y,   15+x,   14+y);
            bar(13+x,   14+y,   4 +x,   15+y);

            minesweeper.show[Row][Column]=seen;
            autoshow(Row,Column,x_init,y_init,Mode);
            break;

        case four:        
            setfillstyle(SOLID_FILL,MAGENTA);
            setcolor(MAGENTA);    
            bar(12+x,   3 +y,   14+x,   15+y);
            bar(16+x,   8 +y,   3 +x,   10+y);
            line(4+x,   7 +y,   8 +x,   3 +y);
            line(5+x,   7 +y,   9 +x,   3 +y);
            line(6+x,   7 +y,   9 +x,   4 +y);
            line(7+x,   7 +y,   9 +x,   5 +y);

            minesweeper.show[Row][Column]=seen;
            autoshow(Row,Column,x_init,y_init,Mode);
            break;
        case three:
            setfillstyle(SOLID_FILL,RED);
            setcolor(RED);
            bar(4 +x,   13+y,   15+x,   15+y);
            bar(14+x,   11+y,   16+x,   12+y);
            bar(8 +x,   8 +y,   12+x,   9 +y);
            bar(13+x,   7 +y,   15+x,   10+y);
            bar(14+x,   5 +y,   16+x,   6 +y);
            bar(15+x,   2 +y,   5 +x,   4 +y);

            line(4+x,   3 +y,   4 +x,   5+y);

            putpixel(   16+x,   3 +y,   RED);
            putpixel(   16+x,   14+y,   RED);

            minesweeper.show[Row][Column]=seen;
            autoshow(Row,Column,x_init,y_init,Mode);
            break;
        case two:
            setfillstyle(SOLID_FILL,GREEN);
            setcolor(GREEN);

            bar(15+x,   15+y,   4 +x,   13+y);
            bar(13+x,   4 +y,   15+x,   6 +y);
            bar(4 +x,   4 +y,   6 +x,   5 +y);

            line(4 +x,  12+y,   7+ x,   12+y);
            line(4 +x,  11+y,   8+ x,   11+y);
            line(5 +x,  10+y,   10+x,   10+y);
            line(7 +x,  9 +y,   12+x,   9+ y);
            line(10+x,  8 +y,   14+x,   8+ y);
            line(12+x,  7 +y,   15+x,   7+ y);
            line(15+x,  3 +y,   4+ x,   3+ y);
            line(5 +x,  2 +y,   14+x,   2+ y);

            minesweeper.show[Row][Column]=seen;
            autoshow(Row,Column,x_init,y_init,Mode);
            break;

        case one:
            setfillstyle(SOLID_FILL,BLUE);
            setcolor(LIGHTGRAY);

            bar(9 +x,   2 +y,   11+x,   15+y);
            bar(5 +x,   15+y,   15+x,   17+y);
            bar(9 +x,   2 +y,   5 +x,   6 +y);
        
            line(5+x,   5 +y,   9 +x,   1 +y);
            line(5+x,   4 +y,   9 +x,   0 +y);
            line(4+x,   4 +y,   8 +x,   0 +y);
            line(3+x,   4 +y,   7 +x,   0 +y);

            minesweeper.show[Row][Column]=seen;
            autoshow(Row,Column,x_init,y_init,Mode);
            break;

        case mine:
            setfillstyle(SOLID_FILL,RED);
            bar(0 +x,   0 +y,   19+x,   19+y);
            setfillstyle(SOLID_FILL,BLACK);
            setcolor(BLACK);
            icon(x,y,"mine");
            minesweeper.status = lose;
            break;
        
        case cover:
            setfillstyle(SOLID_FILL,WHITE);
            bar (x,     y,      x+19,   y+19);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar (x+1,   y+1,    x+19,   y+19);
            setfillstyle(SOLID_FILL,LIGHTGRAY);
            bar (x+1,   y+1,    x+18,   y+18);
            break;

        case none:
            autoshow(Row,Column,x_init,y_init,none);
            break;

        case flag:
            setfillstyle(SOLID_FILL,WHITE);
            bar (x,     y,      x+19,   y+19);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar (x+1,   y+1,    x+19,   y+19);
            setfillstyle(SOLID_FILL,LIGHTGRAY);
            bar (x+1,   y+1,    x+18,   y+18);
            
            if (minesweeper.flags[Row][Column] != true)
            {
                if(minesweeper.map[Row][Column]!=mine)
                    minesweeper.show[Row][Column]=unseen;
                
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,BLACK);
                bar(4 +x,   13+y,   15+x,   14+y);
                bar(9 +x,   9 +y,   10+x,   11+y);
                line(7+x,   12+y,   12+x,   12+y);

                setfillstyle(SOLID_FILL,RED);
                bar(9+x,    3+y,    10+x,   8+y);
                bar(7+x,    4+y,    8+x,    7+y);
                bar(5+x,    5+y,    6+x,    6+y);
                putpixel(4+x,   6+y,RED);
                putpixel(6+x,   7+y,RED);
                putpixel(8+x,   8+y,RED);
                minesweeper.flags[Row][Column] = true;
            }
            else
            {
                minesweeper.flags[Row][Column] = false;
                minesweeper.show[Row][Column] = unseen;
            }   
            break;

        default: 
            break;
    }
}

void formWindow(void)
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(0,454,284,174);

    setfillstyle(SOLID_FILL,BLACK);
    line(7,181,13,181);
    line(7,183,13,183);
    line(7,185,13,185);

    /* Boton de apagar*/
    bar(10,447,10,443);
    arc(10,447,135,45, 3);

    /* Boton de reiniciar */

    arc(10,425,0,270,3);
    line(12,425,14,424);
    line(14,424,14,426);
    line(14,426,12,425);

    /* Imagenes */
    rectangle(6,401,13,406);

    putpixel(11,404,BLACK);
    putpixel(10,404,BLACK);
    putpixel(9,403,BLACK);
    putpixel(7,403,BLACK);

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    for (i = 0; i < 5; i++) for (j = 0; j < 3; j++)
        bar(142 + (46*j),195 + (46*i),185 + (46*j),238 + (46*i));

}

void formMinesweeper(int x, int y)
{
    int rest = 57;
    /**************************************/
    /*   Ventana y barra de herramientas  */
    /**************************************/
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(0+x, 0+y, 29+(21*minesweeper.width)+x, 134+(21*minesweeper.high)+y);
    setfillstyle(SOLID_FILL,BLUE);
    bar(2+x, 2+y, 27+(21*minesweeper.width)+x, 24+y);

    setcolor(WHITE);
    settextstyle(SMALL_FONT,HORIZ_DIR,4);
    outtextxy(26+x, 6+y,"Minesweeper");

    /**************************************/
    /*              ICONO                 */
    /**************************************/
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    icon(3+x,3+y,"mine");

    /**************************************/
    /*   1 - Contenedor de Paneles        */
    /*   2 - Panel de Info                */
    /*   3 - Panel de Juego               */
    /**************************************/
    setfillstyle(SOLID_FILL,WHITE);
    /*  1   */
    bar(2+x,43+y,27+(21*minesweeper.width)+x,45+y);
    bar(2+x,43+y,4+x,132+(21*minesweeper.high)+y);
    /*  2   */
    bar(15+x+(21*minesweeper.width),54+y,17+(21*minesweeper.width)+x,97+y);
    bar(12+x,97+y,15+x+(21*minesweeper.width),95+y);
    /*  3   */
    bar(15+x+(21*minesweeper.width),119+y,17+x+(21*minesweeper.width),121+y+(21*minesweeper.high));
    bar(15+x+(21*minesweeper.width),119+y+(21*minesweeper.high),15+x,121+y+(21*minesweeper.high));

    setfillstyle(SOLID_FILL,DARKGRAY);
    /*  1   */
    bar(25+(21*minesweeper.width)+x,46+y,27+(21*minesweeper.width)+x,132+y+(21*minesweeper.high));
    bar(5+x,130+y+(21*minesweeper.high),27+x+(21*minesweeper.width),132+y+(21*minesweeper.high));
    /*  2   */
    bar(12+x,51+y,17+(21*minesweeper.width)+x,53+y);
    bar(12+x,51+y,14+x,97+y);
    /*  3   */
    bar(12+x,116+y,17+x+(21*minesweeper.width),119+y);
    bar(12+x,116+y,14+x,121+y+(21*minesweeper.high));



    /**************************************/
    /*    Boton para cerrar la ventana    */
    /**************************************/
    setfillstyle(SOLID_FILL,WHITE);
    bar(9+(21*minesweeper.width)+x,5+y,  24+x+(21*minesweeper.width),20+y);
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(10+(21*minesweeper.width)+x,6+y,  24+x+(21*minesweeper.width),20+y);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(10+(21*minesweeper.width)+x,6+y,  23+x+(21*minesweeper.width),19+y);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE,0,3);
    line(12+(21*minesweeper.width)+x,8+y,21+(21*minesweeper.width)+x,17+y);
    line(21+(21*minesweeper.width)+x,8+y,12+(21*minesweeper.width)+x,17+y);

    /**************************************/
    /*              Opciones              */
    /**************************************/
    settextstyle(SMALL_FONT,HORIZ_DIR,5);
    setfillstyle(SOLID_FILL,DARKGRAY);
    outtextxy(10+x ,26+y,"Game");
    outtextxy(50+x ,26+y,"Help");


    /**************************************/
    /*         Boton de Carita            */
    /**************************************/
    setfillstyle(SOLID_FILL,WHITE);
    bar(-3 + (21*minesweeper.width)/2 + x,57 + y,30 + (21*minesweeper.width)/2 + x,91 + y);
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(0 + (21*minesweeper.width)/2 + x,60 + y,30 + (21*minesweeper.width)/2 + x,91 + y);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(0 + (21*minesweeper.width)/2 + x,60 + y,27 + (21*minesweeper.width)/2 + x,88 + y);
}

void MainEvent(void)
{
    int click;
    int window_paint[2], mine_paint[2], uni_paint[2];
    mver();
    do
    {
        
        uni_paint[1] = uni_paint[0];
        mine_paint[1] = mine_paint[0];
        window_paint[1] = window_paint[0];
        if(minesweeper.visible==true)
        {
            minesweeper.isMenuPainting = minesweeper.isMenuActive;
            if(mxpos(1)>7+minesweeper.x && mypos(1)>26+minesweeper.y && mxpos(1)<43+minesweeper.x && mypos(1)<42+minesweeper.y)
            {
                setfillstyle(SOLID_FILL,DARKGRAY);
                setcolor(WHITE);
                minesweeper.isMenuActive = true;
            }
            else
            {
                setfillstyle(SOLID_FILL,LIGHTGRAY);
                setcolor(BLACK);
                minesweeper.isMenuActive = false;
            }
            if(minesweeper.isMenuActive != minesweeper.isMenuPainting)
            {
                mocultar();
                bar(7+minesweeper.x,26+minesweeper.y,43+minesweeper.x,42+minesweeper.y);
                outtextxy(10+minesweeper.x ,26+minesweeper.y,"Game");
                mver();
            }
        }

        if(mxpos(1)>54 && mypos(1)>455 && mxpos(1)<86 && mypos(1)<480)
            uni_paint[0] = true;
            else
                uni_paint[0] = false;

        if(mxpos(1)>26 && mypos(1)>455 && mxpos(1)<53 && mypos(1)<479)
            mine_paint[0] = true;

            else
                mine_paint[0] = false;

        if(mxpos(1)>0 && mypos(1)>455 && mxpos(1)<25 && mypos(1)<479)
            window_paint[0] = true;

            else
                window_paint[0] = false;
            
        if(uni_paint[0] != uni_paint[1])
        {
            mocultar();
            setfillstyle(SOLID_FILL,WHITE);
            bar(86,455,640,480);
            setfillstyle(SOLID_FILL,uni_paint[0]==false?WHITE:BLACK);
            bar(54,455,86,480);
            setfillstyle(SOLID_FILL,uni_paint[0]==false?BLACK:WHITE);
            icon(59,462,"uni");
            mver();
        }

        if(window_paint[0] != window_paint[1])
        {
            mocultar();
            setfillstyle(SOLID_FILL,WHITE);
            bar(86,455,640,480);
            setfillstyle(SOLID_FILL,window_paint[0]==false?WHITE:BLACK);
            bar(0,455,25,480);
            setfillstyle(SOLID_FILL,window_paint[0]==false?BLACK:WHITE);
            icon(5,460,"window");
            mver();
        }
        if (mine_paint[0] != mine_paint[1])
        {
            mocultar();
            setfillstyle(SOLID_FILL,WHITE);
            bar(86,455,640,480);
            setfillstyle(SOLID_FILL,mine_paint[0]==false?WHITE:BLACK);
            bar(26,455,53,480);
            setfillstyle(SOLID_FILL,mine_paint[0]==false?BLACK:WHITE);
            setcolor(mine_paint[0]==false?BLACK:WHITE);
            icon(32,458,"mine");
            mver();
        }
    }
    while(mclick()==0);
    click = mclick();

        if(minesweeper.visible==true)
        {
            eventMinesweeper(minesweeper.x,minesweeper.y, click);
        }
        if(mxpos(1)>26 && mypos(1)>455 && mxpos(1)<53 && mypos(1)<479)
        {
            formMinesweeper(minesweeper.x,minesweeper.y);
            newgame(minesweeper.x,minesweeper.y);
            minesweeper.visible=true;
        }
        if(mxpos(1)>0 && mypos(1)>455 && mxpos(1)<25 && mypos(1)<479)
        {
            if(windowhome.visible==true)
            {
                setfillstyle(SOLID_FILL,BLACK);
                bar(0,454,284,174);
                windowhome.visible=false;
            }
            else
            {
                formWindow();
                windowhome.visible=true;
            }
        }
        if(mxpos(1)>54 && mypos(1)>455 && mxpos(1)<86 && mypos(1)<480)
        {
            closegraph();
            runAcademicRegister();
            initgraph(&modo,&gmodo,"");
            Desktop();
        }

    while(mclick()!=0); 
    MainEvent();    
}

void Desktop(void)
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
    bar(-1,455,640,480);
    setfillstyle(SOLID_FILL,BLACK);
    icon(5,460,"window");
    icon(32,458,"mine");
    setfillstyle(SOLID_FILL,BLACK);
    icon(59,462,"uni");
}

void icon(int x, int y, char *name)
{
    int windowIcon[4][14] ={{7,8,    7,14,   13,14,  14,15,  15,15,  15,8,   7,8},{7,1,   13,1,   14,0,   15,0,   15,6,   7,6,    7,1},{0,2,   5,2,    5,6,    0,6,    0,2},{0,8,   5,8,    5,13,   0,13,   0,8}};

    if(strcmp(name,"window")==0)
    {
        for(i=0;i<14;i++)
            for(j=0;j<4;j++)
                if(i%2==0)
                    windowIcon[j][i]+=x;
                else
                    windowIcon[j][i]+=y;
        
        for(i=0;i<4;i++)
        {
            if(i<2)
                fillpoly(7,windowIcon[i]);
            else
                fillpoly(5,windowIcon[i]);
        }
    }
    else if (strcmp(name,"mine")==0)
    {
        bar(5 +x,   5 +y,   14+x,   14+y);
        bar(9 +x,   16+y,   10+x,   18+y);
        bar(16+x,   9 +y,   18+x,   10+y);
        bar(9 +x,   3 +y,   10+x,   1 +y);
        bar(3 +x,   9 +y,   1 +x,   10+y);

        line(15+x,  12+y,   15+x,   7 +y);
        line(12+x,  15+y,   7 +x,   15+y);
        line(4 +x,  7 +y,   4 +x,   12+y);
        line(7 +x,  4 +y,   12+x,   4 +y);

        putpixel(4 +x,  4 +y,   BLACK);
        putpixel(4 +x,  15+y,   BLACK);
        putpixel(15+x,  15+y,   BLACK);
        putpixel(15+x,  4 +y,   BLACK);

        setfillstyle(SOLID_FILL,WHITE==getcolor() ? BLACK : WHITE);
        bar(7 +x,   7 +y,   8 +x,   8 +y);
    }
    else if (strcmp(name,"uni")==0)
    {
        bar(0+x,0+y,2+x,11+y);
        bar(3+x,9+y,12+x,11+y);
        bar(10+x,8+y,12+x,5+y);
        bar(7+x,6+y,5+x,0+y);
        bar(8+x,0+y,17+x,2+y);
        bar(15+x,0+y,17+x,11+y);
        bar(17+x,11+y,22+x,9+y);
        bar(20+x,8+y,22+x,5+y);
        bar(20+x,2+y,22+x,0+y);
    }
    


}
