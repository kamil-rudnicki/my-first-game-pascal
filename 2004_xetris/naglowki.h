#ifndef	H_NAGLOWKI
#define H_NAGLOWKI

#include <allegro.h>
#include "klocek.h"
#include "plansza.h"
#include "gra.h"
#include "highscore.h"

extern BITMAP *dblbuffer;//drugi bufor
extern BITMAP *buffer3;
extern DATAFILE *datafile_sound;
extern DATAFILE *datafile_gfx;
extern DATAFILE *datafile_font;
extern int elapsed_seconds;
extern int elapsed_seconds1;

void increment_seconds();

const int klocek1_1[4][4]={1,0,0,0,
					 1,0,0,0,
					 1,0,0,0,
					 1,0,0,0};

const int klocek1_2[4][4]={1,1,1,1,
					 0,0,0,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek2_1[4][4]={0,2,0,0,
					 0,2,0,0,
					 2,2,0,0,
					 0,0,0,0};

const int klocek2_2[4][4]={2,0,0,0,
					 2,2,2,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek2_3[4][4]={2,2,0,0,
					 2,0,0,0,
					 2,0,0,0,
					 0,0,0,0};

const int klocek2_4[4][4]={2,2,2,0,
					 0,0,2,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek3_1[4][4]={2,0,0,0,
					 2,0,0,0,
					 2,2,0,0,
					 0,0,0,0};

const int klocek3_2[4][4]={2,2,2,0,
					 2,0,0,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek3_3[4][4]={2,2,0,0,
					 0,2,0,0,
					 0,2,0,0,
					 0,0,0,0};

const int klocek3_4[4][4]={0,0,2,0,
					 2,2,2,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek4_1[4][4]={3,3,0,0,
					 3,3,0,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek5_1[4][4]={0,4,0,0,
					 4,4,4,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek5_2[4][4]={4,0,0,0,
					 4,4,0,0,
					 4,0,0,0,
					 0,0,0,0};

const int klocek5_3[4][4]={4,4,4,0,
					 0,4,0,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek5_4[4][4]={0,4,0,0,
					 4,4,0,0,
					 0,4,0,0,
					 0,0,0,0};

const int klocek6_1[4][4]={5,5,0,0,
					 0,5,5,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek6_2[4][4]={0,5,0,0,
					 5,5,0,0,
					 5,0,0,0,
					 0,0,0,0};

const int klocek7_1[4][4]={0,5,5,0,
					 5,5,0,0,
					 0,0,0,0,
					 0,0,0,0};

const int klocek7_2[4][4]={5,0,0,0,
					 5,5,0,0,
					 0,5,0,0,
					 0,0,0,0};


#endif