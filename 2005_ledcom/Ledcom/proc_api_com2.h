//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// funkcja komunikatow		//
//////////////////////////////

#ifndef COM2PROC_H
#define COM2PROC_H

LRESULT CALLBACK WndCOM2Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//switch (uMsg)
    //{	

		//default:
			return CallWindowProc(WndProc[3], hwnd, uMsg, wParam, lParam);
	//}

	//return 0L;
}

#endif