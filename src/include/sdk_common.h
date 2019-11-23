/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef SDK_COMMON_H
#define SDK_COMMON_H

//This file should be included only by sdk.h and sdk_precomp.h
//It includes all the common and necessary header files for precompilation.

#if defined(NOPCH)
    #undef CB_PRECOMP
#endif // NOPCH

#if ( defined(CB_PRECOMP) && !defined(WX_PRECOMP) )
    #define WX_PRECOMP
#endif // CB_PRECOMP

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

    // some common wxWidgets headers
    #include <wx/app.h>
    #include <wx/arrstr.h>
    #include <wx/bmpbuttn.h>
    #include <wx/button.h>
    #include <wx/checkbox.h>
    #include <wx/checklst.h>
    #include <wx/choice.h>
    #include <wx/choicdlg.h>
    #include <wx/colordlg.h>
    #include <wx/combobox.h>
    #include <wx/confbase.h>
    #include <wx/datetime.h>
    #include <wx/dcclient.h>
    #include <wx/dialog.h>
    #include <wx/dir.h>
    #include <wx/dynarray.h>
    #include <wx/event.h>
    #include <wx/file.h>
    #include <wx/filedlg.h>
    #include <wx/filename.h>
    #include <wx/font.h>
    #include <wx/frame.h>
    #include <wx/fs_zip.h>
    #include <wx/hashmap.h>
    #include <wx/image.h>
    #include <wx/imaglist.h>
    #include <wx/intl.h>
    #include <wx/list.h>
    #include <wx/listbox.h>
    #include <wx/listctrl.h>
    #include <wx/log.h>
    #include <wx/menu.h>
    #include <wx/menuitem.h>
    #include <wx/msgdlg.h>
    #include <wx/notebook.h>
    #include <wx/panel.h>
    #include <wx/print.h>
    #include <wx/process.h>
    #include <wx/radiobox.h>
    #include <wx/radiobut.h>
    #include <wx/regex.h>
    #include <wx/sizer.h>
    #include <wx/slider.h>
    #include <wx/socket.h>
    #include <wx/spinctrl.h>
    #include <wx/splitter.h>
    #include <wx/statbmp.h>
    #include <wx/stattext.h>
    #include <wx/string.h>
    #include <wx/textdlg.h>
    #include <wx/textctrl.h>
    #include <wx/thread.h>
    #include <wx/timer.h>
    #include <wx/toolbar.h>
    #include <wx/treectrl.h>
    #include <wx/txtstrm.h>
    #include <wx/utils.h>
    #include <wx/wfstream.h>
    #include <wx/xrc/xmlres.h>

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
