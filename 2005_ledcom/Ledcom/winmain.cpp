//////////////////////////////////////////
//			LEDCOM ver. 1.0				//
//			Kamil Rudnicki				//
//  www.caru.w.pl www.hardheads.prv.pl	//
//										//
//  Program do zaswiecania i gaszenia	//
//   diod podlaczonych do portow COM	//
//										//
// Data ostatniej kompilacji 28.11.2004 //
//////////////////////////////////////////

#include <windows.h>
#include <commctrl.h>
#include <windowsx.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include "com.h"
#include "zasoby.h"
#include "resource.h"
#include "winmain.h"

//--------------------------------------------------------------

HWND hCom;					//radiobuttony
WNDPROC WndProc[5];			//komunikat
NOTIFYICONDATA tray;		//tray
HBITMAP g_hbmBall = NULL;	//logo
HBITMAP g_hbmMask = NULL;	//logo

#include "proc_api_main.h"
#include "proc_api_groupbox.h"
#include "proc_api_com1.h"
#include "proc_api_com2.h"
#include "proc_api_com12.h"
#include "proc_api_none.h"

//--------------------------------------------------------------

LRESULT InitWindows(HWND hWND)
{
	srand((unsigned)time(NULL));
	SetTimer(hWND, timer1_ID, 40, NULL); 
	hFont=CreateFont(14,0,0,0,0,0,0,0,0,0,0,0,0,"Arial");

	//--------------------------------------------------------------

	hCom=CreateWindow("button", "Porty:", WS_CHILD | BS_GROUPBOX | WS_VISIBLE | WS_TABSTOP, 5, 80, 80, 120, hOkno, (HMENU) groupcom_ID, hInst, NULL );
	CreateWindow("button", "BRAK", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_MULTILINE | BS_FLAT,5,20,70,18,hCom,(HMENU)brak_ID,hInst,NULL);
	CreateWindow("button", "COM1", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_MULTILINE | BS_FLAT,5,40,70,18,hCom,(HMENU)com1_ID,hInst,NULL);
	CreateWindow("button", "COM2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_MULTILINE | BS_FLAT,5,60,70,18,hCom,(HMENU)com2_ID,hInst,NULL);
	CreateWindow("button", "COM1\nCOM2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_MULTILINE | BS_FLAT,5,80,70,30,hCom,(HMENU)com12_ID,hInst,NULL);
	CreateWindow("button", "Ustawienia", WS_CHILD | WS_VISIBLE,5,210,80,25,hWND,(HMENU)ustawienia_ID,hInst,NULL);
	CreateWindow("button", "O programie", WS_CHILD | WS_VISIBLE,5,239,80,25,hWND,(HMENU)o_programie_ID,hInst,NULL);

	SendMessage(GetDlgItem(hCom, com12_ID), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(hCom, com1_ID), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(hCom, com2_ID), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(hCom, brak_ID), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(hWND, groupcom_ID), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(hWND, ustawienia_ID), WM_SETFONT, (WPARAM)hFont, TRUE); 
	SendMessage(GetDlgItem(hWND, o_programie_ID), WM_SETFONT, (WPARAM)hFont, TRUE); 

	WndProc[0]=(WNDPROC)SetWindowLong(hCom, GWL_WNDPROC, (LONG)WndNewProc);

	CreateWindowEx(0, WC_TABCONTROL, 0, WS_CHILD | TCS_BOTTOM | TCS_FIXEDWIDTH, 95, 5, 343, 260, hOkno, (HMENU)brak_tab, hInst, NULL); 
	CreateWindowEx(0, WC_TABCONTROL, 0, WS_CHILD | TCS_BOTTOM | TCS_FIXEDWIDTH, 95, 5, 343, 260, hOkno, (HMENU)com1_tab, hInst, NULL); 
	CreateWindowEx(0, WC_TABCONTROL, 0, WS_CHILD | TCS_BOTTOM | TCS_FIXEDWIDTH, 95, 5, 343, 260, hOkno, (HMENU)com2_tab, hInst, NULL); 
	CreateWindowEx(0, WC_TABCONTROL, 0, WS_CHILD | TCS_BOTTOM | TCS_FIXEDWIDTH, 95, 5, 343, 260, hOkno, (HMENU)com12_tab, hInst, NULL); 
	
	CreateWindow("button", "Po kliknieciu:", WS_CHILD | BS_GROUPBOX | WS_VISIBLE | WS_TABSTOP, 15, 10, 120, 80, GetDlgItem(hOkno, com1_tab), (HMENU)brak1, hInst, NULL );
		CreateWindow("button", "klawiatury", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX ,25,40,70,18,GetDlgItem(hOkno, com1_tab),(HMENU)klawiatura,hInst,NULL);
		CreateWindow("button", "myszy", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX ,25,60,70,18,GetDlgItem(hOkno, com1_tab),(HMENU)mysza,hInst,NULL);
	CreateWindow("button", "Czestotliwosc mrugania:", WS_CHILD | BS_GROUPBOX | WS_VISIBLE | WS_TABSTOP, 70, 120, 180, 110, GetDlgItem(hOkno, com1_tab), (HMENU)brak2, hInst, NULL );
	CreateWindow("button", "po ruszeniu mysza", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX ,160,20,120,18,GetDlgItem(hOkno, com1_tab),(HMENU)poruszeniumyszka,hInst,NULL);
	CreateWindow("button", "w rytm muzyki z WINAMP'a\n(nalezy zainstalowac i aktywowac plugin lcplugin.exe)", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_MULTILINE,160,50,175,40,GetDlgItem(hOkno, com1_tab),(HMENU)zwinamp,hInst,NULL);
	CreateWindow("button", "aktywne", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX ,80,150,100,18,GetDlgItem(hOkno, com1_tab),(HMENU)aktywne,hInst,NULL);
		CreateWindow("button", "losowo", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX ,80,200,100,18,GetDlgItem(hOkno, com1_tab),(HMENU)losowo,hInst,NULL);
		CreateWindowEx(0, TRACKBAR_CLASS, 0, WS_CHILD | WS_VISIBLE | TBS_ENABLESELRANGE | TBS_AUTOTICKS , 75, 173, 170, 20, GetDlgItem(hOkno, com1_tab), (HMENU)trackbar, hInst, NULL); 
	
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), brak1), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), brak2), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), klawiatura), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), mysza), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), poruszeniumyszka), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), aktywne), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), losowo), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), zwinamp), WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), TBM_SETRANGE, (WPARAM) TRUE, (LPARAM) MAKELONG(0, 25));
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), losowo), false);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), false);

	if(GetPrivateProfileInt("ustawienia","zapisuj",1,sciezka))
	{
		if(GetPrivateProfileInt("com1and2","czestotliwosc",0,sciezka)){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), aktywne), BM_SETCHECK, 1, 0);
			aktywne1=true;
			EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), losowo), true);
			EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), true);
		}
		if(GetPrivateProfileInt("com1and2","losowo",0,sciezka)){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), losowo), BM_SETCHECK, 1, 0);
			losowo1=true;
		}
		if(GetPrivateProfileInt("com1and2","poruszeniumyszka",0,sciezka)){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), poruszeniumyszka), BM_SETCHECK, 1, 0);
			poruszeniumyszka1=true;
		}
		if(GetPrivateProfileInt("com1and2","winamp",0,sciezka)){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), zwinamp), BM_SETCHECK, 1, 0);
			zwinamp1=true;
			hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szName);
		}
		if(GetPrivateProfileInt("com1and2","myszklik",0,sciezka)){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), mysza), BM_SETCHECK, 1, 0);
			mysza1=true;
		}
		if(GetPrivateProfileInt("com1and2","klawiaturaklik",0,sciezka)){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), klawiatura), BM_SETCHECK, 1, 0);
			klawiatura1=true;
		}

		int szybkosc=GetPrivateProfileInt("com1and2","szybkosc",0,sciezka);
		if(szybkosc){
			SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), TBM_SETPOS, (WPARAM) true, (LPARAM) szybkosc);
			if(szybkosc==0) szybkosc=1;
		}
		SetTimer(hWND, timer_ID, szybkosc*100, NULL);
	}
	else SetTimer(hWND, timer_ID, 100, NULL);
	

	//Podpinamy swoj¹ obs³ugê komunikatów do okien roboczych
	WndProc[1]=(WNDPROC)SetWindowLong(GetDlgItem(hOkno, brak_tab), GWL_WNDPROC, (LONG)WndBRAKProc);
	WndProc[2]=(WNDPROC)SetWindowLong(GetDlgItem(hOkno, com1_tab), GWL_WNDPROC, (LONG)WndCOM1Proc);
	WndProc[3]=(WNDPROC)SetWindowLong(GetDlgItem(hOkno, com2_tab), GWL_WNDPROC, (LONG)WndCOM2Proc);
	WndProc[4]=(WNDPROC)SetWindowLong(GetDlgItem(hOkno, com12_tab), GWL_WNDPROC, (LONG)WndCOM12Proc);
	
	//wczytanie ktory port jest aktywny
	if(GetPrivateProfileInt("ustawienia","zapisuj",0,sciezka)==1)
	{
			 if(GetPrivateProfileInt("ustawienia","com",0,sciezka)==1){ SendMessage(hCom, WM_COMMAND, com1_ID, 0); SendMessage(GetDlgItem(hCom, com1_ID), BM_SETCHECK, 1, 0); tryb=com1_ID;}
		else if(GetPrivateProfileInt("ustawienia","com",0,sciezka)==2){ SendMessage(hCom, WM_COMMAND, com2_ID, 0); SendMessage(GetDlgItem(hCom, com2_ID), BM_SETCHECK, 1, 0); tryb=com1_ID;}
		else if(GetPrivateProfileInt("ustawienia","com",0,sciezka)==3){ SendMessage(hCom, WM_COMMAND, com12_ID, 0); SendMessage(GetDlgItem(hCom, com12_ID), BM_SETCHECK, 1, 0); tryb=com12_ID;}
		else{ SendMessage(hCom, WM_COMMAND, brak_ID, 0); SendMessage(GetDlgItem(hCom, brak_ID), BM_SETCHECK, 1, 0); tryb=brak_ID;}
	}
	else
	{
		SendMessage(hCom, WM_COMMAND, brak_ID, 0); 
		SendMessage(GetDlgItem(hCom, brak_ID), BM_SETCHECK, 1, 0);
		tryb=brak_ID;
	}

	return true;
}

