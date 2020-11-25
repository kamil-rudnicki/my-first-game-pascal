#include "naglowki.h"

void plansza::zerowanie_planszy()
{
	szerokosc=14;
	wysokosc=21;
	
	for(int i=0; i<wysokosc+1; i++)
		for(int j=0; j<szerokosc+2; j++) pole[i][j]=0;

	for(i=0; i<wysokosc; i++) pole[i][0]=-1;
	for(i=0; i<wysokosc+1; i++) pole[i][szerokosc+1]=-1;
	for(i=0; i<szerokosc+1; i++) pole[wysokosc][i]=-1;
}

//**********************************************************************

void plansza::rysuj_element_klocka(int x, int y, int kolor, int szerokosc)
{
	if(kolor==1) blit((BITMAP *)datafile_gfx[0].dat, dblbuffer, 0, 0, x, y, x+szerokosc, y+szerokosc);
	else if(kolor==2) blit((BITMAP *)datafile_gfx[1].dat, dblbuffer, 0, 0, x, y, x+szerokosc, y+szerokosc);
	else if(kolor==3) blit((BITMAP *)datafile_gfx[2].dat, dblbuffer, 0, 0, x, y, x+szerokosc, y+szerokosc);
	else if(kolor==4) blit((BITMAP *)datafile_gfx[3].dat, dblbuffer, 0, 0, x, y, x+szerokosc, y+szerokosc);
	else if(kolor==5) blit((BITMAP *)datafile_gfx[4].dat, dblbuffer, 0, 0, x, y, x+szerokosc, y+szerokosc);
}

//**********************************************************************

void plansza::rysuj_plansze()
{
	for(int i=0; i<wysokosc; i++)
		for(int j=1; j<szerokosc+1; j++) rysuj_element_klocka((j*20)+10, (i*20)+25, pole[i][j], 20);
}

//**********************************************************************

int plansza::sprawdz_linia()
{
int numer=0, i, j, ilosc=0;


for(i=0; i<21; i++){
numer=1;

	for(j=1; j<15; j++){
		if(pole[i][j]==0) numer=0;
	}

	if(numer==1){
		stop_sample((SAMPLE *)datafile_sound[12].dat);
		play_sample((SAMPLE *)datafile_sound[14].dat,256,127,1000,0);
		obniz(i);
		ilosc++;
	}
}
return ilosc;

}

//**********************************************************************

void plansza::obniz(int n)
{
for(int i=n; i>0; i--)
{
	for(int j=1; j<15; j++) pole[i][j]=pole[i-1][j];
}

}

//**********************************************************************

void plansza::zaciemnij(int x1, int y1, int x2, int y2, int ile, int tryb, BITMAP *bitm)
{
int kolor=0,  r1=0,  g1=0, b1=0;

for(int i=x1; i<x2; i++)
for(int j=y1; j<y2; j++){

	kolor=_getpixel16(bitm, i, j);
	r1=getr16(kolor);
	g1=getg16(kolor);
	b1=getb16(kolor);

	if(tryb==1){
		r1-=ile;
		g1-=ile;
		b1-=ile;
	}else if(tryb==2){
		r1+=ile;
		g1+=ile;
		b1+=ile;
	}else if(tryb==3){
		r1+=ile;
	}else if(tryb==4){
		g1+=ile;
	}else if(tryb==5){
		g1+=ile;
	}

	if(r1<0) r1=0; if(r1>255) r1=255;
	if(g1<0) g1=0; if(g1>255) g1=255;
	if(b1<0) b1=0; if(b1>255) b1=255;

	_putpixel16(bitm, i, j, makecol(r1, g1, b1));
}



}