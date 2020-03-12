/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 10912 $
 * $Id: edittooldlg.cpp 10912 2016-09-25 16:10:13Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/edittooldlg.cpp $
 */

#include "sdk_precomp.h"
#ifndef WX_PRECOMP
    #include <wx/radiobox.h>
#endif
#ifndef CB_PRECOMP
    #include <wx/button.h>
    #include <wx/checkbox.h>
    #include <wx/intl.h>
    #include <wx/string.h>
    #include <wx/textctrl.h>
    #include <wx/xrc/xmlres.h>

    #include "ca/exception.h"
    #include "globals.h"
#endif

#include "edittooldlg.h"
#include "cbtool.h"
#include <wx/filedlg.h>


BEGIN_EVENT_TABLE(EditToolDlg, wxScrollingDialog)
    EVT_BUTTON(XRCID("btnBrowseCommand"),     EditToolDlg::OnBrowseCommand)
    EVT_BUTTON(XRCID("btnBrowseDir"),         EditToolDlg::OnBrowseDir)
    EVT_UPDATE_UI(-1,                        EditToolDlg::OnUpdateUI)
END_EVENT_TABLE()

EditToolDlg::EditToolDlg(wxWindow* parent, cbTool* tool)
    : m_Tool(tool)
{
    if (!tool)
        caThrow(_T("Tool* parameter is mandatory in EditToolDlg()"));

    wxXmlResource::Get()->LoadObject(this, parent, _T("dlgEditTool"),_T("wxScrollingDialog"));
    XRCCTRL(*this, "wxID_OK", wxButton)->SetDefault();
    XRCCTRL(*this, "txtName", wxTextCtrl)->SetValue(m_Tool->GetName());
    XRCCTRL(*this, "txtCommand", wxTextCtrl)->SetValue(m_Tool->GetCommand());
    XRCCTRL(*this, "txtParams", wxTextCtrl)->SetValue(m_Tool->GetParams());
    XRCCTRL(*this, "txtDir", wxTextCtrl)->SetValue(m_Tool->GetWorkingDir());
    XRCCTRL(*this, "rbLaunchOptions", wxRadioBox)->SetSelection(static_cast<int>(m_Tool->GetLaunchOption()));
} // end of constructor

EditToolDlg::~EditToolDlg()
{
    //dtor
}

// events

void EditToolDlg::OnUpdateUI(cb_unused wxUpdateUIEvent& event)
{
    const wxString name = XRCCTRL(*this, "txtName", wxTextCtrl)->GetValue();
    const wxString command = XRCCTRL(*this, "txtCommand", wxTextCtrl)->GetValue();
    bool en = !name.IsEmpty() && !command.IsEmpty();
    XRCCTRL(*this, "wxID_OK", wxButton)->Enable(en);
} // end of OnUpdateUI

void EditToolDlg::OnBrowseCommand(cb_unused wxCommandEvent& event)
{
    const wxFileName file(XRCCTRL(*this, "txtCommand", wxTextCtrl)->GetValue());
    wxString filename = wxFileSelector(_("Select executable"), file.GetPath(wxPATH_GET_VOLUME), file.GetFullName());
    if (!filename.IsEmpty())
        XRCCTRL(*this, "txtCommand", wxTextCtrl)->SetValue(filename);
} // end of OnBrowseCommand

void EditToolDlg::OnBrowseDir(cb_unused wxCommandEvent& event)
{
    const wxString dir = ChooseDirectory(this, _("Select working directory"), XRCCTRL(*this, "txtDir", wxTextCtrl)->GetValue());
    if (!dir.IsEmpty())
        XRCCTRL(*this, "txtDir", wxTextCtrl)->SetValue(dir);
} // end of OnBrowseDir

void EditToolDlg::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        m_Tool->SetName(XRCCTRL(*this, "txtName", wxTextCtrl)->GetValue());
        m_Tool->SetCommand(XRCCTRL(*this, "txtCommand", wxTextCtrl)->GetValue());
        m_Tool->SetParams(XRCCTRL(*this, "txtParams", wxTextCtrl)->GetValue());
        m_Tool->SetWorkingDir(XRCCTRL(*this, "txtDir", wxTextCtrl)->GetValue());
        m_Tool->SetLaunchOption(static_cast<cbTool::eLaunchOption>(XRCCTRL(*this, "rbLaunchOptions", wxRadioBox)->GetSelection()));
    }

    wxScrollingDialog::EndModal(retCode);
} // end of EndModal
