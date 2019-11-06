/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 11797 $
 * $Id: manager.cpp 11797 2019-07-21 16:56:22Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/manager.cpp $
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include <wx/xrc/xmlres.h>
    #include <wx/fs_zip.h>
    #include <wx/menu.h>

    #include "manager.h" // class's header file
    #include "sdk_events.h"
    #include "cbexception.h"
    #include "projectmanager.h"
    #include "editormanager.h"
    #include "logmanager.h"
    #include "pluginmanager.h"
    #include "toolsmanager.h"
    #include "macrosmanager.h"
    #include "configmanager.h"
    #include "scriptingmanager.h"
    #include "templatemanager.h"
    #include "personalitymanager.h"
    #include "uservarmanager.h"
    #include "filemanager.h"
    #include "globals.h"
    #include "xtra_res.h" // our new ToolBarAddOn handler
#endif

#include <wx/app.h>    // wxTheApp
#include <wx/toolbar.h>
#include <wx/fs_mem.h>


#ifdef PPRCESS_EVENT_PERFORMANCE_MEASURE
    // this preprocessor directive can be defined in cbfunctor.h to enable performance measure
    #include <cxxabi.h>  // demangle C++ names
    #include <cstdlib>   // free the memory created by abi::__cxa_demangle
#endif // PPRCESS_EVENT_PERFORMANCE_MEASURE

#include "cbcolourmanager.h"
#include "ccmanager.h"
#include "debuggermanager.h"

static Manager* s_ManagerInstance = nullptr;


