/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CMAINFRAME56
#define CMAINFRAME56

#include "wx/wx.h"
#include "wx/image.h"
#include "CNewGameWindow.h"
#include "CGameWindow.h"
#include "CLanguage.h"
#include "CStatusBar.h"

class CMainFrame : public wxFrame
{
public:
    CMainFrame(const wxString& title, wxLocale &w);

    // event handlers 
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnNewGame(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
	void OnLanguage(wxCommandEvent& event);
	void OnUndoMove(wxCommandEvent& event);
	void OnMoveForMe(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()

	void SetupStrings();

	CGameWindow *m_game_window;
	wxLocale &m_locale;
	CStatusBar *m_statusbar;
	
};


enum
{
    CMainFrame_Quit = wxID_EXIT,
    CMainFrame_About = wxID_ABOUT,
	CMainFrame_NewGame,
	CMainFrame_Help,
	CMainFrame_Language,
	CMainFrame_UndoMove,
	CMainFrame_MoveForMe
};

#endif


