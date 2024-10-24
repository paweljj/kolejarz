#include "Stacja.h"

tStacja::tStacja()
{
  ilosc_postojowych=szerokosc=wysokosc=ilosc_tras=dlugosc_bocznic=0;
}

void tStacja::Aktualizuj(void)
{
  int i;
  for(i=0;i<ilosc_postojowych && pkt_postojowe[i][0]!=LOKOWNIA;i++);
  if(i<ilosc_postojowych && stan_postojowych[i][0].Rodzaj()!=PUSTY)
  {
    stan[pkt_postojowe[i][2]/100][pkt_postojowe[i][2]%100]=POLE_ZAJETE;
    Lokomotywownia.MoznaWystawic(NIE);
  }
  else
    Lokomotywownia.MoznaWystawic(TAK);
  Lokomotywownia.Aktualizuj();
}

/* ================================================================== *
 * Funkcja Anuluj
 * ------------------------------------------------------------------
 * Przeznaczenie:
 * Pomocnicza dla Zaznacz.
 * Anuluje zaznaczania tras. Funkcja ta nie powinna byc wywolywana
 * bezposrednio; nalezy wywolywac funkcje Zaznacz bez zadnego parametru.
 * ------------------------------------------------------------------
 * Mozliwe wywolania i zwracane wartosci:
 *   Anuluj() - powoduje anulowanie tras
 *     Zawsze zwraca OK (?)
 *
 * ------------------------------------------------------------------
 * Data ostatniej modyfikacji: 2 lipca 2001
 * Wersja: 1.PF
 * ================================================================== */
int tStacja::Anuluj(void)
{
  int i,j;

  for(i=0;i<wysokosc;i++)
  for(j=0;j<szerokosc;j++)
  {
    if(stan[i][j]==WYBOR_TRASY)
      stan[i][j]=POLE_WOLNE;
  }

  return OK;
}

/*******************************************************************************
 *** Funkcja podaje poczatek lub koniec bocznicy                             ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   wsp - wspolrzedne bocznicy                                            ***
 ***   rodzaj - poczatek/koniec                                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   poczatek/koniec bocznicy                                              ***
 ***                                                                         ***
 *** Wersja 0.01                                                             ***
 *** Data ostatniej modyfikacji: 26.07.2001                                  ***
 *******************************************************************************/
int tStacja::Bocznica(int wsp, int rodzaj)
{
  int poz=NrPunktu(wsp);
  if(rodzaj==POCZATEK_BOCZNICY)
    return pkt_postojowe[poz][5]+ilosc_postojowych;
  else
    return pkt_postojowe[poz][5]+ilosc_postojowych+pkt_postojowe[poz][1]-1;
}

/*******************************************************************************
 *** Funkcja zarzadza punktami posrednimi miedzy mijanka a stacja.           ***
 *** Zmniejsza czasy dojazdu miedzy punktami i przepisuje pociagi.           ***
 ***                                                                         ***
 *** Wersja 0.06                                                             ***
 *** Data ostatniej modyfikacji: 23.01.2005                                  ***
 *******************************************************************************/
void tStacja::CzasMijanki(void)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    if(mijanka[i][ROZMIAR_MIJANKI]!=WOLNA_MIJANKA)
    {
      for(int p=0;p<ROZMIAR_MIJANKI;p+=3)
      {
        if(mijanka[i][p+1]>1)
          mijanka[i][p+1]-=1;
        else if(mijanka[i][p+1]==1)
        {// mamy pociag do przepisania
          if(mijanka[i][ROZMIAR_MIJANKI]==WJEZDZA && !p && !CzyStoiPociag(pkt_postojowe[i][2]))
          {//trzeba stworzyc pociag na punkcie wjazdowym
            bool powrot=false;
            int lok=TworzPociag(mijanka[i][p],i);
            if(lok<0/*lok==-1*/)
            {
              lok=0;
              powrot=true;
            }
            int poz=i;
            int r=mijanka[i][p];
            int jednostka=Zegar.Jednostka();
            stan_postojowych[poz][lok].Czas((pkt_postojowe[poz][1]/100)*60/jednostka);
            if (!stan_postojowych[poz][lok].Czas())
              stan_postojowych[poz][lok].Czas(1); //zabazpieczenie dla wjazdow bez okreslonego wyprzedzenia
            if(!powrot)
              Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Rozklad.DodajCzas(Zegar.Godzina(),Wyprzedz(i,true)));
//            mijanka[i][ROZMIAR_MIJANKI]=WOLNA_MIJANKA;
            mijanka[i][p]=mijanka[i][p+1]=0;
          }
          else if(mijanka[i][ROZMIAR_MIJANKI]==WJEZDZA && p)
          {//trzeba przepisac pociag w lewo
            if(!mijanka[i][p-2])
            {//mamy wolne miejsce
              mijanka[i][p-3]=mijanka[i][p];
              mijanka[i][p-2]=mijanka[i][p-1];
              mijanka[i][p]=mijanka[i][p+1]=0;
            }
          }
          else if(mijanka[i][ROZMIAR_MIJANKI]==WYJEZDZA)
          {
            if(p==ROZMIAR_MIJANKI-1 || mijanka[i][p+1]==1)
            {//trzeba skasowac pociag
              mijanka[i][p]=mijanka[i][p+1]=0;
            }
            else
            {//trzeba przepisac pociag w prawo
              if(!mijanka[i][p+4])
              {
                mijanka[i][p+3]=mijanka[i][p];
                mijanka[i][p+4]=mijanka[i][p+5];
                mijanka[i][p]=mijanka[i][p+1]=0;
              }
            }
          }
        }
      }
    }
    //sprawdzenie czy wszystkie punkty sa wolne
    bool f=true;
    if(pkt_postojowe[i][0]==WJAZD_WYJAZD)
    {
      for(int p=1;p<ROZMIAR_MIJANKI;p+=3)
      {
        if(mijanka[i][p]>0)
          f=false;
      }
      if(f)
      {
        if(mijanka[i][ROZMIAR_MIJANKI]==WYJEZDZA && stan[pkt_postojowe[i][2]/100][pkt_postojowe[i][2]%100]!=POLE_WOLNE)
          continue;
        if(mijanka[i][ROZMIAR_MIJANKI]==WJEZDZA && stan[pkt_postojowe[i][2]/100][pkt_postojowe[i][2]%100]!=POLE_WOLNE)
          continue;
        mijanka[i][ROZMIAR_MIJANKI]=WOLNA_MIJANKA;
       // int poz=pkt_postojowe[i][2];
       // stan[poz/100][poz%100]=POLE_WOLNE;
      }
      if(mijanka[i][ROZMIAR_MIJANKI]==WJEZDZA)
      {
        int poz=pkt_postojowe[i][2];
        if(stan[poz/100][poz%100]==POLE_WOLNE)
        stan[poz/100][poz%100]=POLE_ZAREZERWOWANE;
      }
    }
  }
}

/*******************************************************************************
 *** Funkcja sprawdza poprawnosc punktu wyjazdowego.                         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 08.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyDobryPunkt(int poz_p, int poczatek,int koniec)
{
  int i;
    if(pkt_postojowe[poz_p][2]==poczatek)
    {
      for(i=0;i<DLUGOSC_POSTOJOWYCH && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY && stan_postojowych[poz_p][i].Polaczenie();i++)
      {
        if(stan_postojowych[poz_p][i].Typ()<3)
          break;
      }
    }
    else
    {
      for(i=0;i<DLUGOSC_POSTOJOWYCH && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY;i++);
      i--;
      for(;i>=0 && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY;i--)
      {
        if(i>0)
        {
          if(!stan_postojowych[poz_p][i-1].Polaczenie())
            break;
        }
        else
          break;
        if(stan_postojowych[poz_p][i].Typ()<3)
          break;
      }
    }
    if(stan_postojowych[poz_p][i].Typ()<3)
    {
      if(Rozklad.Dokad(stan_postojowych[poz_p][i].Rozklad())!=koniec)
        return false;
    }
    return true;
}

/*******************************************************************************
 *** Funkcja sprawdza czy zaznaczany pociag jedzie.                          ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 08.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyJedzie(int poz_p, int poczatek)
{
  if(pkt_postojowe[poz_p][2]==poczatek)
  {
    if(CzyRuch(poz_p,0))
    {
      return true;;
    }
  }
  else
  {
    int i;
    for(i=DLUGOSC_POSTOJOWYCH-1;i>=1;i--)
    {
      if(stan_postojowych[poz_p][i].Rodzaj()!=PUSTY)
        break;
    }
    if(CzyRuch(poz_p,i))
    {
      return true;
    }
  }
  return false;
}

/*******************************************************************************
 *** Funkcja sprawdza czy zaznaczana jest sama lokomotywa.                   ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 12.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyLokomotywa(int poz_p, int p_y, int k_y, int poczatek)
{
  if(pkt_postojowe[poz_p][0]==BOCZNICA)
  {
    poz_p=stan_postojowych[poz_p][0].Bocznica();
    if(p_y<k_y)
    {//w prawo
      int i;
      for(i=DLUGOSC_POSTOJOWYCH-1;i>=0 && stan_postojowych[poz_p][i].Rodzaj()==PUSTY;i--);
      if(stan_postojowych[poz_p][i].Typ()<3)
        return false;
      if(i>0)
      {
        if(stan_postojowych[poz_p][i-1].Polaczenie())
          return false;
      }
    }
    else
    {//w lewo
      if(stan_postojowych[poz_p][0].Typ()<3 || stan_postojowych[poz_p][0].Polaczenie())
        return false;
    }
  }
  else if(pkt_postojowe[poz_p][2]==poczatek)
  {
    if(stan_postojowych[poz_p][0].Typ()<3)
      return false;
    if(stan_postojowych[poz_p][0].Polaczenie())
      return false;
  }
  else
  {
    int i;
    for(i=DLUGOSC_POSTOJOWYCH-1;stan_postojowych[poz_p][i].Rodzaj()==PUSTY && i>=0;i--);
    if(stan_postojowych[poz_p][i].Typ()<3)
      return false;
    if(i>0)
    {
      if(stan_postojowych[poz_p][i-1].Polaczenie())
        return false;
    }
  }
  return true;
}

/*******************************************************************************
 *** Funkcja sprawdza czy trwa laczenie/rozlaczanie.                         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 12.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyManewry(int poz_p,int p_y, int k_y)
{
  int i=poz_p;
  if(pkt_postojowe[poz_p][0]==BOCZNICA)
    i=stan_postojowych[poz_p][0].Bocznica();
  if(p_y>k_y)
  {//w lewo
    for(int x=0;x<DLUGOSC_POSTOJOWYCH;x++)
    {
      if(stan_postojowych[i][x].Czas()!=0)
      {
        return true;
      }
      if(!stan_postojowych[i][x].Polaczenie())
        break;
    }
  }
  else
  {//w prawo
    int x;
    for(x=0;x<DLUGOSC_POSTOJOWYCH && stan_postojowych[i][x].Rodzaj()!=PUSTY;x++);
    x--;
    for(;x>=0;x--)
    {
      if(stan_postojowych[i][x].Czas()!=0)
      {
        return true;
      }
      if(x>0)
        if(!stan_postojowych[i][x-1].Polaczenie())
          break;
    }
  }
  return false;
}

/*******************************************************************************
 *** Funkcja sprawdza czy dany pociag musi sie zatrzymac przy peronie.       ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 04.08.2002                                  ***
 ******************************************************************************/
bool tStacja::CzyPostuj(int poz_p)
{
  if(pkt_postojowe[poz_p][0]==WJAZD || pkt_postojowe[poz_p][0]==WJAZD_WYJAZD)
  {
    int poz=0;
    if(!pkt_postojowe[poz_p][5]%2)
    //prawy wjazd
    {
      for(int i=DLUGOSC_POSTOJOWYCH-1;i>=0;i++)
      {
        if(stan_postojowych[poz_p][i].Rodzaj()!=PUSTY)
        {
          poz=i;
          break;
        }
      }
    }
    if(Rozklad.TypPociagu(stan_postojowych[poz_p][poz].Rozklad(),NIEOKRESLONA)==POCIAG_BEZ_ZATRZYMANIA)
      return false;
    else
      return true;
  }
  else
    return false;
}
/*******************************************************************************
 *** Funkcja sprawdza poprawnosc wyjezdzajacego skladu.                      ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   0 - OK                                                                ***
 ***   1 - brak loka na poczatku skladu                                      ***
 ***                                                                         ***
 *** Wersja: 0.07                                                            ***
 *** Data ostatniej modyfikacji: 04.08.2002                                  ***
 ******************************************************************************/
int tStacja::CzyPrzod(int poz_p, int poczatek)
{
  //dla pociagu bez zatrzymywania warunki nie sa sprawdzane
  if(pkt_postojowe[poz_p][0]==WJAZD_WYJAZD || pkt_postojowe[poz_p][0]==WJAZD) return 0;
  //sprawdzenie czy lok jest podlaczony w dobrym miejscu skladu
  int lok=0;
  int wagon=0;
  int jedn=0;
  int rozkl=-1;
    if(pkt_postojowe[poz_p][2]==poczatek)
    {
      for(int i=0;i<DLUGOSC_POSTOJOWYCH;i++)
      {
        switch(stan_postojowych[poz_p][i].Typ())
        {
          case 0:
          {
            if(!lok && !jedn) return 1;
            if(rozkl==-1) rozkl=stan_postojowych[poz_p][i].Rozklad();
            wagon++;
            int t=stan_postojowych[poz_p][i].Rozklad();
            t=Rozklad.CzyLaczenie(t,NIEOKRESLONA);
            t=t-t/10*10;
            if(t)
            {
              if(t!=wagon+jedn) return 5;
            }
            else
              if(wagon+jedn!=1) return 6;
            break;
          }
          case 1:
          case 2:
          {
            if(wagon) return 3;
            if(rozkl==-1) rozkl=stan_postojowych[poz_p][i].Rozklad();
            jedn++;
            int t=stan_postojowych[poz_p][i].Rozklad();
            t=Rozklad.CzyLaczenie(t,NIEOKRESLONA);
            t=t-t/10*10;
            if(t)
            {
              if(t!=jedn+wagon) return 5;
            }
            else
              if(wagon+jedn!=1) return 6;
            break;
          }
          case 3:
          case 4:
          case 5:
            if(wagon || jedn) return 4;
            lok++;
            break;
        }
        if(!stan_postojowych[poz_p][i].Polaczenie()) break;
      }
      if(lok && !wagon && !jedn) return 2;
      int t=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD);
      if(jedn)
      {
        if(lok>1) return 7;
        else if(lok && stan_postojowych[poz_p][1].Sprawnosc()) return 7;
        else if(przejscia && lok && stan_postojowych[poz_p][0].Numer()) return 9;
        else t=0;
      }
      else if(t<0) t=2;
      else t=1;
      if(t==1 && lok>1)
      {
        if(lok>2) return 7;
        else if(!stan_postojowych[poz_p][1].Sprawnosc() && lok>2) return 7;
        else if(stan_postojowych[poz_p][1].Sprawnosc() && lok>1) return 7;
      }
      else if(t==2 && lok>2)
      {
        if(lok>3) return 7;
        else if(!stan_postojowych[poz_p][1].Sprawnosc() && !stan_postojowych[poz_p][2].Sprawnosc() && lok>3) return 7;
        else if(stan_postojowych[poz_p][1].Sprawnosc() && !stan_postojowych[poz_p][2].Sprawnosc() && lok>2) return 7;
        else if(stan_postojowych[poz_p][1].Sprawnosc() && stan_postojowych[poz_p][2].Sprawnosc() && lok>2) return 7;
      }
      else if(t==2 && lok<2) return 8;
      if(t==1 && lok==1)
      {
        if(przejscia && Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)!=stan_postojowych[poz_p][0].Numer() && stan_postojowych[poz_p][0].Numer()) return 9;
        if(przejscia && Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD)!=stan_postojowych[poz_p][0].Rodzaj() && stan_postojowych[poz_p][0].Numer()) return 10;
      }
      else if(t==1 && lok==2)
      {
        if(przejscia && stan_postojowych[poz_p][0].Numer()) return 9;
        if(przejscia && Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)!=stan_postojowych[poz_p][1].Numer() && stan_postojowych[poz_p][1].Numer()) return 9;
      }
      else if(t==2 && lok==2)
      {
        if(!stan_postojowych[poz_p][0].Sprawnosc() || !stan_postojowych[poz_p][1].Sprawnosc()) return 8;
        int u=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        int uu=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        if(przejscia && u/1000!=stan_postojowych[poz_p][0].Numer() && stan_postojowych[poz_p][0].Numer()) return 9;
        if(przejscia && uu/1000!=stan_postojowych[poz_p][0].Rodzaj() && stan_postojowych[poz_p][0].Numer()) return 10;
        u=u-u/1000*1000;
        uu=uu-uu/1000*1000;
        if(przejscia && u!=stan_postojowych[poz_p][1].Numer() && stan_postojowych[poz_p][1].Numer()) return 9;
        if(przejscia && uu!=stan_postojowych[poz_p][1].Rodzaj() && stan_postojowych[poz_p][1].Numer()) return 10;
      }
      else if(t==2 && lok==3)
      {
        if(przejscia && stan_postojowych[poz_p][0].Numer()) return 9;
        int u=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        int uu=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        if(przejscia && u/1000!=stan_postojowych[poz_p][1].Numer() && stan_postojowych[poz_p][1].Numer()) return 9;
        if(przejscia && uu/1000!=stan_postojowych[poz_p][1].Rodzaj() && stan_postojowych[poz_p][1].Numer()) return 10;
        u=u-u/1000*1000;
        uu=uu-uu/1000*1000;
        if(przejscia && u!=stan_postojowych[poz_p][2].Numer() && stan_postojowych[poz_p][2].Numer()) return 9;
        if(przejscia && uu!=stan_postojowych[poz_p][2].Rodzaj() && stan_postojowych[poz_p][2].Numer()) return 10;
      }
    }
    else
    {
      int i;
      for(i=DLUGOSC_POSTOJOWYCH-1; stan_postojowych[poz_p][i].Rodzaj()==PUSTY && i>=0;i--);
      int old_i=i;
      for(;i>=0;i--)
      {
        switch(stan_postojowych[poz_p][i].Typ())
        {
          case 0:
          {
            if(!lok && !jedn) return 1;
            if(rozkl==-1) rozkl=stan_postojowych[poz_p][i].Rozklad();
            wagon++;
            int t=stan_postojowych[poz_p][i].Rozklad();
            t=Rozklad.CzyLaczenie(t,NIEOKRESLONA);
            t=t-t/10*10;
            if(t)
            {
              if(t!=wagon+jedn) return 5;
            }
            else
              if(wagon+jedn!=1) return 6;
            break;
          }
          case 1:
          case 2:
          {
            if(wagon) return 3;
            if(rozkl==-1) rozkl=stan_postojowych[poz_p][i].Rozklad();
            jedn++;
            int t=stan_postojowych[poz_p][i].Rozklad();
            t=Rozklad.CzyLaczenie(t,NIEOKRESLONA);
            t=t-t/10*10;
            if(t)
            {
              if(t!=wagon+jedn) return 5;
            }
            else
              if(wagon+jedn!=1) return 6;
            break;
          }
          case 3:
          case 4:
          case 5:
            if(wagon || jedn) return 4;
            lok++;
            break;
        }
        if(i && !stan_postojowych[poz_p][i-1].Polaczenie()) break;
      }
      if(lok && !wagon && !jedn) return 2;
      int t=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD);
      if(jedn)
      {
        if(lok>1) return 7;
        else if(lok && stan_postojowych[poz_p][old_i-1].Sprawnosc()) return 7;
        else if(przejscia && lok && stan_postojowych[poz_p][old_i-0].Numer()) return 9;
        else t=0;
      }
      else if(t<0) t=2;
      else t=1;
      if(t==1 && lok>1)
      {
        if(lok>2) return 7;
        else if(!stan_postojowych[poz_p][old_i-1].Sprawnosc() && lok>2) return 7;
        else if(stan_postojowych[poz_p][old_i-1].Sprawnosc() && lok>1) return 7;
      }
      else if(t==2 && lok>2)
      {
        if(lok>3) return 7;
        else if(!stan_postojowych[poz_p][old_i-1].Sprawnosc() && !stan_postojowych[poz_p][old_i-2].Sprawnosc() && lok>3) return 7;
        else if(stan_postojowych[poz_p][old_i-1].Sprawnosc() && !stan_postojowych[poz_p][old_i-2].Sprawnosc() && lok>2) return 7;
        else if(stan_postojowych[poz_p][old_i-1].Sprawnosc() && stan_postojowych[poz_p][old_i-2].Sprawnosc() && lok>2) return 7;
      }
      else if(t==2 && lok<2) return 8;
      if(t==1 && lok==1)
      {
        if(przejscia && Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)!=stan_postojowych[poz_p][old_i-0].Numer() && stan_postojowych[poz_p][old_i-0].Numer()) return 9;
        if(przejscia && Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD)!=stan_postojowych[poz_p][old_i-0].Rodzaj() && stan_postojowych[poz_p][old_i-0].Numer()) return 10;
      }
      else if(t==1 && lok==2)
      {
        if(przejscia && stan_postojowych[poz_p][old_i-0].Numer()) return 9;
        if(przejscia && Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)!=stan_postojowych[poz_p][old_i-1].Numer() && stan_postojowych[poz_p][old_i-1].Numer()) return 9;
      }
      else if(t==2 && lok==2)
      {
        if(!stan_postojowych[poz_p][old_i-0].Sprawnosc() || !stan_postojowych[poz_p][old_i-1].Sprawnosc()) return 8;
        int u=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        int uu=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        if(przejscia && u/1000!=stan_postojowych[poz_p][old_i-0].Numer() && stan_postojowych[poz_p][old_i-0].Numer()) return 9;
        if(przejscia && uu/1000!=stan_postojowych[poz_p][old_i-0].Rodzaj() && stan_postojowych[poz_p][old_i-0].Numer()) return 10;
        u=u-u/1000*1000;
        uu=uu-uu/1000*1000;
        if(przejscia && u!=stan_postojowych[poz_p][old_i-1].Numer() && stan_postojowych[poz_p][old_i-1].Numer()) return 9;
        if(przejscia && uu!=stan_postojowych[poz_p][old_i-1].Rodzaj() && stan_postojowych[poz_p][old_i-1].Numer()) return 10;
      }
      else if(t==2 && lok==3)
      {
        if(przejscia && stan_postojowych[poz_p][old_i-0].Numer()) return 9;
        int u=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        int uu=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD)*(-1);
        if(przejscia && u/1000!=stan_postojowych[poz_p][old_i-1].Numer() && stan_postojowych[poz_p][old_i-1].Numer()) return 9;
        if(przejscia && uu/1000!=stan_postojowych[poz_p][old_i-1].Rodzaj() && stan_postojowych[poz_p][old_i-1].Numer()) return 10;
        u=u-u/1000*1000;
        uu=uu-uu/1000*1000;
        if(przejscia && u!=stan_postojowych[poz_p][old_i-2].Numer() && stan_postojowych[poz_p][old_i-2].Numer()) return 9;
        if(przejscia && uu!=stan_postojowych[poz_p][old_i-2].Rodzaj() && stan_postojowych[poz_p][old_i-2].Numer()) return 10;
      }
    }
    return 100;
}

