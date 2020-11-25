/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CAPP56
#define CAPP56

#include "CMainWindow.h"
#include "wx/wx.h"

class CMainApp : public wxApp
{
public:
    virtual bool OnInit();

private:
	CMainFrame *MainFrame;
	wxLocale m_locale;


};

DECLARE_APP(CMainApp)

#endif