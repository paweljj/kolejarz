#include "Rozklad.h"

tRozklad::tRozklad(void)
{
  srand(time(NULL));
  ilosc_rysunkow=ilosc_stacji=ilosc_pociagow=0;
  gra_testowa=false;
  wyprzedzenie=45;
  plusminus[0][0]=2;     plusminus[0][1]=5;
  plusminus[1][0]=5;     plusminus[1][1]=20;
  plusminus[2][0]=10;     plusminus[2][1]=20;
  plusminus[3][0]=10;     plusminus[3][1]=10;
  plusminus[4][0]=10;     plusminus[4][1]=30;
  plusminus[5][0]=15;     plusminus[5][1]=30;

  for(int i=0;i<250;i++)
    typ_rodzaju_pociagu[i]=-1;
    
  typ_rodzaju_pociagu[0]=TOWAROWY; strcpy(nazwa_typ_rodzaju_pociagu[0][0],"TW"); strcpy(nazwa_typ_rodzaju_pociagu[0][1],"T"); //towarowy
  typ_rodzaju_pociagu[1]=PODMIEJSKI; strcpy(nazwa_typ_rodzaju_pociagu[1][0],"SKM"); strcpy(nazwa_typ_rodzaju_pociagu[1][1],"S"); //SKM
  typ_rodzaju_pociagu[2]=OSOBOWY; strcpy(nazwa_typ_rodzaju_pociagu[2][0],"OS"); strcpy(nazwa_typ_rodzaju_pociagu[2][1],"O"); //OSOBOWY
  typ_rodzaju_pociagu[3]=PODMIEJSKI; strcpy(nazwa_typ_rodzaju_pociagu[3][0],"WKD"); strcpy(nazwa_typ_rodzaju_pociagu[3][1],"W"); //WKD
  typ_rodzaju_pociagu[4]=POSPIESZNY; strcpy(nazwa_typ_rodzaju_pociagu[4][0],"POS"); strcpy(nazwa_typ_rodzaju_pociagu[4][1],"P"); //POSPIESZNY
  typ_rodzaju_pociagu[5]=POSPIESZNY; strcpy(nazwa_typ_rodzaju_pociagu[5][0],"TLK"); strcpy(nazwa_typ_rodzaju_pociagu[5][1],"K"); //TLK
  typ_rodzaju_pociagu[6]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[6][0],"EX"); strcpy(nazwa_typ_rodzaju_pociagu[6][1],"X"); //EXPRES
  typ_rodzaju_pociagu[7]=SPECJALNY; strcpy(nazwa_typ_rodzaju_pociagu[7][0],"LOK"); strcpy(nazwa_typ_rodzaju_pociagu[7][1],"L"); //EXPRES
  typ_rodzaju_pociagu[8]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[8][0],"IC"); strcpy(nazwa_typ_rodzaju_pociagu[8][1],"I"); //INTERCITY
  typ_rodzaju_pociagu[10]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[10][0],"EC"); strcpy(nazwa_typ_rodzaju_pociagu[10][1],"E"); //EUROCITY
  typ_rodzaju_pociagu[12]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[12][0],"HOT"); strcpy(nazwa_typ_rodzaju_pociagu[12][1],"H"); //HOTELOWY
  typ_rodzaju_pociagu[13]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[13][0],"NEX"); strcpy(nazwa_typ_rodzaju_pociagu[13][1],"N"); //NEX
  typ_rodzaju_pociagu[14]=SPECJALNY; strcpy(nazwa_typ_rodzaju_pociagu[14][0],"PC"); strcpy(nazwa_typ_rodzaju_pociagu[14][1],"C"); //POCZTOWY
  typ_rodzaju_pociagu[16]=SPECJALNY; strcpy(nazwa_typ_rodzaju_pociagu[16][0],"BG"); strcpy(nazwa_typ_rodzaju_pociagu[16][1],"B"); //BAGAZOWY
  typ_rodzaju_pociagu[18]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[18][0],"EN"); strcpy(nazwa_typ_rodzaju_pociagu[18][1],"E"); //EURONIGHT
  typ_rodzaju_pociagu[20]=SPECJALNY; strcpy(nazwa_typ_rodzaju_pociagu[20][0],"Z"); strcpy(nazwa_typ_rodzaju_pociagu[20][1],"Z"); //SLUZBOWY
  typ_rodzaju_pociagu[22]=OSOBOWY; strcpy(nazwa_typ_rodzaju_pociagu[22][0],"REG"); strcpy(nazwa_typ_rodzaju_pociagu[22][1],"R"); //REGIO_PLUS
  typ_rodzaju_pociagu[24]=POSPIESZNY; strcpy(nazwa_typ_rodzaju_pociagu[24][0],"IRN"); strcpy(nazwa_typ_rodzaju_pociagu[24][1],"N"); //REGIO_N
  typ_rodzaju_pociagu[102]=PODMIEJSKI; strcpy(nazwa_typ_rodzaju_pociagu[102][0],"S"); strcpy(nazwa_typ_rodzaju_pociagu[102][1],"S"); //NIEM_SKM
  typ_rodzaju_pociagu[103]=OSOBOWY; strcpy(nazwa_typ_rodzaju_pociagu[103][0],"RB"); strcpy(nazwa_typ_rodzaju_pociagu[103][1],"B"); //NIEM_OSOBOWY
  typ_rodzaju_pociagu[104]=POSPIESZNY; strcpy(nazwa_typ_rodzaju_pociagu[104][0],"RE"); strcpy(nazwa_typ_rodzaju_pociagu[104][1],"E"); //NIEM_POSPIESZNY
  typ_rodzaju_pociagu[106]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[106][0],"IR"); strcpy(nazwa_typ_rodzaju_pociagu[106][1],"I"); //NIEM_EXPRES
  typ_rodzaju_pociagu[110]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[110][0],"ICE"); strcpy(nazwa_typ_rodzaju_pociagu[110][1],"C"); //NIEM_EUROCITY
  typ_rodzaju_pociagu[108]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[108][0],"ICN"); strcpy(nazwa_typ_rodzaju_pociagu[108][1],"N"); //NIEM_INTERCITY
  typ_rodzaju_pociagu[204]=POSPIESZNY; strcpy(nazwa_typ_rodzaju_pociagu[204][0],"COR"); strcpy(nazwa_typ_rodzaju_pociagu[204][1],"C"); //FR_COR
  typ_rodzaju_pociagu[206]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[206][0],"EST"); strcpy(nazwa_typ_rodzaju_pociagu[206][1],"E"); //FR_EUROSTAR
  typ_rodzaju_pociagu[202]=OSOBOWY; strcpy(nazwa_typ_rodzaju_pociagu[202][0],"TER"); strcpy(nazwa_typ_rodzaju_pociagu[202][1],"T"); //FR_TER
  typ_rodzaju_pociagu[208]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[208][0],"TGV"); strcpy(nazwa_typ_rodzaju_pociagu[208][1],"G"); //FR_TGV
  typ_rodzaju_pociagu[212]=KWALIFIKOWANY; strcpy(nazwa_typ_rodzaju_pociagu[212][0],"TdN"); strcpy(nazwa_typ_rodzaju_pociagu[212][1],"N"); //FR_TDN
}

/*******************************************************************************
 *** Funkcja zwraca pozycje pociagu do laczenia.                             ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  pozycja pociagu do laczenia                                            ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :22.07.2001                                  ***
 *******************************************************************************/
int tRozklad::CzyLaczenie(int pozycja, int rodzaj)
{
  if(rodzaj==NIEOKRESLONA)
    return rozklad[pozycja][12];
  else if(rodzaj==PRZYJAZD)
  {
    return rozklad[przyjazd[pozycja][0]][12];
  }
  else
  {
    return rozklad[odjazd[pozycja][0]][12];
  }
}

/*******************************************************************************
 *** Funkcja zwraca czy pociag ma byc rozlaczany.                            ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  tak/nie                                                                ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :25.07.2001                                  ***
 *******************************************************************************/
int tRozklad::CzyRozlaczenie(int pozycja, int rodzaj)
{
  if(rodzaj==NIEOKRESLONA)
  {
    return rozklad[pozycja][11];
  }
  else if(rodzaj==PRZYJAZD)
  {
    return rozklad[przyjazd[pozycja][0]][11];
  }
  else
  {
    return rozklad[odjazd[pozycja][0]][11];
  }
}

/*******************************************************************************
 *** Funkcja sprawdza, czy w danym pociagu nastepuje zmiana loka.            ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  przejscia - czy gra uwzglednia przejscia lokow                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  tak/nie                                                                ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 10.01.2002                                  ***
 *******************************************************************************/
bool tRozklad::CzyZmianaLoka(int pozycja, int rodzaj, bool przejscie)
{
  int a,b;
  if(rodzaj==PRZYJAZD)
  {
    if(rozklad[przyjazd[pozycja][0]][4]>=1000)
      return false;
    else
    {
      a=rozklad[przyjazd[pozycja][0]][4];
      b=rozklad[przyjazd[pozycja][0]][8];
    }
  }
  else
  {
    if(rozklad[odjazd[pozycja][0]][4]>=1000)
      return false;
    else
    {
      a=rozklad[odjazd[pozycja][0]][4];
      b=rozklad[odjazd[pozycja][0]][8];
    }
  }
    int la,lb;
    if(a>=1000 || b>=1000) return false;
    else if(a<0 || b<0) return false; 
    la=przejscia[a][5];
    lb=przejscia[b][5];
    if(!la) la=przejscia[a][0];
    if(!lb) lb=przejscia[b][0];
    if(przejscie)
    {
      if(la==lb && przejscia[a][1]==przejscia[b][1]) return false;
      else return true;
    }
    else
    {
      if(la==lb) return false;
      else return true;
    }

}

/*******************************************************************************
 *** Funkcja dodaje dwa czasy.                                               ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  t1, t2 - czasy                                                         ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  nowy czas                                                              ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :22.07.2001                                  ***
 *******************************************************************************/
int tRozklad::DodajCzas(int t1, int t2)
{
  int t=t1/100*60+t1%100;
  t+=t2;
  if(t<0) t=0;
//  if(t>=1440) t-=1440;
  return t/60*100+t%60;
}

/*******************************************************************************
 *** Funkcja zwraca dokad jedzie pociag.                                     ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  dokad jedzie pociag                                                    ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :31.07.2001                                  ***
 *******************************************************************************/
int tRozklad::Dokad(int pozycja)
{
  return rozklad[pozycja][6];
}

/*******************************************************************************
 *** Funkcja zwraca dokad jedzie pociag.                                     ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  dokad jedzie pociag                                                    ***
 ***                                                                         ***
 *** Wersja: 0.05                                                            ***
 *** Data ostatniej modyfikacji: 30.10.2001                                  ***
 *******************************************************************************/