//--------------------------------------------------------------

LRESULT DeleteWindows(HWND hWND)
{
	UnregisterClass(klasa_okna, hInst);
	DestroyWindow(hWND);
	KillTimer(hWND, timer_ID);
	KillTimer(hWND, timer1_ID);
	Shell_NotifyIcon(NIM_DELETE, &tray);
	DeleteObject(g_hbmBall);
	DeleteObject(g_hbmMask);

	//if(pBuf != NULL)UnmapViewOfFile(pBuf);
	if(hMapFile != NULL)CloseHandle(hMapFile);
	
	if(GetPrivateProfileInt("ustawienia","zapisuj",1,sciezka)) 
		WritePrivateProfileString("ustawienia", "zapisuj", "1", sciezka);
	else WritePrivateProfileString("ustawienia", "zapisuj", "0", sciezka);

	//zapisywanie ustawieñ
	if(GetPrivateProfileInt("ustawienia","zapisuj",1,sciezka))
	{
		char com[]="0";
		if(tryb==com1_ID) com[0]='1';
		if(tryb==com2_ID) com[0]='2';
		if(tryb==com12_ID) com[0]='3';
		if(tryb==brak_ID) com[0]='0';
		WritePrivateProfileString("ustawienia", "com", com, sciezka);

		if(aktywne1==0) com[0]='0'; else com[0]='1';
		WritePrivateProfileString("com1and2", "czestotliwosc", com, sciezka);

		if(losowo1==0) com[0]='0'; else com[0]='1';
		WritePrivateProfileString("com1and2", "losowo", com, sciezka);

		if(poruszeniumyszka1==0) com[0]='0'; else com[0]='1';
		WritePrivateProfileString("com1and2", "poruszeniumyszka", com, sciezka);

		if(zwinamp1==0) com[0]='0'; else com[0]='1';
		WritePrivateProfileString("com1and2", "winamp", com, sciezka);

		if(mysza1==0) com[0]='0'; else com[0]='1';
		WritePrivateProfileString("com1and2", "myszklik", com, sciezka);

		if(klawiatura1==0) com[0]='0'; else com[0]='1';
		WritePrivateProfileString("com1and2", "klawiaturaklik", com, sciezka);
				
		char st[20];
		itoa(SendMessage(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), TBM_GETPOS, 0, 0), st, 10);
		WritePrivateProfileString("com1and2", "szybkosc", st, sciezka);
	}

	return true;
}