/*******************************************************************************
 *** Funkcja sprawdza czy pod wspolrzedna w znajduje sie punkt postojowy.    ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  w - wspolrzedne punktu                                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  Rodzaj punktu postojowego                                              ***
 ***  0 - gdy wpolrzedne nie wskazuja na punkt postojowy                     ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 03.07.2001                                  ***
 ******************************************************************************/
int tStacja::CzyPunkt(int w)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    for(int j=2;j<DLUGOSC_PUNKTU;j++)
    {
      if(pkt_postojowe[i][j]==w)
        return pkt_postojowe[i][0];
    }
  }
  return 0;
}


/*******************************************************************************
 *** Funkcja sprawdza czy nie za wczesnie na zaznaczenie trasy.              ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 12.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyPunktualnie(int poz_p, int poczatek)
{
  if(pkt_postojowe[poz_p][2]==poczatek)
    {
      int i;
      for(i=0;i<DLUGOSC_POSTOJOWYCH;i++)
      {
        if(stan_postojowych[poz_p][i].Typ()<3 && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY)
          break;
        if(!stan_postojowych[poz_p][i].Polaczenie())
        {
          i=DLUGOSC_POSTOJOWYCH;
        }
      }
      if(i<DLUGOSC_POSTOJOWYCH)
      {
        int pozycja=stan_postojowych[poz_p][i].Rozklad();
        if(Rozklad.Godzina(pozycja,NIEOKRESLONA,ODJAZD)-Rozklad.DodajCzas(Zegar.Godzina(),30)>0)
          return false;
      }
    }
    else
    {
      int i;
      for(i=DLUGOSC_POSTOJOWYCH-1; i>=0 && stan_postojowych[poz_p][i].Rodzaj()==PUSTY;i--);
      for(;i>=0;i--)
      {
        if(stan_postojowych[poz_p][i].Typ()<3 && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY)
          break;
        if(i>0)
          if(!stan_postojowych[poz_p][i-1].Polaczenie())
          {
            i=-1;
          }
      }
      if(i>=0)
      {
        int pozycja=stan_postojowych[poz_p][i].Rozklad();
        if(Rozklad.Godzina(pozycja,NIEOKRESLONA,ODJAZD)-Rozklad.DodajCzas(Zegar.Godzina(),30)>0)
          return false;
      }
    }
    return true;
}

/*******************************************************************************
 *** Funkcja sprawdza czy dany pociag jest towarowy.                         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 17.01.2004                                  ***
 ******************************************************************************/
bool tStacja::CzyTowarowy(int poz_p)
{
  for(int i=0;i<DLUGOSC_POSTOJOWYCH;i++)
  {
    if(stan_postojowych[poz_p][i].Rodzaj()==PUSTY)
      return false;
    else if(stan_postojowych[poz_p][i].Typ()>=0 && stan_postojowych[poz_p][i].Typ()<=2)
    {
      if(Rozklad.RodzajTyp(Rozklad.RodzajNumer(stan_postojowych[poz_p][i].Rozklad(),NIEOKRESLONA))==TOWAROWY)
        return true;
      else
        return false;
    }
  }
  return false;
}

/*******************************************************************************
 *** Funkcja sprawdza czy dany sklad jedzie lub rusza.                       ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  i,j - wspolrzedne skladu                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  Rodzaj punktu postojowego                                              ***
 ***  0 - gdy wpolrzedne nie wskazuja na punkt postojowy                     ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 01.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyRuch(int i,int j)
{
  if(stan_postojowych[i][j].Ruch()!=STOI)
    return true;
  else if(stan_postojowych[i][j].Typ()>0)
    return false;
  else
  {//wagon
    for(int u=j;u<DLUGOSC_POSTOJOWYCH;u++)
    {
      if(stan_postojowych[i][u].Ruch())
        return true;
      if(!stan_postojowych[i][u].Polaczenie())
        break;
    }
    for(int u=j-1;u>=0;u--)
    {
      if(stan_postojowych[i][u].Ruch() && stan_postojowych[i][u].Polaczenie())
        return true;
      if(!stan_postojowych[i][u].Polaczenie())
        break;
    }
    return false;
  }
}

/*******************************************************************************
 *** Funkcja okresla czy w danym punkcie postojowym stoi lokomotywa.         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   wsp - wspolrzedne sprawdzanego punktu.                                ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   stoi/nie stoi                                                         ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 24.07.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyStoiPociag(int wsp)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    for(int j=2;j<DLUGOSC_PUNKTU;j++)
    {
      if(pkt_postojowe[i][j]==wsp)
      {
        for(int k=0;k<DLUGOSC_POSTOJOWYCH;k++)
        {
          if(stan_postojowych[i][k].Rodzaj()!=PUSTY)
            return true;
        }
        return false;
      }
    }
  }
  return false;
}

/*******************************************************************************
 *** Funkcja sprawdza, czy sklad moze juz zjechac z peronu.                  ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   i,j - wpolrzedne skladu                                               ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 21.01.2002                                  ***
 ******************************************************************************/
bool tStacja::CzyZjechac(int i, int j)
{
  if(stan_postojowych[i][j].Typ()>2)
    return true;
  int r=stan_postojowych[i][j].Rozklad();
  if(Rozklad.RodzajTyp(Rozklad.RodzajNumer(r,NIEOKRESLONA))==SPECJALNY)
    return true;
  if(Rozklad.TypPociagu(r,NIEOKRESLONA)==POCIAG_DOCELOWY || Rozklad.TypPociagu(r,NIEOKRESLONA)==POCIAG_DOCELOWY_ROZLACZANY)
    return false;
  else
    return true;
}

/*******************************************************************************
 *** Funkcja sprawdza czy sklad moze juz zjechac z peronu.                   ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   poz_p - numer punktu postojowego poczatkowego                         ***
 ***   poczatek - poczatek zaznaczanej trasy                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 22.10.2001                                  ***
 ******************************************************************************/
bool tStacja::CzyMoznaZjechac(int poz_p, int poczatek)
{
  int i;
  if(pkt_postojowe[poz_p][2]==poczatek)
  {
    for(i=0;i<DLUGOSC_POSTOJOWYCH && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY && stan_postojowych[poz_p][i].Polaczenie();i++)
    {
      if(stan_postojowych[poz_p][i].Typ()<3)
        break;
    }
  }
  else
  {
    for(i=0;i<DLUGOSC_POSTOJOWYCH && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY;i++);
    i--;
    for(;i>=0 && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY;i--)
    {
      if(i>0)
      {
        if(!stan_postojowych[poz_p][i-1].Polaczenie())
          break;
      }
      else
        break;
      if(stan_postojowych[poz_p][i].Typ()<3)
        break;
    }
  }
  if(stan_postojowych[poz_p][i].Typ()<3)
  {
    if(!CzyZjechac(poz_p,i))
      return false;
  }
  return true;
}

/*******************************************************************************
 *** Funkcja dokonuje niezbednych zmian w tablicy stan dla ruszajacego       ***
 *** pociagu.                                                                ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   pociag - wskaznik na lokomotywe.                                      ***
 ***                                                                         ***
 *** Wersja: 0.04                                                            ***
 *** Data ostatniej modyfikacji: 04.08.2001                                  ***
 ******************************************************************************/
void tStacja::DrogaZaznaczona(tObiektRuchomy* pociag)
{
  int z_i=0,z_j=0;
  bool wyjdz=false;
  //szukam numeru punktu postojowego, z ktorego pociag rusza
  for(z_i=0;z_i<ilosc_postojowych+dlugosc_bocznic;z_i++)
  {
    for(z_j=0;z_j<DLUGOSC_POSTOJOWYCH;z_j++)
    {
      if(&stan_postojowych[z_i][z_j]==pociag)
      {
        wyjdz=true;
        break;
      }
    }
    if(wyjdz) break;
  }
  //szukam numeru punktu postojowego, do ktorego pociag ma zaznaczona trase
  int do_i=0, do_j=0;
  int koniec=stan_postojowych[z_i][z_j].KoniecTrasy();
  if(koniec) //jest wpisana trasa
  {
    wyjdz=false;
    for(do_i=0;do_i<ilosc_postojowych;do_i++)
    {
      for(do_j=2;do_j<DLUGOSC_PUNKTU;do_j++)
      {
        if(pkt_postojowe[do_i][do_j]==koniec)
        {
          wyjdz=true;
          break;
        }
      }
      if(wyjdz) break;
    }
  }
  else return;
  int poczatek=z_j;
  koniec=z_j;
  //szukam konca skladu
  for(;koniec<DLUGOSC_POSTOJOWYCH && stan_postojowych[z_i][koniec].Polaczenie();koniec++);
  //szukam poczatku skladu
  for(;poczatek>0 && stan_postojowych[z_i][poczatek-1].Polaczenie();poczatek--);
  int p=0;
  if(pkt_postojowe[do_i][0]==PERON || pkt_postojowe[do_i][0]==PERON_TOWAROWY)
  {//pociag jedzie na peron
    //szukam wolnego punktu
    for(;p<DLUGOSC_POSTOJOWYCH;p++)
    {
      if(stan_postojowych[do_i][p].Rodzaj()==PUSTY)
        break;
    }
    if(p==DLUGOSC_POSTOJOWYCH) return;
    if(do_j==2)
    {//trasa konczy sie z lewej strony peronu
      if(stan_postojowych[do_i][0].Rodzaj()!=PUSTY)
      {
        //przesuwam wszystko w prawo
        for(int l=koniec-poczatek+p;l>0;l--)
          stan_postojowych[do_i][l].Kopiuj(&stan_postojowych[do_i][l-koniec+poczatek-1]);
        p=0;
      }
    }
  }
  int warunek=p+koniec-poczatek;
  for(int l=0;p<=warunek;p++,l++)
    stan_postojowych[do_i][p].Kopiuj(&stan_postojowych[z_i][poczatek+l]);

  if(z_i<ilosc_postojowych)
  if(stan_postojowych[z_i][0].Rodzaj()==PUSTY && (pkt_postojowe[z_i][0]==PERON || pkt_postojowe[z_i][0]==PERON_TOWAROWY))
  {//na peronie mogla powstac dziura, trzeba ja zalatac
    int p=0;
    for(int j=1;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      if(stan_postojowych[z_i][j].Rodzaj()!=PUSTY)
      {
        stan_postojowych[z_i][p].Kopiuj(&stan_postojowych[z_i][j]);
        p++;
      }
    }
  }
  if(z_i<ilosc_postojowych)
  if(stan_postojowych[z_i][0].Rodzaj()==PUSTY && (pkt_postojowe[z_i][0]==PERON || pkt_postojowe[z_i][0]==PERON_TOWAROWY))
  {
    for(int x=2;x<DLUGOSC_PUNKTU;x++)
    {
      int poz=pkt_postojowe[z_i][x];
      stan[poz/100][poz-(poz/100)*100]=POLE_WOLNE;
    }
  }
  //DLA BOCZNICY
  if((pkt_postojowe[do_i][0]==BOCZNICA)&& stan_postojowych[do_i][0].Rodzaj()!=PUSTY)
  {
    int x=stan_postojowych[do_i][0].Bocznica();
    int p=0;
    if(x<0)
    {//wjazd z lewej strony
      x=-x;

      if(stan_postojowych[x][0].Rodzaj()!=PUSTY)
      {//cos juz stoi i trzeba to przesunac
        int g;
        for(g=0;g<DLUGOSC_POSTOJOWYCH;g++)
        {
          if(stan_postojowych[x][g].Rodzaj()==PUSTY)
            break;
        }
        //dlugosc tego co wjezdza
        int dlugosc;
        for(dlugosc=0;dlugosc<DLUGOSC_POSTOJOWYCH;dlugosc++)
        {
          if(stan_postojowych[do_i][dlugosc].Rodzaj()==PUSTY)
            break;
        }
        //przesuwany
        for(p=g-1+dlugosc;p>=0 && g>0;p--,g--)
        {
          stan_postojowych[x][p].Kopiuj(&stan_postojowych[x][g-1]);
        }
        p=0;
      }
    }
    else
    {//wjazd z prawej strony
      for(p=0;p<DLUGOSC_POSTOJOWYCH;p++)
      {
        if(stan_postojowych[x][p].Rodzaj()==PUSTY)
          break;
      }
    }
    for(int a=0;a<DLUGOSC_POSTOJOWYCH || p<DLUGOSC_POSTOJOWYCH;a++,p++)
    {
      if(stan_postojowych[do_i][a].Rodzaj()!=PUSTY)
        stan_postojowych[x][p].Kopiuj(&stan_postojowych[do_i][a]);
      else
        break;
    }
  }
}

/*******************************************************************************
 *** Funkcja zwraca godzine do wyswietlenia.                                 ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - przyjazd/odjazd                                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj loka                                                            ***
 ***  NULL - gdy nie trzeba wymieniac loka                                   ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 16.08.2001                                  ***
 *******************************************************************************/
char * tStacja::Godzina(int pozycja, int rodzaj, int godzina)
{
  int godz=Rozklad.Godzina(pozycja, rodzaj, godzina);
  if(godz>=POLNOC)
    godz-=POLNOC;
  if(godz<0) godz=-godz;
  char* g=new char [6];
  char c[3];
  sprintf(g,"%d",godz/100);
  strcat(g,":");
  if(godz%100<10)
    strcat(g,"0");
  sprintf(c,"%d",godz%100);
  strcat(g,c);
  return g;
}

/*******************************************************************************
 *** Funkcja zwraca godzine rzeczywista do wyswietlenia.                     ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - przyjazd/odjazd                                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  godzina rzeczywista                                                    ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 07.09.2002                                  ***
 *******************************************************************************/
char * tStacja::GodzinaRzeczywista(int pozycja, int rodzaj, int godzina)
{
  int godz=Rozklad.GodzinaRzeczywista(pozycja, rodzaj, godzina);
  if(godz>=POLNOC)
    godz-=POLNOC;
  if(godz<0) godz=-godz;
  char* g=new char [6];
  char c[3];
  sprintf(g,"%d",godz/100);
  strcat(g,":");
  if(godz%100<10)
    strcat(g,"0");
  sprintf(c,"%d",godz%100);
  strcat(g,c);
  return g;
}

/*******************************************************************************
 *** Funkcja okresla wpolrzedne loka stajacego na danym punkcie postojowym.  ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   wsp - wspolrzedne sprawdzanego punktu.                                ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   wspolrzedne loka                                                      ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 11.01.2003                                  ***
 ******************************************************************************/
int tStacja::KtoZajmujePunkt(int wsp)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    for(int j=2;j<DLUGOSC_PUNKTU;j++)
    {
      if(pkt_postojowe[i][j]==wsp)
      {
        for(int k=0;k<DLUGOSC_POSTOJOWYCH;k++)
        {
          if(stan_postojowych[i][k].Typ())
            return i*100+k;
        }
        return false;
      }
    }
  }
  return 0;
}

/*******************************************************************************
 *** Funkcja sluzy do laczenia i rozlaczania skladow.                        ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  wsp - wspolrzedne danego punktu                                        ***
 ***  pozycja - pozycja danego wagonu                                        ***
 ***  nr - numer w tablicy stan_postojowych dla bocznicy                     ***
 ***                                                                         ***
 *** Wersja: 0.06                                                            ***
 *** Data ostatniej modyfikacji: 23.11.2001                                  ***
 *******************************************************************************/
char* tStacja::Laczenie(int wsp, int pozycja, int nr)
{
  int jednostka=Zegar.Jednostka();
  char* info="";
  switch(CzyPunkt(wsp))
  {
    case PERON:
    case PERON_TOWAROWY:
    {
      int nr=NrPunktu(wsp);
      if(CzyRuch(nr,pozycja) || CzyRuch(nr,pozycja+1))
      {
        info="Poci¹g jest w ruchu.";
        return info;
      }
      if(stan_postojowych[nr][pozycja].Czas() || stan_postojowych[nr][pozycja+1].Czas())
      {
        info="Trwa ³¹czenie/roz³¹czanie.";
        return info;
      }
      if(stan_postojowych[nr][pozycja+1].Rodzaj()!=PUSTY)
      {//wpisujemy czas
        if(stan_postojowych[nr][pozycja].Polaczenie())
        {//rozlaczamy
          stan_postojowych[nr][pozycja].Czas(CZAS_ROZLACZENIA/jednostka);
          stan_postojowych[nr][pozycja+1].Czas(CZAS_ROZLACZENIA/jednostka);
        }
        else
        {//laczymy
          if(stan_postojowych[nr][pozycja].Typ() || stan_postojowych[nr][pozycja+1].Typ())
          {//laczymy loka z czyms
            stan_postojowych[nr][pozycja].Czas(CZAS_LACZENIA_LOKA/jednostka);
            stan_postojowych[nr][pozycja+1].Czas(CZAS_LACZENIA_LOKA/jednostka);
          }
          else
          {//laczymy wagony
            stan_postojowych[nr][pozycja].Czas(CZAS_LACZENIA/jednostka);
            stan_postojowych[nr][pozycja+1].Czas(CZAS_LACZENIA/jednostka);
          }
        }
      }
      else
      {
        info="Na prawo nic nie stoi.";
        return info;
      }
      break;
    }
    case BOCZNICA:
    {
      if(CzyRuch(nr,pozycja) || CzyRuch(nr,pozycja+1))
      {
        info="Poci¹g jest w ruchu.";
        return info;
      }
      if(stan_postojowych[nr][pozycja].Czas() || stan_postojowych[nr][pozycja+1].Czas())
      {
        info="Trwa ³¹czenie/roz³¹czanie.";
        return info;
      }
      if(stan_postojowych[nr][pozycja+1].Rodzaj()!=PUSTY)
      {//wpisujemy czas
        if(stan_postojowych[nr][pozycja].Polaczenie())
        {//rozlaczamy
          stan_postojowych[nr][pozycja].Czas(CZAS_ROZLACZENIA/jednostka);
          stan_postojowych[nr][pozycja+1].Czas(CZAS_ROZLACZENIA/jednostka);
        }
        else
        {//laczymy
          if(stan_postojowych[nr][pozycja].Typ() || stan_postojowych[nr][pozycja+1].Typ())
          {//laczymy loka z czyms
            stan_postojowych[nr][pozycja].Czas(CZAS_LACZENIA_LOKA/jednostka);
            stan_postojowych[nr][pozycja+1].Czas(CZAS_LACZENIA_LOKA/jednostka);
          }
          else
          {//laczymy wagony
            stan_postojowych[nr][pozycja].Czas(CZAS_LACZENIA/jednostka);
            stan_postojowych[nr][pozycja+1].Czas(CZAS_LACZENIA/jednostka);
          }
        }
      }
      else
      {
        info="Na prawo nic nie stoi.";
        return info;
      }
      break;
    }
    default:
      info="W tym punkcie nie wolno ³¹czyæ/roz³¹czaæ sk³adów.";
  }
  return info;
}

