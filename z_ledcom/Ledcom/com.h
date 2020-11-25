//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// klasa portow COM			//
//////////////////////////////

#ifndef COM_H
#define COM_H

#include <windows.h>

class com1
{
public:
	com1();
	~com1();

	HANDLE hNumPort;
	bool swieci;
	bool istnieje;

	bool zaswiec();
	bool zgas();
	void ini();
	void del();
};

class com2
{
public:
	com2();
	~com2();

	HANDLE hNumPort;
	bool swieci;
	bool istnieje;

	bool zaswiec();
	bool zgas();
	void ini();
	void del();
};

#endif