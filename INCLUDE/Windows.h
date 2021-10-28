#include <stdio.h>
#include <conio.h>
#include <GRAPHICS.H>
#include <time.h>
#include <stdlib.h>
#include <DOS.H>
#include <string.h>
#include <MOUSE.H>

#define duration 33
#define mode 1
#define true 1
#define false 0

typedef struct
{
  char Type[2];                     /* Tipo de archivo. establecido en "BM".                */
  unsigned long Size;               /* Tamano en BYTES del archivo                          */
  unsigned long Reserved;           /* Reservado. establecido en cero                       */
  unsigned long OffSet;             /* Desplazamiento hacia datos                           */
  unsigned long headsize;           /* Tama�o de la cabecera del bitmap. establecido en 40 */
  unsigned long Width;              /* Anchura en  pixeles.                                 */
  unsigned long Height;             /*  Altura en pixeles.                                  */
  unsigned int  Planes;             /* Numero de Planos. establecido en 1.                  */
  unsigned int  BitsPerPixel;       /* Numero de Bits por pixeles.                          */
  unsigned long Compression;        /* Compresion. Usually establecido en 0.                */
  unsigned long SizeImage;          /* Tamano en BYTES del bitmap.                          */
  unsigned long XPixelsPreMeter;    /* Pixeles Horizontales por metro.                      */
  unsigned long YPixelsPreMeter;    /* Pixeles Verticales por metro.                        */
  unsigned long ColorsUsed;         /* Numero de colores utilizados.                        */
  unsigned long ColorsImportant;    /* Numero de colores "Importantes".                     */
} BMP;

void WindowsSplashScreen(void);
void showImage(int x, int y, char *locate);
void LockScreen(void);
void Clock(void);
void InitializeGraphics(void);
void Desktop(void);
void icon(int x, int y, char *name);

int i, j, x, y;
int modo = DETECT, gmodo;
time_t Time;
struct tm *today;

void TurnOn(void) 
{
    initgraph(&modo, &gmodo, "");
    /*
    showImage(220,140,"c://TC20//IMAGES//Dell.bmp");
    delay(1000 * duration);
    cleardevice();
    for(i=0;i<5;i++)
    {
        gotoxy(1,1);    printf("_");
        delay(100 * duration);
        gotoxy(1,1);    printf(" ");
        delay(100 * duration);
    }
    cleardevice();
    WindowsSplashScreen();
    cleardevice();
    LockScreen();
    cleardevice();
    /**/
}

void LockScreen(void)
{
    char * month[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};    
    int button[] = {240,225,    400,225,    400,265,    240,265,    240,225};
    int x, y, click, isButton, painting;

    msituar(1,1,1);
    mver();
    showImage(0,0,"c://TC20//IMAGES//js.bmp");

    Time = time(0);
    today = localtime(&Time);
    setcolor(WHITE);
    settextstyle(2,0,10);
    outtextxy(0,400,month[today->tm_mon]);

    Clock();

    setlinestyle(SOLID_LINE,0,2);
    settextstyle(3,0,2);
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(WHITE);

    isButton=false;
    painting = 1;
    do
    {
        delay(10 * duration);
        click = mclick();
        x = mxpos(mode);
        y = mypos(mode);
        
        
        if( (x>240 && x<400) && (y>225 && y<265) )
        {
            if(click==1)
            {
                setfillstyle(1,DARKGRAY);
                fillpoly(5,button);
                outtextxy(280,230,"Sign Up");
                while(mclick()==1);
                isButton = true;
            }

            if(painting == 0)
            {
                painting = 1;

                setfillstyle(1,LIGHTGRAY);
                fillpoly(5,button);
                outtextxy(280,230,"Sign Up");
            }
        }
        else
            if(painting == 1)
            {
                painting = 0;
                
                setfillstyle(1,BLACK);
                fillpoly(5,button);
                outtextxy(280,230,"Sign Up");
            }

        
    }
    while (isButton==false);
}

