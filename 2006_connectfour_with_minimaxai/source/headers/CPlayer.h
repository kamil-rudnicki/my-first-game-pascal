/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CPLAYER323
#define CPLAYER323

#include "CBoard.h"
#include "CGame.h"

class CGame;

class CPlayer
{
public:

	CPlayer(CGame *game, CBoard::player player);
	virtual ~CPlayer();

	virtual bool  Move(int n) = 0;

	CBoard::player m_player;
	CGame *m_game;

};

#endif