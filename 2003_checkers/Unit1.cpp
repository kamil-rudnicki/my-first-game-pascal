//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWarcaby *Warcaby;

#include "bicie.h"

POINT historia[2];
bool cofnij_bialy;

POINT pozycja; //pozycja kursora

bool wykonal_ruch=FALSE;
bool drugi_ruch=FALSE;
bool gra_z_komputerem=FALSE;

POINT pionek;  //pozycja zaznaczonego pionka
bool zaznaczony=FALSE; //zaznaczenie
bool klikniec=FALSE; //klikniecie
int plansza1[8][8]; //miejsce na ktorym stoi pionek
int i, j, k, l, a, b; //zmienne pomocnicze
int kolejka=0;
bool player=FALSE;
bool biciedotylu=TRUE;
bool zaniebicie=TRUE;
bool ok=TRUE;
int sek=0, min=0, sek1=0, srednia=0;
int zbitych[2];

int ax=0, ay=0;
int bx=0, by=0;
int licznik=0;

POINT bialy[12];
bool damka_bialy1[12];
int nr_pionka_bialego=30;
int nr_pionka_czarnego1=30;

POINT czarny[12];
bool damka_czarny1[12];
int nr_pionka_czarnego=30;
int nr_pionka_bialego1=30;


void TWarcaby::damka_bialy()
{
if(licznik==ax) ruch_bialy();
else if((licznik+1)==ax && bx!=0 && by!=0){
         for(int m=0; m<12; m++)
                {
                        if((czarny[m].x==bx) && (czarny[m].y==by))
                        {
                        plansza1[bx][by]=0;
                        nr_pionka_czarnego1=m;
                        bicie_czarny();
                        czarny[m].x=200;
                        czarny[m].y=200;
                        break;
                        }
                }
                ruch_bialy();
         }
}

void TWarcaby::damka_czarny()
{
if(licznik==ax) ruch_czarny();
else if((licznik+1)==ax && bx!=0 && by!=0){
         for(int m=0; m<12; m++)
                {
                        if((bialy[m].x==bx) && (bialy[m].y==by))
                        {
                        plansza1[bx][by]=0;
                        nr_pionka_bialego1=m;
                        bicie_bialy();
                        bialy[m].x=200;
                        bialy[m].y=200;
                        break;
                        }
                }
                ruch_czarny();
         }
}


void TWarcaby::bicie_drugie_bialy()
{
if(plansza1[pozycja.x+1][pozycja.y+1]==2 && plansza1[pozycja.x+2][pozycja.y+2]==0 && (pozycja.x+2)<8 && (pozycja.x+2)>=0 && (pozycja.y+2)<8 && (pozycja.y+2)>=0){
bicie_drugie_bialy1();
}
if(plansza1[pozycja.x-1][pozycja.y+1]==2 && plansza1[pozycja.x-2][pozycja.y+2]==0 && (pozycja.x-2)<8 && (pozycja.x-2)>=0 && (pozycja.y+2)<8 && (pozycja.y+2)>=0){
bicie_drugie_bialy1();
}
if(biciedotylu==TRUE && plansza1[pozycja.x+1][pozycja.y-1]==2 && plansza1[pozycja.x+2][pozycja.y-2]==0 && (pozycja.x+2)<8 && (pozycja.x+2)>=0 && (pozycja.y-2)<8 && (pozycja.y-2)>=0){
bicie_drugie_bialy1();
}
if(biciedotylu==TRUE && plansza1[pozycja.x-1][pozycja.y-1]==2 && plansza1[pozycja.x-2][pozycja.y-2]==0 && (pozycja.x-2)<8 && (pozycja.x-2)>=0 && (pozycja.y-2)<8 && (pozycja.y-2)>=0){
bicie_drugie_bialy1();
}
}

void TWarcaby::bicie_drugie_czarny()
{
if(plansza1[pozycja.x+1][pozycja.y-1]==1 && plansza1[pozycja.x+2][pozycja.y-2]==0 && (pozycja.x+2)<8 && (pozycja.x+2)>=0 && (pozycja.y-2)<8 && (pozycja.y-2)>=0){
bicie_drugie_czarny1();
}
if(plansza1[pozycja.x-1][pozycja.y-1]==1 && plansza1[pozycja.x-2][pozycja.y-2]==0 && (pozycja.x-2)<8 && (pozycja.x-2)>=0 && (pozycja.y-2)<8 && (pozycja.y-2)>=0){
bicie_drugie_czarny1();
}
if(biciedotylu==TRUE && plansza1[pozycja.x+1][pozycja.y+1]==1 && plansza1[pozycja.x+2][pozycja.y+2]==0 && (pozycja.x+2)<8 && (pozycja.x+2)>=0 && (pozycja.y+2)<8 && (pozycja.y+2)>=0){
bicie_drugie_czarny1();
}
if(biciedotylu==TRUE && plansza1[pozycja.x-1][pozycja.y+1]==1 && plansza1[pozycja.x-2][pozycja.y+2]==0 && (pozycja.x-2)<8 && (pozycja.x-2)>=0 && (pozycja.y+2)<8 && (pozycja.y+2)>=0){
bicie_drugie_czarny1();
}
}

