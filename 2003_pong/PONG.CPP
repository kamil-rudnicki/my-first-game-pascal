#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <memory.h>
#include <13h.h>

class gra{
private:
        float x, y;
        int szybkosc;
        int dlugosc_paletki;
        float wektorx, wektory;
        int k_bialy, k_czarny, k_pilka;
        float bialyx, bialyy, czarnyx, czarnyy;
        void rysuj_pilke(int xa, int ya, int kolora);
        void rysuj_paletke(int xa, int ya, int kolora);
        int zycie_bialy, zycie_czarny;
        char znak;

        void gra_dwa();
        void gra_jeden();
        int tryb_gry;
        int staremyszy;
        int sterowanie, poziom;

       void play(void);
       void newgame();
public:
       gra(int szybkosc1, int wektor_x1, int wektor_y1, int tryb, int ster, int pozio);
};

class menu{
private:
   char klawisz;
   int szybkosc;
   int poziom;
   int sterowanie;
   void rysuj(int iloscpozycji, int pozycja, int x, int y, int dlugosc){
     for(int i=1; i<=iloscpozycji; i++){
     if(i==pozycja){ Linia_H(x,x+dlugosc,i*10+y,49);
                     Linia_V(i*10+y-4,i*10+y,x,49);
                     Linia_V(i*10+y-4,i*10+y,x+dlugosc,49);
                     }
     else{ Linia_H(x,x+dlugosc,i*10+y,0);
           Linia_V(i*10+y-4,i*10+y,x,0);
           Linia_V(i*10+y-4,i*10+y,x+dlugosc,0);
           }
     }
   }
public:
   menu();
};