#ifdef PPRCESS_EVENT_PERFORMANCE_MEASURE
static wxString GetCodeblocksEventName(wxEventType type)
{
    wxString name;
    if      (type==cbEVT_APP_STARTUP_DONE) name = _T("cbEVT_APP_STARTUP_DONE");
    else if (type==cbEVT_APP_START_SHUTDOWN) name = _T("cbEVT_APP_START_SHUTDOWN");
    else if (type==cbEVT_APP_ACTIVATED) name = _T("cbEVT_APP_ACTIVATED");
    else if (type==cbEVT_APP_DEACTIVATED) name = _T("cbEVT_APP_DEACTIVATED");
    else if (type==cbEVT_PLUGIN_ATTACHED) name = _T("cbEVT_PLUGIN_ATTACHED");
    else if (type==cbEVT_PLUGIN_RELEASED) name = _T("cbEVT_PLUGIN_RELEASED");
    else if (type==cbEVT_PLUGIN_INSTALLED) name = _T("cbEVT_PLUGIN_INSTALLED");
    else if (type==cbEVT_PLUGIN_UNINSTALLED) name = _T("cbEVT_PLUGIN_UNINSTALLED");
    else if (type==cbEVT_PLUGIN_LOADING_COMPLETE) name = _T("cbEVT_PLUGIN_LOADING_COMPLETE");
    else if (type==cbEVT_EDITOR_CLOSE) name = _T("cbEVT_EDITOR_CLOSE");
    else if (type==cbEVT_EDITOR_OPEN) name = _T("cbEVT_EDITOR_OPEN");
    else if (type==cbEVT_EDITOR_SWITCHED) name = _T("cbEVT_EDITOR_SWITCHED");
    else if (type==cbEVT_EDITOR_ACTIVATED) name = _T("cbEVT_EDITOR_ACTIVATED");
    else if (type==cbEVT_EDITOR_DEACTIVATED) name = _T("cbEVT_EDITOR_DEACTIVATED");
    else if (type==cbEVT_EDITOR_BEFORE_SAVE) name = _T("cbEVT_EDITOR_BEFORE_SAVE");
    else if (type==cbEVT_EDITOR_SAVE) name = _T("cbEVT_EDITOR_SAVE");
    else if (type==cbEVT_EDITOR_MODIFIED) name = _T("cbEVT_EDITOR_MODIFIED");
    else if (type==cbEVT_EDITOR_TOOLTIP) name = _T("cbEVT_EDITOR_TOOLTIP");
    else if (type==cbEVT_EDITOR_TOOLTIP_CANCEL) name = _T("cbEVT_EDITOR_TOOLTIP_CANCEL");
    else if (type==cbEVT_EDITOR_SPLIT) name = _T("cbEVT_EDITOR_SPLIT");
    else if (type==cbEVT_EDITOR_UNSPLIT) name = _T("cbEVT_EDITOR_UNSPLIT");
    else if (type==cbEVT_EDITOR_UPDATE_UI) name = _T("cbEVT_EDITOR_UPDATE_UI");
    else if (type==cbEVT_PROJECT_NEW) name = _T("cbEVT_PROJECT_NEW");
    else if (type==cbEVT_PROJECT_CLOSE) name = _T("cbEVT_PROJECT_CLOSE");
    else if (type==cbEVT_PROJECT_OPEN) name = _T("cbEVT_PROJECT_OPEN");
    else if (type==cbEVT_PROJECT_SAVE) name = _T("cbEVT_PROJECT_SAVE");
    else if (type==cbEVT_PROJECT_ACTIVATE) name = _T("cbEVT_PROJECT_ACTIVATE");
    else if (type==cbEVT_PROJECT_BEGIN_ADD_FILES) name = _T("cbEVT_PROJECT_BEGIN_ADD_FILES");
    else if (type==cbEVT_PROJECT_END_ADD_FILES) name = _T("cbEVT_PROJECT_END_ADD_FILES");
    else if (type==cbEVT_PROJECT_BEGIN_REMOVE_FILES) name = _T("cbEVT_PROJECT_BEGIN_REMOVE_FILES");
    else if (type==cbEVT_PROJECT_END_REMOVE_FILES) name = _T("cbEVT_PROJECT_END_REMOVE_FILES");
    else if (type==cbEVT_PROJECT_FILE_ADDED) name = _T("cbEVT_PROJECT_FILE_ADDED");
    else if (type==cbEVT_PROJECT_FILE_REMOVED) name = _T("cbEVT_PROJECT_FILE_REMOVED");
    else if (type==cbEVT_PROJECT_POPUP_MENU) name = _T("cbEVT_PROJECT_POPUP_MENU");
    else if (type==cbEVT_PROJECT_TARGETS_MODIFIED) name = _T("cbEVT_PROJECT_TARGETS_MODIFIED");
    else if (type==cbEVT_PROJECT_RENAMED) name = _T("cbEVT_PROJECT_RENAMED");
    else if (type==cbEVT_WORKSPACE_CHANGED) name = _T("cbEVT_WORKSPACE_CHANGED");
    else if (type==cbEVT_BUILDTARGET_ADDED) name = _T("cbEVT_BUILDTARGET_ADDED");
    else if (type==cbEVT_BUILDTARGET_REMOVED) name = _T("cbEVT_BUILDTARGET_REMOVED");
    else if (type==cbEVT_BUILDTARGET_RENAMED) name = _T("cbEVT_BUILDTARGET_RENAMED");
    else if (type==cbEVT_BUILDTARGET_SELECTED) name = _T("cbEVT_BUILDTARGET_SELECTED");
    else if (type==cbEVT_PIPEDPROCESS_STDOUT) name = _T("cbEVT_PIPEDPROCESS_STDOUT");
    else if (type==cbEVT_PIPEDPROCESS_STDERR) name = _T("cbEVT_PIPEDPROCESS_STDERR");
    else if (type==cbEVT_PIPEDPROCESS_TERMINATED) name = _T("cbEVT_PIPEDPROCESS_TERMINATED");
    else if (type==cbEVT_THREADTASK_STARTED) name = _T("cbEVT_THREADTASK_STARTED");
    else if (type==cbEVT_THREADTASK_ENDED) name = _T("cbEVT_THREADTASK_ENDED");
    else if (type==cbEVT_THREADTASK_ALLDONE) name = _T("cbEVT_THREADTASK_ALLDONE");
    else if (type==cbEVT_MENUBAR_CREATE_BEGIN) name = _T("cbEVT_MENUBAR_CREATE_BEGIN");
    else if (type==cbEVT_MENUBAR_CREATE_END) name = _T("cbEVT_MENUBAR_CREATE_END");
    else if (type==cbEVT_COMPILER_STARTED) name = _T("cbEVT_COMPILER_STARTED");
    else if (type==cbEVT_COMPILER_FINISHED) name = _T("cbEVT_COMPILER_FINISHED");
    else if (type==cbEVT_COMPILER_SET_BUILD_OPTIONS) name = _T("cbEVT_COMPILER_SET_BUILD_OPTIONS");
    else if (type==cbEVT_CLEAN_PROJECT_STARTED) name = _T("cbEVT_CLEAN_PROJECT_STARTED");
    else if (type==cbEVT_CLEAN_WORKSPACE_STARTED) name = _T("cbEVT_CLEAN_WORKSPACE_STARTED");
    else if (type==cbEVT_DEBUGGER_STARTED) name = _T("cbEVT_DEBUGGER_STARTED");
    else if (type==cbEVT_DEBUGGER_PAUSED) name = _T("cbEVT_DEBUGGER_PAUSED");
    else if (type==cbEVT_DEBUGGER_CONTINUED) name = _T("cbEVT_DEBUGGER_CONTINUED");
    else if (type==cbEVT_DEBUGGER_FINISHED) name = _T("cbEVT_DEBUGGER_FINISHED");
    else if (type==cbEVT_DEBUGGER_CURSOR_CHANGED) name = _T("cbEVT_DEBUGGER_CURSOR_CHANGED");
    else if (type==cbEVT_DEBUGGER_UPDATED) name = _T("cbEVT_DEBUGGER_UPDATED");
    else name = _("unknown CodeBlocksEvent");

    return name;
}
#endif // PPRCESS_EVENT_PERFORMANCE_MEASURE

