/////////////////////////////////////////////////////////////////////////////
// Name:        wxleddef.h
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_WXLEDDEF_H
#define INCLUDE_WXLEDDEF_H

// Defines for shared builds
#ifdef WXMAKINGDLL_LED
    #define WXDLLIMPEXP_LED                  WXEXPORT
    #define WXDLLIMPEXP_DATA_LED(type)       WXEXPORT type
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_LED                  WXIMPORT
    #define WXDLLIMPEXP_DATA_LED(type)       WXIMPORT type
#else // not making nor using DLL
    #define WXDLLIMPEXP_LED
    #define WXDLLIMPEXP_DATA_LED(type)       type
#endif

#endif // INCLUDE_WXLEDDEF_H
