//---------------------------------------------------------------------------

#ifndef WjazdWyjazdH
#define WjazdWyjazdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFWjazdWyjazd : public TForm
{
__published:	// IDE-managed Components
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFWjazdWyjazd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFWjazdWyjazd *FWjazdWyjazd;
//---------------------------------------------------------------------------
#endif
