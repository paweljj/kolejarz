//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OMijanka.h"
#include "FKolejarz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFMijanka *FMijanka;
//---------------------------------------------------------------------------
__fastcall TFMijanka::TFMijanka(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFMijanka::BZezwalamClick(TObject *Sender)
{
  Czekaj=0;        
}
//---------------------------------------------------------------------------

void __fastcall TFMijanka::BCzekajClick(TObject *Sender)
{
  Czekaj=ECzekaj->Text.ToInt();        
}
//---------------------------------------------------------------------------

void __fastcall TFMijanka::FormPaint(TObject *Sender)
{
  int punkt=FGlowna->Stacja.NrPunktu(Wspolrzedne);
  int ilosc=FGlowna->Stacja.Mijanka(punkt);
  Graphics::TBitmap * bitmap= new Graphics::TBitmap();
  bitmap->Canvas->Font->Size=12;

  bitmap->Width=600;
  bitmap->Height=200;
  for(int i=0;i<ilosc;i++)
  {
    int r=FGlowna->Stacja.Mijanka(punkt,i+1);
    bitmap->Canvas->Font->Style=TFontStyles()<<fsBold;
    bitmap->Canvas->TextOutA(0,i*20,String(i+1)+". ");
    bitmap->Canvas->Font->Style=TFontStyles();
    if(r>-1)
    {
      if(FGlowna->Stacja.Mijanka(punkt,ROZMIAR_MIJANKI)==WYJEZDZA)
      {
        PTytul->Caption="Odcinek wyjazdowy od wyjazdu nr: "+String(Numer);
        char* napis=FGlowna->Stacja.Godzina(r,NIEOKRESLONA,ODJAZD);
        bitmap->Canvas->TextOutA(20,i*20,napis);
        delete[] napis;
        napis=FGlowna->Stacja.Numer(r,NIEOKRESLONA,ODJAZD);
        bitmap->Canvas->TextOutA(120,i*20,napis);
      }
      else
      {
        PTytul->Caption="Odcinek dojazdowy do wjazdu nr: "+String(Numer);
        char* napis=FGlowna->Stacja.Godzina(r,NIEOKRESLONA,PRZYJAZD);
        bitmap->Canvas->TextOutA(20,i*20,napis);
        delete[] napis;
        napis=FGlowna->Stacja.Rodzaj(r,NIEOKRESLONA);
        bitmap->Canvas->TextOutA(70,i*20,napis);
        napis=FGlowna->Stacja.Numer(r,NIEOKRESLONA,PRZYJAZD);
        bitmap->Canvas->TextOutA(120,i*20,napis);
        if(FGlowna->Stacja.TypPociagu(r,NIEOKRESLONA)!=POWROT_LOKA)
        {
          napis=FGlowna->Stacja.Skad(r,NIEOKRESLONA);
          bitmap->Canvas->TextOutA(190,i*20,napis);
          delete[] napis;
          napis=FGlowna->Stacja.Dokad(r,NIEOKRESLONA);
          bitmap->Canvas->TextOutA(360,i*20,napis);
          delete[] napis;
        }
        napis=FGlowna->Stacja.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD);
        bitmap->Canvas->TextOutA(520,i*20,napis);
        delete[] napis;
      }
    }
    else
    {
      PTytul->Caption="Wjazd/wyjazd nr: "+String(Numer);
    }
  }
  if(!ilosc)
    PTytul->Caption="Wjazd/wyjazd nr: "+String(Numer);
  PBMijanka->Canvas->Draw(0,0,bitmap);
  delete bitmap;
}
//---------------------------------------------------------------------------


