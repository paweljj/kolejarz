//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FKolejarz.h"
#include "OProgramie.h"
#include "Opcje.h"
#include "ORozklad.h"
#include "OBocznica.h"
#include "OLokom.h"
#include "Podglad.h"
#include "Poczatek.h"
#include "Uwagi.h"
#include "OMijanka.h"
#include "WjazdWyjazd.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFGlowna *FGlowna;
//---------------------------------------------------------------------------
__fastcall TFGlowna::TFGlowna(TComponent* Owner)
        : TForm(Owner)                                      
{
  KolorTlo=PelneOkno=Pauza=PauzaZaznaczanie=PauzaPodglad=CzyGra=Bocznica=Lokomot=StalyRozmiar=false;
  KolorSchemat=KolorPrzyjazdy=KolorOdjazdy=KolorPodglad=clWhite;
  PauzaNieaktywne=true;
  CzyZaznaczanie=false;
  Dzwieki=true;
  NowyPociag=Blad=Mijanka=Odjazd=PktKarne=Opoznienie=false;
  NowyPociagPlik=BladPlik=MijankaPlik=OdjazdPlik=PktKarnePlik=OpoznieniePlik="";
  Pociag=Szerokosc=Wysokosc=IloscWyswietlanychPociagow=0;
  Sciezka=GetCurrentDir();
  Tytul=Caption+" - ";
  //wczytanie numerow do pamieci
  for(int i=1;i<10;i++)
  {
    Numery[i]=new Graphics::TBitmap;
    String s="NR";
    s+=i;
    try
    {
      Numery[i]->LoadFromResourceName((int)HInstance,s);
    }
    catch(...)
    {
      delete Numery[i];
      Numery[i]=NULL;
    }
  }
  //wczytanie liter do pamieci
  for(int i=1;i<ILOSC_LITER;i++)
  {
    Litery[i]=new Graphics::TBitmap;
    String s="L";
    s+=i;
    try
    {
      Litery[i]->LoadFromResourceName((int)HInstance,s);
    }
    catch(...)
    {
      delete Litery[i];
      Litery[i]=NULL;
    }
  }
  /*for(int i=0;i<ILOSC_TOROW-100;i++)
  {
    int a=(i+100)/10;
    int b=i+100-a*10;
    Graphics::TBitmap *bitmap =new Graphics::TBitmap();
    Graphics::TBitmap *btmap =new Graphics::TBitmap();
    bitmap->Height=14;
    bitmap->Width=14;
    btmap->Height=14;
    btmap->Width=14;
    String s="TOR";
    s+=i+100;
    if(!(b==0 || b==9))
      bitmap->LoadFromResourceName((int)HInstance,s);
    btmap->Canvas->Brush->Color=KolorSchemat;
    btmap->Canvas->Pen->Color=KolorSchemat;
    btmap->Canvas->Rectangle(0,0,14,14);
    bitmap->Transparent=true;
    if((i/10)==53)
      bitmap->TransparentColor=bitmap->Canvas->Pixels[0][0];
    else
      bitmap->TransparentColor=clWhite;
    btmap->Canvas->Draw(0,0,bitmap);
    bitmap->Transparent=false;
    Tory->Add(btmap,NULL);
    delete bitmap;
    delete btmap;
  }*/
  Dymek = new THintWindow(this);
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::MOProgramieClick(TObject *Sender)
{
  Timer->Enabled=false;
  FOProgramie->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::WyswietlZegar(TObject *Sender)
{
  String s="";
  int h=Stacja.Godzina()/100;
  int m=Stacja.Godzina()-h*100;
  if(h==0)
    s="00";
  else
  {
    if(h<10)
      s="0"+String(h);
    else
      s=String(h);
  }
  s+=":";

  if(m==0)
    s+="00";
  else
  {
    if(m<10)
      s+="0"+String(m);
    else
      s+=String(m);
  }
  s+=":";

  if(Stacja.Sekundy()==0)
    s+="00";
  else
  {
    if(Stacja.Sekundy()<10)
      s+="0"+String(Stacja.Sekundy());
    else
      s+=String(Stacja.Sekundy());
  }
  StatusBar->Panels->Items[2]->Text=s;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::TimerTimer(TObject *Sender)
{
  if(!Application->Active && PauzaNieaktywne) return;
  if(!CzyGra )
    Timer->Enabled=false;
  else
  {
    int w=Stacja.Odmierz();
    int m=-1;
    m=Stacja.TworzPociagi(m);
    for(;;)
    {
      if(m>=0)
      {
        Timer->Enabled=false;
        FMijanka->PNapis->Visible=true;
        FMijanka->BCzekaj->Visible=true;
        FMijanka->ECzekaj->Visible=true;
        FMijanka->Label1->Visible=true;
        FMijanka->Caption="Pozwolenia zajêcia odcinka";
        FMijanka->BZezwalam->Caption="Zezwalam";
        AnsiString napis=Stacja.Numer(m,PRZYJAZD,PRZYJAZD);
        FMijanka->Wspolrzedne=Stacja.WjazdWyjazd(m,PRZYJAZD);
        FMijanka->Numer=Stacja.Wjazd(m,PRZYJAZD);
        FMijanka->LTekst->Caption="Poci¹g numer " + napis  +" czeka na pozwolenie zajêcia odcinka";
        if(Dzwieki && Mijanka)
        {
          try
          {
            MPMijanka->Play();
          }
          catch(...)
          {
            Mijanka=false;
            Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
          }
        }
        FMijanka->ShowModal();
        m=Stacja.TworzPociagi(m,FMijanka->Czekaj);
        if(!Pauza)
          Timer->Enabled=true;
      }
      else
        break;
    }
    //sprawdzam czy jest jakis pociag ktory ma wlasnie odjechac
    bool odjazd=false;
    for(int i=0;i<FGlowna->Stacja.IloscPociagow();i++)
    {
      if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==CZEKA_NA_WYJAZD)
      {
        odjazd=true;
        break;
      }
    }
    if(odjazd && Dzwieki && Odjazd)
    {
      try
      {
        MPOdjazd->Play();
      }
      catch(...)
      {
        Odjazd=false;
        Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
      }
    }
    if(w%10 && Dzwieki && NowyPociag)
    {
      try
      {
        MPNowyPociag->Play();
      }
      catch(...)
      {
        NowyPociag=false;
        Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
      }
    }
    if(w/10 && Dzwieki && Opoznienie)
    {
      try
      {
        MPOpoznienie->Play();
      }
      catch(...)
      {
        Opoznienie=false;
        Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
      }
    }
    WyswietlZegar(this);
    RysujStacje(this);
    RysujPociag(this);
    if(!PelneOkno)WypiszRozklad(this);
    if(Bocznica)
      FBocznica->RysujBocznice();
    if(Lokomot)
      FLokomot->Rysuj();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::NowagraClick(TObject *Sender)
{
  Timer->Enabled=false;
  if(CzyGra)
  {
    if(Application->MessageBox("Czy chcesz zapisaæ stan gry?","Zapis stanu gry",MB_YESNO)==IDYES)
      Zapiszstangry1Click(this);
  }
  if(ODRozklad->Execute())
  {
    String s=ODRozklad->FileName;
    switch(Stacja.WczytajRozklad(s.c_str()))
    {
      case 0:
      {// poprawnie wczytano Rozklad
        WczytajRysunki();
        CzyGra=true;
        break;
      }
      case 1:
      {
        Application->MessageBox("B³¹d odczytu pliku z opisem rozkladu.","B³ad odczytu pliku",MB_OK);
        return;
      }

      case 2:
      {
        Application->MessageBox("Stara wersja pliku z rozk³adem. Skontaktuj siê z autorem rozk³adu.","Stara wersja pliku",MB_OK);
        return;
      }
      case 3:
      {
        Application->MessageBox("B³¹d odczytu pliku z opisem stacji.","B³ad odczytu pliku",MB_OK);
        return;
      }
      case 4:
      {
        Application->MessageBox("B³¹d w opisie rozk³adu jazdy. Skontaktuj siê z autorem rozk³adu.","Z³y opis",MB_OK);
        return;
      }
      case 5:
      {
        Application->MessageBox("B³¹d w opisie wjazdu na linii jednotorowej. Skontaktuj siê z autorem stacji.","Z³y opis",MB_OK);
        return;
      }
      case 6:
      {
        Application->MessageBox("Brak lokomotywowni. Skontaktuj siê z autorem stacji.","Brak szopy",MB_OK);
        return;
      }
      case 7:
      {
        Application->MessageBox("Niew³aœciwe parametry lokomotywowni. Skontaktuj siê z autorem stacji.","Z³y opis",MB_OK);
        return;
      }
      case 8:
      {
        Application->MessageBox("Niew³aœciwe wspó³rzêdne punktu. Jeden lub kilka poci¹gów nie mo¿e byc stworzonych. Skontaktuj siê z autorem rozk³adu.","Z³y opis",MB_OK);
        return;
      }
      case 9:
      {
        Application->MessageBox("Brak wolnych miejsc dla poci¹gów. Skontaktuj siê z autorem rozk³adu.","Z³y opis",MB_OK);
        return;
      }
      case 10:
      {
        Application->MessageBox("Lok ma stac na zajêtym miejscu. Skontaktuj siê z autorem rozk³adu.","Z³y opis",MB_OK);
        return;
      }
      case 11:
      {
        Application->MessageBox("Wagon ma stac na zajêtym miejscu. Skontaktuj siê z autorem rozk³adu.","Z³y opis",MB_OK);
        return;
      }
      case 12:
      {
        Application->MessageBox("B³¹d w ustawieniu loka. Skontaktuj siê z autorem rozk³adu.","Z³y opis",MB_OK);
        return;
      }
    }
    StanGry="";
    int l;
    for(l=s.Length();l>0;l--)
    {
      if(s[l]=='\\') break;
    }
    SDStan->InitialDir=s.SubString(1,l-1);
    String txt=s.SubString(1,s.Length()-4)+".txt";
    try
    {
      FUwagi->MUwagi->Lines->LoadFromFile(txt);
      MUwagi->Visible=true;
      FPoczatek->BUwagi->Enabled=true;
    }
    catch (...)
    {
      MUwagi->Visible=false;
      FPoczatek->BUwagi->Enabled=false;
      FUwagi->MUwagi->Clear();
    }
    //zaladowanie rysunku tla o ile istnieje
    if (Tlo)
    {
      delete Tlo;
      Tlo=NULL;
    }
    String tlo=s.SubString(1,s.Length()-4);
    int i;
    for(i=tlo.Length();i>0;i--)
      if(tlo[i]=='\\') break;
    tlo=tlo.SubString(1,i)+Stacja.NazwaPlikuStacji();
    tlo=tlo.SubString(1,tlo.Length()-4);
    tlo+=".bmp";   
    Tlo=new Graphics::TBitmap();
    try
    {
      Tlo->LoadFromFile(tlo);
    }
    catch(...)
    {
      delete Tlo;
      Tlo=NULL;
    }
    RysujStacje(this);
    Caption=Tytul+Stacja.NazwaPlikuStacji();
     FPoczatek->ShowModal();
    if(!Pauza)
      Timer->Enabled=true;
     DostosujWielkoscOkna();
  }
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::RysujStacje(TObject *Sender)
{
  Graphics::TBitmap* rysunek=new Graphics::TBitmap();
  Graphics::TBitmap* rys=new Graphics::TBitmap();
  rysunek->Width=PBStacja->Width;
  rysunek->Height=PBStacja->Height;
  rysunek->Canvas->Brush->Color=KolorSchemat;
  rysunek->Canvas->Pen->Color=KolorSchemat;
  rysunek->Canvas->Rectangle(0,0,rysunek->Width,rysunek->Height);
  rys->Width=14;
  rys->Height=14;
  if(KolorTlo && Tlo)
    rysunek->Canvas->Draw(0,0,Tlo);
  if(CzyGra)//jesli wczytana jest jakas Stacja
  {
    int Zaznaczanie=0;
    if(CzyZaznaczanie) Zaznaczanie=3;
    for(int x=0;x<Stacja.Wysokosc();x++)
    {
      for(int y=0;y<Stacja.Szerokosc();y++)
      {
        if(Stacja.Obraz(x,y)>=100) //tor niezelektryfikowany
        {
          int s;
          s=Stacja.Obraz(x,y)/10;
          switch(Stacja.Stan(x,y))
          {
            case POLE_WOLNE: //pole niezajete
              if(CzyZaznaczanie) Zaznaczanie=1;
              s=s*10+7+Zaznaczanie;
              if(CzyZaznaczanie) Zaznaczanie=3;
              break;
            case POLE_ZAREZERWOWANE: //pole zarezerwowane
              s=s*10+1+Zaznaczanie;
              break;
            case POLE_ZAJETE: //pole zajete przez sklad
              s=s*10+3+Zaznaczanie;
              break;
            case WYBOR_TRASY: //wybor trasy
              s=s*10+1;
              break;
            case WYBOR_TRASY_POCIAG:
              s=s*10+3;
              break;
          }
          //wyswietlenie konkretnego toru
          if(KolorTlo)
          {
            Tory->Draw(rys->Canvas,0,0,s-100,true);
            rys->Transparent=true;
            if((s/10)==53)
              rys->TransparentColor=rys->Canvas->Pixels[0][0];
            else
              rys->TransparentColor=clWhite;
            rysunek->Canvas->Draw(y*14,x*14,rys);
            rys->Transparent=false;
          }
          else
            Tory->Draw(rysunek->Canvas,y*14,x*14,s-100,true);
        }
        else if(Stacja.Obraz(x,y)<10 &&Stacja.Obraz(x,y)>0)
        {
          int s;
          s=Stacja.Obraz(x,y);
          rysunek->Canvas->Draw(y*14,x*14,Numery[s]);
        }
        else if(Stacja.Obraz(x,y)<0 && Stacja.Obraz(x,y)>-100)
        {
          int s;
          s=Stacja.Obraz(x,y);
          rysunek->Canvas->Draw(y*14,x*14,Litery[-s]);
        }
        else if(Stacja.Obraz(x,y))
        {
          int s;
          s=Stacja.Obraz(x,y);
          switch(Stacja.Stan(x,y))
          {
            case POLE_WOLNE: //pole niezajete
              s=s*10+2+Zaznaczanie;
              break;
            case POLE_ZAREZERWOWANE: //pole zarezerwowane
              s=s*10+1+Zaznaczanie;
              break;
            case POLE_ZAJETE: //pole zajete przez sklad
              s=s*10+3+Zaznaczanie;
              break;
            case WYBOR_TRASY: //wybor trasy
              s=s*10+1;
              break;
            case WYBOR_TRASY_POCIAG:
              s=s*10+3;
              break;
          }
          //wyswietlenie konkretnego toru
          if(KolorTlo)
          {
            Tory->Draw(rys->Canvas,0,0,s-100,true);
            rys->Transparent=true;
            if((s/10)==53)
              rys->TransparentColor=rys->Canvas->Pixels[0][0];
            else
              rys->TransparentColor=clWhite;
            rysunek->Canvas->Draw(y*14,x*14,rys);
            rys->Transparent=false;
          }
          else
            Tory->Draw(rysunek->Canvas,y*14,x*14,s-100,true);
        }
      }
    }
    PBStacja->Canvas->Draw(0,0,rysunek);
  }
  delete rysunek;
  delete rys;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::FormPaint(TObject *Sender)
{
  if(CzyGra)
  {
    RysujStacje(this);
    RysujPociag(this);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::PBStacjaMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  ZaznaczanieTras(Button,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::MPrzyjazdyClick(TObject *Sender)
{
  Timer->Enabled=false;
  FRozklad->Rodzaj(PRZYJAZD);
  FRozklad->Caption="Przyjazdy";
  FRozklad->SBTlo->VertScrollBar->Position=0;
  FRozklad->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::RysujPociag(TObject *Sender)
{
  int poz=0;
  for(int i=0;i<10;i++)
  {
    Wagony[i][0]=-1;
    Wagony[i][1]=-1;
  }
  Graphics::TBitmap* rysunek=new Graphics::TBitmap();
  rysunek->Height=PBPociag->Height;
  rysunek->Width=PBPociag->Width;
  rysunek->Canvas->Brush->Color=KolorPodglad;
  rysunek->Canvas->Pen->Color=KolorPodglad;
  rysunek->Canvas->Rectangle(0,0,rysunek->Width,rysunek->Height);
  if(!Pociag)
  {
    PBPociag->Canvas->Draw(0,0,rysunek);
    delete rysunek;
    return;
  }
  int nr=Stacja.NrPunktu(Pociag);
  if(nr==-1)
  {
    delete rysunek;
    return;
  }
  for(int i=0;i<DLUGOSC_POSTOJOWYCH;i++)
  {
    char* napis;
    int nazwa=Stacja.NazwaNr(nr,i);
    if(nazwa<=0 ) break;
    if(KolorPodglad!=clWhite)
    {
      Tabor[nazwa]->Transparent=true;
      Tabor[nazwa]->TransparentColor=clWhite;
      rysunek->Canvas->Draw(poz,0,Tabor[nazwa]);
      Tabor[nazwa]->Transparent=false;
    }
    else
      rysunek->Canvas->Draw(poz,0,Tabor[nazwa]);
    Wagony[i][0]=poz;
    Wagony[i][1]=poz+Tabor[nazwa]->Width;
    //informacje pod rysunkiem
    if(!Stacja.Sprawnosc(nr,i))
      rysunek->Canvas->Font->Color=clRed;
    else if(!Stacja.CzyZjechac(nr,i))
      rysunek->Canvas->Font->Color=clGreen;
    else
      rysunek->Canvas->Font->Color=clBlack;
    if(Stacja.CzyRuch(nr,i))
      rysunek->Canvas->Font->Style=TFontStyles()<<fsItalic;
    else if(Stacja.Czas(nr,i))
      rysunek->Canvas->Font->Style=TFontStyles()<<fsBold;
    else
      rysunek->Canvas->Font->Style=TFontStyles();
    rysunek->Canvas->TextFlags=ETO_OPAQUE;
    if(Stacja.RodzajSkladu(nr,i)>=3)
    {//lokomotywa
      rysunek->Canvas->TextOut(poz,42,Stacja.Nazwa(nr,i));
      napis=Stacja.NumerLoka(nr,i);
      rysunek->Canvas->TextOut(poz,56,napis);
      delete [] napis;
    }
    else if(Stacja.RodzajSkladu(nr,i)>=1)
    {//jednostka nierozlaczalna
      int p=Stacja.NrRozklad(nr,i);
      if(Stacja.CzyZjechac(nr,i))
      {
        if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
          rysunek->Canvas->TextOutA(poz,42,Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD)));
        else
          rysunek->Canvas->TextOutA(poz,42,Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,ODJAZD)));
      }
      else
      {
        rysunek->Canvas->TextOutA(poz,42,Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD)));
      }
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
          napis=Stacja.Numer(p,NIEOKRESLONA,PRZYJAZD);
      else
        napis=Stacja.Numer(p,NIEOKRESLONA,ODJAZD);
      rysunek->Canvas->TextOutA(poz+15,42,napis);
      delete[] napis;
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
        rysunek->Canvas->TextOutA(poz+58,42,Stacja.Wjazd(p,NIEOKRESLONA));
      else
        rysunek->Canvas->TextOutA(poz+58,42,Stacja.Wyjazd(p,NIEOKRESLONA));
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
        napis=Stacja.Godzina(p,NIEOKRESLONA,PRZYJAZD);
      else
        napis=Stacja.Godzina(p,NIEOKRESLONA,ODJAZD);
      rysunek->Canvas->TextOutA(poz+70,42,napis);
      delete[] napis;
      int a;
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           a=FGlowna->Stacja.Opoznienie(p,NIEOKRESLONA,PRZYJAZD);
      else
        a=FGlowna->Stacja.Opoznienie(p,NIEOKRESLONA);
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
      rysunek->Canvas->TextOutA(poz+100,42,s);
      napis=Stacja.Skad(p,NIEOKRESLONA);
      rysunek->Canvas->TextOutA(poz,56,napis);
      delete[] napis;
      napis=Stacja.Dokad(p,NIEOKRESLONA);
      rysunek->Canvas->TextOutA(poz,70,napis);
      delete[] napis;
      rysunek->Canvas->TextOutA(poz+130,42,Stacja.Nazwa(nr,i));
      napis=Stacja.NumerLoka(nr,i);
      rysunek->Canvas->TextOutA(poz+130,56,napis);
      delete [] napis;
    }
    else
    {//sklad
      int p=Stacja.NrRozklad(nr,i);
      if(Stacja.CzyZjechac(nr,i))
      {
        if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           rysunek->Canvas->TextOutA(poz,42,Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD)));
        else
          rysunek->Canvas->TextOutA(poz,42,Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,ODJAZD)));
      }
      else
      {
        rysunek->Canvas->TextOutA(poz,42,Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD)));
      }
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           napis=Stacja.Numer(p,NIEOKRESLONA,PRZYJAZD);
      else
        napis=Stacja.Numer(p,NIEOKRESLONA,ODJAZD);
      rysunek->Canvas->TextOutA(poz+15,42,napis);
      delete[] napis;
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           rysunek->Canvas->TextOutA(poz+58,42,Stacja.Wjazd(p,NIEOKRESLONA));
      else
        rysunek->Canvas->TextOutA(poz+58,42,Stacja.Wyjazd(p,NIEOKRESLONA));
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           napis=Stacja.Godzina(p,NIEOKRESLONA,PRZYJAZD);
      else
        napis=Stacja.Godzina(p,NIEOKRESLONA,ODJAZD);
      rysunek->Canvas->TextOutA(poz+70,42,napis);
      delete[] napis;
      int a;
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           a=FGlowna->Stacja.Opoznienie(p,NIEOKRESLONA,PRZYJAZD);
      else
        a=FGlowna->Stacja.Opoznienie(p,NIEOKRESLONA);
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
      rysunek->Canvas->TextOutA(poz+100,42,s);
      napis=Stacja.Skad(p,NIEOKRESLONA);
      rysunek->Canvas->TextOutA(poz,56,napis);
      delete[] napis;
      napis=Stacja.Dokad(p,NIEOKRESLONA);
      rysunek->Canvas->TextOutA(poz,70,napis);
      delete[] napis;
    }
    poz+=Tabor[nazwa]->Width;
    if(!Stacja.CzyPolaczony(nr,i))
      poz+=10;
  }
  PBPociag->Canvas->Draw(0,0,rysunek);
  delete rysunek;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::PBPociagMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StatusBar->Panels->Items[1]->Text="";
  if(!(Y>0 && Y<40)) return;
  int i;
  for(i=0;i<10;i++)
  {
    if(Wagony[i][0]<X && Wagony[i][1]>X) break;
  }
  if(i==10) return;
  String s;
  char* napis=0;
  if(Button==mbRight)
  {
    napis=Stacja.Laczenie(Pociag,i);
    s=napis;
    RysujPociag(this);
  }
  else if(Button==mbLeft)
  {
    if(i>0)
    {
      napis=Stacja.Laczenie(Pociag,i-1);
      s=napis;
      RysujPociag(this);
    }
    else
      s="Po lewej stronie nic nie stoi";
  }
  if(s.Length() && Dzwieki && Blad)
  {
    try
    {
      MPBlad->Play();
    }
    catch(...)
    {
      Blad=false;
      Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
    }
  }
  StatusBar->Panels->Items[1]->Text=s;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::WypiszRozklad(TObject *Sender)
{
  Graphics::TBitmap* przyjazdy=new Graphics::TBitmap();
  przyjazdy->Height=PBPrzyjazdy->Height;
  przyjazdy->Width=PBPrzyjazdy->Width;
  przyjazdy->Canvas->Brush->Color=KolorPrzyjazdy;
  przyjazdy->Canvas->Pen->Color=KolorPrzyjazdy;
  przyjazdy->Canvas->Rectangle(0,0,przyjazdy->Width,przyjazdy->Height);
  Graphics::TBitmap* odjazdy=new Graphics::TBitmap();
  odjazdy->Height=PBOdjazdy->Height;
  odjazdy->Width=PBOdjazdy->Width;
  odjazdy->Canvas->Brush->Color=KolorOdjazdy;
  odjazdy->Canvas->Pen->Color=KolorOdjazdy;
  odjazdy->Canvas->Rectangle(0,0,odjazdy->Width,odjazdy->Height);
  int licznik=0;
    for(int i=0;i<FGlowna->Stacja.IloscPociagow();i++)
    {
      if(Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ROZLACZANY || Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_DOCELOWY_ROZLACZANY
         || FGlowna->Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ZE_STACJI_LACZONY)
        continue;
      else if (FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==JEST ||
                FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==CZEKA_NA_WYJAZD)
      {
        licznik++;
        przyjazdy->Canvas->Font->Color=clBlue;
      }
      else if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==BEDZIE ||
        (/*FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==JEST ||*/
         FGlowna->Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ZE_STACJI))
      {
        licznik++;
        przyjazdy->Canvas->Font->Color=clBlack;
      }
      else if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==CZEKA_NA_WJAZD)
      {
        licznik++;
        przyjazdy->Canvas->Font->Color=clRed;
      }
      else if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==WJEZDZA)
      {
        licznik++;
        przyjazdy->Canvas->Font->Color=clGreen;
      }
      else
        continue;
      if(Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_BEZ_ZATRZYMANIA)
        przyjazdy->Canvas->Font->Style=TFontStyles()<<fsItalic;
      else if(Stacja.CzyRozlaczenie(i,PRZYJAZD))
        przyjazdy->Canvas->Font->Style=TFontStyles()<<fsUnderline;
      else
        przyjazdy->Canvas->Font->Style=TFontStyles();
      int poz=(licznik-1)*14;
      String s;
      char* napis=0;
      s=FGlowna->Stacja.Wjazd(i,PRZYJAZD);
      przyjazdy->Canvas->TextOutA(2,poz,s);
      napis=FGlowna->Stacja.Godzina(i,PRZYJAZD,PRZYJAZD);
      przyjazdy->Canvas->TextOutA(15,poz,napis);
      delete[] napis;
      int p=FGlowna->Stacja.Opoznienie(i,PRZYJAZD);
      if(p>0)
      {
        s="+";
        s+=p;
      }
      else if(p==0)
        s="";
      else
        s=p;
      przyjazdy->Canvas->TextOutA(44,poz,s);
      napis=FGlowna->Stacja.NazwaRodzajTyp(i,PRZYJAZD);
      napis[1]='\0';
     /* napis=FGlowna->Stacja.Rodzaj(i,PRZYJAZD);
      char n[2];
      n[0]=napis[0];n[1]='\0';
      if(!strcmp(napis,"EX")) n[0]='X';*/
      przyjazdy->Canvas->TextOutA(75,poz,napis);
      delete [] napis;
      napis=FGlowna->Stacja.Numer(i,PRZYJAZD,PRZYJAZD);
      przyjazdy->Canvas->TextOutA(90,poz,napis);
      delete[] napis;
      przyjazdy->Canvas->TextOutA(130,poz,FGlowna->Stacja.Peron(Stacja.Peron(i,PRZYJAZD,PRZYJAZD)));
      if(Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_DOCELOWY || Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ZE_STACJI
         || Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_DOCELOWY_ROZLACZANY || Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ZE_STACJI_LACZONY)
        przyjazdy->Canvas->TextOutA(146,poz,"#");
      else if(Stacja.CzyZmianaLoka(i,PRZYJAZD))
        przyjazdy->Canvas->TextOutA(146,poz,">");
      if(licznik==przyjazdy->Height/14) break;
    }
    licznik=0;
    for(int i=0;i<FGlowna->Stacja.IloscPociagow();i++)
    {
      if(Stacja.TypPociagu(i,ODJAZD)==POWROT_LOKA)
        continue;
      int l=Stacja.CzyLaczenie(i,ODJAZD);
      int ll=l-(l/10)*10;
      if(l &&ll!=1)
      {
        continue;
      }
      else if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==JEST)
      {
        licznik++;
        odjazdy->Canvas->Font->Color=clBlue;
      }
      else if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==BEDZIE || FGlowna->Stacja.StanPociagu(i,ODJAZD)==CZEKA_NA_WJAZD
              || FGlowna->Stacja.StanPociagu(i,ODJAZD)==WJEZDZA)
      {
        licznik++;
        odjazdy->Canvas->Font->Color=clBlack;
      }
      else if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==CZEKA_NA_WYJAZD)
      {
        licznik++;
        odjazdy->Canvas->Font->Color=clRed;
      }
      else
        continue;
      if(Stacja.TypPociagu(i,ODJAZD)==POCIAG_BEZ_ZATRZYMANIA)
        odjazdy->Canvas->Font->Style=TFontStyles()<<fsItalic;
      else if(l)
        odjazdy->Canvas->Font->Style=TFontStyles()<<fsUnderline;
      else
        odjazdy->Canvas->Font->Style=TFontStyles();
      int poz=(licznik-1)*14;
      String s;
      char * napis=0;
      if(Stacja.TypPociagu(i,ODJAZD)==POCIAG_ZE_STACJI ||Stacja.TypPociagu(i,ODJAZD)==POCIAG_DOCELOWY
         || Stacja.TypPociagu(i,ODJAZD)==POCIAG_ZE_STACJI_LACZONY ||Stacja.TypPociagu(i,ODJAZD)==POCIAG_DOCELOWY_ROZLACZANY)
        odjazdy->Canvas->TextOutA(0,poz,"#");
      else if(Stacja.CzyZmianaLoka(i,ODJAZD))
        odjazdy->Canvas->TextOutA(0,poz,">");
      odjazdy->Canvas->TextOutA(10,poz,FGlowna->Stacja.Peron(Stacja.Peron(i,ODJAZD,ODJAZD)));
      napis=FGlowna->Stacja.Godzina(i,ODJAZD,ODJAZD);
      odjazdy->Canvas->TextOutA(26,poz,napis);
      delete[] napis;
      int p=FGlowna->Stacja.Opoznienie(i,ODJAZD);
      if(p>0)
      {
        s="+";
        s+=p;
      }
      else if(p==0)
        s="";
      else
        s=p;
      odjazdy->Canvas->TextOutA(55,poz,s);
      napis=FGlowna->Stacja.NazwaRodzajTyp(i,ODJAZD);
      napis[1]='\0';
      /*napis=FGlowna->Stacja.Rodzaj(i,ODJAZD);
      char n[2];
      n[0]=napis[0];n[1]='\0';
      if(!strcmp(napis,"EX")) n[0]='X';*/
      odjazdy->Canvas->TextOutA(85,poz,napis);
      delete[] napis;
      napis=FGlowna->Stacja.Numer(i,ODJAZD,ODJAZD);
      odjazdy->Canvas->TextOutA(100,poz,napis);
      delete[] napis;
      s=FGlowna->Stacja.Wyjazd(i,ODJAZD);
      odjazdy->Canvas->TextOutA(142,poz,s);
      if(licznik==odjazdy->Height/14) break;
    }
    PBPrzyjazdy->Canvas->Draw(0,0,przyjazdy);
    PBOdjazdy->Canvas->Draw(0,0,odjazdy);
    delete przyjazdy;
    delete odjazdy;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::MOdjazdyClick(TObject *Sender)
{
  Timer->Enabled=false;
  FRozklad->Rodzaj(ODJAZD);
  FRozklad->Caption="Odjazdy";
  FRozklad->SBTlo->VertScrollBar->Position=0;
  FRozklad->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::ZaznaczanieTras(TMouseButton Button, int X, int Y,bool bocznica)
{
  if(!Pauza)
    Timer->Enabled=true;
  int y=X/14;
  int x=Y/14;
  static int etap=0; //1 - wywolanie z punktem posrednim
  StatusBar->Panels->Items[1]->Text="";
  if(Button==mbRight && CzyGra) //wybieranie pociagu
  {
    if(bocznica)
    {
      Timer->Enabled=(!PauzaZaznaczanie && !Pauza);
      Pociag=x*100+y;
      RysujPociag(this);
      etap=0;
      CzyZaznaczanie=false;
      Stacja.Zaznacz();
      RysujStacje(this);
    }
    else if(Stacja.CzyPunkt(x*100+y)==BOCZNICA )
    { 
      etap=0;
      CzyZaznaczanie=false;
      Stacja.Zaznacz();
      RysujStacje(this);
      FBocznica->Parametry(Stacja.NrPunktu(x*100+y),Stacja.Bocznica(x*100+y,POCZATEK_BOCZNICY),Stacja.Bocznica(x*100+y,KONIEC_BOCZNICY),x*100+y);
      Bocznica=true;
      FBocznica->ShowModal();
      Bocznica=false;
    }
    else if(Stacja.CzyPunkt(x*100+y)==LOKOWNIA)
    {
      Pociag=x*100+y;
      RysujPociag(this);
      etap=0;
      CzyZaznaczanie=false;
      Stacja.Zaznacz();
      RysujStacje(this);
      if(Stacja.Stan(x,y)==POLE_WOLNE)
      {
        Lokomot=true;
        FLokomot->ShowModal();
        Lokomot=false;
      }
    }
    else if(Stacja.CzyPunkt(x*100+y) && Stacja.CzyStoiPociag(x*100+y))
    {
      Timer->Enabled=(!PauzaZaznaczanie && !Pauza);
      Pociag=x*100+y;
      RysujPociag(this);
      etap=0;
      CzyZaznaczanie=false;
      Stacja.Zaznacz();
      RysujStacje(this);
    }
    else
      return;
  }
  else if(Button==mbLeft && CzyGra && Pociag ) //wybieranie trasy
  {
    tObiektRuchomy * obiekt=Stacja.Obiekt(Pociag,x*100+y);
    if(etap) //zaznaczenie jednej konkretnej trasy
    {
      int stan=NIEOKRESLONA;
      try
      {
        stan=Stacja.Zaznacz(obiekt,x*100+y,obiekt->TypLoka());
      }
      catch(...)
      {}
      if(stan==OK)
      {
        CzyZaznaczanie=false;
        RysujStacje(this);
        etap=0;
        Pociag=0;
        RysujPociag(this);
      }
      else
      {
        if(stan==BRAK_JEDNOZNACZNOSCI)
        {
          StatusBar->Panels->Items[1]->Text="Wskazany punk nie identyfikuje jednoznacznie trasy";
          if(Dzwieki && Blad)
          {
            try
            {
              MPBlad->Play();
            }
            catch(...)
            {
             Blad=false;
             Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
            }
          }
        }
        if(stan==BRAK_TRASY)
        {
          StatusBar->Panels->Items[1]->Text="Wskazany punkt nie znajduje siê na zaznaczanej trasie";
          if(Dzwieki && Blad)
          {
            try
            {
              MPBlad->Play();
            }
            catch(...)
            {
              Blad=false;
             Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
           }
          }
        }
      }
    }
    else  //zaznaczenie wszystkich mozliwych tras
    {
      int punkt=Stacja.CzyPunkt(x*100+y);
      if(punkt)
      {
        if(punkt==PERON || punkt==PERON_TOWAROWY)
        {
          y=Stacja.Wspolrzedna(Pociag,x*100+y);
        }
        if(Stacja.CzyPunkt(Pociag)==PERON || Stacja.CzyPunkt(Pociag)==PERON_TOWAROWY)
        {
          int p=Pociag;
          Pociag=(Pociag/100)*100;
          Pociag+=Stacja.Wspolrzedna(x*100+y,p);
        }
        int p_k=-1;
        if(punkt==BOCZNICA)
        {
          FBocznica->Parametry(Stacja.NrPunktu(x*100+y),Stacja.Bocznica(x*100+y,POCZATEK_BOCZNICY),Stacja.Bocznica(x*100+y,KONIEC_BOCZNICY),x*100+y);
          FBocznica->CzyZaznaczanie=true;
          if(FBocznica->ShowModal()==mrIgnore)
          {
            FBocznica->CzyZaznaczanie=false;
            p_k=FBocznica->Numer;
          }
          else
          {
            FBocznica->CzyZaznaczanie=false;
            return;
          }
        }
        char* napis=Stacja.Zaznaczanie(Pociag,x*100+y,p_k);
        String w=napis;
        if(w.Length())
        {//nie mozna zaznaczyc trasy
          StatusBar->Panels->Items[1]->Text=w;
          if(Dzwieki && Blad)
          {
            try
            {
              MPBlad->Play();
            }
            catch(...)
            {
              Blad=false;
              Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
            }
          }
          return;
        }
        etap=1;
        obiekt=Stacja.Obiekt(Pociag,x*100+y);
        if(!obiekt)
        {
          etap=0;
          return;
        }
        if(Stacja.Zaznacz(Pociag,x*100+y,obiekt->TypLoka())==OK)
        {
          CzyZaznaczanie=true;
          RysujStacje(this);
        }
        else
        {
          StatusBar->Panels->Items[1]->Text="Brak trasy miêdzy wskazanymi punktami";
          if(Dzwieki && Blad)
          {
            try
            {
              MPBlad->Play();
            }
            catch(...)
            {
              Blad=false;
              Application->MessageBox("B³¹d podczas odtwarzania dŸwiêku. DŸwiêk zostaje wy³¹czony.","B³ad odtarzania dŸwiêku",MB_OK);
            }
          }
          etap=0;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::WczytajgreClick(TObject *Sender)
{
  Timer->Enabled=false;
  if(CzyGra)
  {
    if(Application->MessageBox("Czy chcesz zapisaæ stan gry?","Zapis stanu gry",MB_YESNO)==IDYES)
      Zapiszstangry1Click(this);
  }
  if(ODStan->Execute())
  {
    String s=ODStan->FileName;
    int stan=Stacja.WczytajStan(s.c_str());
    if(stan==0)
    {// poprawnie wczytano Rozklad i Stacje
      WczytajRysunki();
      CzyGra=true;
      StanGry=s;
    }
    else if(stan==1)
    {
      Application->MessageBox("B³¹d odczytu pliku z zapisanym stanem gry","B³¹d odczytu pliku.",MB_OK);
      return;
    }
    else
    {
      Application->MessageBox("Plik z zapisanym stanem gry pochodzi ze starszej wersji Kolejarza.","Niew³aœciwa wersja pliku.",MB_OK);
      return;
    }
    if(Stacja.CzyGraTestowa())
      StatusBar->Panels->Items[0]->Text="Gra testowa";
    else
      StatusBar->Panels->Items[0]->Text="Punkty karne";
    CzyZaznaczanie=false;
    RysujStacje(this);
    Caption=Tytul+Stacja.NazwaPlikuStacji();
    if(!Pauza)
      Timer->Enabled=true;
    DostosujWielkoscOkna();
    int l;
    for(l=s.Length();l>0;l--)
    {
      if(s[l]=='\\') break;
    }
    String txt=s.SubString(1,l);
    String tmp=Stacja.NazwaPlikuStacji();
    txt=txt+tmp.SubString(1,tmp.Length()-4)+".txt";
    try
    {
      FUwagi->MUwagi->Lines->LoadFromFile(txt);
      MUwagi->Visible=true;
    }
    catch (...)
    {
      MUwagi->Visible=false;
      FUwagi->MUwagi->Clear();
    }
    //zaladowanie rysunku tla o ile istnieje
    if (Tlo)
    {
      delete Tlo;
      Tlo=NULL;
    }
    String tlo=s.SubString(1,s.Length()-4);
    int i;
    for(i=tlo.Length();i>0;i--)
      if(tlo[i]=='\\') break;
    tlo=tlo.SubString(1,i)+Stacja.NazwaPlikuStacji();
    tlo=tlo.SubString(1,tlo.Length()-4);
    tlo+=".bmp";   
    Tlo=new Graphics::TBitmap();
    try
    {
      Tlo->LoadFromFile(tlo);
    }
    catch(...)
    {
      delete Tlo;
      Tlo=NULL;
    }
  }
  if(!Pauza)
      Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::ZapiszgreClick(TObject *Sender)
{
  Timer->Enabled=false;
  if(SDStan->Execute())
  {
    StanGry=SDStan->FileName;
    if(Stacja.ZapiszStan(StanGry.c_str())!=0)
    {
      Application->MessageBox("Nast¹pi³ b³¹d podczas próby zapisu pliku *.sav","B³¹d zapisu",ID_OK);
    }
  }
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::Tematypomocy1Click(TObject *Sender)
{
  Timer->Enabled=false;
  //Application->HelpCommand(HELP_FINDER,0);
  ShellExecute(Handle,"open","kolejarz.chm",NULL,NULL,SW_SHOW);
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::MZegarClick(TObject *Sender)
{
  Timer->Enabled=false;
  FOpcje->PageControl->ActivePageIndex=0;
  FOpcje->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::MOpoznieniaClick(TObject *Sender)
{
  Timer->Enabled=false;
  FOpcje->PageControl->ActivePageIndex=1;
  FOpcje->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::MPauzaClick(TObject *Sender)
{
  MPauza->Checked=!MPauza->Checked;
  Timer->Enabled=!MPauza->Checked;
  Pauza=!Timer->Enabled;
}
//---------------------------------------------------------------------------


void __fastcall TFGlowna::Lokomotywownia1Click(TObject *Sender)
{
  Lokomot=true;
  FLokomot->ShowModal();
  Lokomot=false;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::Zakocz1Click(TObject *Sender)
{
  if(CzyGra)
    if(Application->MessageBox("Czy chcesz zapisaæ stan gry?","Zapis stanu gry",MB_YESNO)==IDYES)
      Zapiszstangry1Click(this);
  Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::Zapiszstangry1Click(TObject *Sender)
{
  Timer->Enabled=false;
  if(StanGry.Length())
  {
    if(Stacja.ZapiszStan(StanGry.c_str())!=0)
    {
      Application->MessageBox("Nast¹pi³ b³¹d podczas próby zapisu pliku *.sav","B³¹d zapisu",ID_OK);
    }
  }
  else
  {
    if(SDStan->Execute())
    {
      StanGry=SDStan->FileName;
      if(Stacja.ZapiszStan(StanGry.c_str())!=0)
      {
        Application->MessageBox("Nast¹pi³ b³¹d podczas próby zapisu pliku *.sav","B³¹d zapisu",ID_OK);
      }
    }
  }
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(CzyGra)
    if(Application->MessageBox("Czy chcesz zapisaæ stan gry?","Zapis stanu gry",MB_YESNO)==IDYES)
      Zapiszstangry1Click(this);

  PlikINI->WriteInteger("Zegar","Interval",Timer->Interval);
  PlikINI->WriteBool("Zegar","Czas_rzeczywisty",FOpcje->CBCzasRzeczywisty->Checked);

  PlikINI->WriteInteger("Opoznienia","Wyprzedzenie",Stacja.Wyprzedzenie());
  PlikINI->WriteInteger("Opoznienia","Podmiejski-",Stacja.PlusMinus(0,0));
  PlikINI->WriteInteger("Opoznienia","Podmiejski+",Stacja.PlusMinus(0,1));
  PlikINI->WriteInteger("Opoznienia","Osobowy-",Stacja.PlusMinus(1,0));
  PlikINI->WriteInteger("Opoznienia","Osobowy+",Stacja.PlusMinus(1,1));
  PlikINI->WriteInteger("Opoznienia","Pospieszny-",Stacja.PlusMinus(2,0));
  PlikINI->WriteInteger("Opoznienia","Pospieszny+",Stacja.PlusMinus(2,1));
  PlikINI->WriteInteger("Opoznienia","Expres-",Stacja.PlusMinus(3,0));
  PlikINI->WriteInteger("Opoznienia","Expres+",Stacja.PlusMinus(3,1));
  PlikINI->WriteInteger("Opoznienia","Towarowy-",Stacja.PlusMinus(4,0));
  PlikINI->WriteInteger("Opoznienia","Towarowy+",Stacja.PlusMinus(4,1));
  PlikINI->WriteInteger("Opoznienia","Specjalny-",Stacja.PlusMinus(5,0));
  PlikINI->WriteInteger("Opoznienia","Specjalny+",Stacja.PlusMinus(5,1));

  PlikINI->WriteBool("Opcje","Pauza_zaznaczanie",PauzaZaznaczanie);
  PlikINI->WriteBool("Opcje","Pauza_podglad",PauzaPodglad);
  PlikINI->WriteBool("Opcje","Pauza_nieaktywne",PauzaNieaktywne);
  PlikINI->WriteInteger("Opcje","Rozklad_pierwszych",IloscWyswietlanychPociagow);
  PlikINI->WriteBool("Opcje","Staly_rozmiar",StalyRozmiar);

  PlikINI->WriteBool("Kolor","Tlo",KolorTlo);
  PlikINI->WriteInteger("Kolor","Schemat_stacji",KolorSchemat);
  PlikINI->WriteInteger("Kolor","Przyjazdy",KolorPrzyjazdy);
  PlikINI->WriteInteger("Kolor","Odjazdy",KolorOdjazdy);
  PlikINI->WriteInteger("Kolor","Podglad_skladow",KolorPodglad);

  PlikINI->WriteBool("Dzwieki","Dzwiek",Dzwieki);
  PlikINI->WriteBool("Dzwieki","Nowy_pociag",NowyPociag);
  PlikINI->WriteString("Dzwieki","Nowy_pociag_plik",NowyPociagPlik);
  PlikINI->WriteBool("Dzwieki","Blad",Blad);
  PlikINI->WriteString("Dzwieki","Blad_plik",BladPlik);
  PlikINI->WriteBool("Dzwieki","Mijanka",Mijanka);
  PlikINI->WriteString("Dzwieki","Mijanka_plik",MijankaPlik);
  PlikINI->WriteBool("Dzwieki","Odjazd",Odjazd);
  PlikINI->WriteString("Dzwieki","Odjazd_plik",OdjazdPlik);
  PlikINI->WriteBool("Dzwieki","Pkt_karne",PktKarne);
  PlikINI->WriteString("Dzwieki","Pkt_karne_plik",PktKarnePlik);
  PlikINI->WriteBool("Dzwieki","Opoznienie",Opoznienie);
  PlikINI->WriteString("Dzwieki","Opoznienie_plik",OpoznieniePlik);

  delete PlikINI;

}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::FormDestroy(TObject *Sender)
{
  for(int i=0;i<ILOSC_RYSUNKOW;i++)
  {
    delete Tabor[i];
  }
  for(int i=0;i<10;i++)
  {
    delete Numery[i];
  }
  for(int i=0;i<ILOSC_LITER;i++)
  {
    delete Litery[i];
  }
  delete Tlo;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::PBPrzyjazdyDblClick(TObject *Sender)
{
  Timer->Enabled=false;
  FRozklad->Rodzaj(PRZYJAZD);
  FRozklad->Caption="Przyjazdy";
  FRozklad->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TFGlowna::PBOdjazdyDblClick(TObject *Sender)
{
  Timer->Enabled=false;
  FRozklad->Rodzaj(ODJAZD);
  FRozklad->Caption="Odjazdy";
  FRozklad->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::WczytajRysunki(void)
{
  for(int i=1;i<ILOSC_RYSUNKOW;i++)
  {
    if(Tabor[i])
    {
      delete Tabor[i];
      Tabor[i]=NULL;
    }
    else
      break;
  }
  SetCurrentDir(Sciezka+"\\Tabor\\");
  for(int i=1;i<=Stacja.IloscRysunkow();i++)
  {
    String s=Stacja.Nazwa(i,NIEOKRESLONA);
    s+=".bmp";
    Tabor[i]=new Graphics::TBitmap();
    try
    {
      Tabor[i]->LoadFromFile(s);
    }
    catch(...)
    {
      String ss="Brak rysunku "+s;
      Application->MessageBox(ss.c_str(),"Brak rysunku",MB_OK);
      Application->Terminate();
    }
  }
  SetCurrentDir(Sciezka);
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_SPACE)
  {
    if(!Pociag) return;
    if(!Stacja.CzyPodglad()) return;
    Timer->Enabled=(!PauzaPodglad && !PauzaZaznaczanie && !Pauza);
    //licze rozmiar rysunku
    int poz=0;
    int nr=Stacja.NrPunktu(Pociag);
    int * sklad;
    for(int i=0;i<DLUGOSC_POSTOJOWYCH;i++)
    {
      int nazwa=Stacja.NazwaNr(nr,i);
      if(nazwa<=0 ) break;
      if(Stacja.RodzajSkladu(nr,i)>2)
      {
        poz+=Tabor[nazwa]->Width;
        if(!Stacja.CzyPolaczony(nr,i))
          poz+=10;
      }
      else
      {
        char* napis;
        sklad=Stacja.Podglad(nr,i);
        for(int u=0;sklad[u];)
        {
          for(int il=sklad[u];il>0;il--)
          {
            poz+=Tabor[sklad[u+1]]->Width;
          }
          u+=2;
        }
        if(!Stacja.CzyPolaczony(nr,i))
          poz+=10;
        delete [] sklad;
        sklad=NULL;
      }
    }
    //rysuje
    Graphics::TBitmap* rysunek=new Graphics::TBitmap();
    rysunek->Height=40;
    rysunek->Width=poz;
    rysunek->Canvas->Brush->Color=KolorPodglad;
    rysunek->Canvas->Pen->Color=KolorPodglad;
    rysunek->Canvas->Rectangle(0,0,rysunek->Width,rysunek->Height);
    poz=0;
    nr=Stacja.NrPunktu(Pociag);
    for(int i=0;i<DLUGOSC_POSTOJOWYCH;i++)
    {
      int nazwa=Stacja.NazwaNr(nr,i);
      if(nazwa<=0 ) break;
      if(Stacja.RodzajSkladu(nr,i)>2)
      {
        if(KolorPodglad!=clWhite)
        {
          Tabor[nazwa]->Transparent=true;
          Tabor[nazwa]->TransparentColor=clWhite;
          rysunek->Canvas->Draw(poz,0,Tabor[nazwa]);
          Tabor[nazwa]->Transparent=false;
        }
        else
          rysunek->Canvas->Draw(poz,0,Tabor[nazwa]);
        poz+=Tabor[nazwa]->Width;
        if(!Stacja.CzyPolaczony(nr,i))
          poz+=10;
      }
      else
      {
        char* napis;
        sklad=Stacja.Podglad(nr,i);
        for(int u=0;sklad[u];)
        {
          for(int il=sklad[u];il>0;il--)
          {
            if(KolorPodglad!=clWhite)
            {
              Tabor[sklad[u+1]]->Transparent=true;
              Tabor[sklad[u+1]]->TransparentColor=clWhite;
              rysunek->Canvas->Draw(poz,0,Tabor[sklad[u+1]]);
              Tabor[sklad[u+1]]->Transparent=false;
            }
            else
              rysunek->Canvas->Draw(poz,0,Tabor[sklad[u+1]]);
            poz+=Tabor[sklad[u+1]]->Width;
          }
          u+=2;
        }
        if(!Stacja.CzyPolaczony(nr,i))
          poz+=10;
        delete [] sklad;
        sklad=NULL;
      }
    }
    FPodgladSkladu->Width=FGlowna->Width-5;
    FPodgladSkladu->IPodglad->Width=rysunek->Width;
    FPodgladSkladu->IPodglad->Picture->Assign(rysunek);
    FPodgladSkladu->Color=KolorPodglad;
    delete rysunek;
    FPodgladSkladu->SBTlo->HorzScrollBar->Position=0;
    FPodgladSkladu->ShowModal();
    if(!Pauza && !PauzaZaznaczanie)
      Timer->Enabled=true;
  }
  else if(Key>48 && Key<=57)
  {
    int nr=Key-48;
    int w=Stacja.WspWjazdu(nr);
    if(w>-1)
    {
      Timer->Enabled=false;
      FMijanka->Wspolrzedne=w;
      FMijanka->Numer=nr;
      FMijanka->PNapis->Visible=false;
      FMijanka->BCzekaj->Visible=false;
      FMijanka->ECzekaj->Visible=false;
      FMijanka->Label1->Visible=false;
      FMijanka->Caption="Informacja o odcinku";
      FMijanka->BZezwalam->Caption="OK";
      FMijanka->ShowModal();
      if(!Pauza)
        Timer->Enabled=true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::PBPociagMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if(PelneOkno==false)
  {
    PelneOkno=true;
    Zmiana();
  }

  //Wyswietlanie odpowiedniego dymka

  if(!(Y>0 && Y<40))
  {
    Dymek->ReleaseHandle();
    return;
  }
  int i;
  for(i=0;i<10;i++)
  {
    if(Wagony[i][0]<X && Wagony[i][1]>X) break;
  }
  if(i==10)
  {
    Dymek->ReleaseHandle();
    return;
  }
  POINT Punkt;
  String tekst1,tekst2;
  ::GetCursorPos(&Punkt);

  int nr=Stacja.NrPunktu(Pociag);
  if(nr==-1) return;
  int p=Stacja.NrRozklad(nr,i);
  char* napis;
  if(Stacja.RodzajSkladu(nr,i)>=3)
  {//lokomotywa
    napis=Stacja.NumerLoka(nr,i);
    tekst1=String(Stacja.Nazwa(nr,i));
    tekst2=String(napis);
    delete [] napis;
  }
  else
  {//jednostka nierozlaczalna i sklad
    int czesc;
    if(Stacja.CzyZjechac(nr,i))
    {
      if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
      {
           tekst1=String("P: ")+Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD));
           czesc=Stacja.NumerCzesci(p,PRZYJAZD);
      }
      else
      {
        tekst1=String("P: ")+Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,ODJAZD));
        czesc=Stacja.NumerCzesci(p,ODJAZD);
      }
    }
    else
    {
      tekst1=String("P: ")+Stacja.Peron(Stacja.Peron(p,NIEOKRESLONA,PRZYJAZD));
      czesc=Stacja.NumerCzesci(p,PRZYJAZD);
    }
    if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           napis=Stacja.Numer(p,NIEOKRESLONA,PRZYJAZD);
    else
      napis=Stacja.Numer(p,NIEOKRESLONA,ODJAZD);
    tekst1=tekst1+"  Nr: "+napis;
    delete[] napis;
    if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           tekst1=tekst1+"  W: "+Stacja.Wjazd(p,NIEOKRESLONA);
    else
      tekst1=tekst1+"  W: "+Stacja.Wyjazd(p,NIEOKRESLONA);
    if((Stacja.CzyPunkt(Pociag)==WJAZD || Stacja.CzyPunkt(Pociag)==WJAZD_WYJAZD)
           &&(FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==WJEZDZA || FGlowna->Stacja.StanPociagu(p,NIEOKRESLONA)==JEST))
           napis=Stacja.GodzinaRzeczywista(p,NIEOKRESLONA,PRZYJAZD);
    else
      napis=Stacja.GodzinaRzeczywista(p,NIEOKRESLONA,ODJAZD);
    tekst1=tekst1+"  Godz: "+napis;
    delete[] napis;
    napis=Stacja.Skad(p,NIEOKRESLONA);
    tekst2=napis+String(" - ");
    delete[] napis;
    napis=Stacja.Dokad(p,NIEOKRESLONA);
    tekst2=tekst2+napis;
    delete[] napis;
    if(czesc)
      tekst1=tekst1+" ("+String(czesc)+")";
  }

  int d=(Dymek->CalcHintRect(1000,tekst1,0).Right<Dymek->CalcHintRect(1000,tekst2,0).Right)?Dymek->CalcHintRect(1000,tekst2,0).Right:Dymek->CalcHintRect(1000,tekst1,0).Right;
  TRect Obszar=Rect(Punkt.x+10,Punkt.y+20,Punkt.x+d+10,Punkt.y+50);
  Dymek->ActivateHint(Obszar,tekst1+'\n'+tekst2);

}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::PBStacjaMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if(PelneOkno==true)
  {
    PelneOkno=false;
    Zmiana();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::Zmiana(void)
{
  if(Pociag && !StalyRozmiar)
  {
    if(PelneOkno && Stacja.CzyStoiPociag(Pociag))
    {
      POINT Punkt;
      ::GetCursorPos(&Punkt);
      Punkt.x-=153;
      ::SetCursorPos(Punkt.x,Punkt.y);
      PBPrzyjazdy->Width=0;
      PBOdjazdy->Width=0;
      Dymek->ReleaseHandle();
    }
    else
    {
      PBPrzyjazdy->Width=153;
      PBOdjazdy->Width=153;
      Dymek->ReleaseHandle();
    }
  }
  else
    Dymek->ReleaseHandle();
  RysujPociag(this);
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::PBOdjazdyPaint(TObject *Sender)
{
  WypiszRozklad(this);
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  Timer->Enabled=false;
  if(Application->MessageBox("Chcesz zakoñczyæ grê?","Koniec gry",MB_YESNO)==IDNO)
  {
    CanClose=false;
    Timer->Enabled=true;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFGlowna::OUstawieniaClick(TObject *Sender)
{
  Timer->Enabled=false;
  FOpcje->PageControl->ActivePageIndex=2;
  FOpcje->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::FormActivate(TObject *Sender)
{
  PlikINI=new TIniFile(Sciezka+"\\kolejarz.ini");

  Timer->Interval=PlikINI->ReadInteger("Zegar","Interval",0);
  FOpcje->CBCzasRzeczywisty->Checked=PlikINI->ReadBool("Zegar","Czas_rzeczywisty",FOpcje->CBCzasRzeczywisty->Checked);

  Stacja.Wyprzedzenie(PlikINI->ReadInteger("Opoznienia","Wyprzedzenie",Stacja.Wyprzedzenie()));
  Stacja.PlusMinus(0,0,PlikINI->ReadInteger("Opoznienia","Podmiejski-",Stacja.PlusMinus(0,0)));
  Stacja.PlusMinus(0,1,PlikINI->ReadInteger("Opoznienia","Podmiejski+",Stacja.PlusMinus(0,1)));
  Stacja.PlusMinus(1,0,PlikINI->ReadInteger("Opoznienia","Osobowy-",Stacja.PlusMinus(1,0)));
  Stacja.PlusMinus(1,1,PlikINI->ReadInteger("Opoznienia","Osobowy+",Stacja.PlusMinus(1,1)));
  Stacja.PlusMinus(2,0,PlikINI->ReadInteger("Opoznienia","Pospieszny-",Stacja.PlusMinus(2,0)));
  Stacja.PlusMinus(2,1,PlikINI->ReadInteger("Opoznienia","Pospieszny+",Stacja.PlusMinus(2,1)));
  Stacja.PlusMinus(3,0,PlikINI->ReadInteger("Opoznienia","Expres-",Stacja.PlusMinus(3,0)));
  Stacja.PlusMinus(3,1,PlikINI->ReadInteger("Opoznienia","Expres+",Stacja.PlusMinus(3,1)));
  Stacja.PlusMinus(4,0,PlikINI->ReadInteger("Opoznienia","Towarowy-",Stacja.PlusMinus(4,0)));
  Stacja.PlusMinus(4,1,PlikINI->ReadInteger("Opoznienia","Towarowy+",Stacja.PlusMinus(4,1)));
  Stacja.PlusMinus(5,0,PlikINI->ReadInteger("Opoznienia","Specjalny-",Stacja.PlusMinus(5,0)));
  Stacja.PlusMinus(5,1,PlikINI->ReadInteger("Opoznienia","Specjalny+",Stacja.PlusMinus(5,1)));

  PauzaZaznaczanie=PlikINI->ReadBool("Opcje","Pauza_zaznaczanie",PauzaZaznaczanie);
  PauzaPodglad=PlikINI->ReadBool("Opcje","Pauza_podglad",PauzaPodglad);
  PauzaNieaktywne=PlikINI->ReadBool("Opcje","Pauza_nieaktywne",PauzaNieaktywne);
  IloscWyswietlanychPociagow=PlikINI->ReadInteger("Opcje","Rozklad_pierwszych",IloscWyswietlanychPociagow);
  StalyRozmiar=PlikINI->ReadBool("Opcje","Staly_rozmiar",StalyRozmiar);

  KolorTlo=PlikINI->ReadBool("Kolor","Tlo",KolorTlo);
  KolorSchemat=PlikINI->ReadInteger("Kolor","Schemat_stacji",KolorSchemat);
  KolorPrzyjazdy=PlikINI->ReadInteger("Kolor","Przyjazdy",KolorPrzyjazdy);
  KolorOdjazdy=PlikINI->ReadInteger("Kolor","Odjazdy",KolorOdjazdy);
  KolorPodglad=PlikINI->ReadInteger("Kolor","Podglad_skladow",KolorPodglad);

  Dzwieki=PlikINI->ReadBool("Dzwieki","Dzwiek",Dzwieki);
  NowyPociag=PlikINI->ReadBool("Dzwieki","Nowy_pociag",NowyPociag);
  NowyPociagPlik=PlikINI->ReadString("Dzwieki","Nowy_pociag_plik",NowyPociagPlik);
  Blad=PlikINI->ReadBool("Dzwieki","Blad",Blad);
  BladPlik=PlikINI->ReadString("Dzwieki","Blad_plik",BladPlik);
  Mijanka=PlikINI->ReadBool("Dzwieki","Mijanka",Mijanka);
  MijankaPlik=PlikINI->ReadString("Dzwieki","Mijanka_plik",MijankaPlik);
  Odjazd=PlikINI->ReadBool("Dzwieki","Odjazd",Odjazd);
  OdjazdPlik=PlikINI->ReadString("Dzwieki","Odjazd_plik",OdjazdPlik);
  PktKarne=PlikINI->ReadBool("Dzwieki","Pkt_karne",PktKarne);
  PktKarnePlik=PlikINI->ReadString("Dzwieki","Pkt_karne_plik",PktKarnePlik);
  Opoznienie=PlikINI->ReadBool("Dzwieki","Opoznienie",Opoznienie);
  OpoznieniePlik=PlikINI->ReadString("Dzwieki","Opoznienie_plik",OpoznieniePlik);

  WczytajDzwieki();
  /*if(Dzwieki)
  {
    if(NowyPociag)
    {
      MPNowyPociag->Close();
      MPNowyPociag->FileName=NowyPociagPlik;
      try
      {
        MPNowyPociag->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Nowy poci¹g na wjeŸdzie.","B³¹d odczytu",MB_OK);
        NowyPociag=false;
      }
    }
    if(Blad)
    {
      MPBlad->Close();
      MPBlad->FileName=BladPlik;
      try
      {
        MPBlad->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Niedozwolona operacja.","B³¹d odczytu",MB_OK);
        Blad=false;
      }
    }
    if(Mijanka)
    {
      MPMijanka->Close();
      MPMijanka->FileName=MijankaPlik;
      try
      {
        MPMijanka->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Poci¹g czeka na mijance.","B³¹d odczytu",MB_OK);
        Mijanka=false;
      }
    }
    if(Odjazd)
    {
      MPOdjazd->Close();
      MPOdjazd->FileName=OdjazdPlik;
      try
      {
        MPOdjazd->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Poci¹g opóŸniony na peronie.","B³¹d odczytu",MB_OK);
        Odjazd=false;
      }
    }
    if(PktKarne)
    {
      MPPktKarne->Close();
      MPPktKarne->FileName=PktKarnePlik;
      try
      {
        MPPktKarne->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Naliczanie punktów karnych.","B³¹d odczytu",MB_OK);
        PktKarne=false;
      }
    }
    if(Opoznienie)
    {
      MPOpoznienie->Close();
      MPOpoznienie->FileName=OpoznieniePlik;
      try
      {
        MPOpoznienie->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Losowanie opóŸnienia pociagu.","B³¹d odczytu",MB_OK);
        Opoznienie=false;
      }
    }
  }
  if(!NowyPociag && !Blad && !Mijanka && !Odjazd && !PktKarne && !Opoznienie)
    Dzwieki=false;
  SetCurrentDir(Sciezka);*/
  if(KolorSchemat==clBlack && KolorPrzyjazdy==clBlack && KolorOdjazdy==clBlack && KolorPodglad==clBlack)
    KolorSchemat=KolorPrzyjazdy=KolorOdjazdy=KolorPodglad=clWhite;
  WczytajTory();
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::ll1Click(TObject *Sender)
{
  Zapiszstangry1Click(this);
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::OnHint(TObject *Sender)
{
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::FormCreate(TObject *Sender)
{
  Application->OnHint=OnHint;
}
//---------------------------------------------------------------------------


void __fastcall TFGlowna::FormShow(TObject *Sender)
{
  Wysokosc=Height;
  Szerokosc=Width>800?800:Width;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::DostosujWielkoscOkna(void)
{
  Width=Szerokosc;
  PBStacja->Height=Stacja.Wysokosc()*14;
  StatusBar->Panels->Items[0]->Width=PBPrzyjazdy->Width;
  StatusBar->Panels->Items[1]->Width=PBPociag->Width;  
//  Height=10*14+PBStacja->Height; 
}
//---------------------------------------------------------------------------   
void __fastcall TFGlowna::MUwagiClick(TObject *Sender)
{
  FUwagi->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::MWjazdWyjazdClick(TObject *Sender)
{
  Timer->Enabled=false;
  FWjazdWyjazd->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------



void __fastcall TFGlowna::OUKoloryClick(TObject *Sender)
{
  Timer->Enabled=false;
  FOpcje->PageControl->ActivePageIndex=3;
  FOpcje->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::PBPrzyjazdyMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if(PelneOkno==true)
  {
    PelneOkno=false;
    Zmiana();
  }        
}
//---------------------------------------------------------------------------

void __fastcall TFGlowna::PBOdjazdyMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if(PelneOkno==true)
  {
    PelneOkno=false;
    Zmiana();
  }        
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::WczytajTory(bool poczatek)
{
  if(!poczatek)
  {
    Tory->Clear();
  }
  //wczytanie torow do pamieci
  for(int i=0;i<ILOSC_TOROW-100;i++)
  {
    int a=(i+100)/10;
    int b=i+100-a*10;
    Graphics::TBitmap *bitmap =new Graphics::TBitmap();
    Graphics::TBitmap *btmap =new Graphics::TBitmap();
    bitmap->Height=14;
    bitmap->Width=14;
    btmap->Height=14;
    btmap->Width=14;
    String s="TOR";
    s+=i+100;
    if(!(b==0 || b==9))
      bitmap->LoadFromResourceName((int)HInstance,s);
    btmap->Canvas->Brush->Color=KolorSchemat;
    btmap->Canvas->Pen->Color=KolorSchemat;
    btmap->Canvas->Rectangle(0,0,14,14);
    bitmap->Transparent=true;
    if((i/10)==43)
      bitmap->TransparentColor=bitmap->Canvas->Pixels[0][0];
    else
      bitmap->TransparentColor=clWhite;
    btmap->Canvas->Draw(0,0,bitmap);
    bitmap->Transparent=false;
    Tory->Add(btmap,NULL);
    delete bitmap;
    delete btmap;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::OUDzwiekiClick(TObject *Sender)
{
  Timer->Enabled=false;
  FOpcje->PageControl->ActivePageIndex=4;
  FOpcje->ShowModal();
  if(!Pauza)
    Timer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFGlowna::WczytajDzwieki(void)
{
  if(Dzwieki)
  {
    if(NowyPociag)
    {
      MPNowyPociag->Close();
      MPNowyPociag->FileName=NowyPociagPlik;
      try
      {
        MPNowyPociag->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Nowy poci¹g na wjeŸdzie.","B³¹d odczytu",MB_OK);
        NowyPociag=false;
      }
    }
    if(Blad)
    {
      MPBlad->Close();
      MPBlad->FileName=BladPlik;
      try
      {
        MPBlad->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Niedozwolona operacja.","B³¹d odczytu",MB_OK);
        Blad=false;
      }
    }
    if(Mijanka)
    {
      MPMijanka->Close();
      MPMijanka->FileName=MijankaPlik;
      try
      {
        MPMijanka->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Poci¹g czeka na mijance.","B³¹d odczytu",MB_OK);
        Mijanka=false;
      }
    }
    if(Odjazd)
    {
      MPOdjazd->Close();
      MPOdjazd->FileName=OdjazdPlik;
      try
      {
        MPOdjazd->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Poci¹g opóŸniony na peronie.","B³¹d odczytu",MB_OK);
        Odjazd=false;
      }
    }
    if(PktKarne)
    {
      MPPktKarne->Close();
      MPPktKarne->FileName=PktKarnePlik;
      try
      {
        MPPktKarne->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Naliczanie punktów karnych.","B³¹d odczytu",MB_OK);
        PktKarne=false;
      }
    }
    if(Opoznienie)
    {
      MPOpoznienie->Close();
      MPOpoznienie->FileName=OpoznieniePlik;
      try
      {
        MPOpoznienie->Open();
      }
      catch(...)
      {
        Application->MessageBox("B³¹d odczytu pliku dŸwiêkowego dla zdarzenia - Losowanie opóŸnienia pociagu.","B³¹d odczytu",MB_OK);
        Opoznienie=false;
      }
    }
  }
  if(!NowyPociag && !Blad && !Mijanka && !Odjazd && !PktKarne && !Opoznienie)
    Dzwieki=false;
  SetCurrentDir(Sciezka);
}
//---------------------------------------------------------------------------
