#include "lokom.h"#define NULL 0
/*#include <stdlib.h>*/
#include <stdio.h>

tLokomotywownia::tLokomotywownia(void)
{
  max_pojemnosc=0;
  obecna_ilosc=0;
  max_naprawianych_jednoczesnie=0;
  naprawianych_jednoczesnie=0;
  czas_zamawiania=0;
  czas_naprawy=0;
  stan=NULL;
  mozna_wystawic=NIE;
  moj_raport.pola=NULL;
}

tLokomotywownia::~tLokomotywownia(void)
{
  delete [] temp01;
  delete [] temp02;
  delete [] stan;
  delete [] moj_raport.pola;
}

// OK
// BRAK_MIEJSCA
int tLokomotywownia::Przyjmij(tObiektRuchomy * co)
{
  int i;
  if(obecna_ilosc<max_pojemnosc)
  {
    for(i=0;stan[i].status==ZAJETE;i++);
    stan[i].obiekt.Kopiuj(co);
    if(stan[i].obiekt.Sprawnosc())
    {
      stan[i].status=ZAJETE;
      stan[i].stan=SPRAWNA;
    }
    else
    {
      stan[i].status=ZAJETE;
      stan[i].stan=ZEPSUTA;
      stan[i].czas=czas_naprawy;
    }
    obecna_ilosc++;
    Sortuj();
    return OK;
  }

  return BRAK_MIEJSCA;
}

void tLokomotywownia::Sortuj(void)
{
  int i,j,numer;
  float min;

  //robimy kopie
  for(i=0;i<max_pojemnosc;i++)
  {
    temp01[i].obiekt.Kopiuj(&(stan[i].obiekt));
    temp01[i].stan=stan[i].stan;
    temp01[i].czas=stan[i].czas;
    temp01[i].status=stan[i].status;

    if(stan[i].status==ZAJETE)
      temp02[i]=temp01[i].obiekt.Rodzaj() * 1000.0 + temp01[i].obiekt.Numer();
    stan[i].status=WOLNE;
    //else
      //temp02[i]=1000000;
  }

  for(j=0;j<obecna_ilosc;j++)
  {
    numer=-1;
    min=1000000;
    for(i=max_pojemnosc-1;i>=0;i--)
    {
      if(temp01[i].status==ZAJETE)
      {
        if(temp02[i]<=min)// && temp02[i]>0)
        {
          min=temp02[i];
          numer=i;
        }
      }
    }

    if(numer==-1)
    {
      //wszystko posortowane
      break;
    }
    else
    {
      //stan[numer].status=WOLNE;

      stan[j].obiekt.Kopiuj(&(temp01[numer].obiekt));
      stan[j].stan=temp01[numer].stan;
      stan[j].czas=temp01[numer].czas;
      stan[j].status=temp01[numer].status;
      temp01[numer].status=WOLNE;
    }
  }
}

//OK
//BRAK
//CHILOWY_BRAK
int tLokomotywownia::Zamow(int typ, int numer=-1)
{
  int i;
  int byla=NIE;

  if(numer==-1)
  {
    for(i=0;i<obecna_ilosc;i++)
    {
      if(stan[i].obiekt.Rodzaj()==typ)
      {
        byla=TAK;
        if(stan[i].stan==SPRAWNA)
        {
          stan[i].stan=ZAMOWIONA;
	  stan[i].czas=czas_zamawiania;
	  return OK;
        }
      }
    }
  }
  else
  {
    for(i=0;i<obecna_ilosc;i++)
    {
      if(stan[i].obiekt.Rodzaj()==typ &&
         stan[i].obiekt.Numer()==numer)
      {
        byla=TAK;
        if(stan[i].stan==SPRAWNA)
        {
          stan[i].stan=ZAMOWIONA;
	  stan[i].czas=czas_zamawiania;
	  return OK;
        }
      }
    }
  }

  if(byla==TAK)
    return CHWILOWY_BRAK;
  else
    return BRAK; //bylo OK ?!
}

//NIEZNANY_PARAMETR
// wartosc parametru
//OK
//BLAD_PAMIECI

