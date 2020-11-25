//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TInformacje : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
private:	// User declarations
public:		// User declarations
        __fastcall TInformacje(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInformacje *Informacje;
//---------------------------------------------------------------------------
#endif
