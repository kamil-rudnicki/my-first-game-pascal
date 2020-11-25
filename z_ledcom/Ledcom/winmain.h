//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// funkcja winmain  		//
//////////////////////////////

#ifndef WINMAIN_H
#define WINMAIN_H

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------

HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent)
{
	HDC hdcMem, hdcMem2;
	HBITMAP hbmMask;
	BITMAP bm;

	GetObject(hbmColour, sizeof(BITMAP), &bm);
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	hdcMem = CreateCompatibleDC(0);
	hdcMem2 = CreateCompatibleDC(0);

	SelectObject(hdcMem, hbmColour);
	SelectObject(hdcMem2, hbmMask);

	SetBkColor(hdcMem, crTransparent);

	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);

	return hbmMask;
}

//--------------------------------------------------------------

void zaswiec()
{
	if(tryb==com1_ID) com1.zgas();
	else if(tryb==com2_ID) com2.zgas();
	else if(tryb==com12_ID || tryb==brak_ID){ com1.zgas(); com2.zgas();}
}

//--------------------------------------------------------------

void zgas()
{
	if(tryb==com1_ID) com1.zaswiec();
	else if(tryb==com2_ID) com2.zaswiec();
	else if(tryb==com12_ID){ com1.zaswiec(); com2.zaswiec();}
	else if(tryb==brak_ID){ com1.zaswiec(); com2.zaswiec();}
}

//--------------------------------------------------------------

LRESULT InitMainWindow(HINSTANCE hInstance)
{
	INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_TAB_CLASSES;
    InitCommonControlsEx(&icex);

	WNDCLASSEX KlasaOkna;

	// wype³niamy strukturê WNDCLASSEX
	ZeroMemory(&KlasaOkna, sizeof(WNDCLASSEX));
	KlasaOkna.cbSize = sizeof(WNDCLASSEX);
	KlasaOkna.hInstance = hInstance;
	KlasaOkna.lpfnWndProc = MainWndProc;
	KlasaOkna.lpszClassName = klasa_okna;
	KlasaOkna.hCursor = LoadCursor(NULL, IDC_ARROW);
	KlasaOkna.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	KlasaOkna.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE+1; 
 
	if(!RegisterClassEx (&KlasaOkna))
		return false; 

	hOkno = CreateWindowEx(
				NULL, // rozszerzony styl
				klasa_okna, // klasa okna
				"Ledcom", // tekst na p. tytu³u
				WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX, // styl okna
				CW_USEDEFAULT, // wspó³rzêdna X
				CW_USEDEFAULT, // wspó³rzêdna Y
				window_x, // szerokoœæ
				window_y, // wysokoœæ
				NULL, // okno nadrzêdne
				NULL, // menu
				hInstance, // instancjs aplikacji
				NULL); // dodatkowe dane

	if(hOkno == 0)
		return false;
	if(GetPrivateProfileInt("ustawienia","zminimalizowany",0,sciezka)){
		if(ShowWindow(hOkno , SW_HIDE)) return false;
	}else{
		if(ShowWindow(hOkno , SW_SHOW)) return false;
	}
    if(!UpdateWindow(hOkno))
		return false;

	return true;
}

#endif