char* tRozklad::Dokad(int pozycja, int rodzaj)
{
  int dokad;
  char* rel=new char[MAX_NAZWA];
  if(rodzaj==NIEOKRESLONA)
  {
    if(rozklad[pozycja][0]==POCIAG_DOCELOWY || rozklad[pozycja][0]==POCIAG_DOCELOWY_ROZLACZANY)
      dokad=0;
    else
      dokad=rozklad[pozycja][7];
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(rozklad[przyjazd[pozycja][0]][0]==POCIAG_DOCELOWY
       || rozklad[przyjazd[pozycja][0]][0]==POCIAG_DOCELOWY_ROZLACZANY
       || rozklad[przyjazd[pozycja][0]][0]==POCIAG_ZE_STACJI
       || rozklad[przyjazd[pozycja][0]][0]==POCIAG_ZE_STACJI_LACZONY)
      dokad=0;
    else
      dokad=rozklad[przyjazd[pozycja][0]][7];
  }
  else
  {
    /*if(rozklad[odjazd[pozycja][0]][0]==POCIAG_ZE_STACJI)
      dokad=0;
    else*/
      dokad=rozklad[odjazd[pozycja][0]][7];
  }
  int i;
  for(i=0;nazwa[dokad][i]!='\0' && i<MAX_NAZWA-1;i++)
    rel[i]=nazwa[dokad][i];
  rel[i]='\0';
  return rel;
}

/*******************************************************************************
 *** Funkcja zwraca/ustawia godzine.                                         ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - godz. przyjazdu/odjazdu pociagu                              ***
 ***  ustaw - nowa godzina                                                   ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  godzina przyjazdu/wyjazdu                                              ***
 ***                                                                         ***
 *** Wersja: 0.04                                                            ***
 *** Data ostatniej modyfikacji: 33.08.2001                                  ***
 *******************************************************************************/
int tRozklad::Godzina(int pozycja, int rodzaj, int godzina, int ustaw)
{
  int godz;
  if(ustaw!=NIEOKRESLONA)
  {
    if(rodzaj==NIEOKRESLONA)
    {
      if(godzina==PRZYJAZD)
        rozklad[pozycja][1]=ustaw;
      else
        rozklad[pozycja][5]=ustaw;
    }
    else if(rodzaj==PRZYJAZD)
    {
      if(godzina==PRZYJAZD)
        rozklad[przyjazd[pozycja][0]][1]=ustaw;
      else
        rozklad[przyjazd[pozycja][0]][5]=ustaw;
    }
    else
    {
      if(godzina==PRZYJAZD)
        rozklad[odjazd[pozycja][0]][1]=ustaw;
      else
        rozklad[odjazd[pozycja][0]][5]=ustaw;
    }
    godz=ustaw;
  }
  else
  {
    if(rodzaj==NIEOKRESLONA)
    {
      if(godzina==PRZYJAZD)
        godz=rozklad[pozycja][1];
      else
        godz=rozklad[pozycja][5];
    }
    else if(rodzaj==PRZYJAZD)
    {
      if(godzina==PRZYJAZD)
        godz=rozklad[przyjazd[pozycja][0]][1];
      else
        godz=rozklad[przyjazd[pozycja][0]][5];
    }
    else
    {
      if(godzina==PRZYJAZD)
        godz=rozklad[odjazd[pozycja][0]][1];
      else
        godz=rozklad[odjazd[pozycja][0]][5];
    }
  }
  return godz;
}

/*******************************************************************************
 *** Funkcja zwraca/ustawia rzeczywista godzine.                             ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - godz. przyjazdu/odjazdu pociagu                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  godzina przyjazdu/wyjazdu                                              ***
 ***                                                                         ***
 *** Wersja: 0.04                                                            ***
 *** Data ostatniej modyfikacji: 14.08.2001                                  ***
 *******************************************************************************/
int tRozklad::GodzinaRzeczywista(int pozycja, int rodzaj, int godzina, int ustaw)
{
  int godz;
  if(ustaw!=-1)
  {
    if(rodzaj==NIEOKRESLONA)
    {
      if(godzina==PRZYJAZD)
      {
        rozklad[pozycja][SZEROKOSC-2]=ustaw;
      }
      else
      {
        godz=rozklad[pozycja][SZEROKOSC-1]=ustaw;
      }
    }
    else if(rodzaj==PRZYJAZD)
    {
      if(godzina==PRZYJAZD)
      {
        rozklad[przyjazd[pozycja][0]][SZEROKOSC-2]=ustaw;
      }
      else
      {
        rozklad[przyjazd[pozycja][0]][SZEROKOSC-1]=ustaw;
      }
    }
    else
    {
      if(godzina==PRZYJAZD)
      {
        rozklad[odjazd[pozycja][0]][SZEROKOSC-2]=ustaw;
      }
      else
      {
        rozklad[odjazd[pozycja][0]][SZEROKOSC-1]=ustaw;
      }
    }
    godz=ustaw;
  }
  else
  {
    if(rodzaj==NIEOKRESLONA)
    {
      if(godzina==PRZYJAZD)
      {
        godz=rozklad[pozycja][SZEROKOSC-2];
        if(godz==NIEOKRESLONA)
          godz=rozklad[pozycja][1];
      }
      else
      {
        godz=rozklad[pozycja][SZEROKOSC-1];
        if(godz==NIEOKRESLONA)
          godz=rozklad[pozycja][5];
      }
    }
    else if(rodzaj==PRZYJAZD)
    {
      if(godzina==PRZYJAZD)
      {
        godz=rozklad[przyjazd[pozycja][0]][SZEROKOSC-2];
        if(godz==NIEOKRESLONA)
          godz=rozklad[przyjazd[pozycja][0]][1];
      }
      else
      {
        godz=rozklad[przyjazd[pozycja][0]][SZEROKOSC-1];
        if(godz==NIEOKRESLONA)
          godz=rozklad[przyjazd[pozycja][0]][5];
      }
    }
    else
    {
      if(godzina==PRZYJAZD)
      {
        godz=rozklad[odjazd[pozycja][0]][SZEROKOSC-2];
        if(godz==NIEOKRESLONA)
          godz=rozklad[odjazd[pozycja][0]][1];
      }
      else
      {
        godz=rozklad[odjazd[pozycja][0]][SZEROKOSC-1];
        if(godz==NIEOKRESLONA)
          godz=rozklad[odjazd[pozycja][0]][5];
      }
    }
  }
  return godz;
}

/*******************************************************************************
 *** Funkcja zwraca ilosc pociagow w trakcji podwojnej.                      ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  ograniczenie - ograniczenie przegladania rozkladu                      ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  ilosc pociagow w rakcji podwojnej                                      ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 20.04.2002                                  ***
 *******************************************************************************/
int tRozklad::IloscPociagowWTrakcjiPodwojnej(int rodzaj,int ograniczenie)
{
  if(!ograniczenie) ograniczenie=ilosc_pociagow;
  int licznik=0;
  if(rodzaj==PRZYJAZD)
  {
    for(int i=0;i<ograniczenie;i++)
      if(rozklad[przyjazd[i][0]][4]<0) licznik++;
  }
  else
  {
    for(int i=0;i<ograniczenie;i++)
    {
      if(rozklad[odjazd[i][0]][8]<0) licznik++;
      if(rozklad[odjazd[i][0]][0]==POWROT_LOKA) licznik--;
    }
  }
  return licznik;
}

/*******************************************************************************
 *** Funkcja kasuje przejscie loka wymienianego loka.                        ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 07.12.2001                                  ***
 *******************************************************************************/
void tRozklad::KasowaniePrzejscia(int pozycja)
{
  if(rozklad[pozycja][4]>=1000)
    return;
  else if(rozklad[pozycja][4]<0)
  {
    int t=rozklad[pozycja][4]*(-1);
    przejscia[t/1000][5]=0;
    t=t-t/1000*1000;
    przejscia[t][5]=0;
  }
  else
  {
    przejscia[rozklad[pozycja][4]][5]=0;
  }
}

/*******************************************************************************
 *** Funkcja koryguje przejscie loka.                                        ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  lok - lok powrotny                                                     ***
 ***  dwa - gdy trakcja podwojna                                             ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 07.12.2001                                  ***
 *******************************************************************************/
