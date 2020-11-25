//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TWarcaby : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TImage *Image1;
        TTimer *Timer1;
        TMainMenu *MainMenu1;
        TMenuItem *Plik1;
        TMenuItem *Opcje1;
        TMenuItem *Ogrze1;
        TLabel *Label2;
        TImage *Image2;
        TMenuItem *Nowagra1;
        TMenuItem *Koniec1;
        TMenuItem *Biciedotyu1;
        TMenuItem *Informacje1;
        TMenuItem *N3;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TImage *Image8;
        TImage *Image9;
        TImage *Image10;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TImage *Image14;
        TImage *Image15;
        TImage *Image16;
        TImage *Image17;
        TImage *Image18;
        TImage *Image19;
        TImage *Image20;
        TImage *Image21;
        TImage *Image22;
        TImage *Image23;
        TImage *Image24;
        TImage *Image25;
        TMenuItem *GraczvsGracz1;
        TMenuItem *Zaniebicietraciszycie1;
        TShape *Shape1;
        TLabel *Label1;
        TImage *Image27;
        TImage *Image26;
        TLabel *Label3;
        TLabel *Label4;
        TTimer *Timer2;
        TImage *Image29;
        TLabel *Label13;
        TLabel *Label14;
        TBevel *Bevel1;
        TLabel *Label15;
        TLabel *Label16;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall bialy2(TObject *Sender);
        void __fastcall czarny2(TObject *Sender);
        void __fastcall Informacje1Click(TObject *Sender);
        void __fastcall Biciedotyu1Click(TObject *Sender);
        void __fastcall GraczvsGracz1Click(TObject *Sender);
        void __fastcall klik(TObject *Sender);
        void __fastcall Zaniebicietraciszycie1Click(TObject *Sender);
        void __fastcall N1player1Click(TObject *Sender);
        void __fastcall Koniec1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
void plansza_inicjuj();
void maluj_czarny();
void maluj_bialy();
void bicie_czarny();
void bicie_bialy();
void blad();
void ruch_bialy();
void ruch_czarny();
void dama_bialy();
void dama_czarny();
void za_niebicie_bialy();
void za_niebicie_czarny();
void bicie_drugie_bialy();
void bicie_drugie_czarny();
void bicie_drugie_bialy1();
void bicie_drugie_czarny1();
void damka_bialy();
void damka_czarny();
__fastcall TWarcaby(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWarcaby *Warcaby;
//---------------------------------------------------------------------------
#endif
