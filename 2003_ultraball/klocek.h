#ifndef KLOCEK
#define KLOCEK

#include "ball.h"
#include "fmod.h"
#include <gl\gl.h>									// Header File For The OpenGL32 Library
#include <gl\glu.h>

extern GLuint  g_mouseTexture;    //texture
extern FSOUND_SAMPLE *sound_ball_falling;

class klocek{
public:
	~klocek(){};
	int typ;
	float x;
	float y;
	bool istnieje;
	float width, height;
	void hit();
	void zderzenie_klocka(Ball *ball);
	void rysuj_klocek(float x, float y);
	klocek();
};

klocek::klocek()
{
	width=6;
	height=2;
}

void klocek::hit()
{
	istnieje=false;
	FSOUND_PlaySound(FSOUND_FREE, sound_ball_falling);
}

void klocek::zderzenie_klocka(Ball *ball)
{	
	if(istnieje==true)
	{
		if ((ball->xi > 0) &&									// If ball is travelling right
			((ball->x + ball->diameter + ball->speed) > x) &&	// Check ball will actually cross the path of the paddle during next move
			((ball->x + ball->diameter + ball->speed) < (x + width)) &&
			((ball->y - ball->radius) < y) &&					// Then check we are within the range of the width of the paddle
			((ball->y - ball->radius) >= (y - height)))			// One of these has to be >= otherwise we miss inbetween bricks
			{
				ball->xi=-ball->xi; 
				hit();
			}
		else if ((ball->xi < 0) &&								// If ball is travelling left
			((ball->x - ball->speed) < (x + width)) &&			// Check ball will actually cross the path of the paddle during next move
			((ball->x - ball->speed) > x) &&
			((ball->y - ball->radius) < y) &&					// Then check we are within the range of the width of the paddle
			((ball->y - ball->radius) >= (y - height)))			// One of these has to be >= otherwise we miss inbetween bricks
			{
				ball->xi=-ball->xi;
				hit();
			}
		if ((ball->yi < 0) &&									// If ball is travelling down
		    (((ball->y - ball->diameter - ball->speed) < y) &&			// Check ball will actually cross the path of the paddle during next move
			((ball->y - ball->diameter - ball->speed) > y - height)) &&
			((ball->x + ball->radius) >= x) &&					// One of these has to be >= otherwise we miss inbetween bricks	
			((ball->x + ball->radius) < (x + width)))			// Then check we are within the range of the width of the paddle
			{
				ball->yi=-ball->yi;
				hit();
			}
		else if ((ball->yi > 0) &&								// If ball is travelling up
			((ball->y + ball->speed) > (y - height)) &&			// Check ball will actually cross the path of the paddle during next move
			((ball->y + ball->speed) < (y)) &&					// But not past the back of it
			((ball->x + ball->radius) >= x) &&					// One of these has to be >= otherwise we miss inbetween bricks
			((ball->x + ball->radius) < (x + width)))			// Then check we are within the range of the width of the paddle
			{
				ball->yi=-ball->yi;
				hit();
			}
	}
}

void klocek::rysuj_klocek(float x, float y){
	if(istnieje)
	{
	glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, g_mouseTexture);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);	// górna œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, height/2, -2);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(width/2, height/2, -2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(width/2, height/2, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, height/2, 0);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);	// tylna œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(width/2, -height/2, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(width/2, height/2, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2, height/2, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, 0);
		glEnd();
		
		glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);	// prawa œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(width/2, height/2, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(width/2, height/2, -2);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(width/2, -height/2, -2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(width/2, -height/2, 0);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);	// lewa œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, height/2, -2);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2, height/2, 0); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, 0);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, -1.0f, 0.0f);	// dolna œciana
			glTexCoord2f(0.0f, 0.0f); glVertex3f(width/2, -height/2, -2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -2); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2, -height/2, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(width/2, -height/2, 0);	
		glEnd();
	glPopMatrix();
	}
}

#endif