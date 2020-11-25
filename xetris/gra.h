#ifndef	H_GRA
#define H_GRA

class gra{
public:
	int nowa_gra();
	void menu();
	void credits();
	void HiScore();
	int write_name(int p);

	int linie;
	int punkty;
	int level;
};

#endif