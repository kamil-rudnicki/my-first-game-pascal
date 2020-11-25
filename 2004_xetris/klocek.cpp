#include "naglowki.h"

void klocek::losuj()
{
int i=rand()%7;

if(i==0){	  ilosc_obrotow=2; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }
else if(i==1){ilosc_obrotow=4; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }
else if(i==2){ilosc_obrotow=4; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }
else if(i==3){ilosc_obrotow=1; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }
else if(i==4){ilosc_obrotow=4; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }
else if(i==5){ilosc_obrotow=2; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }
else if(i==6){ilosc_obrotow=2; aktualny_obrot=rand()%ilosc_obrotow+1; wprowadz(i,aktualny_obrot); }

numer=i;
}

//**********************************************************************

int klocek::szerokosc()
{
int i=0;
int a=0;

for(int m=0; m<4; m++){
	for(int n=0; n<4; n++) if(tab[m][n]!=0) i=n;
	if(i>a) a=i;
}

return a+1;
}

//**********************************************************************

int klocek::wysokosc()
{
int i=0;
int a=0;

for(int m=0; m<4; m++){
	for(int n=0; n<4; n++) if(tab[n][m]!=0) i=n;
	if(i>a) a=i;
}

return a+1;
}

//**********************************************************************

void klocek::wstaw(int x, int y, plansza &p)
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) if(tab[i][j]!=0) p.pole[y+i][x+j]=tab[i][j];
}

//**********************************************************************

void klocek::usun(int x, int y, plansza &p)
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) if(tab[i][j]!=0) p.pole[y+i][x+j]=0;
}

//**********************************************************************

int klocek::sprawdz(int x, int y, plansza &p)
{
	for(int m=0; m<4; m++){
		for(int n=0; n<4; n++){
			if(tab[n][m]!=0){
				if(p.pole[y+n][x+m]!=0) return 1;

			}
		}
	}
	
return 0;
}



//**********************************************************************

void klocek::obroc_lewo()
{
	if(aktualny_obrot==1) aktualny_obrot=ilosc_obrotow;
	else aktualny_obrot--;
	wprowadz(numer,aktualny_obrot);
}

//**********************************************************************

void klocek::obroc_prawo()
{
	if(aktualny_obrot==ilosc_obrotow) aktualny_obrot=1;
	else aktualny_obrot++;
	wprowadz(numer,aktualny_obrot);
}

//**********************************************************************

void klocek::wprowadz(int num,int obr)
{
	if(num==0){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek1_1[m][n];
		else if(obr==2) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek1_2[m][n];
	}else if(num==1){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek2_1[m][n];
		else if(obr==2) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek2_2[m][n];
		else if(obr==3) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek2_3[m][n];
		else if(obr==4) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek2_4[m][n];
	}else if(num==2){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek3_1[m][n];
		else if(obr==2) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek3_2[m][n];
		else if(obr==3) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek3_3[m][n];
		else if(obr==4) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek3_4[m][n];
	}else if(num==3){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek4_1[m][n];
	}else if(num==4){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek5_1[m][n];
		else if(obr==2) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek5_2[m][n];
		else if(obr==3) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek5_3[m][n];
		else if(obr==4) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek5_4[m][n];
	}else if(num==5){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek6_1[m][n];
		else if(obr==2) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek6_2[m][n];
	}else if(num==6){
		if(obr==1)		for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek7_1[m][n];
		else if(obr==2) for(int m=0; m<4; m++) for(int n=0; n<4; n++) tab[m][n]=klocek7_2[m][n];
	}
}

//**********************************************************************

void klocek::wyswietl(int x, int y)
{
	plansza plansza;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
		if(tab[i][j]!=0) plansza.rysuj_element_klocka((j*20)+x, (i*20)+y, tab[i][j], 20);
}

//**********************************************************************