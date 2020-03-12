/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef SDK_COMMON_H
#define SDK_COMMON_H

//This file should be included only by sdk.h and sdk_precomp.h
//It includes all the common and necessary header files for precompilation.

//#if defined(NOPCH)
    //#undef CB_PRECOMP
//#endif // NOPCH

#if ( defined(CB_PRECOMP) && !defined(WX_PRECOMP) && !defined(NOPCH))
    #define WX_PRECOMP
#endif

// basic wxWidgets headers : this one itself will check for precompiled headers
// and if so will include a list of wx headers, at the bottom we add some more headers
// in the case of precompilation (note : some headers are in both lists)
// so even if NO CB_PRECOMP we can still have WX_PRECOMP turned on in this "wxprec" header
#include <wx/wxprec.h>

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#include "prep.h" // this is deliberately not inside the #ifdef block

#ifdef CB_PRECOMP

    // some common wxWidgets headers included by 20 or more core cpp files
    #include <wx/button.h>              // included by 50+ core cpp files
    #include <wx/checkbox.h>            // included by 31 core cpp files
    #include <wx/filedlg.h>             // included by 26 core cpp files
    #include <wx/intl.h>                // included by 50+ core cpp files
    #include <wx/listbox.h>             // included by 21 core cpp files
    #include <wx/menu.h>                // included by 39 core cpp files
    #include <wx/msgdlg.h>              // included by 34 core cpp files
    #include <wx/sizer.h>               // included by 28 core cpp files
    #include <wx/stattext.h>            // included by 28 core cpp files
    #include <wx/string.h>              // included by 50+ core cpp files
    #include <wx/textctrl.h>            // included by 34 core cpp files
    #include <wx/utils.h>               // included by 22 core cpp files
    // wx headers not in wx/wx.h
    #include <wx/dir.h>                 // included by 21 core cpp files
    #include <wx/filename.h>            // included by 44 core cpp files
    #include <wx/listctrl.h>            // included by 25 core cpp files
    #include <wx/regex.h>               // included by 32 core cpp files
    #include <wx/xrc/xmlres.h>          // included by 50+ core cpp files

/*
 *  cbplugin.h removed because it changes too often.
 *  cbstyledtextctrl.h removed because it includes "wx/wxscintilla.h".
 *  editorcolourset.h removed because it includes "wx/wxscintilla.h".
 */

    #include <algorithm>              // included by 28 plugins cpp files
    #include <map>                    // included by cbproject.h
    #include <set>                    // included by configmanager.h
    #include <vector>                 // included by cbproject.h

    #include "cbproject.h"            // included by 65 plugins cpp files
    #include "cbeditor.h"             // included by 65 plugins cpp files
    #include "cbexception.h"          // included by editormanager.h
    #include "configmanager.h"        // included by 137 plugins cpp files
    #include "editorbase.h"           // included by cbeditor.h
    #include "editormanager.h"        // included by 79 plugins cpp files
    #include "globals.h"              // included by configmanager.h
    #include "logmanager.h"           // included by 122 plugins cpp files
    #include "manager.h"              // included by configmanager.h
    #include "projectbuildtarget.h"   // included by cbproject.h
    #include "projectfile.h"          // included by projectbuildtarget.h
    #include "projectmanager.h"       // included by cbproject.h
    #include "sdk_events.h"           // included by manager.h
    #include "settings.h"             // included by cbproject.h
#endif // CB_PRECOMP

#endif // SDK_COMMON_H
