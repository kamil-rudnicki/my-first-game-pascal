#ifndef FONT
#define FONT


extern HDC g_hdc;
unsigned int listBase;				// pierwsza lista wyœwietlania
GLYPHMETRICSFLOAT gmf[256];			// informacje o po³o¿eniu i orientacji znaków


// CreateOutlineFont()
// opis: tworzy czcionkê obrysow¹ za pomoc¹ funkcji CreateFont()
unsigned int CreateOutlineFont(char *fontName, int fontSize, float depth)
{
	HFONT hFont;         // uchwyt czcionki systemu Windows
	unsigned int base;

	base = glGenLists(256);      // listy wyœwietlania dla 256 znaków

	if (stricmp(fontName, "symbol") == 0)
	{
	     hFont = CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, SYMBOL_CHARSET, 
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
							FF_DONTCARE | DEFAULT_PITCH, fontName);
	}
	else
	{
		 hFont = CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
							FF_DONTCARE | DEFAULT_PITCH, fontName);
	}

	if (!hFont)
		return 0;

	SelectObject(g_hdc, hFont);
	wglUseFontOutlines(g_hdc, 0, 255, base, 0.0f, depth, WGL_FONT_POLYGONS, gmf);

	return base;
}

void ClearFont(unsigned int base)
{
	glDeleteLists(base, 256);
}

void PrintString(unsigned int base, char *str)
{
	float length = 0;

	if ((str == NULL))
		return;

	// centruje tekst
	for (unsigned int loop=0;loop<(strlen(str));loop++)	// okresla d³ugoœæ tekstu
	{
		length+=gmf[str[loop]].gmfCellIncX;		        // sumuje szerokoœci znaków
	}
	glTranslatef(-length/2,0.0f,0.0f);                  // przesuwa uk³ad wspó³rzêdnych o po³owê uzyskanej sumy

	// rysuje tekst
	glPushAttrib(GL_LIST_BIT);
		glListBase(base);
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	glPopAttrib();
}

#endif