/*******************************************************************************
 *** Funkcja zwraca nazwe loka.                                              ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj loka                                                            ***
 ***                                                                         ***
 *** Wersja: 0.06                                                            ***
 *** Data ostatniej modyfikacji: 14.02.2005                                  ***
 *******************************************************************************/
char* tStacja::Lok(int pozycja, int rodzaj)
{
  int l=Rozklad.Lok(pozycja,rodzaj);
  if(l==0) return NULL;
  else if(l<0)
  {
    l=l*(-1);
    char* nazwa=new char[18];
    strcpy(nazwa,Rozklad.NazwaTypu(l/1000));
    l=l-l/1000*1000;
    strcat(nazwa,"|");
    strcat(nazwa,Rozklad.NazwaTypu(l));
    return nazwa;
  }
  else
  {
    char* nazwa=new char[18];
    strcpy(nazwa,Rozklad.NazwaTypu(l));
    return nazwa;
  }
}

/*******************************************************************************
 *** Funkcja sprawdza czy w punkcie postojowym jest miejsce na pociag.       ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   pozycja - numer punktu postojowego koncowego                          ***
 ***   poczatek - numer punktu postojowego poczatkowego                      ***
 ***   p_y - wspolrzedna poczatku                                            ***
 ***   k_y - wspolrzedna konca                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   prawda/falsz                                                          ***
 ***                                                                         ***
 *** Wersja: 0.06                                                            ***
 *** Data ostatniej modyfikacji: 24.10.2001                                  ***
 ******************************************************************************/
bool tStacja::Miejsce(int pozycja, int poczatek, int p_y, int k_y)
{
  int old_poczatek=poczatek;
  //obliczam dlugosc skladu
  if(pkt_postojowe[poczatek][0]==BOCZNICA)
  {
    poczatek=stan_postojowych[poczatek][0].Bocznica();
  }
  int dlugosc=0; //dlugosc tego co wjezdza
  if(p_y<k_y)
  {//w prawo
    int i;
    for(i=DLUGOSC_POSTOJOWYCH-1;i>=0 && stan_postojowych[poczatek][i].Rodzaj()==PUSTY;i--);
    for(;i>=0;i--, dlugosc++)
    {
      if(stan_postojowych[poczatek][i].Rodzaj()==PUSTY)
        break;
      if(dlugosc && !stan_postojowych[poczatek][i].Polaczenie())
      {
        //dlugosc--;
        break;
      }
    }
  }
  else
  {//w lewo
    for(dlugosc=0;dlugosc<DLUGOSC_POSTOJOWYCH;dlugosc++)
    {
      if(stan_postojowych[poczatek][dlugosc].Rodzaj()==PUSTY)
        break;
      if(!stan_postojowych[poczatek][dlugosc].Polaczenie())
      {
        dlugosc++;
        break;
      }
    }
  }
  if(pozycja>=ilosc_postojowych)
  {//bocznica
    int ilosc;
    for(ilosc=0;stan_postojowych[pozycja][ilosc].Rodzaj()!=PUSTY;ilosc++);
    if(ilosc+dlugosc>DLUGOSC_POSTOJOWYCH) return false;
    else
      return true;
  }
  else if(pkt_postojowe[pozycja][0]==LOKOWNIA)
  {
    //lokomotywownia
    if(Lokomotywownia.CzyJestMiejsce()==TAK && stan_postojowych[pozycja][0].Rodzaj()==PUSTY)
      return true;
    else
      return false;
  }
  else if(pkt_postojowe[pozycja][0]!=PERON && pkt_postojowe[pozycja][0]!=PERON_TOWAROWY)
  {
    //zwykly punkt
    if(stan_postojowych[pozycja][0].Rodzaj()==PUSTY)
      return true;
    else
      return false;
  }
  else
  {//peron
    if(pkt_postojowe[old_poczatek][0]==WJAZD || pkt_postojowe[old_poczatek][0]==WJAZD_WYJAZD)
    {
      if(stan_postojowych[pozycja][0].Rodzaj()!=PUSTY)
        return false;
      else
        return true;
    }
    int ilosc;
    for(ilosc=0;stan_postojowych[pozycja][ilosc].Rodzaj()!=PUSTY;ilosc++);
    if(ilosc+dlugosc>DLUGOSC_POSTOJOWYCH) return false;
    else
      return true;
  }
}

/*******************************************************************************
 *** Funkcja zwraca pociagi znajdujace sie miedzy mijanka a wjazdem.         ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  punkt - odnosnik to mijanki                                            ***
 ***  odcinek - numer odcinka miedzy wjazdem a mijanka                       ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  gdy odinek=0 - ilosc punktow                                           ***
 ***  gdy odcinek<>0 - odnosnik do rozkladu                                  ***
 ***  gdy odcinek=ROZIAR_MIJANKI - rodzaj zajetosci mijanki                  ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 11.05.2003                                  ***
 *******************************************************************************/
int tStacja::Mijanka(int punkt, int odcinek)
{
  if(odcinek==ROZMIAR_MIJANKI)
    return mijanka[punkt][odcinek];
  else if(!odcinek)
  {
    int ilosc=0;
    for(int i=2;i<ROZMIAR_MIJANKI && mijanka[punkt][i]!=-1;i+=3)
      ilosc++;
    return ilosc;
  }
  else
  {
    if(mijanka[punkt][(odcinek-1)*3+1])
      return mijanka[punkt][(odcinek-1)*3];
    else
      return -1;
  }
}

/*******************************************************************************
 *** Funkcja zwraca nazwe bitmapy do wyswietlenia.                           ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   i - numer punktu postojowego/numer loka                               ***
 ***   j - numer pola/NIEOKRESLONA                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   nazwa bitmapy do wczytania                                            ***
 ***                                                                         ***
 *** Wersja: 0.04                                                            ***
 *** Data ostatniej modyfikacji: 17.10.2001                                  ***
 ******************************************************************************/
const char* tStacja::Nazwa(int i, int j)
{
  if(j==NIEOKRESLONA)
    return nazwy_rysunkow[i];
  else if(j==-1)
    return Rozklad.NazwaTypu(i);
  else
    return Rozklad.NazwaTypu(stan_postojowych[i][j].Rodzaj());
}

/*******************************************************************************
 *** Funkcja zwraca numer obrazaka taboru do wyswietlenia.                   ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   i - numer punktu postojowego                                          ***
 ***   j - numer pola                                                        ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   numer bitmapy do wczytania                                            ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 10.08.2001                                  ***
 ******************************************************************************/
int tStacja::NazwaNr(int i, int j)
{
    return stan_postojowych[i][j].Rodzaj();
}

/*******************************************************************************
 *** Funkcja przelicza wspolrzedne punktu postojowego na jego numer.         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   wsp - wspolrzedne punktu postojowego                                  ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   numer punktu postojowego                                              ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 11.07.2001                                  ***
 ******************************************************************************/
int tStacja::NrPunktu(int wsp)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    for(int j=2;j<DLUGOSC_PUNKTU;j++)
    {
      if(pkt_postojowe[i][j]==wsp)
        return i;
    }
  }
  return -1;
}

/*******************************************************************************
 *** Funkcja okresla, ktorego pociagu dotyczy zaznaczana trasa.              ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   wsp - wspolrzedne poczatku zaznaczanej trasy                          ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   wskaznik na lokomotywe                                                ***
 ***                                                                         ***
 *** Wersja: 0.10                                                            ***
 *** Data ostatniej modyfikacji: 17.06.2002                                  ***
 ******************************************************************************/
tObiektRuchomy * tStacja::Obiekt(int wsp,int koniec)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    if(pkt_postojowe[i][2]==wsp)
    {
      if(pkt_postojowe[i][0]==BOCZNICA)
      {
          i=stan_postojowych[i][0].Bocznica();
      }
      if(i>=ilosc_postojowych && koniec)
      {
        if(koniec%100-wsp%100>0)
        {//w prawo
          for(int j=DLUGOSC_POSTOJOWYCH-1;j>=0;j--)
          {
            if(stan_postojowych[i][j].Typ()>0)
              return &stan_postojowych[i][j];
            if(j>0)
            {
              if(stan_postojowych[i][j].Rodzaj()!=PUSTY && !stan_postojowych[i][j-1].Polaczenie())
                return 0;
            }
            else
              return 0;
          }
        }
        else
        {//w lewo
          for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
          {
            if(stan_postojowych[i][j].Typ()>0)
              return &stan_postojowych[i][j];
            if(!stan_postojowych[i][j].Polaczenie())
              return 0;
          }
        }
      }
      else
      {
        if(koniec%100-wsp%100>0)
        {//w prawo
          for(int j=DLUGOSC_POSTOJOWYCH-1;j>=0;j--)
          {
            if(stan_postojowych[i][j].Typ()>0)
              return &stan_postojowych[i][j];
            if(j>0)
            {
              if(stan_postojowych[i][j].Rodzaj()!=PUSTY && !stan_postojowych[i][j-1].Polaczenie())
                return 0;
            }
            else
              return 0;
          }
        }
        else
        {//w lewo
          for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
          {
            if(stan_postojowych[i][j].Typ()>0)
              return &stan_postojowych[i][j];
            if(!stan_postojowych[i][j].Polaczenie())
              return 0;
          }
        }
      }
    }
    if(pkt_postojowe[i][4]==wsp)
    {
      for(int j=DLUGOSC_POSTOJOWYCH-1;j>=0;j--)
      {
        if(stan_postojowych[i][j].Typ()>0)
          return &stan_postojowych[i][j];
        if(j>0)
        {
          if(stan_postojowych[i][j].Rodzaj()!=PUSTY && !stan_postojowych[i][j-1].Polaczenie())
            return 0;
        }
        else
          return 0;
      }
    }
  }
  return 0;
}

/*******************************************************************************
 *** Funkcja wykonuje niezbedne czynnosci co kazde tykniecie zegara.         ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 21.04.2003                                  ***
 ******************************************************************************/

int tStacja::Odmierz(void)
{
  int w=0;
  try
    {
      Zegar.Odmierz();
    }
    catch(int)
    {
      Rozklad.NowaDoba();
    }
    w=Poruszanie();
//    TworzPociag();
    int ww=Rozklad.Opoznienie(Zegar.Godzina());
    Aktualizuj();
    return w+10*ww;
}

/*******************************************************************************
 *** Funkcja zwraca peron zapisany cyframi rzymskimi.                        ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   peron - numer peronu                                                  ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   peron cyframi rzymskimi                                               ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 07.09.2002                                  ***
 ******************************************************************************/
char* tStacja::Peron(int peron)
{
  char* p=0;
  switch(peron)
  {
    case 1:
      p="I";
      break;
    case 2:
      p="II";
      break;
    case 3:
      p="III";
      break;
    case 4:
      p="IV";
      break;
    case 5:
      p="V";
      break;
    case 6:
      p="VI";
      break;
    case 7:
      p="VII";
      break;
    case 8:
      p="VIII";
      break;
    case 9:
      p="IX";
      break;
    default:
      p=" ";
  }
  return p;
}

/*******************************************************************************
 *** Funkcja zwraca tablice z zestawieniem skaldu.                           ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   i - numer punktu postojowego                                          ***
 ***   j - numer pola                                                        ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   tablica z zestawieniem skladu                                         ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 07.10.2001                                  ***
 ******************************************************************************/
int * tStacja::Podglad(int i, int j)
{
  return Rozklad.Podglad(stan_postojowych[i][j].Rozklad());
}

/*******************************************************************************
 *** Funkcja sluzy do poruszania pociagow i zmniejszania czasu laczenia.     ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   1 - jezeli zostal swtworzony nowy pociag                              ***
 ***                                                                         ***
 *** Wersja: 0.39                                                            ***
 *** Data ostatniej modyfikacji: 14.07.2005                                  ***
 ******************************************************************************/