void TWarcaby::bicie_drugie_bialy1()
{
pionek.x=pozycja.x;
pionek.y=pozycja.y;
zaznaczony=TRUE;
drugi_ruch=TRUE;
ok=FALSE;
kolejka=0;
Label14->Caption="No to masz drugie biecie.";
Image26->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_ZOLTY");

for(int m=0; m<12; m++)
        {
                if(pionek.x == bialy[m].x && pionek.y == bialy[m].y){
                nr_pionka_bialego=m;
                }
        }

if(nr_pionka_bialego==0) Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==1) Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==2) Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==3) Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==4) Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==5) Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==6) Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==7) Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==8) Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==9) Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==10) Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==11) Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
}

void TWarcaby::bicie_drugie_czarny1()
{
pionek.x=pozycja.x;
pionek.y=pozycja.y;
zaznaczony=TRUE;
drugi_ruch=TRUE;
ok=FALSE;
kolejka=1;
Label14->Caption="No to masz drugie biecie.";
Image26->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_ZIELONY");
for(int m=0; m<12; m++)
        {
                if(pionek.x == czarny[m].x && pionek.y == czarny[m].y){
                nr_pionka_czarnego=m;
                }
        }
if(nr_pionka_czarnego==0) Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==1) Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==2) Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==3) Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==4) Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==5) Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==6) Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==7) Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==8) Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==9) Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==10) Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==11) Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
}


void __fastcall TWarcaby::klik(TObject *Sender)
{
if(damka_bialy1[nr_pionka_bialego]==FALSE && kolejka==0 && zaznaczony==TRUE && plansza1[pozycja.x][pozycja.y]==0 && pozycja.x<8 && pozycja.x>=0 && pozycja.y>=0 && pozycja.y<8)
{
        //normalny ruch
        if((pozycja.x==pionek.x+1 && pozycja.y==pionek.y+1) || (pozycja.x==pionek.x-1 && pozycja.y==pionek.y+1))
        {
                ruch_bialy();

if(zaniebicie==TRUE){
int n=0;
  for(int m=0; m<8; m++)
  {
  if(m==pozycja.x && n==pozycja.y) continue;
    for(n=0; n<8; n++)
    {
    if(m==pozycja.x && n==pozycja.y) continue;
    if(plansza1[m][n]==1 && plansza1[m-1][n+1]==2 && plansza1[m-2][n+2]==0 && (m-2)<8 && (m-2)>=0 && (n+2)<8 && (n+2)>=0){
    a=m; b=n;
    za_niebicie_bialy();    m=8; n=8;   break;
    }else if(plansza1[m][n]==1 && plansza1[m+1][n+1]==2 && plansza1[m+2][n+2]==0 && (m+2)<8 && (m+2)>=0 && (n+2)<8 && (n+2)>=0){
    a=m; b=n;
    za_niebicie_bialy();    m=8; n=8;   break;
    }else if(biciedotylu==TRUE && plansza1[m][n]==1 && plansza1[m-1][n-1]==2 && plansza1[m-2][n-2]==0 && (m-2)<8 && (m-2)>=0 && (n-2)<8 && (n-2)>=0){
    a=m; b=n;
    za_niebicie_bialy();    m=8; n=8;   break;
    }else if(biciedotylu==TRUE && plansza1[m][n]==1 && plansza1[m+1][n-1]==2 && plansza1[m+2][n-2]==0 && (m+2)<8 && (m+2)>=0 && (n-2)<8 && (n-2)>=0){
    a=m; b=n;
    za_niebicie_bialy();    m=8; n=8;   break;
    }
    }
  }
}

        }
        else if(pozycja.x==pionek.x-2 && pozycja.y==pionek.y+2 && plansza1[pionek.x-1][pionek.y+1]==2)//bicie w lewo
        {
                for(int m=0; m<12; m++)
                {
                        if((czarny[m].x==pionek.x-1) && (czarny[m].y==pionek.y+1))
                        {
                        plansza1[pionek.x-1][pionek.y+1]=0;
                        nr_pionka_czarnego1=m;
                        bicie_czarny();
                        czarny[m].x=200;
                        czarny[m].y=200;
                        }
                }
                ruch_bialy();  if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_bialy();
        }
        else if(pozycja.x==pionek.x+2 && pozycja.y==pionek.y+2 && plansza1[pionek.x+1][pionek.y+1]==2)//bicie w prawo
        {
                for(int m=0; m<12; m++)
                {
                        if((czarny[m].x==pionek.x+1) && (czarny[m].y==pionek.y+1))
                        {
                        plansza1[pionek.x+1][pionek.y+1]=0;
                        nr_pionka_czarnego1=m;
                        bicie_czarny();
                        czarny[m].x=200;
                        czarny[m].y=200;
                        }
                }
                ruch_bialy(); if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_bialy();
        }
        else if(biciedotylu==TRUE && pozycja.x==pionek.x-2 && pozycja.y==pionek.y-2 && plansza1[pionek.x-1][pionek.y-1]==2)//bicie w lewo, do ty³u
        {
        for(int m=0; m<12; m++)
                {
                        if((czarny[m].x==pionek.x-1) && (czarny[m].y==pionek.y-1))
                        {
                        plansza1[pionek.x-1][pionek.y-1]=0;
                        nr_pionka_czarnego1=m;
                        bicie_czarny();
                        czarny[m].x=200;
                        czarny[m].y=200;
                        }
                }
                ruch_bialy();  if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_bialy();
        }else if(biciedotylu==TRUE && pozycja.x==pionek.x+2 && pozycja.y==pionek.y-2 && plansza1[pionek.x+1][pionek.y-1]==2)//bicie w prawo, do ty³u
        {
        for(int m=0; m<12; m++)
                {
                        if((czarny[m].x==pionek.x+1) && (czarny[m].y==pionek.y-1))
                        {
                        plansza1[pionek.x+1][pionek.y-1]=0;
                        nr_pionka_czarnego1=m;
                        bicie_czarny();
                        czarny[m].x=200;
                        czarny[m].y=200;
                        }
                }
                ruch_bialy(); if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_bialy();
        }



}else if(damka_bialy1[nr_pionka_bialego]==TRUE && kolejka==0 && zaznaczony==TRUE && plansza1[pozycja.x][pozycja.y]==0 && pozycja.x<8 && pozycja.x>=0 && pozycja.y>=0 && pozycja.y<8)
{
//////////////////////////////////////////////////////////////////
licznik=0; bx=0; by=0;

if(pozycja.x < pionek.x && pozycja.y < pionek.y){
ax=pionek.x-pozycja.x;
ay=pionek.y-pozycja.y;

        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x-a][pionek.y-a]==0) licznik++;
         else if(plansza1[pionek.x-a][pionek.y-a]==2){ bx=pionek.x-a; by=pionek.y-a; }
         }
        }
