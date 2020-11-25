/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CGAMEWINDOW24
#define CGAMEWINDOW24

#include "wx/wx.h"
#include "wx/image.h"
#include "wx/dcbuffer.h"
#include "CBoard.h"
#include "CStatusBar.h"

//only declarations
class CGame;
class CPlayer;

class CGameWindow : public wxPanel
{
public:
    CGameWindow(wxWindow *parent, CStatusBar *stat_bar);

    // event handlers 
	void OnPaint(wxPaintEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnMouse(wxMouseEvent& event);
	void OnErase(wxEraseEvent& event);

	void Draw(CBoard board);
	void Draw(wxDC &dc);
	void Draw();

	enum Player{
		human,
		computer_easy,
		computer_medium,
		computer_hard
	};

	void NewGame(Player player1, Player player2);
	bool MoveForMe();
	bool UndoMove();

private:
    DECLARE_EVENT_TABLE()

	void DrawBackground(wxDC &dc);
	void DrawDraughts(wxDC &dc);
	void DrawSelect(wxDC &dc);
	
	wxTimer m_timer;
	wxImage m_img_green;
	wxImage m_img_red;
	wxImage m_img_background;
	wxImage m_img_select1;
	wxImage m_img_select2;

	CGame *m_game;
	CPlayer *m_player1;
	CPlayer *m_player2;

	Player m_player1_type;
	Player m_player2_type;

	CStatusBar *m_status_bar;
	CBoard m_board;

	bool m_blink;
	int m_box_size;
	int m_select;
};

enum
{
    CGameWindow_timer
};

#endif