int tStacja::Poruszanie(void)
{
  int wynik=0;
  for(int i=0;i<ilosc_postojowych+dlugosc_bocznic;i++)
  {
    for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      /*if(stan_postojowych[i][j].Ruch()==RUSZA)
      {
      int yy=stan_postojowych[i][j].Ruch();
      int yyy=pkt_postojowe[i][0];
      int yyyy=mijanka[i][ROZMIAR_MIJANKI];
      int yyyyy=stan_postojowych[i][j].Czas();
      int yyyyyy=0;
      } */
      if(stan_postojowych[i][j].Ruch()==RUSZA && i<ilosc_postojowych &&
         (pkt_postojowe[i][0]==WJAZD || (pkt_postojowe[i][0]==WJAZD_WYJAZD && mijanka[i][ROZMIAR_MIJANKI]!=WYJEZDZA))
          && stan_postojowych[i][j].Czas())
      //pociag dojezdza do stacji
      {
        if( stan_postojowych[i][j].Czas()==1)
        {
          stan_postojowych[i][j].Czas(0);
          int r;
          for (int t=0;t<DLUGOSC_POSTOJOWYCH;t++)
          {
            r= stan_postojowych[i][t].Rozklad();
            if(r>=0 && stan_postojowych[i][t].Rodzaj()!=PUSTY)
              Rozklad.Stan(r,NIEOKRESLONA,JEST);
          }
          stan_postojowych[i][j].Ruch(STOI);
          int poz=pkt_postojowe[i][2];
          stan[poz/100][poz-(poz/100)*100]=POLE_ZAJETE;
          wynik=1;
        }
      }
      else if(stan_postojowych[i][j].Ruch()==RUSZA && i<ilosc_postojowych &&
             (pkt_postojowe[i][0]==WYJAZD || (pkt_postojowe[i][0]==WJAZD_WYJAZD && mijanka[i][ROZMIAR_MIJANKI]==WYJEZDZA))
              && stan_postojowych[i][j].Czas())
      //pociag wyjezdza ze stacji
      {
        if( stan_postojowych[i][j].Czas()==1)
        {
          stan_postojowych[i][j].Czas(0);
          tObiektRuchomy t;
          int rozkl;
          int lok=0;
          for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
          {
            if(int a=stan_postojowych[i][j].Rodzaj()!=PUSTY)
            {
              if(stan_postojowych[i][j].Typ()<3)//LOK)
              {
                if(stan_postojowych[i][j].Typ())
                  lok++;
                rozkl=stan_postojowych[i][j].Rozklad();
                if(pkt_postojowe[i][0]==WJAZD_WYJAZD)
                {
                  mijanka[i][ROZMIAR_MIJANKI]=WYJEZDZA;
                  mijanka[i][1]=mijanka[i][2];
                  mijanka[i][0]=rozkl;
                }
                if(Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA)==POCIAG_ZE_STACJI)
                {
                  Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,POCIAG_DOCELOWY);
                }
                else if(Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA)==POCIAG_ZE_STACJI_LACZONY)
                {
                  Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,POCIAG_DOCELOWY_ROZLACZANY);
                }
                int g=Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD);
                Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,g+POLNOC);
                if(g<0)
                {
                  Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,-g);
                  Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,NIEOKRESLONA);
                }
                else
                {
                  Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,g+POLNOC);
                  g=Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD);
                  Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD,g);
                }
                Rozklad.Stan(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,BEDZIE);
              }
              else
                lok++;
            }
            else
              break;
          }
          //  if(przejscia)
          {
            if(pkt_postojowe[i][5]%2)
            {//lewy wyjazd
              int typ_loka=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD);
              int szopa_loka=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD);
              if(lok==1)
              {
                if(stan_postojowych[i][1].Typ()==1 || stan_postojowych[i][1].Typ()==2)
                Rozklad.PowrotLoka(rozkl,stan_postojowych[i][0].Rodzaj(),WspWjazd(pkt_postojowe[i][5]/10));
                else if(szopa_loka!=stan_postojowych[i][0].Numer() || typ_loka!=stan_postojowych[i][0].Rodzaj())
                Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][0].Rodzaj());
              }
              else if(lok==2)
              {
                if(stan_postojowych[i][1].Sprawnosc())
                {//trakcja podwojna
                  szopa_loka*=(-1);
                  typ_loka*=(-1);
                  if(szopa_loka/1000!=stan_postojowych[i][0].Numer() || typ_loka/1000!=stan_postojowych[i][0].Rodzaj())
                    Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][0].Rodzaj(),1);
                  szopa_loka=szopa_loka-szopa_loka/1000*1000;
                  typ_loka=typ_loka-typ_loka/1000*1000;
                  if(szopa_loka!=stan_postojowych[i][1].Numer() || typ_loka!=stan_postojowych[i][1].Rodzaj())
                    Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][1].Rodzaj(),2);
                }
                else
                {// jeden lok popsuty
                  Rozklad.PowrotLoka(rozkl,stan_postojowych[i][0].Rodzaj(),WspWjazd(pkt_postojowe[i][5]/10));
                }
              }
              else
              {
                Rozklad.PowrotLoka(rozkl,stan_postojowych[i][0].Rodzaj(),WspWjazd(pkt_postojowe[i][5]/10));
              }
            }
            else
            {//prawy wyjazd
              int v;
              for(v=DLUGOSC_POSTOJOWYCH-1; stan_postojowych[i][v].Rodzaj()==PUSTY && v>=0;v--);
              int typ_loka=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD);
              int szopa_loka=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD);
              if(lok==1)
              {
                if(stan_postojowych[i][v-1].Typ()==1 || stan_postojowych[i][v-1].Typ()==2)
                  Rozklad.PowrotLoka(rozkl,stan_postojowych[i][v-0].Rodzaj(),WspWjazd(pkt_postojowe[i][5]/10));
                else if(szopa_loka!=stan_postojowych[i][v].Numer() || typ_loka!=stan_postojowych[i][v].Rodzaj())
                  Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][v].Rodzaj());
              }
              else if(lok==2)
              {
                if(stan_postojowych[i][v-1].Sprawnosc())
                {//trakcja podwojna
                  szopa_loka*=(-1);
                  typ_loka*=(-1);
                  if(szopa_loka/1000!=stan_postojowych[i][v].Numer() || typ_loka/1000!=stan_postojowych[i][v].Rodzaj())
                    Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][v].Rodzaj(),1);
                  szopa_loka=szopa_loka-szopa_loka/1000*1000;
                  typ_loka=typ_loka-typ_loka/1000*1000;
                  if(szopa_loka!=stan_postojowych[i][v-1].Numer() || typ_loka!=stan_postojowych[i][v-1].Rodzaj())
                    Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][v-1].Rodzaj(),2);
                }
                else
                {// jeden lok popsuty
                  Rozklad.PowrotLoka(rozkl,stan_postojowych[i][v-0].Rodzaj(),WspWjazd(pkt_postojowe[i][5]/10));
                }
              }
              else
              {
                Rozklad.PowrotLoka(rozkl,stan_postojowych[i][v-0].Rodzaj(),WspWjazd(pkt_postojowe[i][5]/10));
              }
            }
          }
          for(int x=0;x<DLUGOSC_POSTOJOWYCH;x++)
          {
            if(stan_postojowych[i][x].Rodzaj()!=PUSTY)
            {
              t.Kopiuj(&stan_postojowych[i][x]);
            }
            else
              break;
          }
          int poz=pkt_postojowe[i][2];
          stan[poz/100][poz-(poz/100)*100]=POLE_WOLNE;
        }
      }
      else if(int d=stan_postojowych[i][j].Ruch()==RUSZA) //pociag ma zaznaczona trase do odjazdu
      {
        //tutaj beda sprawdzane warunki czy pociag moze juz ruszyc
        if(i>=ilosc_postojowych)
        {//bocznica
          //szukam z ktorej bocznicy rusza pociag
          int b;
          for(b=0;b<ilosc_postojowych;b++)
          {
            if((pkt_postojowe[b][0]==BOCZNICA)
              && pkt_postojowe[b][5]+pkt_postojowe[b][1]+ilosc_postojowych-1>=i
              && pkt_postojowe[b][5]+ilosc_postojowych<=i)
              break;

          }
          if(stan_postojowych[i][j].KoniecTrasy()%100-stan_postojowych[i][j].PoczatekTrasy()%100>0)
          {//jedziemy w prawo
            int koniec;
            for(koniec=0;koniec<DLUGOSC_POSTOJOWYCH;koniec++)
              if(stan_postojowych[i][koniec].Rodzaj()==PUSTY) break;
            koniec--;//ostatnie zajete miejsce
            int poczatek;
            for(poczatek=koniec-1;poczatek>=0 && stan_postojowych[i][poczatek].Polaczenie();poczatek--);
            poczatek++; //pierwsze zajete miejsce
            for(int v=0;stan_postojowych[i][poczatek+v].Rodzaj()!=PUSTY;v++)
              stan_postojowych[b][v].Kopiuj(&stan_postojowych[i][v+poczatek]);
            for(int v=koniec;v>=0;v--)
            {
              if(stan_postojowych[b][v].Typ()>0)
              {
                stan_postojowych[b][v].Ruch(JEDZIE);
                DrogaZaznaczona(&stan_postojowych[b][v]);
                break;
              }
            }
          }
          else
          {//jedziemy w lewo
            for(int v=0;v<DLUGOSC_POSTOJOWYCH;v++)
            {
              stan_postojowych[b][v].Kopiuj(&stan_postojowych[i][v]);
              if(!stan_postojowych[b][v].Polaczenie())
                break;
            }
            //mogla powstac dziura
            if(stan_postojowych[i][0].Rodzaj()==PUSTY)
            {
              int sklad;
              for(sklad=0;sklad<DLUGOSC_POSTOJOWYCH && stan_postojowych[i][sklad].Rodzaj()==PUSTY;sklad++);
              //sklad--;
              for(int p=0;sklad<DLUGOSC_POSTOJOWYCH && stan_postojowych[i][sklad].Rodzaj()!=PUSTY;sklad++,p++)
                stan_postojowych[i][p].Kopiuj(&stan_postojowych[i][sklad]);
            }
            for(int v=0;v<DLUGOSC_POSTOJOWYCH;v++)
            {
              if(stan_postojowych[b][v].Typ()>0)
              {
                stan_postojowych[b][v].Ruch(JEDZIE);
                DrogaZaznaczona(&stan_postojowych[b][v]);
                break;
              }
            }
          }
/*          stan_postojowych[b][j].Kopiuj(&stan_postojowych[i][j]);
          stan_postojowych[b][j].Ruch(JEDZIE);
          DrogaZaznaczona(&stan_postojowych[b][j]);*/
/*          stan_postojowych[i][j].Ruch(JEDZIE);
          DrogaZaznaczona(&stan_postojowych[i][j]);*/
        }
        else if(pkt_postojowe[i][0]==PERON || pkt_postojowe[i][0]==PERON_TOWAROWY)
        {//pociag rusza z peronu
          int n=NrPunktu(stan_postojowych[i][j].KoniecTrasy());
          if(pkt_postojowe[n][0]==WYJAZD || pkt_postojowe[n][0]==WJAZD_WYJAZD)
          {
            if(stan_postojowych[i][j].Typ()<3)
            {//dla jednostek nierozlaczalnych
              int pozycja=stan_postojowych[i][j].Rozklad();
              if(Rozklad.Godzina(pozycja,NIEOKRESLONA,ODJAZD)-Zegar.Godzina()<=0)
              {
                Rozklad.Stan(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,BYL);
                stan_postojowych[i][j].Ruch(JEDZIE);
                DrogaZaznaczona(&stan_postojowych[i][j]);
                Rozklad.GodzinaRzeczywista(pozycja,NIEOKRESLONA,ODJAZD,Zegar.Godzina());
              }
            }
            else
            {//normalny sklad
              if(stan_postojowych[i][j].KoniecTrasy()%100-stan_postojowych[i][j].PoczatekTrasy()%100>0)
              {//w prawo
                //szukam wagonu
                int w=j;
                bool lok=false;
                if(w>0)
                {
                  for(;w>0;w--)
                  {
                    if(stan_postojowych[i][w].Typ()<3)
                      break;
                    if(!stan_postojowych[i][w-1].Polaczenie())
                    {
                      lok=true;
                      break;
                    }
                  }
                  if(!lok && !w)
                  {
                    if(stan_postojowych[i][w].Typ()>=3)
                      lok=true;
                  }
                }
                else
                  lok=true;
                if(lok)
                {//same loki
                  stan_postojowych[i][j].Ruch(JEDZIE);
                  DrogaZaznaczona(&stan_postojowych[i][j]);
                  Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,Zegar.Godzina());
                }
                else
                {//normalny sklad
                  int pozycja=stan_postojowych[i][w].Rozklad();
                  if(Rozklad.Godzina(pozycja,NIEOKRESLONA,ODJAZD)-Zegar.Godzina()<=0)
                  {
                    for(;w>=0;w--)
                    {
                      if(stan_postojowych[i][w].Typ()<3)
                      {
                        Rozklad.Stan(stan_postojowych[i][w].Rozklad(),NIEOKRESLONA,BYL);
                        Rozklad.GodzinaRzeczywista(stan_postojowych[i][w].Rozklad(),NIEOKRESLONA,ODJAZD,Zegar.Godzina());
                      }
                      if(w==0) break;
                      if(!stan_postojowych[i][w-1].Polaczenie())
                        break;
                    }
                    stan_postojowych[i][j].Ruch(JEDZIE);
                    DrogaZaznaczona(&stan_postojowych[i][j]);
                    //Rozklad.GodzinaRzeczywista(pozycja,NIEOKRESLONA,ODJAZD,Zegar.Godzina());
                  }
                }
              }
              else
              {//w lewo
                //szukamy wagonu
                int w=j;
                bool lok=false;
                for(;w<DLUGOSC_POSTOJOWYCH ;w++)
                {
                  if(stan_postojowych[i][w].Typ()<3)
                    break;
                  if(!stan_postojowych[i][w].Polaczenie())
                  {
                    lok=true;
                    break;
                  }
                }
                if(lok)
                {//same loki
                  stan_postojowych[i][j].Ruch(JEDZIE);
                  DrogaZaznaczona(&stan_postojowych[i][j]);
                  Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,Zegar.Godzina());
                }
                else
                {//normalny sklad
                  int pozycja=stan_postojowych[i][w].Rozklad();
                  if(Rozklad.Godzina(pozycja,NIEOKRESLONA,ODJAZD)-Zegar.Godzina()<=0)
                  {
                    for(;w<DLUGOSC_POSTOJOWYCH;w++)
                    {
                      if(stan_postojowych[i][w].Typ()<3)
                      {
                        Rozklad.Stan(stan_postojowych[i][w].Rozklad(),NIEOKRESLONA,BYL);
                        Rozklad.GodzinaRzeczywista(stan_postojowych[i][w].Rozklad(),NIEOKRESLONA,ODJAZD,Zegar.Godzina());
                      }
                      if(!stan_postojowych[i][w].Polaczenie())
                        break;
                    }
                    stan_postojowych[i][j].Ruch(JEDZIE);
                    DrogaZaznaczona(&stan_postojowych[i][j]);
                    //Rozklad.GodzinaRzeczywista(pozycja,NIEOKRESLONA,ODJAZD,Zegar.Godzina());
                  }
                }
              }
            }
          }
          else
          {
            stan_postojowych[i][j].Ruch(JEDZIE);
            DrogaZaznaczona(&stan_postojowych[i][j]);
          }
        }
/*        else if(pkt_postojowe[i][0]==WJAZD || pkt_postojowe[i][0]==WJAZD_WYJAZD)
        // pociag rusza z wjazdu
        {
          int aaa= Rozklad.Stan(NrRozklad(i,j),PRZYJAZD);
          int yy=NrRozklad(i,j);
          Rozklad.Stan(NrRozklad(i,j),PRZYJAZD,JEST);
          stan_postojowych[i][j].Ruch(JEDZIE);
          DrogaZaznaczona(&stan_postojowych[i][j]);
        }*/
        else if(pkt_postojowe[i][0]==WJAZD || pkt_postojowe[i][0]==WJAZD_WYJAZD)
        {
          for(int p=0;p<DLUGOSC_POSTOJOWYCH;p++)
          {
            if(stan_postojowych[i][p].Typ()<3 && stan_postojowych[i][p].Rodzaj()!=PUSTY)
            {
              int g=Rozklad.Godzina(stan_postojowych[i][p].Rozklad(),NIEOKRESLONA,PRZYJAZD);
              if(g<0)
              {
                Rozklad.Godzina(stan_postojowych[i][p].Rozklad(),NIEOKRESLONA,PRZYJAZD,-g);
                Rozklad.GodzinaRzeczywista(stan_postojowych[i][p].Rozklad(),NIEOKRESLONA,PRZYJAZD,NIEOKRESLONA);
              }
              else
              {
                Rozklad.Godzina(stan_postojowych[i][p].Rozklad(),NIEOKRESLONA,PRZYJAZD,g+POLNOC);
                g=Rozklad.GodzinaRzeczywista(stan_postojowych[i][p].Rozklad(),NIEOKRESLONA,PRZYJAZD);
                if(g>POLNOC) g-=POLNOC;
                Rozklad.GodzinaRzeczywista(stan_postojowych[i][p].Rozklad(),NIEOKRESLONA,PRZYJAZD,g+POLNOC);
              }
            }
          }
          // dla pociagow bez zatrzymywania
          int n=NrPunktu(stan_postojowych[i][j].KoniecTrasy());
          int nn=NrPunktu(stan_postojowych[i][j].PoczatekTrasy());
          if((pkt_postojowe[nn][0]==WJAZD || pkt_postojowe[nn][0]==WJAZD_WYJAZD)
              &&(pkt_postojowe[n][0]==WYJAZD || pkt_postojowe[n][0]==WJAZD_WYJAZD))
                Rozklad.Stan(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,BYL);
          //dla wszystkoch pociagow
          stan_postojowych[i][j].Ruch(JEDZIE);
          DrogaZaznaczona(&stan_postojowych[i][j]);
        }
        else
        {
/*          // dla pociagow bez zatrzymywania
          int n=NrPunktu(stan_postojowych[i][j].KoniecTrasy());
          int nn=NrPunktu(stan_postojowych[i][j].PoczatekTrasy());
          if((pkt_postojowe[nn][0]==WJAZD || pkt_postojowe[nn][0]==WJAZD_WYJAZD)
              &&(pkt_postojowe[n][0]==WYJAZD || pkt_postojowe[n][0]==WJAZD_WYJAZD))
                Rozklad.Stan(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,BYL);*/
          //dla wszystkoch pociagow
          stan_postojowych[i][j].Ruch(JEDZIE);
          DrogaZaznaczona(&stan_postojowych[i][j]);

        }
      }
      else if(stan_postojowych[i][j].Ruch()==JEDZIE) //pociag jedzie
      {
        int poz=stan_postojowych[i][j].Pozycja(); //pozycja biezaca pociagu
        stan[poz/100][poz-(poz/100)*100]=POLE_WOLNE;
        int nr=NrPunktu(poz);
        if(nr>=0)
        {
          if((pkt_postojowe[nr][0]==PERON || pkt_postojowe[nr][0]==PERON_TOWAROWY) && stan_postojowych[nr][0].Rodzaj()!=PUSTY)
            stan[poz/100][poz-(poz/100)*100]=POLE_ZAJETE;
        }
        poz=stan_postojowych[i][j].Odcinek();
        if(poz)
        {
          stan[poz/100][poz-(poz/100)*100]=POLE_ZAJETE;
        }
        else //koniec trasy
        {
          for(int x=2;x<DLUGOSC_PUNKTU;x++)
          {
            if(i<ilosc_postojowych)
            {
              poz=pkt_postojowe[i][x];
              if(poz)
                stan[poz/100][poz-(poz/100)*100]=POLE_ZAJETE;
              if (pkt_postojowe[i][0]==WJAZD_WYJAZD) x=DLUGOSC_PUNKTU;
            }

          }
          if(i<ilosc_postojowych)
          {
            switch(pkt_postojowe[i][0])
            {
              case WYJAZD:
              {
                for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
                {
                  if(stan_postojowych[i][j].Rodzaj()!=PUSTY)
                  {
                    if(stan_postojowych[i][j].Typ())//nie wagon)
                    {
                      stan_postojowych[i][j].Ruch(RUSZA);
                      int jednostka=Zegar.Jednostka();
                      stan_postojowych[i][j].Czas(pkt_postojowe[i][1]*60/jednostka);
                      if (!stan_postojowych[i][j].Czas())
                        stan_postojowych[i][j].Czas(2); //zabazpieczenie dla wyjazdow bez okreslonego czasu
                    }
                  }
                }
                poz=pkt_postojowe[i][2];
                stan[poz/100][poz-(poz/100)*100]=POLE_ZAREZERWOWANE;
                break;
              }
              case WJAZD_WYJAZD:
              {
                for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
                {
                  if(stan_postojowych[i][j].Rodzaj()!=PUSTY)
                  {
                    if(stan_postojowych[i][j].Typ())//nie wagon)
                    {
                      stan_postojowych[i][j].Ruch(RUSZA);
                      int jednostka=Zegar.Jednostka();
                      stan_postojowych[i][j].Czas((pkt_postojowe[i][1]/100)*60/jednostka);
                      if (!stan_postojowych[i][j].Czas())
                        stan_postojowych[i][j].Czas(2); //zabazpieczenie dla wyjazdow bez okreslonego czasu
                      mijanka[i][ROZMIAR_MIJANKI]=WYJEZDZA;
                      /*mijanka[i][1]=mijanka[i][2];
                      mijanka[i][0]=stan_postojowych[i][j].Rozklad();*/
                    }
                  }
                }
                poz=pkt_postojowe[i][2];
                stan[poz/100][poz-(poz/100)*100]=POLE_ZAREZERWOWANE;
                /*tObiektRuchomy t;
                int rozkl;
                int lok=0;
                for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
                {
                  if(int a=stan_postojowych[i][j].Rodzaj()!=PUSTY)
                  {
                    if(stan_postojowych[i][j].Typ()<3)//LOK)
                    {
                      if(stan_postojowych[i][j].Typ())
                        lok++;
                      rozkl=stan_postojowych[i][j].Rozklad();
                      if(Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA)==POCIAG_ZE_STACJI)
                      {
                        Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,POCIAG_DOCELOWY);
                      }
                      else if(Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA)==POCIAG_ZE_STACJI_LACZONY)
                      {
                        Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,POCIAG_DOCELOWY_ROZLACZANY);
                      }
                      int g=Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD);
                      Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,g+POLNOC);
                      if(g<0)
                      {
                        Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,-g);
                        Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,NIEOKRESLONA);
                      }
                      else
                      {
                        Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,ODJAZD,g+POLNOC);
                        g=Rozklad.Godzina(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD);
                        Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD,g);
                      }
                      Rozklad.Stan(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,BEDZIE);
                    }
                    else
                      lok++;
                  }
                  else
                    break;
                }
              //  if(przejscia)
                {
                  if(pkt_postojowe[i][5]%2)
                  {//lewy wyjazd
                    int typ_loka=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD);
                    int szopa_loka=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD);
                    if(lok==1)
                    {
                      if(stan_postojowych[i][1].Typ()==1 || stan_postojowych[i][1].Typ()==2)
                        Rozklad.PowrotLoka(rozkl,stan_postojowych[i][0].Rodzaj());
                      else if(szopa_loka!=stan_postojowych[i][0].Numer() || typ_loka!=stan_postojowych[i][0].Rodzaj())
                        Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][0].Rodzaj());
                    }
                    else if(lok==2)
                    {
                      if(stan_postojowych[i][1].Sprawnosc())
                      {//trakcja podwojna
                        szopa_loka*=(-1);
                        typ_loka*=(-1);
                        if(szopa_loka/1000!=stan_postojowych[i][0].Numer() || typ_loka/1000!=stan_postojowych[i][0].Rodzaj())
                          Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][0].Rodzaj(),1);
                        szopa_loka=szopa_loka-szopa_loka/1000*1000;
                        typ_loka=typ_loka-typ_loka/1000*1000;
                        if(szopa_loka!=stan_postojowych[i][1].Numer() || typ_loka!=stan_postojowych[i][1].Rodzaj())
                          Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][1].Rodzaj(),2);
                      }
                      else
                      {// jeden lok popsuty
                        Rozklad.PowrotLoka(rozkl,stan_postojowych[i][0].Rodzaj());
                      }
                    }
                    else
                    {
                      Rozklad.PowrotLoka(rozkl,stan_postojowych[i][0].Rodzaj());
                    }
                  }
                  else
                  {//prawy wyjazd
                    int v;
                    for(v=DLUGOSC_POSTOJOWYCH-1; stan_postojowych[i][v].Rodzaj()==PUSTY && v>=0;v--);
                    int typ_loka=Rozklad.Lokomotywa(rozkl,NIEOKRESLONA,ODJAZD);
                    int szopa_loka=Rozklad.Szopa(rozkl,NIEOKRESLONA,ODJAZD);
                    if(lok==1)
                    {
                      if(stan_postojowych[i][v-1].Typ()==1 || stan_postojowych[i][v-1].Typ()==2)
                        Rozklad.PowrotLoka(rozkl,stan_postojowych[i][v-0].Rodzaj());
                      else if(szopa_loka!=stan_postojowych[i][v].Numer() || typ_loka!=stan_postojowych[i][v].Rodzaj())
                        Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][v].Rodzaj());
                    }
                    else if(lok==2)
                    {
                      if(stan_postojowych[i][v-1].Sprawnosc())
                      {//trakcja podwojna
                        szopa_loka*=(-1);
                        typ_loka*=(-1);
                        if(szopa_loka/1000!=stan_postojowych[i][v].Numer() || typ_loka/1000!=stan_postojowych[i][v].Rodzaj())
                          Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][v].Rodzaj(),1);
                        szopa_loka=szopa_loka-szopa_loka/1000*1000;
                        typ_loka=typ_loka-typ_loka/1000*1000;
                        if(szopa_loka!=stan_postojowych[i][v-1].Numer() || typ_loka!=stan_postojowych[i][v-1].Rodzaj())
                          Rozklad.KorygowaniePrzejscia(rozkl,stan_postojowych[i][v-1].Rodzaj(),2);
                      }
                      else
                      {// jeden lok popsuty
                        Rozklad.PowrotLoka(rozkl,stan_postojowych[i][v-0].Rodzaj());
                      }
                    }
                    else
                    {
                      Rozklad.PowrotLoka(rozkl,stan_postojowych[i][v-0].Rodzaj());
                    }
                  }
                }
                for(int x=0;x<DLUGOSC_POSTOJOWYCH;x++)
                {
                  if(stan_postojowych[i][x].Rodzaj()!=PUSTY)
                  {
                    t.Kopiuj(&stan_postojowych[i][x]);
                  }
                  else
                    break;
                  poz=pkt_postojowe[i][2];
                  stan[poz/100][poz-(poz/100)*100]=POLE_WOLNE;
                }*/
                break;
              }
              case LOKOWNIA:
              {
                Lokomotywownia.Przyjmij(&stan_postojowych[i][0]);
                poz=pkt_postojowe[i][2];
                stan[poz/100][poz-(poz/100)*100]=POLE_WOLNE;
                break;
              }
              case PERON:
              {
                int r=stan_postojowych[i][j].Rozklad();
                if((Rozklad.TypPociagu(r,NIEOKRESLONA)==POCIAG_DOCELOWY || Rozklad.TypPociagu(r,NIEOKRESLONA)==POCIAG_DOCELOWY_ROZLACZANY)
                   && Rozklad.Stan(r,NIEOKRESLONA)==JEST)
                  Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Zegar.Godzina()+POLNOC);
                break;
              }
            }
          }
        }
      }
      //odwracanie pociagow
      if(stan_postojowych[i][j].Typ()<3 && stan_postojowych[i][j].Rodzaj()!=PUSTY)
      {
        if(Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA)==POCIAG_DOCELOWY
           && Rozklad.DodajCzas(Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD),-1435)
           <=Zegar.Godzina() && Rozklad.DodajCzas(Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD),-1435)>0)
        {
          Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,POCIAG_ZE_STACJI);
        }
        else if(Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA)==POCIAG_DOCELOWY_ROZLACZANY
           && Rozklad.DodajCzas(Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD),-1435)
           <=Zegar.Godzina() && Rozklad.DodajCzas(Rozklad.GodzinaRzeczywista(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,PRZYJAZD),-1435)>0)
        {
          Rozklad.TypPociagu(stan_postojowych[i][j].Rozklad(),NIEOKRESLONA,POCIAG_ZE_STACJI_LACZONY);
        }
      }
    }
  }
  for(int i=0;i<ilosc_postojowych+dlugosc_bocznic;i++)
  {
    for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      if(stan_postojowych[i][j].Czas())
      {//trwa laczenie/rozlaczanie
        //int a=stan_postojowych[i][j].Czas(stan_postojowych[i][j].Czas()-1);
        if(!stan_postojowych[i][j].Czas(stan_postojowych[i][j].Czas()-1))
        {
          stan_postojowych[i][j+1].Czas(stan_postojowych[i][j+1].Czas()-1);
          if(stan_postojowych[i][j].Polaczenie())
            stan_postojowych[i][j].Polaczenie(false);
          else
          stan_postojowych[i][j].Polaczenie(true);
        }
      }
    }
  }
  CzasMijanki();
  return wynik;
}

