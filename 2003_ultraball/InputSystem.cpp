/****************************************************************************
 InputSystem.cpp
 
 Implementacja klasy DirectInput obudowuj¹cej system wejœcia.
  
 Autor    :   Dave Astle
 Data     :   3/5/2001

 Opracowano dla potrzeb ksi¹¿ki "Programowanie gier w OpenGL"
*****************************************************************************/
#include "InputSystem.h"


/*****************************************************************************
 CKeyboard::Constructor

 Inicjuje urz¹dzenie DirectInput
*****************************************************************************/
CKeyboard::CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd)
{
  if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
  {
    // obs³uga b³êdów
  }

  if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
  {
    // obs³uga b³êdów
  }

  if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
  {
    // obs³uga b³êdów
  }

  if (FAILED(m_pDIDev->Acquire()))
  {
    // obs³uga b³êdów
  }

  Clear();
} // CKeyboard::Constructor


/*****************************************************************************
 CKeyboard::Destructor

 Zwalnia urz¹dzenie DirectInput
*****************************************************************************/
CKeyboard::~CKeyboard()
{
  if (m_pDIDev)
  {
    m_pDIDev->Unacquire();
    m_pDIDev->Release();
  }
} // CKeyboard::Destructor


/*****************************************************************************
 CKeyboard::Update()

 Odpytuje klawiaturê i przechowuje informacjê o jej stanie.
*****************************************************************************/
bool CKeyboard::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
  {
    if (FAILED(m_pDIDev->Acquire()))
    {
      return false;
    }
    if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
    {
      return false;
    }
  }
  return true;
} // CKeyboard::Update()


/*****************************************************************************
 CKeyboard::Acquire()

 Zajmuje klawiaturê.
*****************************************************************************/
bool CKeyboard::Acquire()
{
  Clear();
  return (!FAILED(m_pDIDev->Acquire()));
} // CKeyboard::Acquire()


/*****************************************************************************
 CKeyboard::Unacquire()

 Zwalnia klawiaturê.
*****************************************************************************/
bool CKeyboard::Unacquire()
{
  Clear();
  return (!FAILED(m_pDIDev->Unacquire()));
} // CKeyboard::Unacquire()



/*****************************************************************************
 CMouse::Constructor

 Inicjuje urz¹dzenie DirectInput.
*****************************************************************************/
CMouse::CMouse(LPDIRECTINPUT8 pDI, HWND hwnd, bool isExclusive)
{
  if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
  {
    // obs³uga b³êdów
  }

  if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
  {
    // obs³uga b³êdów
  }

  DWORD flags;
  if (isExclusive)
    flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
  else
    flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;


  if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, flags)))
  {
    // obs³uga b³êdów
  }

  if (FAILED(m_pDIDev->Acquire()))
  {
    // obs³uga b³êdów
  }

  if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
  {
    // obs³uga b³êdów
  }
} // CMouse::Constructor


/*****************************************************************************
 CMouse::Destructor

 Zwalnia urz¹dzenie DirectInput
*****************************************************************************/
CMouse::~CMouse()
{
  if (m_pDIDev)
  {
    m_pDIDev->Unacquire();
    m_pDIDev->Release();
  }
} // CMouse::Destructor


/*****************************************************************************
 CMouse::Update()

 Odpytuje mysz i przechowuje informacje o jej stanie.
*****************************************************************************/
bool CMouse::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
  {
    if (FAILED(m_pDIDev->Acquire()))
    {
      return false;
    }
    if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
    {
      return false;
    }
  }

  return true;
} // CMouse::Update()


/*****************************************************************************
 CMouse::Acquire()

 Zajmuje mysz.
*****************************************************************************/
bool CMouse::Acquire()
{
  return (!FAILED(m_pDIDev->Acquire()));
} // CMouse::Acquire


/*****************************************************************************
 CMouse::Unacquire()

 Zwalnia mysz
*****************************************************************************/
bool CMouse::Unacquire()
{
  return (!FAILED(m_pDIDev->Unacquire()));
} // CMouse::Unacquire()


/*****************************************************************************
 CInputSystem::Initialize()

 Inicjuje system wejœcia. Parametr isExclusive powinien mieæ wartoœæ true 
 dla wy³¹cznego dostepu do myszy. Parametr flags jest kombinacj¹ znaczników
 IS_USEKEYBOARD i/lub IS_USEMOUSE.
*****************************************************************************/
bool CInputSystem::Initialize(HWND hwnd, HINSTANCE appInstance, bool isExclusive, DWORD flags)
{
  // tworzy obiekt DirectInput
  if (FAILED(DirectInput8Create(appInstance,
                               DIRECTINPUT_VERSION,
                               IID_IDirectInput8,
                               (void **)&m_pDI,
                               NULL)))
    return false;

  if (flags & IS_USEKEYBOARD)
  {
    m_pKeyboard = new CKeyboard(m_pDI, hwnd);
    if (m_pKeyboard == NULL)
      return false;
  }
  if (flags & IS_USEMOUSE)
  {
    m_pMouse = new CMouse(m_pDI, hwnd, isExclusive);
    if (m_pMouse == NULL)
      return false;
  }

  return true;
} // CInputSystem::Initialize()


/*****************************************************************************
 CInputSystem::Shutdown()

 Zwalnia obiekty i pamiêæ.
*****************************************************************************/
bool CInputSystem::Shutdown()
{
  UnacquireAll();
  if (m_pKeyboard)
  {
    delete m_pKeyboard;
    m_pKeyboard = NULL;
  }

  if (m_pKeyboard)
  {
    delete m_pMouse;
    m_pMouse = NULL;
  }

  if (FAILED(m_pDI->Release()))
    return false;

  return true;
} // CInputSystem::Shutdown()


/*****************************************************************************
 CInputSystem::Update()

 Odpytuje wszystkie urz¹dzenia.
*****************************************************************************/
bool CInputSystem::Update()
{
  if (m_pKeyboard)
    m_pKeyboard->Update();
  if (m_pMouse)
    m_pMouse->Update();

  return true;
} // CInputSystem::Update()


/*****************************************************************************
 CInputSystem::AcquireAll()

 Zajmuje wszystkie urz¹dzenia.
*****************************************************************************/
void CInputSystem::AcquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Acquire();
  if (m_pMouse)
    m_pMouse->Acquire();
} // CInputSystem::AcquireAll()


/*****************************************************************************
 CInputSystem::UnacquireAll()

 Zwalnia wszystkie urz¹dzenia.
*****************************************************************************/
void CInputSystem::UnacquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Unacquire();
  if (m_pMouse)
    m_pMouse->Unacquire();
} // CInputSystem::UnacquireAll()