void Clock(void)
{
    char date[6]={'\0'},minute[3]={'\0'};

    Time = time(0);
    today = localtime(&Time);

    itoa(today->tm_hour,date,10);
    itoa(today->tm_min,minute,10);
    if(today->tm_min>10)
        strcat(date,":");
    else
        strcat(date,":0");
    strcat(date,minute);
    settextstyle(2,0,10);

    setcolor(WHITE);
    outtextxy(0,350,date);
    
    setcolor(BLACK);
    for(i=0;i<60;i++)
    {
        if(mclick()!=0 || kbhit())
        {
            outtextxy(0,500,date);
            return;
        }
        else delay(4500);

        if(mclick()!=0 || kbhit())
        {
            outtextxy(0,500,date);
            return;
        }
        else delay(4500);
        
        if(mclick()!=0 || kbhit())
        {
            outtextxy(0,500,date);
            return;
        }
        else delay(4500);
    }   
    outtextxy(0,500,date);
    Clock();
    
}


void WindowsSplashScreen(void)
{
    int logo[4][10] =  {{288,159,   318,155,    318,182,    287,182,    288,159},   {321,155,   359,149,    359,182,    321,182,    321,155},   {288,185,   318,185,    318,212,    287,208,    288,185},   {321,185,   359,185,    359,217,    321,212,    321,185}};
                    
    int charger[2][50] = {  {320,321,323,325,326,327,327,327,327,326,324,322,321,319,317,315,313,312,312,312,312,313,314,316,317,   320,321,323,325,326,327,327,327,327,326,324,322,321,319,317,315,313,312,312,312,312,313,314,316,317},
                            {368,368,369,370,371,373,375,377,379,381,382,383,384,384,383,382,381,379,377,375,373,371,370,369,368,   368,368,369,370,371,373,375,377,379,381,382,383,384,384,383,382,381,379,377,375,373,371,370,369,368}};
    
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,LIGHTCYAN);

    for(i=0;i<4;i++)
        fillpoly(5,logo[i]);

    for(j=0;j<4;j++)
        for (i=0;i<25;i++)
        {
            putpixel(charger[0][i+1],charger[1][i+1],WHITE);
            putpixel(charger[0][i+3],charger[1][i+3],WHITE);
            putpixel(charger[0][i+6],charger[1][i+6],WHITE);
            putpixel(charger[0][i+9],charger[1][i+9],WHITE);
            

            putpixel(charger[0][i],charger[1][i],BLACK);
            putpixel(charger[0][i+2],charger[1][i+2],BLACK);
            putpixel(charger[0][i+5],charger[1][i+5],BLACK);
            putpixel(charger[0][i+8],charger[1][i+8],BLACK);
            
            if(i>10||i<1)
                delay(20 * duration);
            else
                delay(8 * duration);
        }
}

void showImage(int x, int y, char *locate)
{
    int b,a;
    BMP Obj;
    unsigned char* Datas;
    int in=0;
    unsigned char c=0;
    FILE * image;

    image = fopen(locate,"rb");
    if(!image)
    {
        printf("Error : No se puede abrir el archivo ...");
        getch();
        exit(0);
    }

    fread(&Obj, sizeof(Obj), 1, image);
    if(Obj.BitsPerPixel!=4)  /* Este NO es un bmp de 16 colores que podamos leer*/
    {
        fclose(image);
        printf("Error : Formato de archivo no soportado...");
        getch();
        exit(0);
    }

    fseek(image,Obj.OffSet,SEEK_SET);
    Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
    for(b=Obj.Height;b>=0;b--)
    {
        fread(Datas, sizeof(unsigned char), Obj.Width/2, image);
        c=0;
        in=0;
        for(a=0;a<=Obj.Width;a+=2)
        {
            c = (Datas[in] | 0xF0) & 0x0F;
            putpixel(a+1+x,b+y,c);
            c = (Datas[in] | 0x00) >>4;
            putpixel(a+x,b+y,c);
            in++;
        }
    }
    free(Datas);
    fclose(image);
}

