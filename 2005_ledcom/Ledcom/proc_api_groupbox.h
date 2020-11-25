//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// funkcja komunikatow		//
//////////////////////////////

#ifndef GROUPBOXPROC_H
#define GROUPBOXPROC_H

void kontrolki_nieaktywne(bool siwe)
{
	if(siwe && !aktywne1){
		EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), losowo), false);
		EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), false);
	}else{
		EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), losowo), siwe);
		EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), trackbar), siwe);
	}
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), poruszeniumyszka), siwe);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), klawiatura), siwe);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), mysza), siwe);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), aktywne), siwe);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), zwinamp), siwe);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), brak1), siwe);
	EnableWindow(GetDlgItem(GetDlgItem(hOkno, com1_tab), brak2), siwe);
}

LRESULT CALLBACK WndNewProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
    {	
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case com1_ID:
				ShowWindow(GetDlgItem(hOkno, com1_tab), SW_SHOW);
				//ShowWindow(GetDlgItem(hOkno, com2_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, com12_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, brak_tab), SW_HIDE);
				tryb=com1_ID;
				com1.ini();
				com2.del();
				kontrolki_nieaktywne(true);
				zgas();
				break;
			case com2_ID:
				ShowWindow(GetDlgItem(hOkno, com1_tab), SW_SHOW);
				//ShowWindow(GetDlgItem(hOkno, com2_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, com12_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, brak_tab), SW_HIDE);
				tryb=com2_ID;
				com1.del();
				com2.ini();
				kontrolki_nieaktywne(true);
				zgas();
				break;
			case com12_ID:
				ShowWindow(GetDlgItem(hOkno, com1_tab), SW_SHOW);
				//ShowWindow(GetDlgItem(hOkno, com2_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, com12_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, brak_tab), SW_HIDE);
				tryb=com12_ID;
				com1.ini();
				com2.ini();
				zgas();
				kontrolki_nieaktywne(true);
				break;
			case brak_ID:
				ShowWindow(GetDlgItem(hOkno, com1_tab), SW_SHOW);
				//ShowWindow(GetDlgItem(hOkno, com2_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, com12_tab), SW_HIDE);
				//ShowWindow(GetDlgItem(hOkno, brak_tab), SW_HIDE);
				tryb=brak_ID;
				com1.del();
				com2.del();
				kontrolki_nieaktywne(false);
				zgas();
				break;
			}
			break;

		default:
			return CallWindowProc(WndProc[0], hwnd, uMsg, wParam, lParam);
	}

	return 0L;
}

#endif