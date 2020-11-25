/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CGameWindow.h"
#include "CGame.h"
#include "CPlayerHuman.h"
#include "CPlayerComputer.h"

#pragma warning(disable : 4355)

BEGIN_EVENT_TABLE(CGameWindow, wxPanel)
	EVT_PAINT(CGameWindow::OnPaint)
	EVT_TIMER(CGameWindow_timer, CGameWindow::OnTimer)
	EVT_MOUSE_EVENTS(CGameWindow::OnMouse) 
	EVT_ERASE_BACKGROUND(CGameWindow::OnErase)
END_EVENT_TABLE()

//*******************************************************************

CGameWindow::CGameWindow(wxWindow *parent, CStatusBar *stat_bar)
: wxPanel(parent),
	    m_timer(this, CGameWindow_timer)
{
	m_game=0;
	m_player1=0;
	m_player2=0;
	m_status_bar=stat_bar;

	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxGIFHandler);

	m_img_background.LoadFile("graphics/background.jpg");
	if(m_img_background.Ok())
		m_img_select2=m_img_background.Size(wxSize(464,64), wxPoint(0,0));
	m_img_green.LoadFile("graphics/green.gif");
	if(m_img_green.Ok()){
		m_img_green.ConvertAlphaToMask();
		m_img_green.InitAlpha();
	}
	m_img_red.LoadFile("graphics/red.gif");
	if(m_img_red.Ok()){
		m_img_red.ConvertAlphaToMask();
		m_img_red.InitAlpha();
	}
	m_img_select1.LoadFile("graphics/arrow.gif");
	if(m_img_select1.Ok()){
		m_img_select1.ConvertAlphaToMask();
		m_img_select1.InitAlpha();
	}
	

	m_timer.Start(500);
	m_blink=true;
	m_box_size=60;
	m_select=0;
}

//***************************************************************************

//first argument - green player
//second argument - red player
void CGameWindow::NewGame(Player player1, Player player2)
{
	if(m_game) delete m_game;
	m_game = new CGame(this, m_status_bar, player1, player2);

	if(m_player1) delete m_player1;
		if(player1==human)			m_player1 = new CPlayerHuman(m_game, CBoard::green);
	else if(player1==computer_easy)	m_player1 = new CPlayerComputer(m_game, CBoard::green, 2);
	else if(player1==computer_medium)m_player1 = new CPlayerComputer(m_game, CBoard::green, 6);
	else if(player1==computer_hard)	m_player1 = new CPlayerComputer(m_game, CBoard::green, 9);
	else wxMessageBox(_("Error in creating player."), _("Error"), wxOK | wxICON_ERROR);
	
	if(m_player2) delete m_player2;
		if(player2==human)			m_player2 = new CPlayerHuman(m_game, CBoard::red);
	else if(player2==computer_easy)	m_player2 = new CPlayerComputer(m_game, CBoard::red, 2);
	else if(player2==computer_medium)m_player2 = new CPlayerComputer(m_game, CBoard::red, 6);
	else if(player2==computer_hard)	m_player2 = new CPlayerComputer(m_game, CBoard::red, 9);
	else wxMessageBox(_("Error in creating player."), _("Error"), wxOK | wxICON_ERROR);
}

//***************************************************************************

void CGameWindow::OnMouse(wxMouseEvent& event)
{
	int t=int((event.m_x-9)/m_box_size);

	if(event.LeftUp())
	{
		if(m_game && m_game->IsGameEnd())
			m_game->NewGame();

		if(m_player1 && m_player2 && !m_player1->Move(t))
			m_player2->Move(t);	
	}
	else if(event.Moving())
	{
		if(m_select!=t)
		{
			m_select=t;
			wxClientDC dc(this);
			PrepareDC( dc );

			DrawSelect(dc);
		}
	}

	event.Skip();
}

//***************************************************************************

void CGameWindow::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);
	PrepareDC( dc );

	Draw(dc);
}

//***************************************************************************

void CGameWindow::OnErase(wxEraseEvent& event)
{
	
}

//***************************************************************************

void CGameWindow::OnTimer(wxTimerEvent& event)
{
    if(m_blink) m_blink=false;
	else m_blink=true;

			if(m_player1 && m_player2 && !m_player2->Move(-1))
				m_player1->Move(-1);

	Draw();
}

//***************************************************************************

void CGameWindow::DrawBackground(wxDC &dc)
{
	dc.DrawBitmap(m_img_background,0,0);
}

//***************************************************************************

void CGameWindow::DrawSelect(wxDC &dc)
{
	dc.DrawBitmap(m_img_select2,0,0);
	dc.DrawBitmap(m_img_select1,m_select*m_box_size+9,0);	
}

//***************************************************************************

void CGameWindow::DrawDraughts(wxDC &dc)
{
	for(int i=0; i<m_board.width; i++)
		for(int j=0; j<m_board.height; j++)
		{
			if( (m_board.Get(i, j)==CBoard::red && !m_board.IsBlink(i,j)) ||
				(m_board.Get(i, j)==CBoard::red && m_board.IsBlink(i,j) && m_blink) ) 
					dc.DrawBitmap(m_img_red,i*m_box_size+9,j*m_box_size+67);
			else if((m_board.Get(i, j)==CBoard::green && !m_board.IsBlink(i,j)) ||
				(m_board.Get(i, j)==CBoard::green && m_board.IsBlink(i,j) && m_blink)) dc.DrawBitmap(m_img_green,i*m_box_size+9,j*m_box_size+67);
		}
}

//***************************************************************************

void CGameWindow::Draw(CBoard board)
{
	m_board=board;

	Draw();
}

//***************************************************************************

void CGameWindow::Draw(wxDC &dc)
{
	DrawBackground(dc);
	DrawDraughts(dc);
	DrawSelect(dc);
}

//***************************************************************************

void CGameWindow::Draw()
{
	wxClientDC dc1(this);

	wxBufferedDC dc(&dc1);
    PrepareDC( dc );

	Draw(dc);
}

//***************************************************************************

bool CGameWindow::MoveForMe()
{
	if(m_game)
		return m_game->MoveForMe();

	
	return false;
}

//***************************************************************************

bool CGameWindow::UndoMove()
{
	if(m_game)
		return m_game->UndoMove();
	
	return false;
}

//***************************************************************************