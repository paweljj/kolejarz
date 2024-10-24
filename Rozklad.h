#ifndef _ROZKLAD
#define _ROZKLAD

#include "Struktury.h"
#include <fstream.h>


/*******************************************************************************
 *** Klasa reprezentuje rozklad jazdy pociagow.                              ***
 ***                                                                         ***
 *** Wersja: 0.44                                                            ***
 *** Data ostatniej modyfikacji: 14.07.2005                                  ***
 ******************************************************************************/
class tRozklad
{
  int ilosc_pociagow;
  bool bocznica_towarowe; //jezeli true, to tory towarowe i bocznice sa traktowane tak samo przy ustawianiu skladow 
  #define SZEROKOSC 28
  tablica<int> rozklad;  //rozklad wczytany z pliku
  /*    [0] - typ pociagu */
  #define POCIAG_PRZELOTOWY 2
  #define POCIAG_ZE_STACJI 1
  #define POCIAG_DOCELOWY 0
  #define POCIAG_ROZLACZANY 3
  #define POCIAG_DOCELOWY_ROZLACZANY 4
  #define POCIAG_BEZ_ZATRZYMANIA 5
  #define POCIAG_ZE_STACJI_LACZONY 6
  #define POWROT_LOKA 7
  #define POLNOC 2400
  /*    [1] - planowa godzina przyjazdu
        [2] - numer punktu wjazdowego
        [3] - wskaznik do opisu skad przyjechal
        [4] - rodzaj lokomotywy
        [5] - planowa godzina odjazdu
        [6] - numer punktu wyjazdowego
        [7] - wskaznik do opisu dokad odjezdza
        [8] - rodzaj lokomotywy wyjazdowej
        [9] - numer pociagu wjezdzajacego
        [10] - numer pociagu wyjezdzajacego
        [11] - czy bedzie rozlaczany i gdzie jest opis drugiej czesci
        [12] - czy bedzie laczony i z ktorym pociagiem
        [13] - rodzaj pociagu przyjezdzajacego*/
 /* #define TOWAROWY 0
  #define SKM 1
  #define OSOBOWY 2
  #define WKD 3
  #define POSPIESZNY 4
  #define EXPRES 6
  #define INTERCITY 8
  #define EUROCITY 10
  #define HOTELOWY 12
  #define NEX 13
  #define POCZTOWY 14
  #define BAGAZOWY 16
  #define EURONIGHT 18
  #define SLUZBOWY 20
  #define REGIO_PLUS 22
  #define REGIO_N 24

  #define NIEM_SKM 102
  #define NIEM_OSOBOWY 103
  #define NIEM_POSPIESZNY 104
  #define NIEM_EXPRES 106
  #define NIEM_EUROCITY 110
  #define NIEM_INTERCITY 108

  #define FR_COR 204
  #define FR_EUROSTAR 206
  #define FR_TER 202
  #define FR_TGV 208
  #define FR_TDN 212 */
  /*    [14] - rodzaj pociagu wyjezdzajacego
        [15] - stan pociagu */
  #define JEST 1
  #define BYL -1
  #define BEDZIE 0
  #define CZEKA_NA_WJAZD 2
  #define CZEKA_NA_WYJAZD 3
  #define WJEZDZA 4
  /*    [16] - rodzaj wagonu
        [17] - odnosnik do skladu
        [18] - peron wjazdowy
        [19] - peron wyjazdowy
        [20] - nazwa przyjazd
        [21] - nazwa odjazd
        [22] - wspolrzedna na poczatku gry
        [23] - pozycja na poczatku gry
        [24] - tor w grupie torow postojowych na poczatku gry
        [25]
        [26] - rzeczywista godzina przyjazdu
        [27] - rzeczywista godzina odjazdu  */
  #define NIEOKRESLONA -100

  int ilosc_stacji;
  tablica<char> nazwa; //tablica z nazwami stacji
  #define MAX_NAZWA 30

  tablica<int> odjazd;   //rozklad posortowany wzgledem godz. odjazdu
  tablica<int> przyjazd; //rozklad posortowany wzgledem godz. przyjazdu
  #define PRZYJAZD 2
  #define ODJAZD 1

  int ilosc_skladow;
  tablica<int> sklady;  //zestawienia wagonow dla kazdego skladu
  #define DLUGOSC_SKLADU 30

  int ilosc_nazw_szop;
  tablica<char> nazwa_szopy;

  int ilosc_przejsc;
  #define DLUGOSC_PRZEJSC 7
  tablica<int> przejscia;
  /*    [0] - nazwa loka
        [1] - indeks szopy
        [2] - indeks pociagu przyjazd
        [3] - indeks pociagu odjazd
        [4] - numer tablicy prawdopodobienstw
        [5] - nazwa loka niewlasciwego
        [6] - zapasowa nazwa loka
  */

