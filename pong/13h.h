#define PALETTE_MASK        0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA        0x3c9
#define SCREEN_WIDTH      (unsigned int)320
#define SCREEN_HEIGHT     (unsigned int)200

#define CHAR_WIDTH        8
#define CHAR_HEIGHT       8

#define ROM_CHAR_SET_SEG 0xF000
#define ROM_CHAR_SET_OFF 0xFA6E

unsigned far char *video_buffer=(unsigned char far*)0xA0000000L;
unsigned char far *rom_char_set = (char far *)0xF000FA6EL;

typedef struct RGB_color_typ
{
unsigned char red;
unsigned char green;
unsigned char blue;
}RGB_color,*RGB_color_ptr;

void putpixel(int x, int y, unsigned char color)
{
unsigned char far *video_buffer = (char far *)0xA0000000L;
video_buffer[y*320+x]=color;
}

void tryb13h()
{
    asm {
      mov ax,0x0013
      int 0x10
    }
}

//////////////////// Funkcja do rysowania lini pionowej /////////////////////
void Linia_V(int y1, int y2, int x, unsigned int color)
{
unsigned char far *video_buffer = (char far *)0xA0000000L;
unsigned int line_offset, index;
line_offset =((y1<<8)+(y1<<6))+x;
for(index=0; index<=y2-y1; index++)
{
video_buffer[line_offset]= color;
line_offset+=320;
}
}
///////////////////// Funkcja do rysowania lini poziomej/////////////////////
void Linia_H(int x1, int x2, int y, unsigned int color)
{
unsigned char far *video_buffer = (char far *)0xA0000000L;
_fmemset((char far *)(video_buffer + ((y<<8)+(y<<6))+x1),
color,x2-x1+1);
}

struct REGPACK reg;

void CzytajPozycja (int &czarnyx1, int &czarnyy1)
 {
 reg.r_ax=0x3;
 intr(0x33,&reg);
 czarnyx1=reg.r_cx;
 czarnyy1=reg.r_dx;
 }

void Pokaz (void)
 {
 reg.r_ax=0x1;
 intr(0x33,&reg);
 }

void ZapiszPozycja (int x, int y)
 {
 reg.r_ax=0x4;
 reg.r_cx=x;
 reg.r_dx=y;
 intr(0x33,&reg);
 }

void Blit_Char(int xc,int yc,char c,int color,int trans_flag)
{
// Ta funkcja korzysta ze zbioru zbakow umieszczonego w pamieci ROM
int offset,x,y;
unsigned char data;
char far *work_char;
unsigned char bit_mask = 0x80;
work_char = rom_char_set + c * CHAR_HEIGHT; // przesuniecie poczatku znaku w pamieci ROM
offset = (yc << 8) + (yc << 6) + xc; //przesuniecie znaku w buforze Video
for (y=0; y<CHAR_HEIGHT; y++)
    {
    bit_mask = 0x80; //inicjacja maski bitowej
    for (x=0; x<CHAR_WIDTH; x++)
	{
	// teraz testujemy ktore piksele sa przezroczyste (maja wartosc=0)
	if ((*work_char & bit_mask))
	     video_buffer[offset+x] = color;
	else if (!trans_flag)  // takes care of transparency
	    video_buffer[offset+x] = 0;
	bit_mask = (bit_mask>>1);
	}
       // przejscie do nastepnej linii
       offset      += SCREEN_WIDTH;
       work_char++;
      }
      }
// Wys. lancuch znakow ///////////////////////////////////////////////////////
void Blit_String(int x,int y, int color, char * string,int trans_flag)
{
int index;
// pusczona w petle (tyle powtorzen ile liter w lancuchu) funkcja Blit_Char
for (index=0; string[index]!=0; index++)
     {
     Blit_Char(x+(index<<3),y,string[index],color,trans_flag);
}
}