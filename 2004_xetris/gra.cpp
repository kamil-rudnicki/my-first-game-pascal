#include "naglowki.h"

int gra::write_name(int p)
{
int position=0;												//This keeps track of the cursor position
char ch;													//keyboard characters are stored in this variable
char string[NAME_LENGTH+1]="\0";								//string to hold the users name
string[0]='_';
HighScore hiScore;
plansza plansza1;
clear_keybuf();
play_sample((SAMPLE *)datafile_sound[13].dat,256,127,1000,0);

	if(hiScore.testRecord(p)==0) return 1;							//See if users score is good enough for the highscore table, if not, return 0
	
		rect(dblbuffer, 170, 130, 520, 330, makecol(0, 0, 0));
		plansza1.zaciemnij(170,130,520,330,120,1,dblbuffer);
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "   Game Over", 183, 145, makecol(250, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "Type your name, and press enter: ", 183, 231, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "Type your name, and press enter: ", 182, 230, makecol(250, 250, 250));
		blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		blit(dblbuffer, buffer3, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		textout(dblbuffer, (FONT *)datafile_font[1].dat, string, 182, 270, makecol(100, 250, 100));
		blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

		while(!key[KEY_ESC]){
			blit(buffer3, dblbuffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			ch=0;													//Clears the key buffer
			ch=readkey();											//Gets a key from the keyboard	
			play_sample((SAMPLE *)datafile_sound[11].dat,256,127,1000,0);
			if(key[KEY_ENTER]) break;								//If user hits the enter key, be sure the line feed isn't saved into the last element of the string
			if(key[KEY_BACKSPACE]){									//When the user hits the backspace...
			if(position>0) position--;							//If the cursor is inside the textfield then decrease the cursor position
				string[position]='_';								//Imitate a backspace (clear the preceeding character)
				ch=0;												//Clear keyboard buffer
			}
			if((ch!=0)&&(position<NAME_LENGTH)){					//If a character was pressed, and the cursor position is within text boundries...
				string[position]=ch;								//Make the string position equal the key entered
				position++;											//increment the string position
				string[position]='_';
			}
			
			string[position+1]='_';								//Terminitate the string
			string[position+1]='\0';
			textout(dblbuffer, (FONT *)datafile_font[1].dat, string, 182, 270, makecol(100, 250, 100));
			blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}
	string[position]='\0';
	hiScore.addRecord(string,p);
	hiScore.~HighScore();
	HiScore();									//Add users record to highscore table
	return 0;
}

//**********************************************************************

void gra::HiScore()
{
	for(int i=0; i<16; i++) 
		for(int j=0; j<12; j++) blit((BITMAP *)datafile_gfx[6].dat, dblbuffer, 0, 0, i*40, j*40, i*40+40, j*40+40);

		plansza plan;
		plan.zaciemnij(120, 120, 480, 425, 50,1,dblbuffer);
		rect(dblbuffer, 120, 120, 480, 425, makecol(0, 0, 0));

	HighScore hiScore;			 					
	char tempString[20];

	for(int y=0;y<MAX_RECORDS;y++){											//Loops through the record
		textout(dblbuffer,(FONT *)datafile_font[1].dat,hiScore.viewRecordName(y),160,(y+3)*20+100,makecol(0, 0, 0));	//Prints the name
		sprintf(tempString,"%i",hiScore.viewRecordScore(y));					//Copies the score into a string
		textout(dblbuffer,(FONT *)datafile_font[1].dat, tempString,400,(y+3)*20+100,makecol(0, 0, 0));		//Prints the score
		textout(dblbuffer,(FONT *)datafile_font[1].dat, ". ",140,(y+3)*20+100,makecol(0, 0, 0));
		if(y==9)textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 125, (y+3)*20+100, makecol(0, 0, 250), "%d", y+1);
		else textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 135, (y+3)*20+100, makecol(0, 0, 250), "%d", y+1);
	}

	textout(dblbuffer, (FONT *)datafile_font[0].dat, " BEST SCORE", 203, 42, makecol(250, 0, 0));
	textout(dblbuffer, (FONT *)datafile_font[0].dat, " BEST SCORE", 199, 38, makecol(240, 240, 240));
	textout(dblbuffer,(FONT *)datafile_font[1].dat,"NAME                   SCORE",160,130,makecol(0, 80, 0));
	textout(dblbuffer,(FONT *)datafile_font[1].dat,"------------------------------",160,143,makecol(0, 80, 0));
	textout(dblbuffer, (FONT *)datafile_font[1].dat, "Press any key.", 250, 440, makecol(100,100,100));
	
blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//zmiana bufora
readkey();
}

