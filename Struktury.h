#ifndef _STRUKTURY
#define _STRUKTURY

/* =================== DYNAMICZNA TABLICA DWUWYMIAROWA ====================== */

/* ========================================================================== *
 * Klasa pomocnicza do klasy tablica.                                         *
 *                                                                            *
 * Data ostatniej modyfikacji: 10.12.2001                                     *
 * ========================================================================== */
template <class typ>
class  wiersze
{
public:
   typ *wiersz;
   wiersze(void){wiersz=0;};
   ~wiersze(void){delete [] wiersz;};
   typ & operator[](unsigned int ktory);
};

/* ========================================================================== *
 * Dynamiczna tablica dwuwymiarowa dowolnego typu.                            *
 *                                                                            *
 * Data ostatniej modyfikacji: 10.12.2001                                     *
 * ========================================================================== */
template <class typ>
class tablica
{
   wiersze<typ> *a;
public:
   tablica(void){a=0;};
   ~tablica(void){delete [] a;};
   tablica (int q, int w);
   void tworz(int q,int w);
   wiersze<typ> & operator[](unsigned int ktor);
};

template <class typ>
typ & wiersze<typ>::operator[](unsigned int ktory)
{
   return wiersz[ktory];
}

template <class typ>
tablica<typ>::tablica (int q,int w)
{
   a=new wiersze<typ>[q];
   for (int y=0;y<q;y++)
   {
     a[y].wiersz=new typ[w];
   }
}
/* ========================================================================== *
 * Umozliwia stworzenie tablicy prostokatnej po wczesniejszym                 *
 * jej zadeklarowaniu z uzyciem konstruktora bezargumentowego.                *
 *                                                                            *
 * Data ostatniej modyfikacji: 10.12.2001                                     *
 * ========================================================================== */
template <class typ>
void tablica<typ>::tworz(int q,int w)
{
   delete [] a;
   a=new wiersze<typ>[q];
   for (int y=0;y<q;y++)
   { 
     a[y].wiersz=new typ[w];
   }
}

template <class typ>
wiersze<typ> & tablica<typ>::operator[](unsigned int ktory)
{
  return a[ktory];
}

/* ================ KONIEC DYNAMICZNEJ TABLICY DWUWYMIAROWEJ ================ */


#endif