damka_bialy();
}
else if(pozycja.x > pionek.x && pozycja.y < pionek.y){
ax=pozycja.x-pionek.x;
ay=pionek.y-pozycja.y;

        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x+a][pionek.y-a]==0) licznik++;
         else if(plansza1[pionek.x+a][pionek.y-a]==2){ bx=pionek.x+a; by=pionek.y-a; }
         }
        }
damka_bialy();
}
else if(pozycja.x < pionek.x && pozycja.y > pionek.y){
ax=pionek.x-pozycja.x;
ay=pozycja.y-pionek.y;

        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x-a][pionek.y+a]==0) licznik++;
         else if(plansza1[pionek.x-a][pionek.y+a]==2){ bx=pionek.x-a; by=pionek.y+a; }
         }
        }
damka_bialy();
}
else if(pozycja.x > pionek.x && pozycja.y > pionek.y){
ax=pozycja.x-pionek.x;
ay=pozycja.y-pionek.y;


        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x+a][pionek.y+a]==0) licznik++;
         else if(plansza1[pionek.x+a][pionek.y+a]==2){ bx=pionek.x+a; by=pionek.y+a; }
         }
        }
damka_bialy();
}
}

else if(damka_czarny1[nr_pionka_czarnego]==FALSE && gra_z_komputerem==FALSE && kolejka==1 && zaznaczony==TRUE && plansza1[pozycja.x][pozycja.y]==0 && pozycja.x<8 && pozycja.x>=0 && pozycja.y>=0 && pozycja.y<8)
{
        //normalny ruch
        if((pozycja.x==pionek.x+1 && pozycja.y==pionek.y-1) || (pozycja.x==pionek.x-1 && pozycja.y==pionek.y-1))
        {
                ruch_czarny();

if(zaniebicie==TRUE){
int n=0;
  for(int m=0; m<8; m++)
  {
  if(m==pozycja.x && n==pozycja.y) continue;
    for(n=0; n<8; n++)
    {
    if(m==pozycja.x && n==pozycja.y) continue;
    if(plansza1[m][n]==2 && plansza1[m-1][n-1]==1 && plansza1[m-2][n-2]==0 && (m-2)<8 && (m-2)>=0 && (n-2)<8 && (n-2)>=0){
    a=m; b=n;
    za_niebicie_czarny();    m=8; n=8;   break;
    }else if(plansza1[m][n]==2 && plansza1[m+1][n-1]==1 && plansza1[m+2][n-2]==0 && (m+2)<8 && (m+2)>=0 && (n-2)<8 && (n-2)>=0){
    a=m; b=n;
    za_niebicie_czarny();    m=8; n=8;   break;
    }else if(biciedotylu==TRUE && plansza1[m][n]==2 && plansza1[m-1][n+1]==1 && plansza1[m-2][n+2]==0 && (m-2)<8 && (m-2)>=0 && (n+2)<8 && (n+2)>=0){
    a=m; b=n;
    za_niebicie_czarny();    m=8; n=8;   break;
    }else if(biciedotylu==TRUE && plansza1[m][n]==2 && plansza1[m+1][n+1]==1 && plansza1[m+2][n+2]==0 && (m+2)<8 && (m+2)>=0 && (n+2)<8 && (n+2)>=0){
    a=m; b=n;
    za_niebicie_czarny();    m=8; n=8;   break;
    }
    }
  }
}

        }
        else if(pozycja.x==pionek.x-2 && pozycja.y==pionek.y-2 && plansza1[pionek.x-1][pionek.y-1]==1)//bicie w lewo
        {
                for(int m=0; m<12; m++)
                {
                        if((bialy[m].x==pionek.x-1) && (bialy[m].y==pionek.y-1))
                        {
                        plansza1[pionek.x-1][pionek.y-1]=0;
                        nr_pionka_bialego1=m;
                        bicie_bialy();
                        bialy[m].x=200;
                        bialy[m].y=200;
                        }
                }
                ruch_czarny();  if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_czarny();
        }
        else if(pozycja.x==pionek.x+2 && pozycja.y==pionek.y-2 && plansza1[pionek.x+1][pionek.y-1]==1)//bicie w prawo
        {
                for(int m=0; m<12; m++)
                {
                        if((bialy[m].x==pionek.x+1) && (bialy[m].y==pionek.y-1))
                        {
                        plansza1[pionek.x+1][pionek.y-1]=0;
                        nr_pionka_bialego1=m;
                        bicie_bialy();
                        bialy[m].x=200;
                        bialy[m].y=200;
                        }
                }
                ruch_czarny(); if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_czarny();
        }
        else if(biciedotylu==TRUE && pozycja.x==pionek.x-2 && pozycja.y==pionek.y+2 && plansza1[pionek.x-1][pionek.y+1]==1)//bicie w lewo, do ty³u
        {
        for(int m=0; m<12; m++)
                {
                        if((bialy[m].x==pionek.x-1) && (bialy[m].y==pionek.y+1))
                        {
                        plansza1[pionek.x-1][pionek.y+1]=0;
                        nr_pionka_bialego1=m;
                        bicie_bialy();
                        bialy[m].x=200;
                        bialy[m].y=200;
                        }
                }
                ruch_czarny();  if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_czarny();
        }else if(biciedotylu==TRUE && pozycja.x==pionek.x+2 && pozycja.y==pionek.y+2 && plansza1[pionek.x+1][pionek.y+1]==1)//bicie w prawo, do ty³u
        {
        for(int m=0; m<12; m++)
                {
                        if((bialy[m].x==pionek.x+1) && (bialy[m].y==pionek.y+1))
                        {
                        plansza1[pionek.x+1][pionek.y+1]=0;
                        nr_pionka_bialego1=m;
                        bicie_bialy();
                        bialy[m].x=200;
                        bialy[m].y=200;
                        }
                }
                ruch_czarny(); if(drugi_ruch==TRUE) ok=TRUE; drugi_ruch=FALSE;
                bicie_drugie_czarny();
        }

}else if(damka_czarny1[nr_pionka_czarnego]==TRUE && kolejka==1 && zaznaczony==TRUE && plansza1[pozycja.x][pozycja.y]==0 && pozycja.x<8 && pozycja.x>=0 && pozycja.y>=0 && pozycja.y<8)
{
//////////////////////////////////////////////////////////////
licznik=0; bx=0; by=0;

if(pozycja.x < pionek.x && pozycja.y < pionek.y){
ax=pionek.x-pozycja.x;
ay=pionek.y-pozycja.y;

        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x-a][pionek.y-a]==0) licznik++;
         else if(plansza1[pionek.x-a][pionek.y-a]==1){ bx=pionek.x-a; by=pionek.y-a; }
         }
        }
