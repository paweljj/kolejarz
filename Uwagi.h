//---------------------------------------------------------------------------

#ifndef UwagiH
#define UwagiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFUwagi : public TForm
{
__published:	// IDE-managed Components
        TMemo *MUwagi;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TFUwagi(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFUwagi *FUwagi;
//---------------------------------------------------------------------------
#endif
