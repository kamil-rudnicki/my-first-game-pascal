/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CPlayerComputer.h"
#include <stdlib.h>
#include "wx/toolbar.h"

//***************************************************************************

CPlayerComputer::CPlayerComputer(CGame *game, CBoard::player player, int n)
	: CPlayer(game, player), plus_infinity(10000), minus_infinity(-10000)
{
	if(n<1 || n>10) n=2;
	m_max_search_depth=n;
}

//***************************************************************************

CPlayerComputer::~CPlayerComputer()
{
}

//***************************************************************************

bool CPlayerComputer::Move(int n)
{
	bool temp=false;

	if(m_game->GetAllow(m_player))
	{
		m_board=m_game->GetBoard();

		wxLogStatus(_("Please wait a moment, I must think..."));
		Point temp_result=Minimax(m_player, 0, minus_infinity, plus_infinity);
		wxLogStatus(_("OK, it's your turn!"));


		if(temp_result.x==-1){
			Expectians temp_expectians=GenerateMoves();
			srand(time(0));
			int c=rand()%temp_expectians.m_count;
			temp_result.x=temp_expectians.m_cord[c][0];
		}

		temp=m_game->MakeMove(temp_result.x);
	}

	return temp;
}

//***************************************************************************

CBoard::player CPlayerComputer::NextPlayer(CBoard::player p)
{
	if(p==CBoard::red) return CBoard::green;
	else return CBoard::red;

	return CBoard::empty;
}

//***************************************************************************

CPlayerComputer::Expectians CPlayerComputer::GenerateMoves()
{
	Expectians expectians;

	expectians.m_count=0;

	for(int i=0; i<7; i++)
		for(int j=5; j>=0; j--)
			if(m_board.Get(i, j)==CBoard::empty)
			{
				expectians.m_count++;
				expectians.m_cord[expectians.m_count-1][0]=i;
				expectians.m_cord[expectians.m_count-1][1]=j;
				break;
			}

	return expectians;
}

//***************************************************************************

