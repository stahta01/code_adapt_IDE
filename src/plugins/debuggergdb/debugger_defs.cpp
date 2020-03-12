/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 11820 $
 * $Id: debugger_defs.cpp 11820 2019-07-30 17:26:39Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/plugins/debuggergdb/debugger_defs.cpp $
 */

#include "sdk.h"
#ifndef CB_PRECOMP
#include <wx/font.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/frame.h>
#include "manager.h"
#endif
#include "scrollingdialog.h"
#include <cbdebugger_interfaces.h>
#include "debugger_defs.h"
#include "debuggerdriver.h"
#include "debuggergdb.h"

#include <wx/arrimpl.cpp>
#include <cinttypes>

#if !defined(CB_TEST_PROJECT)

const int DEBUGGER_CURSOR_CHANGED = wxNewId();
const int DEBUGGER_SHOW_FILE_LINE = wxNewId();

DebuggerCmd::DebuggerCmd(DebuggerDriver* driver, const wxString& cmd, bool logToNormalLog)
    : m_Cmd(cmd),
    m_pDriver(driver),
    m_LogToNormalLog(logToNormalLog)
{
}

void DebuggerCmd::ParseOutput(const wxString& output)
{
    if (!output.IsEmpty() && m_LogToNormalLog)
        m_pDriver->Log(output);
}

DbgCmd_UpdateWindow::DbgCmd_UpdateWindow(DebuggerDriver* driver,
                                         cbDebuggerPlugin::DebugWindows windowToUpdate) :
    DebuggerCmd(driver),
    m_windowToUpdate(windowToUpdate)
{
}

void DbgCmd_UpdateWindow::Action()
{
    CodeBlocksEvent event(cbEVT_DEBUGGER_UPDATED);
    event.SetInt(int(m_windowToUpdate));
    event.SetPlugin(m_pDriver->GetDebugger());
    Manager::Get()->ProcessEvent(event);
}

