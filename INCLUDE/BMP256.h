#include <conio.h>
#include <stdio.h>
#include <graphics.h>


long int BIT_PIXEL, PIXEL_BIT,CUERPO, PALETA, PALETA_TAM, TAM_X, TAM_Y;
int huge DetectVGA256()
{  /* 0 = 320x200x256  modo CGA  320(horizontal) con 200(vertical) pixeles(puntos) en 256colores
		1 = 640x400x256  modo ATT400
		2 = 640x480x256  modo VGA
		3 = 800x600x256  modo SVGA
		4 = 1024x768x256; modo XGA
		Todos son los modos graficos estandar  */
  return 4;
}
typedef struct
{
  unsigned char b, g, r, a;
} Color;
int getcol (FILE * BMP);
int ShowBMP (int posx, int posy, char *fname);
void initgraphfull256 (void)
{
int modo = DETECT, tarj,TIPOLETRA;
int color=0,x=180,y=50;

/*Instalamos el driver SVGA.bgi para acceder a 256 colores*/
installuserdriver("Svga256",DetectVGA256);
/*Instalamos en nuestro proyecto el tipo de letra*/
TIPOLETRA = installuserfont("LITT.CHR");
/*Iniciamos el modo grafico*/
initgraph(&modo,&tarj,"C:\\TC20\\BIN");
}

int ShowBMP (int posx, int posy, char *fname)
{
  FILE * BMP;
  int color;
  int k, c;
  Color col;
  int x, y;
  BMP = fopen (fname, "rb");
  if (BMP == NULL)
    return 1;
  fseek (BMP, 10, SEEK_SET);
  fread (&CUERPO, sizeof (CUERPO), 1, BMP);
  fseek (BMP, 18, SEEK_SET);
  fread (&TAM_X, sizeof (TAM_X), 1, BMP);
  fseek (BMP, 22, SEEK_SET);
  fread (&TAM_Y, sizeof (TAM_Y), 1, BMP);
  fseek (BMP, 28, SEEK_SET);
  fread (&BIT_PIXEL, sizeof (BIT_PIXEL), 1, BMP);
  PIXEL_BIT = 8 / BIT_PIXEL;
  PALETA_TAM = 1 << BIT_PIXEL;
  PALETA = CUERPO - 4 * PALETA_TAM;
  fseek (BMP, PALETA, SEEK_SET);
  for (k = 0; k < PALETA_TAM; k++)
    {
      fread (&col, sizeof (col), 1, BMP);
      setrgbpalette (k, (col.r) >> 2, (col.g) >> 2, (col.b) >> 2);
    }
  for (y = TAM_Y - 1; y >= 0; y--)
    for (x = 0; x < TAM_X; x++)
      putpixel (posx+x, posy+y, getcol (BMP));

  fclose(BMP);
  return 0;
}

int getcol (FILE * BMP)
{
  static int x = 0;
  static int n = 0;
  static long int col[4];
  unsigned char b;
  if (x >= TAM_X)
    {
      x = 0;
      while (n % 4)
	{
	  fread (&b, sizeof (b), 1, BMP);
	  n++;
	}
      n = 0;
    }
  if (x % PIXEL_BIT == 0)
    {
      int k = PIXEL_BIT;
      int mask = (1 << BIT_PIXEL) - 1;
      fread (&b, sizeof (b), 1, BMP);
      n++;
      while (k--)
	{
	  col[k] = b & mask;
	  b >>= BIT_PIXEL;
	}
    }
  return col[x++ % PIXEL_BIT];
}