void tRozklad::KorygowaniePrzejscia(int pozycja, int lok, int dwa)
{
  if(rozklad[pozycja][4]>=1000)
    return;
  else if(rozklad[pozycja][8]<0)
  {
    int t=rozklad[pozycja][8]*(-1);
    if(dwa==1) przejscia[t/1000][5]=lok;
    t=t-t/1000*1000;
    if(dwa==2) przejscia[t][5]=lok;
  }
  else
  {
    przejscia[rozklad[pozycja][8]][5]=lok;
  }
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
 ***  0 dla wagonow bezposrednich                                            ***
 ***                                                                         ***
 *** Wersja: 0.08                                                            ***
 *** Data ostatniej modyfikacji: 20.12.2001                                  ***
 *******************************************************************************/
int tRozklad::Lok(int pozycja, int rodzaj)
{
  int b;
  if(rodzaj==PRZYJAZD)
  {
    if(rozklad[przyjazd[pozycja][0]][4]>=1000)
      b=rozklad[przyjazd[pozycja][0]][4]/1000;
    else if(rozklad[przyjazd[pozycja][0]][4]<0)
    {
      int l=rozklad[przyjazd[pozycja][0]][4]*(-1);
      if (przejscia[l/1000][5])
        b=przejscia[l/1000][5]*1000;
      else
        b=przejscia[l/1000][0]*1000;
      l=l-l/1000*1000;
      if(przejscia[l][5])
        b+=przejscia[l][5];
      else
        b+=przejscia[l][0];
      b*=(-1);
    }
    else
    {
      if(przejscia[rozklad[przyjazd[pozycja][0]][4]][5])
        b=przejscia[rozklad[przyjazd[pozycja][0]][4]][5];
      else
        b=przejscia[rozklad[przyjazd[pozycja][0]][4]][0];
    }
/*    if(rozklad[przyjazd[pozycja][0]][11])
    {
      int t=rozklad[przyjazd[pozycja][0]][11];
      t=t-t/10*10;
      if(t!=1)
        b=0;
    }*/
  }
  else
  {
    if(rozklad[odjazd[pozycja][0]][4]>=1000)
      b=rozklad[odjazd[pozycja][0]][4]/1000;
    else if(rozklad[odjazd[pozycja][0]][8]<0)
    {
      int l=rozklad[odjazd[pozycja][0]][8]*(-1);
      if (przejscia[l/1000][5])
        b=przejscia[l/1000][5]*1000;
      else
        b=przejscia[l/1000][0]*1000;
      l=l-l/1000*1000;
      if(przejscia[l][5])
        b+=przejscia[l][5];
      else
        b+=przejscia[l][0];
      b*=(-1);
    }
    else
    {
      if(przejscia[rozklad[odjazd[pozycja][0]][8]][5])
        b=przejscia[rozklad[odjazd[pozycja][0]][8]][5];
      else
        b=przejscia[rozklad[odjazd[pozycja][0]][8]][0];
    }
/*    if(rozklad[odjazd[pozycja][0]][12])
    {
      int t=rozklad[odjazd[pozycja][0]][12];
      t=t-t/10*10;
      if(t!=1)
        b=0;
    }*/
  }
  return b;
}

/*******************************************************************************
 *** Funkcja zwraca rodzaj loka.                                             ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  punkt - lok przyjezdzajacy/ lok wyjezdzajacy                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj loka                                                            ***
 ***                                                                         ***
 *** Wersja: 0.09                                                            ***
 *** Data ostatniej modyfikacji: 20.12.2001                                  ***
 *******************************************************************************/
int tRozklad::Lokomotywa(int pozycja, int rodzaj, int punkt)
{
  int b;
  if(rodzaj==NIEOKRESLONA)
  {
    if(punkt==PRZYJAZD)
    {
      if(rozklad[pozycja][4]>=1000)
        b=rozklad[pozycja][4]/1000;
      else if(rozklad[pozycja][4]<0)
      {
        int t=rozklad[pozycja][4]*(-1);
        if(przejscia[t/1000][5])
          b=przejscia[t/1000][5]*1000;
        else
          b=przejscia[t/1000][0]*1000;
        t=t-t/1000*1000;
        if(przejscia[t][5])
          b+=przejscia[t][5];
        else
          b+=przejscia[t][0];
        b*=(-1);
      }
      else
      {
        if(przejscia[rozklad[pozycja][4]][5])
          b=przejscia[rozklad[pozycja][4]][5];
        else
          b=przejscia[rozklad[pozycja][4]][0];
      }
/*      if(rozklad[pozycja][11])
      {
        int t=rozklad[pozycja][11];
        t=t-t/10*10;
        if(t!=1)
          b=0;
      }*/
    }
//return rozklad[pozycja][4];
    else
    {
      if(rozklad[pozycja][4]>=1000)
        b=rozklad[pozycja][4]/1000;
      else if(rozklad[pozycja][8]<0)
      {
        int t=rozklad[pozycja][8]*(-1);
        b=przejscia[t/1000][0]*1000;
        t=t-t/1000*1000;
        b+=przejscia[t][0];
        b*=(-1);
      }
      else
        b=przejscia[rozklad[pozycja][8]][0];
/*      if(rozklad[pozycja][12])
      {
        int t=rozklad[pozycja][12];
        t=t-t/10*10;
        if(t!=1)
          b=0;
      }*/
    }
//return rozklad[pozycja][8];
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(punkt==PRZYJAZD)
    {
      if(rozklad[przyjazd[pozycja][0]][4]>=1000)
        b=rozklad[przyjazd[pozycja][0]][4]/1000;
      else if(rozklad[przyjazd[pozycja][0]][4]<0)
      {
        int t=rozklad[przyjazd[pozycja][0]][4]*(-1);
        if(przejscia[t/1000][5])
          b=przejscia[t/1000][5]*1000;
        else
          b=przejscia[t/1000][0]*1000;
        t=t-t/1000*1000;
        if(przejscia[t][5])
          b+=przejscia[t][5];
        else
          b+=przejscia[t][0];
        b*=(-1);
      }
      else
      {
        if(przejscia[rozklad[przyjazd[pozycja][0]][4]][5])
          b=przejscia[rozklad[przyjazd[pozycja][0]][4]][5];
        else
          b=przejscia[rozklad[przyjazd[pozycja][0]][4]][0];
      }
/*      if(rozklad[przyjazd[pozycja][0]][11])
      {
        int t=rozklad[przyjazd[pozycja][0]][11];
        t=t-t/10*10;
        if(t!=1)
          b=0;
      }*/
    }
//return rozklad[przyjazd[pozycja][0]][4];
    else
    {
      if(rozklad[przyjazd[pozycja][0]][4]>=1000)
        b=rozklad[przyjazd[pozycja][0]][4]/1000;
      else if(rozklad[przyjazd[pozycja][0]][8]<0)
      {
        int t=rozklad[przyjazd[pozycja][0]][8]*(-1);
        b=przejscia[t/1000][0]*1000;
        t=t-t/1000*1000;
        b+=przejscia[t][0];
        b*=(-1);
      }

      else
        b=przejscia[rozklad[przyjazd[pozycja][0]][8]][0];
/*      if(rozklad[przyjazd[pozycja][0]][12])
      {
        int t=rozklad[przyjazd[pozycja][0]][12];
        t=t-t/10*10;
        if(t!=1)
          b=0;
      }*/
    }
//return rozklad[przyjazd[pozycja][0]][8];
  }
  else
  {
    if(punkt==PRZYJAZD)
    {
      if(rozklad[odjazd[pozycja][0]][4]>=1000)
        b=rozklad[odjazd[pozycja][0]][4]/1000;
      else if(rozklad[odjazd[pozycja][0]][4]<0)
      {
        int t=rozklad[odjazd[pozycja][0]][4]*(-1);
        if(przejscia[t/1000][5])
          b=przejscia[t/1000][5]*1000;
        else
          b=przejscia[t/1000][0]*1000;
        t=t-t/1000*1000;
        if(przejscia[t][5])
          b+=przejscia[t][5];
        else
          b+=przejscia[t][0];
        b*=(-1);
      }
      else
      {
        if(przejscia[rozklad[odjazd[pozycja][0]][4]][5])
          b=przejscia[rozklad[odjazd[pozycja][0]][4]][5];
        else
          b=przejscia[rozklad[odjazd[pozycja][0]][4]][0];
      }
/*      if(rozklad[odjazd[pozycja][0]][11])
      {
        int t=rozklad[odjazd[pozycja][0]][11];
        t=t-t/10*10;
        if(t!=1)
          b=0;
      }*/
    }
//return rozklad[odjazd[pozycja][0]][4];
    else
    {
      if(rozklad[odjazd[pozycja][0]][4]>=1000)
        b=rozklad[odjazd[pozycja][0]][4]/1000;
      else if(rozklad[odjazd[pozycja][0]][8]<0)
      {
        int t=rozklad[odjazd[pozycja][0]][8]*(-1);
        b=przejscia[t/1000][0]*1000;
        t=t-t/1000*1000;
        b+=przejscia[t][0];
        b*=(-1);
      }
      else
        b=przejscia[rozklad[odjazd[pozycja][0]][8]][0];
/*      if(rozklad[odjazd[pozycja][0]][12])
      {
        int t=rozklad[odjazd[pozycja][0]][12];
        t=t-t/10*10;
        if(t!=1)
          b=0;
      }*/
    }
//return rozklad[odjazd[pozycja][0]][8];
  }
  return b;
}

/*******************************************************************************
 *** Funkcja zwraca nazwe pociagu w formie gotowej do wyswietlenia.          ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - godz. przyjazdu/odjazdu pociagu                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  nazwa pociagu                                                          ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 15.12.2001                                  ***
 *******************************************************************************/
char* tRozklad::NazwaPociagu(int pozycja, int rodzaj,int godzina)
{
  int nr;
  if(rodzaj==NIEOKRESLONA)
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[pozycja][20];
    else
      nr=rozklad[pozycja][21];
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[przyjazd[pozycja][0]][20];
    else
      nr=rozklad[przyjazd[pozycja][0]][21];
  }
  else
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[odjazd[pozycja][0]][20];
    else
      nr=rozklad[odjazd[pozycja][0]][21];
  }
  if(!nr) return 0;
  char* g=new char [MAX_NAZWA];
  for(int i=0;i<MAX_NAZWA;i++)
    g[i]=nazwa_pociagu[nr-1][i];
  return g;
}

/*******************************************************************************
 *** Funkcja zwraca jednoliterowy skrot nazy rodzaju pociagu                 ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - godz. przyjazdu/odjazdu pociagu                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  skrocona nazwa typu pociagu                                            ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 24.06.2005                                  ***
 *******************************************************************************/
char* tRozklad::NazwaRodzajTyp(int pozycja, int rodzaj)
{
  int nr;
  if(rodzaj==NIEOKRESLONA)
  {
    nr=rozklad[pozycja][13];
  }
  else if(rodzaj==PRZYJAZD)
  {
    nr=rozklad[przyjazd[pozycja][0]][13];
  }
  else
  {
    nr=rozklad[odjazd[pozycja][0]][14];
  }
  char* g=new char [2];
  g[0]=nazwa_typ_rodzaju_pociagu[nr][1][0];
  g[1]='\n';
  return g;
}

/*******************************************************************************
 *** Funkcja dokonuje porawy rozkladu przed nowa doba.                       ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 14.08.2001                                  ***
 *******************************************************************************/
void tRozklad::NowaDoba(void)
{
  for(int i=0;i<ilosc_pociagow;i++)
  {
    if(rozklad[i][1]>=POLNOC)
    {
      rozklad[i][1]-=POLNOC;
      rozklad[i][SZEROKOSC-2]=NIEOKRESLONA;
    }
    else
    {
      if(rozklad[i][SZEROKOSC-2]>=POLNOC)
        rozklad[i][SZEROKOSC-2]-=POLNOC;
      rozklad[i][1]=-rozklad[i][1];
    }
    if(rozklad[i][5]>=POLNOC)
    {
      rozklad[i][5]-=POLNOC;
      rozklad[i][SZEROKOSC-1]=NIEOKRESLONA;
    }
    else
    {
      if(rozklad[i][SZEROKOSC-1]>=POLNOC)
        rozklad[i][SZEROKOSC-1]-=POLNOC;
      else
        rozklad[i][SZEROKOSC-1]=0;
      rozklad[i][5]=-rozklad[i][5];
    }
  }
}

/*******************************************************************************
 *** Funkcja zwraca numer pociagu w formie gotowej do wyswietlenia.          ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - godz. przyjazdu/odjazdu pociagu                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer pociagu                                                          ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 11.12.2001                                  ***
 *******************************************************************************/
char* tRozklad::Numer(int pozycja, int rodzaj, int godzina)
{
  int nr;
  if(rodzaj==NIEOKRESLONA)
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[pozycja][9];
    else
      nr=rozklad[pozycja][10];
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[przyjazd[pozycja][0]][9];
    else
      nr=rozklad[przyjazd[pozycja][0]][10];
  }
  else
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[odjazd[pozycja][0]][9];
    else
      nr=rozklad[odjazd[pozycja][0]][10];
  }
  if(!nr) return 0;
  char* g=new char [10];
  sprintf(g,"%d",nr);
  return g;
}

/*******************************************************************************
 *** Funkcja zwraca pozycje danego wagonu w skladach laczonych.              ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - godz. przyjazdu/odjazdu pociagu                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  pozycja wagonu                                                         ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 08.09.2002                                  ***
 *******************************************************************************/
int tRozklad::NumerCzesci(int pozycja, int rodzaj)
{
  int nr;
  if(rodzaj==PRZYJAZD)
    nr=rozklad[pozycja][11];
  else
    nr=rozklad[pozycja][12];
  return nr % 10;
}

/*******************************************************************************
 *** Funkcja zwraca numer pociagu w rozkladzie.                              ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  laczenie - gdy pociag ma byc rozlaczany                                ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer pociagu w rozkladzie                                             ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 12.10.2001                                  ***
 *******************************************************************************/
int tRozklad::NumerWRozkladzie(int pozycja, int rodzaj,bool laczenie )
{
  if(rodzaj==PRZYJAZD && laczenie)
  {
    int p=przyjazd[pozycja][0];
    return rozklad[p][11]; //bylo -1
  }
  else if(rodzaj==ODJAZD && laczenie)
  {
    int p=odjazd[pozycja][0];
    return rozklad[p][11];  //bylo -1
  }
  else if(rodzaj==PRZYJAZD)
  {
    return przyjazd[pozycja][0];
  }
  else
  {
    return odjazd[pozycja][0];
  }
}

