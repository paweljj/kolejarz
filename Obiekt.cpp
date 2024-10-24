#include "Obiekt.h"

/*******************************************************************************
 *** Konstruktor obiektu.                                                    ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 11.12.2001                                  ***
 ******************************************************************************/
tObiektRuchomy::tObiektRuchomy(void)
{
  rozklad=0;
  rodzaj=PUSTY;
  numer=0;
  sprawnosc=true;
  polaczenie=false;
  ruch=false;
  trasa=0;
  czas=0;
  bocznica=0;
  typ=0;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/ustawienia wjazdu na bocznice.              ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  i - nowy numer                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer wjazdu na bocznice                                               ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 24.07.2001                                  ***
 ******************************************************************************/

int tObiektRuchomy::Bocznica(int i)
{
  if(i!=0)
    bocznica=i;
  return bocznica;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/ustawienia czasu.                           ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  c - nowy czas                                                          ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  czas                                                                   ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 21.04.2003                                  ***
 ******************************************************************************/
int tObiektRuchomy::Czas(int c)
{
  if(c>-1)
    czas =c;
  return czas;
}

/*******************************************************************************
 *** Funkcja zwraca koniec trasy dla pociagu.                                ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  ostatni odcinek w trasie                                               ***
 **   0 - brak wpisanej trasy                                                ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 10.07.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::KoniecTrasy(void)
{
  if(trasa)
  {
    return trasa[0];
  }
  else
    return 0;
}

/*******************************************************************************
 *** Funkcja kopiuje pociagi.                                                ***                                                                         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  skad - skad ma byc przekopiowany pociag                                ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 24.07.2001                                  ***
 ******************************************************************************/
void tObiektRuchomy::Kopiuj(tObiektRuchomy *skad)
{
  rozklad=skad->rozklad;
  rodzaj=skad->rodzaj;
  typ=skad->typ;
  numer=skad->numer;
  sprawnosc=skad->sprawnosc;
  polaczenie=skad->polaczenie;
  ruch=skad->ruch;
  trasa=skad->trasa;
  czas=skad->czas;
  skad->rozklad=0;
  skad->trasa=0;
  skad->rodzaj=PUSTY;
  skad->typ=0;
  skad->numer=0;
  skad->czas=0;
  skad->sprawnosc=true;
  skad->polaczenie=false;
  skad->ruch=false;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/ustawienia numeru loka.                     ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  n - numer loka                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer loka                                                             ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 04.07.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Numer(int n)
{
  if(n==0) return numer;
  else
  {
    numer=n;
    return n;
  }
}

/*******************************************************************************
 *** Funkcja skraca trase do przejechania wraz z poruszaniem sie pociagu.    ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  odcinek w trasie                                                       ***
 ***  0 - koniec trasy                                                       ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 24.07.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Odcinek(void)
{
  int i;
  for(i=0;;i++)
  {
    if(trasa[i]==0) break;
  }
  if(i==1) //koniec trasy
  {
    ruch=STOI;
    //int t=trasa[i-1];
    delete [] trasa;
    trasa=0;
    return 0 /*t*/;
  }
  else
  {
    i--;
    trasa[i]=0;
    return trasa[i-1];
  }
}

/*******************************************************************************
 *** Funkcja zwraca poczatek trasy dla pociagu.                              ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  pierwszy odcinek w trasie                                              ***
 **   0 - brak wpisanej trasy                                                ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 14.07.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::PoczatekTrasy(void)
{
  if(trasa)
  {
    for(int i=0;;i++)
    {
      if(trasa[i]==0)
        return trasa[i-1];
    }
  }
  else
    return 0;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/zapisania czy obiekt jest polaczony         ***
 *** z innym.                                                                ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  polaczenie                                                             ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 02.08.2001                                  ***
 ******************************************************************************/
bool tObiektRuchomy::Polaczenie(int p)
{
  if(p!=-1)
    polaczenie=p;
  return this->polaczenie;
}

/*******************************************************************************
 *** Funkcja zwraca aktualna pozycje jadacego pociagu.                       ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  odcinek w trasie                                                       ***
 ***  0 - koniec trasy                                                       ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 04.07.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Pozycja(void)
{
  int i;
  for(i=0;;i++)
  {
    if(trasa[i]==0)
      return trasa[i-1];
  }
  //return 0;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/ustawienia pola rodzaj.                     ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  r - rodzaj obiektu lok/wagon                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj obiektu                                                         ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 01.10.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Rodzaj(int r)
{
  if(r==0) return rodzaj;
  else
  {
    if(r>0)
    {
      rodzaj=r;
      return r;
    }
  }
  return PUSTY;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/ustawienia pola rozklad.                    ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  r - odnosnik do wiersza w rozkladzie                                   ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  odnosnik do rozkladu (dla wagonu)                                      ***
 ***  -1 dla lokomotywy                                                       ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 02.08.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Rozklad(int r)
{
  if(r==-1)
  {
    if(rodzaj>=100)//LOK)
      return -1;
    else
      return rozklad;
  }
  else if(rodzaj<100)//LOK)
  {
    rozklad=r;
    return rozklad;
  }
  else
    return -1;

}

/*******************************************************************************
 *** Funkcja sluzy do odczytania czy lok sie rusza.                          ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  ruch                                                                   ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 01.10.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Ruch(int r)
{
  if(r<0)
  {
    if(Typ()>0) return ruch;
    else return STOI;
  }
  else if(Typ()>0)
  {
    ruch=r;
    return ruch;
  }
  else
    return STOI;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/zapisu sprawnosci loka.                     ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***    spr - nowa sprawnosc                                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  sprawnosc loka                                                         ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 30.07.2001                                  ***
 ******************************************************************************/
bool tObiektRuchomy::Sprawnosc(int spr)
{
  if(spr!=NIEOKRESLONA)
    sprawnosc=spr;
  return sprawnosc;
}

/*******************************************************************************
 *** Funkcja sluzy do zapisania trasy dla pociagu.                           ***                                                                         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  t - wskaznik do tablicy z trasa                                        ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 04.07.2001                                  ***
 ******************************************************************************/
void tObiektRuchomy::Trasa(int *t)
{
  delete trasa;
  trasa=t;
}

/*******************************************************************************
 *** Funkcja sluzy do pobierania kolejnych odcinkow z trasy.                 ***                                                                         ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  i - numer odcinka w trasie                                             ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 01.08.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Trasa(int i)
{
  if(trasa)
    return trasa[i];
  else
    return 0;
}

/*******************************************************************************
 *** Funkcja tworzy pociagi.                                                 ***                                                                         ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  ro - rozklad                                                           ***
 ***  r - rodzaj                                                             ***
 ***  t - typ                                                                ***
 ***  nr - numer                                                             ***
 ***  spr - sprawnosc                                                        ***
 ***  pol - polaczenie                                                       ***
 ***  ru - ruch                                                              ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 01.10.2001                                  ***
 ******************************************************************************/
void tObiektRuchomy::Tworz(int ro,int r,int t,int nr, bool spr, bool pol,int ru)
{
  rozklad=ro;
  rodzaj=r;
  typ=t;
  numer=nr;
  sprawnosc=spr;
  polaczenie=pol;
  ruch=ru;
}

/*******************************************************************************
 *** Funkcja sluzy do odczytania/ustawienia pola typ.                        ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  r - typ                                                                ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  typ obiektu                                                            ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 01.10.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::Typ(int r)
{
  if(r==0) return typ;
  else
  {
    if(r>0)
    {
      typ=r;
      return r;
    }
  }
  return 0;
}


/*******************************************************************************
 *** Funkcja zwraca typ lokomotywy (elektryczna/spalinowa)                   ***                                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  typ loka                                                               ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 01.10.2001                                  ***
 ******************************************************************************/
int tObiektRuchomy::TypLoka(void)
{
  if(typ==1 || typ==3)
    return ELEKTRYCZNA;
  else
    return SPALINOWA;
}
