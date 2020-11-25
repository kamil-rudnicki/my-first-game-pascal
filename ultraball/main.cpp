#define INITGUID
#define WIN32_LEAN_AND_MEAN   // "odchudza" aplikacjê Windows
#define WND_CLASS_NAME  "OpenGL Window Class"
#include <windows.h>          // standardowball.y plik nag³ówkowball.y Windows 
#include <gl/gl.h>						// standardowball.y plik nag³ówkowball.y OpenGL 
#include <gl/glu.h>		
#include <gl/glaux.h>	
#include "InputSystem.h"
#include "bitmap.h"
#include "font.h"
#include "HiResTimer.h"
#include "plansza.h"
#include "klocek.h"
#include "paletka.h"
#include "fmod.h"
#include "ball.h"

const int   SCREEN_WIDTH    = 800;
const int   SCREEN_HEIGHT   = 600;
const int   SCREEN_BPP      = 32;
const bool  USE_FULLSCREEN  = true; 
const char  *APP_TITLE       = "3D ULTRA BALL";
HDC       g_hdc;		  // globalnball.y kontekst urz¹dzenia
HGLRC     g_hrc;                  // globalnball.y kontekst tworzenia grafiki
BOOL      g_isFullscreen = TRUE;  // prze³¹cza trball.yb pe³noekranowball.y i okienkowball.y
BOOL      g_isActive = TRUE;      // false jeœli okno zwiniête do ikonball.y
HWND      g_hwnd = NULL;          // uchwball.yt okna  
HINSTANCE g_hInstance;            // instancja aplikacji
CInputSystem  g_input;
float     g_mouseX        = 0;
float     g_mouseY        = SCREEN_HEIGHT / 2;
int     g_screenWidth   = SCREEN_WIDTH;
int     g_screenHeight  = SCREEN_HEIGHT;
unsigned int g_listBase = 0;
bool keyPressed[256];			// klocki przball.yciœniêæ klawiszball.y
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL    SetupWindow(const char *title, int width, int height, int bits, bool isFullscreen);
BOOL    KillWindow();
GLvoid  ResizeScene(GLsizei width, GLsizei height);
BOOL    InitializeScene();
BOOL    DisplayScene();
BOOL    Cleanup();
void    ProcessInput();
void    LoadTexture(char *filename, GLuint &texture);


FSOUND_SAMPLE *sound_wall_bounce;						// bounce off wall
FSOUND_SAMPLE *sound_ball_falling;
void InitFMOD(void);

GLuint  g_tloTexture;    //texture
GLuint  g_paletkaTexture;    //texture
GLuint  g_livesTexture;    //texture
GLuint  g_mouseTexture;    //texture

Ball ball;
Paddle paddle;
plansza plansza;
bool start=false;

////// Zmienne oœwietlenia
float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };	// œwiat³o otoczenia
float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	// œwiat³o rozproszone
float lightPosition[] = { 0.0f, 1.0f, 0.0f, 1.0f };	// po³o¿enie Ÿród³a œwiat³a
float matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float matDiff[] = { 1.0f, 1.0f, 1.0f, 1.0f};




BOOL InitializeScene()
{
	glFrontFace(GL_CCW); 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	//sound
	InitFMOD();

	//input
	g_input.Initialize(g_hwnd, g_hInstance, true, IS_USEKEYBOARD | IS_USEMOUSE);

	//tekstury
	glEnable(GL_TEXTURE_2D);
	LoadTexture("gfx/tex1.bmp", g_tloTexture);
	LoadTexture("gfx/tex3.bmp", g_paletkaTexture);
	LoadTexture("gfx/lives.bmp", g_livesTexture);
	LoadTexture("gfx/tex2.bmp", g_mouseTexture);
	
	//czcionka
	listBase = CreateOutlineFont("Arial", 6, 0.1f);  // czcionka Arial o rozmiarze 10 pkt.
 
	//kolor tla
	glClearColor(0.0f, 0.0f, 0.09f, 0.0f);

	// w³¹cza oœwietlenie
	glEnable(GL_LIGHTING);						
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);		// sk³adowa otoczenia
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);		// sk³adowa rozproszona
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);	// po³o¿enie Ÿród³a œwiat³a
	glEnable(GL_LIGHT0);
	
  return TRUE;
} 

