#ifndef EXPORTER_H
#define EXPORTER_H


#include <cbplugin.h> // the base class we 're inheriting
#include <settings.h> // needed to use the Code::Blocks SDK

#include "BaseExporter.h"

class Exporter : public cbPlugin
{
	public:
		Exporter();
		~Exporter();
    void BuildMenu(wxMenuBar *menuBar);
//		int Configure() { return 0; }
		void OnAttach(); // fires when the plugin is attached to the application
		void OnRelease(bool appShutDown); // fires when the plugin is released from the application
    void OnExportHTML(wxCommandEvent &event);
    void OnExportRTF(wxCommandEvent &event);
    void OnExportODT(wxCommandEvent &event);
    void OnExportPDF(wxCommandEvent &event);
    void ExportFile(BaseExporter *exp, const wxString &default_extension, const wxString &wildcard);
    void OnUpdateUI(wxUpdateUIEvent &event);
  private:
    void BuildModuleMenu(const ModuleType /*type*/, wxMenu * /*menu*/, const FileTreeData* /*data*/ = 0) {}
    bool BuildToolBar(wxToolBar * /*toolBar*/) { return false; }
    void RemoveToolBar(wxToolBar * /*toolBar*/) {}

    DECLARE_EVENT_TABLE();
};

#endif // EXPORTER_H
