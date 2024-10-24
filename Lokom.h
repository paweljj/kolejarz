#ifndef _LOKOM
#define _LOKOM

#include "obiekt.h"

#define ZEPSUTA 1
#define NAPRAWIANA 2
#define SPRAWNA 3 
#define GOTOWA 4
#define ZAMOWIONA 5
#define WOLNE 6
#define ZAJETE 7
#define OK 0 //8
#define BRAK_MIEJSCA 9
#define BRAK 10
#define CHWILOWY_BRAK 11
#define TAK 1
#define NIE 0
#define POJEMNOSC 14
#define CZAS_NAPRAWY 15
#define CZAS_ZAMAWIANIA 16
#define NAPRAWIANYCH_JEDNOCZESNIE 17
#define NIEZNANY_PARAMETR (-1)
#define BLAD_PAMIECI 18
#define NIE_JEST_GOTOWA 19
#define GOTOWYCH 20

class opis_obiektu
{
  public:
  tObiektRuchomy obiekt;
  int stan; // jedno z powyzszych
  int czas; //
  int status; // czy dane pole z obiektem jest wolne
};

class pole_raportu
{
  public:
  tObiektRuchomy *obiekt;
  int stan;
  int czas;
};

class tRaport
{
  public:
  int zepsutych;
  int naprawianych;
  int sprawnych;
  int gotowych;
  int zamowionych;
  int dl;// ile pol z pola jest waznych
  pole_raportu * pola;
};

class tLokomotywownia
{
private:
int max_pojemnosc;
int obecna_ilosc;
int max_naprawianych_jednoczesnie;
int naprawianych_jednoczesnie;
int czas_zamawiania;
int czas_naprawy;
int mozna_wystawic;
tObiektRuchomy *baza;//tutaj kopiowac wydawane lokomotywy
opis_obiektu *stan; // lista przechowujaca lokomotywy
opis_obiektu *temp01;
float * temp02;
tRaport moj_raport;
void Sortuj(void);

public:
 tLokomotywownia(void);
 ~tLokomotywownia(void);
 int Przyjmij(tObiektRuchomy * co);
 int Zamow(int typ, int numer);
 int Parametry(int parametr, int wartosc);
 void Reset(void);
 void Aktualizuj(void);
 int CzyJestMiejsce(void);
 int Daj(int typ, int numer);
 tRaport * DajRaport(void);
 void UstawBaze(tObiektRuchomy *wsk);
 void MoznaWystawic(int a);
 void Save(char * nazwa);
 void Load(char * nazwa);
};

#endif

 
