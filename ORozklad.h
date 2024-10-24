//---------------------------------------------------------------------------
#ifndef ORozkladH
#define ORozkladH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TFRozklad : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *SBTlo;
        TImage *ITabela;
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        int rodzaj;
public:		// User declarations
        __fastcall TFRozklad(TComponent* Owner);
        void __fastcall Rodzaj(int r){rodzaj=r;};
};
//---------------------------------------------------------------------------
extern PACKAGE TFRozklad *FRozklad;
//---------------------------------------------------------------------------
#endif
