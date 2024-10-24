//---------------------------------------------------------------------------

#ifndef OMijankaH
#define OMijankaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFMijanka : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *BZezwalam;
        TButton *BCzekaj;
        TEdit *ECzekaj;
        TLabel *Label1;
        TPanel *PNapis;
        TLabel *LTekst;
        TPanel *PTytul;
        TPaintBox *PBMijanka;
        void __fastcall BZezwalamClick(TObject *Sender);
        void __fastcall BCzekajClick(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFMijanka(TComponent* Owner);
        int Czekaj;
        int Numer;
        int Wspolrzedne;
};
//---------------------------------------------------------------------------
extern PACKAGE TFMijanka *FMijanka;
//---------------------------------------------------------------------------
#endif
