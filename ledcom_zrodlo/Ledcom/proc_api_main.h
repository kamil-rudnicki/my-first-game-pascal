//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// funkcja komunikatow		//
//////////////////////////////

#ifndef MAINPROC_H
#define MAINPROC_H

bool ok=false;

LRESULT CALLBACK OprogramieDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OpcjeDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//******************************************************************************
//funkcja komunikatow: glownego okna
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
    {
		case WM_SYSCOMMAND:
			if(wParam==SC_MINIMIZE){ 
				ShowWindow(hWnd, SW_HIDE); 
				break;
			}
			DefWindowProc(hWnd,uMsg,wParam,lParam);
			break;
	
		case WM_CREATE:
			g_hbmBall = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BALL)); 
				if(g_hbmBall == NULL) MessageBox(0, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);
			g_hbmMask = CreateBitmapMask(g_hbmBall, RGB(172, 211, 115)); 
				if(g_hbmMask == NULL) MessageBox(0, "Could not create mask!", "Error", MB_OK | MB_ICONEXCLAMATION);
			break;	
			
		case WM_COMMAND:
			if(LOWORD(wParam)==o_programie_ID) DialogBox(hInst, (LPCTSTR)IDD_DIALOG1,hWnd, (DLGPROC)OprogramieDialog);
			if(LOWORD(wParam)==ustawienia_ID) DialogBox(hInst, (LPCTSTR)IDD_DIALOG2,hWnd, (DLGPROC)OpcjeDialog);
			break;

		case WM_DESTROY:
			
			PostQuitMessage(WM_QUIT);
			break;

		case WM_ENDSESSION:
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
			break;

		case WM_TIMER:
			if(wParam == timer_ID && tryb!=brak_ID){
				//miganie
				if(aktywne1 && losowo1 && rand()%2)
				{
					if(ok) ok=false; 
					else ok=true; 
				}else if(aktywne1 && !losowo1)
				{
					if(ok) ok=false;
					else ok=true;
				}
			}
			else if(tryb!=brak_ID){
				
				bool ruszmysz=false;
				if(poruszeniumyszka1){
					POINT pt;
					GetCursorPos(&pt);
					if(poz_kursora.x!=pt.x || poz_kursora.y!=pt.y) ruszmysz=true;
					poz_kursora.x=pt.x;
					poz_kursora.y=pt.y;
				}
				
				bool przycisk_myszka=false;
				if(mysza1){
					if(HIBYTE(GetAsyncKeyState(VK_LBUTTON))) przycisk_myszka=true;
					else if(HIBYTE(GetAsyncKeyState(VK_RBUTTON))) przycisk_myszka=true;
					else if(HIBYTE(GetAsyncKeyState(VK_MBUTTON))) przycisk_myszka=true;
				}

				bool czesto=false;
				if(ok && aktywne1) czesto=true;
				
				bool muza=false;
				pBuf=NULL;
				if(hMapFile==NULL && zwinamp1) hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szName);
				if(hMapFile!=NULL && zwinamp1)pBuf = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS,0, 0,BUF_SIZE);  
				if(hMapFile!=NULL && pBuf != NULL && atoi(pBuf)>130 && zwinamp1) muza=true;
				if(pBuf != NULL)UnmapViewOfFile(pBuf);

				bool klawisze=false;
				for(int i=0; i<256 && klawiatura1; i++)
				{
					if((GetAsyncKeyState(i)&0x8000) && !HIBYTE(GetAsyncKeyState(VK_MBUTTON)) && !HIBYTE(GetAsyncKeyState(VK_RBUTTON)) && !HIBYTE(GetAsyncKeyState(VK_LBUTTON))) klawisze=true;
				}

				if(!czesto && !przycisk_myszka && !ruszmysz && !muza && !klawisze) zgas();
				else zaswiec();
			}
			break; 

		case WM_PAINT:
			{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

				BITMAP bm;
				RECT rcClient;
				HDC hdcMem = CreateCompatibleDC(hdc);
				GetObject(g_hbmBall, sizeof(bm), &bm);
				
				GetClientRect(hWnd, &rcClient);
				
				SelectObject(hdcMem, g_hbmMask);		
				BitBlt(hdc, 5, 5, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCAND);
				SelectObject(hdcMem, g_hbmBall);
				BitBlt(hdc, 5, 5, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);

				DeleteDC(hdcMem);

			EndPaint(hWnd, &ps);
			}
			break;
			
		case WM_TRAY:
			switch(lParam)
			{
			case WM_RBUTTONDOWN:
				ShowWindow(hOkno, SW_RESTORE);
				break;
			case WM_LBUTTONDOWN:
				ShowWindow(hOkno, SW_RESTORE);
				break;
			}
			break;

		default:
			return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
	return(0L);
}