damka_czarny();
}
else if(pozycja.x > pionek.x && pozycja.y < pionek.y){
ax=pozycja.x-pionek.x;
ay=pionek.y-pozycja.y;

        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x+a][pionek.y-a]==0) licznik++;
         else if(plansza1[pionek.x+a][pionek.y-a]==1){ bx=pionek.x+a; by=pionek.y-a; }
         }
        }
damka_czarny();
}
else if(pozycja.x < pionek.x && pozycja.y > pionek.y){
ax=pionek.x-pozycja.x;
ay=pozycja.y-pionek.y;

        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x-a][pionek.y+a]==0) licznik++;
         else if(plansza1[pionek.x-a][pionek.y+a]==1){ bx=pionek.x-a; by=pionek.y+a; }
         }
        }
damka_czarny();
}
else if(pozycja.x > pionek.x && pozycja.y > pionek.y){
ax=pozycja.x-pionek.x;
ay=pozycja.y-pionek.y;


        if(ax==ay)
        {
        for(int a=1; a<=ax; a++){
         if(plansza1[pionek.x+a][pionek.y+a]==0) licznik++;
         else if(plansza1[pionek.x+a][pionek.y+a]==1){ bx=pionek.x+a; by=pionek.y+a; }
         }
        }
damka_czarny();
}


}





}



