/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CBoard.h"

//***************************************************************************

CBoard::CBoard(): width(7), height(6)
{
	Clear();
}

CBoard & CBoard::operator =(const CBoard &p)
{
	Clear();

	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			board[i][j]=p.board[i][j];
	
	for(int i=0; i<4; i++)
	{
		blink_board[i][0]=p.blink_board[i][0];
		blink_board[i][1]=p.blink_board[i][1];
	}

	return *this;
}

CBoard::CBoard(const CBoard &p): width(7), height(6)
{
	Clear();

	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			board[i][j]=p.board[i][j];
	
	for(int i=0; i<4; i++)
	{
		blink_board[i][0]=p.blink_board[i][0];
		blink_board[i][1]=p.blink_board[i][1];
	}
}

//***************************************************************************

CBoard::~CBoard()
{

}

//***************************************************************************

void CBoard::Add(CBoard::player p, int x, int y)
{
	if(x>=0 && x<width && y>=0 && y<height)
		board[x][y]=p;
}

//***************************************************************************

//return 0 if there is no space to move
int CBoard::Add(CBoard::player p, int x)
{
	int t=-1;

	if(x>=0 && x<width)
		for(int i=height-1; i>=0; i--)
			if(board[x][i]==empty)
			{
				t=i;
				board[x][i]=p;
				return t;
			}

	return t;
}

//***************************************************************************

void CBoard::Clear()
{
	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			board[i][j]=empty;

	for(int i=0; i<4; i++)
		for(int j=0; j<2; j++)
			blink_board[i][j]=-1;
}

//***************************************************************************

void CBoard::Clear(int x, int y)
{
	if(x>=0 && x<width && y>=0 && y<height)
		board[x][y]=empty;
}

//***************************************************************************

CBoard::player CBoard::Get(int x, int y)
{
	if(x>=0 && x<width && y>=0 && y<height)
		return board[x][y];

	return draw;
}

//***************************************************************************

CBoard::player CBoard::CheckVertical(int x, int y, int &val)
{
	val=0;
	player p=empty;
	if(y>(height-4)) return empty;
	int green_p=0;
	int red_p=0;

	if(board[x][y]==red) red_p++;
	else if(board[x][y]==green) green_p++;
	if(board[x][y+1]==red) red_p++;
	else if(board[x][y+1]==green) green_p++;
	if(board[x][y+2]==red) red_p++;
	else if(board[x][y+2]==green) green_p++;
	if(board[x][y+3]==red) red_p++;
	else if(board[x][y+3]==green) green_p++;

	//if(board[x][y+1]==board[x][y+2]==board[x][y]==board[x][y+3]==green) green_p=4;
	//else if(board[x][y+1]==board[x][y+2]==board[x][y]==board[x][y+3]==red) red_p=4;

	if(red_p>0 && green_p>0) return empty;
	if(green_p>0){ 
		val=green_p;
		return green;
	}else if(red_p>0){
		val=red_p;
		return red;
	}

	return empty;
}

//***************************************************************************

CBoard::player CBoard::CheckHorizontal(int x, int y, int &val, int &pos)
{
	val=0;
	pos=-1;
	player p=empty;
	if(x>(width-4)) return empty;
	int green_p=0;
	int red_p=0;

	if(board[x][y]==red) red_p++;
	else if(board[x][y]==green) green_p++;
	if(board[x+1][y]==red) red_p++;
	else if(board[x+1][y]==green) green_p++;
	if(board[x+2][y]==red) red_p++;
	else if(board[x+2][y]==green) green_p++;
	if(board[x+3][y]==red) red_p++;
	else if(board[x+3][y]==green) green_p++;

	if(red_p>0 && green_p>0) return empty;
	if(green_p>0){ 
		val=green_p;

		if(green_p==3 && board[x+1][y]==green &&  board[x+2][y]==green)
			if(board[x][y]==empty) pos=1;
			else pos=0;

		return green;
	}else if(red_p>0){
		val=red_p;

		if(green_p==3 && board[x+1][y]==red &&  board[x+2][y]==red)
			if(board[x][y]==empty) pos=1;
			else pos=0;

		return red;
	}

	return empty;
}

//***************************************************************************

