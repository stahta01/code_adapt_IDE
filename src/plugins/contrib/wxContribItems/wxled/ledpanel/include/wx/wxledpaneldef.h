/////////////////////////////////////////////////////////////////////////////
// Name:        wxledpaneldef.h
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_WXLEDPANELDEF_H
#define INCLUDE_WXLEDPANELDEF_H

// Defines for shared builds
#ifdef WXMAKINGDLL_LEDPANEL
    #define WXDLLIMPEXP_LEDPANEL                  WXEXPORT
    #define WXDLLIMPEXP_DATA_LEDPANEL(type)       WXEXPORT type
#elif defined(WXUSINGDLL)
    #define WXDLLIMPEXP_LEDPANEL                  WXIMPORT
    #define WXDLLIMPEXP_DATA_LEDPANEL(type)       WXIMPORT type
#else // not making nor using DLL
    #define WXDLLIMPEXP_LEDPANEL
    #define WXDLLIMPEXP_DATA_LEDPANEL(type)       type
#endif

#endif // INCLUDE_WXLEDPANELDEF_H
