//---------------------------------------------------------------------------
#ifndef FKolejarzH
#define FKolejarzH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------

#include "Stacja.h"
#include <ImgList.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TFGlowna : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *MPlik;
        TMenuItem *MPomoc;
        TStatusBar *StatusBar;
        TPaintBox *PBStacja;
        TBevel *Bevel1;
        TPaintBox *PBPrzyjazdy;
        TBevel *Bevel2;
        TPaintBox *PBOdjazdy;
        TBevel *Bevel3;
        TPaintBox *PBPociag;
        TMenuItem *MOpcje;
        TMenuItem *MOProgramie;
        TMenuItem *MRozklad;
        TMenuItem *MPrzyjazdy;
        TMenuItem *MOdjazdy;
        TTimer *Timer;
        TMenuItem *Nowagra;
        TOpenDialog *ODRozklad;
        TMenuItem *Zapiszgre;
        TMenuItem *Wczytajgre;
        TOpenDialog *ODStan;
        TSaveDialog *SDStan;
        TMenuItem *N2;
        TMenuItem *Tematypomocy1;
        TMenuItem *MZegar;
        TMenuItem *MOpoznienia;
        TMenuItem *N3;
        TMenuItem *MPauza;
        TMenuItem *Lokomotywownia1;
        TMenuItem *N1;
        TMenuItem *Zapiszstangry1;
        TMenuItem *N4;
        TMenuItem *Zakocz1;
        TImageList *Tory;
        TMenuItem *OUstawienia;
        TMenuItem *ll1;
        TMediaPlayer *MPNowyPociag;
        TMediaPlayer *MPBlad;
        TMenuItem *MUwagi;
        TMenuItem *N5;
        TMenuItem *MWjazdWyjazd;
        TMenuItem *OUKolory;
        TMediaPlayer *MPMijanka;
        TMediaPlayer *MPOdjazd;
        TMediaPlayer *MPPktKarne;
        TMediaPlayer *MPOpoznienie;
        TMenuItem *OUDzwieki;
        void __fastcall MOProgramieClick(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall NowagraClick(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall PBStacjaMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MPrzyjazdyClick(TObject *Sender);
        void __fastcall PBPociagMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MOdjazdyClick(TObject *Sender);
        void __fastcall WczytajgreClick(TObject *Sender);
        void __fastcall ZapiszgreClick(TObject *Sender);
        void __fastcall Tematypomocy1Click(TObject *Sender);
        void __fastcall MZegarClick(TObject *Sender);
        void __fastcall MOpoznieniaClick(TObject *Sender);
        void __fastcall MPauzaClick(TObject *Sender);
        void __fastcall Lokomotywownia1Click(TObject *Sender);
        void __fastcall Zakocz1Click(TObject *Sender);
        void __fastcall Zapiszstangry1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall PBPrzyjazdyDblClick(TObject *Sender);
        void __fastcall PBOdjazdyDblClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PBPociagMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall PBStacjaMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall PBOdjazdyPaint(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall OUstawieniaClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall ll1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MUwagiClick(TObject *Sender);
        void __fastcall MWjazdWyjazdClick(TObject *Sender);
        void __fastcall OUKoloryClick(TObject *Sender);
        void __fastcall PBPrzyjazdyMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall PBOdjazdyMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall OUDzwiekiClick(TObject *Sender);
private:	// User declarations
        void __fastcall OnHint(TObject *Sender);

        bool CzyGra;  //czy zostala wczytana stacja i rozklad
        bool CzyZaznaczanie; //czy trwa zaznaczanie jakiejs trasu
        int Pociag;      //czy zostal zaznaczony pociag (lewa mysza)
                         //przechowuje wspolrzedne zaznaczonego pociagu
        bool Pauza;
        int Szerokosc;
        int Wysokosc;

        String Tytul; //tytul na belce glownego okna

        void __fastcall WyswietlZegar(TObject *Sender);
        void __fastcall RysujStacje(TObject *Sender);
        void __fastcall RysujPociag(TObject *Sender);
        void __fastcall WypiszRozklad(TObject *Sender);
        void __fastcall WczytajRysunki(void);
        void __fastcall DostosujWielkoscOkna(void);



        int Wagony[10][2];

#define ILOSC_TOROW 790
#define ILOSC_LITER 38

        bool Bocznica;
        bool Lokomot;
        bool PelneOkno; //czy dolne okno ma zajmowac cala szerokosc ekranu

        String StanGry;
        THintWindow *Dymek;
        Graphics::TBitmap* Tlo;

        TIniFile * PlikINI;
public:		// User declarations
        __fastcall TFGlowna(TComponent* Owner);
        void __fastcall ZaznaczanieTras(TMouseButton Button, int X, int Y,bool bocznica=false);
        void __fastcall Zmiana(void);
        void __fastcall WczytajTory(bool poczatek=true);
        void __fastcall WczytajDzwieki(void);

        Graphics::TBitmap* Numery[10];
        Graphics::TBitmap* Litery[ILOSC_LITER];
        tStacja Stacja;

        Graphics::TBitmap* Tabor[ILOSC_RYSUNKOW];
        bool PauzaZaznaczanie;
        bool PauzaPodglad;
        bool PauzaNieaktywne;
        bool Dzwieki;
        bool StalyRozmiar;
        bool NowyPociag;
        String NowyPociagPlik;
        bool Blad;
        String BladPlik;
        bool Mijanka;
        String MijankaPlik;
        bool Odjazd;
        String OdjazdPlik;
        bool PktKarne;
        String PktKarnePlik;
        bool Opoznienie;
        String OpoznieniePlik;
        TColor KolorSchemat;
        TColor KolorPrzyjazdy;
        TColor KolorOdjazdy;
        TColor KolorPodglad;
        bool KolorTlo; //czy ma byc bitmapa jako tlo
        int IloscWyswietlanychPociagow;
        String Sciezka; //sciezka do pliku z gra
};
//---------------------------------------------------------------------------
extern PACKAGE TFGlowna *FGlowna;
//---------------------------------------------------------------------------
#endif
