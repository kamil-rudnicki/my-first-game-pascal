#include "naglowki.h"

BITMAP *dblbuffer;//drugi bufor
BITMAP *buffer3;//drugi bufor

int elapsed_seconds=0;
int elapsed_seconds1=0;

DATAFILE *datafile_sound;
DATAFILE *datafile_gfx;
DATAFILE *datafile_font;

void increment_seconds()
{
    elapsed_seconds++;
}
END_OF_FUNCTION(increment_seconds);
void increment_seconds1()
{
    elapsed_seconds1++;
}
END_OF_FUNCTION(increment_seconds1);
 
int main(void)
{
	//INICJACJA
    allegro_init();
    install_keyboard();
	install_timer();  
	set_color_depth(16);	
	srand((unsigned)time(NULL));
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	text_mode(-1);
	set_volume(255, 150);

	datafile_font = load_datafile("data/font.dat");
	if (!datafile_font) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error loading: font.dat");
      return 1;}
	datafile_gfx = load_datafile("data/gfx.dat");
	if (!datafile_gfx) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error loading: gfx.dat");
      return 1;}
	datafile_sound = load_datafile("data/sound.dat");
	if (!datafile_sound) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error loading: sound.dat");
      return 1;}

	play_midi((MIDI *)datafile_sound[rand()%11].dat, TRUE);

	//USTAWIANIE
	//if (set_gfx_mode(GFX_DIRECTX_WIN, 640, 480, 0, 0) < 0) {//okno	
	if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0) {//pe³ny ekran
	printf("%s\n", allegro_error);
	exit(1);
    }

	dblbuffer = create_bitmap(SCREEN_W, SCREEN_H);
	buffer3 = create_bitmap(SCREEN_W, SCREEN_H);
    clear(dblbuffer);
	clear(buffer3);
	clear(screen);

	LOCK_VARIABLE(elapsed_seconds);
    LOCK_FUNCTION(increment_seconds);
    install_int_ex(increment_seconds, BPS_TO_TIMER(1));
	LOCK_VARIABLE(elapsed_seconds1);
    LOCK_FUNCTION(increment_seconds1);
    install_int_ex(increment_seconds1, BPS_TO_TIMER(10));	

		gra The_game;
		The_game.menu();

    destroy_bitmap(dblbuffer);
	destroy_bitmap(buffer3);
	unload_datafile(datafile_gfx);
	unload_datafile(datafile_sound);
	unload_datafile(datafile_font);
	return 0;
}
END_OF_MAIN();