int tLokomotywownia::Parametry(int parametr, int wartosc=-1)
{
  int i;

  if(wartosc==-1) //odczyt
  {
    switch(parametr)
    {
      case POJEMNOSC:
        return max_pojemnosc;
      case CZAS_NAPRAWY:
        return czas_naprawy;
      case CZAS_ZAMAWIANIA:
        return czas_zamawiania;
      case NAPRAWIANYCH_JEDNOCZESNIE:
        return max_naprawianych_jednoczesnie;
      default:
        return NIEZNANY_PARAMETR;
    }
  }
  else //ustawianie
  {
    switch(parametr)
    {
      case POJEMNOSC:
      {
        stan=new opis_obiektu[wartosc];
        temp01=new opis_obiektu[wartosc];
        temp02=new float [wartosc];
	     moj_raport.pola=new pole_raportu[wartosc];
	     if(stan!=NULL && moj_raport.pola!=NULL && temp01!=NULL && temp02!=NULL)
	     {
	       max_pojemnosc=wartosc;
	       obecna_ilosc=0;
	       moj_raport.dl=0;
	       for(i=0;i<max_pojemnosc;i++)
	       {
	         stan[i].status=WOLNE;
	       }
	       return OK;
	     }
	     else
	       return BLAD_PAMIECI;
      }
      case CZAS_NAPRAWY:
      {
        czas_naprawy=wartosc;
	return OK;
      }
      case CZAS_ZAMAWIANIA:
      {
        czas_zamawiania=wartosc;
	return OK;
      }
      case NAPRAWIANYCH_JEDNOCZESNIE:
      {
        max_naprawianych_jednoczesnie=wartosc;
	return OK;
      }
      default:
        return NIEZNANY_PARAMETR;
    }
  }
}

void tLokomotywownia::Reset()
{
  max_pojemnosc=0;
  obecna_ilosc=0;
  max_naprawianych_jednoczesnie=0;
  naprawianych_jednoczesnie=0;
  czas_zamawiania=0;
  czas_naprawy=0;
  mozna_wystawic=NIE;
  delete [] temp01;
  delete [] temp02;
  delete [] stan;
  delete [] moj_raport.pola;
}

void tLokomotywownia::Aktualizuj()
{
  int i;
  int ile_naprawianych=0;
  int o_i=obecna_ilosc;
  int byla_gotowa=NIE;
  int zepsuta=NIE; // czy jest jakas zepsuta lokomotywa

  for(i=0;i<o_i;i++)// tutu max_pojemnosc;i++)
  {
    if(stan[i].status==ZAJETE)
    switch (stan[i].stan)
    {
      case ZEPSUTA:
      {
        zepsuta=TAK;
        break;
      }
      case NAPRAWIANA:
      {
        ile_naprawianych++;
        stan[i].czas--;
        if(stan[i].czas==0)
        {
          stan[i].obiekt.Sprawnosc(SPRAWNA);//tutu
	  stan[i].stan=SPRAWNA;
        }
        break;
      }
      case ZAMOWIONA:
      {

       stan[i].czas--;
	    if(stan[i].czas==0)
	      stan[i].stan=GOTOWA;
       break;
      }
      case GOTOWA:
      {
        if(mozna_wystawic==TAK)
        {
          byla_gotowa=TAK;
          mozna_wystawic=NIE;
          stan[i].status=WOLNE;
          obecna_ilosc--;
          // wydanie obiektu
          baza->Kopiuj(&(stan[i].obiekt)); //tutu
        }
        break;
      }
    }
  }

   
  if(zepsuta==TAK)
    for(i=0;i<o_i;i++)// tutu max_pojemnosc;i++)
    {
      if(ile_naprawianych<max_naprawianych_jednoczesnie)
      {
        if(stan[i].stan==ZEPSUTA)
        {
          stan[i].stan=NAPRAWIANA;
	  ile_naprawianych++;
        }
      }
      else
        break;
   }


   if(byla_gotowa==TAK)
   Sortuj();
}

//TAK
// NIE
int tLokomotywownia::CzyJestMiejsce(void)
{
  if(max_pojemnosc>obecna_ilosc)
   return TAK;
  else
    return NIE;
}

/*
// OK
// NIE_JEST_GOTOWA
// BRAK
int tLokomotywownia::Daj(int typ,int numer)
{ int i;

  for(i=0;i<max_pojemnosc;i++)
  {
    if(stan[i].obiekt.Rodzaj()==typ &&
       stan[i].obiekt.Numer()==numer)
    {
      if(stan[i].stan==GOTOWA)
      {
        stan[i].status=WOLNE;
	// wydanie obiektu
        return OK;
      }
      else
      {
        return NIE_JEST_GOTOWA;
      }
    }
  }

  return BRAK;
}
*/

void tLokomotywownia::UstawBaze(tObiektRuchomy *wsk)
{
  baza=wsk;
}