//--------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	HANDLE mutex = CreateMutex(NULL, TRUE, "LEDCOM_10TEST"); 
	if(GetLastError() == ERROR_ALREADY_EXISTS){ 
		if(mutex) CloseHandle(mutex); 
		return 0; 
	}

	hInst = hInstance;
	
	//inicjalizacja glownego okna i klasy okna
	if(!InitMainWindow(hInst))
	{
		MessageBox(0,"Nie udalo sie zainicjowac okna!", "Error",MB_OK|MB_ICONSTOP);
	}

	//inicjalizacja kontrolek
	if(!InitWindows(hOkno))
	{
		MessageBox(0,"Nie udalo sie zainicjowac kontrolek!", "Error",MB_OK|MB_ICONSTOP);
	}

	//tray icon
	tray.cbSize = sizeof(NOTIFYICONDATA); 
	tray.hWnd = hOkno; 
	tray.uID = tray_ID; 
	tray.uFlags = NIF_MESSAGE | NIF_TIP | NIF_ICON; 
	tray.uCallbackMessage = WM_TRAY; 
	tray.hIcon = LoadIcon(hInst ,MAKEINTRESOURCE(IDI_ICON1));
	lstrcpyn(tray.szTip, "Ledcom ver. 1.0", sizeof(tray.szTip)); 
	if(!Shell_NotifyIcon(NIM_ADD, &tray)) 
		MessageBox(0, "B³ad Tray'a", "B³ad", MB_OK); 

	// pêtla komunikatów
	MSG msgKomunikat;
	while (GetMessage(&msgKomunikat, NULL, 0, 0))
	{
		TranslateMessage (&msgKomunikat);
		DispatchMessage (&msgKomunikat);
	}

	//kasowanie kontrolek i innych
	if(!DeleteWindows(hOkno))
	{
		MessageBox(0,"Nie udalo sie skasowac kontrolek!", "Error",MB_OK|MB_ICONSTOP);
	}

	ReleaseMutex(mutex); 
	CloseHandle(mutex);

	// zwracamy kod wyjœcia
	return static_cast<int>(msgKomunikat.wParam);
}