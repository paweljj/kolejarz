#ifndef _OBIEKT
#define _OBIEKT

/*******************************************************************************
 *** Klasa reprezentuje lokiomotywy i wagony.                                ***
 ***                                                                         ***
 *** Wersja: 0.14                                                            ***
 *** Data ostatniej modyfikacji: 21.04.2003                                  ***
 ******************************************************************************/
class tObiektRuchomy
{
#define NIEOKRESLONA -100

  int rozklad; //odnosnik do rozkladu
  int rodzaj; // wagon/lok danego typu
  #define ELEKTRYCZNA 1
  #define SPALINOWA 0
  #define PUSTY 0

  int typ;   /* 0 - wagon
                1 - EZT
                2 - autobus szynowy
                3 - lok elektryczny
                4 - lok spalinowy
                5 - parowoz*/
  int numer; // szopa loka/typ wagonu
  bool sprawnosc; // lok zepsuty/sprawny
  bool polaczenie; // czy polaczony z obiektem na prawo
  int ruch; //czy sie rusza
  #define JEDZIE 1
  #define RUSZA 2
  #define STOI 0
  int* trasa;
  int czas;
  int bocznica;
  #define CZAS_LACZENIA 60
  #define CZAS_LACZENIA_LOKA 180
  #define CZAS_ROZLACZENIA 60

public:
  tObiektRuchomy(void);

  int Bocznica(int i=0);
  int Czas(int c=-1);
  int KoniecTrasy(void);
  void Kopiuj(tObiektRuchomy *skad);
  int Numer(int n=0);
  int Odcinek(void);
  int PoczatekTrasy(void);
  bool Polaczenie(int p=-1);
  int Pozycja(void);
  int Rodzaj(int r=0);
  int Rozklad(int r=-1);
  int Ruch(int r=-1);
  bool Sprawnosc(int spr=NIEOKRESLONA);
  void Trasa(int *t);
  int Trasa(int i);
  void Tworz(int ro,int r,int t,int nr, bool spr=true, bool pol=false,int ru=STOI);
  int Typ(int r=0);
  int TypLoka(void);

};


#endif
