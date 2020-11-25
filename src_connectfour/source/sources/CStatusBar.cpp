/*
	Connect four 1.0
	--------------------------
	Author: Kamil Rudnicki
	Date: 2006.02.10
	License: GPL

	kamil.rudnicki@gmail.com
	http://www.widget.czest.pl
*/

#include "CStatusBar.h"

#pragma warning(disable : 4355)

BEGIN_EVENT_TABLE(CStatusBar, wxStatusBar)
    EVT_TIMER(wxID_ANY, CStatusBar::OnTimer)
END_EVENT_TABLE()

//***************************************************************************

CStatusBar::CStatusBar(wxWindow *parent)
           : wxStatusBar(parent, wxID_ANY)
             , m_timer(this), m_time(0,0,0,0)
{
	wxImage::AddHandler(new wxGIFHandler);
	m_img_green.LoadFile("graphics/green.gif");
	if(m_img_green.Ok()){
		m_img_green.ConvertAlphaToMask();
		m_img_green.InitAlpha();
		m_img_green.Rescale(16,16);
	}
	m_img_red.LoadFile("graphics/red.gif");
	if(m_img_red.Ok()){
		m_img_red.ConvertAlphaToMask();
		m_img_red.InitAlpha();
		m_img_red.Rescale(16,16);
	}

	m_timer.Start(1000);

    static const int widths[3] = { -1, 35 ,80 };

    SetFieldsCount(3);
    SetStatusWidths(3, widths);

	wxRect rect;
	GetFieldRect(Field_Bitmap, rect);
	m_statbmp = new wxStaticBitmap( this, wxID_ANY, wxBitmap(m_img_green), wxPoint(rect.GetX(), rect.GetY()+2)); 
	
}

//***************************************************************************

CStatusBar::~CStatusBar()
{
    if(m_timer.IsRunning())
        m_timer.Stop();
}

//***************************************************************************

void CStatusBar::ResetClock()
{
	m_time.ResetTime();
}

//***************************************************************************

void CStatusBar::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	SetStatusText(m_time.FormatTime(), Field_Clock);
	m_time+=wxTimeSpan(0,0,1,0);
}

//***************************************************************************

void CStatusBar::SetGreen()
{
	m_statbmp->SetBitmap(wxBitmap(m_img_green));
	m_statbmp->Update();
}

//***************************************************************************

void CStatusBar::SetRed()
{
	m_statbmp->SetBitmap(wxBitmap(m_img_red));
	m_statbmp->Update();
}

//***************************************************************************