void InitFMOD(void)
{
	FMUSIC_MODULE *song;								// Storage for background music
    if (FSOUND_Init(44100, 32, 0))						// Initialize sound board at 44kHz
	{
		song = FMUSIC_LoadSong("mid/5.mid");		// Load our selected track
		FMUSIC_PlaySong(song);							// Start it plaball.ying
		sound_wall_bounce	= FSOUND_Sample_Load(FSOUND_FREE, "mid/3.wav", FSOUND_2D, 0);
		sound_ball_falling  = FSOUND_Sample_Load(FSOUND_FREE, "mid/2.wav", FSOUND_2D, 0);
	}
}
float rot=0;
BOOL DisplayScene()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// opró¿nia bufoball.y ekranu i g³êbi
glLoadIdentity();

//sprite 2D
glPushMatrix();
	glTranslatef(11, 8, -20);
	glColor3f(1,1,1);
	PrintString(listBase, "afd");//punktball.y
	glTranslatef(-12, 0, 0);
	glColor3f(1,0,0);
	PrintString(listBase, "1");//runda
glPopMatrix();

//GRA
glPushMatrix();
	glTranslatef(0, 0, -75.0f);
	glTranslatef(0, -1, 0.0f);
	g_input.Update();
	ProcessInput();


	//glRotatef(50*float(sin(rot+=0.007f)), 0, 0, 1);		// Swing board around a little



	lightPosition[0]=ball.x;
	lightPosition[1]=ball.y;
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);	// po³o¿enie Ÿród³a œwiat³a

	if(start==TRUE)
	{
		//wspolrzedne kulki
		ball.x += (float)ball.xi * ball.speed;
		ball.y += (float)ball.yi * ball.speed;
	}else
	{
		ball.x=paddle.x+paddle.width1;
		ball.y=paddle.y+paddle.height+ball.radius;

	}

	//ograniczenia planszball.y
	if(ball.x<=plansza.x+ball.radius || ball.x>=-plansza.x-ball.radius){ ball.xi=-ball.xi; FSOUND_PlaySound(FSOUND_FREE, sound_wall_bounce);}
	if(ball.y>=plansza.y-ball.radius){ ball.yi=-ball.yi; FSOUND_PlaySound(FSOUND_FREE, sound_wall_bounce);}
	if(ball.y<=-plansza.y+ball.radius){start=false; paddle.x=0-paddle.width1; ball.xi=0;}
	
	
	
	if(g_mouseX<0 && paddle.x-paddle.speed>=plansza.x){
		paddle.oldx=paddle.x;
		paddle.x-=paddle.speed;
		g_mouseX=0;
	}
	else if(g_mouseX>0 && paddle.x+paddle.width+paddle.speed<=-plansza.x){
		paddle.oldx=paddle.x;
		paddle.x+=paddle.speed;
		g_mouseX=0;
	}

	paddle.Check_Ball_Collision(&ball);
	
	for(int i=0; i<plansza.ilosc_klockow; i++)
	{
		plansza.klocki[i].zderzenie_klocka(&ball);
		plansza.klocki[i].rysuj_klocek(plansza.klocki[i].x+(plansza.klocki[i].width/2), plansza.klocki[i].y-(plansza.klocki[i].height/2));	
	}

	ball.Draw();
	paddle.Draw();
	plansza.rysuj_plansze();

glPopMatrix();	
glFlush();
return TRUE;
} 

  
BOOL Cleanup()
{
	g_input.Shutdown();
    ClearFont(listBase);
	
	glDeleteTextures(1, &g_mouseTexture);
	glDeleteTextures(1, &g_tloTexture);
	glDeleteTextures(1, &g_paletkaTexture);
	glDeleteTextures(1, &g_livesTexture);
	
  return TRUE;
} 

