/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef FRAME_H
#define FRAME_H

#include "nativeparser_test.h"


//(*Headers(CCTestFrame)
#include "wx/wxscintilla.h"
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

#include <wx/fdrepdlg.h>

class wxProgressDialog;

class CCTestFrame : public wxFrame
{
public:
    CCTestFrame(const wxString& main_file);
    virtual ~CCTestFrame();

    void AppendToLog(const wxString& log);

    // copy the include search paths and macro replacement rules to the Parser
    // and run the cctest in each file. (currently the file has cc_*.cpp or ccc_*.cpp)
    void Start();

protected:
    //(*Identifiers(CCTestFrame)
    static const long ID_CHK_HIDE;
    static const long wxID_TEST_SINGLE;
    static const long wxID_PARSE;
    static const long wxID_PRINT_TREE;
    static const long wxID_SAVE_TEST_RESULT;
    static const long wxID_TOKEN;
    //*)

private:
    // initialize the wxScintilla control
    void InitControl();
    // load the source file content to wxScintilla control
    void LoadToControl();
    void SetMarkerStyle(int marker, int markerType, wxColor fore, wxColor back);

    //(*Handlers(CCTestFrame)
    void OnMenuQuitSelected(wxCommandEvent& event);
    void OnMenuSaveSelected(wxCommandEvent& event);
    void OnMenuOpenSelected(wxCommandEvent& event);
    void OnMenuFindSelected(wxCommandEvent& event);
    void OnMenuReparseSelected(wxCommandEvent& event);
    void OnMenuTokenSelected(wxCommandEvent& event);
    void OnMenuAboutSelected(wxCommandEvent& event);
    void OnParse(wxCommandEvent& event);
    void OnPrintTree(wxCommandEvent& event);
    void OnTestSingle(wxCommandEvent& event);
    void OnSaveTestResultClick(wxCommandEvent& event);
    //*)

    void OnMarginClick(wxScintillaEvent& event);
    void OnFindDialog(wxFindDialogEvent& event);
    void OnCCLogger(wxCommandEvent& event);
    void OnCCAddToken(wxCommandEvent& event);


    //(*Declarations(CCTestFrame)
    wxButton* btnParse;
    wxButton* btnPrintTree;
    wxButton* btnSaveTestResult;
    wxButton* btnTestSingle;
    wxCheckBox* m_DoHideCtrl;
    wxCheckBox* m_DoTreeCtrl;
    wxFileDialog* m_OpenFile;
    wxFileDialog* m_SaveFile;
    wxNotebook* m_ParserCtrl;
    wxPanel* panCompletionTest;
    wxScintilla* m_Control;
    wxStatusBar* m_StatuBar;
    wxTextCtrl* m_CompletionTestCtrl;
    wxTextCtrl* m_IncludeCtrl;
    wxTextCtrl* m_LogCtrl;
    wxTextCtrl* m_TreeCtrl;
    //*)

    wxProgressDialog*    m_ProgDlg;
    // the source file going to parse
    wxString             m_MainFile;
    wxString             m_CurrentFile;
    size_t               m_LogCount;

    wxFindReplaceData    m_FRData;
    wxFindReplaceDialog* m_FRDlg;
    int                  m_LastIndex;

    /** main testing class, derived from NativeParserBase class */
    NativeParserTest m_NativeParser;

    DECLARE_EVENT_TABLE()
};

#endif