///////////////////////////////////////MENU
menu::menu()
{
szybkosc=8;
Linia_H(0,64000,0,0);




//Linia_H(124,168,20,5);

Linia_H(0,319,170,2);
Linia_H(0,319,197,2);
Linia_H(0,319,0,2);
Linia_H(0,319,58,2);
Linia_V(0,196,0,2);
Linia_V(0,196,319,2);

Blit_String(10, 175, 23, "By: Kamil Rudnicki",1);
Blit_String(10, 185, 23, "http://kamilrudnicki.w.interia.pl",1);

Blit_String(130,90,90, "NEW GAME",1);
Blit_String(130,100,90,"  EXIT ",1);

int valid=1;
int ilosc_pozycji=2;
int pozycja=1;
int x1=10, y1=10, x2=1, y2=1;

while(valid){

Blit_String(x1+1,y1,1,"PONG",1);
Blit_String(x1,y1,9,"PONG",1);
delay(10);
if(x1<3 || x1>285) x2=-x2;
if(y1<3 || y1>50) y2=-y2;

Blit_String(x1+1,y1,0,"PONG",1);
Blit_String(x1,y1,0,"PONG",1);
x1=x1+x2;
y1=y1+y2;


  rysuj(ilosc_pozycji,pozycja, 120,88,80);

  if(kbhit()) klawisz=getch();
  if(klawisz==27) exit(1);
  else if(klawisz==72){
                   if(pozycja<=1) pozycja=ilosc_pozycji;
                   else pozycja--;
                   klawisz='n';
  }
  else if(klawisz==80){
                   if(pozycja>=ilosc_pozycji) pozycja=1;
                   else pozycja++;
                   klawisz='n';
  }
  else if(klawisz==13){
                       if(pozycja==1) valid=0;
                       if(pozycja==2) exit(1);
  }
}

Linia_H(0,64000,0,0);
Blit_String(117,90,35, "ONE PLAYER",1);
Blit_String(115,100,34,"TWO PLAYERS",1);

int koniec=0;
valid=1;
ilosc_pozycji=2;
pozycja=1;
klawisz='m';


while(valid){

  rysuj(ilosc_pozycji,pozycja, 110,88,100);

  if(kbhit()) klawisz=getch();
  if(klawisz==27) exit(1);
  else if(klawisz==72){
                   if(pozycja<=1) pozycja=ilosc_pozycji;
                   else pozycja--;
                   klawisz='n';
  }
  else if(klawisz==80){
                   if(pozycja>=ilosc_pozycji) pozycja=1;
                   else pozycja++;
                   klawisz='n';
  }
  else if(klawisz==13){
                       if(pozycja==2){
                       Linia_H(0,64000,0,2);
                       Blit_String(110,10,35, "CONTROLS",1);
                       Blit_String(15,50,120,"Player 1",1);
                       Blit_String(210,50,120, "Player 2",1);
                       Blit_String(210,80,1,"Mouse",1);
                       Blit_String(15,80,1, "Keybord",1);
                       Blit_String(15,90,0, " Up   - arrow up",1);
                       Blit_String(15,100,0," Down - arrow down",1);
                       getch();
                       gra theGame(szybkosc,1,1,2,1,1);
                       koniec=1;
                       valid=0;
                       }
                       if(pozycja==1) valid=0;
  }
}

Linia_H(0,64000,0,0);
Blit_String(125,10,49, "DIFFICULT",1);
Blit_String(142,90,35,  " Easy",1);
Blit_String(142,100,34, "Medium",1);
Blit_String(142,110,35, " Hard",1);

if(koniec==0) valid=1;
ilosc_pozycji=3;
pozycja=2;
klawisz='m';

while(valid){

  rysuj(ilosc_pozycji,pozycja, 135,88,60);

  if(kbhit()) klawisz=getch();
  if(klawisz==27) exit(1);
  else if(klawisz==72){
                   if(pozycja<=1) pozycja=ilosc_pozycji;
                   else pozycja--;
                   klawisz='n';
  }
  else if(klawisz==80){
                   if(pozycja>=ilosc_pozycji) pozycja=1;
                   else pozycja++;
                   klawisz='n';
  }
  else if(klawisz==13){
                       if(pozycja==3){poziom=3; valid=0;}
                       if(pozycja==2){poziom=2; valid=0;}
                       if(pozycja==1){poziom=1; valid=0;}
  }
}

Linia_H(0,64000,0,0);
Blit_String(130,10,49, "CONTROL",1);
Blit_String(80,90,35, "Keyboard (arrow keys)",1);
Blit_String(80,100,34,"        Mouse",1);

if(koniec==0) valid=1;
ilosc_pozycji=2;
pozycja=2;
klawisz='m';

while(valid){

  rysuj(ilosc_pozycji,pozycja, 75,88,182);

  if(kbhit()) klawisz=getch();
  if(klawisz==27) exit(1);
  else if(klawisz==72){
                   if(pozycja<=1) pozycja=ilosc_pozycji;
                   else pozycja--;
                   klawisz='n';
  }
  else if(klawisz==80){
                   if(pozycja>=ilosc_pozycji) pozycja=1;
                   else pozycja++;
                   klawisz='n';
  }
  else if(klawisz==13){
       if(pozycja==1){sterowanie=1; valid=0;}
       if(pozycja==2){sterowanie=2; valid=0;}
  }
}
klawisz='a';
if(koniec==0) gra theGame(szybkosc,1,1,1, sterowanie, poziom);

}

void gra::gra_jeden()
{
if(poziom==1)
{
  if(czarnyy<y && x>170 && (czarnyy+dlugosc_paletki)<=179){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy+=0.4, k_czarny);}
  if(czarnyy>y && x>170 && (czarnyy-dlugosc_paletki)>7){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy-=0.4, k_czarny);}
}
else if(poziom==2)
{
  if(czarnyy<y+2 && x>80 && (czarnyy+dlugosc_paletki)<=179){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy+=0.63, k_czarny);}
  if(czarnyy>y-2 && x>80 && (czarnyy-dlugosc_paletki)>7){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy-=0.63, k_czarny);}
  if(czarnyy<87 && x<80 && (czarnyy+dlugosc_paletki)<=179){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy+=0.63, k_czarny);}
  if(czarnyy>87 && x<80 && (czarnyy-dlugosc_paletki)>7){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy-=0.63, k_czarny);}
}
else if(poziom==3)
{
  if(czarnyy<y && x<240 && (czarnyy+dlugosc_paletki)<=179){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy+=0.74, k_czarny);}
  if(czarnyy>y && x<240 && (czarnyy-dlugosc_paletki)>7){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy-=0.74, k_czarny);}
  if(czarnyy<y+15 && x>240 && (czarnyy+dlugosc_paletki)<=179){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy+=0.74, k_czarny);}
  if(czarnyy>y-15 && x>240 && (czarnyy-dlugosc_paletki)>7){
  rysuj_paletke(czarnyx, czarnyy, 50);
  rysuj_paletke(czarnyx, czarnyy-=0.74, k_czarny);}
}

