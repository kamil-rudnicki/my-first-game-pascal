/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CSTATUSBAR12
#define CSTATUSBAR12

#include "wx/wx.h"
#include "wx/datetime.h"
#include "wx/image.h"

class CStatusBar : public wxStatusBar
{
public:
    CStatusBar(wxWindow *parent);
    virtual ~CStatusBar();

    void ResetClock();
	void SetGreen();
	void SetRed();

    void OnTimer(wxTimerEvent& WXUNUSED(event));

private:
	DECLARE_EVENT_TABLE()

    enum
    {
        Field_Text,
        Field_Bitmap,
        Field_Clock
    };


    wxTimer m_timer;
	wxDateTime m_time;

	wxImage m_img_green;
	wxImage m_img_red;
	wxStaticBitmap *m_statbmp;
};

#endif