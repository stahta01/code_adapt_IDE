///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "ConfigPanel.h"

///////////////////////////////////////////////////////////////////////////

ConfigPanel::ConfigPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("BrowseTracker Options"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Tahoma") ) );

	bSizer3->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( 0, 10, 0, 0, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	Cfg_BrowseMarksEnabled = new wxCheckBox( this, wxID_ANY, wxT("Enable BookMark Tracking"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( Cfg_BrowseMarksEnabled, 1, wxALL, 5 );

	Cfg_WrapJumpEntries = new wxCheckBox( this, wxID_ANY, wxT("Wrap Jump Entries"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( Cfg_WrapJumpEntries, 1, wxALL, 5 );

	Cfg_ShowToolbar = new wxCheckBox( this, wxID_ANY, wxT("Show Tool bar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( Cfg_ShowToolbar, 0, wxALL, 5 );


	bSizer3->Add( bSizer7, 0, wxEXPAND|wxSHAPED, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	wxString Cfg_ToggleKeyChoices[] = { wxT("Left_Mouse"), wxT("Ctrl-Left_Mouse") };
	int Cfg_ToggleKeyNChoices = sizeof( Cfg_ToggleKeyChoices ) / sizeof( wxString );
	Cfg_ToggleKey = new wxRadioBox( this, wxID_ANY, wxT("Toggle BookMark Key"), wxDefaultPosition, wxDefaultSize, Cfg_ToggleKeyNChoices, Cfg_ToggleKeyChoices, 3, wxRA_SPECIFY_COLS );
	Cfg_ToggleKey->SetSelection( 1 );
	bSizer8->Add( Cfg_ToggleKey, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer8, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT(" Left_Mouse delay before BookMark Toggle (Milliseconds)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer9->Add( m_staticText4, 0, wxALL|wxEXPAND, 5 );

	Cfg_LeftMouseDelay = new wxSlider( this, wxID_ANY, 200, 0, 1000, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_HORIZONTAL|wxSL_LABELS );
	bSizer9->Add( Cfg_LeftMouseDelay, 1, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer9, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxString Cfg_ClearAllKeyChoices[] = { wxT("Ctrl-Left_Mouse"), wxT("Ctrl-Left_DblClick") };
	int Cfg_ClearAllKeyNChoices = sizeof( Cfg_ClearAllKeyChoices ) / sizeof( wxString );
	Cfg_ClearAllKey = new wxRadioBox( this, wxID_ANY, wxT("Clear All BookMarks"), wxDefaultPosition, wxDefaultSize, Cfg_ClearAllKeyNChoices, Cfg_ClearAllKeyChoices, 2, wxRA_SPECIFY_COLS );
	Cfg_ClearAllKey->SetSelection( 0 );
	bSizer10->Add( Cfg_ClearAllKey, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer10, 1, wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Note: The Ctrl-Left_Mouse key options are disabled when\nthe editors multi-selection option is enabled at:\nSettings/Editor/Margins/Allow Multiple Selections\n\nMenu items can be used for additional BrowseTracker functions.\n(MainMenu/View/BrowseTracker)\n"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer3->Add( m_staticText3, 0, wxALL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();

	// Connect Events
	Cfg_BrowseMarksEnabled->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ConfigPanel::OnEnableBrowseMarks ), NULL, this );
	Cfg_WrapJumpEntries->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ConfigPanel::OnWrapJumpEntries ), NULL, this );
	Cfg_ShowToolbar->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ConfigPanel::OnShowToolbar ), NULL, this );
	Cfg_ToggleKey->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ConfigPanel::OnToggleBrowseMarkKey ), NULL, this );
	Cfg_ClearAllKey->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ConfigPanel::OnClearAllBrowseMarksKey ), NULL, this );
}

ConfigPanel::~ConfigPanel()
{
	// Disconnect Events
	Cfg_BrowseMarksEnabled->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ConfigPanel::OnEnableBrowseMarks ), NULL, this );
	Cfg_WrapJumpEntries->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ConfigPanel::OnWrapJumpEntries ), NULL, this );
	Cfg_ShowToolbar->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ConfigPanel::OnShowToolbar ), NULL, this );
	Cfg_ToggleKey->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ConfigPanel::OnToggleBrowseMarkKey ), NULL, this );
	Cfg_ClearAllKey->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ConfigPanel::OnClearAllBrowseMarksKey ), NULL, this );

}
