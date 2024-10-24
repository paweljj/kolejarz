//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OBocznica.h"
#include "FKolejarz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFBocznica *FBocznica;
//---------------------------------------------------------------------------
__fastcall TFBocznica::TFBocznica(TComponent* Owner)
        : TForm(Owner)
{
  CzyZaznaczanie=Wyjscie=false;
  Dymek = new THintWindow(this);
}
//---------------------------------------------------------------------------
void __fastcall TFBocznica::Parametry(int poz,int pocz, int kon, int w)
{
  pozycja=poz;
  poczatek=pocz;
  koniec=kon;
  wsp=w;
}
//---------------------------------------------------------------------------
void __fastcall TFBocznica::PBBocznicaPaint(TObject *Sender)
{
  RysujBocznice();
}
//---------------------------------------------------------------------------
void __fastcall TFBocznica::RysujBocznice(void)
{
  int ilosc=koniec-poczatek+1;
  FBocznica->Height=(ilosc+1)*WYSOKOSC+FBocznica->Panel1->Height-10;
  Graphics::TBitmap* rysunek=new Graphics::TBitmap();
  rysunek->Width=PBBocznica->Width;
  rysunek->Height=PBBocznica->Height;
  for(int x=0;x<20;x++)
    for(int y=0;y<DLUGOSC_POSTOJOWYCH;y++)
      Wagony[x][y]=-1;

  for(int poz=0;poz<koniec-poczatek+1;poz++)
  {
    if(FGlowna->Stacja.CzyRuch(poz+poczatek,0))
      Semafor[poz]=GORA;
    else
      Semafor[poz]=DOL;
    Graphics::TBitmap* bitmap=new Graphics::TBitmap();
    if(Semafor[poz]==DOL)
      bitmap->LoadFromResourceName((int)HInstance,"SEMAFOR_DOL");
    else
      bitmap->LoadFromResourceName((int)HInstance,"SEMAFOR_GORA");
    rysunek->Canvas->Draw(0,poz*WYSOKOSC+12,bitmap);
    delete bitmap;
    int y=30;
    for(int i=0;i<DLUGOSC_POSTOJOWYCH;i++)
    {
      int nr=poz+poczatek;//pozycja;
      int nazwa=FGlowna->Stacja.NazwaNr(poz+poczatek,i);
      if(nazwa<=0 ) break;
      rysunek->Canvas->Draw(y,poz*WYSOKOSC,FGlowna->Tabor[nazwa]);
      Wagony[2*poz][i]=y;
      Wagony[2*poz+1][i]=y+FGlowna->Tabor[nazwa]->Width;
      //informacje pod rysunkiem
      if(!FGlowna->Stacja.Sprawnosc(nr,i))
        rysunek->Canvas->Font->Color=clRed;
      else
        rysunek->Canvas->Font->Color=clBlack;
      if(FGlowna->Stacja.CzyRuch(nr,i))
        rysunek->Canvas->Font->Style=TFontStyles()<<fsItalic;
      else if(FGlowna->Stacja.Czas(nr,i))
        rysunek->Canvas->Font->Style=TFontStyles()<<fsBold;
      else
        rysunek->Canvas->Font->Style=TFontStyles();
      if(FGlowna->Stacja.RodzajSkladu(nr,i)>=3)
      {//lokomotywa
        String s=FGlowna->Stacja.Nazwa(nr,i);
//        s+="-";
//        s+=FGlowna->Stacja.NumerLoka(nr,i);
        rysunek->Canvas->TextOutA(y,poz*WYSOKOSC+40,s);
      }
      else if(FGlowna->Stacja.RodzajSkladu(nr,i)>=1)
      {//jednostka nierozlaczalna
        char* napis=0;
        int p=FGlowna->Stacja.NrRozklad(nr,i);
        rysunek->Canvas->TextOutA(y,poz*WYSOKOSC+40,FGlowna->Stacja.Peron(FGlowna->Stacja.Peron(p,NIEOKRESLONA,ODJAZD)));
        napis=FGlowna->Stacja.Numer(p,NIEOKRESLONA,ODJAZD);
        rysunek->Canvas->TextOutA(y+19,poz*WYSOKOSC+40,napis);
        delete[] napis;
        rysunek->Canvas->TextOutA(y+62,poz*WYSOKOSC+40,FGlowna->Stacja.Wyjazd(p,NIEOKRESLONA));
        napis=FGlowna->Stacja.Godzina(p,NIEOKRESLONA,ODJAZD);
        rysunek->Canvas->TextOutA(y+74,poz*WYSOKOSC+40,napis);
        delete[] napis;
        int a=FGlowna->Stacja.Opoznienie(p,NIEOKRESLONA);
        String s;
        if(a>0)
        {
          s="+";
          s+=a;
        }
        else if(a==0)
          s="";
        else
          s=a;
        rysunek->Canvas->TextOutA(y+104,poz*WYSOKOSC+40,s);
        String ss=FGlowna->Stacja.Nazwa(nr,i);
        rysunek->Canvas->TextOutA(y+134,poz*WYSOKOSC+40,ss);
      }
      else
      {//sklad
        char* napis=0;
        int p=FGlowna->Stacja.NrRozklad(nr,i);
        rysunek->Canvas->TextOutA(y,poz*WYSOKOSC+40,FGlowna->Stacja.Peron(FGlowna->Stacja.Peron(p,NIEOKRESLONA,ODJAZD)));
        napis=FGlowna->Stacja.Numer(p,NIEOKRESLONA,ODJAZD);
        rysunek->Canvas->TextOutA(y+19,poz*WYSOKOSC+40,napis);
        delete[] napis;
        rysunek->Canvas->TextOutA(y+62,poz*WYSOKOSC+40,FGlowna->Stacja.Wyjazd(p,NIEOKRESLONA));
        napis=FGlowna->Stacja.Godzina(p,NIEOKRESLONA,ODJAZD);
        rysunek->Canvas->TextOutA(y+74,poz*WYSOKOSC+40,napis);
        delete[] napis;
        int a=FGlowna->Stacja.Opoznienie(p,NIEOKRESLONA);
        String s;
        if(a>0)
        {
          s="+";
          s+=a;
        }
        else if(a==0)
          s="";
        else
          s=a;
        rysunek->Canvas->TextOutA(y+104,poz*WYSOKOSC+40,s);
      }
      y+=FGlowna->Tabor[nazwa]->Width;
      if(!FGlowna->Stacja.CzyPolaczony(nr,i))
      y+=10;
    }
  }
  PBBocznica->Canvas->Draw(0,0,rysunek);
  delete rysunek;
}
//------------------------------------------------------------------------------
void __fastcall TFBocznica::PBBocznicaMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

  FGlowna->StatusBar->Panels->Items[1]->Text="";
  int y=(Y-5)/WYSOKOSC;
  if(X>0 && X<28 && FGlowna->Stacja.RodzajSkladu2(poczatek+y,0)!=PUSTY && !CzyZaznaczanie)
  {
    FGlowna->Stacja.Bocznica(pozycja,0,poczatek+y);
    int xx=wsp/100*14;
    int yy=wsp%100*14;
    Close();
    FGlowna->ZaznaczanieTras(mbRight,yy,xx,true);
  }
  if(CzyZaznaczanie)
  {
    Numer=y+poczatek;
    ModalResult=mrIgnore;
    CloseQuery();
    return;
  }
  int i;
  for(i=0;i<10;i++)
  {
    if(Wagony[2*y+1][i]>X && Wagony[2*y][i]<X) break;
  }
  if(i==10)
  { //wyjscie przy zaznaczaniu wyjazdu
    return;
  }
  String s;
  char* napis=0;
  if(Button==mbRight)
  {
    napis=FGlowna->Stacja.Laczenie(wsp,i,y+poczatek);
    s=napis;
    RysujBocznice();
  }
  else if(Button==mbLeft)
  {
    if(i>0)
    {
      napis=FGlowna->Stacja.Laczenie(wsp,i-1,y+poczatek);
      s=napis;
      RysujBocznice();
    }
    else
      s="Po lewej stronie nic nie stoi";
  }
  FGlowna->StatusBar->Panels->Items[1]->Text=s;
}
//---------------------------------------------------------------------------