void TWarcaby::blad()
{
ShowMessage("Wyst¹pi³ b³¹d");
}

void TWarcaby::za_niebicie_bialy()
{
        for(int o=0; o<12; o++)
        {
                if(a == bialy[o].x && b == bialy[o].y){
                nr_pionka_bialego1=o;
                bicie_bialy();
                bialy[o].x=200;
                bialy[o].y=200;
                }
        }
plansza1[a][b]=0;
ShowMessage("Za niebicie tracisz ¿ycie :->");
zbitych[0]++;
Label15->Caption=IntToStr(zbitych[0]);
}

void TWarcaby::za_niebicie_czarny()
{
for(int o=0; o<12; o++)
        {
                if(a == czarny[o].x && b == czarny[o].y){
                nr_pionka_czarnego1=o;
                bicie_czarny();
                czarny[o].x=200;
                czarny[o].y=200;
                }
        }
plansza1[a][b]=0;
zbitych[1]++;
Label16->Caption=IntToStr(zbitych[1]);
ShowMessage("Za niebicie tracisz ¿ycie :->");
}

void TWarcaby::ruch_bialy()
{
if(pozycja.y==7 && pozycja.x>=0 && pozycja.x<8){
 damka_bialy1[nr_pionka_bialego]=TRUE;
 Label14->Caption="Gratuluje, zdoby³es damkê.";
}

historia[1].x=pionek.x;
historia[1].y=pionek.y;
historia[0].x=pozycja.x;
historia[0].y=pozycja.y;
cofnij_bialy=TRUE;

maluj_bialy();
plansza1[pozycja.x][pozycja.y]=1;
plansza1[pionek.x][pionek.y]=0;
kolejka=1;
zaznaczony=FALSE;
bialy[nr_pionka_bialego].x=pozycja.x;
bialy[nr_pionka_bialego].y=pozycja.y;
Label14->Caption="Teraz jest ruch gracza zielonego.";
Image26->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_ZIELONY");
}

void TWarcaby::ruch_czarny()
{
if(pozycja.y==0 && pozycja.x>=0 && pozycja.x<8){
 damka_czarny1[nr_pionka_czarnego]=TRUE;
 Label14->Caption="Gratuluje, zdoby³es damkê.";
}

czarny[nr_pionka_czarnego].x=pozycja.x;
czarny[nr_pionka_czarnego].y=pozycja.y;
maluj_czarny();
plansza1[pozycja.x][pozycja.y]=2;
plansza1[pionek.x][pionek.y]=0;
kolejka=0;
zaznaczony=FALSE;
Label14->Caption="Teraz jest ruch gracza ¿ó³tego.";
Image26->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_ZOLTY");
}

void TWarcaby::maluj_bialy()
{
 if(nr_pionka_bialego==0){
 Image2->Left=pozycja.x*40;
 Image2->Top=pozycja.y*40;
         if(damka_bialy1[0]==FALSE) Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
         else Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==8){
 Image10->Left=pozycja.x*40;
 Image10->Top=pozycja.y*40;
          if(damka_bialy1[8]==FALSE) Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
         else Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==9){
 Image11->Left=pozycja.x*40;
 Image11->Top=pozycja.y*40;
         if(damka_bialy1[9]==FALSE) Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
         else Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==10){
 Image12->Left=pozycja.x*40;
 Image12->Top=pozycja.y*40;
        if(damka_bialy1[10]==FALSE) Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
         else Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==11){
 Image13->Left=pozycja.x*40;
 Image13->Top=pozycja.y*40;
        if(damka_bialy1[11]==FALSE) Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==1){
 Image3->Left=pozycja.x*40;
 Image3->Top=pozycja.y*40;
        if(damka_bialy1[1]==FALSE) Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==2){
 Image4->Left=pozycja.x*40;
 Image4->Top=pozycja.y*40;
        if(damka_bialy1[2]==FALSE) Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==3){
 Image5->Left=pozycja.x*40;
 Image5->Top=pozycja.y*40;
        if(damka_bialy1[3]==FALSE) Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==4){
 Image6->Left=pozycja.x*40;
 Image6->Top=pozycja.y*40;
        if(damka_bialy1[4]==FALSE) Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==5){
 Image7->Left=pozycja.x*40;
 Image7->Top=pozycja.y*40;
        if(damka_bialy1[5]==FALSE) Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==6){
 Image8->Left=pozycja.x*40;
 Image8->Top=pozycja.y*40;
        if(damka_bialy1[6]==FALSE) Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }else if(nr_pionka_bialego==7){
 Image9->Left=pozycja.x*40;
 Image9->Top=pozycja.y*40;
        if(damka_bialy1[7]==FALSE) Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
        else Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
 }
}

