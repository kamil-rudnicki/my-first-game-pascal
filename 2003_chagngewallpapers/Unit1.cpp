//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

int ilosctapet=0;

#include <Registry.hpp>
#include <inifiles.hpp>
#include <FileCtrl.hpp>
#include "Unit1.h"
#include "Unit2.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma resource "*.dfm"
TTapeter *Tapeter;
//---------------------------------------------------------------------------
__fastcall TTapeter::TTapeter(TComponent* Owner)
        : TForm(Owner)
{
    TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    ilosctapet=Ini->ReadInteger("Ustawienia","ilosc_tapet", 0);
    for(int i=1; i<=ilosctapet; i++)
    {
    ListBox1->Items->Add(IntToStr(i)+".  "+Ini->ReadString("Tapety",IntToStr(i), "Nie znaleziono wartoœci!"));
    }

    if(Ini->ReadBool("Ustawienia","tapeta_losowa", true)==true){
    RadioButton1->Checked=false;
    RadioButton2->Checked=true;
    }else{
    RadioButton2->Checked=false;
    RadioButton1->Checked=true;
    }
    delete Ini;

TRegistry& klucz = *new TRegistry();
klucz.OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true/*cancreate*/);
    try
    {klucz.WriteString("Tapeter",ExtractFileDir(Application->ExeName)+"\\Pliki\\zmieniacz.exe");}
    catch (...)
    {}
delete &klucz;
}
//---------------------------------------------------------------------------


void __fastcall TTapeter::Button3Click(TObject *Sender)
{
TRegistry& klucz = *new TRegistry();
klucz.OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true/*cancreate*/);

    try
    {klucz.WriteString("Tapeter",ExtractFileDir(Application->ExeName)+"\\Pliki\\zmieniacz.exe");}
    catch (...)
    {ShowMessage("Dodanie programu do autostartu\nnie powiod³o siê.");}
    ShowMessage("Dodanie programu do autostartu\npowiod³o siê!");
delete &klucz;
}
//---------------------------------------------------------------------------

void __fastcall TTapeter::Button4Click(TObject *Sender)
{
TRegistry& klucz = *new TRegistry();
klucz.OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true/*cancreate*/);
if (klucz.DeleteValue("Tapeter")) ShowMessage("Usuniêcie programu z autostartu powiod³o siê!\nUwaga, program sam dodaje siê do autostartu przy uruchomieniu.");
else {ShowMessage("Usuniêcie programu z autostartu\nnie powiod³o siê!");}
delete &klucz;
}
//---------------------------------------------------------------------------

