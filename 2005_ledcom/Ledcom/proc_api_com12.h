//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// funkcja komunikatow		//
//////////////////////////////

#ifndef COM12PROC_H
#define COM12PROC_H

LRESULT CALLBACK WndCOM12Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*switch (uMsg)
    {	


		default:
			
	}*/
	return CallWindowProc(WndProc[4], hwnd, uMsg, wParam, lParam);
	//return 0L;
}

#endif