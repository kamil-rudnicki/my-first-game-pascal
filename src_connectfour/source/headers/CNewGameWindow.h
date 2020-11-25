/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CNEWGAMEWINDOW34
#define CNEWGAMEWINDOW34

#include "wx/wx.h"
#include "wx/config.h"

class CGameWindow;

class CNewGameDialog : public wxDialog
{
public:
	CNewGameDialog(wxWindow *parent, CGameWindow *gamewindow);
	virtual ~CNewGameDialog() { }

	void OnOk(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

private:
	DECLARE_EVENT_TABLE()

	CGameWindow *m_gamewindow;

	wxButton *m_pOk;
	wxButton *m_pCancel;
	wxChoice *m_pChoiceGreen;
	wxChoice *m_pChoiceRed;
	wxConfig *m_pconfig;
};

enum
{
    CNewGameDialog_Ok,
	CNewGameDialog_Cancel,
	CNewGameDialog_ChoiceGreen,
	CNewGameDialog_ChoiceRed,
};

#endif