/*******************************************************************************
 *** Funkcja w sposob losowy dokonuje opoznienia pociagu.                    ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  czas - aktualny czas                                                   ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  1 - gdy dokonano opoznienia pociagu                                    ***
 ***                                                                         ***
 *** Wersja: 0.21                                                            ***
 *** Data ostatniej modyfikacji: 23.04.2006                                  ***
 *******************************************************************************/
int tRozklad::Opoznienie(int czas)
{
  int wynik=0;
  if(!CzyGraTestowa())
  {
    for(int i=0;i<ilosc_pociagow;i++)
    {
      if(rozklad[i][SZEROKOSC-2]==NIEOKRESLONA && DodajCzas(rozklad[i][1],-wyprzedzenie)<=czas
        && rozklad[i][0]!=POCIAG_ROZLACZANY && rozklad[i][0]!=POCIAG_DOCELOWY_ROZLACZANY)
      {//mamy pociag do opoznienia
        int pr=rand()%101;
        bool op=false;
        switch (RodzajTyp(rozklad[i][13]))
        {
          case TOWAROWY:
            if(plusminus[4][0]>pr)
            {//przyspieszenie
              pr=rand()%6;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],-pr);
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
              wynik=1;
            }
            else if(plusminus[4][0]+plusminus[4][1]>pr)
            {//opoznienie
              op=true;
            }
            else if(plusminus[4][0]+plusminus[4][1]+1>pr)
            {//uszkodzony lok
              pr=rand()%20+120;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
              rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr+30);
              wynik=1;
            }
            else
            {
              rozklad[i][SZEROKOSC-2]=rozklad[i][1];
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
            }
            break;
          case OSOBOWY:
            if(plusminus[1][0]>pr)
            {//przyspieszenie
              pr=rand()%6;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],-pr);
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
              wynik=1;
            }
            else if(plusminus[1][0]+plusminus[1][1]>pr)
            {//opoznienie
              op=true;
            }
            else if(plusminus[1][0]+plusminus[1][1]+1>pr)
            {//uszkodzony lok
              pr=rand()%20+120;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
              rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr+30);
              wynik=1;
            }
            else
            {
              rozklad[i][SZEROKOSC-2]=rozklad[i][1];
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
            }
            break;
          case PODMIEJSKI:
            if(plusminus[0][0]>pr)
            {//przyspieszenie
              pr=rand()%3;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],-pr);
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
              wynik=1;
            }
            else if(plusminus[0][0]+plusminus[0][1]>pr)
            {//opoznienie
              op=true;
            }
            else if(plusminus[0][0]+plusminus[0][1]+1>pr)
            {//uszkodzony lok
              pr=rand()%10;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
              rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr+30);
              wynik=1;
            }
            else
            {
              rozklad[i][SZEROKOSC-2]=rozklad[i][1];
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
            }
            break;
          case POSPIESZNY:
            if(plusminus[2][0]>pr)
            {//przyspieszenie
              pr=rand()%11;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],-pr);
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
              wynik=1;
            }
            else if(plusminus[2][0]+plusminus[2][1]>pr)
            {//opoznienie
              op=true;
            }
            else if(plusminus[2][0]+plusminus[2][1]+1>pr)
            {//uszkodzony lok
              pr=rand()%20+120;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
              rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr+30);
              wynik=1;
            }
            else
            {
              rozklad[i][SZEROKOSC-2]=rozklad[i][1];
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
            }
            break;
          case KWALIFIKOWANY:
            if(plusminus[3][0]>pr)
            {//przyspieszenie
              pr=rand()%11;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],-pr);
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
              wynik=1;
            }
            else if(plusminus[3][0]+plusminus[3][1]>pr)
            {//opoznienie
              op=true;
            }
            else if(plusminus[3][0]+plusminus[3][1]+1>pr)
            {//uszkodzony lok
              pr=rand()%20+120;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
              rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr+30);
              wynik=1;
            }
            else
            {
              rozklad[i][SZEROKOSC-2]=rozklad[i][1];
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
            }
            break;
          case SPECJALNY:
            if(plusminus[5][0]>pr)
            {//przyspieszenie
              pr=rand()%15;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],-pr);
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
              wynik=1;
            }
            else if(plusminus[5][0]+plusminus[5][1]>pr)
            {//opoznienie
              op=true;
            }
            else if(plusminus[5][0]+plusminus[5][1]+1>pr)
            {//uszkodzony lok
              pr=rand()%20+120;
              rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
              rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr+30);
              wynik=1;
            }
            else
            {
              rozklad[i][SZEROKOSC-2]=rozklad[i][1];
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
            }
            break;
        }
        //dla pociagu opoznionego
        if(op)
        {
          op=false;
          pr=rand()%100+1;
          if(pr<50)
            pr=rand()%10+1;
          else if(pr<70)
            pr=rand()%20+11;
          else if(pr<85)
            pr=rand()%30+31;
          else if(pr<95)
            pr=rand()%30+61;
          else
            pr=rand()%30+91;
          if(RodzajTyp(rozklad[i][13])==PODMIEJSKI)
            pr=rand()%5;
          rozklad[i][SZEROKOSC-2]=DodajCzas(rozklad[i][1],pr);
          if(rozklad[i][0]==POCIAG_DOCELOWY || rozklad[i][0]==POCIAG_DOCELOWY_ROZLACZANY)
          {
            int godz_od=DodajCzas(rozklad[i][SZEROKOSC-2],10);
            if(godz_od>rozklad[i][5])
              rozklad[i][SZEROKOSC-1]=godz_od;
            else
              rozklad[i][SZEROKOSC-1]=rozklad[i][5];
          }
          else
            rozklad[i][SZEROKOSC-1]=DodajCzas(rozklad[i][5],pr);
          wynik=1;
        }
        if(rozklad[i][11])
        {//dla pociagu rozlaczanego
          //rozklad[rozklad[i][11]-1][SZEROKOSC-2]=rozklad[i][SZEROKOSC-2];
          //licze opoznienie
          int godz=rozklad[i][SZEROKOSC-2];
          int r=rozklad[i][11]/10;
          int b=rozklad[i][1];
          int op=godz/100*60+godz%100-(b/100*60+b%100);
          for(;;)
          {
            rozklad[r][SZEROKOSC-2]=godz;
            rozklad[r][SZEROKOSC-1]=DodajCzas(rozklad[r][5],op);
            //dla pociagu laczonego
            if(rozklad[r][12])
            {
              int godz_od=rozklad[r][SZEROKOSC-1];
              int rr=r;
              for(;;)
              {
                if(rozklad[rr][SZEROKOSC-1]>godz_od)
                  godz_od=rozklad[rr][SZEROKOSC-1];
                rr=rozklad[rr][12]/10;
                if(rr==r) break;
              }
              for(;;)
              {
                rozklad[rr][SZEROKOSC-1]=godz_od;
                rr=rozklad[rr][12]/10;
                if(rr==r) break;
              }
            }
            r=rozklad[r][11];
            if(r-(r/10)*10==1) break;
            r/=10;
          }
        }
        //dla pociagu laczonego
        if(rozklad[i][12])
        {
          int godz_od=rozklad[i][SZEROKOSC-1];
          int rr=i;
          for(;;)
          {
            if(rozklad[rr][SZEROKOSC-1]>godz_od)
              godz_od=rozklad[rr][SZEROKOSC-1];
            rr=rozklad[rr][12]/10;
            if(rr==i) break;
          }
          for(;;)
          {
            rozklad[rr][SZEROKOSC-1]=godz_od;
            rr=rozklad[rr][12]/10;
            if(rr==i) break;
          }
        }
        //losowa zmiana loka
        int lok=rozklad[i][4];
        int lok2=-1;
        if(lok>=1000) continue;
        else if(lok<-1000)
        {
          lok*=-1;
          lok2=lok-lok/1000*1000;
          lok/=1000;
        }
        if(przejscia[lok][2]>=0 || przejscia[lok][5] || !przejscia[lok][4]) continue;
        int losowa=rand()%101;
        int suma=0;
        for(int p=0;p<ilosc_nazw_lokow;p++)
        {
          suma+=prawdopodobienstwa[Przejscia(lok,4)-1][p];
          if(suma>losowa)
          {
            przejscia[lok][6]=przejscia[lok][0];
            przejscia[lok][0]=p+1;
            break;
          }
        }
        if(lok2>-1)
        {
          if(przejscia[lok2][2]>=0 || przejscia[lok2][5] || !przejscia[lok2][4]) continue;
          losowa=rand()%101;
          suma=0;
          for(int p=0;p<ilosc_nazw_lokow;p++)
          {
            suma+=prawdopodobienstwa[Przejscia(lok2,4)-1][p];
            if(suma>losowa)
            {
              przejscia[lok2][6]=przejscia[lok2][0];
              przejscia[lok2][0]=p+1;
              break;
            }
          }
        }
      }
    }
  }
  Sortuj(ODJAZD);
  Sortuj(PRZYJAZD);
  return wynik;
}

/*******************************************************************************
 *** Funkcja zwraca lub zwieksza opoznienie pociagu.                         ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  opoznienie - wartosc o ktora trzeba zmienic opoznienie                 ***
 ***  godzina - opoznienie przyjazdu/wyjazdu                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  opoznienie pociagu                                                     ***
 ***                                                                         ***
 *** Wersja: 0.07                                                            ***
 *** Data ostatniej modyfikacji: 26.04.2003                                  ***
 *******************************************************************************/