void TWarcaby::maluj_czarny()
{
 if(nr_pionka_czarnego==0){
 Image14->Left=pozycja.x*40;
 Image14->Top=pozycja.y*40;
        if(damka_czarny1[0]==FALSE) Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==1){
 Image15->Left=pozycja.x*40;
 Image15->Top=pozycja.y*40;
        if(damka_czarny1[1]==FALSE) Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==2){
 Image16->Left=pozycja.x*40;
 Image16->Top=pozycja.y*40;
        if(damka_czarny1[2]==FALSE) Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==3){
 Image17->Left=pozycja.x*40;
 Image17->Top=pozycja.y*40;
        if(damka_czarny1[3]==FALSE) Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==4){
 Image18->Left=pozycja.x*40;
 Image18->Top=pozycja.y*40;
        if(damka_czarny1[4]==FALSE) Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==5){
 Image19->Left=pozycja.x*40;
 Image19->Top=pozycja.y*40;
        if(damka_czarny1[5]==FALSE) Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==6){
 Image20->Left=pozycja.x*40;
 Image20->Top=pozycja.y*40;
        if(damka_czarny1[6]==FALSE) Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==7){
 Image21->Left=pozycja.x*40;
 Image21->Top=pozycja.y*40;
        if(damka_czarny1[7]==FALSE) Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==8){
 Image22->Left=pozycja.x*40;
 Image22->Top=pozycja.y*40;
        if(damka_czarny1[8]==FALSE) Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==9){
 Image23->Left=pozycja.x*40;
 Image23->Top=pozycja.y*40;
        if(damka_czarny1[9]==FALSE) Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==10){
 Image24->Left=pozycja.x*40;
 Image24->Top=pozycja.y*40;
       if(damka_czarny1[10]==FALSE) Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
 }else if(nr_pionka_czarnego==11){
 Image25->Left=pozycja.x*40;
 Image25->Top=pozycja.y*40;
        if(damka_czarny1[11]==FALSE) Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
        else Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
        }
}

void TWarcaby::plansza_inicjuj()
{
Image2->Visible=TRUE; Image3->Visible=TRUE;
Image4->Visible=TRUE; Image5->Visible=TRUE;
Image6->Visible=TRUE; Image7->Visible=TRUE;
Image8->Visible=TRUE; Image9->Visible=TRUE;
Image10->Visible=TRUE; Image11->Visible=TRUE;
Image12->Visible=TRUE; Image13->Visible=TRUE;
Image14->Visible=TRUE; Image15->Visible=TRUE;
Image16->Visible=TRUE; Image17->Visible=TRUE;
Image18->Visible=TRUE; Image19->Visible=TRUE;
Image20->Visible=TRUE; Image21->Visible=TRUE;
Image22->Visible=TRUE; Image23->Visible=TRUE;
Image24->Visible=TRUE; Image25->Visible=TRUE;

for(int m=0; m<12; m++)
{
 for(int n=0; n<12; n++)
  {
        plansza1[m][n]=0;
  }
}
bialy[0].x=0; bialy[0].y=0;
bialy[1].x=2; bialy[1].y=0;
bialy[2].x=4; bialy[2].y=0;
bialy[3].x=6; bialy[3].y=0;
bialy[4].x=1; bialy[4].y=1;
bialy[5].x=3; bialy[5].y=1;
bialy[6].x=5; bialy[6].y=1;
bialy[7].x=7; bialy[7].y=1;
bialy[8].x=0; bialy[8].y=2;
bialy[9].x=2; bialy[9].y=2;
bialy[10].x=4; bialy[10].y=2;
bialy[11].x=6; bialy[11].y=2;

czarny[0].x=1; czarny[0].y=5;
czarny[1].x=3; czarny[1].y=5;
czarny[2].x=5; czarny[2].y=5;
czarny[3].x=7; czarny[3].y=5;
czarny[4].x=0; czarny[4].y=6;
czarny[5].x=2; czarny[5].y=6;
czarny[6].x=4; czarny[6].y=6;
czarny[7].x=6; czarny[7].y=6;
czarny[8].x=1; czarny[8].y=7;
czarny[9].x=3; czarny[9].y=7;
czarny[10].x=5; czarny[10].y=7;
czarny[11].x=7; czarny[11].y=7;

plansza1[0][0]=1; plansza1[2][0]=1;
plansza1[4][0]=1; plansza1[6][0]=1;
plansza1[1][1]=1; plansza1[3][1]=1;
plansza1[5][1]=1; plansza1[7][1]=1;
plansza1[0][2]=1; plansza1[2][2]=1;
plansza1[4][2]=1; plansza1[6][2]=1;

plansza1[1][5]=2; plansza1[3][5]=2;
plansza1[5][5]=2; plansza1[7][5]=2;
plansza1[0][6]=2; plansza1[2][6]=2;
plansza1[4][6]=2; plansza1[6][6]=2;
plansza1[1][7]=2; plansza1[3][7]=2;
plansza1[5][7]=2; plansza1[7][7]=2;

for(int m=0; m<12; m++)
{
  nr_pionka_bialego=m;
  pozycja.x=bialy[m].x; pozycja.y=bialy[m].y;
  maluj_bialy();

  nr_pionka_czarnego=m;
  pozycja.x=czarny[m].x; pozycja.y=czarny[m].y;
  maluj_czarny();
  damka_bialy1[m]=0;
  damka_czarny1[m]=0;
}


zaznaczony=FALSE;
klikniec=FALSE;
i=0; j=0; k=0;
wykonal_ruch=FALSE;
drugi_ruch=FALSE;
gra_z_komputerem=FALSE;
kolejka=0; ok=TRUE;
sek=0, min=0, sek1=0, srednia=0;
ax=0, ay=0; licznik=0;
nr_pionka_bialego=30;
nr_pionka_czarnego1=30;
nr_pionka_czarnego=30;
nr_pionka_bialego1=30;
Image26->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_ZOLTY");
Label14->Caption="No to zaczynamy! Ruch gracza ¿ó³tego.";
zbitych[0]=0; zbitych[1]=0;
Label15->Caption="0"; Label16->Caption="0";
}

