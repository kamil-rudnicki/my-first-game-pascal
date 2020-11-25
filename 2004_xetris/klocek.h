#ifndef	H_KLOCEK
#define H_KLOCEK

#include "plansza.h"

class klocek{
public:
	void wstaw(int x, int y, plansza &p);
	void usun(int x, int y, plansza &p);
	void losuj();
	int sprawdz(int x, int y, plansza &p);
	void obroc_lewo();
	void obroc_prawo();
	void wprowadz(int num, int obr);
	void wyswietl(int x, int y);
	int tab[4][4];

private:
	int numer;
	int ilosc_obrotow;
	int aktualny_obrot;
	int szerokosc();
	int wysokosc();
	
};

#endif




