/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CMainWindow.h"
#include "CAboutDialog.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
    EVT_MENU(CMainFrame_Quit,  CMainFrame::OnQuit)
    EVT_MENU(CMainFrame_NewGame, CMainFrame::OnNewGame)
	EVT_MENU(CMainFrame_About, CMainFrame::OnAbout)
	EVT_MENU(CMainFrame_Help, CMainFrame::OnHelp)
	EVT_MENU(CMainFrame_Language, CMainFrame::OnLanguage)
	EVT_MENU(CMainFrame_UndoMove, CMainFrame::OnUndoMove)
	EVT_MENU(CMainFrame_MoveForMe, CMainFrame::OnMoveForMe)
END_EVENT_TABLE()

//*******************************************************************

CMainFrame::CMainFrame(const wxString& title, wxLocale &w)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(450,520), wxMINIMIZE_BOX  | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN),
	    m_locale(w)
{
	wxImage::AddHandler(new wxGIFHandler);
	wxIcon icon;
	icon.LoadFile("graphics/icon.ico", wxBITMAP_TYPE_ICO );
    SetIcon(icon);

	m_statusbar = new CStatusBar(this);
	SetStatusBar(m_statusbar);

	SetupStrings();

	SetClientSize(438,464);

	m_game_window = new CGameWindow(this, m_statusbar);
}

//***************************************************************************

void CMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

//***************************************************************************

void CMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	CAboutDialog *dlg = new CAboutDialog(this);
	dlg->ShowModal();
}

//***************************************************************************

void CMainFrame::OnNewGame(wxCommandEvent& WXUNUSED(event))
{
    CNewGameDialog *dlg = new CNewGameDialog(this, m_game_window);
	dlg->ShowModal();

	m_statusbar->ResetClock();
}

//***************************************************************************

void CMainFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
	wxBoxSizer *topsizer;
    wxHtmlWindow *html;
    wxDialog dlg(this, wxID_ANY, wxString(_("Help")));

    topsizer = new wxBoxSizer(wxVERTICAL);

    html = new wxHtmlWindow(&dlg, wxID_ANY, wxDefaultPosition,
            wxSize(450, 300), wxHW_NO_SELECTION | wxHW_SCROLLBAR_AUTO);

    html->SetBorders(0);
    html->LoadPage(_("Help\\help_en.html"));

    topsizer->Add(html, 1, wxALL, 10);

    topsizer->Add(new wxStaticLine(&dlg, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    wxButton *but = new wxButton(&dlg, wxID_OK, _("OK"));
    but->SetDefault();

    topsizer->Add(but, 0, wxALL | wxALIGN_RIGHT, 15);

    dlg.SetSizer(topsizer);
    topsizer->Fit(&dlg);

    dlg.ShowModal();
}

//***************************************************************************

void CMainFrame::OnLanguage(wxCommandEvent& WXUNUSED(event))
{
	CLanguage lang(m_locale);
	lang.ChooseLang(); 

	SetupStrings();
}

//***************************************************************************

void CMainFrame::SetupStrings()
{
	SetTitle(wxGetTranslation("Connect Four 1.0"));

	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenu *optionsMenu;
	wxMenu *helpMenu;

	// create a menu bar
    helpMenu = new wxMenu;
	helpMenu->Append(CMainFrame_Help, _("Help"), _("Help"));
	helpMenu->AppendSeparator();
    helpMenu->Append(CMainFrame_About, _("&About...\tF1"), _("About the program"));

	fileMenu = new wxMenu;
	fileMenu->Append(CMainFrame_NewGame, _("New game"), _("Start a new game"));
	fileMenu->AppendSeparator();
    fileMenu->Append(CMainFrame_Quit, _("Exit\tAlt-X"), _("Do you really want to quit?"));

	optionsMenu = new wxMenu;
	optionsMenu->Append(CMainFrame_UndoMove, _("Undo move"), _("Undo last move"));
	optionsMenu->Append(CMainFrame_MoveForMe, _("Move for me"), _("Do you want to computer move for you?"));
	optionsMenu->AppendSeparator();
	optionsMenu->Append(CMainFrame_Language, _("Change language"), _("Change the language"));

    menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("File"));
	menuBar->Append(optionsMenu, _("Options"));
    menuBar->Append(helpMenu, _("Help"));

    wxMenuBar* formerMenuBar = GetMenuBar();
    SetMenuBar(menuBar);
    delete formerMenuBar;

    SetStatusText(_("Welcome!"));
}

//***************************************************************************

void CMainFrame::OnUndoMove(wxCommandEvent& WXUNUSED(event))
{
	m_game_window->UndoMove();
}

//***************************************************************************

void CMainFrame::OnMoveForMe(wxCommandEvent& WXUNUSED(event))
{
	m_game_window->MoveForMe();
}

//***************************************************************************