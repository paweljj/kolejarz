//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OProgramie.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TFOProgramie *FOProgramie;
//--------------------------------------------------------------------- 
__fastcall TFOProgramie::TFOProgramie(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------


void __fastcall TFOProgramie::Label12Click(TObject *Sender)
{
  ShellExecute(Handle,"open","http://www.kolejarz.prv.pl","","",SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFOProgramie::Label6Click(TObject *Sender)
{
  ShellExecute(Handle,"open","mailto:pawelj@hot.pl?subject=[Kolejarz 1.77]","","",SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFOProgramie::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_ESCAPE)
    Close();        
}
//---------------------------------------------------------------------------

