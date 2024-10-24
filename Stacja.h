#ifndef _STACJA
#define _STACJA

#include "Inne.h"
#include "Rozklad.h"
#include "Lokom.h"

/*******************************************************************************
 *** Klasa reprezentuje stacje kolejowa.                                     ***
 ***                                                                         ***
 *** Wersja: 0.57                                                            ***
 *** Data ostatniej modyfikacji: 03.07.2005                                  ***
 ******************************************************************************/
class tStacja
{
  tCzas Zegar;
  tRozklad Rozklad;
  tLokomotywownia Lokomotywownia;

  char nazwa_pliku_stacji[30];
  char nazwy_rysunkow[ILOSC_RYSUNKOW][DLUGOSC_NAZWY_PLIKU]; //tablica z nazwami rysunkow taboru


  tablica<int> obraz; //obraz stacji - zawiera numery bitmap do wyswietlenia
  tablica<int> stan;  //stan danego punktu
  #define POLE_WOLNE 0
  #define POLE_ZAREZERWOWANE 1
  #define POLE_ZAJETE 2
  #define WYBOR_TRASY 3
  #define WYBOR_TRASY_POCIAG 4

  tablica<int> trasa; //tablica wszystkich tras
  /*  [0] - czy trasa dwukierunkowa (1/0)
      [1] - czy trasa zelektryfikowana
      [2] - koniec trasy
      [3] - poczatek trasy
      [...] - srodek trasy
      [...+1] - koniec trasy
      dalej - same zera         */

  int szerokosc;
  int wysokosc;
  int ilosc_tras;  //ilosc wczytanych tras
  #define MAX_DLUGOSC_TRASY 200
  int ilosc_postojowych; //ilosc punktow postojowych
  int dlugosc_bocznic;  //laczna pojemnosc wszystkich bocznic
  tablica<int> pkt_postojowe;  //opis wszystkich punktow postojowych
  #define DLUGOSC_PUNKTU 5
  /*  [0] - rodzaj                    */
  #define WJAZD 1             /*Przy zmianie uwzglednic zmiany w pliku *.stc*/
  #define WYJAZD 2
  #define WJAZD_WYJAZD 3
  #define PERON 4
  #define BOCZNICA 5
  #define PKT_POSTOJOWY 6
  #define PKT_DLA_LOKOMOTYW 7
  #define LOKOWNIA 8
  #define PERON_TOWAROWY 9
  /*    [1] - maksymalna pojemnosc / dla wjazdow i wyjazdow czas w min. miedzy dwoma pociagami
                / dla wjazdow_wyjazdow  czas miedzy dwoma pociagami*100+ czas do mijanki
      [2..4] - wspolrzedne
      [3] - dla wjazdow/wyjazdow - wyprzedzenie tworzenia pociagow
      [5] - numer nieparzysty - lewy, parzysty prawy  - dla wjazdow/wyjazdow
          - poczatek bocznicy
          - numer peronu*/
  bool przejscia;

  tablica<tObiektRuchomy> stan_postojowych; //tablica z pociagami
  #define DLUGOSC_POSTOJOWYCH 10

  tablica<int> mijanka; //tablica z punktami pomiedzy stacja a mijanka na trasie jednotorowej
  /*    [0] - odnosnik do rozkladu
        [1] - czas zwolnienia punktu
        [2] - czas dojazdu do punktu
  ostatnie pole w kazdym wierszu okresla kierunek w jakim jada pociagi w punktach posrednich*/
  #define ROZMIAR_MIJANKI 30
  #define WYJEZDZA -4
  #define WOLNA_MIJANKA -1

