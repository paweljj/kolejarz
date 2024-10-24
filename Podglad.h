//---------------------------------------------------------------------------

#ifndef PodgladH
#define PodgladH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFPodgladSkladu : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *SBTlo;
        TImage *IPodglad;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TFPodgladSkladu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPodgladSkladu *FPodgladSkladu;
//---------------------------------------------------------------------------
#endif
