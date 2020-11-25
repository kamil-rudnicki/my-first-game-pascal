/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CBOARD67
#define CBOARD67

class CBoard{
public:

   CBoard();
   CBoard(const CBoard &p);
   CBoard & operator =(const CBoard &p);
   ~CBoard();

   enum player{
	   empty=0, 
	   green=1, 
	   red=2,
	   draw
   };

   void Blink();

   player CheckVertical(int x, int y, int &val); //pionowo
   player CheckHorizontal(int x, int y, int &val, int &pos); //poziomo
   player CheckCrossRight(int x, int y, int &val, int &pos);
   player CheckCrossLeft(int x, int y, int &val, int &pos);

   void Add(player p, int x, int y);
   int Add(player p, int x);
   void Clear(int x, int y);
   void Clear();
   player Get(int x, int y);
   player IsFinish();
   bool IsBlink(int x, int y);

   const int width;
   const int height;

private:
	
	int blink_board[4][2];
	player board[7][6];
};

#endif