  void Aktualizuj(void);
  int Anuluj(void);
  void CzasMijanki(void);
  bool CzyDobryPunkt(int poz_p, int poczatek,int koniec);
  bool CzyJedzie(int poz_p,int poczatek);
  bool CzyLokomotywa(int poz_p, int p_y, int k_y, int poczatek);
  bool CzyManewry(int poz_p,int p_y, int k_y);
  bool CzyPostuj(int poz_p);
  int CzyPrzod(int poz_p, int poczatek);
  bool CzyPunktualnie(int poz_p, int poczatek);
  bool CzyTowarowy(int poz_p);
  bool CzyMoznaZjechac(int poz_p, int poczatek);
  int KtoZajmujePunkt(int wsp);
  void DrogaZaznaczona(tObiektRuchomy* pociag);
  bool Miejsce(int pozycja,int poczatek,int p_y,int k_y);
  int Poruszanie(void);
  int TworzPociag(int i, int n);
  int Ustaw(int h,int m){return Zegar.Ustaw(h,m);};
  int Wczytaj(const char *nazwa);
  int WszystkieTrasy(int poczatek, int koniec,int elek);

  #define POCZATEK_BOCZNICY 55
  #define KONIEC_BOCZNICY 60
public:
  tStacja();

  int Bocznica(int wsp, int rodzaj);
  bool CzyRuch(int i,int j);
  int CzyPunkt(int w);
  bool CzyStoiPociag(int wsp);
  bool CzyZjechac(int i, int j);
  char* Laczenie(int wsp, int pozycja, int nr=-1);
  const char* Nazwa(int i, int j=NIEOKRESLONA);
  int NazwaNr(int i, int j);
  const char * NazwaPlikuStacji(void){return nazwa_pliku_stacji;};
  int NrPunktu(int wsp);
  tObiektRuchomy* Obiekt(int wsp,int koniec=0);
  int Obraz(int x,int y){return this->obraz[x][y];};
  int * Podglad(int i, int j);
  bool Przejscia(int p=-1){if(p!=-1) przejscia=p; return przejscia;};
  int Stan(int x,int y){return this->stan[x][y];};
  int Szerokosc(void){return szerokosc;};
  int TworzPociagi(int r=-2, int czekaj=0);
  int WczytajRozklad(char * nazwa_pliku);
  int WczytajStan(char *nazwa);
  long WjazdWyjazd(int w=0);
  int Wspolrzedna(int z, int _do);
  int WspWjazdu(int numer);
  int WspWjazd(int numer);
  int Wyprzedz(int pozycja, bool mijanka=false);
  int Wysokosc(void){return wysokosc;};
  int ZapiszStan(char *nazwa);
  int Zaznacz(tObiektRuchomy * wsk, int pkt,int elek);
  int Zaznacz(int p1=-1, int p2=-1,int elek=1);
  #define OK 0
  #define BLAD 1
  #define BRAK_TRASY 2
  #define BRAK_JEDNOZNACZNOSCI 3
  #define TRASY_ZAJETE 5
  char* Zaznaczanie(int poczatek, int koniec, int p_k=-1);

  int Odmierz(void);
  int Godzina(void){return Zegar.Godzina();};
  int Jednostka(void){return Zegar.Jednostka();};
  int Sekundy(void){return Zegar.Sekundy();};

