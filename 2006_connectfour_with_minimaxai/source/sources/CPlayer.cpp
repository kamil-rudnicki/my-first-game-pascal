/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CPlayer.h"

//***************************************************************************

CPlayer::CPlayer(CGame *game, CBoard::player player)
{
	m_game=game;
	m_player=player;
}

//***************************************************************************

CPlayer::~CPlayer()
{
}

//***************************************************************************