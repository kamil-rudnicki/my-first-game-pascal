/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CNewGameWindow.h"
#include "wx/image.h"
#include "CGameWindow.h"
#include "CLanguage.h"

BEGIN_EVENT_TABLE(CNewGameDialog, wxDialog)
    EVT_BUTTON  (CNewGameDialog_Ok,   CNewGameDialog::OnOk)
	EVT_BUTTON  (CNewGameDialog_Cancel,   CNewGameDialog::OnCancel)
	EVT_CLOSE   (CNewGameDialog::OnClose) 
END_EVENT_TABLE()

//***************************************************************************

CNewGameDialog::CNewGameDialog(wxWindow *parent, CGameWindow *gamewindow)
			: wxDialog(parent, -1, _("Connect four"), wxDefaultPosition, wxSize(330, 280), wxDEFAULT_DIALOG_STYLE)
{
	

	m_pconfig = new wxConfig("Connect_four");

	m_gamewindow=gamewindow;

	(void)new wxStaticBox(this, wxID_ANY, _("New game"),wxPoint(10, 5), wxSize(300, 200));
	(void)new wxStaticText(this, wxID_ANY, _("Game starts green player"), wxPoint(80,20));

	m_pOk = new wxButton(this, CNewGameDialog_Ok, _("Ok"), wxPoint(180, 210), wxSize(60, 27));
	m_pCancel = new wxButton(this, CNewGameDialog_Cancel, _("Cancel"), wxPoint(250, 210), wxSize(60, 27));

	wxArrayString stringarray;
	stringarray.Add(_("Computer - easy"));
	stringarray.Add(_("Computer - medium"));
	stringarray.Add(_("Computer - hard"));
	stringarray.Add(_("Human"));

	m_pChoiceGreen = new wxChoice(this, CNewGameDialog_ChoiceGreen, wxPoint(60,45), wxSize(220,50), stringarray);
	m_pChoiceGreen->Select(m_pconfig->Read(wxT("green_choice"), 3));

	m_pChoiceRed = new wxChoice(this, CNewGameDialog_ChoiceRed, wxPoint(60,75), wxSize(220,50), stringarray);
	m_pChoiceRed->Select(m_pconfig->Read(wxT("red_choice"), 3));

	//loading and scaling images
	wxImage::AddHandler(new wxGIFHandler);
	wxImage m_img_green;
	wxImage m_img_red;
	m_img_green.LoadFile("graphics/green.gif");
	if(m_img_green.Ok()){
		m_img_green.ConvertAlphaToMask();
		m_img_green.InitAlpha();
		m_img_green.Rescale(20,20);
	}
	m_img_red.LoadFile("graphics/red.gif");
	if(m_img_red.Ok()){
		m_img_red.ConvertAlphaToMask();
		m_img_red.InitAlpha();
		m_img_red.Rescale(20,20);
	}

	new wxStaticBitmap(this, -1, wxBitmap(m_img_red), wxPoint(30,75));
	new wxStaticBitmap(this, -1, wxBitmap(m_img_green), wxPoint(30,45));
	
}

//***************************************************************************

void CNewGameDialog::OnOk(wxCommandEvent& event)
{
	CGameWindow::Player player_red;
	CGameWindow::Player player_green;

	int i=m_pChoiceGreen->GetCurrentSelection();
		 if(i==3) player_green=CGameWindow::human;
	else if(i==0) player_green=CGameWindow::computer_easy;
	else if(i==1) player_green=CGameWindow::computer_medium;
	else if(i==2) player_green=CGameWindow::computer_hard;

	i=m_pChoiceRed->GetCurrentSelection();
		 if(i==3) player_red=CGameWindow::human;
	else if(i==0) player_red=CGameWindow::computer_easy;
	else if(i==1) player_red=CGameWindow::computer_medium;
	else if(i==2) player_red=CGameWindow::computer_hard;

	m_gamewindow->NewGame(player_green, player_red);
	Close();
}

//***************************************************************************

void CNewGameDialog::OnCancel(wxCommandEvent& event)
{
	Close();
}

//***************************************************************************

void CNewGameDialog::OnClose(wxCloseEvent& event)
{
	m_pconfig->Write(wxT("red_choice"), m_pChoiceRed->GetCurrentSelection());
	m_pconfig->Write(wxT("green_choice"), m_pChoiceGreen->GetCurrentSelection());

	delete m_pconfig;
	
	Destroy();
}

//***************************************************************************