//----------------------------------------------------------------------------
#ifndef OpcjeH
#define OpcjeH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//#include <Grids.hpp>
#include "CSPIN.h"
#include <Dialogs.hpp>
#include <MPlayer.hpp>
//----------------------------------------------------------------------------
class TFOpcje : public TForm
{
__published:
	TPanel *Panel1;
	TPanel *Panel2;
        TPageControl *PageControl;
        TTabSheet *TSZegar;
        TTabSheet *TSOpoznienie;
        TTabSheet *TSOpcje;
	TButton *OKBtn;
	TButton *CancelBtn;
	TButton *HelpBtn;
        TEdit *EWyprzedzenie;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *E1;
        TEdit *E2;
        TEdit *E3;
        TEdit *E4;
        TEdit *E5;
        TEdit *E6;
        TEdit *E7;
        TEdit *E8;
        TEdit *E9;
        TEdit *E10;
        TLabel *Label8;
        TLabel *Label9;
        TTrackBar *TBSzybkosc;
        TCheckBox *CBCzasRzeczywisty;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *E11;
        TEdit *E12;
        TRadioGroup *RadioGroup1;
        TCheckBox *CBZaznaczanie;
        TCheckBox *CBPodglad;
        TRadioGroup *RadioGroup2;
        TRadioButton *RBCaly;
        TRadioButton *RBNieCaly;
        TEdit *EPierwszych;
        TLabel *Label13;
        TCheckBox *CBNieaktywne;
        TCheckBox *CBRozmiar;
        TTabSheet *TBKolory;
        TColorDialog *CDKolory;
        TCheckBox *CBTlo;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *ESchemat;
        TButton *BZmien1;
        TEdit *EPrzyjazdy;
        TEdit *EOdjazdy;
        TEdit *EPodglad;
        TButton *BZmien2;
        TButton *BZmien3;
        TButton *Button4;
        TTabSheet *TSDzwieki;
        TCheckBox *CBDzwiek;
        TLabel *Label18;
        TGroupBox *GBDzwieki;
        TCheckBox *CBNowyPociag;
        TCheckBox *CBMijanka;
        TCheckBox *CBOpoznienie;
        TCheckBox *CBOdjazd;
        TCheckBox *CBPktKarne;
        TCheckBox *CBBlad;
        TButton *BNowyPociag;
        TButton *BMijanka;
        TButton *BOpoznienie;
        TButton *BOdjazd;
        TButton *BPktKarne;
        TButton *BBlad;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TLabel *LNowyPociag;
        TLabel *LMijanka;
        TLabel *LOpoznienie;
        TLabel *LOdjazd;
        TLabel *LPktKarne;
        TLabel *LBlad;
        TOpenDialog *OPDzwieki;
        TMediaPlayer *MPDzwieki;
        void __fastcall OKBtnClick(TObject *Sender);
        void __fastcall EWyprzedzenieExit(TObject *Sender);
        void __fastcall E1Exit(TObject *Sender);
        void __fastcall E2Exit(TObject *Sender);
        void __fastcall E3Exit(TObject *Sender);
        void __fastcall E4Exit(TObject *Sender);
        void __fastcall E5Exit(TObject *Sender);
        void __fastcall E6Exit(TObject *Sender);
        void __fastcall E7Exit(TObject *Sender);
        void __fastcall E8Exit(TObject *Sender);
        void __fastcall E9Change(TObject *Sender);
        void __fastcall E10Change(TObject *Sender);
        void __fastcall TBSzybkoscChange(TObject *Sender);
        void __fastcall CBCzasRzeczywistyClick(TObject *Sender);
        void __fastcall E11Exit(TObject *Sender);
        void __fastcall E12Exit(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CBZaznaczanieClick(TObject *Sender);
        void __fastcall BZmien1Click(TObject *Sender);
        void __fastcall BZmien2Click(TObject *Sender);
        void __fastcall BZmien3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CBDzwiekClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall BNowyPociagClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall BMijankaClick(TObject *Sender);
        void __fastcall BOpoznienieClick(TObject *Sender);
        void __fastcall BOdjazdClick(TObject *Sender);
        void __fastcall BPktKarneClick(TObject *Sender);
        void __fastcall BBladClick(TObject *Sender);
        void __fastcall CancelBtnClick(TObject *Sender);
        void __fastcall CBNowyPociagClick(TObject *Sender);
        void __fastcall CBMijankaClick(TObject *Sender);
        void __fastcall CBOpoznienieClick(TObject *Sender);
        void __fastcall CBOdjazdClick(TObject *Sender);
        void __fastcall CBPktKarneClick(TObject *Sender);
        void __fastcall CBBladClick(TObject *Sender);
        void __fastcall TSDzwiekiShow(TObject *Sender);
private:
        bool CzyZmiana;
        int Wyprzedzenie;
        bool PlusMinus;
public:
	virtual __fastcall TFOpcje(TComponent* AOwner);

};
//----------------------------------------------------------------------------
extern PACKAGE TFOpcje *FOpcje;
//----------------------------------------------------------------------------
#endif    
