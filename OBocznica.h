//---------------------------------------------------------------------------

#ifndef OBocznicaH
#define OBocznicaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFBocznica : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PBBocznica;
        TPanel *Panel1;
        TButton *BOK;
        void __fastcall PBBocznicaPaint(TObject *Sender);
        void __fastcall PBBocznicaMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PBBocznicaMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Panel1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall BOKMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
        int pozycja;  //pozycja bocznicy w tabeli pkt_postojowe
        int poczatek; //pocztek bocznicy w stan_postojowych
        int koniec;   //koniec bocznicy w stan postojowych
        int wsp;      //wpolrzedne punktu

        int Wagony[20][10];
        int Semafor[10];
        #define GORA 1
        #define DOL 2
        THintWindow *Dymek;
public:		// User declarations
        __fastcall TFBocznica(TComponent* Owner);
        void __fastcall Parametry(int poz,int pocz, int kon ,int w);
        void __fastcall RysujBocznice(void);

        bool CzyZaznaczanie;
        int Numer; //numer w tabeli stan_postojowych po zaznaczeniu drogi
        bool Wyjscie;
};
#define WYSOKOSC 51
//---------------------------------------------------------------------------
extern PACKAGE TFBocznica *FBocznica;
//---------------------------------------------------------------------------
#endif
