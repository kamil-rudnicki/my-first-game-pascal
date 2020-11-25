//////////////////////////////
// LEDCOM	www.caru.w.pl	//
// by: Kamil Rudnicki		//
// klasa portow COM			//
//////////////////////////////

#include "com.h"

//--------------------------------------------------------------

com1::com1()
{
	istnieje=false;
	swieci=false;
}

//--------------------------------------------------------------

com1::~com1()
{
	if(istnieje) CloseHandle(hNumPort);
}

//--------------------------------------------------------------

bool com1::zaswiec()
{
	if(swieci==false && istnieje) EscapeCommFunction(hNumPort, SETDTR);
	swieci=true;
	return true;
}

//--------------------------------------------------------------

bool com1::zgas()
{
	if(swieci==true && istnieje) EscapeCommFunction(hNumPort, CLRDTR);
	swieci=false;
	return true;
}

//--------------------------------------------------------------

void com1::ini()
{
	if(!istnieje)
	{
		//inicjalizacja portu com1
		DCB dcb;
		hNumPort = CreateFile("COM1", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		dcb.DCBlength  = sizeof(dcb);
		dcb.BaudRate   = CBR_9600;
		dcb.fParity       = FALSE;
		dcb.Parity        = NOPARITY;
		dcb.StopBits     = ONESTOPBIT;
		dcb.ByteSize     = 8;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		dcb.fOutxCtsFlow     = FALSE;
		dcb.fOutxDsrFlow     = FALSE;
		dcb.fDsrSensitivity   = FALSE;
		dcb.fAbortOnError    = FALSE;
		dcb.fOutX = FALSE;
		dcb.fInX = FALSE;
		dcb.fErrorChar = FALSE;
		dcb.fNull = FALSE;
		SetCommState(hNumPort, &dcb);
		EscapeCommFunction(hNumPort, CLRDTR);
	}
	istnieje=true;
	swieci=false;
}

//--------------------------------------------------------------

void com1::del()
{
	if(istnieje) CloseHandle(hNumPort);
	istnieje=false;
}


//----COM2-----------------COM2----------------------------------



com2::com2()
{
	istnieje=false;
	swieci=false;
}

//--------------------------------------------------------------

com2::~com2()
{
	if(istnieje) CloseHandle(hNumPort);
}

//--------------------------------------------------------------

bool com2::zaswiec()
{
	if(swieci==false && istnieje) EscapeCommFunction(hNumPort, SETDTR);
	swieci=true;
	return true;
}

//--------------------------------------------------------------

bool com2::zgas()
{
	if(swieci==true && istnieje) EscapeCommFunction(hNumPort, CLRDTR);
	swieci=false;
	return true;
}

//--------------------------------------------------------------

void com2::ini()
{
	if(!istnieje)
	{
		//inicjalizacja portu com2
		DCB dcb;
		hNumPort = CreateFile("COM2", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		dcb.DCBlength  = sizeof(dcb);
		dcb.BaudRate   = CBR_9600;
		dcb.fParity       = FALSE;
		dcb.Parity        = NOPARITY;
		dcb.StopBits     = ONESTOPBIT;
		dcb.ByteSize     = 8;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		dcb.fOutxCtsFlow     = FALSE;
		dcb.fOutxDsrFlow     = FALSE;
		dcb.fDsrSensitivity   = FALSE;
		dcb.fAbortOnError    = FALSE;
		dcb.fOutX = FALSE;
		dcb.fInX = FALSE;
		dcb.fErrorChar = FALSE;
		dcb.fNull = FALSE;
		SetCommState(hNumPort, &dcb);
		EscapeCommFunction(hNumPort, CLRDTR);
	}
	istnieje=true;
	swieci=false;
}

//--------------------------------------------------------------

void com2::del()
{
	if(istnieje) CloseHandle(hNumPort);
	istnieje=false;
}