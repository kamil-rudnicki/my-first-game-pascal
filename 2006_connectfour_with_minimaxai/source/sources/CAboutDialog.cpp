/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "wx/statline.h"
#include "CAboutDialog.h"
#include "wx/image.h"
#include "hyperlink.h"

BEGIN_EVENT_TABLE(CAboutDialog, wxDialog)
    EVT_BUTTON  (CAboutDialog_Ok,   CAboutDialog::OnOk)
END_EVENT_TABLE()

//***************************************************************************

CAboutDialog::CAboutDialog(wxWindow *parent)
			: wxDialog(parent, -1, _("About..."), wxDefaultPosition, wxSize(330, 280), wxDEFAULT_DIALOG_STYLE)
{
	m_pOk = new wxButton(this, CAboutDialog_Ok, _("Ok"), wxPoint(250, 210), wxSize(60, 27));

	//loading and scaling images
	wxImage::AddHandler(new wxICOHandler);
	wxImage m_img_red;
	m_img_red.LoadFile("graphics/icon.ico");
	if(m_img_red.Ok()){
		m_img_red.ConvertAlphaToMask();
		m_img_red.InitAlpha();
	}

	new wxStaticBitmap(this, -1, wxBitmap(m_img_red), wxPoint(10,10));
	new wxStaticText(this, wxID_ANY, _("Connect four version 1.0"), wxPoint(80,18));
	new wxStaticLine(this, wxID_ANY, wxPoint(10,40), wxSize(300,2));
	
	new wxStaticText(this, wxID_ANY, _("(c) 2006 Kamil Rudnicki\nLicense: GPL\n\nThanks to:\n - wxWidgets Team\n - Tomasz \"SVN\" Kalita\n - Krzysiek Sornat"), wxPoint(70,60));

	new wxHyperLink (this, -1, _("http://www.widget.czest.pl"), wxPoint(70,160));
	new wxHyperLink (this, -1, _("kamil.rudnicki@gmail.com"), wxPoint(70,180));
}

//***************************************************************************

void CAboutDialog::OnOk(wxCommandEvent& event)
{
	Close();
}

//***************************************************************************
