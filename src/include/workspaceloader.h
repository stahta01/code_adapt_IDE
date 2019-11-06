/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef WORKSPACELOADER_H
#define WORKSPACELOADER_H

#include "ibaseworkspaceloader.h"

#include "settings.h" // DLLIMPORT

#define WORKSPACE_LAYOUT_FILE_VERSION_MAJOR 1
#define WORKSPACE_LAYOUT_FILE_VERSION_MINOR 0

class DLLIMPORT WorkspaceLoader : public IBaseWorkspaceLoader
{
    public:
        WorkspaceLoader();
        ~WorkspaceLoader() override;

        bool Open(const wxString& filename, wxString& Title) override;
        bool Save(const wxString& title, const wxString& filename) override;

        bool SaveLayout(const wxString& filename);
        bool LoadLayout(const wxString& filename);
};

#endif // WORKSPACELOADER_H
