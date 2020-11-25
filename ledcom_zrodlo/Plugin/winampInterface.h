#ifndef WINAMPINTERFACE_H
#define WINAMPINTERFACE_H

#include <windows.h>
#include <string.h>

// winampVisModule
typedef struct winampVisModule {
  char *description; // description of module
  HWND hwndParent;   // parent window (filled in by calling app)
  HINSTANCE hDllInstance; // instance handle to this DLL (filled in by calling app)
  int sRate;		 // sample rate (filled in by calling app)
  int nCh;			 // number of channels (filled in...)
  int latencyMs;     // latency from call of RenderFrame to actual drawing
                     // (calling app looks at this value when getting data)
  int delayMs;       // delay between calls in ms

  int spectrumNch;
  int waveformNch;
  unsigned char spectrumData[2][576];
  unsigned char waveformData[2][576];

  void (*Config)(struct winampVisModule *this_mod);  // configuration dialog
  int (*Init)(struct winampVisModule *this_mod);     // 0 on success, creates window, etc
  int (*Render)(struct winampVisModule *this_mod);   // returns 0 if successful, 1 if vis should end
  void (*Quit)(struct winampVisModule *this_mod);    // call when done
 
  void *userData; // user data, optional
} winampVisModule;

// winampVisHeader
typedef struct {
  int version;    
  char *description;
  winampVisModule* (*getModule)(int);
} winampVisHeader;


// exported symbols
typedef winampVisHeader* (*winampVisGetHeaderType)();

// version of current module (0x101 == 1.01)
#define VIS_HDRVER 0x101

#endif

