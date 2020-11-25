//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <stdlib.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
int tapeta=0, ilosc=0;
bool losowa;


TIniFile *Ini = new
    TIniFile(ExtractFileDir(Application->ExeName) + "\\Ustawienia.ini");
    ilosc=Ini->ReadInteger("Ustawienia","ilosc_tapet", 0);
    if(ilosc<=0){delete Ini; exit(1); }
    losowa=Ini->ReadBool("Ustawienia","tapeta_losowa", false);


if(!losowa){
tapeta=Ini->ReadInteger("Ustawienia","aktualna_tapeta", 0);
tapeta++;
if(tapeta>ilosc) tapeta=1;
Ini->WriteInteger("Ustawienia","aktualna_tapeta", tapeta);


AnsiString AS = Ini->ReadString("Tapety",IntToStr(tapeta), "Nie znaleziono wartoœci!");
char* ch = AS.c_str();
SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, ch, SPIF_UPDATEINIFILE || SPIF_SENDWININICHANGE);
}

else{
randomize();
int losowa=random(ilosc)+1;
Ini->WriteInteger("Ustawienia","aktualna_tapeta", losowa);

AnsiString AS = Ini->ReadString("Tapety",IntToStr(losowa), "Nie znaleziono wartoœci!");
char* ch = AS.c_str();
SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, ch, SPIF_UPDATEINIFILE || SPIF_SENDWININICHANGE);
}


delete Ini;
exit(1);
}
//---------------------------------------------------------------------------
