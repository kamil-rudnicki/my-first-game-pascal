/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CGAME23
#define CGAME23

#include "wx/wx.h"
#include "wx/sound.h"
#include "CGameWindow.h"
#include "CBoard.h"
#include "CStatusBar.h"
#include <vector>

using namespace std;

class CGameWindow;

class CGame
{
public:
	CGame(CGameWindow *m, CStatusBar *status_bar, CGameWindow::Player p1, CGameWindow::Player p2);
	~CGame();

	bool GetAllow(CBoard::player p);
	CBoard GetBoard();
	bool MakeMove(int n);
	bool IsGameEnd();
	void NewGame();
	bool MoveForMe();
	bool UndoMove();
	
private:

	vector<CBoard> m_board_history;
	CBoard m_board;

	CStatusBar *m_status_bar;
	CGameWindow *m_game_window;

	wxSound m_sound_click;
	wxSound m_sound_finish;

	CBoard::player NextPlayer();
	CBoard::player m_player; //acctualy player to move
	CBoard::player m_tempplayer; 

	CGameWindow::Player m_player_type1;
	CGameWindow::Player m_player_type2;
};

#endif