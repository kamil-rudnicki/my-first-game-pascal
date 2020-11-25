/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CPlayerHuman.h"
#include "CPlayerComputer.h"

//***************************************************************************

CPlayerHuman::CPlayerHuman(CGame *game, CBoard::player player)
	: CPlayer(game, player)
{
	
}

//***************************************************************************

CPlayerHuman::~CPlayerHuman()
{
}

//***************************************************************************

bool CPlayerHuman::Move(int n)
{
	bool temp=false;

	if(m_game->GetAllow(m_player))
	{
		temp=m_game->MakeMove(n);
	}

	return temp;
}

//***************************************************************************