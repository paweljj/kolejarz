//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OLokom.h"
#include "FKolejarz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFLokomot *FLokomot;
//---------------------------------------------------------------------------
__fastcall TFLokomot::TFLokomot(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFLokomot::PBLokiPaint(TObject *Sender)
{
  Rysuj();
}
//---------------------------------------------------------------------------
void __fastcall TFLokomot::Rysuj(void)
{
  tRaport* raport=FGlowna->Stacja.DajRaport();
  int ilosc_typow=0;
  int rodzaj;
  if(raport->dl>0)
  {
    rodzaj=raport->pola[0].obiekt->Rodzaj();
    ilosc_typow++;
  }
  for(int i=0;i<raport->dl;i++)
  {
    if(rodzaj!=raport->pola[i].obiekt->Rodzaj())
    {
      rodzaj=raport->pola[i].obiekt->Rodzaj();
      ilosc_typow++;
    }
  }
  if(ilosc_typow>0)
  {
    if(ilosc_typow<=12)
    {
      FLokomot->Height=(ilosc_typow+1)*40+FLokomot->Panel1->Height+5;
      FLokomot->Width=250;
    }
    else
    {
      ilosc_typow=ilosc_typow/2+ilosc_typow%2;
      FLokomot->Height=(ilosc_typow+1)*40+FLokomot->Panel1->Height+5;
      FLokomot->Width=500;
    }
  }
  BZamknij->Left=Panel1->Width/2-BZamknij->Width/2;
  Graphics::TBitmap* rysunek=new Graphics::TBitmap();
  rysunek->Width=PBLoki->Width;
  rysunek->Height=PBLoki->Height;
  int dobrych=0;
  int zepsutych=0;
  int zamowionych=0;
  int i;
  if(raport->dl>0)
  {
    rodzaj=raport->pola[0].obiekt->Rodzaj();
    String nazwa=FGlowna->Stacja.Nazwa(rodzaj,-1);
    for(i=0;raport->pola[i].obiekt->Rodzaj()==rodzaj;i++)
    {
      if(raport->pola[i].stan==ZAMOWIONA || raport->pola[i].stan==GOTOWA)
        zamowionych++;
      else if(raport->pola[i].obiekt->Sprawnosc())
      {
        dobrych++;
        Rodzaje[0][0][dobrych]=raport->pola[i].obiekt->Numer();
      }
      else
        zepsutych++;
      if(i==raport->dl-1)
      {
        i++;
        Rodzaje[0][0][dobrych+1]=-1;
        break;
      }
      Rodzaje[0][0][dobrych+1]=-1;
    }
    Rodzaje[0][0][0]=rodzaj;
    rysunek->Canvas->Font->Color=clBlack;
    rysunek->Canvas->Draw(0,0,FGlowna->Tabor[rodzaj]);
    rysunek->Canvas->TextOutA(110,20,nazwa);
    rysunek->Canvas->TextOutA(150,20,dobrych);
    rysunek->Canvas->Font->Color=clRed;
    rysunek->Canvas->TextOutA(180,20,zepsutych);
    rysunek->Canvas->Font->Color=clBlue;
    rysunek->Canvas->TextOutA(210,20,zamowionych);
  }
  int lok=40;
  int lok2=0;
  int j=2;
  for(;i<raport->dl;)
  {
    if(rodzaj!=raport->pola[i].obiekt->Rodzaj())
    {
      rodzaj=raport->pola[i].obiekt->Rodzaj();
      String nazwa=FGlowna->Stacja.Nazwa(rodzaj,-1);
      dobrych=zepsutych=zamowionych=0;
      for(;raport->pola[i].obiekt->Rodzaj()==rodzaj;i++)
      {
        if(raport->pola[i].stan==ZAMOWIONA || raport->pola[i].stan==GOTOWA)
          zamowionych++;
        else if(raport->pola[i].obiekt->Sprawnosc())
        {
          dobrych++;
          if(j>ilosc_typow)
          {
            Rodzaje[lok2/40][1][dobrych]=raport->pola[i].obiekt->Numer();
          }
          else
          {
            Rodzaje[lok/40][0][dobrych]=raport->pola[i].obiekt->Numer();
          }
        }
        else
          zepsutych++;
        if(j>ilosc_typow)
          Rodzaje[lok2/40][1][dobrych+1]=-1;
        else
          Rodzaje[lok/40][0][dobrych+1]=-1;
        if(i==raport->dl-1)
        {
          i++;
          break;
        }
      }
      if(j>ilosc_typow)
      {
        rysunek->Canvas->Font->Color=clBlack;
        rysunek->Canvas->Draw(250,lok2,FGlowna->Tabor[rodzaj]);
        rysunek->Canvas->TextOutA(360,lok2+20,nazwa);
        rysunek->Canvas->TextOutA(400,lok2+20,dobrych);
        rysunek->Canvas->Font->Color=clRed;
        rysunek->Canvas->TextOutA(430,lok2+20,zepsutych);
        rysunek->Canvas->Font->Color=clBlue;
        rysunek->Canvas->TextOutA(460,lok2+20,zamowionych);
        Rodzaje[lok2/40][1][0]=rodzaj;
        lok2+=40;
      }
      else
      {
        rysunek->Canvas->Font->Color=clBlack;
        rysunek->Canvas->Draw(0,lok,FGlowna->Tabor[rodzaj]);
        rysunek->Canvas->TextOutA(110,lok+20,nazwa);
        rysunek->Canvas->TextOutA(150,lok+20,dobrych);
        rysunek->Canvas->Font->Color=clRed;
        rysunek->Canvas->TextOutA(180,lok+20,zepsutych);
        rysunek->Canvas->Font->Color=clBlue;
        rysunek->Canvas->TextOutA(210,lok+20,zamowionych);
        Rodzaje[lok/40][0][0]=rodzaj;
        lok+=40;
        j++;
      }
    }
  }
  PBLoki->Canvas->Draw(0,0,rysunek);
  delete rysunek;
}
//---------------------------------------------------------------------------

void __fastcall TFLokomot::PBLokiMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(!(X>=0 && X<110) && !(X>250 && X<360))
  {
    LBSzopy->Visible=false;
    return;
  }
  int y=X/250;
  int x=Y/40;
  LBSzopy->Clear();
  for(int i=1;;i++)
  {
    if(Rodzaje[x][y][i]==-1)
      break;
    char *s=FGlowna->Stacja.Szopa(Rodzaje[x][y][i]);
    LBSzopy->Items->Add(s);
    delete [] s;
  }
  XX=x;
  YY=y;
  LBSzopy->Left=y*250;
  LBSzopy->Top=x*40;
  if(LBSzopy->Items->Count)
  {
    if(!FGlowna->Stacja.Przejscia())
      FGlowna->Stacja.Zamow(Rodzaje[XX][YY][0],Rodzaje[XX][YY][1]);
    else
      LBSzopy->Visible=true;
    Rysuj();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFLokomot::LBSzopyClick(TObject *Sender)
{
  FGlowna->Stacja.Zamow(Rodzaje[XX][YY][0],Rodzaje[XX][YY][LBSzopy->ItemIndex+1]);
  LBSzopy->Visible=false;
  Rysuj();
  BZamknij->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFLokomot::FormClose(TObject *Sender, TCloseAction &Action)
{
  LBSzopy->Visible=false;        
}
//---------------------------------------------------------------------------

void __fastcall TFLokomot::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_ESCAPE)
    Close();        
}
//---------------------------------------------------------------------------