/*******************************************************************************
 *** Funkcja zwraca i ustawia stan pociagu.                                  ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  ustaw - stan                                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj loka                                                            ***
 ***  NULL - gdy nie trzeba wymieniac loka                                   ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji :25.07.2001                                  ***
 *******************************************************************************/
int tStacja::StanPociagu(int pozycja, int rodzaj, int ustaw)
{
  int godz=Rozklad.GodzinaRzeczywista(pozycja, rodzaj, rodzaj);
  if(Zegar.Godzina()>=godz && Rozklad.Stan(pozycja,rodzaj)==JEST && rodzaj==ODJAZD)
      Rozklad.Stan(pozycja,rodzaj,CZEKA_NA_WYJAZD);
//  godz=Rozklad.Stan(pozycja,rodzaj);
  return Rozklad.Stan(pozycja,rodzaj);
}

/*******************************************************************************
 *** Funkcja zwraca nazwe szopy.                                             ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie/numer szopy                     ***
 ***  rodzaj - przyjazd/odjazd /NIEOKRESLONA                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer szopy                                                            ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 05.12.2001                                  ***
 *******************************************************************************/
char* tStacja::Szopa(int pozycja, int rodzaj)
{
  if(!przejscia) return 0;
  if(rodzaj==NIEOKRESLONA)
    return Rozklad.Szopa(pozycja);
  else
  {
    int w=Rozklad.Szopa(pozycja, rodzaj);
    if(w!=NIEOKRESLONA)
    {
      if(w<0)
      {
        char* napis=new char[MAX_NAZWA*3];
        char* t;
        w*=(-1);
        t=Rozklad.Szopa(w/1000);
        strcpy(napis,t);
        delete [] t;
        strcat(napis,"|");
        w=w-w/1000*1000;
        t=Rozklad.Szopa(w);
        strcat(napis,t);
        delete [] t;
        return napis;
      }
      else
        return Rozklad.Szopa(w);
    }
    else
      return 0;
  }
}

/*******************************************************************************
 *** Funkcja sluzy do tworzenia pociagow na wjazdach.                        ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   rrr - odnosnik do rozkladu                                            ***
 ***   czekaj - czas jaki pociag ma czekac na wjazd                          ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   odnosnik do rozkladu                                                  ***
 ***                                                                         ***
 *** Wersja: 0.41                                                            ***
 *** Data ostatniej modyfikacji: 23.01.2005                                  ***
 ******************************************************************************/
int tStacja::TworzPociagi(int rrr, int czekaj)
{
  if(Zegar.Sekundy())
    return -1;
  for(int i=0;i<Rozklad.IloscPociagow();i++)
  {
    int n=Rozklad.Wjazd(i,PRZYJAZD);
    n=NrPunktu(n);
    if( (Rozklad.Stan(i,PRZYJAZD)==BEDZIE || Rozklad.Stan(i,PRZYJAZD)==CZEKA_NA_WJAZD)
        && Rozklad.DodajCzas(Rozklad.GodzinaRzeczywista(i,PRZYJAZD,PRZYJAZD),-Wyprzedz(n))<=Zegar.Godzina()
        && Rozklad.TypPociagu(i,PRZYJAZD)!=POCIAG_ROZLACZANY && Rozklad.TypPociagu(i,PRZYJAZD)!=POCIAG_DOCELOWY_ROZLACZANY)
    {// mamy pociag do stworzenia
      int poz=NrPunktu(Rozklad.Wjazd(i,PRZYJAZD));
      if (pkt_postojowe[poz][0]==WJAZD_WYJAZD)
      {//wjazd_wyjazd
        if(mijanka[poz][ROZMIAR_MIJANKI]==WYJEZDZA ||
          (mijanka[poz][ROZMIAR_MIJANKI]==WOLNA_MIJANKA && mijanka[poz][2]==-1 && stan[pkt_postojowe[poz][2]/100][pkt_postojowe[poz][2]%100]!=POLE_WOLNE)
          || (mijanka[poz][ROZMIAR_MIJANKI]!=WJEZDZA && mijanka[poz][2]!=-1 && stan[pkt_postojowe[poz][2]/100][pkt_postojowe[poz][2]%100]!=POLE_WOLNE))
        {//punkty posrednie zajete przez wyjezdzajacy pociag lub wjazd_wyjazd jest zajety
          int pkt=Rozklad.Wjazd(i,PRZYJAZD);
          int czekac=0;
          if(stan[pkt/100][pkt%100]!=POLE_WOLNE)
          {
            if(CzyStoiPociag(pkt))
            {
              Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
              int kto=KtoZajmujePunkt(Rozklad.Wjazd(i,PRZYJAZD));
              int kto_x=kto/100;
              int kto_y=kto-kto_x*100;
              int czekac=stan_postojowych[kto_x][kto_y].Czas();
              int jednostka=Zegar.Jednostka();
              czekac=czekac*jednostka/60;
            }
            else
              czekac=pkt_postojowe[poz][1]%100;
          }
          else
          {//zajety jest ktorys z punktow posrednich
            for(int u=1;u<ROZMIAR_MIJANKI && mijanka[poz][u]!=-1;u+=3)
            {
              if(mijanka[poz][u])
                czekac=mijanka[poz][u];
              else
                czekac+=mijanka[poz][u];
            }
            int jednostka=Zegar.Jednostka();
            czekac=czekac*jednostka/60;
          }
          czekac++;
          Rozklad.Opoznienie(i,PRZYJAZD,czekac);
          Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
        }
        else
        {//mijanka jest wolna lub zajeta przez pociag wjezdzajacy
          int koniec=0; //ostatni punkt mijanki
          for(;koniec<ROZMIAR_MIJANKI&&mijanka[poz][koniec]!=-1;koniec++);
          if(koniec<3)
          {//brak punktow posrednich
            if(!CzyStoiPociag(Rozklad.Wjazd(i,PRZYJAZD)) && stan[pkt_postojowe[poz][2]/100][pkt_postojowe[poz][2]%100]==POLE_WOLNE)
            {//tworzymy pociag na wjezdzie
              if(rrr!=i)
                return i;
              if(czekaj)
              {
                Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
                Rozklad.Opoznienie(i,PRZYJAZD,czekaj);
              }
              else
              {
                bool powrot=false;
                int lok=TworzPociag(i,n);
                int poz=NrPunktu(Rozklad.Wjazd(i,PRZYJAZD));
                if(lok<0/*lok==-1*/)
                {
                  poz=-lok;
                  lok=0;
                  powrot=true;
                }
                int r=Rozklad.NumerWRozkladzie(i,PRZYJAZD);
                int jednostka=Zegar.Jednostka();
                stan_postojowych[poz][lok].Czas((pkt_postojowe[poz][1]%100)*60/jednostka);
                if (!stan_postojowych[poz][lok].Czas())
                  stan_postojowych[poz][lok].Czas(1); //zabazpieczenie dla wjazdow bez okreslonego wyprzedzenia
                if(!powrot)
                  Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Rozklad.DodajCzas(Zegar.Godzina(),Wyprzedz(n)));
              }
            }
            else
            {//wjazd zajety - trzeba opoznic pociag
              Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
              int kto=KtoZajmujePunkt(Rozklad.Wjazd(i,PRZYJAZD));
              int kto_x=kto/100;
              int kto_y=kto-kto_x*100;
              int czekac=stan_postojowych[kto_x][kto_y].Czas();
              int jednostka=Zegar.Jednostka();
              czekac=czekac*jednostka/60+1;
              Rozklad.Opoznienie(i,PRZYJAZD,czekac);
            }
          }
          else
          {//sa punkty posrednie
            if(!mijanka[poz][koniec-2])
            {//mozna jechac
              if(rrr!=i)
                return i;
              if(czekaj)
              {
                Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
                Rozklad.Opoznienie(i,PRZYJAZD,czekaj);
              }
              else
              {
                mijanka[poz][koniec-3]=Rozklad.NumerWRozkladzie(i,PRZYJAZD);
                mijanka[poz][koniec-2]=mijanka[poz][koniec-1];
                mijanka[poz][ROZMIAR_MIJANKI]=WJEZDZA;
                Rozklad.Stan(i,PRZYJAZD,WJEZDZA);
              }
            }
            else
            {//punkt zajety
              Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
              int czekac=mijanka[poz][koniec-2];
              int jednostka=Zegar.Jednostka();
              czekac=czekac*jednostka/60+1;
              Rozklad.Opoznienie(i,PRZYJAZD,czekac);
            }
          }
        }


        /*poz=pkt_postojowe[poz][2];
        if(CzyStoiPociag(Rozklad.Wjazd(i,PRZYJAZD)) || stan[poz/100][poz%100]!=POLE_WOLNE
            || mijanka[NrPunktu(Rozklad.Wjazd(i,PRZYJAZD))][ROZMIAR_MIJANKI]==WYJEZDZA)
        {//wjazd_wyjazd zajety
          int poz=NrPunktu(Rozklad.Wjazd(i,PRZYJAZD));
          for(int p=0;p<ROZMIAR_MIJANKI;p+=3)
          {
            if(mijanka[poz][p]==-1 || mijanka[poz][ROZMIAR_MIJANKI]==WYJEZDZA)
            {//wszystkie punkty sa zajete trzeba opoznic pociag
              Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
              int czekac;
              if(mijanka[poz][ROZMIAR_MIJANKI]==WYJEZDZA)
                czekac=5; //!!!!!!!TO TRZEBA ZMIENIC !!!!!!!!!!!!!!!!!!!!!!!!
              else
                czekac=mijanka[poz][p-2];
              int jednostka=Zegar.Jednostka();
              czekac=czekac*jednostka/60+1;
              Rozklad.Opoznienie(i,PRZYJAZD,czekac);
              break;
            }
            else if(!mijanka[poz][p+1] && mijanka[poz][ROZMIAR_MIJANKI]!=WYJEZDZA)
            {//punkt posredni jest wolny
              mijanka[poz][p]=Rozklad.NumerWRozkladzie(i,PRZYJAZD);
              mijanka[poz][p+1]=mijanka[poz][p+2];
              mijanka[poz][ROZMIAR_MIJANKI]=WJEZDZA;
              Rozklad.Stan(i,PRZYJAZD,WJEZDZA);
              break;
            }
          }
        }
        else
        {//wjazd_wyjazd wolny
          int lok=TworzPociag(i,n);
          int poz=NrPunktu(Rozklad.Wjazd(i,PRZYJAZD));
          int r=Rozklad.NumerWRozkladzie(i,PRZYJAZD);
          int jednostka=Zegar.Jednostka();
          stan_postojowych[poz][lok].Czas((pkt_postojowe[poz][1]%100)*60/jednostka);
          if (!stan_postojowych[poz][lok].Czas())
            stan_postojowych[poz][lok].Czas(1); //zabazpieczenie dla wjazdow bez okreslonego wyprzedzenia
          Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Rozklad.DodajCzas(Zegar.Godzina(),Wyprzedz(n)));
          //mijanka[poz][ROZMIAR_MIJANKI]=WJEZDZA;
        }*/
      }
      else
      {//wjazd normalny
        poz=pkt_postojowe[poz][2];
        if(CzyStoiPociag(Rozklad.Wjazd(i,PRZYJAZD)) || stan[poz/100][poz%100]!=POLE_WOLNE)
        {
          if(Rozklad.Stan(i,PRZYJAZD)!=CZEKA_NA_WJAZD)
          {
            //punkt zajety trzeba opoznic pociag
            Rozklad.Stan(i,PRZYJAZD,CZEKA_NA_WJAZD);
            int kto=KtoZajmujePunkt(Rozklad.Wjazd(i,PRZYJAZD));
            int kto_x=kto/100;
            int kto_y=kto-kto_x*100;
            int czekac=stan_postojowych[kto_x][kto_y].Czas();
            int jednostka=Zegar.Jednostka();
            czekac=czekac*jednostka/60+1;
            Rozklad.Opoznienie(i,PRZYJAZD,czekac);
          }
          else continue;//return;
        }
        else
        {
          bool powrot=false;
          int lok=TworzPociag(i,n);
          int poz=NrPunktu(Rozklad.Wjazd(i,PRZYJAZD));
          if(lok<0)
          {
            poz=-lok;
            lok=0;
            powrot=true;
          }
          int r=Rozklad.NumerWRozkladzie(i,PRZYJAZD);
          int jednostka=Zegar.Jednostka();
          stan_postojowych[poz][lok].Czas(pkt_postojowe[poz][1]*60/jednostka);
          if (!stan_postojowych[poz][lok].Czas())
            stan_postojowych[poz][lok].Czas(1); //zabazpieczenie dla wjazdow bez okreslonego wyprzedzenia
          if(!powrot)
            Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Rozklad.DodajCzas(Zegar.Godzina(),Wyprzedz(n)));
        }
      }
    }
  }
  return -1;
}

/*******************************************************************************
 *** Funkcja sluzy do fizycznego tworzenia pociagow na wjazdach.             ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  i - odnosnik do rozkladu                                               ***
 ***  n - numer punktu postojowego                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  pozycja lokomotywy lub -pozycja dla powrotu loka                       ***
 ***                                                                         ***
 *** Wersja: 0.11                                                            ***
 *** Data ostatniej modyfikacji: 13.05.2005                                  ***
 ******************************************************************************/
int tStacja::TworzPociag(int i, int n)
{
  int wartosc;
  int poz=NrPunktu(Rozklad.Wjazd(i,PRZYJAZD));
  if(pkt_postojowe[n][0]==WJAZD_WYJAZD)
     poz=n;
  int nr2=-1;
  if(pkt_postojowe[poz][5]%2)
  {//lewy wjazd
    int r=Rozklad.NumerWRozkladzie(i,PRZYJAZD); //odnosnik do rozkladu
    if(pkt_postojowe[n][0]==WJAZD_WYJAZD && mijanka[n][1]!=-1)
      r=i;
    bool awaria=false;
    bool kopiuj=true;
    if(Rozklad.Opoznienie(r,NIEOKRESLONA)>=120) awaria=true;
    int p;
    for(p=DLUGOSC_POSTOJOWYCH-1;p>=0;)
    {
      Rozklad.Stan(r,NIEOKRESLONA,WJEZDZA);
      if(Rozklad.TypPociagu(r,NIEOKRESLONA)==POWROT_LOKA)
      { 
        stan_postojowych[poz][0].Tworz(-1/*r*/,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false,RUSZA);
        nr2=Rozklad.Wjazd(r,NIEOKRESLONA);//Rozklad.Wjazd(i,PRZYJAZD);
        wartosc=-NrPunktu(Rozklad.Wjazd(r,NIEOKRESLONA));
        Rozklad.PowrotLoka(r,NIEOKRESLONA);
        kopiuj=false;
        //wartosc=-1;//-poz-1;
        //wartosc=NrPunktu(Rozklad.Wjazd(r,NIEOKRESLONA));
        break;
      }
      else if(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)<0 || Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD))>2 || Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD))==0)
      {// sklad z lokiem
        if(p==DLUGOSC_POSTOJOWYCH-1)
        {
          if(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)<0)
          { // trakcja podwojna
            int t=Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)*(-1);
            int s=Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD)*(-1);
            stan_postojowych[poz][p].Tworz(r,t/1000,Rozklad.NumerTypu(t/1000),s/1000,!awaria,false,RUSZA);//****
            p--;
            t=t-t/1000*1000;
            s=s-s/1000*1000;
            stan_postojowych[poz][p].Tworz(r,t,Rozklad.NumerTypu(t),s,!awaria,false);//,RUSZA);//****
            p--;
          }
          else
          {
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false,RUSZA);//****
            p--;
          }
        }
        else
        {// tworzenie wagonow
          int typ_wagonu=Rozklad.RodzajWagonu(r,NIEOKRESLONA);
          if(Rozklad.CzyRozlaczenie(r,NIEOKRESLONA))
          {
            stan_postojowych[poz][p].Tworz(r,typ_wagonu,0,0,true/*,true*/);
            r=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA)/10;
            p--;
            int temp=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA);
            if((temp-(temp/10)*10)==1)
              break;
          }
          else
          {
            stan_postojowych[poz][p].Tworz(r,typ_wagonu,0,0);
            p--;
            break;
          }
        }
      }
      else
      {//sklad nierozlaczalny
        if(Rozklad.CzyRozlaczenie(r,NIEOKRESLONA))
        {
          if(p==DLUGOSC_POSTOJOWYCH-1)
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false,RUSZA); //***
          else
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false);
          r=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA)/10;
          p--;
          int temp=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA);
          if((temp-(temp/10)*10)==1)
            break;
        }
        else
        {
          if(p==DLUGOSC_POSTOJOWYCH-1)
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false,RUSZA);
          else
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false);
          p--;
          break;
        }
        awaria=false;
      }
    }
    Rozklad.KasowaniePrzejscia(r);
    //kopiowanie pociagu w lewo
    if(kopiuj)
    {
      p++;
      int k;
      for(k=0;k<DLUGOSC_POSTOJOWYCH && p<DLUGOSC_POSTOJOWYCH;k++,p++)
      {
        stan_postojowych[poz][k].Kopiuj(&stan_postojowych[poz][p]);
        stan_postojowych[poz][k].Polaczenie(true);
      }
      stan_postojowych[poz][k-1].Polaczenie(false);
      wartosc=k-1;
/*      int jednostka=Zegar.Jednostka();
      stan_postojowych[poz][k-1].Czas(pkt_postojowe[poz][1]*60/jednostka);
      if (!stan_postojowych[poz][k-1].Czas())
        stan_postojowych[poz][k-1].Czas(1); //zabazpieczenie dla wjazdow bez okreslonego wyprzedzenia
      Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Rozklad.DodajCzas(Zegar.Godzina(),Wyprzedz(n)));*/
    }
  }
  else
  {//prawy wjazd
    int r=Rozklad.NumerWRozkladzie(i,PRZYJAZD); //odnosnik do rozkladu
    if(pkt_postojowe[n][0]==WJAZD_WYJAZD && mijanka[n][1]!=-1)
      r=i;
    bool awaria=false;
    if(Rozklad.Opoznienie(r,NIEOKRESLONA)>=120) awaria=true;
    int p;
    for(p=0;p<DLUGOSC_POSTOJOWYCH;)
    {
      Rozklad.Stan(r,NIEOKRESLONA,WJEZDZA);
      if(Rozklad.TypPociagu(r,NIEOKRESLONA)==POWROT_LOKA)
      {
        stan_postojowych[poz][0].Tworz(-1/*r*/,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false,RUSZA);
        nr2=Rozklad.Wjazd(r,NIEOKRESLONA);//Rozklad.Wjazd(i,PRZYJAZD);
        wartosc=-NrPunktu(Rozklad.Wjazd(r,NIEOKRESLONA));
        Rozklad.PowrotLoka(r,NIEOKRESLONA);
        //wartosc=-1;//-poz-1;

        break;
      }
      else if(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)<0 || Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD))>2 || Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD))==0)
      {// sklad z lokiem
        if(p==0)
        {
          if(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)<0)
          { //trakcja podwojna
            int t=Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)*(-1);
            int s=Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD)*(-1);
            stan_postojowych[poz][p].Tworz(r,t/1000,Rozklad.NumerTypu(t/1000),s/1000,!awaria,true,RUSZA);
            p++;
            t=t-t/1000*1000;
            s=s-s/1000*1000;
            stan_postojowych[poz][p].Tworz(r,t,Rozklad.NumerTypu(t),s,!awaria,true);//,RUSZA);
            p++;
          }
          else
          {
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,true,RUSZA);
            p++;
          }
        }
        else
        {// tworzenie wagonow
          int typ_wagonu=Rozklad.RodzajWagonu(r,NIEOKRESLONA);
          if(Rozklad.CzyRozlaczenie(r,NIEOKRESLONA))
          {
            stan_postojowych[poz][p].Tworz(r,typ_wagonu,0,0,true,true);
            r=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA)/10;
            p++;
            int temp=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA);
            if((temp-(temp/10)*10)==1)
              break;
          }
          else
          {
            stan_postojowych[poz][p].Tworz(r,typ_wagonu,0,0);
            p++;
            break;
          }
        }
      }
      else
      {//sklad nierozlaczalny
        if(Rozklad.CzyRozlaczenie(r,NIEOKRESLONA))
        {
          if(p==0)
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,true,RUSZA);
          else
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,true);
          r=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA)/10;
          p++;
          int temp=Rozklad.CzyRozlaczenie(r,NIEOKRESLONA);
          if((temp-(temp/10)*10)==1)
            break;
        }
        else
        {
          if(p==0)
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false,RUSZA);
          else
            stan_postojowych[poz][p].Tworz(r,Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(r,NIEOKRESLONA,PRZYJAZD)),Rozklad.Szopa(r,NIEOKRESLONA,PRZYJAZD),!awaria,false);
          p++;
          break;
        }
        awaria=false;
      }
    }
    stan_postojowych[poz][--p].Polaczenie(false);
    if(wartosc>0)
      wartosc=0;
