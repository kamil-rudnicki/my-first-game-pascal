/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CApp.h"
#include "CLanguage.h"

IMPLEMENT_APP(CMainApp)

//***************************************************************************

bool CMainApp::OnInit()
{	
	CLanguage lang(m_locale);
	lang.Startup();
	
	MainFrame = new CMainFrame("Connect Four 1.0", m_locale);
    MainFrame->Show(true);

    return true;
}