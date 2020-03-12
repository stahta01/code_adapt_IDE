/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 10912 $
 * $Id: printdlg.cpp 10912 2016-09-25 16:10:13Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/src/printdlg.cpp $
 */

#include "sdk.h"
#ifndef WX_PRECOMP
    #include <wx/radiobox.h>
#endif
#ifndef CB_PRECOMP
    #include <wx/button.h>
    #include <wx/intl.h>
    #include <wx/checkbox.h>
    #include <wx/radiobox.h>
    #include <wx/string.h>
    #include <wx/xrc/xmlres.h>
    #include "cbeditor.h"
    #include "configmanager.h"
    #include "editormanager.h"
    #include "manager.h"
#endif
#include "cbstyledtextctrl.h"

#include "printdlg.h"

PrintDialog::PrintDialog(wxWindow* parent)
{
	//ctor
	wxXmlResource::Get()->LoadObject(this, parent, _T("dlgPrint"),_T("wxScrollingDialog"));
	XRCCTRL(*this, "wxID_OK", wxButton)->SetDefault();

	cbEditor* ed = Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor();
	if (ed)
	{
        bool hasSel = ed->GetControl()->GetSelectedText().Length();
        XRCCTRL(*this, "rbScope", wxRadioBox)->SetSelection(hasSel ? 0 : 1);
	}
	else
        XRCCTRL(*this, "rbScope", wxRadioBox)->SetSelection(1);

    int mode = Manager::Get()->GetConfigManager(_T("app"))->ReadInt(_T("/print_mode"), 1);
    XRCCTRL(*this, "rbColourMode", wxRadioBox)->SetSelection(mode);
    bool print_line_numbers = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/print_line_numbers"), true);
    XRCCTRL(*this, "chkLineNumbers", wxCheckBox)->SetValue(print_line_numbers);
}

PrintDialog::~PrintDialog()
{
	//dtor
}

PrintScope PrintDialog::GetPrintScope() const
{
    return (PrintScope)XRCCTRL(*this, "rbScope", wxRadioBox)->GetSelection();
}

PrintColourMode PrintDialog::GetPrintColourMode() const
{
    return (PrintColourMode)XRCCTRL(*this, "rbColourMode", wxRadioBox)->GetSelection();
}

bool PrintDialog::GetPrintLineNumbers() const
{
    return XRCCTRL(*this, "chkLineNumbers", wxCheckBox)->GetValue();
}

void PrintDialog::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        int mode = XRCCTRL(*this, "rbColourMode", wxRadioBox)->GetSelection();
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/print_mode"), (int)mode);
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/print_line_numbers"), GetPrintLineNumbers());
    }
    return wxScrollingDialog::EndModal(retCode);
}