//---------------------------------------------------------------------------
__fastcall TWarcaby::TWarcaby(TComponent* Owner)
        : TForm(Owner)
{
Warcaby->plansza_inicjuj();
}

//---------------------------------------------------------------------------

void __fastcall TWarcaby::Timer1Timer(TObject *Sender)
{
   GetCursorPos(&pozycja);
   pozycja.x=(pozycja.x-Warcaby->Left-36)/40;
   pozycja.y=(pozycja.y-Warcaby->Top-72)/40;

   Label1->Caption=IntToStr(pozycja.y+1)+" : ";
   if(pozycja.x==0) Label1->Caption=Label1->Caption+"A";
   else if(pozycja.x==1) Label1->Caption=Label1->Caption+"B";
   else if(pozycja.x==2) Label1->Caption=Label1->Caption+"C";
   else if(pozycja.x==3) Label1->Caption=Label1->Caption+"D";
   else if(pozycja.x==4) Label1->Caption=Label1->Caption+"E";
   else if(pozycja.x==5) Label1->Caption=Label1->Caption+"F";
   else if(pozycja.x==6) Label1->Caption=Label1->Caption+"G";
   else if(pozycja.x==7) Label1->Caption=Label1->Caption+"H";
}


//---------------------------------------------------------------------------

void __fastcall TWarcaby::bialy2(TObject *Sender)
{
if(kolejka==0 && ok==TRUE){
if(Image2->Visible==TRUE && damka_bialy1[0]==FALSE) Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image3->Visible==TRUE && damka_bialy1[1]==FALSE) Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image4->Visible==TRUE && damka_bialy1[2]==FALSE) Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image5->Visible==TRUE && damka_bialy1[3]==FALSE) Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image6->Visible==TRUE && damka_bialy1[4]==FALSE) Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image7->Visible==TRUE && damka_bialy1[5]==FALSE) Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image8->Visible==TRUE && damka_bialy1[6]==FALSE) Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image9->Visible==TRUE && damka_bialy1[7]==FALSE) Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image10->Visible==TRUE && damka_bialy1[8]==FALSE) Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image11->Visible==TRUE && damka_bialy1[9]==FALSE) Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image12->Visible==TRUE && damka_bialy1[10]==FALSE) Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");
if(Image13->Visible==TRUE && damka_bialy1[11]==FALSE) Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK");
else Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA1");

pionek.x=pozycja.x;
pionek.y=pozycja.y;
zaznaczony=TRUE;

for(int m=0; m<12; m++)
        {
                if(pionek.x == bialy[m].x && pionek.y == bialy[m].y){
                nr_pionka_bialego=m;
                }
        }



if(nr_pionka_bialego==0 && damka_bialy1[0]==FALSE) Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==1 && damka_bialy1[1]==FALSE) Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==2 && damka_bialy1[2]==FALSE) Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==3 && damka_bialy1[3]==FALSE) Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==4 && damka_bialy1[4]==FALSE) Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==5 && damka_bialy1[5]==FALSE) Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==6 && damka_bialy1[6]==FALSE) Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==7 && damka_bialy1[7]==FALSE) Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==8 && damka_bialy1[8]==FALSE) Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==9 && damka_bialy1[9]==FALSE) Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==10 && damka_bialy1[10]==FALSE) Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");
else if(nr_pionka_bialego==11 && damka_bialy1[11]==FALSE) Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK1");

else if(nr_pionka_bialego==0 && damka_bialy1[0]==TRUE) Image2->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==1 && damka_bialy1[1]==TRUE) Image3->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==2 && damka_bialy1[2]==TRUE) Image4->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==3 && damka_bialy1[3]==TRUE) Image5->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==4 && damka_bialy1[4]==TRUE) Image6->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==5 && damka_bialy1[5]==TRUE) Image7->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==6 && damka_bialy1[6]==TRUE) Image8->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==7 && damka_bialy1[7]==TRUE) Image9->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==8 && damka_bialy1[8]==TRUE) Image10->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==9 && damka_bialy1[9]==TRUE) Image11->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==10 && damka_bialy1[10]==TRUE) Image12->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");
else if(nr_pionka_bialego==11 && damka_bialy1[11]==TRUE) Image13->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA4");

}
}
//---------------------------------------------------------------------------