//**********************************************************************

void gra::credits()
{
	blit(screen, buffer3, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//zmiana bufora

	for(int i=0; i<16; i++) 
			for(int j=0; j<12; j++) blit((BITMAP *)datafile_gfx[6].dat, dblbuffer, 0, 0, i*40, j*40, i*40+40, j*40+40);

		textout(dblbuffer, (FONT *)datafile_font[0].dat, "X E T R I S", 183, 42, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "X E T R I S", 179, 38, makecol(24, 24, 240));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "ver. 0.9", 360, 80, makecol(100,250,50));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "By: Kamil Rudnicki", 22, 180, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "By: Kamil Rudnicki", 21, 179, makecol(250, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "Web site:   http://kamilrudnicki.w.interia.pl", 22, 220, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "Email:      kamil1616@poczta.fm", 22, 240, makecol(0,0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "This game is based on ALLEGRO library. ", 22, 300, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "License: FREEWARE ", 22, 320, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "Press any key.", 250, 440, makecol(100,100,100));

	blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//zmiana bufora
	readkey();
	



}

//**********************************************************************

void gra::menu()
{
int numer=1;
float delay=0;
bool finish=false;
int x=226;
float dx=1;
bool menu=false;
int maks=5;
int sfx_volume=9;
int midi_volume=7;
plansza plan;
klocek k1, k2, k3, k4, k5;
k1.losuj();
k2.losuj();
k3.losuj();
k4.losuj();
k5.losuj();
int m=0, n=0;
int x1=0, y1=0;

/*	rest(1000);
	int i=1;
	float i1=1;
	while(i>0){
		clear(dblbuffer);
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "Kamil Rudnicki presents", 130, 210, makecol(i, i, i));
		blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		i+=i1;
		if(i>=250){rest(1000); i1=-1;}
	}
	i=1;
	i1=1;
	while(i!=0){
		clear(dblbuffer);
		textout(dblbuffer, (FONT *)datafile_font[0].dat, " X E T R I S", 190, 210, makecol(i, i, i));
		blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		i+=i1;
		if(i>=250){rest(500); i1=0; i=0;}
	}
	i=1;
	i1=1;
	while(i!=0){
		clear_to_color(dblbuffer, makecol(i, i, i));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, " X E T R I S", 190, 210, makecol(250, 250, 250));
		blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		i+=i1;
		if(i>=250){rest(500); i1=0; i=0;}
	}*/

	while(!finish){

		if(delay>0) delay -= 0.02;
		if(delay <= 0)
		{
		if (key[KEY_DOWN])
			{
			play_sample((SAMPLE *)datafile_sound[11].dat,256,127,1000,0);
			numer++;
			if(numer>maks) numer=maks;
				delay=0.1;
			}
		if (key[KEY_UP])
			{
			play_sample((SAMPLE *)datafile_sound[11].dat,256,127,1000,0);
			numer--;
			if(numer<1) numer=1;
				delay=0.1;
			}

		if (key[KEY_ENTER])
			{
			play_sample((SAMPLE *)datafile_sound[12].dat,256,127,1000,0);

			if(!menu){
			if(numer==1) {
				m=0; n=0;
				clear_keybuf(); 
				int n=nowa_gra(); 
				if(n==1) if(write_name(punkty)==1){clear_keybuf(); HiScore();}
				clear_keybuf(); delay=0.4;
			}
			else if(numer==2){m=0; n=0; clear_keybuf(); HiScore(); clear_keybuf(); delay=0.3;}
			else if(numer==3){clear_keybuf(); delay=0.3; menu=true; maks=3; numer=1;}
			else if(numer==4){m=0; n=0; clear_keybuf(); credits(); clear_keybuf(); delay=0.3;}
			else if(numer==5) finish=true;
			}else{
				if(numer==1){
					midi_volume++;
					if(midi_volume>9) midi_volume=0;
					if(midi_volume<0) midi_volume=9;
					clear_keybuf(); delay=0.1;
					if(midi_volume==0) set_volume(sfx_volume*28, 0);
					else set_volume(sfx_volume*28, midi_volume*28);
				}
				else if(numer==2){
					sfx_volume++;
					if(sfx_volume>9) sfx_volume=0;
					if(sfx_volume<0) sfx_volume=9;
					clear_keybuf(); delay=0.1;
					if(sfx_volume==0) set_volume(0, midi_volume*28);
					else set_volume(sfx_volume*28, midi_volume*28);
				}
				else if(numer==3){
					menu=false;
					maks=5;
					numer=1;
					clear_keybuf(); delay=0.3;
				}
			}
			}
		}


		drawing_mode(DRAW_MODE_COPY_PATTERN, (BITMAP *)datafile_gfx[6].dat,x1, y1);
		rectfill(dblbuffer, 0, 0, 640, 480, -1);
		solid_mode();
		
		if(x>226) dx=-1;
		else if(x<220) dx=1;

		x1++;
		y1++;
		if(x1>640) x1=0;
		if(y1>480) y1=0;

		x+=dx;

		plan.zaciemnij(170, 170, 480, 425, 50,1,dblbuffer);
		rect(dblbuffer, 170, 170, 480, 425, makecol(0, 0, 0));

		k1.wyswietl(30,50);
		k4.wyswietl(60,400);
		k3.wyswietl(520,380);
		k2.wyswietl(120,60);
		k5.wyswietl(520,20);

		textout(dblbuffer, (FONT *)datafile_font[0].dat, "X E T R I S", 220, 40, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "X E T R I S", 222, 42, makecol(240, 240, 240));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "X E T R I S", x, 45, makecol(0, 0, 240));

		if(!menu){
		textout(dblbuffer, (FONT *)datafile_font[0].dat, " NEW GAME", 220, 180, makecol(240, 240, 240));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, " BEST SCORE", 210, 230, makecol(240, 240, 240));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "  OPTIONS", 232, 280, makecol(240, 240, 240));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "  CREDITS", 230, 330, makecol(240, 240, 240));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "   EXIT", 240, 380, makecol(240, 240, 240));
		if(numer==1)textout(dblbuffer, (FONT *)datafile_font[0].dat, " NEW GAME", 216, 176, makecol(240, 0, 0));
		else if(numer==2)textout(dblbuffer, (FONT *)datafile_font[0].dat, " BEST SCORE", 214, 234, makecol(0, 240, 0));
		else if(numer==3)textout(dblbuffer, (FONT *)datafile_font[0].dat, "  OPTIONS", 228, 284, makecol(0, 0, 240));
		else if(numer==4)textout(dblbuffer, (FONT *)datafile_font[0].dat, "  CREDITS", 226, 326, makecol(240, 0, 0));
		else if(numer==5)textout(dblbuffer, (FONT *)datafile_font[0].dat, "   EXIT", 236, 384, makecol(0, 240, 0));
		}else{

		textprintf(dblbuffer,(FONT *)datafile_font[0].dat,230,280,makecol(240, 240, 240)," music: %d",midi_volume);
		textprintf(dblbuffer,(FONT *)datafile_font[0].dat,230,330,makecol(240, 240, 240),"  SFX: %d",sfx_volume);
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "  BACK", 240, 380, makecol(240, 240, 240));

		if(numer==1)textprintf(dblbuffer,(FONT *)datafile_font[0].dat,234,276,makecol(0, 0, 240)," music: %d",midi_volume);
		else if(numer==2)textprintf(dblbuffer,(FONT *)datafile_font[0].dat,234,334,makecol(240, 0, 0),"  SFX: %d",sfx_volume);
		else if(numer==3)textout(dblbuffer, (FONT *)datafile_font[0].dat, "  BACK", 236, 384, makecol(0, 240, 0));
		

			textout(dblbuffer, font, "KEYS:", 240, 180, makecol(250, 250, 250));
			textout(dblbuffer, font, "change music:  A", 240, 190, makecol(250, 250, 0));
			textout(dblbuffer, font, "move left:     left", 240, 200, makecol(250, 250, 0));
			textout(dblbuffer, font, "move right:    right", 240, 210, makecol(250, 250, 0));
			textout(dblbuffer, font, "move down:     down", 240, 220, makecol(250, 250, 0));
			textout(dblbuffer, font, "rotate left:   Z", 240, 230, makecol(250, 250, 0));
			textout(dblbuffer, font, "rotate right:  X", 240, 240, makecol(250, 250, 0));
			textout(dblbuffer, font, "drop:          space", 240, 250, makecol(250, 250, 0));
		}

	
		vsync();
		
		if(m<480 && n<640){
			stretch_blit(dblbuffer, screen, 0, 0, SCREEN_W, SCREEN_H, 0, 0, n, m);
			if(m<480) m+=9;
			if(n<640) n+=12;
		}
		else blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//zmiana bufora
	}

}

