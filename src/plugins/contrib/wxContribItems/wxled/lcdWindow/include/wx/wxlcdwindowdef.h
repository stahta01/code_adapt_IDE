/////////////////////////////////////////////////////////////////////////////
// Name:        wxlcdwindowdef.h
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_WXLCDWINDOWDEF_H
#define INCLUDE_WXLCDWINDOWDEF_H

// Defines for shared builds
#ifdef WXMAKINGDLL_LCDWINDOW
    #define WXDLLIMPEXP_LCDWINDOW                  WXEXPORT
    #define WXDLLIMPEXP_DATA_LCDWINDOW(type)       WXEXPORT type
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_LCDWINDOW                  WXIMPORT
    #define WXDLLIMPEXP_DATA_LCDWINDOW(type)       WXIMPORT type
#else // not making nor using DLL
    #define WXDLLIMPEXP_LCDWINDOW
    #define WXDLLIMPEXP_DATA_LCDWINDOW(type)       type
#endif

#endif // INCLUDE_WXLCDWINDOWDEF_H