void __fastcall TWarcaby::czarny2(TObject *Sender)
{
if(kolejka==1 && ok==TRUE){
if(Image14->Visible==TRUE && damka_czarny1[0]==FALSE)Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image15->Visible==TRUE && damka_czarny1[1]==FALSE)Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image16->Visible==TRUE && damka_czarny1[2]==FALSE)Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image17->Visible==TRUE && damka_czarny1[3]==FALSE)Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image18->Visible==TRUE && damka_czarny1[4]==FALSE)Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image19->Visible==TRUE && damka_czarny1[5]==FALSE)Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image20->Visible==TRUE && damka_czarny1[6]==FALSE)Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image21->Visible==TRUE && damka_czarny1[7]==FALSE)Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image22->Visible==TRUE && damka_czarny1[8]==FALSE)Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image23->Visible==TRUE && damka_czarny1[9]==FALSE)Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image24->Visible==TRUE && damka_czarny1[10]==FALSE)Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");
if(Image25->Visible==TRUE && damka_czarny1[11]==FALSE)Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK2");
else Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA2");

pionek.x=pozycja.x;
pionek.y=pozycja.y;
zaznaczony=TRUE;

for(int m=0; m<12; m++)
        {
                if(pionek.x == czarny[m].x && pionek.y == czarny[m].y){
                nr_pionka_czarnego=m;
                }
        }
       
if(nr_pionka_czarnego==0 && damka_czarny1[0]==FALSE) Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==1 && damka_czarny1[1]==FALSE) Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==2 && damka_czarny1[2]==FALSE) Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==3 && damka_czarny1[3]==FALSE) Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==4 && damka_czarny1[4]==FALSE) Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==5 && damka_czarny1[5]==FALSE) Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==6 && damka_czarny1[6]==FALSE) Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==7 && damka_czarny1[7]==FALSE) Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==8 && damka_czarny1[8]==FALSE) Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==9 && damka_czarny1[9]==FALSE) Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==10 && damka_czarny1[10]==FALSE) Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");
else if(nr_pionka_czarnego==11 && damka_czarny1[11]==FALSE) Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_PIONEK3");

else if(nr_pionka_czarnego==0 && damka_czarny1[0]==TRUE) Image14->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==1 && damka_czarny1[1]==TRUE) Image15->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==2 && damka_czarny1[2]==TRUE) Image16->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==3 && damka_czarny1[3]==TRUE) Image17->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==4 && damka_czarny1[4]==TRUE) Image18->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==5 && damka_czarny1[5]==TRUE) Image19->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==6 && damka_czarny1[6]==TRUE) Image20->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==7 && damka_czarny1[7]==TRUE) Image21->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==8 && damka_czarny1[8]==TRUE) Image22->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==9 && damka_czarny1[9]==TRUE) Image23->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==10 && damka_czarny1[10]==TRUE) Image24->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
else if(nr_pionka_czarnego==11 && damka_czarny1[11]==TRUE) Image25->Picture->Bitmap->Handle = LoadBitmap(HInstance, "ID_DAMA3");
}
}
//---------------------------------------------------------------------------


void __fastcall TWarcaby::Informacje1Click(TObject *Sender)
{
Informacje->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TWarcaby::Biciedotyu1Click(TObject *Sender)
{
if(biciedotylu==TRUE){
Biciedotyu1->Checked=FALSE;
biciedotylu=FALSE;
}
else if(biciedotylu==FALSE){
Biciedotyu1->Checked=TRUE;
biciedotylu=TRUE;
}
}
//---------------------------------------------------------------------------

void __fastcall TWarcaby::GraczvsGracz1Click(TObject *Sender)
{
plansza_inicjuj();
Panel1->Enabled=TRUE;
gra_z_komputerem=FALSE;
}

//---------------------------------------------------------------------------

void __fastcall TWarcaby::Zaniebicietraciszycie1Click(TObject *Sender)
{
if(zaniebicie==TRUE){
Zaniebicietraciszycie1->Checked=FALSE;
zaniebicie=FALSE;
}
else if(zaniebicie==FALSE){
Zaniebicietraciszycie1->Checked=TRUE;
zaniebicie=TRUE;
}
}
//---------------------------------------------------------------------------

void __fastcall TWarcaby::N1player1Click(TObject *Sender)
{
gra_z_komputerem=TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TWarcaby::Koniec1Click(TObject *Sender)
{
exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TWarcaby::Timer2Timer(TObject *Sender)
{
if(sek<10 && min<10) Label4->Caption="0"+IntToStr(min)+" : 0"+IntToStr(sek);
else Label4->Caption="0"+IntToStr(min)+" : "+IntToStr(sek);
sek++;
if(sek>60){ sek=0; min++; }

sek1++;
}
//---------------------------------------------------------------------------


