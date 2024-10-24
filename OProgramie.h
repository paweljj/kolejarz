//----------------------------------------------------------------------------
#ifndef OProgramieH
#define OProgramieH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TFOProgramie : public TForm
{
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
	TButton *OKButton;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TBevel *Bevel1;
        TLabel *Label9;
        TLabel *Label10;
        TBevel *Bevel2;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        void __fastcall Label12Click(TObject *Sender);
        void __fastcall Label6Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:
public:
	virtual __fastcall TFOProgramie(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TFOProgramie *FOProgramie;
//----------------------------------------------------------------------------
#endif    
