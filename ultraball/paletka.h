#ifndef PALETKA
#define PALETKA

#include <windows.h>
#include <math.h>									// For sin/cos functions
#include <gl\gl.h>									// Header File For The OpenGL32 Library
#include "Ball.h"

extern GLuint g_paletkaTexture;
extern FSOUND_SAMPLE *sound_ball_falling;
 
class Paddle {
public:
	  float width, height;	
	  float width1, height1;				// Paddle dimensions
      float x, y;									// Top-left position on screen
	  float oldx, oldy;								// Last x,y position
	  float speed;									// Movement speed
      Paddle();										// Constructor
	  ~Paddle();									// Destructor
	  void Check_Ball_Collision(Ball *ball);				// Does collisions with paddle, and take appropriate action on ball
	  void Draw();										// Draw to opengl screen
	  plansza plansza;
};

Paddle :: Paddle():
	width(20),
	height(2),
	speed(1.0f)
{ 

	width1=width/2;
	height1=height/2;
	x=0-width1;
	y=-34;
}

Paddle :: ~Paddle()
{ }

void Paddle :: Check_Ball_Collision(Ball *ball)
{
	if((ball->yi < 0) && ((ball->y - ball->diameter - ball->speed) < y) && ((ball->x + ball->diameter) >= x) && (ball->x <= (x + width)))	
	{
		ball->xi = (float)sin( ((ball->x + ball->radius - x - width/2) / (width/2)) * 65/180 * 3.141592654 );
		ball->yi = (float)cos( ((ball->x + ball->radius - x - width/2) / (width/2)) * 65/180 * 3.141592654 );
		FSOUND_PlaySound(FSOUND_FREE, sound_ball_falling);
	}
	
}

void Paddle::Draw()
{
glBindTexture(GL_TEXTURE_2D, g_paletkaTexture);
glColor3f(1.0f,1.0f,1.2f);				// green colour


glPushMatrix();
		glTranslatef(x+width1, y+height1, 0);
		glBindTexture(GL_TEXTURE_2D, g_paletkaTexture);
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);	// górna œciana
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-width1, height1, plansza.depth);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(width1, height1, plansza.depth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(width1, height1, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-width1, height1, 0);

			glNormal3f(1.0f, 0.0f, 0.0f);	// prawa œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(width1, height1, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(width1, height1, plansza.depth);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(width1, -height1, plansza.depth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(width1, -height1, 0);

			glNormal3f(-1.0f, 0.0f, 0.0f);	// lewa œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-width1, -height1, plansza.depth);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-width1, height1, plansza.depth);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-width1, height1, 0); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-width1, -height1, 0);

			glNormal3f(0.0f, -1.0f, 0.0f);	// dolna œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(width1, -height1, plansza.depth);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-width1, -height1, plansza.depth); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-width1, -height1, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(width1, -height1, 0);	

			glNormal3f(0.0f, 0.0f, -1.0f);	// tylna œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(width1, height1, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(width1, -height1, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-width1, -height1, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-width1, height1, 0);
		glEnd();
glPopMatrix();


}

#endif