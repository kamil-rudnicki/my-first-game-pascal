/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#ifndef CLANGUAGE23
#define CLANGUAGE23

#include "wx/wx.h"
#include "wx/config.h"

class CLanguage
{
public:
	CLanguage(wxLocale &w);
	~CLanguage();

	bool ChooseLang(int n=-1);
	void Startup();

private:

	wxLocale &m_locale;
	wxConfig *m_pconfig;

};


#endif