#ifndef	H_BALL
#define H_BALL

#include <windows.h>
#include <gl\gl.h>							// Header File For The OpenGL32 Library
#include <gl\glu.h>							// Glu32 header for quadrics

class Ball {
private:
	GLUquadricObj *g_normalObject;					// Storage for quadratic object
public:
    float x, y, z;						// pozycja
	float xi, yi, zi;						// wektor x, y
	float speed;							// szybkosc
	float radius;							//wielkosc kuli
    float diameter;						//wielkosc kuli *2
	Ball();								
	~Ball();								
	Draw();								
};

Ball :: Ball():
	x(0.0f),
	y(-24.0f),
	z(0.0f),
	xi(0.0f),
	yi(0.8f),
	zi(0.0f),
	speed(0.8f)
{ 
	g_normalObject = gluNewQuadric();
	gluQuadricTexture(g_normalObject, GL_TRUE);
	radius = 1;
	diameter=radius*2;
}


Ball :: ~Ball()
{ 
	if (g_normalObject) gluDeleteQuadric(g_normalObject);
}


Ball :: Draw()
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glBegin(GL_POLYGON);
			glColor3f(2,2,2);
			gluSphere(g_normalObject, radius, 30, 20);
		glEnd();
	glPopMatrix();
}


#endif