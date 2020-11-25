#ifndef	H_PLANSZA
#define H_PLANSZA

extern BITMAP *dblbuffer;//drugi bufor

class plansza{
public:
	int pole[22][16];//plansza 21:14
	void rysuj_plansze();
	void zerowanie_planszy();
	int szerokosc;
	int wysokosc;
	int sprawdz_linia();
	void obniz(int n);
	void rysuj_element_klocka(int x, int y, int kolor, int szerokosc);
	void zaciemnij(int x1, int y1, int x2, int y2, int ile, int tryb, BITMAP *bitm);
};

#endif