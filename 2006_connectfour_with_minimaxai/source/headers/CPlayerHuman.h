/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CPLAYERHUMAN23
#define CPLAYERHUMAN23

#include "CPlayer.h"

class CPlayerHuman : public CPlayer
{
public:
	CPlayerHuman(CGame *game, CBoard::player player);
	~CPlayerHuman();

	bool Move(int n);
    
private:

};

#endif