  bool CzyGraTestowa(void){return Rozklad.CzyGraTestowa();};
  bool CzyRozlaczenie(int nr, int rodzaj){return Rozklad.CzyRozlaczenie(nr,rodzaj);};
  int CzyLaczenie(int nr, int rodzaj){return Rozklad.CzyLaczenie(nr,rodzaj);};
  bool CzyPodglad(void){return Rozklad.CzyPodglad();};
  bool CzyZmianaLoka(int pozycja, int rodzaj){return Rozklad.CzyZmianaLoka(pozycja, rodzaj, przejscia);};
  char* Dokad(int pozycja, int rodzaj){return Rozklad.Dokad(pozycja, rodzaj);};
  char * Godzina(int pozycja, int rodzaj, int godzina);
  char * GodzinaRzeczywista(int pozycja, int rodzaj, int godzina);
  void GraTestowa(bool gra){Rozklad.GraTestowa(gra);};
  int IloscPociagow(void){return Rozklad.IloscPociagow();};
  int IloscPociagowWTrakcjiPodwojnej(int rodzaj,int ograniczenie=0){return Rozklad.IloscPociagowWTrakcjiPodwojnej(rodzaj,ograniczenie);};
  int IloscRysunkow(void){return Rozklad.IloscRysunkow();};
  char* Lok(int pozycja, int rodzaj);
  int Mijanka(int punkt, int odcinek=0);
  char* NazwaPociagu(int pozycja, int rodzaj, int godzina){return Rozklad.NazwaPociagu(pozycja, rodzaj, godzina);};
  char* NazwaRodzajTyp(int pozycja, int rodzaj){return Rozklad.NazwaRodzajTyp(pozycja,rodzaj);};
  char* Numer(int pozycja, int rodzaj, int godzina){return Rozklad.Numer(pozycja, rodzaj, godzina);};
  int NumerCzesci(int pozycja, int rodzaj){return Rozklad.NumerCzesci(pozycja,rodzaj);};
  int Opoznienie(int pozycja, int rodzaj, int godzina=NIEOKRESLONA){return Rozklad.Opoznienie(pozycja,rodzaj,0,godzina);};
  int Peron(int pozycja, int rodzaj, int godzina){return Rozklad.Peron(pozycja, rodzaj, godzina);};
  char* Peron(int peron);
  int PlusMinus(int x, int y, int wartosc=NIEOKRESLONA){return Rozklad.PlusMinus(x,y,wartosc);};
  char* Rodzaj(int pozycja, int rodzaj){return Rozklad.Rodzaj(pozycja, rodzaj);};
  char* Skad(int pozycja, int rodzaj){return Rozklad.Skad(pozycja, rodzaj);};
  int StanPociagu(int pozycja, int rodzaj, int ustaw=NIEOKRESLONA);
  char* Szopa(int pozycja, int rodzaj=NIEOKRESLONA);
  int TypPociagu(int pozycja, int rodzaj){return Rozklad.TypPociagu(pozycja, rodzaj);};
  int Wjazd(int pozycja, int rodzaj){return pkt_postojowe[NrPunktu(Rozklad.Wjazd(pozycja,rodzaj))][5]/10;};
  int WjazdWyjazd(int pozycja, int rodzaj){return pkt_postojowe[NrPunktu(Rozklad.Wjazd(pozycja,rodzaj))][2];};
  int Wyjazd(int pozycja, int rodzaj){return pkt_postojowe[NrPunktu(Rozklad.Wyjazd(pozycja,rodzaj))][5]/10;};
  int Wyprzedzenie(int ustaw=NIEOKRESLONA){return Rozklad.Wyprzedzenie(ustaw);};

  int Bocznica(int i,int j,int wartosc){return stan_postojowych[i][j].Bocznica(wartosc);};
  int Czas(int i, int j, int czas=-1){return stan_postojowych[i][j].Czas(czas);};
  bool CzyPolaczony(int i, int j){return stan_postojowych[i][j].Polaczenie();};
  char* NumerLoka(int i, int j){if(przejscia)return Rozklad.Szopa(stan_postojowych[i][j].Numer());else return 0;};
  int NrRozklad(int i, int j){return stan_postojowych[i][j].Rozklad();};
  int RodzajSkladu(int i, int j){return stan_postojowych[i][j].Typ();};
  int RodzajSkladu2(int i, int j){return stan_postojowych[i][j].Rodzaj();};
  bool Sprawnosc(int i, int j){return stan_postojowych[i][j].Sprawnosc();};
  int TypLoka(int i, int j){return stan_postojowych[i][j].TypLoka();};

  tRaport * DajRaport(void){return Lokomotywownia.DajRaport();};
  int Zamow(int typ, int numer){return Lokomotywownia.Zamow(typ,numer);};
  //TO TRZEBA SKASOWAC !!!!!!!!!!!!!!!!!!!!
  int CzyJestMiejsce(void){return Lokomotywownia.CzyJestMiejsce();};
};


#define DAJ_POCZATEK -2
#define DAJ_KONIEC -3
#endif