CBoard::player CBoard::CheckCrossRight(int x, int y, int &val, int &pos)
{
	val=0;
	pos=-1;
	player p=empty;
	if(y>(height-4) || x>(width-4)) return empty;
	int green_p=0;
	int red_p=0;

	if(board[x][y]==red) red_p++;
	else if(board[x][y]==green) green_p++;
	if(board[x+1][y+1]==red) red_p++;
	else if(board[x+1][y+1]==green) green_p++;
	if(board[x+2][y+2]==red) red_p++;
	else if(board[x+2][y+2]==green) green_p++;
	if(board[x+3][y+3]==red) red_p++;
	else if(board[x+3][y+3]==green) green_p++;

	if(red_p>0 && green_p>0) return empty;
	if(green_p>0){ 
		val=green_p;

		if(green_p==3 && board[x+1][y+1]==green &&  board[x+2][y+2]==green)
			if(board[x][y]==empty) pos=1;
			else pos=0;
		
		return green;
	}else if(red_p>0){
		val=red_p;

		if(green_p==3 && board[x+1][y+1]==red &&  board[x+2][y+2]==red)
			if(board[x][y]==empty) pos=1;
			else pos=0;

		return red;
	}

	return empty;
}

//***************************************************************************

CBoard::player CBoard::CheckCrossLeft(int x, int y, int &val, int &pos)
{
	val=0;
	pos=-1;
	player p=empty;
	if(y>(height-4) || x<3) return empty;
	int green_p=0;
	int red_p=0;

	if(board[x][y]==red) red_p++;
	else if(board[x][y]==green) green_p++;
	if(board[x-1][y+1]==red) red_p++;
	else if(board[x-1][y+1]==green) green_p++;
	if(board[x-2][y+2]==red) red_p++;
	else if(board[x-2][y+2]==green) green_p++;
	if(board[x-3][y+3]==red) red_p++;
	else if(board[x-3][y+3]==green) green_p++;

	if(red_p>0 && green_p>0) return empty;
	if(green_p>0){ 
		val=green_p;

		if(green_p==3 && board[x-1][y+1]==green &&  board[x-2][y+2]==green)
			if(board[x][y]==empty) pos=1;
			else pos=0;

		return green;
	}else if(red_p>0){
		val=red_p;

		if(green_p==3 && board[x-1][y+1]==red &&  board[x-2][y+2]==red)
			if(board[x][y]==empty) pos=1;
			else pos=0;

		return red;
	}

	return empty;
}

//***************************************************************************

CBoard::player CBoard::IsFinish()
{
	int is_draw=0;
	int nothing;

	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			int temp_val=0;
			player temp_player=empty;

			temp_player=empty;
			temp_player=CheckVertical(j, i, temp_val);
			if(temp_val==4){
				blink_board[0][0]=j; blink_board[0][1]=i; 
				blink_board[1][0]=j; blink_board[1][1]=i+1; 
				blink_board[2][0]=j; blink_board[2][1]=i+2; 
				blink_board[3][0]=j; blink_board[3][1]=i+3; 

				if(temp_player==red) return red;
				else if(temp_player==green)return green;
			}
			is_draw+=temp_val;

			temp_player=empty;
			temp_player=CheckHorizontal(j, i, temp_val, nothing);
			if(temp_val==4){
				blink_board[0][0]=j; blink_board[0][1]=i; 
				blink_board[1][0]=j+1; blink_board[1][1]=i; 
				blink_board[2][0]=j+2; blink_board[2][1]=i; 
				blink_board[3][0]=j+3; blink_board[3][1]=i; 

				if(temp_player==red) return red;
				else if(temp_player==green)return green;
			}
			is_draw+=temp_val;

			temp_player=empty;
			temp_player=CheckCrossRight(j, i, temp_val, nothing);
			if(temp_val==4){
				blink_board[0][0]=j; blink_board[0][1]=i; 
				blink_board[1][0]=j+1; blink_board[1][1]=i+1; 
				blink_board[2][0]=j+2; blink_board[2][1]=i+2; 
				blink_board[3][0]=j+3; blink_board[3][1]=i+3; 

				if(temp_player==red) return red;
				else if(temp_player==green) return green;
			}
			is_draw+=temp_val;

			temp_player=empty;
			temp_player=CheckCrossLeft(j, i, temp_val, nothing);
			if(temp_val==4){
				blink_board[0][0]=j; blink_board[0][1]=i; 
				blink_board[1][0]=j-1; blink_board[1][1]=i+1; 
				blink_board[2][0]=j-2; blink_board[2][1]=i+2; 
				blink_board[3][0]=j-3; blink_board[3][1]=i+3; 

				if(temp_player==red) return red;
				else if(temp_player==green)return green;
			}
			is_draw+=temp_val;
		}
	}

	if(is_draw==0) return draw;

	return empty;
}

//***************************************************************************

bool CBoard::IsBlink(int x, int y)
{
	for(int i=0; i<4; i++)
	{
		if(blink_board[i][0]==x && blink_board[i][1]==y)
			return true;
	}

	return false;
}

//***************************************************************************