void __fastcall TFBocznica::PBBocznicaMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  //Wyswietlanie odpowiedniego dymka
  if(Y>PBBocznica->Height || X>PBBocznica->Width)
  {
    Dymek->ReleaseHandle();
    return;
  }
  int y=(Y-5)/WYSOKOSC;
  int i;
  for(i=0;i<10;i++)
  {
    if(Wagony[2*y+1][i]>X && Wagony[2*y][i]<X) break;
  }
  if(i==10)
  { //wyjscie przy zaznaczaniu wyjazdu
    Dymek->ReleaseHandle();
    return;
  }
  POINT Punkt;
  String tekst1,tekst2;
  ::GetCursorPos(&Punkt);

  int nr=y+poczatek;
  if(nr==-1) return;
  int p=FGlowna->Stacja.NrRozklad(nr,i);
  char* napis;
  if(FGlowna->Stacja.RodzajSkladu(nr,i)>=3)
  {//lokomotywa
    napis=FGlowna->Stacja.NumerLoka(nr,i);
    tekst1=String(FGlowna->Stacja.Nazwa(nr,i));
    tekst2=String(napis);
    delete [] napis;
  }
  else
  {//jednostka nierozlaczalna i sklad
    int czesc;
    if(FGlowna->Stacja.CzyZjechac(nr,i))
    {
      tekst1=String("P: ")+FGlowna->Stacja.Peron(FGlowna->Stacja.Peron(p,NIEOKRESLONA,ODJAZD));
      czesc=FGlowna->Stacja.NumerCzesci(p,ODJAZD);
    }
    else
    {
      tekst1=String("P: ")+FGlowna->Stacja.Peron(FGlowna->Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD));
      czesc=FGlowna->Stacja.NumerCzesci(p,PRZYJAZD);
    }
    napis=FGlowna->Stacja.Numer(p,NIEOKRESLONA,ODJAZD);
    tekst1=tekst1+"  Nr: "+napis;
    delete[] napis;
    tekst1=tekst1+"  W: "+FGlowna->Stacja.Wyjazd(p,NIEOKRESLONA);
    napis=FGlowna->Stacja.GodzinaRzeczywista(p,NIEOKRESLONA,ODJAZD);
    tekst1=tekst1+"  Godz: "+napis;
    delete[] napis;
    napis=FGlowna->Stacja.Skad(p,NIEOKRESLONA);
    tekst2=napis+String(" - ");
    delete[] napis;
    napis=FGlowna->Stacja.Dokad(p,NIEOKRESLONA);
    tekst2=tekst2+napis;
    delete[] napis;
    if(czesc)
      tekst1=tekst1+" ("+String(czesc)+")";
  }

  int d=(Dymek->CalcHintRect(1000,tekst1,0).Right<Dymek->CalcHintRect(1000,tekst2,0).Right)?Dymek->CalcHintRect(1000,tekst2,0).Right:Dymek->CalcHintRect(1000,tekst1,0).Right;
  TRect Obszar=Rect(Punkt.x+10,Punkt.y+20,Punkt.x+d+10,Punkt.y+50);
  if(Wyjscie)
    Dymek->ReleaseHandle();
  else
    Dymek->ActivateHint(Obszar,tekst1+'\n'+tekst2);

}
//---------------------------------------------------------------------------


void __fastcall TFBocznica::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  Dymek->ReleaseHandle();
  Wyjscie=true;
}
//---------------------------------------------------------------------------


void __fastcall TFBocznica::FormActivate(TObject *Sender)
{
  Wyjscie=false;        
}
//---------------------------------------------------------------------------

void __fastcall TFBocznica::Panel1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  Dymek->ReleaseHandle();        
}
//---------------------------------------------------------------------------

void __fastcall TFBocznica::BOKMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  Dymek->ReleaseHandle();        
}
//---------------------------------------------------------------------------








void __fastcall TFBocznica::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_ESCAPE)
    Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFBocznica::FormDestroy(TObject *Sender)
{
  delete Dymek;
}
//---------------------------------------------------------------------------

