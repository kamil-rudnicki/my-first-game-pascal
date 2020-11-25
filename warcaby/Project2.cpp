//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Warcaby);
USEFORM("Unit2.cpp", Informacje);
USEFORM("Unit3.cpp", Form3);

#include "Unit3.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
		    TForm3* SplashScreen = new TForm3(Application);
  			SplashScreen->Show();
  			 SplashScreen->Update();
                 Application->Title = "Warcaby";
                 Application->CreateForm(__classid(TWarcaby), &Warcaby);
                 Application->CreateForm(__classid(TInformacje), &Informacje);
                 
  Sleep(2000); 
   delete SplashScreen;
Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
