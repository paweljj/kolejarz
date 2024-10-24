#include "Inne.h"
#include <math.h>
/*******************************************************************************
 *** Konstruktor klasy czas.                                                 ***
 *** Parametry:                                                              ***
 ***  h - godzina                                                            ***
 ***  m - minuty                                                             ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :26.03.2000                                  ***
 ******************************************************************************/
tCzas::tCzas(int h,int m)
{
  if (!Ustaw(h,m))
  {
    godz=0;
    min=0;
    sek=0;
  }
  jednostka=10;
}/*czas::czas*/

/*******************************************************************************
 *** Funkcja podaje aktualny czas w formie liczby calkowitej.                ***
 *** Zwraca:                                                                 ***
 ***  godz*100+min - aktualny czas                                           ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :26.03.2000                                  ***
 ******************************************************************************/
int tCzas::Godzina(void)
{
  return godz*100+min;
}/*czas::godzina*/

/*******************************************************************************
 *** Zmienia (odmierza) czas.                                                ***
 ***                                                                         ***
 *** FUNKCJA RZUCA WYJATEK W MOMENCE ROZPOCZECIA NASTEPNEJ DOBY              ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji :11.08.2001                                  ***
 ******************************************************************************/
void tCzas::Odmierz(void) throw(int)
{
   sek+=jednostka;
   if (sek>=60)
   {
   	min++;
      sek=fabs(60-sek);
   }
   if (min==60)
   {
   	godz++;
      min=0;
   }
   if (godz==24)
   {
   	godz=0;
        throw 1;
   }
}/*czas::odmierz*/

/*******************************************************************************
 *** Funkcja podaje liczbe sekund.                                           ***
 *** Zwraca:                                                                 ***
 ***  liczbe sekund                                                          ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :26.03.2000                                  ***
 ******************************************************************************/
int tCzas::Sekundy(void)
{
  return sek;
}/*czas::sekundy*/

/*******************************************************************************
 *** Funkcja ustawia zegar.                                                  ***
 *** Parametry:                                                              ***
 ***  h - godzina                                                            ***
 ***  m - minuty                                                             ***
 ***  s - sekundy                                                            ***
 *** Zwraca:                                                                 ***
 ***  0 - podana liczbe nie mozna zapisac jako czas                          ***
 ***  1 - ustawiono nowy czas                                                ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :26.03.2000                                  ***
 ******************************************************************************/
int tCzas::Ustaw(int h,int m, int s)
{
   if (h>=0 && h<=24 && m>=0 && m<=59)
   {
      godz=h;
      min=m;
      sek=s;
      return 1;
   }
   else
   	return 0;
}/*czas::ustaw*/

/*******************************************************************************
 *** Funkcja ustawia/zwraca jednostke taktowania.                            ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  j - nowa jednostka                                                     ***
 ***                                                                         ***
 *** Zwraca wartosc:                                                         ***
 ***  nowa jednostka                                                         ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :11.08.2001                                  ***
 ******************************************************************************/
int tCzas::Jednostka(int j)
{
  if(j<=0) return jednostka;
  if(!(60%j))
    jednostka=j;
  else
    jednostka=10;
  return jednostka;
}