int tRozklad::Opoznienie(int pozycja, int rodzaj, int opoznienie, int godzina)
{
  int a,b;
  if(rodzaj==NIEOKRESLONA)
  {
    if (godzina==PRZYJAZD)
    {
      if(rozklad[pozycja][SZEROKOSC-2]!=NIEOKRESLONA)
      {
        if(opoznienie)
        {
          rozklad[pozycja][SZEROKOSC-2]=DodajCzas(rozklad[pozycja][SZEROKOSC-2],opoznienie);
        }
        a=rozklad[pozycja][SZEROKOSC-2];
        b=rozklad[pozycja][1];
        if(b<0)
        {
          b=-b;
          b=1440-(b/100*60+b%100);
          b=b/60*100+b%60;
          b=-b;
        }
        return a/100*60+a%100-(b/100*60+b%100);
      }
    }
    else
    {
      if(rozklad[pozycja][SZEROKOSC-1]!=NIEOKRESLONA)
      {
        if(opoznienie)
        {
          rozklad[pozycja][SZEROKOSC-1]=DodajCzas(rozklad[pozycja][SZEROKOSC-1],opoznienie);
        }
        a=rozklad[pozycja][SZEROKOSC-1];
        b=rozklad[pozycja][5];
        if(b<0)
        {
          b=-b;
          b=1440-(b/100*60+b%100);
          b=b/60*100+b%60;
          b=-b;
        }
        return a/100*60+a%100-(b/100*60+b%100);
      }
    }
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(rozklad[przyjazd[pozycja][0]][SZEROKOSC-2]!=NIEOKRESLONA)
    {
      if(opoznienie)
      {
        rozklad[przyjazd[pozycja][0]][SZEROKOSC-2]=DodajCzas(rozklad[przyjazd[pozycja][0]][SZEROKOSC-2],opoznienie);
        //dla pociagu rozlaczanego
        if(rozklad[przyjazd[pozycja][0]][11])
        {
          int godz=rozklad[przyjazd[pozycja][0]][SZEROKOSC-2];
          int rr=przyjazd[pozycja][0];
          rr=rozklad[rr][11]/10;
          for(;;)
          {
            rozklad[rr][SZEROKOSC-2]=godz;
            rr=rozklad[rr][11]/10;
            if(rr==przyjazd[pozycja][0]) break;
          }
        }
      }
      a=rozklad[przyjazd[pozycja][0]][SZEROKOSC-2];
      b=rozklad[przyjazd[pozycja][0]][1];
      if(b<0)
      {
        b=-b;
        b=1440-(b/100*60+b%100);
        b=b/60*100+b%60;
        b=-b;
      }
      return a/100*60+a%100-(b/100*60+b%100);
    }
  }
  else
  {
    if(rozklad[odjazd[pozycja][0]][SZEROKOSC-1]!=NIEOKRESLONA)
    {
      if(opoznienie)
      {
        rozklad[odjazd[pozycja][0]][SZEROKOSC-1]=DodajCzas(rozklad[odjazd[pozycja][0]][SZEROKOSC-1],opoznienie);
        /*//dla pociagu rozlaczanego
        if(rozklad[odjazd[pozycja][0]][11])
        {
          int godz=rozklad[odjazd[pozycja][0]][SZEROKOSC-1];
          int rr=przyjazd[pozycja][0];
          rr=rozklad[rr][11]/10;
          for(;;)
          {
            rozklad[rr][SZEROKOSC-1]=godz;
            rr=rozklad[rr][11]/10;
            if(rr==odjazd[pozycja][0]) break;
          }
        }*/
      }
      a=rozklad[odjazd[pozycja][0]][SZEROKOSC-1];
      b=rozklad[odjazd[pozycja][0]][5];
      if(b<0)
      {
        b=-b;
        b=1440-(b/100*60+b%100);
        b=b/60*100+b%60;
        b=-b;
      }
      return a/100*60+a%100-(b/100*60+b%100);
    }
  }
  return 0;
}

/*******************************************************************************
 *** Funkcja zwraca numer peronu.                                            ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  godzina - godz. przyjazdu/odjazdu pociagu                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer peronu                                                           ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 15.12.2001                                  ***
 *******************************************************************************/
int tRozklad::Peron(int pozycja, int rodzaj, int godzina)
{
  int nr;
  if(rodzaj==NIEOKRESLONA)
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[pozycja][18];
    else
      nr=rozklad[pozycja][19];
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[przyjazd[pozycja][0]][18];
    else
      nr=rozklad[przyjazd[pozycja][0]][19];
  }
  else
  {
    if(godzina==PRZYJAZD)
      nr=rozklad[odjazd[pozycja][0]][18];
    else
      nr=rozklad[odjazd[pozycja][0]][19];
  }
  return nr;
}

/*******************************************************************************
 *** Funkcja zwraca lub ustawia prawdopodobienstwo opoznienia pociagu.       ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  x,y - pozycja                                                          ***
 ***  wartosc - nowe opoznienie/przyspieszenie                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  opoznienie/przyspieszenie pociagu                                      ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :22.07.2001                                  ***
 *******************************************************************************/
int tRozklad::PlusMinus(int x, int y, int wartosc)
{
  if(wartosc!=NIEOKRESLONA)
    plusminus[x][y]=wartosc;
  return plusminus[x][y];
}

/*******************************************************************************
 *** Funkcja zwraca zestawienie skladu.                                      ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  zestawienie skladu                                                     ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 07.10.2001                                  ***
 *******************************************************************************/
int * tRozklad::Podglad(int pozycja)
{
  int nr=rozklad[pozycja][17];
  int *sk=new int[DLUGOSC_SKLADU];
  for(int i=0;i<DLUGOSC_SKLADU;i++)
  {
    sk[i]=sklady[nr][i];
  }
  return sk;
}

/*******************************************************************************
 *** Funkcja wpisuje/kasuje do rokladu powracajacego loka.                   ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  odnosnk - numer pozycji z opisem odjezdzajacego pociagu/loka.          ***
 ***  lok - odnosnik do loka / NIEOKRESLONA                                  ***
 ***  wjazd - wspolrzedne wjazdu
 ***                                                                         ***
 *** Wersja: 0.09                                                            ***
 *** Data ostatniej modyfikacji: 07.04.2006                                  ***
 *******************************************************************************/
void tRozklad::PowrotLoka(int odnosnik, int lok, int wjazd)
{
  if(lok==NIEOKRESLONA)
  {//kasowanie z rokladu
    for(;odnosnik<ilosc_pociagow-1;odnosnik++)
      for(int i=0;i<SZEROKOSC;i++)
        rozklad[odnosnik][i]=rozklad[odnosnik+1][i];
    ilosc_pociagow--;
  }
  else
  {//dopisanie do rozkladu
    //znajduje z ktorym pociagiem powinien wrocic sprawny lok
   /* int pociag=rozklad[odnosnik][4];
    if(pociag>=1000)
      pociag=odnosnik;
    else
    {
      pociag=rozklad[odnosnik][8];
      if(pociag<0)
        pociag=pociag/(-1000);
      pociag=abs(przejscia[pociag][2]);
    }*/
    for(int i=0;i<SZEROKOSC;i++)
      rozklad[ilosc_pociagow][i]=0;
    rozklad[ilosc_pociagow][0]=POWROT_LOKA;
    rozklad[ilosc_pociagow][SZEROKOSC-2]=rozklad[ilosc_pociagow][1]=DodajCzas(rozklad[odnosnik][1],30);
    rozklad[ilosc_pociagow][2]=wjazd; //rozklad[odnosnik][6];  
    rozklad[ilosc_pociagow][4]=lok*1000;
    rozklad[ilosc_pociagow][13]=POWROT_LOKA;
    rozklad[ilosc_pociagow][15]=BEDZIE;
    rozklad[ilosc_pociagow][SZEROKOSC-1]=9999;
    ilosc_pociagow++;
  }
}

/*******************************************************************************
 *** Funkcja zwraca pozycje pociagu znajdujacego sie                         ***
 *** na stacji na poczatku gry.                                              ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  wpolrzedne punktu                                                      ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 13.01.2004                                  ***
 *******************************************************************************/
int tRozklad::Pozycja(int pozycja)
{
  return rozklad[pozycja][23];
}

/*******************************************************************************
 *** Funkcja zwraca rodzaj pociagu gotowy do wyswietlenia.                   ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj pociagu                                                         ***
 ***                                                                         ***
 *** Wersja: 0.10                                                            ***
 *** Data ostatniej modyfikacji: 09.12.2004                                  ***
 *******************************************************************************/
char* tRozklad::Rodzaj(int pozycja, int rodzaj)
{
  int r;
  char *nazwa;
  if(rodzaj==NIEOKRESLONA)
  {
    r=rozklad[pozycja][13];
  }
  else if(rodzaj==PRZYJAZD)
  {
    r=rozklad[przyjazd[pozycja][0]][13];
  }
  else
  {
    r=rozklad[odjazd[pozycja][0]][14];
  }
  /*switch (r)
  {
    case TOWAROWY:
      nazwa="TW";
      break;
    case SKM:
      nazwa="SKM";
      break;
    case OSOBOWY:
      nazwa="OS";
      break;
    case WKD:
      nazwa="WKD";
      break;
    case POSPIESZNY:
      nazwa="POS";
      break;
    case EXPRES:
      nazwa="EX";
      break;
    case INTERCITY:
      nazwa="IC";
      break;
    case EUROCITY:
      nazwa="EC";
      break;
    case HOTELOWY:
      nazwa="HOT";
      break;
    case NEX:
      nazwa="NEX";
      break;
    case POCZTOWY:
      nazwa="PC";
      break;
    case BAGAZOWY:
      nazwa="BG";
      break;
    case POWROT_LOKA:
      nazwa="LOK";
      break;
    case EURONIGHT:
      nazwa="EN";
      break;
    case SLUZBOWY:
      nazwa="Z";
      break;
    case REGIO_PLUS:
      nazwa="REG";
      break;
    case REGIO_N:
      nazwa="IRN";
      break;
    case NIEM_SKM:
      nazwa="S";
      break;
    case NIEM_OSOBOWY:
      nazwa="RB";
      break;
    case NIEM_POSPIESZNY:
      nazwa="RE";
      break;
    case NIEM_EXPRES:
      nazwa="IR";
      break;
    case NIEM_EUROCITY:
      nazwa="ICE";
      break;
    case NIEM_INTERCITY:
      nazwa="ICN";
      break;
    case FR_COR:
      nazwa="COR";
      break;
    case FR_EUROSTAR:
      nazwa="EST";
      break;
    case FR_TER:
      nazwa="TER";
      break;
    case FR_TGV:
      nazwa="TGV";
      break;
    case FR_TDN:
      nazwa="TdN";
      break;
    default:
      nazwa="XXX";
  }*/
  nazwa=nazwa_typ_rodzaju_pociagu[r][0];
  return nazwa;
}

/*******************************************************************************
 *** Funkcja zwraca rodzaj pociagu - numer.                                  ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj pociagu                                                         ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 08.10.2001                                  ***
 *******************************************************************************/
int tRozklad::RodzajNumer(int pozycja, int rodzaj)
{
  if(rodzaj==NIEOKRESLONA)
  {
    return rozklad[pozycja][13]; //zwraca rodzaj przyjezdzajacy
  }
  else if(rodzaj==PRZYJAZD)
  {
    return rozklad[przyjazd[pozycja][0]][13];
  }
  else
  {
    return rozklad[odjazd[pozycja][0]][14];
  }
}

/*******************************************************************************
 *** Funkcja zwraca typ rodzaju pociagu - os, kwalif.                        ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  typ - typ pociagu z rozkladu                                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  typ rodzaju pociagu                                                    ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 24.06.2005                                  ***
 *******************************************************************************/
int tRozklad::RodzajTyp(int typ)
{
  return typ_rodzaju_pociagu[typ];
}

/*******************************************************************************
 *** Funkcja zwraca rodzaj wagonu.                                           ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj wagonu                                                          ***
 ***                                                                         ***
 *** Wersja: 0.02                                                            ***
 *** Data ostatniej modyfikacji: 09.10.2001                                  ***
 *******************************************************************************/
int tRozklad::RodzajWagonu(int pozycja, int rodzaj)
{
  if(rodzaj==NIEOKRESLONA)
  {
    return rozklad[pozycja][16];
  }
  else if(rodzaj==PRZYJAZD)
  {
    return rozklad[przyjazd[pozycja][0]][16];
  }
  else
  {
    return rozklad[odjazd[pozycja][0]][16];
  }
}


