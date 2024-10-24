//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Opcje.h"
#include "FKolejarz.h"
//---------------------------------------------------------------------
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFOpcje *FOpcje;
//---------------------------------------------------------------------
__fastcall TFOpcje::TFOpcje(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TFOpcje::OKBtnClick(TObject *Sender)
{
  if(CzyZmiana)
  {
    CzyZmiana=false;
    if(CBCzasRzeczywisty->Checked)
      FGlowna->Timer->Interval=FGlowna->Stacja.Jednostka()*1000;
    else
      FGlowna->Timer->Interval=-(TBSzybkosc->Position)+5000;
  }
  if(Wyprzedzenie>=0)
  {
    FGlowna->Stacja.Wyprzedzenie(Wyprzedzenie);
    Wyprzedzenie=-1;
  }
  if(PlusMinus)
  {
    PlusMinus=false;
    FGlowna->Stacja.PlusMinus(0,0,E1->Text.ToInt());
    FGlowna->Stacja.PlusMinus(0,1,E6->Text.ToInt());
    FGlowna->Stacja.PlusMinus(1,0,E2->Text.ToInt());
    FGlowna->Stacja.PlusMinus(1,1,E7->Text.ToInt());
    FGlowna->Stacja.PlusMinus(2,0,E3->Text.ToInt());
    FGlowna->Stacja.PlusMinus(2,1,E8->Text.ToInt());
    FGlowna->Stacja.PlusMinus(3,0,E4->Text.ToInt());
    FGlowna->Stacja.PlusMinus(3,1,E9->Text.ToInt());
    FGlowna->Stacja.PlusMinus(4,0,E5->Text.ToInt());
    FGlowna->Stacja.PlusMinus(4,1,E10->Text.ToInt());
    FGlowna->Stacja.PlusMinus(5,0,E11->Text.ToInt());
    FGlowna->Stacja.PlusMinus(5,1,E12->Text.ToInt());
  }

  FGlowna->PauzaZaznaczanie=CBZaznaczanie->Checked;
  FGlowna->PauzaPodglad=CBPodglad->Checked;
  FGlowna->PauzaNieaktywne=CBNieaktywne->Checked;
  FGlowna->StalyRozmiar=CBRozmiar->Checked;
  if(RBCaly->Checked) FGlowna->IloscWyswietlanychPociagow=0;
  else
  {
    if(EPierwszych->Text.Length()==0) FGlowna->IloscWyswietlanychPociagow=0;
    else FGlowna->IloscWyswietlanychPociagow=EPierwszych->Text.ToInt();
  }
  if(FGlowna->KolorSchemat!=ESchemat->Color)
  {
    FGlowna->KolorSchemat=ESchemat->Color;
    FGlowna->WczytajTory(false);
  }
  FGlowna->KolorPrzyjazdy=EPrzyjazdy->Color;
  FGlowna->KolorOdjazdy=EOdjazdy->Color;
  FGlowna->KolorPodglad=EPodglad->Color;
  FGlowna->KolorTlo=CBTlo->Checked;
  FGlowna->Dzwieki=!CBDzwiek->Checked;
  FGlowna->NowyPociag=CBNowyPociag->Checked;
  FGlowna->NowyPociagPlik=LNowyPociag->Caption;
  FGlowna->Blad=CBBlad->Checked;
  FGlowna->BladPlik=LBlad->Caption;
  FGlowna->Mijanka=CBMijanka->Checked;
  FGlowna->MijankaPlik=LMijanka->Caption;
  FGlowna->Odjazd=CBOdjazd->Checked;
  FGlowna->OdjazdPlik=LOdjazd->Caption;
  FGlowna->PktKarne=CBPktKarne->Checked;
  FGlowna->PktKarnePlik=LPktKarne->Caption;
  FGlowna->Opoznienie=CBOpoznienie->Checked;
  FGlowna->OpoznieniePlik=LOpoznienie->Caption;
  MPDzwieki->Close();
  FGlowna->WczytajDzwieki();
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::EWyprzedzenieExit(TObject *Sender)
{
   if(EWyprzedzenie->Modified)
   {
     Wyprzedzenie=EWyprzedzenie->Text.ToInt();
   }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E1Exit(TObject *Sender)
{
  if(E1->Modified)
  {
    E1->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E2Exit(TObject *Sender)
{
  if(E2->Modified)
  {
    E2->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E3Exit(TObject *Sender)
{
  if(E3->Modified)
  {
    E3->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E4Exit(TObject *Sender)
{
  if(E4->Modified)
  {
    E4->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E5Exit(TObject *Sender)
{
  if(E5->Modified)
  {
    E5->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E6Exit(TObject *Sender)
{
  if(E6->Modified)
  {
    E6->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E7Exit(TObject *Sender)
{
  if(E7->Modified)
  {
    E7->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E8Exit(TObject *Sender)
{
  if(E8->Modified)
  {
    E8->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E9Change(TObject *Sender)
{
  if(E9->Modified)
  {
    E9->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E10Change(TObject *Sender)
{
  if(E10->Modified)
  {
    E10->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFOpcje::TBSzybkoscChange(TObject *Sender)
{
  CzyZmiana=true;        
}
//---------------------------------------------------------------------------


void __fastcall TFOpcje::CBCzasRzeczywistyClick(TObject *Sender)
{
  TBSzybkosc->Enabled=!CBCzasRzeczywisty->Checked;
  CzyZmiana=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E11Exit(TObject *Sender)
{
  if(E11->Modified)
  {
    E11->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::E12Exit(TObject *Sender)
{
  if(E12->Modified)
  {
    E12->Text.ToInt();
    PlusMinus=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::FormShow(TObject *Sender)
{
  CzyZmiana=false;
  Wyprzedzenie=-1;

  E1->Text=FGlowna->Stacja.PlusMinus(0,0);
  E6->Text=FGlowna->Stacja.PlusMinus(0,1);
  E2->Text=FGlowna->Stacja.PlusMinus(1,0);
  E7->Text=FGlowna->Stacja.PlusMinus(1,1);
  E3->Text=FGlowna->Stacja.PlusMinus(2,0);
  E8->Text=FGlowna->Stacja.PlusMinus(2,1);
  E4->Text=FGlowna->Stacja.PlusMinus(3,0);
  E9->Text=FGlowna->Stacja.PlusMinus(3,1);
  E5->Text=FGlowna->Stacja.PlusMinus(4,0);
  E10->Text=FGlowna->Stacja.PlusMinus(4,1);
  E11->Text=FGlowna->Stacja.PlusMinus(5,0);
  E12->Text=FGlowna->Stacja.PlusMinus(5,1);
  PlusMinus=false;

  CBZaznaczanie->Checked=FGlowna->PauzaZaznaczanie;
  CBPodglad->Checked=FGlowna->PauzaPodglad;
  CBNieaktywne->Checked=FGlowna->PauzaNieaktywne;
  if(FGlowna->PauzaZaznaczanie) CBPodglad->Enabled=false;
  else
  {
    CBPodglad->Enabled=true;
  }

  EWyprzedzenie->Text=FGlowna->Stacja.Wyprzedzenie();
  TBSzybkosc->Position=-(FGlowna->Timer->Interval)+5000;
  CBRozmiar->Checked=FGlowna->StalyRozmiar;
  if(!FGlowna->IloscWyswietlanychPociagow) RBCaly->Checked=true;
  else
  {
    RBNieCaly->Checked=true;
    EPierwszych->Text=FGlowna->IloscWyswietlanychPociagow;
  }
  ESchemat->Color=FGlowna->KolorSchemat;
  EPrzyjazdy->Color=FGlowna->KolorPrzyjazdy;
  EOdjazdy->Color=FGlowna->KolorOdjazdy;
  EPodglad->Color=FGlowna->KolorPodglad;
  CBTlo->Checked=FGlowna->KolorTlo;
  CBDzwiek->Checked=!FGlowna->Dzwieki;
  CBNowyPociag->Checked=FGlowna->NowyPociag;
  LNowyPociag->Caption=FGlowna->NowyPociagPlik;
  CBBlad->Checked=FGlowna->Blad;
  LBlad->Caption=FGlowna->BladPlik;
  CBMijanka->Checked=FGlowna->Mijanka;
  LMijanka->Caption=FGlowna->MijankaPlik;
  CBOdjazd->Checked=FGlowna->Odjazd;
  LOdjazd->Caption=FGlowna->OdjazdPlik;
  CBPktKarne->Checked=FGlowna->PktKarne;
  LPktKarne->Caption=FGlowna->PktKarnePlik;
  CBOpoznienie->Checked=FGlowna->Opoznienie;
  LOpoznienie->Caption=FGlowna->OpoznieniePlik;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBZaznaczanieClick(TObject *Sender)
{
  if(CBZaznaczanie->Checked)
  {
    CBPodglad->Enabled=false;
    FGlowna->PauzaPodglad=false;
    CBPodglad->Checked=false;
  }
  else
  {
    CBPodglad->Enabled=true;
  }
}
//---------------------------------------------------------------------------  
void __fastcall TFOpcje::BZmien1Click(TObject *Sender)
{
  CDKolory->Color=ESchemat->Color;
  if(CDKolory->Execute())
    ESchemat->Color=CDKolory->Color;

}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BZmien2Click(TObject *Sender)
{
  CDKolory->Color=EPrzyjazdy->Color;
  if(CDKolory->Execute())
    EPrzyjazdy->Color=CDKolory->Color;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BZmien3Click(TObject *Sender)
{
  CDKolory->Color=EOdjazdy->Color;
  if(CDKolory->Execute())
    EOdjazdy->Color=CDKolory->Color;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button4Click(TObject *Sender)
{
  CDKolory->Color=EPodglad->Color;
  if(CDKolory->Execute())
    EPodglad->Color=CDKolory->Color;
}
//---------------------------------------------------------------------------


void __fastcall TFOpcje::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_ESCAPE)
    Close();        
}
//---------------------------------------------------------------------------



void __fastcall TFOpcje::CBDzwiekClick(TObject *Sender)
{
  if(CBDzwiek->Checked)
    GBDzwieki->Visible=false;
  else
    GBDzwieki->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button1Click(TObject *Sender)
{
  if(OPDzwieki->Execute())
  {
    LNowyPociag->Caption=OPDzwieki->FileName;
  }
  CBNowyPociag->Checked=true;       
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BNowyPociagClick(TObject *Sender)
{
  FGlowna->MPNowyPociag->Close();
  MPDzwieki->Close();
  MPDzwieki->FileName=LNowyPociag->Caption;
  try
  {
    MPDzwieki->Open();
    MPDzwieki->Play();
  }
  catch(...)
  {
    Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego.","B³¹d odczytu",MB_OK);
    CBNowyPociag->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button2Click(TObject *Sender)
{
  if(OPDzwieki->Execute())
  {
    LMijanka->Caption=OPDzwieki->FileName;
  }
  CBMijanka->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button3Click(TObject *Sender)
{
  if(OPDzwieki->Execute())
  {
    LOpoznienie->Caption=OPDzwieki->FileName;
  }
  CBOpoznienie->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button5Click(TObject *Sender)
{
  if(OPDzwieki->Execute())
  {
    LOdjazd->Caption=OPDzwieki->FileName;
  }
  CBOdjazd->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button6Click(TObject *Sender)
{
  if(OPDzwieki->Execute())
  {
    LPktKarne->Caption=OPDzwieki->FileName;
  }
  CBPktKarne->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::Button7Click(TObject *Sender)
{
  if(OPDzwieki->Execute())
  {
    LBlad->Caption=OPDzwieki->FileName;
  }
  CBBlad->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BMijankaClick(TObject *Sender)
{
  FGlowna->MPMijanka->Close();
  MPDzwieki->Close();
  MPDzwieki->FileName=LMijanka->Caption;
  try
  {
    MPDzwieki->Open();
    MPDzwieki->Play();
  }
  catch(...)
  {
    Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego.","B³¹d odczytu",MB_OK);
    CBMijanka->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BOpoznienieClick(TObject *Sender)
{
  FGlowna->MPOpoznienie->Close();
  MPDzwieki->Close();
  MPDzwieki->FileName=LOpoznienie->Caption;
  try
  {
    MPDzwieki->Open();
    MPDzwieki->Play();
  }
  catch(...)
  {
    Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego.","B³¹d odczytu",MB_OK);
    CBOpoznienie->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BOdjazdClick(TObject *Sender)
{
  FGlowna->MPOdjazd->Close();
  MPDzwieki->Close();
  MPDzwieki->FileName=LOdjazd->Caption;
  try
  {
    MPDzwieki->Open();
    MPDzwieki->Play();
  }
  catch(...)
  {
    Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego.","B³¹d odczytu",MB_OK);
    CBOdjazd->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BPktKarneClick(TObject *Sender)
{
  FGlowna->MPPktKarne->Close();
  MPDzwieki->Close();
  MPDzwieki->FileName=LPktKarne->Caption;
  try
  {
    MPDzwieki->Open();
    MPDzwieki->Play();
  }
  catch(...)
  {
    Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego.","B³¹d odczytu",MB_OK);
    CBPktKarne->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::BBladClick(TObject *Sender)
{
  FGlowna->MPBlad->Close();
  MPDzwieki->Close();
  MPDzwieki->FileName=LBlad->Caption;
  try
  {
    MPDzwieki->Open();
    MPDzwieki->Play();
  }
  catch(...)
  {
    Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego.","B³¹d odczytu",MB_OK);
    CBBlad->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CancelBtnClick(TObject *Sender)
{
  MPDzwieki->Close();
  FGlowna->WczytajDzwieki();
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBNowyPociagClick(TObject *Sender)
{
  if(CBNowyPociag->Checked==false) return;
  if((LNowyPociag->Caption == LBlad->Caption && CBBlad->Checked) ||
     (LNowyPociag->Caption == LMijanka->Caption && CBMijanka->Checked) ||
     (LNowyPociag->Caption == LOdjazd->Caption && CBOdjazd->Checked) ||
     (LNowyPociag->Caption == LPktKarne->Caption && CBPktKarne->Checked) ||
     (LNowyPociag->Caption == LOpoznienie->Caption && CBOpoznienie->Checked))
  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
    CBNowyPociag->Checked=false;
  }
/*  if(( == LNowyPociag->Caption && CBNowyPociag->Checked) ||
     ( == LBlad->Caption && CBBlad->Checked) ||
     ( == LMijanka->Caption && CBMijanka->Checked) ||
     ( == LOdjazd->Caption && CBOdjazd->Checked) ||
     ( == LPktKarne->Caption && CBPktKarne->Checked) ||
     ( == LOpoznienie->Caption && CBOpoznienie->Checked))
  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBMijankaClick(TObject *Sender)
{
  if(CBMijanka->Checked==false) return;
  if((LMijanka->Caption == LNowyPociag->Caption && CBNowyPociag->Checked) ||
     (LMijanka->Caption == LBlad->Caption && CBBlad->Checked) ||
     (LMijanka->Caption == LOdjazd->Caption && CBOdjazd->Checked) ||
     (LMijanka->Caption == LPktKarne->Caption && CBPktKarne->Checked) ||
     (LMijanka->Caption == LOpoznienie->Caption && CBOpoznienie->Checked))
  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
    CBMijanka->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBOpoznienieClick(TObject *Sender)
{
  if(CBOpoznienie->Checked==false) return;
  if((LOpoznienie->Caption == LNowyPociag->Caption && CBNowyPociag->Checked) ||
     (LOpoznienie->Caption == LBlad->Caption && CBBlad->Checked) ||
     (LOpoznienie->Caption == LMijanka->Caption && CBMijanka->Checked) ||
     (LOpoznienie->Caption == LOdjazd->Caption && CBOdjazd->Checked) ||
     (LOpoznienie->Caption == LPktKarne->Caption && CBPktKarne->Checked))

  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
    CBOpoznienie->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBOdjazdClick(TObject *Sender)
{
  if(CBOdjazd->Checked==false) return;
  if((LOdjazd->Caption == LNowyPociag->Caption && CBNowyPociag->Checked) ||
     (LOdjazd->Caption == LBlad->Caption && CBBlad->Checked) ||
     (LOdjazd->Caption == LMijanka->Caption && CBMijanka->Checked) ||
     (LOdjazd->Caption == LPktKarne->Caption && CBPktKarne->Checked) ||
     (LOdjazd->Caption == LOpoznienie->Caption && CBOpoznienie->Checked))
  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
    CBOdjazd->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBPktKarneClick(TObject *Sender)
{
  if(CBPktKarne->Checked==false) return;
  if((LPktKarne->Caption == LNowyPociag->Caption && CBNowyPociag->Checked) ||
     (LPktKarne->Caption == LBlad->Caption && CBBlad->Checked) ||
     (LPktKarne->Caption == LMijanka->Caption && CBMijanka->Checked) ||
     (LPktKarne->Caption == LOdjazd->Caption && CBOdjazd->Checked) ||
     (LPktKarne->Caption == LOpoznienie->Caption && CBOpoznienie->Checked))
  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
    CBPktKarne->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::CBBladClick(TObject *Sender)
{
  if(CBBlad->Checked==false) return;
  if((LBlad->Caption == LNowyPociag->Caption && CBNowyPociag->Checked) ||
     (LBlad->Caption == LMijanka->Caption && CBMijanka->Checked) ||
     (LBlad->Caption == LOdjazd->Caption && CBOdjazd->Checked) ||
     (LBlad->Caption == LPktKarne->Caption && CBPktKarne->Checked) ||
     (LBlad->Caption == LOpoznienie->Caption && CBOpoznienie->Checked))
  {
    Application->MessageBox("Plik dŸwiêkowy jest ju¿ wykorzystywany w innym zdarzeniu.","B³¹d przypisania pliku",MB_OK);
    CBBlad->Checked=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpcje::TSDzwiekiShow(TObject *Sender)
{
  FGlowna->MPNowyPociag->Close();
  FGlowna->MPMijanka->Close();
  FGlowna->MPOpoznienie->Close();
  FGlowna->MPOdjazd->Close();
  FGlowna->MPPktKarne->Close();
  FGlowna->MPBlad->Close();
}
//---------------------------------------------------------------------------