// Custom window to display output of DebuggerInfoCmd
class DebuggerInfoWindow : public wxScrollingDialog
{
    public:
        DebuggerInfoWindow(wxWindow *parent, const wxString& title, const wxString& content)
            : wxScrollingDialog(parent, -1, title, wxDefaultPosition, wxDefaultSize,
                                wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX)
        {
            wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
            wxFont font(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
            m_pText = new wxTextCtrl(this, -1, content, wxDefaultPosition, wxDefaultSize,
                                     wxTE_READONLY | wxTE_MULTILINE | wxTE_RICH2 | wxHSCROLL);
            m_pText->SetFont(font);

            sizer->Add(m_pText, 1, wxGROW);

            SetSizer(sizer);
            sizer->Layout();
        }
        wxTextCtrl* m_pText;
};

void DebuggerInfoCmd::ParseOutput(const wxString& output)
{
    DebuggerInfoWindow win(Manager::Get()->GetAppWindow(), m_Title.wx_str(), output);
    win.ShowModal();
}

#endif // !defined(CB_TEST_PROJECT)

void DebuggerBreakpoint::SetEnabled(bool flag)
{
    enabled = flag;
}

wxString DebuggerBreakpoint::GetLocation() const
{
    switch (type)
    {
        case bptData:
            return breakAddress;
        case bptCode:
            return filenameAsPassed;
        case bptFunction:
            return func;
        default:
            return _("Unknown");
    }
}

int DebuggerBreakpoint::GetLine() const
{
    return line;
}

wxString DebuggerBreakpoint::GetLineString() const
{
    return (type == bptCode) ? wxString::Format(wxT("%d"), line) : wxString(wxEmptyString);
}

wxString DebuggerBreakpoint::GetType() const
{
    switch (type)
    {
        case bptData:
            return _("Data");
        case bptCode:
            return _("Code");
        case bptFunction:
            return _("Function");
        default:
            return _("Unknown");
    }
}

wxString DebuggerBreakpoint::GetInfo() const
{
    switch (type)
    {
        case bptData:
            if (breakOnRead && breakOnWrite)
                return  _("type: read-write");
            else if (breakOnRead)
                return _("type: read");
            else if (breakOnWrite)
                return _("type: write");
            else
                return _("type: unknown");
        case bptCode:
        {
            wxString s;
            if (useCondition)
                s += _("condition: ") + condition;
            if (useIgnoreCount)
            {
                if (!s.empty())
                    s += wxT(" ");
                s += wxString::Format(_("ignore count: %d"), ignoreCount);
            }
            if (temporary)
            {
                if (!s.empty())
                    s += wxT(" ");
                s += _("temporary");
            }
            s += wxString::Format(wxT(" (index: %ld)"), index);
            return s;
        }
        case bptFunction:
        default:
            return wxEmptyString;
    }
}

bool DebuggerBreakpoint::IsEnabled() const
{
    return enabled;
}

bool DebuggerBreakpoint::IsVisibleInEditor() const
{
    return type == bptCode;
}

bool DebuggerBreakpoint::IsTemporary() const
{
    return temporary;
}


GDBWatch::GDBWatch(wxString const &symbol) :
    m_symbol(symbol),
    m_format(Undefined),
    m_array_start(0),
    m_array_count(0),
    m_is_array(false),
    m_forTooltip(false)
{
}
GDBWatch::~GDBWatch()
{
}
void GDBWatch::GetSymbol(wxString &symbol) const
{
    symbol = m_symbol;
}
void GDBWatch::GetValue(wxString &value) const
{
    value = m_raw_value;
}
bool GDBWatch::SetValue(const wxString &value)
{
    if(m_raw_value != value)
    {
        MarkAsChanged(true);
        m_raw_value = value;
    }
    return true;
}
void GDBWatch::GetFullWatchString(wxString &full_watch) const
{
    cb::shared_ptr<const cbWatch> parent = GetParent();
    if (parent)
    {
        parent->GetFullWatchString(full_watch);
        full_watch += wxT(".") + m_symbol;
    }
    else
        full_watch = m_symbol;
}

void GDBWatch::GetType(wxString &type) const
{
    type = m_type;
}
void GDBWatch::SetType(const wxString &type)
{
    m_type = type;
}

wxString GDBWatch::GetDebugString() const
{
    return m_debug_value;
}

wxString GDBWatch::MakeSymbolToAddress() const
{
    return wxT("&") + m_symbol;
}

bool GDBWatch::IsPointerType() const
{
    return ::IsPointerType(m_type);
}

void GDBWatch::SetDebugValue(wxString const &value)
{
    m_debug_value = value;
}

void GDBWatch::SetSymbol(const wxString& symbol)
{
    m_symbol = symbol;
}

void GDBWatch::DoDestroy()
{
    delete this;
}

void GDBWatch::SetFormat(WatchFormat format)
{
    m_format = format;
}

WatchFormat GDBWatch::GetFormat() const
{
    return m_format;
}

void GDBWatch::SetArray(bool flag)
{
    m_is_array = flag;
}

bool GDBWatch::IsArray() const
{
    return m_is_array;
}

void GDBWatch::SetArrayParams(int start, int count)
{
    m_array_start = start;
    m_array_count = count;
}

int GDBWatch::GetArrayStart() const
{
    return m_array_start;
}

int GDBWatch::GetArrayCount() const
{
    return m_array_count;
}

void GDBWatch::SetForTooltip(bool flag)
{
    m_forTooltip = flag;
}

bool GDBWatch::GetForTooltip() const
{
    return m_forTooltip;
}

GDBMemoryRangeWatch::GDBMemoryRangeWatch(uint64_t address, uint64_t size, const wxString& symbol) :
    m_address(address),
    m_size(size),
    m_symbol(symbol)
{
}

bool GDBMemoryRangeWatch::SetValue(const wxString &value)
{
    if (m_value != value)
    {
        m_value = value;
        MarkAsChanged(true);
    }
    return true;
}

wxString GDBMemoryRangeWatch::MakeSymbolToAddress() const
{
    const int tmpBuffSize = 20;
    char tmpAddress[tmpBuffSize];

    memset(tmpAddress, 0, tmpBuffSize);
    snprintf(tmpAddress, tmpBuffSize, "0x%" PRIx64 " ", GetAddress());

    return wxString::FromUTF8(tmpAddress);
};

bool IsPointerType(wxString type)
{
    type.Trim(true);
    type.Trim(false);

    if (type.Contains(wxT("char *")) || type.Contains(wxT("char const *")))
        return false;
    else if (type.EndsWith(wxT("*")))
        return true;
    else if (type.EndsWith(wxT("* const")))
        return true;
    else if (type.EndsWith(wxT("* volatile")))
        return true;
    else if (type.EndsWith(wxT("* const volatile")))
        return true;
    else if (type.EndsWith(wxT("restrict"))) // restrict is only for pointer types
        return true;
    return false;
}

// Use this function to sanitize user input which might end as the last part of GDB commands.
// If the last character is '\', GDB will treat it as line continuation and it will stall.
wxString CleanStringValue(wxString value)
{
    while (value.EndsWith(wxT("\\")))
        value.RemoveLast();
    return value;
}

DebuggerLanguage g_DebugLanguage = dl_Cpp;