/*****************************************************************************
 ResizeScene()

 Konfiguruje perspektball.ywê w oparciu o rozmiarball.y okna.
*****************************************************************************/
GLvoid ResizeScene(GLsizei width, GLsizei height)
{
  // zapobiega dzieleniu przez zero
  if (height==0)  
  {
    height=1;
  }

	glViewport(0, 0, width, height);		// nadaje nowe wball.ymairball.y oknu OpenGL
			glMatrixMode(GL_PROJECTION);			// wball.ybiera macierz rzutowania
			glLoadIdentity();						// resetuje macierz rzutowania

			// wball.yznacza proporcje obrazu
			gluPerspective(54.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

			glMatrixMode(GL_MODELVIEW);				// wball.ybiera macierz modelowania
			glLoadIdentity();	
} // ResizeScene()
/*****************************************************************************
 WinMain()

 Punkt, w którball.ym rozpoczball.yna siê wball.ykonball.ywanie aplikacji Windows. 
*****************************************************************************/
int WINAPI WinMain(HINSTANCE g_hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  MSG   msg;       // komunikat
  BOOL  isDone;    // znacznik zakoñczenia pracball.y aplikacji

  // tworzball.y okno
  if (SetupWindow(APP_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, USE_FULLSCREEN))
    isDone = FALSE;
  else
    isDone = TRUE;  	

  	CHiResTimer timer;
	timer.Init();
	int nFrames = 0;

  // pêtla przetwarzania komunikatów
  while (!isDone)
  {
    if(PeekMessage(&msg, g_hwnd, NULL, NULL, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)   // czball.y odebrano komunikat zakoñczenia pracball.y aplikacji?
      {
        isDone = TRUE;              // ustawia znacznik koñca pracball.y
      }
      else
      {
			if (keyPressed[VK_ESCAPE])
				isDone = true;
			else
			{					
				if (keyPressed[VK_UP]) plansza.depth+=5;
				
				TranslateMessage(&msg);		// t³umaczball.y komunikat i wball.ysball.y³a do sball.ystemu
				DispatchMessage(&msg);
			}


      }
    }

    // nie aktualizuje scenball.y, gdball.y okno jest zwiniête
    if (g_isActive)
    {
      // aktualizuje scenê w ka¿dball.ym przebiegu pêtli
      DisplayScene();
      // prze³¹cza buforball.y
      SwapBuffers(g_hdc);

	  	nFrames++;
		if(nFrames > 100)
		{
			char cOutBuffer[32];
			// wball.yœwietla prêdkoœæ tworzenia klatek
			sprintf(cOutBuffer,"%0.1f",timer.GetFPS(100));
			SetWindowText(g_hwnd, cOutBuffer);
			nFrames = 0;
		}
    }
  }

	Cleanup();

  KillWindow();

  return msg.wParam;
} // WinMain()


/*****************************************************************************
 WndProc()

 procedura okienkowa
*****************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message)
  {
  case WM_ACTIVATE:  // okno jest zwijane do ikonball.y b¹dŸ rozwijane
    {
      if (!HIWORD(wParam))
      {
        // okno zosta³o rozwiniête
        g_isActive = TRUE;
        g_input.AcquireAll();
      }
      else
      {
        // okno zosta³o zwiniête do ikonball.y
        g_isActive=FALSE;
        g_input.UnacquireAll();
      }

      return 0;
    }

  case WM_SYSCOMMAND:  // wball.ygaszacz ekranu b¹dŸ trball.yb oszczêdnball.y monitora
    {
      switch (wParam)
			{
				case SC_SCREENSAVE:     // uruchamianball.y jest wball.ygaszacz ekranu 
				case SC_MONITORPOWER:   // monitor prze³¹cza siê w trball.yb oszczêdnball.y
          // zwrócenie wartoœci 0 zapobiega obu akcjom
        return 0;
      default:
        break;
      }
    } break;

  case WM_CLOSE:    // okno jest zamball.ykane
    {
      // wstawia komunikat WM_QUIT do kolejki
      PostQuitMessage(0);

      return 0;
    }

  case WM_SIZE:
    {
      // aktualizuje szerokoœæ i wball.ysokoœæ scenball.y
      ResizeScene(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }

  case WM_KEYDOWN:					// u¿ball.ytkownik nacisn¹³ klawisz?
	{
		keyPressed[wParam] = true;
		return 0;
		break;
	}

  case WM_KEYUP:
	{
		keyPressed[wParam] = false;
		return 0;
		break;
	}

  default:
    break;
  }

  return (DefWindowProc(hwnd, message, wParam, lParam));
} // WndProc()


/*****************************************************************************
 SetupWindow()

 Tworzball.y okno, kontekst urz¹dzenia oraz kontekst tworzenia grafiki.
*****************************************************************************/
BOOL SetupWindow(const char *title, int width, int height, int bits, bool isFullscreen)
{
  // ustawia globalnball.y znacznik
  g_isFullscreen = isFullscreen;

  // pobiera uchwball.yt instancji aplikacji
  g_hInstance = GetModuleHandle(NULL);

  WNDCLASSEX  wc;    // klasa okna

  // wball.ype³nia strukturê opisuj¹c¹ klasê okna
  wc.cbSize         = sizeof(WNDCLASSEX);
  wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc    = WndProc;
  wc.cbClsExtra     = 0;
  wc.cbWndExtra     = 0;
  wc.hInstance      = g_hInstance;
  wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);	// domball.yœlna ikona
  wc.hIconSm        = LoadIcon(NULL, IDI_WINLOGO);		  // logo windows 
  wc.hCursor        = LoadCursor(NULL, IDC_ARROW);		  // strza³ka (kursor domball.yœlnball.y)
  wc.hbrBackground  = NULL; //(HBRUSH) GetStockObject(BLACK_BRUSH);   // t³o w kolorze czarnball.ym
  wc.lpszMenuName   = NULL;     // bez menu
  wc.lpszClassName  = WND_CLASS_NAME;
  
  // rejestruje klasê okna
  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL,"Nie mo¿na zarejestrowaæ klasy okna", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;       
  }

  // konfiguruje trball.yb pe³noekranowball.y
  if (g_isFullscreen)
  {
    // wball.ype³nia strukturê opisuj¹c¹ trball.yb wball.yœwietlania
    DEVMODE screenSettings;
    memset(&screenSettings,0,sizeof(screenSettings));

    screenSettings.dmSize       = sizeof(screenSettings);
    screenSettings.dmPelsWidth  = width;			// szerokoœæ ekranu
    screenSettings.dmPelsHeight = height;			// wball.ysokoœæ ekranu
    screenSettings.dmBitsPerPel = bits;				// bitów na piksel
    screenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // próbuje prze³aczball.yæ kartê na zdefiniowanball.y wball.y¿ej trball.yb graficznball.y
    if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      // jeœli prze³¹czenie siê nie powiod³o, to pozwala wball.ybraæ trball.yb okienkowball.y
      if (MessageBox(NULL, "Prze³¹czenie do wybranego trybu graficznego nie jest mo¿liwe\n"
                           "Czy przejœæ do tryby okinkowego?",
                           "Programowanie gier w OpenGL",
                           MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
      {
        g_isFullscreen = FALSE;
      }
      else
      {
        return FALSE;
      }
    }
  }

  DWORD dwExStyle;
  DWORD dwStyle;

  // konfiguruje stball.yl okna
	if (g_isFullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;	// okno bez ramki i paska tball.ytu³u
		ShowCursor(FALSE);            // ukrball.ywa kursor
  }
  else
  {
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }

  RECT  windowRect;
  windowRect.left = 0;
  windowRect.right = (LONG) width;
  windowRect.top = 0;
  windowRect.bottom = (LONG) height;

  AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

  // tworzball.y okno
  g_hwnd = CreateWindowEx(dwExStyle,          // stball.yl rozszerzonball.y
                          WND_CLASS_NAME,     // nazwa klasball.y
                          title,              // nazwa aplikacji
                          dwStyle |           // stball.yl okna
                          WS_CLIPCHILDREN |   // wball.ymagane przez Opengl
                          WS_CLIPSIBLINGS,    
                          0, 0,               // wspó³rzêdne x,ball.y coordinate
                          windowRect.right - windowRect.left, // szerokoœæ
                          windowRect.bottom - windowRect.top, // wball.ysokoœæ
                          NULL,               // uchwball.yt okna nadrzêdnego 
                          NULL,               // uchwball.yt menu
                          g_hInstance,        // instancja aplikacji
                          NULL);              // bez dodatkowball.ych parametrów

  // sprawdza poprawnoœæ uchwball.ytu okna
  if (!g_hwnd)
  {
    MessageBox(NULL, "Nie mo¿na utworzyæ okna", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

  // pobiera kontekst urz¹dzenia
  if (!(g_hdc = GetDC(g_hwnd)))
  {
    MessageBox(NULL,"Nie mo¿na utworzyæ kontekstu urz¹dzenia", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // konfiguruje format pikseli
  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),	// rozmiar strukturball.y
    1,                              // domball.yœlna wersja
    PFD_DRAW_TO_WINDOW |            // okno grafiki OpenGL
    PFD_SUPPORT_OPENGL |            
    PFD_DOUBLEBUFFER,               // podwójne buforowanie
    PFD_TYPE_RGBA,                  // trball.yb kolorów RGBA 
    bits,                           // 32-bitowball.y opis kolorów
    0, 0, 0, 0, 0, 0,               // ignoruje bitball.y koloru, bez paletball.y
    0,                              // bez bufora alfa
    0,                              // ignoruje bit przesuniêcia
    0,                              // bez bufora akumulacji
    0, 0, 0, 0,                     // ignoruje bitball.y akumulacji
    16,                             // 16-bitowball.y bufor z
    0,                              // bez bufora powielania
    0,                              // bez bufora pomocniczego
    PFD_MAIN_PLANE,                 // g³ównball.y plan rball.ysowania
    0,                              // zarezerwowane
    0, 0, 0 };                      // ignoruje maski warst
      
	GLuint  pixelFormat;

	// wball.ybiera najodpowiedniejszball.y format pikseli
  if (!(pixelFormat = ChoosePixelFormat(g_hdc, &pfd)))
  {
    MessageBox(NULL, "Nie mo¿na dopasowaæ formatu pikseli", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // wball.ybiera format pikseli dla kontekstu urz¹dzenia
  if(!SetPixelFormat(g_hdc, pixelFormat,&pfd))
  {
    MessageBox(NULL, "Nie mo¿na wybraæ formatu pikseli", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // tworzball.y kontekst tworzenia grafiki OpenGL
  if (!(g_hrc = wglCreateContext(g_hdc)))
  {
    MessageBox(NULL, "Nie mo¿na utworzyæ kontekstu grafiki OpenGL", "B³¹d",MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // aktball.ywuje kontekst tworzenia grafiki
  if(!wglMakeCurrent(g_hdc, g_hrc))
  {
    MessageBox(NULL,"Nie mo¿na aktywowaæ kontekstu grafiki OpenGL", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  // aktball.ywuje okno
  ShowWindow(g_hwnd, SW_SHOW);
  SetForegroundWindow(g_hwnd);
  SetFocus(g_hwnd);

  // zmienia rozmiarball.y scenball.y
  ResizeScene(width, height);

  // wball.ykonuje jednorazow¹ inicjacjê
  if (!InitializeScene())
  {
    MessageBox(NULL, "Inicjacja nie powiod³a siê", "B³¹d", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }

  return TRUE;
} // SetupWindow()


/*****************************************************************************
 KillWindow()

 Przball.ywraca wball.yjœciowball.y trball.yb wball.yœwietlania. Usuwa okno, kontekst urz¹dzenia 
 i kontekst tworzenia grafiki.
*****************************************************************************/
BOOL KillWindow()
{
  //rzball.ywraca orball.yginalnball.y trball.yb wball.yœwietlania, jeœli prze³¹czball.y³ w trball.yb pe³noekranowball.y
  if (g_isFullscreen)
  {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);
  }

  // zwalnia kontekst tworzenia grafiki
  if (g_hrc)
  {
    // zwalnia kontekst
    if (!wglMakeCurrent(NULL,NULL))
    {
      MessageBox(NULL, "Nie mo¿na zwolniæ kontekstu grafiki", "B³¹d", MB_OK | MB_ICONINFORMATION);
    }

    // usuwa kontekst
    if (!wglDeleteContext(g_hrc))
    {
      MessageBox(NULL, "Nie mo¿na usun¹æ kontekstu grafiki", "B³¹d", MB_OK | MB_ICONINFORMATION);
    }

    g_hrc = NULL;
  }

  // zwalnia kontekst urz¹dzenia
  if (g_hdc && !ReleaseDC(g_hwnd, g_hdc))
  {
    MessageBox(NULL, "Nie mo¿na zwolniæ kontekstu urz¹dzenia", "B³¹d", MB_OK | MB_ICONINFORMATION);
    g_hdc = NULL;
  }

  // usuwa okno
  if (g_hwnd && !DestroyWindow(g_hwnd))
  {
    MessageBox(NULL, "Nie mo¿na usun¹æ okna", "B³¹d", MB_OK | MB_ICONINFORMATION);
    g_hwnd = NULL;
  }

  // wball.yrejestrowuje klasê okna
  if (!UnregisterClass(WND_CLASS_NAME, g_hInstance))
  {
    MessageBox(NULL, "Nie mo¿na wyrejestrowaæ klas okna", "B³¹d", MB_OK | MB_ICONINFORMATION);
    g_hInstance = NULL;
  }

  return TRUE;
} // KillWindow()


void ProcessInput()
{
  int dx, dy;
  g_input.GetMouseMovement(dx, dy);
  g_mouseX += dx;
  g_mouseY -= dy;

  if(g_input.ButtonDown(0)) start=TRUE;
  if(g_input.ButtonDown(1)) plansza.depth-=2;
} 








