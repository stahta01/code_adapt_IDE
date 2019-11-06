#ifndef EDITORCONFIGUI_H
#define EDITORCONFIGUI_H

//(*Headers(EditorConfigUI)
#include <wx/panel.h>
class wxBoxSizer;
class wxCheckBox;
class wxChoice;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxSpinEvent;
class wxStaticText;
//*)


class cbProject;
class EditorConfig;

#include "configurationpanel.h"

#include "EditorConfigCommon.h"

class EditorConfigUI : public cbConfigurationPanel
{
	public:
		EditorConfigUI(wxWindow* parent, EditorConfig* plugin, cbProject* prj,
                       const EditorSettings& es);
		virtual ~EditorConfigUI();

		//(*Declarations(EditorConfigUI)
		wxCheckBox* chkActive;
		wxCheckBox* chkTabIndents;
		wxCheckBox* chkUseTabs;
		wxChoice* choEOLMode;
		wxSpinCtrl* spnIndent;
		wxSpinCtrl* spnTabWidth;
		//*)

  virtual wxString GetTitle() const          { return _("EditorConfig options"); };
  virtual wxString GetBitmapBaseName() const { return _T("generic-plugin");      };

	protected:

		//(*Identifiers(EditorConfigUI)
		static const long ID_CHK_ACTIVE;
		static const long ID_CHK_USE_TABS;
		static const long ID_CHK_TAB_INDENTS;
		static const long ID_SPN_TAB_WIDTH;
		static const long ID_SPN_INDENT;
		static const long ID_CHO_EOL_MODE;
		//*)

        EditorConfig* m_Plugin;
        cbProject*    m_Project;

	private:

		//(*Handlers(EditorConfigUI)
		void OnActiveClick(wxCommandEvent& event);
		//*)

    virtual void OnApply();
    virtual void OnCancel() { ; }

		void DoActive(bool en);

		DECLARE_EVENT_TABLE()
};

#endif // EDITORCONFIGUI_H