//**********************************************************************

int gra::nowa_gra()
{
	//ZMIENNE
	int x=6, y=0;
	int old_seconds=elapsed_seconds;
	int old_seconds1= elapsed_seconds1;
	float	repeatDelay=0;
	double  deltaSeconds=0;
	int punkty1=0;
	int level1=level;
	const int nextlevel=15;
	bool przegrana=false;
	int numer=1;
	bool imie=false;
	bool exit=false;
	int muzyka=0;
	int x1=0, y1=0;
	

	punkty=0;
	linie=nextlevel;
	level=1;
	plansza plansza1;
	plansza1.zerowanie_planszy();
	klocek klocek1;
	klocek1.losuj();
	klocek klocek2;
	klocek2.losuj();
	klocek klocek3;
	set_trans_blender(0, 0, 0, 200);
	install_int_ex(increment_seconds, BPS_TO_TIMER(1));	

	while(!przegrana){

		if(!exit){
		
		if (old_seconds != elapsed_seconds) {
			old_seconds = elapsed_seconds;
			
			klocek1.usun(x, y, plansza1);
			if(klocek1.sprawdz(x,y+1,plansza1)==1){

				play_sample((SAMPLE *)datafile_sound[12].dat,256,127,1000,0);
				klocek1.wstaw(x, y, plansza1);
				punkty+=16;

				int a=plansza1.sprawdz_linia();
				if(a){
					linie-=a;
					if(a==1) punkty+=520;
					else if(a==2) punkty+=1220;
					else if(a==3) punkty+=2020;
					else if(a==4) punkty+=2920;
					else punkty+=9999;

					if(linie<=0){
						level++;
						linie=nextlevel;
					}
					if(level!=level1){
						install_int_ex(increment_seconds, BPS_TO_TIMER(level));
						level1=level;
					}
				}

				for(int i=0; i<2; i++)
					for(int j=1; j<15; j++) if(plansza1.pole[i][j]!=0){
						return 1;
					}
						

				klocek1=klocek2; 
				klocek2.losuj(); 
				x=6; y=-1;
			}
			y++;
		} 
               
		if (key[KEY_ESC])
			{
				exit=true;
			}

		if (key[KEY_A])
			{
				stop_midi();
				play_midi((MIDI *)datafile_sound[muzyka].dat, TRUE);
				muzyka++;
				if(muzyka==11) muzyka=0;
				repeatDelay = 0.2;
			}

		if (repeatDelay <= 0)
		{
			if (key[KEY_RIGHT])
			{
				klocek1.usun(x, y, plansza1); 
				if(klocek1.sprawdz(x+1,y,plansza1)==0) x++;
				repeatDelay = 0.08;
			}
			if (key[KEY_LEFT])
			{
				klocek1.usun(x, y, plansza1); 
				if(klocek1.sprawdz(x-1,y,plansza1)==0) x--;
				repeatDelay = 0.08;
			}
			if (key[KEY_Z])
			{
				play_sample((SAMPLE *)datafile_sound[11].dat,256,127,1000,0);

				klocek1.usun(x,y,plansza1);
				klocek3=klocek1;
				klocek1.obroc_lewo();
				repeatDelay = 0.1;
			
			if(klocek1.sprawdz(x,y,plansza1)){
				if(!klocek1.sprawdz(x-1,y,plansza1)) x--;
				else{
					if(!klocek1.sprawdz(x+1,y,plansza1)) x++;
					else{
						if(!klocek1.sprawdz(x-2,y,plansza1)) x -= 2;
						else{
							if(!klocek1.sprawdz(x+2,y,plansza1)) x += 2;
							else{
								if (!klocek1.sprawdz(x-3,y,plansza1)) x -= 3;
								else{
									if (!klocek1.sprawdz(x+3,y,plansza1)) x += 3;
									else{
										klocek1=klocek3;
										repeatDelay=0;
			}}}}}}}
			
			}
			if (key[KEY_X])
			{
				play_sample((SAMPLE *)datafile_sound[11].dat,256,127,1000,0);

				klocek1.usun(x,y,plansza1);
				klocek3=klocek1;
				klocek1.obroc_prawo();
				repeatDelay = 0.1;
			
			if(klocek1.sprawdz(x,y,plansza1)){
				if(!klocek1.sprawdz(x-1,y,plansza1)) x--;
				else{
					if(!klocek1.sprawdz(x+1,y,plansza1)) x++;
					else{
						if(!klocek1.sprawdz(x-2,y,plansza1)) x -= 2;
						else{
							if(!klocek1.sprawdz(x+2,y,plansza1)) x += 2;
							else{
								if (!klocek1.sprawdz(x-3,y,plansza1)) x -= 3;
								else{
									if (!klocek1.sprawdz(x+3,y,plansza1)) x += 3;
									else{
										klocek1=klocek3;
										repeatDelay=0;
			}}}}}}}

			}
			if (key[KEY_DOWN])
			{
				repeatDelay = 0.04;
				klocek1.usun(x, y, plansza1);
				if(klocek1.sprawdz(x,y+1,plansza1)==0) y++;
				else
				{
					play_sample((SAMPLE *)datafile_sound[12].dat,256,127,1000,0);
					klocek1.wstaw(x, y, plansza1);
					punkty+=16;
					int a=plansza1.sprawdz_linia();
					if(a){
						linie-=a;
						if(a==1) punkty+=520;
						else if(a==2) punkty+=1220;
						else if(a==3) punkty+=2020;
						else if(a==4) punkty+=2920;
						else punkty+=9999;
						if(linie<=0){ level++; linie=nextlevel; }
						if(level!=level1){ install_int_ex(increment_seconds, BPS_TO_TIMER(level)); level1=level;}
						}
				for(int i=0; i<2; i++)
					for(int j=1; j<15; j++) if(plansza1.pole[i][j]!=0){return 1;}
				klocek1=klocek2; klocek2.losuj(); x=6; y=-1;
				}
			}
			if (key[KEY_SPACE])
			{
				repeatDelay = 0.08;
				klocek1.usun(x, y, plansza1);
				while(klocek1.sprawdz(x,y+1,plansza1)==0) y++;

					play_sample((SAMPLE *)datafile_sound[12].dat,256,127,1000,0);
					klocek1.wstaw(x, y, plansza1);
					punkty+=16;
					int a=plansza1.sprawdz_linia();
					if(a){
						linie-=a;
						if(a==1) punkty+=520;
						else if(a==2) punkty+=1220;
						else if(a==3) punkty+=2020;
						else if(a==4) punkty+=2920;
						else punkty+=9999;
						if(linie<=0){ level++; linie=nextlevel; }
						if(level!=level1){ install_int_ex(increment_seconds, BPS_TO_TIMER(level)); level1=level;}
						}
				for(int i=0; i<2; i++)
					for(int j=1; j<15; j++) if(plansza1.pole[i][j]!=0){return 1;}
				klocek1=klocek2; klocek2.losuj(); x=6; y=-1;
			}
		}
		}

		
		if (old_seconds1 != elapsed_seconds1) {
			old_seconds1 = elapsed_seconds1;
			if(repeatDelay>0) repeatDelay -= 0.04;
		}
		
		if(punkty1<punkty) punkty1+=2;

		klocek1.wstaw(x, y, plansza1);
		for(int i=0; i<16; i++) 
			for(int j=0; j<12; j++) blit((BITMAP *)datafile_gfx[6].dat, dblbuffer, 0, 0, i*40, j*40, i*40+40, j*40+40);
        
			
		drawing_mode(DRAW_MODE_COPY_PATTERN, (BITMAP *)datafile_gfx[6].dat,x1, y1);
		rectfill(dblbuffer, 490, 220, 590, 320, -1);
		rectfill(dblbuffer, 30, 20, 310, 440, -1);
		solid_mode();
		
		x1++;
		y1++;
		if(x1>640) x1=0;
		if(y1>480) y1=0;
			
		draw_trans_sprite(dblbuffer, (BITMAP *)datafile_gfx[5].dat, 20, 20);

		plansza1.rysuj_plansze();
		plansza1.zaciemnij(490,220,590,320,15,1,dblbuffer);
		rect(dblbuffer, 490, 220, 590, 320, makecol(0, 0, 0));
		klocek2.wyswietl(500,230);
		
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "XETRIS", 435, 35, makecol(0, 0, 0));
		textout(dblbuffer, (FONT *)datafile_font[0].dat, "XETRIS", 440, 40, makecol(60, 250, 30));
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "LINES LEFT: ", 380, 120, makecol(0, 0, 0));
		textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 541, 121, makecol(0, 0, 0), "%d", linie);
		textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 540, 120, makecol(0, 0, 200), "%d", linie);
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "LEVEL: ", 380, 140, makecol(0, 0, 0));
		textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 541, 141, makecol(0, 0, 0), "%d", level);
		textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 540, 140, makecol(0, 200, 0), "%d", level);
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "SCORE: ", 380, 160, makecol(0, 0, 0));
		textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 541, 161, makecol(0, 0, 0), "%d", punkty1);
		textprintf(dblbuffer, (FONT *)datafile_font[1].dat, 540, 160, makecol(200, 0, 0), "%d", punkty1);
		textout(dblbuffer, (FONT *)datafile_font[1].dat, "NEXT: ", 380, 220, makecol(0, 0, 0));
		textout(dblbuffer, font, "By: Kamil Rudnicki", 415, 430, makecol(90, 90, 90));
		plansza1.zaciemnij(31,20,310,65,15,1,dblbuffer);
		hline(dblbuffer, 31, 65, 310, makecol(0, 0, 200));
		

		if(exit){
			rect(dblbuffer, 100, 100, 540, 380, makecol(0, 0, 0));
			plansza1.zaciemnij(100,100,540,380,120,1,dblbuffer);
			textout(dblbuffer, (FONT *)datafile_font[0].dat, "Are you sure?", 182, 152, makecol(0, 0, 0));
			textout(dblbuffer, (FONT *)datafile_font[0].dat, "Are you sure?", 180, 150, makecol(50, 250, 50));
			if(numer==1)	 {plansza1.zaciemnij(120,250,240,310,120,4,dblbuffer); rect(dblbuffer, 120,250,240,310, makecol(0, 0, 0));}
			else if(numer==2){plansza1.zaciemnij(400,250,500,310,120,4,dblbuffer); rect(dblbuffer, 400,250,500,310, makecol(0, 0, 0));}
			textout(dblbuffer, (FONT *)datafile_font[0].dat, "YES", 150, 260, makecol(250, 250, 250));
			textout(dblbuffer, (FONT *)datafile_font[0].dat, "NO", 430, 260, makecol(250, 250, 250));
			
			if (key[KEY_ENTER])
				{
					if(numer==2) exit=false;
					else if(numer==1){return 0;}
				}
			else if (key[KEY_RIGHT])
				{
					numer++;
					if(numer>2) numer=2;
				}	
			else if (key[KEY_LEFT])
				{
					numer--;
					if(numer<1) numer=1;
				}
		}
		
		vsync();
		blit(dblbuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//zmiana bufora
		
    }
	return 0;
}

//**********************************************************************