/*    int jednostka=Zegar.Jednostka();
    stan_postojowych[poz][0].Czas(pkt_postojowe[poz][1]*60/jednostka);
    if (!stan_postojowych[poz][0].Czas())
      stan_postojowych[poz][0].Czas(1); //zabazpieczenie dla wjazdow bez okreslonego wyprzedzenia
    Rozklad.GodzinaRzeczywista(r,NIEOKRESLONA,PRZYJAZD,Rozklad.DodajCzas(Zegar.Godzina(),Wyprzedz(n)));*/
    Rozklad.KasowaniePrzejscia(r);
  }
  int nr;
  if(nr2>-1)
    nr=nr2;
  else
  {
    if(pkt_postojowe[n][0]==WJAZD_WYJAZD)
      nr=pkt_postojowe[n][2];
    else
      nr=Rozklad.Wjazd(i,PRZYJAZD);
  }
  stan[nr/100][nr%100]=POLE_ZAREZERWOWANE;//POLE_ZAJETE;
  return wartosc;
}

/*******************************************************************************
 *** Funkcja sluzy do wczytania stacji z pliku.                              ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  nazwa_pliku - nazwa pliku do wczytania                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  0 - OK                                                                 ***
 ***  1 - blad otwarcia strumienia                                           ***
 ***  2 - zle czasy na wjezdzie_wyjezdzie                                    ***
 ***  3 - brak lokomotywowni                                                 ***
 ***  4 - zle parametry lokomotywowni                                        ***
 ***                                                                         ***
 *** Wersja: 0.20                                                            ***
 *** Data ostatniej modyfikacji: 06.04.2006                                  ***
 ******************************************************************************/
int tStacja::Wczytaj(const char *nazwa)
{
  Lokomotywownia.Reset();
  ifstream plik;
  plik.open(nazwa);
  if(!plik.good()) return 1;
  int wersja;
  plik>>wersja;
  plik.ignore();
  plik>>wysokosc;
  plik.ignore(1);
  plik>>szerokosc;
  plik.ignore(1);
  obraz.tworz(wysokosc,szerokosc);        
  stan.tworz(wysokosc,szerokosc);
  int i,j;
  /* Wyzerowanie odpowiednich struktur */
  for(i=0;i<wysokosc;i++)
  {
    for(j=0;j<szerokosc;j++)
    {
      stan[i][j]=POLE_WOLNE;
    }
  }
   for(i=0;i<wysokosc;i++)
   {
      for(j=0;j<szerokosc;j++)
      {
      	plik>>obraz[i][j];
        plik.ignore(1);  
      }
   }
   plik>>ilosc_tras;
   plik.ignore(1);
   trasa.tworz(ilosc_tras,MAX_DLUGOSC_TRASY);
   for(int i=0;i<ilosc_tras;i++)
   {
     for(int j=0;j<MAX_DLUGOSC_TRASY;j++)
       trasa[i][j]=0;
   }
   for(int i=0;i<ilosc_tras;i++)
   {
     plik>>trasa[i][0];
     plik.ignore(1);
     plik>>trasa[i][1];
     plik.ignore(1);
     for(int j=3;j<MAX_DLUGOSC_TRASY;j++)
     {
       plik>>trasa[i][j];
       plik.ignore(1);
       if(trasa[i][j]==0) //koniec danej trasy
       {
         trasa[i][2]=trasa[i][j-1];
         j=MAX_DLUGOSC_TRASY;
       }
     }
   }
   plik>>ilosc_postojowych;
   plik.ignore();
   plik>>dlugosc_bocznic;
   plik.ignore();
   pkt_postojowe.tworz(ilosc_postojowych,DLUGOSC_PUNKTU+1);
   mijanka.tworz(ilosc_postojowych,ROZMIAR_MIJANKI+1);
   for(int i=0;i<ilosc_postojowych;i++)
     for(int j=0;j<=ROZMIAR_MIJANKI;j++)
       mijanka[i][j]=-1;
   stan_postojowych.tworz(ilosc_postojowych+dlugosc_bocznic,DLUGOSC_POSTOJOWYCH);
   for(int i=0;i<ilosc_postojowych;i++)
     for(int j=0;j<DLUGOSC_PUNKTU+1;j++)
     {
       plik>>pkt_postojowe[i][j];
       plik.ignore();
     }
   bool szopa=false;
   int param;
   int jednostka;
   plik>>jednostka;
   jednostka=Zegar.Jednostka(jednostka);
   plik.ignore(1);
   for(int i=0; i<ilosc_postojowych;i++)
   {
     if(pkt_postojowe[i][0]==WJAZD_WYJAZD)
     {
       int odstep=pkt_postojowe[i][1]/100;
       int mijanki=pkt_postojowe[i][1]%100;
       if(!odstep || !mijanki) return 2;
       if(odstep*10<mijanki) return 2;
       int cz=odstep;
       int jednostka=Zegar.Jednostka();
       for(int j=0;j<ROZMIAR_MIJANKI;j+=3)
       {
         if(cz<mijanki)
         {
           mijanka[i][j]=0;
           mijanka[i][j+1]=0;
           if(cz+odstep<=mijanki)
             mijanka[i][j+2]=odstep*60/jednostka;
           else
             mijanka[i][j+2]=(mijanki-cz)*60/jednostka;
           cz+=odstep;
         }
         else
           break;
       }
     }
     else if(pkt_postojowe[i][0]==LOKOWNIA)
     {
       szopa=true;
       //wjazdy nie moga sie znajdowac na poczatku punktow postojowych
       int t;
       for(int b=0;b<=DLUGOSC_PUNKTU;b++)
       {
         t=pkt_postojowe[0][b];
         pkt_postojowe[0][b]=pkt_postojowe[i][b];
         pkt_postojowe[i][b]=t;
       }
     }
   }
   if(!szopa) return 3;
   plik>>param;
   plik.ignore(1);
   if(param<1) return 4;
   Lokomotywownia.Parametry(POJEMNOSC,param);
   plik>>param;
   plik.ignore(1);
   if(param<1) return 4;
   Lokomotywownia.Parametry(NAPRAWIANYCH_JEDNOCZESNIE,param);
   plik>>param;
   plik.ignore(1);
   if(param<1) return 4;
   Lokomotywownia.Parametry(CZAS_ZAMAWIANIA,param*60/jednostka-2);
   plik>>param;
   if(param<1) return 4;
   Lokomotywownia.Parametry(CZAS_NAPRAWY,param*60/jednostka);
   plik.close();
   return 0;
}

/*******************************************************************************
 *** Funkcja wczytuje stacje i rozklad oraz tworzy pociagi,                  ***
 *** ktore juz sa na stacji.                                                 ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***   nazwa_pliku - nazwa pliku                                             ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   0 - OK                                                                ***
 ***   1 - Blad                                                              ***
 ***   4 - Blad w opisie laczenia/rozlaczania                                ***
 ***   5 - blad w czasach dla wjazdu_wyjazdu                                 ***
 ***   6 - brak lokomotywowni                                                ***
 ***   7 - zle parametry lokomotywowni                                       ***
 ***   8 - nieprawidlowe wspolrzedne                                         ***
 ***   9 - brak wolnych miejsc                                               ***
 ***  10 - blad w ustawieniu lokow                                           ***
 ***  11 - blad w ustawieniu wagonow                                         ***
 ***  12 - w danym punkcie moze stac tylko jeden lok                         ***
 ***                                                                         ***
 *** Wersja: 0.29                                                            ***
 *** Data ostatniej modyfikacji: 23.04.2006                                  ***
 ******************************************************************************/
int tStacja::WczytajRozklad(char * nazwa_pliku)
{
  ifstream plik;
  plik.open(nazwa_pliku);
  if(!plik.good()) return 1;
  int wersja;
  plik>>wersja;
  if (wersja!=1 && wersja!=2 && wersja!=3) return 2;
  plik.ignore(2);
  char nazwa[25];
  plik.getline(nazwa,20);
  plik.close();
  strcat(nazwa,".stc");
  strcpy(nazwa_pliku_stacji,nazwa);
  int blad=Wczytaj(nazwa);
  if(blad==1) return 3;
  else if(blad==2) return 5;
  else if(blad==3) return 6;
  else if(blad==4) return 7;
  int godzina=Rozklad.Wczytaj(nazwa_pliku, nazwy_rysunkow);
  if(godzina==-1) return 1;
  else if(godzina==-2) return 4;
  else
    Zegar.Ustaw(godzina/100,godzina%100);
  //odczyt i tworzenie lokomotyw
  plik.open(nazwa_pliku);
  if(!plik.good()) return 1;
  int rodzaj,ilosc,ilosc_lokow,szopa,wspolrzedna,pozycja,tor;
  wspolrzedna=0;
  int poz;
  for(poz=0;poz<ilosc_postojowych;poz++)
    if(pkt_postojowe[poz][0]==LOKOWNIA) break;
  Lokomotywownia.UstawBaze(&stan_postojowych[poz][0]);
  plik>>ilosc_lokow;
  plik.ignore(2);
  plik.getline(nazwa,20);
  plik>>ilosc_lokow;
  plik.ignore(1);
  for(;ilosc_lokow>0;ilosc_lokow--)
  {
    plik>>rodzaj;
    plik.ignore(1);
    plik>>ilosc;
    plik.ignore(1);
    plik>>szopa;
    plik.ignore(1);
    if(wersja>1)
    {
      plik>>wspolrzedna;
      plik.ignore(1);
      plik>>pozycja;
      plik.ignore(1);
      plik>>tor;
      plik.ignore(1);
    }
    for(;ilosc>0;ilosc--)
    {
      int polaczenie=false;
      if(wspolrzedna<0)
      {
        polaczenie=true;
        wspolrzedna*=(-1);
      }
      if(!wspolrzedna)
      {//lok w szopie
        int pr=rand()%101;
        if(pr<5 && !CzyGraTestowa())
          stan_postojowych[poz][0].Tworz(0,rodzaj,Rozklad.NumerTypu(rodzaj),szopa,false);
        else
          stan_postojowych[poz][0].Tworz(0,rodzaj,Rozklad.NumerTypu(rodzaj),szopa);
        Lokomotywownia.Przyjmij(&stan_postojowych[poz][0]);
      }
      else
      {//lok stoi gdzies na stacji
        if(pkt_postojowe[NrPunktu(wspolrzedna)][0]!=BOCZNICA)
        {
          if(pkt_postojowe[NrPunktu(wspolrzedna)][0]==PERON || pkt_postojowe[NrPunktu(wspolrzedna)][0]==PERON_TOWAROWY)
          {
            if(stan_postojowych[NrPunktu(wspolrzedna)][pozycja].Rodzaj()!=PUSTY) return 10;
            stan_postojowych[NrPunktu(wspolrzedna)][pozycja].Tworz(0,rodzaj,Rozklad.NumerTypu(rodzaj),szopa,true,polaczenie);
            stan[pkt_postojowe[NrPunktu(wspolrzedna)][2]/100][pkt_postojowe[NrPunktu(wspolrzedna)][2]%100]=POLE_ZAJETE;
            stan[pkt_postojowe[NrPunktu(wspolrzedna)][3]/100][pkt_postojowe[NrPunktu(wspolrzedna)][3]%100]=POLE_ZAJETE;
            stan[pkt_postojowe[NrPunktu(wspolrzedna)][4]/100][pkt_postojowe[NrPunktu(wspolrzedna)][4]%100]=POLE_ZAJETE;
          }
          else if(pkt_postojowe[NrPunktu(wspolrzedna)][0]==PKT_DLA_LOKOMOTYW)
          {
            if(pozycja) return 12;
            if(stan_postojowych[NrPunktu(wspolrzedna)][pozycja].Rodzaj()!=PUSTY) return 10;
            stan_postojowych[NrPunktu(wspolrzedna)][pozycja].Tworz(0,rodzaj,Rozklad.NumerTypu(rodzaj),szopa,true,polaczenie);
            stan[pkt_postojowe[NrPunktu(wspolrzedna)][2]/100][pkt_postojowe[NrPunktu(wspolrzedna)][2]%100]=POLE_ZAJETE;
          }
          else
          {
            if(stan_postojowych[NrPunktu(wspolrzedna)][pozycja].Rodzaj()!=PUSTY) return 10;
            if(pozycja && !stan_postojowych[NrPunktu(wspolrzedna)][pozycja-1].Polaczenie()) return 12;
            stan_postojowych[NrPunktu(wspolrzedna)][pozycja].Tworz(0,rodzaj,Rozklad.NumerTypu(rodzaj),szopa,true,polaczenie);
            stan[pkt_postojowe[NrPunktu(wspolrzedna)][2]/100][pkt_postojowe[NrPunktu(wspolrzedna)][2]%100]=POLE_ZAJETE;
          }
        }
        else
        {//bocznica
          int pozyc=ilosc_postojowych+pkt_postojowe[NrPunktu(wspolrzedna)][5]+tor;
          if(stan_postojowych[pozyc][pozycja].Rodzaj()!=PUSTY) return 10;
          stan_postojowych[pozyc][pozycja].Tworz(0,rodzaj,Rozklad.NumerTypu(rodzaj),szopa,true,polaczenie);
        }
      }
    }
  }
  plik.close();
  //tworzenie pociagow na poczatku gry
  tablica<int> tblpociagow;
  /*    [0] - ma stac na peronie
        [1] - ma stac na torach towarowych
        [2] - ma stac na bocznicy
        [3] - ma stac gdzies na bocznicy
        [4] - ma stac gdzies na torach towarowych */
  tblpociagow.tworz(Rozklad.IloscPociagow()+1,5);
  for(int i=0;i<Rozklad.IloscPociagow()+1;i++)
    for(int j=0;j<5;j++)
      tblpociagow[i][j]=0;
  tblpociagow[0][0]=tblpociagow[0][1]=tblpociagow[0][2]=tblpociagow[0][3]=tblpociagow[0][4]=1;
  for(int i=0;i<Rozklad.IloscPociagow();i++)
  {
    if(Rozklad.Stan(i,NIEOKRESLONA)==JEST)
    {
      if(Rozklad.Wspolrzedna(i))
      {//ma okreslone miejsce
        if(pkt_postojowe[NrPunktu(abs(Rozklad.Wspolrzedna(i)))][0]==PERON)
        {
          tblpociagow[tblpociagow[0][0]][0]=i;
          tblpociagow[0][0]++;
        }
        else if(pkt_postojowe[NrPunktu(abs(Rozklad.Wspolrzedna(i)))][0]==BOCZNICA)
        {
          tblpociagow[tblpociagow[0][2]][2]=i;
          tblpociagow[0][2]++;
        }
        else if(pkt_postojowe[NrPunktu(abs(Rozklad.Wspolrzedna(i)))][0]==PERON_TOWAROWY)
        {
          tblpociagow[tblpociagow[0][1]][1]=i;
          tblpociagow[0][1]++;
        }
        else return 8;
      }
      else if(Rozklad.BocznicaTowarowe())
      {//pozycja losowa, wszystko stoi na torach towarowych
        tblpociagow[tblpociagow[0][4]][4]=i;
        tblpociagow[0][4]++;
      }
      else
      {//pozycja losowa
        if(Rozklad.RodzajTyp(Rozklad.RodzajNumer(i,NIEOKRESLONA))!=TOWAROWY)
        {
          tblpociagow[tblpociagow[0][3]][3]=i;
          tblpociagow[0][3]++;
        }
        else
        {
          tblpociagow[tblpociagow[0][4]][4]=i;
          tblpociagow[0][4]++;
        }
      }
    }
  }
  //Tworzenie pociagow na peronach
  for(int i=1;i<tblpociagow[0][0];i++)
  {
    int poz=NrPunktu(abs(Rozklad.Wspolrzedna(tblpociagow[i][0])));
    bool polacz=false;
    if(Rozklad.Wspolrzedna(tblpociagow[i][0])<0) polacz=true;
    if(stan_postojowych[poz][Rozklad.Pozycja(tblpociagow[i][0])].Rodzaj()==PUSTY)
    {
      if(Rozklad.Lokomotywa(tblpociagow[i][0],NIEOKRESLONA,ODJAZD)>0 && Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][0],NIEOKRESLONA,ODJAZD))<3)
      {//sklad nierozlaczalny
        stan_postojowych[poz][Rozklad.Pozycja(tblpociagow[i][0])].Tworz(tblpociagow[i][0],Rozklad.Lokomotywa(tblpociagow[i][0],NIEOKRESLONA,ODJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][0],NIEOKRESLONA,ODJAZD)),Rozklad.Szopa(tblpociagow[i][0],NIEOKRESLONA,ODJAZD),true,polacz);
      }
      else
      {
        int typ_wagonu=Rozklad.RodzajWagonu(tblpociagow[i][0],NIEOKRESLONA);
        stan_postojowych[poz][Rozklad.Pozycja(tblpociagow[i][0])].Tworz(tblpociagow[i][0],typ_wagonu,0,0,true,polacz);
      }
      stan[pkt_postojowe[poz][2]/100][pkt_postojowe[poz][2]%100]=POLE_ZAJETE;
      stan[pkt_postojowe[poz][3]/100][pkt_postojowe[poz][3]%100]=POLE_ZAJETE;
      stan[pkt_postojowe[poz][4]/100][pkt_postojowe[poz][4]%100]=POLE_ZAJETE;
    }
    else
      return 11;
  }
  //Tworzenie pociagow na torach towarowych
  for(int i=1;i<tblpociagow[0][1];i++)
  {
    int poz=NrPunktu(abs(Rozklad.Wspolrzedna(tblpociagow[i][1])));
    bool polacz=false;
    if(Rozklad.Wspolrzedna(tblpociagow[i][1])<0) polacz=true;
    if(stan_postojowych[poz][Rozklad.Pozycja(tblpociagow[i][1])].Rodzaj()==PUSTY)
    {
      if(Rozklad.Lokomotywa(tblpociagow[i][1],NIEOKRESLONA,ODJAZD)>0 && Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][1],NIEOKRESLONA,ODJAZD))<3)
      {//sklad nierozlaczalny
        stan_postojowych[poz][Rozklad.Pozycja(tblpociagow[i][1])].Tworz(tblpociagow[i][1],Rozklad.Lokomotywa(tblpociagow[i][1],NIEOKRESLONA,ODJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][1],NIEOKRESLONA,ODJAZD)),Rozklad.Szopa(tblpociagow[i][1],NIEOKRESLONA,ODJAZD),true,polacz);
      }
      else
      {
        int typ_wagonu=Rozklad.RodzajWagonu(tblpociagow[i][1],NIEOKRESLONA);
        stan_postojowych[poz][Rozklad.Pozycja(tblpociagow[i][1])].Tworz(tblpociagow[i][1],typ_wagonu,0,0,true,polacz);
      }
      stan[pkt_postojowe[poz][2]/100][pkt_postojowe[poz][2]%100]=POLE_ZAJETE;
      stan[pkt_postojowe[poz][3]/100][pkt_postojowe[poz][3]%100]=POLE_ZAJETE;
      stan[pkt_postojowe[poz][4]/100][pkt_postojowe[poz][4]%100]=POLE_ZAJETE;
    }
    else
      return 11;
  }

  int licznik=0;
  for(int i=0;i<ilosc_postojowych;i++)
    if(pkt_postojowe[i][0]==PERON_TOWAROWY)
      licznik++;
  int *p=new int [licznik];
  licznik=0;
  for(int i=0;i<ilosc_postojowych;i++)
  {
    if(pkt_postojowe[i][0]==PERON_TOWAROWY)
    {
      p[licznik]=i;
      licznik++;
    }
  }
  bool* wolne = new bool [licznik];
  for(int t=0;t<licznik;t++)
    wolne[t]=true;
  for(int i=1;i<tblpociagow[0][4];i++)
  {
    for(int koniec=0;koniec<1000;koniec++)
    {
      int poz;
      for(poz=rand()%(licznik);!wolne[poz];poz=rand()%(licznik));
      for(int h=0;h<3;h++)
      {
        if(stan_postojowych[p[poz]][h].Rodzaj()==PUSTY)
        {
          if(Rozklad.Lokomotywa(tblpociagow[i][4],NIEOKRESLONA,ODJAZD)>0 && Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][4],NIEOKRESLONA,ODJAZD))<3)
          {//sklad nierozlaczalny
            if(Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][4],NIEOKRESLONA,ODJAZD))==1 && obraz[p[poz]/100][p[poz]%100]>=100)
            {//EZT na torze bez drutu
              i--;
              h=3;
            }
            else
              stan_postojowych[p[poz]][h].Tworz(tblpociagow[i][4],Rozklad.Lokomotywa(tblpociagow[i][4],NIEOKRESLONA,ODJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][4],NIEOKRESLONA,ODJAZD)),Rozklad.Szopa(tblpociagow[i][4],NIEOKRESLONA,ODJAZD));
          }
          else
          {
            int typ_wagonu=Rozklad.RodzajWagonu(tblpociagow[i][4],NIEOKRESLONA);
            stan_postojowych[p[poz]][h].Tworz(tblpociagow[i][4],typ_wagonu,0,0);
          }
          stan[pkt_postojowe[p[poz]][2]/100][pkt_postojowe[p[poz]][2]%100]=POLE_ZAJETE;
          stan[pkt_postojowe[p[poz]][3]/100][pkt_postojowe[p[poz]][3]%100]=POLE_ZAJETE;
          stan[pkt_postojowe[p[poz]][4]/100][pkt_postojowe[p[poz]][4]%100]=POLE_ZAJETE;
          if(h==2) wolne[poz]=false;
          h=3;
          koniec=1000;
        }
      }
      if(koniec==999) return 9;
    }
  }

  //Tworzenie pociagow pasazerskich na bocznicach
  for(int i=1;i<tblpociagow[0][2];i++)
  {
    int poz=NrPunktu(abs(Rozklad.Wspolrzedna(tblpociagow[i][2])));
    bool polacz=false;
    if(Rozklad.Wspolrzedna(tblpociagow[i][2])<0) polacz=true;
    //int bocznica;
    //for(bocznica=rand()%pkt_postojowe[poz][1];stan_postojowych[bocznica+pkt_postojowe[poz][5]+ilosc_postojowych][DLUGOSC_POSTOJOWYCH-1].Rodzaj()!=PUSTY;bocznica=rand()%pkt_postojowe[poz][1]);
    int bocznica=pkt_postojowe[poz][5]+ilosc_postojowych+Rozklad.Tor(tblpociagow[i][2]);
    if(stan_postojowych[bocznica][Rozklad.Pozycja(tblpociagow[i][2])].Rodzaj()==PUSTY)
    {
      if(Rozklad.Lokomotywa(tblpociagow[i][2],NIEOKRESLONA,ODJAZD)>0 && Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][2],NIEOKRESLONA,ODJAZD))<3)
      {//sklad nierozlaczalny
        stan_postojowych[bocznica][Rozklad.Pozycja(tblpociagow[i][2])].Tworz(tblpociagow[i][2],Rozklad.Lokomotywa(tblpociagow[i][2],NIEOKRESLONA,ODJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][2],NIEOKRESLONA,ODJAZD)),Rozklad.Szopa(tblpociagow[i][2],NIEOKRESLONA,ODJAZD),true,polacz);
      }
      else
      {
        int typ_wagonu=Rozklad.RodzajWagonu(tblpociagow[i][2],NIEOKRESLONA);
        stan_postojowych[bocznica][Rozklad.Pozycja(tblpociagow[i][2])].Tworz(tblpociagow[i][2],typ_wagonu,0,0,true,polacz);
      }
    }
    else
      return 11;
  }

  for(int i=1;i<tblpociagow[0][3];i++)
  {
    //int poz=NrPunktu(Rozklad.Pozycja(tblpociagow[i][3]));
    int poz;
    int bocznica;
    for(bocznica=rand()%dlugosc_bocznic;stan_postojowych[bocznica+ilosc_postojowych][2].Rodzaj()!=PUSTY;bocznica=rand()%dlugosc_bocznic);
    bocznica+=ilosc_postojowych;
    //sprawdzenie czy tory sa z trakcja
    for(int z=0;z<ilosc_postojowych;z++)
    {
      if(pkt_postojowe[z][0]==BOCZNICA)
      {
        if(pkt_postojowe[z][5]<=bocznica-ilosc_postojowych && pkt_postojowe[z][5]+pkt_postojowe[z][1]>bocznica-ilosc_postojowych)
        {
          poz=z;
          z=ilosc_postojowych;
        }
      }
    }

    for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      if(stan_postojowych[bocznica][j].Rodzaj()==PUSTY)
      {
        if(Rozklad.Lokomotywa(tblpociagow[i][3],NIEOKRESLONA,ODJAZD)>0 && Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][3],NIEOKRESLONA,ODJAZD))<3)
        {//sklad nierozlaczalny
          if(Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][3],NIEOKRESLONA,ODJAZD))==1 && obraz[pkt_postojowe[poz][2]/100][pkt_postojowe[poz][2]%100]>=100)
          {//EZT na torze bez drutu
            i--;
            j=DLUGOSC_POSTOJOWYCH;
          }
          else
            stan_postojowych[bocznica][j].Tworz(tblpociagow[i][3],Rozklad.Lokomotywa(tblpociagow[i][3],NIEOKRESLONA,ODJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(tblpociagow[i][3],NIEOKRESLONA,ODJAZD)),Rozklad.Szopa(tblpociagow[i][3],NIEOKRESLONA,ODJAZD));
        }
        else
        {
          int typ_wagonu=Rozklad.RodzajWagonu(tblpociagow[i][3],NIEOKRESLONA);
          stan_postojowych[bocznica][j].Tworz(tblpociagow[i][3],typ_wagonu,0,0);
        }
        j=DLUGOSC_POSTOJOWYCH;
      }
