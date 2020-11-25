#ifndef PLANSZA
#define PLANSZA

#include <fstream.h>
#include "klocek.h"
#include "ball.h"

extern GLuint g_tloTexture;
extern GLuint g_paletkaTexture;

#define NUM_BRICKS_VERTICAL		16								// Number of bricks in the Y direction
#define NUM_BRICKS_HORIZONTAL	24								// Number of bricks in the X direction

class plansza{
public:
	float width, height;
	float x, y;
	static float depth;
	int level;												// Current playing level
	int score;
	int ilosc_klockow;
	klocek klocki[16*24];
	plansza();
	~plansza();
	void laduj_plansze();
	void rysuj_plansze();
};

float plansza::depth;

plansza::plansza()
{
	height=68;
	y=height/2;
	width=96;
	x=-(width/2);
	depth=-3;
	laduj_plansze();
	depth=-2;
	score=10;
}
plansza::~plansza()
{
}

void plansza::rysuj_plansze()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, g_tloTexture);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);//beckgroud
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(x, -y, depth);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(-x, -y, depth);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(-x, y, depth);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(x, y,depth);
		glEnd();
		
	
		glBindTexture(GL_TEXTURE_2D, g_paletkaTexture);
		glBegin(GL_QUADS);//gora
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x-2, y, 0);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-x+2, y, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-x+2, y, depth);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x-2, y, depth);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x-2, y+2, 0);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-x+2, y+2, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-x+2, y+2, depth);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x-2, y+2, depth);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(x-2, y, 0);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(-x+2, y, 0);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(-x+2, y+2, 0);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(x-2, y+2,0);
		glEnd();



		glBegin(GL_QUADS);//prawo
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-x, -y, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-x, -y, depth);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-x, y+2, depth);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, y+2, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-x+2, -y, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-x+2, -y, depth);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-x+2, y, depth);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-x+2, y, 0);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-x+2, -y, 0);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(-x, -y, 0);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(-x, y, 0);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-x+2, y,0);
		glEnd();


		glBegin(GL_QUADS);//lewo
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -y, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x, -y, depth);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y+2, depth); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y+2, 0);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x-2, -y, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x-2, -y, depth);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x-2, y, depth);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x-2, y, 0);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);glVertex3f(x-2, -y, 0);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x, -y, 0);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(x, y, 0);
			glTexCoord2f(0.0f, 1.0f);glVertex3f(x-2, y,0);
		glEnd();


	glPopMatrix();
}



void plansza::laduj_plansze()
{
klocek klocek;
float m=x+(klocek.width/2);
float n=y-(klocek.height/2);
char ch;

int li=0;
ilosc_klockow=0;

ifstream infile("level/runda.txt");
	infile.seekg(0);
	while(!infile.eof())
	{       
	  infile.get(ch);
	  if(ch=='\n')continue;
	  if(ch-48==1)
	  {
		  klocki[li].x=m-(klocek.width/2); klocki[li].y=n+(klocek.height/2);
		  
		  li++; ilosc_klockow++;
		  klocki[li].istnieje=true;
	  }
	  m+=klocek.width; 
	  if(m>-x-(klocek.width/2)){m=x+(klocek.width/2); n-=klocek.height;}
	}
infile.close();
}



#endif