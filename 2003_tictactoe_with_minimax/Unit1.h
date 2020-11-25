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
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TKolko : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TMainMenu *MainMenu1;
        TMenuItem *Plik1;
        TImage *Image2;
        TImage *Image7;
        TTimer *Timer1;
        TLabel *Label1;
        TMenuItem *Koniec1;
        TMenuItem *Nowagra1;
        TMenuItem *N1;
        TMenuItem *Pomoc1;
        TMenuItem *Oprogramie1;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TImage *Image8;
        TImage *Image9;
        TImage *Image10;
        TImage *Image11;
        TMenuItem *gracz1vsgracz21;
        TMenuItem *gracz1vsPC1;
        TMenuItem *atwo1;
        TMenuItem *trudno1;
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Koniec1Click(TObject *Sender);
        void __fastcall Oprogramie1Click(TObject *Sender);
        void __fastcall gracz1vsgracz21Click(TObject *Sender);
        void __fastcall atwo1Click(TObject *Sender);
        void __fastcall trudno1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
void postaw_kolko(int element);
void postaw_krzyzyk(int element);
void Nowa_gra();
        __fastcall TKolko(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKolko *Kolko;
//---------------------------------------------------------------------------
#endif
 