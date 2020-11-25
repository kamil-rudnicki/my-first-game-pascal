#ifndef FONT
#define FONT


extern HDC g_hdc;
unsigned int listBase;				// pierwsza lista wy�wietlania
GLYPHMETRICSFLOAT gmf[256];			// informacje o po�o�eniu i orientacji znak�w


// CreateOutlineFont()
// opis: tworzy czcionk� obrysow� za pomoc� funkcji CreateFont()
unsigned int CreateOutlineFont(char *fontName, int fontSize, float depth)
{
	HFONT hFont;         // uchwyt czcionki systemu Windows
	unsigned int base;

	base = glGenLists(256);      // listy wy�wietlania dla 256 znak�w

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
	for (unsigned int loop=0;loop<(strlen(str));loop++)	// okresla d�ugo�� tekstu
	{
		length+=gmf[str[loop]].gmfCellIncX;		        // sumuje szeroko�ci znak�w
	}
	glTranslatef(-length/2,0.0f,0.0f);                  // przesuwa uk�ad wsp�rz�dnych o po�ow� uzyskanej sumy

	// rysuje tekst
	glPushAttrib(GL_LIST_BIT);
		glListBase(base);
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	glPopAttrib();
}

#endif