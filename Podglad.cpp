//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Podglad.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPodgladSkladu *FPodgladSkladu;
//---------------------------------------------------------------------------
__fastcall TFPodgladSkladu::TFPodgladSkladu(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFPodgladSkladu::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_SPACE || Key==VK_ESCAPE)
    Close();
  else if(Key==VK_LEFT)
    SBTlo->HorzScrollBar->Position-=10;
  else if(Key==VK_RIGHT)
    SBTlo->HorzScrollBar->Position+=10;
}
//---------------------------------------------------------------------------