/*******************************************************************************
 *** Funkcja zwraca skad jedzie pociag.                                      ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  skad jedzie pociag                                                     ***
 ***                                                                         ***
 *** Wersja: 0.05                                                            ***
 *** Data ostatniej modyfikacji: 05.12.2001                                  ***
 *******************************************************************************/
char* tRozklad::Skad(int pozycja, int rodzaj)
{
  int skad;
  char* rel=new char[MAX_NAZWA];
  if(rodzaj==NIEOKRESLONA && pozycja==NIEOKRESLONA)
    skad=0;
  else if(rodzaj==NIEOKRESLONA)
  {
    if(rozklad[pozycja][0]==POCIAG_ZE_STACJI || rozklad[pozycja][0]==POCIAG_ZE_STACJI_LACZONY)
      skad=0;
    else
      skad=rozklad[pozycja][3];
  }
  else if(rodzaj==PRZYJAZD)
  {
    /*if(rozklad[przyjazd[pozycja][0]][0]==POCIAG_DOCELOWY)
      skad=0;
    else*/
      skad=rozklad[przyjazd[pozycja][0]][3];
  }
  else
  {
    if(rozklad[odjazd[pozycja][0]][0]==POCIAG_ZE_STACJI || rozklad[odjazd[pozycja][0]][0]==POCIAG_DOCELOWY
       || rozklad[odjazd[pozycja][0]][0]==POCIAG_ZE_STACJI_LACZONY || rozklad[odjazd[pozycja][0]][0]==POCIAG_DOCELOWY_ROZLACZANY)
    {
      skad=0;
    }
    else
    {
      skad=rozklad[odjazd[pozycja][0]][3];
    }
  }
  int i;
  for(i=0;nazwa[skad][i]!='\0' && i<MAX_NAZWA-1 ;i++)
    rel[i]=nazwa[skad][i];
  rel[i]='\0';
  return rel;
}

/*******************************************************************************
 *** Funbkcja sortuje wyjsciowy tRozklad jazdy.                              ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  PRZYJAZD - sortuje wzgledem godziny odjazdu                            ***
 ***  ODJAZD - sortuje wzgledem godziny przyjazdu                            ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 18.07.2001                                  ***
 *******************************************************************************/
void tRozklad::Sortuj(int a)
{
  switch (a)
  {
    case ODJAZD: // wzgledem godz. odjazdu
    {
      for(int i=0;i<ilosc_pociagow;i++)
      {
        odjazd[i][0]=i;
        odjazd[i][2]=rozklad[i][12]-rozklad[i][12]/10*10;
        if(rozklad[i][SZEROKOSC-1]==NIEOKRESLONA)
          odjazd[i][1]=rozklad[i][5];
        else
          odjazd[i][1]=rozklad[i][SZEROKOSC-1];
      }
      for (int i=0;i<ilosc_pociagow;i++)
      {
      	for (int j=0;j<ilosc_pociagow-1;j++)
        {
       	  if(odjazd[j][2]>odjazd[j+1][2])
          {
            int a=odjazd[j+1][0];
            int b=odjazd[j+1][1];
            int c=odjazd[j+1][2];
            odjazd[j+1][0]=odjazd[j][0];
            odjazd[j+1][1]=odjazd[j][1];
            odjazd[j+1][2]=odjazd[j][2];
            odjazd[j][0]=a;
            odjazd[j][1]=b;
            odjazd[j][2]=c;
          }
        }
      }
      for (int i=0;i<ilosc_pociagow;i++)
      {
      	for (int j=0;j<ilosc_pociagow-1;j++)
        {
       	  if(odjazd[j][1]>odjazd[j+1][1])
          {
            int a=odjazd[j+1][0];
            int b=odjazd[j+1][1];
            odjazd[j+1][0]=odjazd[j][0];
            odjazd[j+1][1]=odjazd[j][1];
            odjazd[j][0]=a;
            odjazd[j][1]=b;
          }
        }
      }
      break;
    }
    case PRZYJAZD: // wzgledem godz. przyjazdu
    {
      for (int i=0;i<ilosc_pociagow;i++)
      {
        przyjazd[i][0]=i;
        przyjazd[i][2]=rozklad[i][11]-rozklad[i][11]/10*10;
        if(rozklad[i][SZEROKOSC-2]==NIEOKRESLONA)
          przyjazd[i][1]=rozklad[i][1];
        else
          przyjazd[i][1]=rozklad[i][SZEROKOSC-2];
      }
      for (int i=0;i<ilosc_pociagow;i++)
        {
          for (int j=0;j<ilosc_pociagow-1;j++)
          {
            if(przyjazd[j][2]>przyjazd[j+1][2])
              {
                int a=przyjazd[j+1][0];
                int b=przyjazd[j+1][1];
                int c=przyjazd[j+1][2];
                przyjazd[j+1][0]=przyjazd[j][0];
                przyjazd[j+1][1]=przyjazd[j][1];
                przyjazd[j+1][2]=przyjazd[j][2];
                przyjazd[j][0]=a;
                przyjazd[j][1]=b;
                przyjazd[j][2]=c;
              }
          }
        }
      for (int i=0;i<ilosc_pociagow;i++)
        {
          for (int j=0;j<ilosc_pociagow-1;j++)
          {
            if(przyjazd[j][1]>przyjazd[j+1][1])
              {
                int a=przyjazd[j+1][0];
                int b=przyjazd[j+1][1];
                przyjazd[j+1][0]=przyjazd[j][0];
                przyjazd[j+1][1]=przyjazd[j][1];
                przyjazd[j][0]=a;
                przyjazd[j][1]=b;
              }
          }
        }
        break;
      }
   }
}

/*******************************************************************************
 *** Funkcja zwraca lub zmienia stan pociagu.                                ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  ustaw - nowy stan pociagu                                              ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  stan pociagu - byl/jest/bedzie                                         ***
 ***                                                                         ***
 *** Wersja: 0.06                                                            ***
 *** Data ostatniej modyfikacji: 28.06.2003                                  ***
 *******************************************************************************/
int tRozklad::Stan(int pozycja, int rodzaj, int ustaw)
{
  if(pozycja<0) return JEST; //dla powrotu loka
  if(ustaw!=NIEOKRESLONA)
  {
    if(rodzaj==PRZYJAZD)
    {
      rozklad[przyjazd[pozycja][0]][15]=ustaw;
      if(ustaw==WJEZDZA || ustaw==CZEKA_NA_WJAZD)
      {
        //dla pociagu rozlaczanego
        if(rozklad[przyjazd[pozycja][0]][11])
        {
          int godz=rozklad[przyjazd[pozycja][0]][SZEROKOSC-2];
          int rr=przyjazd[pozycja][0];
          rr=rozklad[rr][11]/10;
          for(;;)
          {
            rozklad[rr][SZEROKOSC-2]=godz;
            rozklad[rr][15]=ustaw;
            rr=rozklad[rr][11]/10;
            if(rr==przyjazd[pozycja][0]) break;
          }
        }
      }
      return ustaw;
    }
    else if(rodzaj==ODJAZD)
    {
      rozklad[odjazd[pozycja][0]][15]=ustaw;
      return ustaw;
    }
  }
  if(rodzaj==NIEOKRESLONA && ustaw==NIEOKRESLONA)
    return rozklad[pozycja][15];
  else if(rodzaj==NIEOKRESLONA && ustaw!=NIEOKRESLONA)
  {
    rozklad[pozycja][15]=ustaw;
    return ustaw;
  }
  else if(rodzaj==PRZYJAZD)
  {
    return rozklad[przyjazd[pozycja][0]][15];
  }
  else
  {
    return rozklad[odjazd[pozycja][0]][15];
  }
}

/*******************************************************************************
 *** Funkcja zwraca nazwe lokomotywowni.                                     ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  numer - indeks nazwy lokomotywowni                                     ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  nazwa lokomotywowni                                                    ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 27.11.2001                                  ***
 *******************************************************************************/
char* tRozklad::Szopa(int numer)
{
  if(numer>=ilosc_nazw_szop)
    return 0;
  char* wynik=new char[MAX_NAZWA];
  for(int i=0;i<MAX_NAZWA;i++)
    wynik[i]=nazwa_szopy[numer][i];
  return wynik;
}

/*******************************************************************************
 *** Funkcja zwraca nazwe szopy.                                             ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  punkt - lok przyjezdzajacy/ lok wyjezdzajacy                           ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer szopy                                                            ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 07.12.2001                                  ***
 *******************************************************************************/
int tRozklad::Szopa(int pozycja, int rodzaj, int punkt)
{
  int b;
  if(rodzaj==NIEOKRESLONA)
  {
    if(punkt==PRZYJAZD)
    {
      if(rozklad[pozycja][4]>=1000)
        b=rozklad[pozycja][8];
      else if(rozklad[pozycja][4]<0)
      {
        int t=rozklad[pozycja][4]*(-1);
        if(przejscia[t/1000][5])
          b=0;
        else
          b=przejscia[t/1000][1]*1000;
        t=t-t/1000*1000;
        if(przejscia[t][5])
          b+=0;
        else
          b+=przejscia[t][1];
        b*=(-1);
      }
      else
      {
        if(przejscia[rozklad[pozycja][4]][5])
          b=0;
        else
          b=przejscia[rozklad[pozycja][4]][1];
      }
    }
    else
    {
      if(rozklad[pozycja][4]>=1000)
        b=rozklad[pozycja][8];
      else if(rozklad[pozycja][8]<0)
      {
        int t=rozklad[pozycja][8]*(-1);
        b=przejscia[t/1000][1]*1000;
        t=t-t/1000*1000;
        b+=przejscia[t][1];
        b*=(-1);
      }
      else
        b=przejscia[rozklad[pozycja][8]][1];
    }
  }
  else if(rodzaj==PRZYJAZD)
  {
    if(rozklad[przyjazd[pozycja][0]][4]>=1000)
      b=rozklad[przyjazd[pozycja][0]][8];
    else if(rozklad[przyjazd[pozycja][0]][4]<0)
    {
      int t=rozklad[przyjazd[pozycja][0]][4]*(-1);
      if(przejscia[t/1000][5])
        b=0;
      else
        b=przejscia[t/1000][1]*1000;
      t=t-t/1000*1000;
      if(przejscia[t][5])
        b+=0;
      else
        b+=przejscia[t][1];
      b*=(-1);
    }
    else
    {
      if(przejscia[rozklad[przyjazd[pozycja][0]][4]][5])
        b=0;
      else
        b=przejscia[rozklad[przyjazd[pozycja][0]][4]][1];
    }
    if(rozklad[przyjazd[pozycja][0]][11])
    {
      int t=rozklad[przyjazd[pozycja][0]][11];
      t=t-t/10*10;
      if(t!=1)
        b=NIEOKRESLONA;
    }
  }
  else
  {
    if(rozklad[odjazd[pozycja][0]][4]>=1000)
      b=rozklad[odjazd[pozycja][0]][8];
    else if(rozklad[odjazd[pozycja][0]][8]<0)
    {
      int t=rozklad[odjazd[pozycja][0]][8]*(-1);
      b=przejscia[t/1000][1]*1000;
      t=t-t/1000*1000;
      b+=przejscia[t][1];
      b*=(-1);
    }
    else
      b=przejscia[rozklad[odjazd[pozycja][0]][8]][1];
    if(rozklad[odjazd[pozycja][0]][12])
    {
      int t=rozklad[odjazd[pozycja][0]][12];
      t=t-t/10*10;
      if(t!=1)
        b=NIEOKRESLONA;
    }
  }
  return b;
}