/*      else
      {
        if(j+1>=DLUGOSC_POSTOJOWYCH) i--;
      }*/
    }
  }
  //zalatanie ewentualnych dziur w ustawieniu
  for(int i=0;i<ilosc_postojowych+dlugosc_bocznic;i++)
  {
    int zajeta=0;
    for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      if(stan_postojowych[i][j].Rodzaj()!=PUSTY)
      {
        zajeta++;
      }
      else
      {
        for(int p=j;p<DLUGOSC_POSTOJOWYCH;p++)
        {
          if(stan_postojowych[i][p].Rodzaj()!=PUSTY)
          {
            //if(zajeta>0) stan_postojowych[i][zajeta-1].Polaczenie(false);
            stan_postojowych[i][zajeta].Kopiuj(&stan_postojowych[i][p]);
            p=DLUGOSC_POSTOJOWYCH;
            zajeta++;
          }
        }
      }
    }
    if(zajeta>0) stan_postojowych[i][zajeta-1].Polaczenie(false);
  }


  /*//tworzenie pociagow pasazerskich
  bool* wolne=new bool[dlugosc_bocznic];
  for(int i=0;i<dlugosc_bocznic;i++)
    wolne[i]=true;
  for(int i=0;i<Rozklad.IloscPociagow();i++)
  {
    if(Rozklad.Stan(i,NIEOKRESLONA)==JEST && Rozklad.RodzajNumer(i,NIEOKRESLONA)!=TOWAROWY)
    {
      int poz;
      for(poz=rand()%dlugosc_bocznic;!wolne[poz];poz=rand()%dlugosc_bocznic);
      wolne[poz]=false;
      if(Rozklad.Lokomotywa(i,NIEOKRESLONA,ODJAZD)>0 && Rozklad.NumerTypu(Rozklad.Lokomotywa(i,NIEOKRESLONA,ODJAZD))<3)
      {//sklad nierozlaczalny
        stan_postojowych[poz+ilosc_postojowych][0].Tworz(i,Rozklad.Lokomotywa(i,NIEOKRESLONA,ODJAZD),Rozklad.NumerTypu(Rozklad.Lokomotywa(i,NIEOKRESLONA,ODJAZD)),Rozklad.Szopa(i,NIEOKRESLONA,ODJAZD));
      }
      else
      {
        int typ_wagonu=Rozklad.RodzajWagonu(i,NIEOKRESLONA);
        stan_postojowych[poz+ilosc_postojowych][0].Tworz(i,typ_wagonu,0,0);
      }
    }
  }
  delete [] wolne;
  wolne=0;
  int licznik=0;
  for(int i=0;i<ilosc_postojowych;i++)
    if(pkt_postojowe[i][0]==PERON_TOWAROWY)
      licznik++;
  int *p=new int [licznik];
  licznik=0;
  for(int i=0;i<ilosc_postojowych;i++)
  {
    if(pkt_postojowe[i][0]==PERON_TOWAROWY)
    {
      p[licznik]=i;
      licznik++;
    }
  }
  wolne = new bool [licznik];
  for(int t=0;t<licznik;t++)
    wolne[t]=true;

  for(int i=0;i<Rozklad.IloscPociagow();i++)
  {
    if(Rozklad.Stan(i,NIEOKRESLONA)==JEST && Rozklad.RodzajNumer(i,NIEOKRESLONA)==TOWAROWY && licznik)
    {
      int poz;
      for(poz=rand()%(licznik);!wolne[poz];poz=rand()%(licznik));
      wolne[poz]=false;
      int typ_wagonu=Rozklad.RodzajWagonu(i,NIEOKRESLONA);;
      stan_postojowych[p[poz]][0].Tworz(i,typ_wagonu,0,0);
      stan[pkt_postojowe[p[poz]][2]/100][pkt_postojowe[p[poz]][2]%100]=POLE_ZAJETE;
      stan[pkt_postojowe[p[poz]][3]/100][pkt_postojowe[p[poz]][3]%100]=POLE_ZAJETE;
      stan[pkt_postojowe[p[poz]][4]/100][pkt_postojowe[p[poz]][4]%100]=POLE_ZAJETE;
    }
  }
  delete [] wolne;
  delete [] p;*/
  return 0;
}

/*******************************************************************************
 *** Funkcja sluzy do wczytania stanu gry.                                   ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  nazwa_pliku - nazwa pliku do wczytania                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  0 - OK                                                                 ***
 ***  1 - blad otwarcia strumienia                                           ***
 ***  2 - stara wersja pliku                                                 ***
 ***                                                                         ***
 *** Wersja: 0.12                                                            ***
 *** Data ostatniej modyfikacji: 02.07.2005                                  ***
 ******************************************************************************/
