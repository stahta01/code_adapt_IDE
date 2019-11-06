/***************************************************************
 * Name:      SearchInPanel
 *
 * Purpose:   This class is a panel that allows the user to
 *            define the search scope : open files, project,
 *            worspace or directory.
 *            It is used in the ThreadSearchView and the
 *            ThreadSearchConfPanel.
 *            It does nothing but forwarding events to the
 *            parent window.
 *
 * Author:    Jerome ANTOINE
 * Created:   2007-10-08
 * Copyright: Jerome ANTOINE
 * License:   GPL
 **************************************************************/

#include "sdk.h"
#ifndef CB_PRECOMP
    #include <wx/bitmap.h>
    #include <wx/bmpbuttn.h>
    #include <wx/checkbox.h>
    #include <wx/sizer.h>
    #include "configmanager.h"
#endif

#include "wx/things/toggle.h"
#include "wx/tglbtn.h"

#include "SearchInPanel.h"
#include "ThreadSearchCommon.h"
#include "ThreadSearchControlIds.h"


SearchInPanel::SearchInPanel(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long WXUNUSED(style)):
    wxPanel(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    const wxString &prefix = GetImagePrefix(false, parent);
    const double scaleFactor = cbGetContentScaleFactor(*parent);

    // create a dummy button to get the standard button-size,
    // wxCustomButton does not do that properly
    // we have to force this size as MinSize to make it work
    wxBitmapButton dummyBtn(this, wxID_ANY, cbLoadBitmapScaled(prefix + wxT("openfiles.png"),
                                                               wxBITMAP_TYPE_PNG, scaleFactor));
    wxSize dummySize = dummyBtn.GetSize();

    m_pBtnSearchOpenFiles = new wxCustomButton(this,
                                               controlIDs.Get(ControlIDs::idBtnSearchOpenFiles),
                                               cbLoadBitmapScaled(prefix + wxT("openfiles.png"),
                                                                  wxBITMAP_TYPE_PNG, scaleFactor),
                                               wxDefaultPosition, dummySize);
    m_pBtnSearchOpenFiles->SetBitmapDisabled(cbLoadBitmapScaled(prefix + wxT("openfilesdisabled.png"),
                                                                wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchOpenFiles->SetBitmapSelected(cbLoadBitmapScaled(prefix + wxT("openfilesselected.png"),
                                                                wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchOpenFiles->SetMinSize(dummySize);
    m_pBtnSearchTargetFiles = new wxCustomButton(this, controlIDs.Get(ControlIDs::idBtnSearchTargetFiles),
                                                 cbLoadBitmapScaled(prefix + wxT("target.png"),
                                                                    wxBITMAP_TYPE_PNG, scaleFactor),
                                                 wxDefaultPosition, dummySize);
    m_pBtnSearchTargetFiles->SetBitmapDisabled(cbLoadBitmapScaled(prefix + wxT("targetdisabled.png"),
                                                                  wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchTargetFiles->SetBitmapSelected(cbLoadBitmapScaled(prefix + wxT("targetselected.png"),
                                                                  wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchTargetFiles->SetMinSize(dummySize);
    m_pBtnSearchProjectFiles = new wxCustomButton(this, controlIDs.Get(ControlIDs::idBtnSearchProjectFiles),
                                                  cbLoadBitmapScaled(prefix + wxT("project.png"),
                                                                     wxBITMAP_TYPE_PNG,
                                                                     scaleFactor),
                                                  wxDefaultPosition, dummySize);
    m_pBtnSearchProjectFiles->SetBitmapDisabled(cbLoadBitmapScaled(prefix + wxT("projectdisabled.png"),
                                                                   wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchProjectFiles->SetBitmapSelected(cbLoadBitmapScaled(prefix + wxT("projectselected.png"),
                                                                   wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchProjectFiles->SetMinSize(dummySize);
    m_pBtnSearchWorkspaceFiles = new wxCustomButton(this, controlIDs.Get(ControlIDs::idBtnSearchWorkspaceFiles),
                                                    cbLoadBitmapScaled(prefix + wxT("workspace.png"),
                                                                       wxBITMAP_TYPE_PNG,
                                                                       scaleFactor),
                                                    wxDefaultPosition, dummySize);
    m_pBtnSearchWorkspaceFiles->SetBitmapDisabled(cbLoadBitmapScaled(prefix + wxT("workspacedisabled.png"),
                                                                     wxBITMAP_TYPE_PNG,
                                                                     scaleFactor));
    m_pBtnSearchWorkspaceFiles->SetBitmapSelected(cbLoadBitmapScaled(prefix + wxT("workspaceselected.png"),
                                                                     wxBITMAP_TYPE_PNG,
                                                                     scaleFactor));
    m_pBtnSearchWorkspaceFiles->SetMinSize(dummySize);
    m_pBtnSearchDir = new wxCustomButton(this, controlIDs.Get(ControlIDs::idBtnSearchDirectoryFiles),
                                         cbLoadBitmapScaled(prefix + wxT("folder.png"),
                                                            wxBITMAP_TYPE_PNG, scaleFactor),
                                         wxDefaultPosition, dummySize);
    m_pBtnSearchDir->SetBitmapDisabled(cbLoadBitmapScaled(prefix + wxT("folderdisabled.png"),
                                                          wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchDir->SetBitmapSelected(cbLoadBitmapScaled(prefix + wxT("folderselected.png"),
                                                          wxBITMAP_TYPE_PNG, scaleFactor));
    m_pBtnSearchDir->SetMinSize(dummySize);

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(SearchInPanel, wxPanel)
    // begin wxGlade: SearchInPanel::event_table
    EVT_TOGGLEBUTTON(controlIDs.Get(ControlIDs::idBtnSearchOpenFiles), SearchInPanel::OnBtnClickEvent)
    EVT_TOGGLEBUTTON(controlIDs.Get(ControlIDs::idBtnSearchTargetFiles), SearchInPanel::OnBtnSearchTargetFilesClick)
    EVT_TOGGLEBUTTON(controlIDs.Get(ControlIDs::idBtnSearchProjectFiles), SearchInPanel::OnBtnSearchProjectFilesClick)
    EVT_TOGGLEBUTTON(controlIDs.Get(ControlIDs::idBtnSearchWorkspaceFiles), SearchInPanel::OnBtnSearchWorkspaceFilesClick)
    EVT_TOGGLEBUTTON(controlIDs.Get(ControlIDs::idBtnSearchDirectoryFiles), SearchInPanel::OnBtnClickEvent)
    // end wxGlade
END_EVENT_TABLE();


void SearchInPanel::OnBtnClickEvent(wxCommandEvent &event)
{
    event.Skip();
}


void SearchInPanel::OnBtnSearchTargetFilesClick(wxCommandEvent &event)
{
    // If target scope becomes checked, we uncheck if necessary project
    // and workspace.
    if(event.GetInt())
    {
        SetSearchInProjectFiles(false);
        SetSearchInWorkspaceFiles(false);
    }
    event.Skip();
}


void SearchInPanel::OnBtnSearchProjectFilesClick(wxCommandEvent &event)
{
    // If project scope becomes checked, we uncheck if necessary target
    // and workspace.
    if (event.GetInt())
    {
        SetSearchInTargetFiles(false);
        SetSearchInWorkspaceFiles(false);
    }
    event.Skip();
}


void SearchInPanel::OnBtnSearchWorkspaceFilesClick(wxCommandEvent &event)
{
    // If workspace scope becomes checked, we uncheck if necessary target
    // and project.
    if (event.GetInt())
    {
        SetSearchInTargetFiles(false);
        SetSearchInProjectFiles(false);
    }
    event.Skip();
}


// wxGlade: add SearchInPanel event handlers


void SearchInPanel::set_properties()
{
    // begin wxGlade: SearchInPanel::set_properties
    m_pBtnSearchOpenFiles->SetToolTip(_("Search in open files"));
    m_pBtnSearchTargetFiles->SetToolTip(_("Search in target files"));
    m_pBtnSearchProjectFiles->SetToolTip(_("Search in project files"));
    m_pBtnSearchWorkspaceFiles->SetToolTip(_("Search in workspace files"));
    m_pBtnSearchDir->SetToolTip(_("Search in directory files"));
    // end wxGlade
}


void SearchInPanel::do_layout()
{
#if wxCHECK_VERSION(3, 0, 0)
    #define wxADJUST_MINSIZE 0
#endif
    // begin wxGlade: SearchInPanel::do_layout
    wxBoxSizer* SizerTop = new wxBoxSizer(wxHORIZONTAL);
    SizerTop->Add(m_pBtnSearchOpenFiles, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 4);
    SizerTop->Add(m_pBtnSearchTargetFiles, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 4);
    SizerTop->Add(m_pBtnSearchProjectFiles, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 4);
    SizerTop->Add(m_pBtnSearchWorkspaceFiles, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 4);
    SizerTop->Add(m_pBtnSearchDir, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 4);
    SetAutoLayout(true);
    SetSizer(SizerTop);
    SizerTop->Fit(this);
    SizerTop->SetSizeHints(this);
    // end wxGlade
}


//{ Getters
bool SearchInPanel::GetSearchInOpenFiles()      const {return m_pBtnSearchOpenFiles->GetValue();}
bool SearchInPanel::GetSearchInTargetFiles()    const {return m_pBtnSearchTargetFiles->GetValue();}
bool SearchInPanel::GetSearchInProjectFiles()   const {return m_pBtnSearchProjectFiles->GetValue();}
bool SearchInPanel::GetSearchInWorkspaceFiles() const {return m_pBtnSearchWorkspaceFiles->GetValue();}
bool SearchInPanel::GetSearchInDirectory()      const {return m_pBtnSearchDir->GetValue();}
//}

//{ Setters
void SearchInPanel::SetSearchInOpenFiles(bool bSearchInOpenFiles)
{
    m_pBtnSearchOpenFiles->SetValue(bSearchInOpenFiles);
}
void SearchInPanel::SetSearchInTargetFiles(bool bSearchInTargetFiles)
{
    m_pBtnSearchTargetFiles->SetValue(bSearchInTargetFiles);
}
void SearchInPanel::SetSearchInProjectFiles(bool bSearchInProjectFiles)
{
    m_pBtnSearchProjectFiles->SetValue(bSearchInProjectFiles);
}
void SearchInPanel::SetSearchInWorkspaceFiles(bool bSearchInWorkspaceFiles)
{
    m_pBtnSearchWorkspaceFiles->SetValue(bSearchInWorkspaceFiles);
}
void SearchInPanel::SetSearchInDirectory(bool bSearchInDirectoryFiles)
{
    m_pBtnSearchDir->SetValue(bSearchInDirectoryFiles);
}
//}
