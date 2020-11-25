//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
Edit1->Text=DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    Ini->WriteString("Katalog","kat", "");
delete Ini;
Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::DirectoryListBox1Change(TObject *Sender)
{
Edit1->Text=DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    Ini->WriteString("Katalog","kat", Edit1->Text);
delete Ini;
Close();
}
//---------------------------------------------------------------------------
