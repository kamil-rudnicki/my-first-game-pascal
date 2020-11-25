//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "cdiroutl.h"
#include <Grids.hpp>
#include <Outline.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TTapeter : public TForm
{
__published:	// IDE-managed Components
        TButton *Button5;
        TOpenPictureDialog *OpenPictureDialog1;
        TListBox *ListBox1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button6;
        TGroupBox *GroupBox1;
        TButton *Button3;
        TButton *Button4;
        TPageControl *Informacje;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox2;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label7;
        TLabel *Label8;
        TMemo *Memo1;
        TImage *Image1;
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall sprawdz(TObject *Sender, char &Key);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall sdf(TObject *Sender);
private:	// User declarations
void ListujKatalogi(String Path);
public:		// User declarations
        __fastcall TTapeter(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTapeter *Tapeter;
//---------------------------------------------------------------------------
#endif
