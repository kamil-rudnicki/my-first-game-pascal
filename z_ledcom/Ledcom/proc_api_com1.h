//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// funkcja komunikatow		//
//////////////////////////////

#ifndef COM1PROC_H
#define COM1PROC_H

LRESULT CALLBACK WndCOM1Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
    {	
		case WM_COMMAND:
			{
				int ID=LOWORD(wParam);
				if(ID == losowo){
					if(IsDlgButtonChecked(hwnd, losowo)==1) losowo1=true;
					else losowo1=false;

				}else if(ID==poruszeniumyszka){
					if(IsDlgButtonChecked(hwnd, poruszeniumyszka)==1) poruszeniumyszka1=true;
					else poruszeniumyszka1=false;

				}else if(ID==zwinamp){
					if(IsDlgButtonChecked(hwnd, zwinamp)==1){ zwinamp1=true; hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szName);}
					else {zwinamp1=false;if(hMapFile != NULL)CloseHandle(hMapFile);}

				}else if(ID==mysza){
					if(IsDlgButtonChecked(hwnd, mysza)==1) mysza1=true;
					else mysza1=false;

				}else if(ID==klawiatura){
					if(IsDlgButtonChecked(hwnd, klawiatura)==1) klawiatura1=true;
					else klawiatura1=false;

				}else if(ID==aktywne){
					if(IsDlgButtonChecked(hwnd, aktywne)==1){ 
						EnableWindow(GetDlgItem(hwnd, losowo), TRUE); 
						EnableWindow(GetDlgItem(hwnd, trackbar), TRUE);
						aktywne1=true;
						com1.zgas();
					}
					else{ 
						EnableWindow(GetDlgItem(hwnd, losowo), FALSE); 
						EnableWindow(GetDlgItem(hwnd, trackbar), FALSE);
						aktywne1=false;
						com1.zaswiec();
					}
				}
			}
			break;

		case WM_HSCROLL:
			{
				int speed=SendMessage(GetDlgItem(hwnd, trackbar), TBM_GETPOS, 0, 0)*100;
				SetTimer(hOkno, timer_ID, speed, NULL);
			}
			break;

		default:
			return CallWindowProc(WndProc[2], hwnd, uMsg, wParam, lParam);
	}

	return 0L;
}

#endif