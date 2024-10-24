//---------------------------------------------------------------------------

#ifndef OLokomH
#define OLokomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFLokomot : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *BZamknij;
        TPaintBox *PBLoki;
        TListBox *LBSzopy;
        void __fastcall PBLokiPaint(TObject *Sender);
        void __fastcall PBLokiMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall LBSzopyClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TFLokomot(TComponent* Owner);
        void __fastcall Rysuj(void); 

#define ILOSC_LOKOW 51
        int Rodzaje[12][2][ILOSC_LOKOW];
        int XX;
        int YY;
};
//---------------------------------------------------------------------------
extern PACKAGE TFLokomot *FLokomot;
//---------------------------------------------------------------------------
#endif