Manager::Manager() :
    m_pAppWindow(nullptr),
    m_SearchResultLog(nullptr)
{
    for (int &size : m_ImageSizes)
        size = 0;
    for (double &factor : m_UIScaleFactor)
        factor = 0;
}

Manager::~Manager()
{
    // remove all event sinks
    for (EventSinksMap::iterator mit = m_EventSinks.begin(); mit != m_EventSinks.end(); ++mit)
    {
        while (mit->second.size())
        {
            delete (*(mit->second.begin()));
            mit->second.erase(mit->second.begin());
        }
    }

    for (DockEventSinksMap::iterator mit = m_DockEventSinks.begin(); mit != m_DockEventSinks.end(); ++mit)
    {
        while (mit->second.size())
        {
            delete (*(mit->second.begin()));
            mit->second.erase(mit->second.begin());
        }
    }

    for (LayoutEventSinksMap::iterator mit = m_LayoutEventSinks.begin(); mit != m_LayoutEventSinks.end(); ++mit)
    {
        while (mit->second.size())
        {
            delete (*(mit->second.begin()));
            mit->second.erase(mit->second.begin());
        }
    }

    for (LogEventSinksMap::iterator mit = m_LogEventSinks.begin(); mit != m_LogEventSinks.end(); ++mit)
    {
        while (mit->second.size())
        {
            delete (*(mit->second.begin()));
            mit->second.erase(mit->second.begin());
        }
    }
}


Manager* Manager::Get(wxFrame *appWindow)
{
    if (appWindow)
    {
        if (Get()->m_pAppWindow)
            cbThrow(_T("Illegal argument to Manager::Get()"));
        else
        {
            Get()->m_pAppWindow = appWindow;
            LoadResource(_T("manager_resources.zip"));
            Get()->GetLogManager()->Log(_("Manager initialized"));
        }
    }
    return Get();
}

Manager* Manager::Get()
{
    if (!s_ManagerInstance)
        s_ManagerInstance = new Manager;
    return s_ManagerInstance;
}

void Manager::Free()
{
    delete s_ManagerInstance;
    s_ManagerInstance = nullptr;
}

void Manager::SetAppStartedUp(bool app_started_up)
{
    m_AppStartedUp = app_started_up;
}

void Manager::SetAppShuttingDown(bool app_shutting_down)
{
    m_AppShuttingDown = app_shutting_down;
}

void Manager::SetBatchBuild(bool is_batch)
{
    m_IsBatch = is_batch;
}

void Manager::BlockYields(bool block)
{
    m_BlockYields = block;
}

void Manager::ProcessPendingEvents()
{
    if (!m_BlockYields && !m_AppShuttingDown)
        wxTheApp->ProcessPendingEvents();
}

void Manager::Yield()
{
    if (!m_BlockYields && !m_AppShuttingDown)
        wxTheApp->Yield(true);
}