if(sterowanie==1){
  if(kbhit())
  {
  znak=getch();

    if(znak==72 && (bialyy-dlugosc_paletki)>7){
       rysuj_paletke(bialyx, bialyy, 50);
       rysuj_paletke(bialyx, bialyy-=4, k_bialy);}
    else if(znak==80 && (bialyy+dlugosc_paletki)<178){
       rysuj_paletke(bialyx, bialyy, 50);
       rysuj_paletke(bialyx, bialyy+=4, k_bialy);}
    else if(znak==27) exit(1);
  }
}else{

int myszx, myszy;
  CzytajPozycja(myszx, myszy);

  if(myszy<staremyszy && bialyy-dlugosc_paletki>7){
  rysuj_paletke(bialyx, bialyy, 50);
  bialyy-=1.5;
  ZapiszPozycja(100, bialyy-1);
  rysuj_paletke(bialyx, bialyy, k_bialy);
  staremyszy=bialyy-1;
  }

  else if(myszy>staremyszy && bialyy+dlugosc_paletki<179){
  rysuj_paletke(bialyx, bialyy, 50);
  bialyy+=1.5;
  ZapiszPozycja(100,bialyy+1);
  rysuj_paletke(bialyx, bialyy, k_bialy);
  staremyszy=bialyy+1;
  }
  if(kbhit()) if(getch()==27) exit(1);

}

}

///////////////////////////////////////Klawisze na dw¢ch

void gra::gra_dwa()
{
  int myszx, myszy;
  CzytajPozycja(myszx, myszy);

  if(myszy<staremyszy && czarnyy-dlugosc_paletki>7){
  rysuj_paletke(czarnyx, czarnyy, 50);
  czarnyy-=1.5;
  ZapiszPozycja(100, czarnyy-1);
  rysuj_paletke(czarnyx, czarnyy, k_czarny);
  staremyszy=czarnyy-1;
  }

  else if(myszy>staremyszy && czarnyy+dlugosc_paletki<179){
  rysuj_paletke(czarnyx, czarnyy, 50);
  czarnyy+=1.5;
  ZapiszPozycja(100,czarnyy+1);
  rysuj_paletke(czarnyx, czarnyy, k_czarny);
  staremyszy=czarnyy+1;
  }

  if(kbhit())
  {
  znak=getch();

    if(znak==72 && (bialyy-dlugosc_paletki)>7){
       rysuj_paletke(bialyx, bialyy, 50);
       rysuj_paletke(bialyx, bialyy-=6, k_bialy);}
    else if(znak==80 && (bialyy+dlugosc_paletki)<178){
       rysuj_paletke(bialyx, bialyy, 50);
       rysuj_paletke(bialyx, bialyy+=6, k_bialy);}
    //else if(znak==27) exit(1);
  }
}

/////////////////////////////////////Konstruktor

gra::gra(int szybkosc1, int wektor_x1, int wektor_y1, int tryb, int ster, int pozio)
{
x=160; y=87; szybkosc=szybkosc1; wektorx=wektor_x1; wektory=wektor_y1;
bialyx=15; bialyy=87; czarnyx=305; czarnyy=87; dlugosc_paletki=18;
k_pilka=0; k_czarny=1; k_bialy=1; tryb_gry=tryb; staremyszy=87;
ZapiszPozycja(100, 87); zycie_bialy=4; zycie_czarny=4;
sterowanie=ster; poziom=pozio;
newgame();
}

void gra::rysuj_pilke(int xa, int ya, int kolora){
     putpixel(xa, ya, kolora);
     putpixel(xa+1, ya, kolora);
     putpixel(xa-1, ya, kolora);
     putpixel(xa, ya-1, kolora);
     putpixel(xa, ya+1, kolora);
}

