//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// zmienne globalne			//
//////////////////////////////

#ifndef ZASOBY_H
#define ZASOBY_H

bool losowo1=false;
bool aktywne1=false;
bool poruszeniumyszka1=false;
bool mysza1=false;
bool klawiatura1=false;
bool zwinamp1=false;

POINT poz_kursora;
com1 com1;		
com2 com2;	
int tryb=0;
HINSTANCE hInst;
HWND hOkno;	
int  window_x=450;		
int  window_y=300;
HFONT hFont;				//czcionka

//bufor dla pluginu
HANDLE hMapFile;
char *pBuf;
#define BUF_SIZE 128
TCHAR szName[]=TEXT("LEDCOMBETAHE");

void zgas();
void zaswiec();

#define klasa_okna "ledcom"
#define WM_TRAY WM_USER+1
#define sciezka "ledcom.ini"

#define timer_ID 100
#define timer1_ID 121
#define tray_ID 101
#define IDB_BALL 102

#define ustawienia_ID 103
#define o_programie_ID 104
#define groupcom_ID 109

#define com1_ID 105
#define com2_ID 106
#define com12_ID 107
#define brak_ID 108

#define com1_tab 110
#define com2_tab 111
#define com12_tab 112
#define brak_tab 113

#define poruszeniumyszka 115
#define klawiatura 116
#define mysza 117
#define aktywne 118
#define losowo 119
#define trackbar 120
#define zwinamp 121
#define brak1 122
#define brak2 123

#endif