  int ilosc_nazw_lokow;
  int ilosc_prawdopodobienstw;
  tablica<int> prawdopodobienstwa;
  tablica<int> hierarchia_lokow;

  int ilosc_nazw_pociagow;
  tablica<char> nazwa_pociagu;

  int wyprzedzenie;  //wyprzedzenie z jakim jest oglaszane opoznienie pociagu
  int plusminus[6][2];
  int typ_rodzaju_pociagu[250]; //powiazanie miedzy typem (IC) a rodzajem (Kwalifikowany)
  #define PODMIEJSKI 0
  #define OSOBOWY 1
  #define POSPIESZNY 2
  #define KWALIFIKOWANY 3
  #define TOWAROWY 4
  #define SPECJALNY 5
  char nazwa_typ_rodzaju_pociagu[250][2][4]; //skrót 3 literowy, skrót 1 literowy

  #define ILOSC_RYSUNKOW 300
  char nazwa_typu [ILOSC_RYSUNKOW][20]; //nazwy typow lokow
  int numer_typu [ILOSC_RYSUNKOW];       //numer typu lokow
  int ilosc_rysunkow;

  bool gra_testowa;

  void Sortuj(int a);

public:
  tRozklad(void);

  int BocznicaTowarowe(void){return bocznica_towarowe;};
  bool CzyGraTestowa(void){return gra_testowa;};
  int CzyLaczenie(int pozycja, int rodzaj);
  bool CzyPodglad(void){return ilosc_skladow;};
  int CzyRozlaczenie(int pozycja, int rodzaj);
  bool CzyZmianaLoka(int pozycja, int rodzaj, bool przejscia);
  int DodajCzas(int t1, int t2);
  int Dokad(int pozycja);
  char* Dokad(int pozycja, int rodzaj);
  int Godzina(int pozycja, int rodzaj, int godzina, int ustaw=NIEOKRESLONA);
  int GodzinaRzeczywista(int pozycja, int rodzaj, int godzina, int ustaw=-1);
  void GraTestowa(bool gra){gra_testowa=gra;};
  int IloscPociagow(void){return ilosc_pociagow;};
  int IloscPociagowWTrakcjiPodwojnej(int rodzaj,int ograniczenie);
  int IloscRysunkow(int il=-1){if(il==-1)return ilosc_rysunkow;else{ilosc_rysunkow=il;return il;}};
  void KasowaniePrzejscia(int pozycja);
  void KorygowaniePrzejscia(int pozycja, int lok, int dwa=0);
  int Lok(int pozycja, int rodzaj);
  int Lokomotywa(int pozycja, int rodzaj, int punkt);
  char* NazwaPociagu(int pozycja, int rodzaj, int godzina);
  char* NazwaRodzajTyp(int pozycja, int rodzaj);
  const char* NazwaTypu(int i){return nazwa_typu[i];};
  void NowaDoba(void);
  char* Numer(int pozycja, int rodzaj, int godzina);
  int NumerCzesci(int pozycja, int rodzaj);
  int NumerTypu(int i){return numer_typu[i];};
  int NumerWRozkladzie(int pozycja, int rodzaj, bool laczenie=false);
  int Opoznienie(int pozycja, int rodzaj, int opoznienie=0, int godzina=NIEOKRESLONA);
  int Opoznienie(int czas);
  int Peron(int pozycja, int rodzaj, int godzina);
  int PlusMinus(int x, int y, int wartosc=NIEOKRESLONA);
  int * Podglad(int nr);
  void PowrotLoka(int odnosnik, int lok, int wjazd=NIEOKRESLONA);
  int Pozycja(int nr);
  int Przejscia(int x, int y){return abs(przejscia[x][y]);};
  char* Rodzaj(int pozycja, int rodzaj);
  int RodzajNumer(int pozycja, int rodzaj);
  int RodzajTyp(int typ);
  int RodzajWagonu(int pozycja, int rodzaj);
  char* Skad(int pozycja, int rodzaj);
  int Stan(int pozycja, int rodzaj, int ustaw=NIEOKRESLONA);
  char* Szopa(int numer);
  int Szopa(int pozycja, int rodzaj, int rozklad=NIEOKRESLONA);
  int Tor(int nr);
  int TypPociagu(int pozycja, int rodzaj, int ustaw=NIEOKRESLONA);
  int Wyprzedzenie(int ustaw=NIEOKRESLONA);
# define DLUGOSC_NAZWY_PLIKU 50
  int Wczytaj(char * nazwa_pliku, char nazwy_rysunkow[][DLUGOSC_NAZWY_PLIKU]);
  int WczytajStan(streampos pozycja, char * nazwa_pliku);
  int Wjazd(int pozycja, int rodzaj);
  int Wspolrzedna(int nr);
  int Wyjazd(int pozycja, int rodzaj);
  int ZapiszRozklad(char *nazwa);
};

#endif
