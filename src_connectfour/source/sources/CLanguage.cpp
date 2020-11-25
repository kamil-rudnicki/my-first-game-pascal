/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CLanguage.h"

//***************************************************************************

CLanguage::CLanguage(wxLocale &w)
	: m_locale(w)
{

	m_pconfig = new wxConfig("Connect_four");
	Startup();
}

//***************************************************************************

CLanguage::~CLanguage()
{
	delete m_pconfig;
}

//***************************************************************************

bool CLanguage::ChooseLang(int n)
{
	long lng = -1;

	static const wxLanguage langIds[] =
    {
        wxLANGUAGE_ENGLISH,
        wxLANGUAGE_POLISH
    };

	const wxString langNames[] =
    {
		_T("English"),
		_T("Polski")
    };

	wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds), LangArraysMismatch );

	if(n==-1)
	{
		lng = wxGetSingleChoiceIndex
				  (
					_("Please choose your language:"),
					_("Language"),
					WXSIZEOF(langNames),
					langNames
				  );
	}
	else
	{
		lng = n;
	}

	bool result=false;
		
	if ( lng != -1 ){
		result=m_locale.Init(langIds[lng]);
		m_pconfig->Write(wxT("lang"), lng);
	}
	else
		result=m_locale.Init(wxLANGUAGE_ENGLISH);


	wxLocale::AddCatalogLookupPathPrefix(wxT(".\\Lang\\"));
	m_locale.AddCatalog(wxT("lang"));

	return result;
}

//***************************************************************************

void CLanguage::Startup()
{
	if(m_pconfig->Exists(wxT("lang"))){
		ChooseLang(m_pconfig->Read(wxT("lang"), -1));
	}else
		ChooseLang();
}

//***************************************************************************