/*******************************************************************************
 *** Funkcja zwraca tor pociagu znajdujacego sie na torach postojowych       ***
 *** na stacji na poczatku gry.                                              ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  wpolrzedne punktu                                                      ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 13.01.2004                                  ***
 *******************************************************************************/
int tRozklad::Tor(int pozycja)
{
  return rozklad[pozycja][24];
}

/*******************************************************************************
 *** Funkcja zwraca/ustawia typ pociagu.                                     ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***  ustaw - nowy typ pociagu                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  rodzaj pociagu                                                         ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 28.06.2003                                  ***
 *******************************************************************************/
int tRozklad::TypPociagu(int pozycja, int rodzaj, int ustaw)
{
  if(pozycja<0) return POWROT_LOKA;
  if(ustaw!=NIEOKRESLONA)
  {
    if(rodzaj==NIEOKRESLONA)
    {
      rozklad[pozycja][0]=ustaw;
      return rozklad[pozycja][0];
    }
    else if(rodzaj==PRZYJAZD)
    {
      rozklad[przyjazd[pozycja][0]][0]=ustaw;
      return rozklad[przyjazd[pozycja][0]][0];
    }
    else
    {
      rozklad[odjazd[pozycja][0]][0]=ustaw;
      return rozklad[odjazd[pozycja][0]][0];
    }
  }
  else
  {
    if(rodzaj==NIEOKRESLONA)
    {
      return rozklad[pozycja][0];
    }
    else if(rodzaj==PRZYJAZD)
    {
      return rozklad[przyjazd[pozycja][0]][0];
    }
    else
    {
      return rozklad[odjazd[pozycja][0]][0];
    }
  }
}

/*******************************************************************************
 *** Funkcja wczytuje rozklad jazdy z pliku.                                 ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  nazwa_pliku - nazwa pliku do wczytania                                 ***
 ***  nazwy_rysunkow - tablica z nazwami plikow (ze stacji)                  ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 *** godzina rozpoczecia gry                                                 ***
 *** -1 - blad odczytu pliku *.roz                                           ***
 *** -2 - blad w opisie laczenia/rozlaczania                                 ***
 ***                                                                         ***
 *** Wersja: 0.30                                                            ***
 *** Data ostatniej modyfikacji: 02.07.2005                                  ***
 *******************************************************************************/
