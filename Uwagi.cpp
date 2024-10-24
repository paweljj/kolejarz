//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Uwagi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFUwagi *FUwagi;
//---------------------------------------------------------------------------
__fastcall TFUwagi::TFUwagi(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFUwagi::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_ESCAPE)
    Close();        
}
//---------------------------------------------------------------------------

