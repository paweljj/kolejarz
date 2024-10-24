//----------------------------------------------------------------------------
#ifndef PoczatekH
#define PoczatekH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TFPoczatek : public TForm
{
__published:
	TButton *OKBtn;
        TLabel *LNazwa;
        TRadioGroup *RadioGroup1;
        TRadioGroup *RadioGroup2;
        TCheckBox *CBSzopa;
        TCheckBox *CBPodglad;
        TButton *BUwagi;
        TCheckBox *CBGraTestowa;
        TCheckBox *CBPunktyKarne;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BUwagiClick(TObject *Sender);
private:
public:
	virtual __fastcall TFPoczatek(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TFPoczatek *FPoczatek;
//----------------------------------------------------------------------------
#endif    
