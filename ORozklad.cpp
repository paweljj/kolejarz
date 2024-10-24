//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ORozklad.h"
#include "FKolejarz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRozklad *FRozklad;
//---------------------------------------------------------------------------
__fastcall TFRozklad::TFRozklad(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFRozklad::FormPaint(TObject *Sender)
{
  int ilosc=FGlowna->IloscWyswietlanychPociagow;
  if(ilosc>FGlowna->Stacja.IloscPociagow()) ilosc=0;
  if(!ilosc) ilosc=FGlowna->Stacja.IloscPociagow();
  int dlugosc=ilosc+1;
  dlugosc+=FGlowna->Stacja.IloscPociagowWTrakcjiPodwojnej(rodzaj,ilosc);
  dlugosc*=20;
  Graphics::TBitmap * bitmap= new Graphics::TBitmap();
  bitmap->Width=ITabela->Width;
  if(dlugosc>20)
    bitmap->Height=dlugosc;
  else
  {
    dlugosc=ITabela->Height;
    bitmap->Height=ITabela->Height;
  }
  bitmap->Canvas->Font->Size=10;
//  bitmap->PixelFormat=pf8bit;
  if(rodzaj==PRZYJAZD)
  {
    bitmap->Canvas->Brush->Color=FGlowna->KolorPrzyjazdy;
    bitmap->Canvas->Pen->Color=FGlowna->KolorPrzyjazdy;
    bitmap->Canvas->Rectangle(0,0,bitmap->Width,bitmap->Height);
    FRozklad->Color=FGlowna->KolorPrzyjazdy;
    bitmap->Canvas->Pen->Color=clBlack;
    bitmap->Canvas->TextOut(0,0,"Wj.");
    bitmap->Canvas->MoveTo(18,0);
    bitmap->Canvas->LineTo(18,dlugosc);
    bitmap->Canvas->TextOut(20,0,"Godz.");
    bitmap->Canvas->MoveTo(60,0);
    bitmap->Canvas->LineTo(60,dlugosc);
    bitmap->Canvas->TextOut(70,0,"+/-");
    bitmap->Canvas->MoveTo(100,0);
    bitmap->Canvas->LineTo(100,dlugosc);
    bitmap->Canvas->TextOut(101,0,"Pr.");
    bitmap->Canvas->MoveTo(122,0);
    bitmap->Canvas->LineTo(122,dlugosc);
    bitmap->Canvas->TextOut(123,0,"Rodz.");
    bitmap->Canvas->MoveTo(158,0);
    bitmap->Canvas->LineTo(158,dlugosc);
    bitmap->Canvas->TextOut(160,0,"Numer");
    bitmap->Canvas->MoveTo(210,0);
    bitmap->Canvas->LineTo(210,dlugosc);
    bitmap->Canvas->TextOut(212,0,"Nazwa");
    bitmap->Canvas->MoveTo(350,0);
    bitmap->Canvas->LineTo(350,dlugosc);
    bitmap->Canvas->TextOut(360,0,"Relacja");
    bitmap->Canvas->MoveTo(630,0);
    bitmap->Canvas->LineTo(630,dlugosc);
    bitmap->Canvas->TextOut(632,0,"Godz.");
    bitmap->Canvas->MoveTo(670,0);
    bitmap->Canvas->LineTo(670,dlugosc);
    bitmap->Canvas->TextOut(672,0,"W");
    bitmap->Canvas->MoveTo(688,0);
    bitmap->Canvas->LineTo(688,dlugosc);
    bitmap->Canvas->TextOut(690,0,"Lok.");

    bitmap->Canvas->MoveTo(0,20);
    bitmap->Canvas->LineTo(bitmap->Width,20);

    int licznik=0;
    for(int i=0;i<ilosc;i++)
    {
      if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==BEDZIE ||
        (/*FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==JEST ||*/
         FGlowna->Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ZE_STACJI ||
         FGlowna->Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_ZE_STACJI_LACZONY))
      {
        licznik++;
        bitmap->Canvas->Font->Color=clBlack;
      }
      else if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==JEST || FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==CZEKA_NA_WYJAZD)
      {
        licznik++;
        bitmap->Canvas->Font->Color=clBlue;
      }
      else if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==CZEKA_NA_WJAZD)
      {
        licznik++;
        bitmap->Canvas->Font->Color=clRed;
      }
      else if(FGlowna->Stacja.StanPociagu(i,PRZYJAZD)==WJEZDZA)
      {
        licznik++;
        bitmap->Canvas->Font->Color=clGreen;
      }
      else
        continue;
      if(FGlowna->Stacja.TypPociagu(i,PRZYJAZD)==POCIAG_BEZ_ZATRZYMANIA)
        bitmap->Canvas->Font->Style=TFontStyles()<<fsItalic;
      else
        bitmap->Canvas->Font->Style=TFontStyles();
      int poz=licznik*20+5;
      String s;
      s=FGlowna->Stacja.Wjazd(i,PRZYJAZD);
      bitmap->Canvas->TextOutA(1,poz,s);
      char* napis=FGlowna->Stacja.Godzina(i,PRZYJAZD,PRZYJAZD);
      bitmap->Canvas->TextOutA(20,poz,napis);
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
      bitmap->Canvas->TextOutA(62,poz,s);
      bitmap->Canvas->TextOutA(103,poz,FGlowna->Stacja.Peron(FGlowna->Stacja.Peron(i,PRZYJAZD,PRZYJAZD)));
      napis=FGlowna->Stacja.Rodzaj(i,PRZYJAZD);
      bitmap->Canvas->TextOutA(124,poz,napis);
      napis=FGlowna->Stacja.Numer(i,PRZYJAZD,PRZYJAZD);
      bitmap->Canvas->TextOutA(160,poz,napis);
      delete[] napis;
      napis=FGlowna->Stacja.NazwaPociagu(i,PRZYJAZD,PRZYJAZD);
      bitmap->Canvas->TextOutA(212,poz,napis);
      delete[] napis;
      if(FGlowna->Stacja.TypPociagu(i,PRZYJAZD)!=POWROT_LOKA)
      {
        napis=FGlowna->Stacja.Skad(i,PRZYJAZD);
        bitmap->Canvas->TextOutA(352,poz,napis);
        delete[] napis;
        napis=FGlowna->Stacja.Dokad(i,PRZYJAZD);
        bitmap->Canvas->TextOutA(490,poz,napis);
        delete[] napis;
        napis=FGlowna->Stacja.Godzina(i,PRZYJAZD,ODJAZD);
        bitmap->Canvas->TextOutA(632,poz,napis);
        delete[] napis;
        s=FGlowna->Stacja.Wyjazd(i,PRZYJAZD);
        bitmap->Canvas->TextOutA(672,poz,s);
      }
      int t=FGlowna->Stacja.TypPociagu(i,PRZYJAZD);
      if(t!=POCIAG_ROZLACZANY && t!=POCIAG_DOCELOWY_ROZLACZANY && t!=POCIAG_ZE_STACJI_LACZONY)
      {
        napis=FGlowna->Stacja.Lok(i,PRZYJAZD);
        if(FGlowna->Stacja.CzyZmianaLoka(i,PRZYJAZD))
          bitmap->Canvas->Font->Color=clGreen;
        else
          bitmap->Canvas->Font->Color=clBlack;
        if(napis && strchr(napis,'|')/*strlen(napis)>8*/)
        {
          licznik++;
          char* t=strtok(napis,"|");
          bitmap->Canvas->TextOutA(690,poz,t);
          t=strtok(NULL,"|");
          bitmap->Canvas->TextOutA(690,poz+20,t);
          delete [] napis;
          napis=FGlowna->Stacja.Szopa(i,PRZYJAZD);
          t=strtok(napis,"|");
          bitmap->Canvas->TextOutA(730,poz,t);
          t=strtok(NULL,"|");
          bitmap->Canvas->TextOutA(730,poz+20,t);
          delete [] napis;
        }
        else
        {
          bitmap->Canvas->TextOutA(690,poz,napis);
          delete[] napis;
          napis=FGlowna->Stacja.Szopa(i,PRZYJAZD);
          bitmap->Canvas->TextOutA(730,poz,napis);
          delete[] napis;
        }
      }
    }
  }
  else
  {
    bitmap->Canvas->Brush->Color=FGlowna->KolorOdjazdy;
    bitmap->Canvas->Pen->Color=FGlowna->KolorOdjazdy;
    bitmap->Canvas->Rectangle(0,0,bitmap->Width,bitmap->Height);
    FRozklad->Color=FGlowna->KolorOdjazdy;
    bitmap->Canvas->Pen->Color=clBlack;
    bitmap->Canvas->TextOut(0,0,"W.");
    bitmap->Canvas->MoveTo(20,0);
    bitmap->Canvas->LineTo(20,dlugosc);
    bitmap->Canvas->TextOut(22,0,"Godz.");
    bitmap->Canvas->MoveTo(60,0);
    bitmap->Canvas->LineTo(60,dlugosc);
    bitmap->Canvas->TextOut(65,0,"+/-");
    bitmap->Canvas->MoveTo(100,0);
    bitmap->Canvas->LineTo(100,dlugosc);
    bitmap->Canvas->TextOut(101,0,"Pr.");
    bitmap->Canvas->MoveTo(122,0);
    bitmap->Canvas->LineTo(122,dlugosc);
    bitmap->Canvas->TextOut(123,0,"Rodz.");
    bitmap->Canvas->MoveTo(158,0);
    bitmap->Canvas->LineTo(158,dlugosc);
    bitmap->Canvas->TextOut(160,0,"Numer");
    bitmap->Canvas->MoveTo(210,0);
    bitmap->Canvas->LineTo(210,dlugosc);
    bitmap->Canvas->TextOut(212,0,"Nazwa");
    bitmap->Canvas->MoveTo(350,0);
    bitmap->Canvas->LineTo(350,dlugosc);
    bitmap->Canvas->TextOut(360,0,"Relacja");
    bitmap->Canvas->MoveTo(630,0);
    bitmap->Canvas->LineTo(630,dlugosc);
    bitmap->Canvas->TextOut(632,0,"Lok.");

    bitmap->Canvas->MoveTo(0,20);
    bitmap->Canvas->LineTo(Width,20);

    int licznik=0;
    for(int i=0;i<ilosc;i++)
    {
      int aaaaaaaa=FGlowna->Stacja.TypPociagu(i,ODJAZD);
      if(FGlowna->Stacja.TypPociagu(i,ODJAZD)==POWROT_LOKA)
        continue;
      else if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==JEST)
      {
        licznik++;
        bitmap->Canvas->Font->Color=clBlue;
      }
      else if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==BEDZIE || FGlowna->Stacja.StanPociagu(i,ODJAZD)==CZEKA_NA_WJAZD
              || FGlowna->Stacja.StanPociagu(i,ODJAZD)==WJEZDZA)
      {
        licznik++;
        bitmap->Canvas->Font->Color=clBlack;
      }
      else if(FGlowna->Stacja.StanPociagu(i,ODJAZD)==CZEKA_NA_WYJAZD)
      {
        licznik++;
        bitmap->Canvas->Font->Color=clRed;
      }
      else
        continue;
      if(FGlowna->Stacja.TypPociagu(i,ODJAZD)==POCIAG_BEZ_ZATRZYMANIA)
        bitmap->Canvas->Font->Style=TFontStyles()<<fsItalic;
      else
        bitmap->Canvas->Font->Style=TFontStyles();
      int poz=licznik*20+5;
      String s;
      s=FGlowna->Stacja.Wyjazd(i,ODJAZD);
      bitmap->Canvas->TextOutA(1,poz,s);
      char* napis=FGlowna->Stacja.Godzina(i,ODJAZD,ODJAZD);
      bitmap->Canvas->TextOutA(22,poz,napis);
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
      bitmap->Canvas->TextOutA(62,poz,s);
      bitmap->Canvas->TextOutA(102,poz,FGlowna->Stacja.Peron(FGlowna->Stacja.Peron(i,ODJAZD,ODJAZD)));
      napis=FGlowna->Stacja.Rodzaj(i,ODJAZD);
      bitmap->Canvas->TextOutA(124,poz,napis);
      napis=FGlowna->Stacja.Numer(i,ODJAZD,ODJAZD);
      bitmap->Canvas->TextOutA(160,poz,napis);
      delete[] napis;
      napis=FGlowna->Stacja.NazwaPociagu(i,ODJAZD,ODJAZD);
      bitmap->Canvas->TextOutA(212,poz,napis);
      delete[] napis;
      napis=FGlowna->Stacja.Skad(i,ODJAZD);
      bitmap->Canvas->TextOutA(352,poz,napis);
      delete[] napis;
      napis=FGlowna->Stacja.Dokad(i,ODJAZD);
      bitmap->Canvas->TextOutA(490,poz,napis);
      delete[] napis;
      int t=FGlowna->Stacja.CzyLaczenie(i,ODJAZD);
      t=t-t/10*10;
      if(t==0 || t==1)
      {
        napis=FGlowna->Stacja.Lok(i,ODJAZD);
        if(FGlowna->Stacja.CzyZmianaLoka(i,ODJAZD))
          bitmap->Canvas->Font->Color=clGreen;
        else
          bitmap->Canvas->Font->Color=clBlack;
        if(napis && strchr(napis,'|')/*strlen(napis)>8*/)
        {
          licznik++;
          char* t=strtok(napis,"|");
          bitmap->Canvas->TextOutA(632,poz,t);
          t=strtok(NULL,"|");
          bitmap->Canvas->TextOutA(632,poz+20,t);
          delete [] napis;
          napis=FGlowna->Stacja.Szopa(i,ODJAZD);
          t=strtok(napis,"|");
          bitmap->Canvas->TextOutA(678,poz,t);
          t=strtok(NULL,"|");
          bitmap->Canvas->TextOutA(678,poz+20,t);
          delete [] napis;
        }
        else
        {
          bitmap->Canvas->TextOutA(632,poz,napis);
          delete[] napis;
          napis=FGlowna->Stacja.Szopa(i,ODJAZD);
          bitmap->Canvas->TextOutA(678,poz,napis);
          delete[] napis;
        }
      }
    }
  }
//  bitmap->SaveToFile("rozklad.bmp");
  ITabela->Height=bitmap->Height;
  ITabela->Picture->Assign(bitmap);
  delete bitmap;
}
//---------------------------------------------------------------------------

void __fastcall TFRozklad::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key==VK_UP)
    SBTlo->VertScrollBar->Position-=20;
  else if(Key==VK_DOWN)
    SBTlo->VertScrollBar->Position+=20;
  else if(Key==VK_SPACE || Key==VK_ESCAPE)
    Close();
  else if(Key==VK_LEFT)
    SBTlo->HorzScrollBar->Position=0;
  else if(Key==VK_RIGHT)
    SBTlo->HorzScrollBar->Position+=65;
  else if(Key==68)
    ITabela->Picture->SaveToFile(FGlowna->Sciezka+'\\'+FRozklad->Caption+".bmp");
}
//---------------------------------------------------------------------------

void __fastcall TFRozklad::FormShow(TObject *Sender)
{
  if(FGlowna->Width>850)
    Width=890;
}
//---------------------------------------------------------------------------

