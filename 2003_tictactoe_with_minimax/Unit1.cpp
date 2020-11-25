#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TKolko *Kolko;

bool nadwoch=true;

#include "funkcje.h"
#include "ewaluacja.h"
//---------------------------------------------------------------------------
__fastcall TKolko::TKolko(TComponent* Owner)
        : TForm(Owner)
{
Image1->Enabled=false;
}
//---------------------------------------------------------------------------

void TKolko::Nowa_gra()
{
        Image2->Visible=false; Image7->Visible=false;
        Image3->Visible=false; Image8->Visible=false;
        Image4->Visible=false; Image9->Visible=false;
        Image5->Visible=false; Image10->Visible=false;
        Image6->Visible=false; Image11->Visible=false;
        for(int i=0; i<9; i++) v[i]=nic;
        ilosc_krzyzykow=0;
        ilosc_kolek=0;
}

void SprawdzCzyKoniecGry(KTO plansza[9])
{
int wynik=KoniecGry(plansza);
if(wynik)
 {
 if(nadwoch==false){
        if(plansza[wynik]==komputer) ShowMessage("You lose. :-(");
        else ShowMessage("Gratulacje, wygra³eœ :-)"); }
 else{
        if(plansza[wynik]==komputer) ShowMessage("Wygra³ krzy¿yk!!!");
        else ShowMessage("Wygra³o kó³ko!!!"); }
 Kolko->Nowa_gra();
 MessageBeep(0xFFFFFFFF);
 }

KANDYDACI nastepni=generuj_ruchy(plansza);
if(nastepni.cpt==-1){ ShowMessage("Remis. :-|"); Kolko->Nowa_gra(); MessageBeep(0xFFFFFFFF);}
}



void __fastcall TKolko::Image1Click(TObject *Sender)
{
//kiedy sie rusza czlowiek
if(aktualny_gracz==czlowiek)
{
   GetCursorPos(&pozycja_kursora);
   pozycja_kursora.x=((pozycja_kursora.x-Kolko->Left-Image1->Left-4)/100);
   pozycja_kursora.y=((pozycja_kursora.y-Kolko->Top-Image1->Top-40)/100);

   int a;
   a=wspolrzedne_na_element(pozycja_kursora);
   if(v[a]==nic)
   {
        postaw_kolko(a);
        v[a]=czlowiek;
        SprawdzCzyKoniecGry(v);
        aktualny_gracz=Nastepny_Gracz(aktualny_gracz);

   }
}else if(aktualny_gracz==komputer && nadwoch==true)
{
   GetCursorPos(&pozycja_kursora);
   pozycja_kursora.x=((pozycja_kursora.x-Kolko->Left-Image1->Left-4)/100);
   pozycja_kursora.y=((pozycja_kursora.y-Kolko->Top-Image1->Top-40)/100);

   int a;
   a=wspolrzedne_na_element(pozycja_kursora);
   if(v[a]==nic)
   {
        postaw_krzyzyk(a);
        v[a]=komputer;
        SprawdzCzyKoniecGry(v);
        aktualny_gracz=Nastepny_Gracz(aktualny_gracz);
   }
}
}
//---------------------------------------------------------------------------

POLE wybor;

void __fastcall TKolko::Timer1Timer(TObject *Sender)
{
if(aktualny_gracz==komputer && nadwoch==false)
{
Image1->Enabled=false;
        aktualny_gracz=Nastepny_Gracz(aktualny_gracz);


        int pol=Minimax(komputer, 0, v).gracz;
        postaw_krzyzyk(pol);
        v[pol]=komputer;

    
        SprawdzCzyKoniecGry(v);
Image1->Enabled=true;
}
}
//---------------------------------------------------------------------------


void __fastcall TKolko::Koniec1Click(TObject *Sender)
{
exit(1);
}
//---------------------------------------------------------------------------


void __fastcall TKolko::Oprogramie1Click(TObject *Sender)
{
   ShowMessage("Kó³ko i krzy¿yk\n\nBy: Kamil Rudnicki\nkamil1616@poczta.fm\nhttp://kamilrudnicki.w.interia.pl");
}
//---------------------------------------------------------------------------


void __fastcall TKolko::gracz1vsgracz21Click(TObject *Sender)
{
 nadwoch=true;
 Kolko->Nowa_gra();
 Image1->Enabled=true;
 Label1->Caption="By: Kamil Rudnicki";
}
//---------------------------------------------------------------------------


void __fastcall TKolko::atwo1Click(TObject *Sender)
{
  nadwoch=false;
  Kolko->Nowa_gra();
  GLEBOKOSC_OK=1;
  Image1->Enabled=true;
  Label1->Caption="By: Kamil Rudnicki";
}
//---------------------------------------------------------------------------


void __fastcall TKolko::trudno1Click(TObject *Sender)
{
  nadwoch=false;
  Kolko->Nowa_gra();
  GLEBOKOSC_OK=1000;
  Image1->Enabled=true;
  Label1->Caption="By: Kamil Rudnicki";
}
//---------------------------------------------------------------------------