//******************************************************************************
//funkcja komunikatow: okna USTAWIENIA
LRESULT CALLBACK OpcjeDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
		//wczytywanie ustawieñ z pliku ini
		if(GetPrivateProfileInt("ustawienia","autostart",0,sciezka))
			SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_SETCHECK, 1, 0);
		if(GetPrivateProfileInt("ustawienia","zminimalizowany",0,sciezka))
			SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_SETCHECK, 1, 0);
		if(GetPrivateProfileInt("ustawienia","zapisuj",1,sciezka))
			SendMessage(GetDlgItem(hDlg, IDC_CHECK3), BM_SETCHECK, 1, 0);
		return TRUE;
	
	case WM_COMMAND:
		int ID=LOWORD(wParam);
		if(ID == IDOK)
		{
			//zapisywanie ustawieñ do pliku ini
			char zaznaczony[]="0";
			if(IsDlgButtonChecked(hDlg, IDC_CHECK1)==1) zaznaczony[0]='1';
				WritePrivateProfileString("ustawienia", "autostart",zaznaczony,sciezka);
			                                                                                                              
			zaznaczony[0]='0';
			if(IsDlgButtonChecked(hDlg, IDC_CHECK2)==1) zaznaczony[0]='1';
				WritePrivateProfileString("ustawienia", "zminimalizowany",zaznaczony,sciezka);
			
			zaznaczony[0]='0';
			if(IsDlgButtonChecked(hDlg, IDC_CHECK3)==1) zaznaczony[0]='1';
				WritePrivateProfileString("ustawienia", "zapisuj", zaznaczony, sciezka);

			//zapisywanie/usuwanie autostartu do rejestru
			HKEY klucz; 
				DWORD akcja;
				TCHAR szBuf[MAX_PATH]; 
				wsprintf(szBuf, "Software\\Microsoft\\Windows\\CurrentVersion\\Run"); 
				RegCreateKeyEx(HKEY_CURRENT_USER, szBuf , 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &klucz, &akcja);
				TCHAR program_path[MAX_PATH];
				GetModuleFileName(NULL,program_path,MAX_PATH);
				if(GetPrivateProfileInt("ustawienia","autostart",0,sciezka)==1)
				{
					RegSetValueEx(klucz, "Ledcom", 0, REG_SZ, (CONST BYTE *)&program_path, strlen(program_path)); 
				}else
				{
					RegDeleteValue(klucz, "Ledcom");
				}
			RegCloseKey(klucz);

			EndDialog(hDlg,ID);
			return TRUE;
		}
		

		break;
	}
return FALSE;
} 

//******************************************************************************
//funkcja komunikatow: okna O PROGRAMIE
LRESULT CALLBACK OprogramieDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont;

	switch (message)
	{
	case WM_INITDIALOG:
		hFont = CreateFont(14,0,0,0,0,0,0,0,0,0,0,0,0,"Arial CE");
		return TRUE;

	case WM_PAINT:
			{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg, &ps);

				BITMAP bm;
				RECT rcClient;
				HDC hdcMem = CreateCompatibleDC(hdc);
				GetObject(g_hbmBall, sizeof(bm), &bm);
				GetClientRect(hDlg, &rcClient);
				SelectObject(hdcMem, g_hbmMask);		
				BitBlt(hdc, 25, 15, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCAND);
				SelectObject(hdcMem, g_hbmBall);
				BitBlt(hdc, 25, 15, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);
				DeleteDC(hdcMem);

					SelectObject(hdc, hFont);
					SetTextColor(hdc, RGB(0,0,255));
					SetBkMode(hdc, TRANSPARENT);
					TextOut(hdc, 130, 110, "www.caru.w.pl",13);
					TextOut(hdc, 130, 125, "www.hardheads.prv.pl",20);
					TextOut(hdc, 130, 140, "kamil1616@poczta.fm",19);

			EndPaint(hDlg, &ps);
			}
			break;

	case WM_COMMAND:
		int ID=LOWORD(wParam);
		if(ID == IDOK)
		{
			EndDialog(hDlg,ID);
			return TRUE;
		}
		
	}
return FALSE;
} 

#endif