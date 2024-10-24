//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Poczatek.h"
#include "FKolejarz.h"
#include "Uwagi.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TFPoczatek *FPoczatek;
//--------------------------------------------------------------------- 
__fastcall TFPoczatek::TFPoczatek(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TFPoczatek::FormShow(TObject *Sender)
{
  char *s=FGlowna->Stacja.Skad(NIEOKRESLONA,NIEOKRESLONA);
  AnsiString ss="Stacja: ";
  ss+=s;
  LNazwa->Caption=ss;
  delete [] s;

  CBPodglad->Checked=FGlowna->Stacja.CzyPodglad();
}
//---------------------------------------------------------------------------

void __fastcall TFPoczatek::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  FGlowna->Stacja.Przejscia(CBSzopa->Checked);
  FGlowna->Stacja.GraTestowa(CBGraTestowa->Checked);
  if(CBGraTestowa->Checked)
    FGlowna->StatusBar->Panels->Items[0]->Text="Gra testowa";
  else
    FGlowna->StatusBar->Panels->Items[0]->Text="Punkty karne";
}
//---------------------------------------------------------------------------


void __fastcall TFPoczatek::BUwagiClick(TObject *Sender)
{ 
  FUwagi->ShowModal();        
}
//---------------------------------------------------------------------------