int tStacja::WczytajStan(char *nazwa)
{
  ifstream plik;
  plik.open(nazwa);     
  if(!plik.good()) return 1;
  int wersja;
  plik>>wersja;
  plik.ignore(1);
  if(wersja<2) return 2;
  char nazwa2[39];
  plik.getline(nazwa2,30);
  plik.close();
  int blad=Wczytaj(nazwa2);
  if(blad==1) return 1;
  //strcat(nazwa2,".stc");
  strcpy(nazwa_pliku_stacji,nazwa2);
  Lokomotywownia.Load(nazwa);
  int poz;
  for(poz=0;poz<ilosc_postojowych;poz++)
    if(pkt_postojowe[poz][0]==LOKOWNIA) break;
  Lokomotywownia.UstawBaze(&stan_postojowych[poz][0]);
  plik.open(nazwa);
  if(!plik.good()) return 1;
  int tmp, tmp1;
  plik>>tmp;
  plik.ignore(1);
  plik.getline(nazwa2,39);
//  plik.ignore(2);
  plik>>tmp;
  plik>>tmp;
  for(int i=0;i<5;i++)
    plik>>tmp1;
  for(int i=0;i<tmp;i++)
    for(int j=0;j<12;j++)
      plik>>tmp1;
  //wczytanie tablicy stan
  for(int i=0; i<wysokosc;i++)
    for(int j=0;j<szerokosc;j++)
    {
      plik>>stan[i][j];
      if(stan[i][j]==WYBOR_TRASY)
        stan[i][j]=POLE_WOLNE;
      else if(stan[i][j]==WYBOR_TRASY_POCIAG)
        stan[i][j]=POLE_ZAJETE;
      plik.ignore(1);
    }
  //wczytanie tablicy stan_postojowych
  for(int i=0;i<ilosc_postojowych+dlugosc_bocznic;i++)
  {
    for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      plik>>tmp;stan_postojowych[i][j].Rozklad(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Rodzaj(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Typ(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Numer(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Sprawnosc(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Polaczenie(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Ruch(tmp);plik.ignore(1);
      plik>>tmp;plik.ignore(1);
      if(tmp)
      {
        int *t=new int[MAX_DLUGOSC_TRASY];
        t[0]=tmp;
        for(int k=1;k<MAX_DLUGOSC_TRASY;k++)
        {
          plik>>tmp;plik.ignore(1);
          t[k]=tmp;
          if(!tmp) break;
        }
        stan_postojowych[i][j].Trasa(t);
      }
      //stan_postojowych[i][j].Trasa(NULL);
      plik>>tmp;stan_postojowych[i][j].Czas(tmp);plik.ignore(1);
      plik>>tmp;stan_postojowych[i][j].Bocznica(tmp);plik.ignore(1);
    }
  }
  plik>>tmp;
  plik.ignore(1);
  plik>>tmp1;
  plik.ignore(1);
  Zegar.Ustaw(tmp/100,tmp%100,tmp1);
  plik>>tmp;
  plik.ignore(1);
  Przejscia(tmp);
  plik>>tmp;
  plik.ignore(1);
  Rozklad.IloscRysunkow(tmp);
  for (int i=1;i<=tmp;i++)
     for (int j=0;j<DLUGOSC_NAZWY_PLIKU;j++)
       if((nazwy_rysunkow[i][j]=plik.get())=='\n')
       {
          nazwy_rysunkow[i][j]=NULL;
	  break;
       }
    for(int i=0;i<ilosc_postojowych;i++)
    for(int j=0;j<=ROZMIAR_MIJANKI;j++)
    {
      plik>>mijanka[i][j];
      plik.ignore(1);
    }
  streampos pozycja=plik.tellg();
  plik.close();
  Rozklad.WczytajStan(pozycja,nazwa);
  return 0;
}

/*******************************************************************************
 *** Funkcja sluzy do zwracania parametrow wjazdow i wyjazdow.               ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  w - numer kolejny wjazdu                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  dla w =0 - ilosc wjazdow i wyjazdow                                    ***
 ***  dla w<>0 - rodzaj-numer-wyprzedzenie-odstep-czas do mijanki            ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 10.05.2003                                  ***
 ******************************************************************************/
long tStacja::WjazdWyjazd(int w)
{
  if(!w)
  {//licze ilosc punktow
    int ilosc=0;
    for(int i=0;i<ilosc_postojowych;i++)
    {
      if(pkt_postojowe[i][0]<=WJAZD_WYJAZD)
        ilosc++;
    }
    return ilosc;
  }
  else
  {//zwracam parametry konkretnego punktu
    int ilosc=0;
    for(int i=0;i<ilosc_postojowych;i++)
    {
      if(pkt_postojowe[i][0]<=WJAZD_WYJAZD)
        ilosc++;
      if(w==ilosc)
      {
        long p=pkt_postojowe[i][0]+(pkt_postojowe[i][5]/10)*10+pkt_postojowe[i][3]*100+pkt_postojowe[i][1]*1000;
        return p;
      }
    }
  }
  return 0;
}

/*******************************************************************************
 *** Funkcja zwraca odpowiedni punkt konca trasy (dla peronow).              ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  z - wspolrzedne punktu poczatku trasy                                  ***
 ***  do - wspolrzedne punktu konca trasy                                    ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  Wspolrzedna konca trasy                                                ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 03.07.2001                                  ***
 ******************************************************************************/
int tStacja::Wspolrzedna(int z, int _do)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    for(int j=2;j<DLUGOSC_PUNKTU;j++)
    {
      if(pkt_postojowe[i][j]==_do)
      {
        z=z-(z/100)*100;
        _do=_do-(_do/100)*100;
        int p;
        if(z<_do) p=pkt_postojowe[i][2];
        else p=pkt_postojowe[i][4];
        p=p-(p/100)*100;
        return p;
      }
    }
  }
  return 0;
}
/*******************************************************************************
 *** Funkcja zwraca wspolrzedna dla wjazdu.                                  ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  numer - numer wjazdu/wyjazdu                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  Wspolrzedna wjazdu/wyjazdu                                             ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 19.11.2003                                  ***
 ******************************************************************************/
int tStacja::WspWjazd(int numer)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    if((pkt_postojowe[i][0]==WJAZD_WYJAZD||pkt_postojowe[i][0]==WJAZD) && pkt_postojowe[i][5]/10==numer)
      return pkt_postojowe[i][2];
  }
  return -1;
}

/*******************************************************************************
 *** Funkcja zwraca wspolrzedna dla wjazdu/wyjazdu.                          ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  numer - numer wjazdu/wyjazdu                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  Wspolrzedna wjazdu/wyjazdu                                             ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 11.05.2003                                  ***
 ******************************************************************************/
int tStacja::WspWjazdu(int numer)
{
  for(int i=0;i<ilosc_postojowych;i++)
  {
    if(pkt_postojowe[i][0]==WJAZD_WYJAZD && pkt_postojowe[i][5]/10==numer)
      return pkt_postojowe[i][2];
  }
  return -1;
}

/* ================================================================== *
 * Funkcja WszystkieTrasy
 * ------------------------------------------------------------------
 * Przeznaczenie:
 * Pomocnicza dla Zaznacz.
 * Zaznacza wszystkie mozliwe tras miedzy dwoma punktami;
 * Funkcja ta nie powinna byc wywolywana bezposrednio; nalezy wywolywac
 * funkcje Zaznacz z dwoma parametrami (punktami miedzy ktorymi ma
 * byc trasa.
 * ------------------------------------------------------------------
 * Mozliwe wywolania i zwracane wartosci:
 *   WszystkieTrasy(a,b) - powoduje zaznaczenie wszystkich tras miedzy a i b
 *     BRAK_TRASY (?) - gdy nie ma trasy miedzy zadanymi punktami
 *     OK (?)
 *
 * ------------------------------------------------------------------
 * Data ostatniej modyfikacji: 2 lipca 2001
 * Wersja: 1.PF
 * ================================================================== */
int tStacja::WszystkieTrasy(int poczatek, int koniec, int elek)
{
  int i,j,wiersz,kolumna;
  int jest=0;
  int dobra,byla_zla=0;
  int moze_byc;

  for(i=0;i<ilosc_tras;i++)
  {
    //if((trasa[i][2]==poczatek && trasa[i][1]==koniec) ||
    // (trasa[i][1]==poczatek && trasa[i][2]==koniec && trasa[i][0]==1))
    moze_byc=0;
    if(elek==ELEKTRYCZNA)
    {
      if((trasa[i][3]==poczatek && trasa[i][2]==koniec && trasa[i][1]==ELEKTRYCZNA) ||
        (trasa[i][2]==poczatek && trasa[i][3]==koniec && trasa[i][0]==1 && trasa[i][1]==ELEKTRYCZNA))
      {
        moze_byc=1;
      }
    }
    else
    {
      if((trasa[i][3]==poczatek && trasa[i][2]==koniec) ||
        (trasa[i][2]==poczatek && trasa[i][3]==koniec && trasa[i][0]==1))
      {
        moze_byc=1;
      }
    }

    if(moze_byc==1)
    {
      dobra=1;
      for(j=2;j<MAX_DLUGOSC_TRASY;j++)
      {
        kolumna=trasa[i][j] % 100;
        wiersz=(trasa[i][j]-kolumna)/100;
        if(stan[wiersz][kolumna]==POLE_ZAREZERWOWANE)
        {
          byla_zla=1;
          dobra=0;
          break;
        }
        if(stan[wiersz][kolumna]==POLE_ZAJETE  && trasa[i][j]!=koniec && trasa[i][j]!=poczatek)
        {
          byla_zla=1;
          dobra=0;
          break;
        }
      }

      if(dobra==1)
      {
        jest++;
        for(j=2;j<MAX_DLUGOSC_TRASY;j++)
        {
          if(trasa[i][j]==0)
	       break;
    	  kolumna=trasa[i][j] % 100;
          wiersz=(trasa[i][j]-kolumna)/100;

          if(stan[wiersz][kolumna]!=POLE_ZAJETE)
            stan[wiersz][kolumna]=WYBOR_TRASY;
          else if(stan[wiersz][kolumna]==POLE_ZAJETE && trasa[i][j]==koniec)
            stan[wiersz][kolumna]=WYBOR_TRASY;
        }
      }
    }
  }

  if(jest==0)
  {
    if(byla_zla==1)
      return  TRASY_ZAJETE;
    else
      return  BRAK_TRASY;
  }

  kolumna=poczatek % 100;
  wiersz=(poczatek-kolumna)/100;
  stan[wiersz][kolumna]=WYBOR_TRASY_POCIAG;
  return OK;
}

/*******************************************************************************
 *** Funkcja podaje wyprzedzenie dla danego wjazdu lub wyjazdu. Uwzglednia   ***
 *** rowniez wyprzedzenie zwiazane z inteligentna zajetoscia punktow.        ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  pozycja - pozycja wjazdu                                               ***
 ***  mijanka - czy wywolanie dotyczy mijanki                                ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  wyprzedzenie                                                           ***
 ***                                                                         ***
 *** Wersja: 0.05                                                            ***
 *** Data ostatniej modyfikacji: 12.04.2003                                  ***
 ******************************************************************************/
int tStacja::Wyprzedz(int pozycja, bool mijanka)
{
  if(mijanka)
    return pkt_postojowe[pozycja][3]+pkt_postojowe[pozycja][1]/100;
  else if(pkt_postojowe[pozycja][0]==WJAZD)
    return pkt_postojowe[pozycja][3]+pkt_postojowe[pozycja][1];
  else if(pkt_postojowe[pozycja][0]==WJAZD_WYJAZD)
    return pkt_postojowe[pozycja][3]+pkt_postojowe[pozycja][1]%100;
  else
    return 0;
}

/*******************************************************************************
 *** Funkcja sluzy do zapisania stanu gry.                                   ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  nazwa_pliku - nazwa pliku do zapisania                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  0 - OK                                                                 ***
 ***  1 - blad otwarcia strumienia                                           ***
 ***                                                                         ***
 *** Wersja: 0.13                                                            ***
 *** Data ostatniej modyfikacji: 07.04.2006                                  ***
 ******************************************************************************/
int tStacja::ZapiszStan(char *nazwa)
{
  ofstream plik;
  plik.open(nazwa);
  plik<<4<<endl;  // wersja pliku z gra
  plik.write(nazwa_pliku_stacji,29);
  plik<<endl;
  plik.close();
  //lokomotywownia
  Lokomotywownia.Save(nazwa);
//  ofstream plik;
  plik.open(nazwa, ios_base::app);
  if(!plik.good()) return 1;
  //wyglad stacji
  for(int i=0;i<wysokosc;i++)
  {
    for(int j=0;j<szerokosc;j++)
    {
      plik<<stan[i][j]<<",";
    }
    plik<<endl;
  }
  //pociagi
  for(int i=0;i<ilosc_postojowych+dlugosc_bocznic;i++)
  {
    for(int j=0;j<DLUGOSC_POSTOJOWYCH;j++)
    {
      plik<<stan_postojowych[i][j].Rozklad()<<",";
      plik<<stan_postojowych[i][j].Rodzaj()<<",";
      plik<<stan_postojowych[i][j].Typ()<<",";
      plik<<stan_postojowych[i][j].Numer()<<",";
      plik<<stan_postojowych[i][j].Sprawnosc()<<",";
      plik<<stan_postojowych[i][j].Polaczenie()<<",";
      plik<<stan_postojowych[i][j].Ruch()<<",";
      for(int k=0;;k++)
      {
        int tmp=stan_postojowych[i][j].Trasa(k);
        plik<<tmp<<",";
        if(!tmp) break;
      }
      plik<<stan_postojowych[i][j].Czas()<<",";
      plik<<stan_postojowych[i][j].Bocznica()<<",";
      plik<<endl;
    }
  }
  //aktualna godzina
  plik<<Zegar.Godzina()<<","<<Zegar.Sekundy()<<","<<endl;
  plik<<przejscia<<","<<endl;
  //tablica z nazwami plikow taboru
  plik<<Rozklad.IloscRysunkow()<<endl;
  for(int i=1;i<=Rozklad.IloscRysunkow();i++)
  {
    plik.write(nazwy_rysunkow[i],DLUGOSC_NAZWY_PLIKU);
//    plik<<endl;
  }
  plik<<endl;
  for(int i=0;i<ilosc_postojowych;i++)
  {
    for(int j=0;j<=ROZMIAR_MIJANKI;j++)
      plik<<mijanka[i][j]<<",";
    plik<<endl;
  }
  plik.close();
  return Rozklad.ZapiszRozklad(nazwa);
}

/* ================================================================== *
 * Funkcja Zaznacz (przeciazona)
 * ------------------------------------------------------------------
 * Przeznaczenie:
 * Zaznaczanie, anulowanie tras. Przechowuje poczatek i koniec trasy
 * ------------------------------------------------------------------
 * Mozliwe wywolania i zwracane wartosci:
 *   Zaznacz() - powoduje anulowanie tras
 *     Zawsze zwraca OK (?)
 *
 *   Zaznacz(a,b) - powoduje zaznaczenie wszystkich tras miedzy a i b
 *     BRAK_TRASY (?) - gdy nie ma trasy miedzy zadanymi punktami
 *     OK (?)
 *
 *   Zaznacz(DAJ_POCZATEK / DAJ_KONIEC) - zwraca poczatek lub koniec
 *     ostatnio zanaczanej trasy
 *
 *   Funkcja zwraca wartosc BLAD (?) jesli zdazy sie cos nieprzewidzianego.
 * ------------------------------------------------------------------
 * Data ostatniej modyfikacji: 5 lipca 2001
 * Wersja: 2.PF
 * ================================================================== */
int tStacja::Zaznacz(int p1, int p2, int elek)
{
  static int poczatek,koniec;

  if(p1==-1 && p2==-1)
  {
    return Anuluj();
  }
  else if(p1>-1 && p2>-1)
  {
    poczatek=p1;
    koniec=p2;

    return WszystkieTrasy(p1,p2,elek);
  }
  else if(p1==DAJ_POCZATEK)
  {
    return poczatek;
  }
  else if(p1==DAJ_KONIEC)
  {
    return koniec;
  }

  return BLAD;
}

/* ================================================================== *
 * Funkcja Zaznacz (przeciazona)
 * ------------------------------------------------------------------
 * Przeznaczenie:
 * Zatwierdza trase (wczesniej nalezy wywolac Zaznacz(poczatek_trasy,
 * koniec_trasy) aby wiadomo bylo wsrod jakich tras szukac)
 * ------------------------------------------------------------------
 * Mozliwe wywolania i zwracane wartosci:
 *   Zatwierdz(wsk, a) - powoduje zatwierdzenie trasy z punktem posrednim a
 *   i wpisanie jej do jakiejs tablicy pod wskanikiem wsk
 *     BRAK_TRASY (?) - miedzy wczesniej zadanymi punktami nie ma trasy
 *       przechodzacej przez zadany punkt
 *     BRAK_JEDNOZNACZNOSCI (?) podany punkt nie identyfikuje jednonacznie
 *       trasy
 *     PKT_NIE_NALEY (?) gdy wskazany pkt nie nalezy do zadnej z moliwych
 *       do wyboru tras
 *     OK (?)
 *
 * ------------------------------------------------------------------
 * Data ostatniej modyfikacji: 5 lipca 2001
 * Wersja: 2.PF
 * ================================================================== */
int tStacja::Zaznacz(tObiektRuchomy * wsk, int pkt, int elek)
{
  int i,j,k; // iteratory dla for-ow
  int wiersz,kolumna; // wsp punkt z tras
  int gdzie; // gdzie w tablicy z trasami jest dobra trasa
  int poczatek,koniec; // poczatek i koniec trasy
  int cala_wybor; // gdy cala trasa spelniajaca kryteria poczatku i srodka,
                  // faktycznie jast zaznaczona do wyboru
  int pkt_nalezy; // gdy pkt nalezy do trasy o poczatku poczatek i koncu koniec
  int * tablica;
  int jest=0; // ilosc tras spelniajacych zadane warunki
  int moze_byc;


  kolumna=pkt % 100;
  wiersz=(pkt-kolumna)/100;
  if(stan[wiersz][kolumna]!=WYBOR_TRASY)
  {
    return BRAK_TRASY;
    // wskazany pkt nie nalezy do trasy lub nalezy do trasy, ktora nie moze byc
    // aktywowana (np. przebirgala by przez zarezerwowane pola)
  }

  poczatek=Zaznacz(DAJ_POCZATEK);
  koniec=Zaznacz(DAJ_KONIEC);

  for(i=0;i<ilosc_tras;i++) // petla po wszystkich trasach
  {
    //if((trasa[i][2]==poczatek && trasa[i][1]==koniec) ||
      // (trasa[i][1]==poczatek && trasa[i][2]==koniec && trasa[i][0]==1))




    moze_byc=0;
    if(elek==ELEKTRYCZNA)
    {
      if((trasa[i][3]==poczatek && trasa[i][2]==koniec && trasa[i][1]==ELEKTRYCZNA) ||
        (trasa[i][2]==poczatek && trasa[i][3]==koniec && trasa[i][0]==1 && trasa[i][1]==ELEKTRYCZNA))
      {
        moze_byc=1;
      }
    }
    else
    {
      if((trasa[i][3]==poczatek && trasa[i][2]==koniec) ||
        (trasa[i][2]==poczatek && trasa[i][3]==koniec && trasa[i][0]==1))
      {
        moze_byc=1;
      }
    }

    if(moze_byc==1)
    {
      pkt_nalezy=0;
      cala_wybor=1;

      for(j=2;j<MAX_DLUGOSC_TRASY;j++)
      {
        if(trasa[i][j]==0)
        {
          if(pkt_nalezy==1 && cala_wybor==1)
            gdzie=i;
          break;
        }
        if(trasa[i][j]==pkt)
        {
          pkt_nalezy=1;
	}
        kolumna=trasa[i][j] % 100;
        wiersz=(trasa[i][j]-kolumna)/100;

        if(stan[wiersz][kolumna]!=WYBOR_TRASY && trasa[i][j]!=poczatek && trasa[i][j]!=koniec)
          cala_wybor=0;
      }

      if(pkt_nalezy==1 && cala_wybor==1)
        jest++;
    }
  }

  if(jest==0)
  {
    return BRAK_TRASY;
  }
  else if(jest==1)
  {
    for(j=2;j<MAX_DLUGOSC_TRASY;j++)
    {
      if(trasa[gdzie][j]==0)
      {
        tablica=new int [MAX_DLUGOSC_TRASY];

        for(k=0;k<MAX_DLUGOSC_TRASY;k++)
          tablica[k]=0;

        if(trasa[gdzie][3]==poczatek && trasa[gdzie][2]==koniec)
        {
          j--;
          for(k=0;j>2;j--,k++)
          {
            tablica[k]=trasa[gdzie][j];
          }
        }
        else
        {
          for(k=3;k<j;k++)
          {
            tablica[k-3]=trasa[gdzie][k];
          }
        }
        wsk->Trasa(tablica);
        wsk->Ruch(RUSZA);

        break;
      }
      kolumna=trasa[gdzie][j] % 100;
      wiersz=(trasa[gdzie][j]-kolumna)/100;

      if(stan[wiersz][kolumna]==WYBOR_TRASY_POCIAG)
        stan[wiersz][kolumna]=POLE_ZAJETE;
      if(stan[wiersz][kolumna]!=POLE_ZAJETE)
        stan[wiersz][kolumna]=POLE_ZAREZERWOWANE;
    }
    Anuluj();
    return OK;
  }
  else if(jest>1)
  {
    return BRAK_JEDNOZNACZNOSCI;
  }

  return OK; // to po to by nie bylo warning-ow
}

/*******************************************************************************
 *** Funkcja sprawdza, czy mozna zaczac zaznaczanie tras miedzy dwoma        ***
 *** punktami.                                                               ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***   poczatek - poczatek trasy                                             ***
 ***   koniec - koniec trasy                                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***   tekst komunikatu o bledzie                                            ***
 ***   NULL - gdy wszystko jest OK                                           ***
 ***                                                                         ***
 *** Wersja: 0.18                                                            ***
 *** Data ostatniej modyfikacji: 04.08.2002                                  ***
 ******************************************************************************/
char* tStacja::Zaznaczanie(int poczatek, int koniec, int p_k)
{
  char *komunikat=0;
 // int p_x=poczatek/100;
  int p_y=poczatek%100;
 // int k_x=koniec/100;
  int k_y=koniec%100;
  int poz_p=NrPunktu(poczatek);
  int poz_k=NrPunktu(koniec);

  if (poczatek==koniec)
  {
    komunikat="Wskazano dwa razy ten sam punkt";
    return komunikat;
  }
  /*sprawdzam czy jest miejsce w punkcie docelowym*/
  if(p_k!=-1)
  {
    if(k_y<p_y)
      stan_postojowych[poz_k][0].Bocznica(p_k);
    else
      stan_postojowych[poz_k][0].Bocznica(-p_k);
    if(!Miejsce(p_k,poz_p,p_y,k_y))
    {
      komunikat="Brak wolnego miejsca w punkcie docelowym";
      return komunikat;
    }
  }
  else
  {
    if(!Miejsce(poz_k, poz_p,p_y,k_y))
    {
      komunikat="Brak wolnego miejsca w punkcie docelowym";
      return komunikat;
    }
  }
  /*sprawdzam czy pociag sie porusza*/
  if(CzyJedzie(poz_p,poczatek))
  {
    komunikat="Ten poci¹g jeszcze jedzie";
    return komunikat;
  }
/*  if(p_k!=-1)
  {
    if(k_y<p_y)
      stan_postojowych[poz_k][0].Bocznica(p_k);
    else
      stan_postojowych[poz_k][0].Bocznica(-p_k);
    if(!Miejsce(p_k,poz_p,p_y,k_y))
    {
      strcpy(komunikat,"Brak wolnego miejsca w punkcie docelowym");
      return komunikat;
    }
  }*/
  if(pkt_postojowe[poz_k][0]==LOKOWNIA)
  {
    if(!CzyLokomotywa(poz_p,p_y,k_y,poczatek))
    {
      komunikat="Tylko pojedyñcza lokomotywa mo¿e pojechaæ do lokomotywowni";
      return komunikat;
    }
  }
  if(pkt_postojowe[poz_k][0]==PKT_DLA_LOKOMOTYW)
  {
    if(!CzyLokomotywa(poz_p,p_y,k_y,poczatek))
    {
      komunikat="Tylko pojedyñcza lokomotywa mo¿e wjechaæ na ten punkt";
      return komunikat;
    }
  }

  //dla wyjazdu ze stacji
  if(/*(pkt_postojowe[poz_p][0]==PERON || pkt_postojowe[poz_p][0]==PERON_TOWAROWY || pkt_postojowe[poz_p][0]==WJAZD_WYJAZD || pkt_postojowe[poz_p][0]==WJAZD)
        && */(pkt_postojowe[poz_k][0]==WYJAZD || pkt_postojowe[poz_k][0]==WJAZD_WYJAZD))
  {
    switch(CzyPrzod(poz_p,poczatek))
    {
      case 1:
        komunikat="Brak lokomotywy na pocz¹tku sk³adu";
        return komunikat;
      case 2:
        komunikat="Sama lokomotywa nie mo¿e opuœciæ stacji";
        return komunikat;
      case 3:
        komunikat="Jednostka musi siê znajdowaæ na pocz¹tku sk³adu";
        return komunikat;
      case 4:
        komunikat="Lokomotywa musi siê znajdowaæ na pocz¹tku sk³adu";
        return komunikat;
      case 5:
        komunikat="Nieprawid³owa kolejnoœæ wagonów w sk³adzie";
        return komunikat;
      case 6:
        komunikat="Nieprawid³owe zestawienie sk³adu";
        return komunikat;
      case 7:
        komunikat="Za du¿o lokomotyw pod³aczono do sk³adu";
        return komunikat;
      case 8:
        komunikat="Za ma³o lokomotyw pod³aczono do sk³adu";
        return komunikat;
      case 9:
        komunikat="Lokomotywa pochodzi z niew³aœciwej lokomotywowni";
        return komunikat;
      case 10:
        komunikat="Lokomotywa pochodzi z w³aœciwej lokomotywowni, ale ma niew³aœciwy typ";
        return komunikat;
    }
    //sprawdzenie poprawnosci punktu wyjazdowego
    if(!CzyDobryPunkt(poz_p,poczatek, koniec))
    {
      komunikat="Z³y punkt wyjazdowy dla tego poci¹gu";
      return komunikat;
    }
    //czy nie za wczesnie na zaznaczenie trasy
    if(!CzyPunktualnie(poz_p,poczatek))
    {
      komunikat="Za wczeœnie na zaznaczenie wyjazdu";
      return komunikat;
    }
    if(CzyPostuj(poz_p))
    {
      komunikat="Pociag musi sie zatrzymac przy peronie";
      return komunikat;
    }

  }

  if(pkt_postojowe[poz_p][0]==PERON || pkt_postojowe[poz_p][0]==PERON_TOWAROWY)
  {//czy lokomotywa uszkodzona nie ciagnie skladu
    if(pkt_postojowe[poz_p][2]==poczatek)
    {
      if(!stan_postojowych[poz_p][0].Sprawnosc() && stan_postojowych[poz_p][0].Polaczenie())
      {
        komunikat="Uszkodzona lokomotywa nie mo¿e ci¹gn¹æ sk³adu.";
        return komunikat;
      }
      if(!stan_postojowych[poz_p][0].Sprawnosc() && stan_postojowych[poz_p][0].Typ()<3)
      {
        komunikat="Uszkodzona jednostka nie mo¿e siê samodzielnie poruszaæ.";
        return komunikat;
      }
    }
    else
    {
      int i;
      for(i=0;i<DLUGOSC_POSTOJOWYCH && stan_postojowych[poz_p][i].Rodzaj()!=PUSTY;i++);
      i--;
      if(i>0)
      {
        if(!stan_postojowych[poz_p][i].Sprawnosc() && stan_postojowych[poz_p][i-1].Polaczenie())
        {
          komunikat="Uszkodzona lokomotywa nie mo¿e ci¹gn¹æ sk³adu.";
          return komunikat;
        }
      }
      if(!stan_postojowych[poz_p][i].Sprawnosc() && stan_postojowych[poz_p][i].Typ()<3)
      {
        komunikat="Uszkodzona jednostka nie mo¿e siê samodzielnie poruszaæ.";
        return komunikat;
      }
    }
    //czy sklad moze juz zjechac z peronu
    if(!CzyMoznaZjechac(poz_p,poczatek))
    {
      komunikat="Ten poci¹g musi postaæ 5 min. przy peronie.";
      return komunikat;
    }
  }
  //sprawdzenie czy trwa laczenie/rozlaczanie
  if(CzyManewry(poz_p,p_y,k_y))
  {
    komunikat="Trwa ³¹czenie/roz³¹czanie";
    return komunikat;
  }
  //dla wjazdu na stacje
  if(pkt_postojowe[poz_p][0]==WJAZD || pkt_postojowe[poz_p][0]==WJAZD_WYJAZD)
  {
    if(pkt_postojowe[poz_k][0]==PERON_TOWAROWY && !CzyTowarowy(poz_p))
    {
      komunikat="Poci¹g pasa¿erski nie mo¿e wjechaæ na tory towarowe";
      return komunikat;
    }
  }
  return NULL;
}



