/****************************************************************************
 InputSystem.h
 
 Deklaracja klasy DirectInput obudowuj�cej system wej�cia.
  
 Autor    :   Dave Astle
 Data     :   3/5/2001

 Opracowano dla potrzeb ksi��ki "Programowanie gier w OpenGL"
*****************************************************************************/
#ifndef __INPUT_SYSTEM_INCLUDED__
#define __INPUT_SYSTEM_INCLUDED__

/********************************* Pliki nag��wkowe *********************************/
#include <dinput.h>


/********************************* Sta�e ********************************/
#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2


class CKeyboard
{
public:
  CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
  ~CKeyboard();

  bool  KeyDown(int key) { return (m_keys[key] & 0x80) ? true : false; }
  bool  KeyUp(int key) { return (m_keys[key] & 0x80) ? false : true; }

  bool  Update();

  void  Clear() { ZeroMemory(m_keys, 256 * sizeof(char)); }

  bool  Acquire();
  bool  Unacquire();

private:
  LPDIRECTINPUTDEVICE8  m_pDIDev;
  int    m_keys[256];
};


class CMouse
{
public:
  CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive = true);
  ~CMouse();

  bool  ButtonDown(int button) { return (m_state.rgbButtons[button] & 0x80) ? true : false; }
  bool  ButtonUp(int button) { return (m_state.rgbButtons[button] & 0x80) ? false : true; }
  int   GetWheelMovement() { return m_state.lZ; }
  void  GetMovement(int &dx, int &dy) { dx = m_state.lX; dy = m_state.lY; }

  bool  Update();

  bool  Acquire();
  bool  Unacquire();

private:
  LPDIRECTINPUTDEVICE8  m_pDIDev;
  DIMOUSESTATE          m_state;
};


class CInputSystem
{
public:
  bool  Initialize(HWND hwnd, HINSTANCE appInstance, bool isExclusive, DWORD flags = 0);
  bool  Shutdown();

  void  AcquireAll();
  void  UnacquireAll();

  CKeyboard  *GetKeyboard() { return m_pKeyboard; }
  CMouse     *GetMouse()    { return m_pMouse; }

  bool  Update();

  bool  KeyDown(int key) { return (m_pKeyboard && m_pKeyboard->KeyDown(key)); }
  bool  KeyUp(int key) { return (m_pKeyboard && m_pKeyboard->KeyUp(key)); }

  bool  ButtonDown(int button) { return (m_pMouse && m_pMouse->ButtonDown(button)); }
  bool  ButtonUp(int button) { return (m_pMouse && m_pMouse->ButtonUp(button)); }
  void  GetMouseMovement(int &dx, int &dy) { if (m_pMouse) m_pMouse->GetMovement(dx, dy); }
  int   GetMouseWheelMovement() { return (m_pMouse) ? m_pMouse->GetWheelMovement() : 0; }

private:
  CKeyboard  *m_pKeyboard;
  CMouse     *m_pMouse;
  
  LPDIRECTINPUT8 m_pDI;
};


#endif //__INPUT_SYSTEM_INCLUDED__