void gra::rysuj_paletke(int xa, int ya, int kolora){
     Linia_V(ya-dlugosc_paletki, ya+dlugosc_paletki, xa, kolora);
}

void gra::play(void)
{
float roznica, k, l;

while(znak!=27 && x<305 && x>15)
{
  rysuj_pilke(x,y,k_pilka);
  delay(szybkosc);
  if(x+wektorx<17 && bialyy-dlugosc_paletki<y && bialyy+dlugosc_paletki>y){
  wektorx=-wektorx;

  roznica=y-bialyy;
  if(roznica<0){
      roznica=-roznica;
      k=dlugosc_paletki/1;
      l=1/k;
      wektory=roznica*l; wektory=-wektory;
  }
  else{
      k=dlugosc_paletki/1;
      l=1/k;
      wektory=roznica*l;
  }
  }
  else if(x+wektorx>303 && czarnyy-dlugosc_paletki<y && czarnyy+dlugosc_paletki>y){
   wektorx=-wektorx;

  roznica=y-czarnyy;
  if(roznica<0){
      roznica=-roznica;
      k=dlugosc_paletki/2;
      l=1/k;
      wektory=roznica*l; wektory=-wektory;
  }
  else{
      k=dlugosc_paletki/2;
      l=1/k;
      wektory=roznica*l; //wektory=-wektory;
  }
   }
  if(y+wektory<7 || y+wektory>178){
  wektory=-wektory;
   }

  rysuj_pilke(x,y,50);
  x+=wektorx;
  y+=wektory;

  if(tryb_gry==2) gra_dwa();
  else gra_jeden();
}

if(znak==27) exit(1);
if(x>=305)zycie_czarny--;
else if(x<=15)zycie_bialy--;

if(zycie_bialy>0 && zycie_czarny>0) newgame();
else if(tryb_gry==1 && zycie_bialy<=0){Blit_String(110,100,0,"Computer WIN :-(",1); delay(3000);}
else if(tryb_gry==1 && zycie_czarny<=0){Blit_String(120,100,0,"You WIN!",1); delay(3000);}
else if(tryb_gry==2 && zycie_bialy<=0){Blit_String(80,100,0,"Player 2 (right) WIN :-)",1); delay(3000);}
else if(tryb_gry==2 && zycie_czarny<=0){Blit_String(80,100,0,"Player 1 (left) WIN!",1); delay(3000);}
}

void gra::newgame()
{
  x=160; y=87;
  wektory=0;
  Linia_H(0,1599,0,40);
  Linia_H(0,55999,5,50);
  Linia_H(0,6399,180,40);

  Linia_H(0,319,5,1);
  Linia_H(0,319,180,1);
  Linia_H(0,319,0,1);
  Linia_H(0,319,199,1);
  Linia_V(0,199,0,1);
  Linia_V(0,199,319,1);
  rysuj_paletke(bialyx, bialyy, k_bialy);
  rysuj_paletke(czarnyx, czarnyy, k_czarny);
  rysuj_pilke(x, y, k_pilka);

  char zycie_b[]={zycie_bialy, '\0'};
  zycie_b[0]=zycie_bialy+48;
  Blit_String(5,186,0,zycie_b,1);
  zycie_b[0]=zycie_czarny+48;
  Blit_String(300,186,0,zycie_b,1);

  Blit_String(100,186,0,"press any key",1);
  delay(500);

  if(kbhit()){getch(); delay(1000);}
  if(kbhit())getch();
  if(kbhit())getch(); if(kbhit())getch();
  if(kbhit())getch(); if(kbhit())getch();
  if(kbhit())getch(); if(kbhit())getch();
  if(kbhit())getch(); if(kbhit())getch();
  if(kbhit())getch(); if(kbhit())getch();
  getch();
  for(int j=185; j<198; j++) Linia_H(99, 299, j, 40);

  play();
}

void main()
{
randomize();
tryb13h();

while(1==1){
menu theGame;
getch();
}

getch();
}