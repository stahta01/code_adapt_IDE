/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 9753 $
 * $Id: editor_hooks.cpp 9753 2014-04-15 05:12:55Z ollydbg $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/editor_hooks.cpp $
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include "cbeditor.h"
#endif
#include "cbplugin.h"


#include "editor_hooks.h"

#ifdef EDITOR_HOOK_PERFORMANCE_MEASURE
    //put these include directive after #include "editor_hooks.h", as the macro may
    //defined in the header file
    #include <cxxabi.h>  // demangle C++ names
    #include <cstdlib>   // free the memory created by abi::__cxa_demangle
#endif // EDITOR_HOOK_PERFORMANCE_MEASURE

#include <map>


#ifdef EDITOR_HOOK_PERFORMANCE_MEASURE
// this function is only used in performance hook
static wxString GetScintillaEventName(wxEventType type)
{
    wxString name;
    if (type == wxEVT_STC_CHANGE)                  name = _T("wxEVT_STC_CHANGE");
    else if (type == wxEVT_STC_STYLENEEDED)        name = _T("wxEVT_STC_STYLENEEDED");
    else if (type == wxEVT_STC_CHARADDED)          name = _T("wxEVT_STC_CHARADDED");
    else if (type == wxEVT_STC_SAVEPOINTREACHED)   name = _T("wxEVT_STC_SAVEPOINTREACHED");
    else if (type == wxEVT_STC_SAVEPOINTLEFT)      name = _T("wxEVT_STC_SAVEPOINTLEFT");
    else if (type == wxEVT_STC_ROMODIFYATTEMPT)    name = _T("wxEVT_STC_ROMODIFYATTEMPT");
    else if (type == wxEVT_STC_KEY)                name = _T("wxEVT_STC_KEY");
    else if (type == wxEVT_STC_DOUBLECLICK)        name = _T("wxEVT_STC_DOUBLECLICK");
    else if (type == wxEVT_STC_UPDATEUI)           name = _T("wxEVT_STC_UPDATEUI");
    else if (type == wxEVT_STC_MODIFIED)           name = _T("wxEVT_STC_MODIFIED");
    else if (type == wxEVT_STC_MACRORECORD)        name = _T("wxEVT_STC_MACRORECORD");
    else if (type == wxEVT_STC_MARGINCLICK)        name = _T("wxEVT_STC_MARGINCLICK");
    else if (type == wxEVT_STC_NEEDSHOWN)          name = _T("wxEVT_STC_NEEDSHOWN");
    else if (type == wxEVT_STC_PAINTED)            name = _T("wxEVT_STC_PAINTED");
    else if (type == wxEVT_STC_USERLISTSELECTION)  name = _T("wxEVT_STC_USERLISTSELECTION");
    else if (type == wxEVT_STC_URIDROPPED)         name = _T("wxEVT_STC_URIDROPPED");
    else if (type == wxEVT_STC_DWELLSTART)         name = _T("wxEVT_STC_DWELLSTART");
    else if (type == wxEVT_STC_DWELLEND)           name = _T("wxEVT_STC_DWELLEND");
    else if (type == wxEVT_STC_START_DRAG)         name = _T("wxEVT_STC_START_DRAG");
    else if (type == wxEVT_STC_DRAG_OVER)          name = _T("wxEVT_STC_DRAG_OVER");
    else if (type == wxEVT_STC_DO_DROP)            name = _T("wxEVT_STC_DO_DROP");
    else if (type == wxEVT_STC_ZOOM)               name = _T("wxEVT_STC_ZOOM");
    else if (type == wxEVT_STC_HOTSPOT_CLICK)      name = _T("wxEVT_STC_HOTSPOT_CLICK");
    else if (type == wxEVT_STC_HOTSPOT_DCLICK)     name = _T("wxEVT_STC_HOTSPOT_DCLICK");
    else if (type == wxEVT_STC_CALLTIP_CLICK)      name = _T("wxEVT_STC_CALLTIP_CLICK");
    else if (type == wxEVT_STC_AUTOCOMP_SELECTION) name = _T("wxEVT_STC_AUTOCOMP_SELECTION");
    else if (type == wxEVT_STC_INDICATOR_CLICK)    name = _T("wxEVT_STC_INDICATOR_CLICK");
    else if (type == wxEVT_STC_INDICATOR_RELEASE)  name = _T("wxEVT_STC_INDICATOR_RELEASE");
    else name = _T("unknown wxEVT_STC_EVENT");

    return name;
}
#endif // EDITOR_HOOK_PERFORMANCE_MEASURE

namespace EditorHooks
{
    typedef std::map<int, HookFunctorBase*> HookFunctorsMap;
    static HookFunctorsMap s_HookFunctorsMap;
    static int             s_UniqueID = 0;
}

int EditorHooks::RegisterHook(EditorHooks::HookFunctorBase* functor)
{
    for (HookFunctorsMap::iterator it = s_HookFunctorsMap.begin(); it != s_HookFunctorsMap.end(); ++it)
    {
        if (it->second == functor)
            return it->first;
    }
    s_HookFunctorsMap[s_UniqueID] = functor;
    return s_UniqueID++;
}

EditorHooks::HookFunctorBase* EditorHooks::UnregisterHook(int id, bool deleteHook)
{
    HookFunctorsMap::iterator it = s_HookFunctorsMap.find(id);
    if (it != s_HookFunctorsMap.end())
    {
        EditorHooks::HookFunctorBase* functor = it->second;
        s_HookFunctorsMap.erase(it);
        if (deleteHook)
        {
            delete functor;
            return nullptr;
        }
        return functor;
    }
    return nullptr;
}

bool EditorHooks::HasRegisteredHooks()
{
    return s_HookFunctorsMap.size() != 0;
}

void EditorHooks::CallHooks(cbEditor* editor, wxStyledTextEvent& event)
{
    for (HookFunctorsMap::iterator it = s_HookFunctorsMap.begin(); it != s_HookFunctorsMap.end(); ++it)
    {
        EditorHooks::HookFunctorBase* functor = it->second;
        if (functor)
        {
#ifdef EDITOR_HOOK_PERFORMANCE_MEASURE
            wxStopWatch sw;
#endif // EDITOR_HOOK_PERFORMANCE_MEASURE

            functor->Call(editor, event);

#ifdef EDITOR_HOOK_PERFORMANCE_MEASURE
            if(sw.Time() < 10) // only print a handler run longer than 10 ms
                continue;

            const char *p = functor->GetTypeName();
            int   status;
            char *realname;
            realname = abi::__cxa_demangle(p, 0, 0, &status);
            wxString txt;
            // if the demangled C++ function name success, then realname is not NULL
            if (realname != 0)
            {
                txt = wxString::FromUTF8(realname);
                free(realname);
            }
            else
                txt = wxString::FromUTF8(p); // show the mangled(original) name

            wxEventType type = event.GetEventType();
            txt << GetScintillaEventName(type);
            Manager::Get()->GetLogManager()->DebugLog(F(wxT("%s take %ld ms"), txt.wx_str(), sw.Time()));
#endif // EDITOR_HOOK_PERFORMANCE_MEASURE
        }

    }
}

namespace EditorHooks
{
    cbSmartIndentEditorHookFunctor::cbSmartIndentEditorHookFunctor(cbSmartIndentPlugin *plugin):
    m_plugin(plugin){}

    void cbSmartIndentEditorHookFunctor::Call(cbEditor *editor, wxStyledTextEvent &event) const
    {
        m_plugin->OnEditorHook(editor, event);
    }
}
