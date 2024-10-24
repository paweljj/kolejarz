#ifndef _INNE
#define _INNE

/*******************************************************************************
 *** Klasa czas sluzy do odmierzania czasu.                                  ***
 ***                                                                         ***
 *** Wersja: 0.07                                                            ***
 *** Data ostatniej modyfikacji: 07.09.2001                                  ***
 ******************************************************************************/
class tCzas
{
   int godz;
   int min;
   int sek;
   int jednostka;

public:
   tCzas(int h=0,int m=0);

   int Godzina(void);  // Funkcja zwracajaca czas
   void Odmierz(void) throw(int);  // Funkcja do zmiany czasu
   int Sekundy(void); //Funkcja zwracajaca sekundy
   int Ustaw(int h,int m, int s=0);     // Funkcja do ustawienia godziny
   int Jednostka(int j=0);
};

#endif