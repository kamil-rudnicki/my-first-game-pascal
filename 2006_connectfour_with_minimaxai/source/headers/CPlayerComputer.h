/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CPLAYERCOMPUTER23
#define CPLAYERCOMPUTER23

#include "CPlayer.h"

class CPlayerComputer : public CPlayer
{
public:
	CPlayerComputer(CGame *game, CBoard::player player, int n);
	~CPlayerComputer();

	bool Move(int n);
    
private:

	//mini-max algorithm
	struct Point{
		int x;
		int y;
		int val;
	};
	struct Expectians{
		int m_count;
		int m_cord[7][2];
	};

	int m_max_search_depth; //from 2 till 7
	const int plus_infinity;
	const int minus_infinity;
	CBoard m_board;

	int Evaluate(CBoard::player player);
	inline Expectians GenerateMoves();
	inline CBoard::player NextPlayer(CBoard::player p);
	Point Minimax(CBoard::player player, int depth, int alpha, int beta);
	//end mini-max algorithm

};

#endif