int tRozklad::Wczytaj(char * nazwa_pliku, char nazwy_rysunkow[][DLUGOSC_NAZWY_PLIKU])
{
   ifstream plik;
   plik.open(nazwa_pliku);
   if(!plik.good()) return -1;
   int w,wersja;
   plik>>w;
   plik.ignore(2);
   char nic[30];
   plik.getline(nic,30);
   int pomin;
   plik>>pomin;
   plik.ignore(1);
   for(int i=0;i<3*pomin;i++)
   {
     plik>>wersja;
     plik.ignore(1);
   }
   if(w>1)
   {//pominiecie punktow dla lokow na stacji
     for(int i=0;i<3*pomin;i++)
     {
       plik>>wersja;
       plik.ignore(1);
     }
   }
   plik>>ilosc_pociagow;
   plik.ignore(1);
   if(ilosc_pociagow<0)
   {
     ilosc_pociagow*=(-1);
     bocznica_towarowe=true;
   }
   else
     bocznica_towarowe=false;
   rozklad.tworz(2*ilosc_pociagow,SZEROKOSC);
   przyjazd.tworz(2*ilosc_pociagow,3);
   odjazd.tworz(2*ilosc_pociagow,3);
   for(int i=0;i<ilosc_pociagow;i++)
   {
     for(int j=0;j<SZEROKOSC-2;j++)
     {
       int oo;
       plik>>oo;
       rozklad[i][j]=oo;
       plik.ignore();
     }
     rozklad[i][SZEROKOSC-2]=NIEOKRESLONA;
     rozklad[i][SZEROKOSC-1]=NIEOKRESLONA;
     rozklad[i][4]*=1000;
     if((rozklad[i][0]==POCIAG_PRZELOTOWY || rozklad[i][0]==POCIAG_ROZLACZANY)&& rozklad[i][11] && rozklad[i][11]==rozklad[i][12])
       return -2;
   }
   int godzina;
   plik>>godzina;
   plik.ignore(1);
   plik>>ilosc_przejsc;
   plik.ignore(1);
   przejscia.tworz(ilosc_przejsc,DLUGOSC_PRZEJSC);
   for(int i=0;i<ilosc_przejsc;i++)
   {
     for(int j=0;j<DLUGOSC_PRZEJSC-2;j++)
     {
       plik>>przejscia[i][j];
       plik.ignore(1);
     }
     przejscia[i][5]=przejscia[i][6]=0;
     if(przejscia[i][0]<0)
     {
       przejscia[i][0]*=(-1);
       rozklad[Przejscia(i,2)][4]=rozklad[Przejscia(i,2)][8]=rozklad[Przejscia(i,3)][4]=rozklad[Przejscia(i,3)][8]=i;
     }
     else
     {
       if(rozklad[Przejscia(i,2)][4])
         rozklad[Przejscia(i,2)][4]=(rozklad[Przejscia(i,2)][4]*1000+i)*(-1);
       else
         rozklad[Przejscia(i,2)][4]=i;
       if(rozklad[Przejscia(i,3)][8])
         rozklad[Przejscia(i,3)][8]=(rozklad[Przejscia(i,3)][8]*1000+i)*(-1);
       else
         rozklad[Przejscia(i,3)][8]=i;
     }
   }
   plik>>ilosc_nazw_lokow;
   plik.ignore(1);
   plik>>ilosc_prawdopodobienstw;
   plik.ignore(1);
   prawdopodobienstwa.tworz(ilosc_prawdopodobienstw,ilosc_nazw_lokow);
   for(int i=0;i<ilosc_prawdopodobienstw;i++)
     for(int j=0;j<ilosc_nazw_lokow;j++)
     {
       plik>>prawdopodobienstwa[i][j];
       plik.ignore(1);
     }
   plik>>ilosc_skladow;
   plik.ignore(1);
   sklady.tworz(ilosc_skladow,DLUGOSC_SKLADU);
   for(int i=0;i<ilosc_skladow;i++)
   {
     for(int j=0;j<DLUGOSC_SKLADU;j++)
     {
       plik>>sklady[i][j];
       plik.ignore(1);
       if(sklady[i][j]==0)
         break;
     }
   }

   int ilosc_nazw_wagonow;
   plik>>ilosc_nazw_wagonow;
   plik.ignore(2);
   ilosc_rysunkow=ilosc_nazw_wagonow+ilosc_nazw_lokow;
   hierarchia_lokow.tworz(ilosc_nazw_lokow,1);
   char bufor[100];
   int nr;
   for(nr=1;nr<=ilosc_nazw_lokow;nr++)
   {
     plik.getline(bufor,99);
     char* a=strtok(bufor," ");
     strcpy(nazwy_rysunkow[nr],a);
     a=strtok(NULL," ");
     strcpy(nazwa_typu[nr],a);
     a=strtok(NULL," ");
     numer_typu[nr]=(int)a[0]-48;
     a=strtok(NULL," ");
     hierarchia_lokow[nr-1][0]=(int)a[0]-48;
   }
   for(;nr<=ilosc_nazw_wagonow+ilosc_nazw_lokow;nr++)
   {
     plik.getline(bufor,99);
     char* a=strtok(bufor," ");
     strcpy(nazwy_rysunkow[nr],a);
   }
   plik>>ilosc_nazw_szop;
   plik.ignore(2);
   nazwa_szopy.tworz(ilosc_nazw_szop,MAX_NAZWA);
   for (int i=0;i<ilosc_nazw_szop;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       nazwa_szopy[i][j]=NULL;
   for (int i=0;i<ilosc_nazw_szop;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       if((nazwa_szopy[i][j]=plik.get())=='\n')
       {
          nazwa_szopy[i][j]=NULL;
	  break;
       }
   plik>>ilosc_stacji;
   plik.ignore(2);
   nazwa.tworz(ilosc_stacji,MAX_NAZWA);
   for (int i=0;i<ilosc_stacji;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       nazwa[i][j]=NULL;
   for (int i=0;i<ilosc_stacji;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       if((nazwa[i][j]=plik.get())=='\n')
       {
          nazwa[i][j]=NULL;
	  break;
       }
   plik>>ilosc_nazw_pociagow;
   plik.ignore(2);
   nazwa_pociagu.tworz(ilosc_nazw_pociagow,MAX_NAZWA);
   for (int i=0;i<ilosc_nazw_pociagow;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       nazwa_pociagu[i][j]=NULL;
   for (int i=0;i<ilosc_nazw_pociagow;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       if((nazwa_pociagu[i][j]=plik.get())=='\n')
       {
          nazwa_pociagu[i][j]=NULL;
	  break;
       }
   if(w>2)
   {
     int ilosc;
     plik>>ilosc;
     for(int i=0;i<ilosc;i++)
     {
       plik.ignore(1);
       int ind;
       plik>>ind;
       plik.ignore(1);
       plik>>typ_rodzaju_pociagu[ind];
       plik.ignore(1);
       plik>>nazwa_typ_rodzaju_pociagu[ind][0][0]>>nazwa_typ_rodzaju_pociagu[ind][0][1]>>nazwa_typ_rodzaju_pociagu[ind][0][2];
       plik.ignore(1);
       plik>>nazwa_typ_rodzaju_pociagu[ind][1][0];
     }
   }
   plik.close();
   Sortuj(PRZYJAZD);
   Sortuj(ODJAZD);
   for(int i=0;i<ilosc_pociagow;i++)
   {
     if(rozklad[i][11]-rozklad[i][11]/10*10==1)
     {
       for(int j=i;;)
       {
         j=rozklad[j][11]/10;
         if(j==i) break;
         if(!rozklad[j][4]) rozklad[j][4]=rozklad[i][4];
       }
     }
     if(rozklad[i][12]-rozklad[i][12]/10*10==1)
     {
       for(int j=i;;)
       {
         j=rozklad[j][12]/10;
         if(j==i) break;
         if(!rozklad[j][8]) rozklad[j][8]=rozklad[i][8];
       }
     }
   }
   return godzina;
}/*tRozklad::wczytaj*/

/*******************************************************************************
 *** Funkcja wczytuje rozklad jazdy z pliku ze stanem stacji.                ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  nazwa_pliku - nazwa pliku do wczytania                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 *** 0 -OK                                                                   ***
 *** 1 - blad odczytu pliku *.roz                                            ***
 ***                                                                         ***
 *** Wersja: 0.13                                                            ***
 *** Data ostatniej modyfikacji: 03.07.2005                                  ***
 *******************************************************************************/
int tRozklad::WczytajStan(streampos pozycja, char * nazwa_pliku)
{
   ifstream plik;
   plik.open(nazwa_pliku);
   if(!plik.good()) return 1;
   int wersja;
   plik>>wersja;
   plik.seekg(pozycja);
   plik>>ilosc_pociagow;
   plik.ignore(1);
   rozklad.tworz(2*ilosc_pociagow,SZEROKOSC);
   przyjazd.tworz(2*ilosc_pociagow,3);
   odjazd.tworz(2*ilosc_pociagow,3);
   for(int i=0;i<ilosc_pociagow;i++)
   {
     for(int j=0;j<SZEROKOSC;j++)
     {
       plik>>rozklad[i][j];
       plik.ignore();
     }
   }
   plik>>ilosc_przejsc;
   plik.ignore(1);
   przejscia.tworz(ilosc_przejsc,DLUGOSC_PRZEJSC);
   for(int i=0;i<ilosc_przejsc;i++)
   {
     for(int j=0;j<DLUGOSC_PRZEJSC;j++)
     {
       plik>>przejscia[i][j];
       plik.ignore(1);
     }
   }
   plik>>ilosc_skladow;
   plik.ignore(1);
   sklady.tworz(ilosc_skladow,DLUGOSC_SKLADU);
   for(int i=0;i<ilosc_skladow;i++)
   {
     for(int j=0;j<DLUGOSC_SKLADU;j++)
     {
       plik>>sklady[i][j];
       plik.ignore(1);
       if(sklady[i][j]==0)
         break;
     }
   }
   plik>>ilosc_stacji;
   plik.ignore(2);
   nazwa.tworz(ilosc_stacji,MAX_NAZWA);
   for (int i=0;i<ilosc_stacji;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       nazwa[i][j]=NULL;
   for (int i=0;i<ilosc_stacji;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       if((nazwa[i][j]=plik.get())=='\n')
       {
          nazwa[i][j]=NULL;
	  break;
       }
   plik.ignore(1);
   for (int i=1;i<=ilosc_rysunkow;i++)
     for (int j=0;j<20;j++)
       if((nazwa_typu[i][j]=plik.get())=='\n')
       {
          nazwa_typu[i][j]=NULL;
	  break;
       }
   for (int i=1;i<=ilosc_rysunkow;i++)
   {
     plik>>numer_typu[i];
     plik.ignore(1);
   }
   plik>>ilosc_nazw_szop;
   plik.ignore(2);
   nazwa_szopy.tworz(ilosc_nazw_szop,MAX_NAZWA);
   for (int i=0;i<ilosc_nazw_szop;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       nazwa_szopy[i][j]=NULL;
   for (int i=0;i<ilosc_nazw_szop;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       if((nazwa_szopy[i][j]=plik.get())=='\n')
       {
          nazwa_szopy[i][j]=NULL;
	  break;
       }
   plik>>ilosc_nazw_lokow;
   plik.ignore(1);
   plik>>ilosc_prawdopodobienstw;
   plik.ignore(1);
   prawdopodobienstwa.tworz(ilosc_prawdopodobienstw,ilosc_nazw_lokow);
   for(int i=0;i<ilosc_prawdopodobienstw;i++)
     for(int j=0;j<ilosc_nazw_lokow;j++)
     {
       plik>>prawdopodobienstwa[i][j];
       plik.ignore(1);
     }
   plik>>ilosc_nazw_pociagow;
   plik.ignore(2);
   nazwa_pociagu.tworz(ilosc_nazw_pociagow,MAX_NAZWA);
   for (int i=0;i<ilosc_nazw_pociagow;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       nazwa_pociagu[i][j]=NULL;
   for (int i=0;i<ilosc_nazw_pociagow;i++)
     for (int j=0;j<MAX_NAZWA;j++)
       if((nazwa_pociagu[i][j]=plik.get())=='\n')
       {
          nazwa_pociagu[i][j]=NULL;
	  break;
       }
   hierarchia_lokow.tworz(ilosc_nazw_lokow,1);
   for(int i=0;i<ilosc_nazw_lokow;i++)
   {
     plik>>hierarchia_lokow[i][0];
     plik.ignore(1);
   }
   if(wersja>2)
   {
     for(int i=0;i<250;i++)
     {
       plik>>typ_rodzaju_pociagu[i];
       plik.ignore(1);
       plik>>nazwa_typ_rodzaju_pociagu[i][0][0]>>nazwa_typ_rodzaju_pociagu[i][0][1]>>nazwa_typ_rodzaju_pociagu[i][0][2];
       plik.ignore(1);
       plik>>nazwa_typ_rodzaju_pociagu[i][1][0];
     }
     plik>>gra_testowa;
   }
   else
     gra_testowa=false;
   plik.close();
   Sortuj(PRZYJAZD);
   Sortuj(ODJAZD);
   return 0;
}


/*******************************************************************************
 *** Funkcja zwraca numer wjazdu.                                            ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer wjazdu                                                           ***
 ***                                                                         ***
 *** Wersja: 0.04                                                            ***
 *** Data ostatniej modyfikacji: 21.04.2003                                  ***
 *******************************************************************************/
int tRozklad::Wjazd(int pozycja, int rodzaj)
{
  if(rodzaj==PRZYJAZD)
  { 
    return rozklad[przyjazd[pozycja][0]][2];
  }
  else if(rodzaj==ODJAZD)
  {
    return rozklad[odjazd[pozycja][0]][2];
  }
  else
    return rozklad[pozycja][2];
}

/*******************************************************************************
 *** Funkcja zwraca wspolrzedne punktu dla pociagow znajdujacych sie         ***
 *** na stacji na poczatku gry.                                              ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  wpolrzedne punktu                                                      ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji: 13.01.2004                                  ***
 *******************************************************************************/
int tRozklad::Wspolrzedna(int pozycja)
{
  return rozklad[pozycja][22];
}

/*******************************************************************************
 *** Funkcja zwraca numer wyjazdu.                                           ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  pozycja - pozycja pociagu w rozkladzie                                 ***
 ***  rodzaj - przyjazd/odjazd                                               ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  numer wyjazdu                                                          ***
 ***                                                                         ***
 *** Wersja: 0.03                                                            ***
 *** Data ostatniej modyfikacji: 12.08.2001                                  ***
 *******************************************************************************/
int tRozklad::Wyjazd(int pozycja, int rodzaj)
{
  if(rodzaj==NIEOKRESLONA)
  {
    return rozklad[pozycja][6];
  }
  else if(rodzaj==PRZYJAZD)
  {
    return rozklad[przyjazd[pozycja][0]][6];
  }
  else
  {
    return rozklad[odjazd[pozycja][0]][6];
  }
}

/*******************************************************************************
 *** Funkcja zwraca lub ustawia wyprzedzenie.                                ***
 ***                                                                         ***
 *** Parametry:                                                              ***
 ***  ustaw - wyprzedzenie do ustawienia                                     ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  wyprzedzenie                                                           ***
 ***                                                                         ***
 *** Wersja: 0.01                                                            ***
 *** Data ostatniej modyfikacji :22.07.2001                                  ***
 *******************************************************************************/
int tRozklad::Wyprzedzenie(int ustaw)
{
  if(ustaw!=NIEOKRESLONA)
  {
    if(ustaw>15)
     wyprzedzenie=ustaw;
    else
      wyprzedzenie=15;
  }
  return wyprzedzenie;
}

/*******************************************************************************
 *** Funkcja sluzy do zapisania rozkladu.                                    ***
 ***                                                                         ***
 *** Parametr:                                                               ***
 ***  nazwa_pliku - nazwa pliku do zapisania                                 ***
 ***                                                                         ***
 *** Zwracana wartosc:                                                       ***
 ***  0 - OK                                                                 ***
 ***  1 - blad otwarcia strumienia                                           ***
 ***                                                                         ***
 *** Wersja: 0.13                                                            ***
 *** Data ostatniej modyfikacji: 03.07.2005                                  ***
 ******************************************************************************/
int tRozklad::ZapiszRozklad(char *nazwa_pliku)
{
  ofstream plik;
  plik.open(nazwa_pliku,ios_base::app);
  if(!plik.good()) return 1;
  plik<<ilosc_pociagow<<","<<endl;
  for(int i=0;i<ilosc_pociagow;i++)
  {
    for(int j=0;j<SZEROKOSC;j++)
    {
      plik<<rozklad[i][j]<<",";
    }
    plik<<endl;
  }
  plik<<ilosc_przejsc<<","<<endl;
  for(int i=0;i<ilosc_przejsc;i++)
  {
    for(int j=0;j<DLUGOSC_PRZEJSC;j++)
      plik<<przejscia[i][j]<<",";
    plik<<endl;
  }

  plik<<ilosc_skladow<<","<<endl;
  for(int i=0;i<ilosc_skladow;i++)
   {
     for(int j=0;j<DLUGOSC_SKLADU;j++)
     {
       plik<<sklady[i][j]<<",";
       if(sklady[i][j]==0)
       {
         plik<<endl;
         break;
       }
     }
   }

  plik<<ilosc_stacji<<","<<endl;
  for(int i=0;i<ilosc_stacji;i++)
  {
    for (int j=0;j<MAX_NAZWA;j++)
    {
      plik<<nazwa[i][j];
    }
  }
  plik<<endl;
  for(int i=1;i<=ilosc_rysunkow;i++)
  {
    plik.write(nazwa_typu[i],20);
  }
  plik<<endl;
  for(int i=1;i<=ilosc_rysunkow;i++)
  {
    plik<<numer_typu[i]<<',';
  }
  plik<<ilosc_nazw_szop<<","<<endl;
  for(int i=0;i<ilosc_nazw_szop;i++)
  {
    for (int j=0;j<MAX_NAZWA;j++)
    {
      plik<<nazwa_szopy[i][j];
    }
  }
  plik<<endl<<ilosc_nazw_lokow<<","<<ilosc_prawdopodobienstw<<","<<endl;
  for(int i=0;i<ilosc_prawdopodobienstw;i++)
  {
    for(int j=0;j<ilosc_nazw_lokow;j++)
    {
      plik<<prawdopodobienstwa[i][j]<<",";
    }
    plik<<endl;
  }
  plik<<ilosc_nazw_pociagow<<","<<endl;
  for(int i=0;i<ilosc_nazw_pociagow;i++)
  {
    for(int j=0;j<MAX_NAZWA;j++)
    {
      plik<<nazwa_pociagu[i][j];
    }
  }
  plik<<endl;
  for(int i=0;i<ilosc_nazw_lokow;i++)
    plik<<hierarchia_lokow[i][0]<<",";
  plik<<endl;
  for(int i=0;i<250;i++)
  {
    plik<<typ_rodzaju_pociagu[i]<<" "<<nazwa_typ_rodzaju_pociagu[i][0][0]<<
    nazwa_typ_rodzaju_pociagu[i][0][1]<<nazwa_typ_rodzaju_pociagu[i][0][2]<<" "<<
    nazwa_typ_rodzaju_pociagu[i][1][0]<<endl;
  }
  plik<<endl;
  plik<<gra_testowa;
  plik.close();
  return 0;
}