tRaport * tLokomotywownia::DajRaport(void)
{
  int i;
  int zepsutych=0;
  int naprawianych=0;
  int zamowionych=0;
  int sprawnych=0;
  int gotowych=0;
  int dl=0;

  for(i=0;i<obecna_ilosc;i++)// tutu max_pojemnosc;i++)
  {
    if(stan[i].status==ZAJETE)
    {
      switch (stan[i].stan)
      {
        case ZEPSUTA:
        {
          zepsutych++;
          break;
        }
      case NAPRAWIANA:
      {
        zepsutych++;
	     naprawianych++;
        break;
      }
      case ZAMOWIONA:
      {
        zamowionych++;
        break;
      }
      case SPRAWNA:
      {
        sprawnych++;
        break;
      }
      case GOTOWYCH:
      {
        gotowych++;
        break;
      }
    }

      moj_raport.pola[dl].obiekt=&stan[i].obiekt;
      moj_raport.pola[dl].stan=stan[i].stan;
      moj_raport.pola[dl].czas=stan[i].czas;
      dl++;
    }
  }

  moj_raport.zepsutych=zepsutych;
  moj_raport.naprawianych=naprawianych;
  moj_raport.sprawnych=sprawnych;
  moj_raport.gotowych=gotowych;
  moj_raport.zamowionych=zamowionych;
  moj_raport.dl=dl;

  return & moj_raport;
}

// wywolanie a=TAK || a=NIE
void tLokomotywownia::MoznaWystawic(int a)
{
  mozna_wystawic=a;
}

void tLokomotywownia::Save(char *nazwa)
{
  int i;
  FILE * f_out;
  //fprintf(stderr,"SS");
  f_out=fopen(nazwa,"at"); 
  fprintf(f_out,"%d %d %d %d %d %d %d\n",
                max_pojemnosc,
		obecna_ilosc,
		max_naprawianych_jednoczesnie,
		naprawianych_jednoczesnie,
		czas_zamawiania,
		czas_naprawy,
		mozna_wystawic);

  for(i=0;i<obecna_ilosc;i++)
  {
    fprintf(f_out,"%d %d %d %d %d %d %d %d %d %d %d %d\n",
                  stan[i].obiekt.Typ(),
                  stan[i].obiekt.Rozklad(),
		  stan[i].obiekt.Rodzaj(),
		  stan[i].obiekt.Numer(),
		  stan[i].obiekt.Sprawnosc(),
		  stan[i].obiekt.Polaczenie(),
		  stan[i].obiekt.Ruch(),
		  //stan[i].obiekt.
		  stan[i].obiekt.Czas(),
		  stan[i].obiekt.Bocznica(),
		  stan[i].stan,
		  stan[i].czas,
		  stan[i].status);
  }

  fclose(f_out);
  //fprintf(stderr,"SE");
}

void tLokomotywownia::Load(char *nazwa)
{
  int i;
  int oi;
  int p1,p2,p3,p4,p5,p6,p7,p8,p9;
  FILE * f_in;

  //fprintf(stderr,"LS");

  f_in=fopen(nazwa,"rt");
  int t;
  fscanf(f_in,"%d\n",&t);
  char nic[39];
//  fscanf(f_in,"%s\n",&nic);

  fgets(nic,39,f_in);
  fscanf(f_in,"%d",&max_pojemnosc);

  Parametry(POJEMNOSC,max_pojemnosc);

  fscanf(f_in,"%d %d %d %d %d %d\n",
                //&max_pojemnosc,
		&obecna_ilosc,
		&max_naprawianych_jednoczesnie,
		&naprawianych_jednoczesnie,
		&czas_zamawiania,
		&czas_naprawy,
		&mozna_wystawic);
 // Parametry(POJEMNOSC,max_pojemnosc);
   //        obecna_ilosc=oi;
  for(i=0;i<obecna_ilosc;i++)
  {
    //fprintf(stderr,"%d ",i);

    fscanf(f_in,"%d %d %d %d %d %d %d %d %d %d %d %d\n",
                 &p9,&p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,
		 &stan[i].stan,
		  &stan[i].czas,
		  &stan[i].status);

  //fprintf(stderr,"%d %d %d %d %d %d %d %d %d %d %d\n",
    //             p1,p2,p3,p4,p5,p6,p7,p8,
      //		 stan[i].stan,
	//	  stan[i].czas,
	  //	  stan[i].status);

                  stan[i].obiekt.Typ(p9),
		  stan[i].obiekt.Rozklad(p1);
		  stan[i].obiekt.Rodzaj(p2);
		  stan[i].obiekt.Numer(p3);
		  stan[i].obiekt.Sprawnosc(p4);
		  stan[i].obiekt.Polaczenie(false),//tutu Polaczenie(p5);
		  stan[i].obiekt.Ruch(p6);
		  //stan[i].obiekt.
		  stan[i].obiekt.Czas(p7);
		  stan[i].obiekt.Bocznica(p8);

  }

  fclose(f_in);
 /*
  fprintf(stderr,"%d %d %d %d %d %d %d\n",
                max_pojemnosc,
		obecna_ilosc,
		max_naprawianych_jednoczesnie,
		naprawianych_jednoczesnie,
		czas_zamawiania,
		czas_naprawy,
		mozna_wystawic);
*/
//fprintf(stderr,"LE");

}

