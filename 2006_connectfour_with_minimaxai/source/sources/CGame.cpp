/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CGame.h"
#include "CPlayerComputer.h"

//***************************************************************************

CGame::CGame(CGameWindow *m, CStatusBar *status_bar, CGameWindow::Player p1, CGameWindow::Player p2)
{
	m_player_type1=p1;
	m_player_type2=p2;

	m_status_bar=status_bar;
	m_status_bar->ResetClock();

	m_game_window=m;
	m_player=CBoard::green;

	m_sound_click.Create("sounds/hit.wav");
	m_sound_finish.Create("sounds/aplaus.wav");

	m_game_window->Draw(m_board);
}

//***************************************************************************

CGame::~CGame()
{
}

//***************************************************************************

bool CGame::GetAllow(CBoard::player p)
{
	if(p==m_player) return true;
	return false;
}

//***************************************************************************

CBoard::player CGame::NextPlayer()
{
	
	if(m_player==CBoard::empty)
		m_player=m_tempplayer;
	else
		m_tempplayer=m_player;

	if(m_player==CBoard::red){
		m_player=CBoard::green;
		m_status_bar->SetGreen();
	}
	else { 
		m_player=CBoard::red;
		m_status_bar->SetRed();
	}

	return m_player;
}

//***************************************************************************

CBoard CGame::GetBoard()
{
	return m_board;
}

//***************************************************************************

bool CGame::MakeMove(int n)
{
	if(m_board.Add(m_player, n)==-1){
		return false;
	}

	m_board_history.push_back(m_board);

	m_sound_click.Play();

	CBoard::player result=m_board.IsFinish();
	if(result!=CBoard::empty){

		m_player=CBoard::empty;

		

		if(result==CBoard::draw) wxMessageBox(_("You are good, but not enought to win.\nIt's draw!"), _("Draw"), wxOK, 0);
		else{
			if((m_player_type1==CGameWindow::human && result==CBoard::green) ||
				(m_player_type2==CGameWindow::human && result==CBoard::red))
					m_sound_finish.Play();
		}

	}else
		NextPlayer();

	m_game_window->Draw(m_board);

	return true;
}

//***************************************************************************

bool CGame::IsGameEnd()
{
	if(m_player==CBoard::empty)
		return true;

	return false;
}

//***************************************************************************

void CGame::NewGame()
{
	m_player=CBoard::green;
	m_board.Clear();
	m_game_window->Draw(m_board);
	m_status_bar->ResetClock();
}

//***************************************************************************

bool CGame::MoveForMe()
{
	CPlayerComputer player_computer(this, m_player, 9);
	return player_computer.Move(-1);
}

//***************************************************************************

bool CGame::UndoMove()
{
	if(m_board_history.size()>2)
	{
		if(m_player_type1!=CGameWindow::human || m_player_type2!=CGameWindow::human)
		{
			m_board_history.pop_back();
			NextPlayer();
		}

		m_board_history.pop_back();
		m_board=m_board_history.back();

		m_game_window->Draw(m_board);
		NextPlayer();

		return true;
	}

	return false;
}

//***************************************************************************
