#include "winampInterface.h"
#include "resource.h"
#include <stdio.h>
//********************************************************************

void config ( struct winampVisModule *this_mod );
int init(struct winampVisModule *this_mod);	   // initialization for module
int render(struct winampVisModule *this_mod);  // rendering for module
void quit(struct winampVisModule *this_mod);   // deinitialization for module
LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

winampVisModule *getModule(int which);
char szAppName[] = "Ledcom_plugin";
#define ID_VIS_CFG 40390

winampVisHeader hdr = {	VIS_HDRVER, "Ledcom",getModule };
winampVisModule mod = {
	"Ledcom",
	NULL,	// hwndParent
	NULL,	// hDllInstance
	0,		// sRate
	0,		// nCh
	25,		// latencyMS
	25,		// delayMS
	1,		// spectrumNch
	0,		// waveformNch
	{ 0, },	// spectrumData
	{ 0, },	// waveformData
	config,	//config,
	init,
	render, 
	quit
};

#define BUF_SIZE 128
TCHAR szName[]=TEXT("LEDCOMBETAHE");
TCHAR szMsg[]=TEXT("0");
HANDLE hMapFile;
LPCTSTR pBuf;
char st[32];

//********************************************************************

#ifdef __cplusplus
extern "C" {
#endif
__declspec( dllexport ) winampVisHeader *winampVisGetHeader()
{
	return &hdr;
}
#ifdef __cplusplus
}
#endif

//********************************************************************

winampVisModule *getModule ( int which)  
{
	if (which == 0)
		return &mod;
	return NULL;
}

//********************************************************************

void config ( struct winampVisModule *this_mod ) 
{
	DialogBox ( this_mod->hDllInstance, MAKEINTRESOURCE(IDD_CONFIG), this_mod->hwndParent, (DLGPROC)DialogProc );
}

//********************************************************************

int init ( struct winampVisModule *this_mod ) 
{
	WNDCLASSEX wndClassEx;
	// init our wndClass (this should really only be done once)
	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.lpfnWndProc = (WNDPROC)WndProc;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = this_mod->hDllInstance;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.lpszClassName = szAppName;
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register our class
	if (!RegisterClassEx(&wndClassEx)) {	
		// show an error box
		MessageBox (
			this_mod->hwndParent,
			"Error registering window class",
			"Error",
			MB_OK);
		// let's bail
		return 1;
	}

	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, szName);
	if(hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE) MessageBox(0,"Nie mog³em utworzyæ MapFile!", "Error",MB_OK|MB_ICONSTOP);
		   
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,BUF_SIZE);           
	if (pBuf == NULL) MessageBox(0,"Nie mog³em utworzyæ buforu pamiêci!", "Error",MB_OK|MB_ICONSTOP);

	return 0;
}

//********************************************************************

void quit ( struct winampVisModule *this_mod ) 
{
	UnregisterClass(szAppName,this_mod->hDllInstance);

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
}

//********************************************************************

LRESULT CALLBACK WndProc ( HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam ) 
{
	switch (iMsg) {
		case WM_CREATE:	
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			{
				winampVisModule *this_mod = (winampVisModule *)GetWindowLong(hWnd,GWL_USERDATA);
				PostMessage(this_mod->hwndParent, iMsg, wParam, lParam);
			}
			break;

		case WM_KEYUP: 
			{
				winampVisModule *this_mod = (winampVisModule *)GetWindowLong(hWnd,GWL_USERDATA);
				PostMessage(this_mod->hwndParent, iMsg, wParam, lParam);
			}
		return 0;
	} 
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

//********************************************************************

BOOL CALLBACK DialogProc (HWND hDlg,UINT iMsg,WPARAM wParam, LPARAM lParam )  
{
	switch (iMsg)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			int ID=LOWORD(wParam);
			if (ID == IDOK){
				EndDialog(hDlg,ID);
				return TRUE;
			}
		break;
	}
	return FALSE;
}

//********************************************************************

int render(struct winampVisModule *this_mod) 
{
	
	sprintf(st,"%d",this_mod->spectrumData[0][50]);
	
	ZeroMemory((PVOID)pBuf, 128);
	CopyMemory((PVOID)pBuf, st, 128);

	return 0;
}


