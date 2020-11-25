/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CABOUTDIALOG67
#define CABOUTDIALOG67

#include "wx/wx.h"

class CAboutDialog : public wxDialog
{
public:
	CAboutDialog(wxWindow *parent);
	virtual ~CAboutDialog() { }

	void OnOk(wxCommandEvent& event);

private:
	DECLARE_EVENT_TABLE()

	wxButton *m_pOk;
};

enum
{
    CAboutDialog_Ok,
};

#endif