void Manager::Shutdown()
{
    m_AppShuttingDown = true;

    ToolsManager::Free();
    TemplateManager::Free();
    CCManager::Free();
    PluginManager::Free();
    DebuggerManager::Free();
    ScriptingManager::Free();
    ProjectManager::Free();
    EditorManager::Free();
    PersonalityManager::Free();
    MacrosManager::Free();
    UserVariableManager::Free();
    LogManager::Free();
    CfgMgrBldr::Free();
}

bool Manager::ProcessEvent(CodeBlocksEvent& event)
{
    if (IsAppShuttingDown())
        return false;

    EventSinksMap::iterator mit = m_EventSinks.find(event.GetEventType());
    if (mit != m_EventSinks.end())
    {
        for (EventSinksArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
        {
#ifdef PPRCESS_EVENT_PERFORMANCE_MEASURE
            wxStopWatch sw;
#endif // PPRCESS_EVENT_PERFORMANCE_MEASURE

            (*it)->Call(event);

#ifdef PPRCESS_EVENT_PERFORMANCE_MEASURE
            if(sw.Time() > 10) // only print a handler run longer than 10 ms
            {
                // get a mangled C++ name of the function
                const char *p = (*it)->GetTypeName();
                int   status;
                char *realname;
                realname = abi::__cxa_demangle(p, 0, 0, &status);
                wxString msg;

                // if the demangled C++ function name success, then realname is not NULL
                if (realname != 0)
                {
                    msg = wxString::FromUTF8(realname);
                    free(realname);
                }
                else
                    msg = wxString::FromUTF8(p);

                wxEventType type=event.GetEventType();
                msg << GetCodeblocksEventName(type);
                Manager::Get()->GetLogManager()->DebugLog(F(_("%s take %ld ms"), msg.wx_str(), sw.Time()));
            }
#endif // PPRCESS_EVENT_PERFORMANCE_MEASURE
        }
    }
    return true;
}

bool Manager::ProcessEvent(CodeBlocksDockEvent& event)
{
    if (IsAppShuttingDown())
        return false;

    DockEventSinksMap::iterator mit = m_DockEventSinks.find(event.GetEventType());
    if (mit != m_DockEventSinks.end())
    {
        for (DockEventSinksArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
            (*it)->Call(event);
    }
    return true;
}

bool Manager::ProcessEvent(CodeBlocksLayoutEvent& event)
{
    if (IsAppShuttingDown())
        return false;

    LayoutEventSinksMap::iterator mit = m_LayoutEventSinks.find(event.GetEventType());
    if (mit != m_LayoutEventSinks.end())
    {
        for (LayoutEventSinksArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
            (*it)->Call(event);
    }
    return true;
}

bool Manager::ProcessEvent(CodeBlocksLogEvent& event)
{
    if (IsAppShuttingDown())
        return false;

    LogEventSinksMap::iterator mit = m_LogEventSinks.find(event.GetEventType());
    if (mit != m_LogEventSinks.end())
    {
        for (LogEventSinksArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
            (*it)->Call(event);
    }
    return true;
}

bool Manager::IsAppShuttingDown()
{
    return m_AppShuttingDown;
}

bool Manager::IsAppStartedUp()
{
    return m_AppStartedUp;
}

void Manager::LoadXRC(wxString relpath)
{
    LoadResource(relpath);
}

wxMenuBar *Manager::LoadMenuBar(wxString resid,bool createonfailure)
{
    wxMenuBar *m = wxXmlResource::Get()->LoadMenuBar(resid);
    if (!m && createonfailure) m = new wxMenuBar();
    return m;
}

wxMenu *Manager::LoadMenu(wxString menu_id,bool createonfailure)
{
    wxMenu *m = wxXmlResource::Get()->LoadMenu(menu_id);
    if (!m && createonfailure) m = new wxMenu(_T(""));
    return m;
}

wxToolBar* Manager::CreateEmptyToolbar()
{
    const wxSize size(m_ImageSizes[UIComponent::Toolbars], m_ImageSizes[UIComponent::Toolbars]);
    wxWindow *appFrame = GetAppFrame();

#ifdef __WXMSW__
    const double scaleFactor = 1.0;
#else
    const double scaleFactor = cbGetContentScaleFactor(*appFrame);
#endif // __WXMSW__
    const wxSize scaledSize(size.x/scaleFactor, size.y/scaleFactor);

    wxToolBar* toolbar = new wxToolBar(appFrame, -1, wxDefaultPosition, scaledSize, wxTB_FLAT | wxTB_NODIVIDER);
    toolbar->SetToolBitmapSize(scaledSize);

    return toolbar;
}

void Manager::AddonToolBar(wxToolBar* toolBar,wxString resid)
{
    if (!toolBar)
        return;
    if (m_ToolbarHandler)
        m_ToolbarHandler->SetCurrentResourceID(resid);
    wxXmlResource::Get()->LoadObject(toolBar,nullptr,resid,_T("wxToolBarAddOn"));
    if (m_ToolbarHandler)
        m_ToolbarHandler->SetCurrentResourceID(wxString());
}

void Manager::SetImageSize(int size, UIComponent component)
{
    cbAssert(component>=0 && component < UIComponent::Last);
    m_ImageSizes[component] = size;

    if (component == UIComponent::Toolbars)
    {
        cbAssert(m_ToolbarHandler);
        m_ToolbarHandler->SetToolbarImageSize(size);
    }
}

int Manager::GetImageSize(UIComponent component) const
{
    cbAssert(component>=0 && component < UIComponent::Last);
    cbAssert(m_ImageSizes[component] > 0);
    return m_ImageSizes[component];
}

void Manager::SetUIScaleFactor(double scaleFactor, UIComponent component)
{
    cbAssert(component>=0 && component < UIComponent::Last);
    m_UIScaleFactor[component] = scaleFactor;
}

double Manager::GetUIScaleFactor(UIComponent component) const
{
    cbAssert(component>=0 && component < UIComponent::Last);
    cbAssert(m_UIScaleFactor[component] >= 1.0);
    return m_UIScaleFactor[component];
}

void Manager::SetToolbarHandler(wxToolBarAddOnXmlHandler *handler)
{
    m_ToolbarHandler = handler;
}

wxFrame* Manager::GetAppFrame() const
{
    return m_pAppWindow;
}

wxWindow* Manager::GetAppWindow() const
{
    return (wxWindow*)m_pAppWindow;
}

ProjectManager* Manager::GetProjectManager() const
{
    return ProjectManager::Get();
}

EditorManager* Manager::GetEditorManager() const
{
    return EditorManager::Get();
}

LogManager* Manager::GetLogManager() const
{
    return LogManager::Get();
}

PluginManager* Manager::GetPluginManager() const
{
    return PluginManager::Get();
}

ToolsManager* Manager::GetToolsManager() const
{
    return ToolsManager::Get();
}

MacrosManager* Manager::GetMacrosManager() const
{
    return MacrosManager::Get();
}

PersonalityManager* Manager::GetPersonalityManager() const
{
    return PersonalityManager::Get();
}

UserVariableManager* Manager::GetUserVariableManager() const
{
    return UserVariableManager::Get();
}

ScriptingManager* Manager::GetScriptingManager() const
{
    return ScriptingManager::Get();
}

ConfigManager* Manager::GetConfigManager(const wxString& name_space) const
{
    return CfgMgrBldr::GetConfigManager(name_space);
}

FileManager* Manager::GetFileManager() const
{
    return FileManager::Get();
}

DebuggerManager* Manager::GetDebuggerManager() const
{
    return DebuggerManager::Get();
}

ColourManager* Manager::GetColourManager() const
{
    return ColourManager::Get();
}

CCManager* Manager::GetCCManager() const
{
    return CCManager::Get();
}

bool Manager::LoadResource(const wxString& file)
{
    wxString resourceFile = ConfigManager::LocateDataFile(file, sdDataGlobal | sdDataUser);
    wxString memoryFile = _T("memory:") + file;

    if (wxFile::Access(resourceFile, wxFile::read) == false)
    {
        Get()->GetLogManager()->LogError(_("Manager failed to access XRC resource '") + resourceFile + _("'."));
        return false;
    }

    // The code below forces a reload of the resource
    // Currently unused...

//    {
//        wxMemoryFSHandler::RemoveFile(file);
//    }
//#if wxABI_VERSION > 20601
//    // unload old resources with the same name
//    wxXmlResource::Get()->Unload(memoryFile);
//#endif

    wxFile f(resourceFile, wxFile::read);
    char *buf = nullptr;

    try
    {
        size_t len = f.Length();
        buf = new char[len];
        f.Read(buf, len);
        {
            wxMemoryFSHandler::AddFile(file, buf, len);
        }
        if ( !wxXmlResource::Get()->Load(memoryFile) )
            Get()->GetLogManager()->LogError(_("Manager failed to load XRC resource '") + resourceFile + _("'."));
        delete[] buf;
        return true;
    }
    catch (...)
    {
        delete[] buf;
        Get()->GetLogManager()->LogError(_("Manager hardly failed to load XRC resource '") + resourceFile + _("'."));
        return false;
    }
}

wxCmdLineParser* Manager::GetCmdLineParser()
{
    return &m_CmdLineParser;
}

void Manager::RegisterEventSink(wxEventType eventType, IEventFunctorBase<CodeBlocksEvent>* functor)
{
    m_EventSinks[eventType].push_back(functor);
}

void Manager::RegisterEventSink(wxEventType eventType, IEventFunctorBase<CodeBlocksDockEvent>* functor)
{
    m_DockEventSinks[eventType].push_back(functor);
}

void Manager::RegisterEventSink(wxEventType eventType, IEventFunctorBase<CodeBlocksLayoutEvent>* functor)
{
    m_LayoutEventSinks[eventType].push_back(functor);
}

void Manager::RegisterEventSink(wxEventType eventType, IEventFunctorBase<CodeBlocksLogEvent>* functor)
{
    m_LogEventSinks[eventType].push_back(functor);
}

void Manager::RemoveAllEventSinksFor(void* owner)
{
    for (EventSinksMap::iterator mit = m_EventSinks.begin(); mit != m_EventSinks.end(); ++mit)
    {
        EventSinksArray::iterator it = mit->second.begin();
        bool endIsInvalid = false;
        while (!endIsInvalid && it != mit->second.end())
        {
            if ((*it) && (*it)->GetThis() == owner)
            {
                EventSinksArray::iterator it2 = it++;
                endIsInvalid = it == mit->second.end();
                delete (*it2);
                mit->second.erase(it2);
            }
            else
                ++it;
        }
    }

    for (DockEventSinksMap::iterator mit = m_DockEventSinks.begin(); mit != m_DockEventSinks.end(); ++mit)
    {
        DockEventSinksArray::iterator it = mit->second.begin();
        bool endIsInvalid = false;
        while (!endIsInvalid && it != mit->second.end())
        {
            if ((*it) && (*it)->GetThis() == owner)
            {
                DockEventSinksArray::iterator it2 = it++;
                endIsInvalid = it == mit->second.end();
                delete (*it2);
                mit->second.erase(it2);
            }
            else
                ++it;
        }
    }

    for (LayoutEventSinksMap::iterator mit = m_LayoutEventSinks.begin(); mit != m_LayoutEventSinks.end(); ++mit)
    {
        LayoutEventSinksArray::iterator it = mit->second.begin();
        bool endIsInvalid = false;
        while (!endIsInvalid && it != mit->second.end())
        {
            if ((*it) && (*it)->GetThis() == owner)
            {
                LayoutEventSinksArray::iterator it2 = it++;
                endIsInvalid = it == mit->second.end();
                delete (*it2);
                mit->second.erase(it2);
            }
            else
                ++it;
        }
    }

    for (LogEventSinksMap::iterator mit = m_LogEventSinks.begin(); mit != m_LogEventSinks.end(); ++mit)
    {
        LogEventSinksArray::iterator it = mit->second.begin();
        bool endIsInvalid = false;
        while (!endIsInvalid && it != mit->second.end())
        {
            if ((*it) && (*it)->GetThis() == owner)
            {
                LogEventSinksArray::iterator it2 = it++;
                endIsInvalid = it == mit->second.end();
                delete (*it2);
                mit->second.erase(it2);
            }
            else
                ++it;
        }
    }
}

bool            Manager::m_AppShuttingDown = false;
bool            Manager::m_AppStartedUp    = false;
bool            Manager::m_BlockYields     = false;
bool            Manager::m_IsBatch         = false;
wxCmdLineParser Manager::m_CmdLineParser;
wxToolBarAddOnXmlHandler* Manager::m_ToolbarHandler = nullptr;