void __fastcall TTapeter::Button5Click(TObject *Sender)
{
if(OpenPictureDialog1->Execute()){
    try{
    TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");

    ilosctapet++;
    Ini->WriteInteger("Ustawienia","ilosc_tapet", ilosctapet);
    Ini->WriteString("Tapety",IntToStr(ilosctapet), OpenPictureDialog1->FileName);

    ListBox1->Clear();
    for(int i=1; i<=ilosctapet; i++){
    ListBox1->Items->Add(IntToStr(i)+".  "+Ini->ReadString("Tapety",IntToStr(i), "Nie znaleziono wartoœci!"));
    }
delete Ini;
   }
  catch(Exception &e){
      ShowMessage("Nieprawid³owy plik graficzny!\n" + e.Message);
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TTapeter::Button6Click(TObject *Sender)
{
TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    ilosctapet=0;
    Ini->WriteInteger("Ustawienia","ilosc_tapet", ilosctapet);
    Ini->WriteInteger("Ustawienia","aktualna_tapeta", 0);
    Ini->EraseSection("Tapety");
    ListBox1->Clear();
delete Ini;
}
//---------------------------------------------------------------------------



void __fastcall TTapeter::RadioButton1Click(TObject *Sender)
{
    TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    Ini->WriteBool("Ustawienia","tapeta_losowa", false);
    delete Ini;
}
//---------------------------------------------------------------------------

void __fastcall TTapeter::RadioButton2Click(TObject *Sender)
{
    TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    Ini->WriteBool("Ustawienia","tapeta_losowa", true);
    delete Ini;        
}
//---------------------------------------------------------------------------


void __fastcall TTapeter::Button1Click(TObject *Sender)
{
int ktory=ListBox1->ItemIndex+1;
if(ktory<=ilosctapet && ktory>=1){

TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    ilosctapet=ilosctapet-1;
    Ini->WriteInteger("Ustawienia","ilosc_tapet", ilosctapet);
    Ini->WriteInteger("Ustawienia","aktualna_tapeta", 0);

String *sciezki = new String[ilosctapet];
int li1=0;
int li2=0;
while(li1<=ilosctapet){
if(ktory-1==li1){li1++; continue; }

sciezki[li2]=Ini->ReadString("Tapety",IntToStr(li1+1), "Nie znaleziono wartoœci!");
li1++; li2++;
}

Ini->EraseSection("Tapety");
for(int i=1; i<=ilosctapet; i++)
{
Ini->WriteString("Tapety",IntToStr(i), sciezki[i-1]);
}

ListBox1->Items->Clear();
for(int i=1; i<=ilosctapet; i++)
{
ListBox1->Items->Add(IntToStr(i)+".  "+Ini->ReadString("Tapety",IntToStr(i), "Nie znaleziono wartoœci!"));
}

delete Ini;
}
}
//---------------------------------------------------------------------------

void __fastcall TTapeter::sprawdz(TObject *Sender, char &Key)
{
if ((Key!='0')&&(Key!='1')&&(Key!='2')&&(Key!='3')&&(Key!='4')&&
(Key!='5')&&(Key!='6')&&(Key!='7')&&(Key!='8')&&(Key!='9')&&(Key!=8))
{Key=0;}
}
//---------------------------------------------------------------------------

void TTapeter::ListujKatalogi(String Path)
{
   TSearchRec sr;
   int result;

   result = FindFirst(Path + "*.*", faAnyFile, sr);
   TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");

   while (result == 0)
   {
      if ((sr.Name != ".") && (sr.Name != "..") && (!(sr.Attr & faDirectory) > 0))
      {
         AnsiString NazwaPliku = Path + sr.Name;

         if(ExtractFileExt(NazwaPliku)==".bmp"){
         ilosctapet++;
    Ini->WriteInteger("Ustawienia","ilosc_tapet", ilosctapet);
    Ini->WriteString("Tapety",IntToStr(ilosctapet), NazwaPliku);
         }
      }
      result = FindNext(sr);
   }
   delete Ini;
   FindClose(sr);
}



void __fastcall TTapeter::Button2Click(TObject *Sender)
{

Form2->ShowModal();
TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    if(Ini->ReadString("Katalog","kat", "")!=""){

      if (DirectoryExists(Ini->ReadString("Katalog","kat", "")))
      {
         ListBox1->Items->Clear();
         ListujKatalogi(Ini->ReadString("Katalog","kat", "") + "\\");
      }
    for(int i=1; i<=ilosctapet; i++){
    ListBox1->Items->Add(IntToStr(i)+".  "+Ini->ReadString("Tapety",IntToStr(i), "Nie znaleziono tapety!"));
    }
    Ini->WriteString("Katalog","kat", "");
    }
delete Ini;
}
//---------------------------------------------------------------------------


void __fastcall TTapeter::sdf(TObject *Sender)
{
int ktory=ListBox1->ItemIndex+1;
TIniFile *Ini = new
TIniFile(ExtractFileDir(Application->ExeName) + "\\Pliki\\Ustawienia.ini");
    Image1->Picture->LoadFromFile(Ini->ReadString("Tapety",IntToStr(ktory), "Nie znaleziono wartoœci!"));
delete Ini;
}
//---------------------------------------------------------------------------