int CPlayerComputer::Evaluate(CBoard::player player)
{
	int greenresult=0;
	int redresult=0;
	CBoard::player temp_player;
	int temp_val=0;
	int ble;

	for(int i=0; i<6; i++)
	{
		for(int j=0; j<7; j++)
		{
			temp_player=m_board.CheckHorizontal(j,i,temp_val, ble);
			if(temp_val>0)
			{
				if(temp_player==CBoard::green)
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return plus_infinity;
						else return minus_infinity;
					}
					else if(temp_val==3){
						if(ble==-1) temp_val=30;
						else if((ble==0  && m_board.Get(j-1, i)==CBoard::empty && (m_board.Get(j-1, i+1)==CBoard::green || m_board.Get(j-1, i+1)==CBoard::red)) ||
							(ble==1  && m_board.Get(j+4, i)==CBoard::empty && (m_board.Get(j+4, i+1)==CBoard::green || m_board.Get(j+4, i+1)==CBoard::red)))
							temp_val=500;
					}
					else if(temp_val==2) temp_val=10;
					else if(temp_val==1) temp_val=3;
					greenresult+=temp_val;
				}
				else
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return minus_infinity;
						else return plus_infinity;  
					}
					else if(temp_val==3){
						if(ble==-1) temp_val=30;
						else if((ble==0  && m_board.Get(j-1, i)==CBoard::empty && (m_board.Get(j-1, i+1)==CBoard::green || m_board.Get(j-1, i+1)==CBoard::red)) ||
							(ble==1  && m_board.Get(j+4, i)==CBoard::empty && (m_board.Get(j+4, i+1)==CBoard::green || m_board.Get(j+4, i+1)==CBoard::red)))
							temp_val=500;
					}
					else if(temp_val==2) temp_val=10;
					else if(temp_val==1) temp_val=3;
					redresult+=temp_val;
				}
			}


			
			temp_player=m_board.CheckCrossLeft(j,i,temp_val, ble);
			if(temp_val>0)
			{
				if(temp_player==CBoard::green)
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return plus_infinity;
						else return minus_infinity;
					}
					else if(temp_val==3){
						if(ble==-1) temp_val=30;
						else if((ble==0 && m_board.Get(j+1, i-1)==CBoard::empty && (m_board.Get(j+1, i)==CBoard::green || m_board.Get(j+1, i)==CBoard::red)) ||
							(ble==1 && m_board.Get(j-4, i+4)==CBoard::empty && (m_board.Get(j-4, i+5)==CBoard::green || m_board.Get(j-4, i+5)==CBoard::red)))
							temp_val=500;
					}
					else if(temp_val==2) temp_val=10;
					else if(temp_val==1) temp_val=3;
					greenresult+=temp_val;
				}
				else
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return minus_infinity;
						else return plus_infinity;  
					}
					else if(temp_val==3){
						if(ble==-1) temp_val=30;
						else if((ble==0 && m_board.Get(j+1, i-1)==CBoard::empty && (m_board.Get(j+1, i)==CBoard::green || m_board.Get(j+1, i)==CBoard::red)) ||
							(ble==1 && m_board.Get(j-4, i+4)==CBoard::empty && (m_board.Get(j-4, i+5)==CBoard::green || m_board.Get(j-4, i+5)==CBoard::red)))
							temp_val=500;
					}
					else if(temp_val==2) temp_val=10;
					else if(temp_val==1) temp_val=3;
					redresult+=temp_val;
				}
			}

			temp_player=m_board.CheckCrossRight(j,i,temp_val, ble);
			if(temp_val>0)
			{
				if(temp_player==CBoard::green)
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return plus_infinity;
						else return minus_infinity;
					}
					else if(temp_val==3){
						if(ble==-1) temp_val=30;
						else if((ble==0 && m_board.Get(j-1, i-1)==CBoard::empty && (m_board.Get(j-1, i)==CBoard::green || m_board.Get(j-1, i)==CBoard::red)) ||
							(ble==1 && m_board.Get(j+4, i+4)==CBoard::empty&& (m_board.Get(j+4, i+5)==CBoard::green || m_board.Get(j+4, i+5)==CBoard::red)))
							temp_val=500;
					}
					else if(temp_val==2) temp_val=10;
					else if(temp_val==1) temp_val=3;
					greenresult+=temp_val;
				}
				else
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return minus_infinity;
						else return plus_infinity;  
					}
					else if(temp_val==3){
						if(ble==-1) temp_val=30;
						else if((ble==0 && m_board.Get(j-1, i-1)==CBoard::empty && (m_board.Get(j-1, i)==CBoard::green || m_board.Get(j-1, i)==CBoard::red)) ||
							(ble==1 && m_board.Get(j+4, i+4)==CBoard::empty && (m_board.Get(j+4, i+5)==CBoard::green || m_board.Get(j+4, i+5)==CBoard::red)))
							temp_val=500;
					}
					else if(temp_val==2) temp_val=10;
					else if(temp_val==1) temp_val=3;
					redresult+=temp_val;
				}
			}

			

			temp_player=m_board.CheckVertical(j,i,temp_val);
			if(temp_val>0)
			{
				if(temp_player==CBoard::green)
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return plus_infinity;
						else return minus_infinity;
					}
				}
				else
				{ 
					if(temp_val==4){ 
						if(player==CBoard::green) return minus_infinity;
						else return plus_infinity;  
					}
				}
			}
		}
	}

	int result=0;

	if(player==CBoard::green) result=greenresult-redresult;
	else result=redresult-greenresult;

	return result;
}

//***************************************************************************

CPlayerComputer::Point CPlayerComputer::Minimax(CBoard::player player, int depth, int alpha, int beta)
{
	Expectians expectians=GenerateMoves();
	Point best;
	best.x=-1;

	if(depth==m_max_search_depth || expectians.m_count==0 || m_board.IsFinish()!=CBoard::empty){
		best.val=Evaluate(player);
		return best;
	}

	best.val=alpha;
	int v;

	for(int i=0; i<expectians.m_count; i++)
	{
		m_board.Add(player, expectians.m_cord[i][0], expectians.m_cord[i][1]);
		v=-Minimax(NextPlayer(player), depth+1, -beta, -best.val).val;
		if(v>best.val){
			best.x=expectians.m_cord[i][0];
			best.y=expectians.m_cord[i][1];
			best.val=v;
			if (v >= beta)
			{
				m_board.Add(CBoard::empty, expectians.m_cord[i][0], expectians.m_cord[i][1]);
				return best;
			}
		}
		m_board.Add(CBoard::empty, expectians.m_cord[i][0], expectians.m_cord[i][1]);
	}

	return best;
}

//***************************************************************************