//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WjazdWyjazd.h"
#include "FKolejarz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFWjazdWyjazd *FWjazdWyjazd;
//---------------------------------------------------------------------------
__fastcall TFWjazdWyjazd::TFWjazdWyjazd(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFWjazdWyjazd::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_SPACE || Key==VK_ESCAPE)
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFWjazdWyjazd::FormPaint(TObject *Sender)
{
  int ilosc=FGlowna->Stacja.WjazdWyjazd();
  Graphics::TBitmap * bitmap= new Graphics::TBitmap();
  bitmap->Height=(ilosc+1)*20;
  bitmap->Width=200;
  FWjazdWyjazd->Height=bitmap->Height+30;
  bitmap->Canvas->Font->Size=10;
  bitmap->Canvas->TextOutA(55,0,"Wyp.");
  bitmap->Canvas->TextOutA(95,0,"Odstep");
  bitmap->Canvas->TextOutA(150,0,"Mijanka");
  for(int i=1;i<=ilosc;i++)
  {
    long g=FGlowna->Stacja.WjazdWyjazd(i);
    int rodzaj=g%10;g/=10;
    int numer=g%10;g/=10;
    int wyp=g%10;g/=10;
    int odstep=g;
    if(rodzaj==WJAZD)
      FGlowna->Tory->Draw(bitmap->Canvas,10,i*20,402,true);
    else if(rodzaj==WYJAZD)
      FGlowna->Tory->Draw(bitmap->Canvas,10,i*20,412,true);
    else
      FGlowna->Tory->Draw(bitmap->Canvas,10,i*20,422,true);
    bitmap->Canvas->Draw(30,i*20,FGlowna->Numery[numer]);
    if(wyp)
      bitmap->Canvas->TextOutA(65,i*20,wyp);
    if(rodzaj==WJAZD_WYJAZD)
    {
      bitmap->Canvas->TextOutA(110,i*20,odstep/100);
      bitmap->Canvas->TextOutA(165,i*20,odstep%100);
    }
    else
      bitmap->Canvas->TextOutA(110,i*20,odstep);
  }
  FWjazdWyjazd->Canvas->Draw(0,0,bitmap);
  delete bitmap;
  }
//---------------------------------------------------------------------------
