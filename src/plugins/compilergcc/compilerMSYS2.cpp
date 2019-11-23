/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 */

#include "sdk.h"         // Precompiled Header needs to be the first include
#include "compilerMSYS2.h"
#include <wx/filefn.h>

CompilerMSYS2::CompilerMSYS2(wxString arch)
    : CompilerMINGW(wxS("MSYS2 ") + arch + wxS(" GCC"), wxS("msys2") + arch + wxS("-gcc"))
{
    m_Weight = 29;
    m_Arch = arch;
    Reset();
}

CompilerMSYS2::~CompilerMSYS2()
{
}

Compiler * CompilerMSYS2::CreateCopy()
{
    return (new CompilerMSYS2(*this));
}

AutoDetectResult CompilerMSYS2::AutoDetectInstallationDir()
{
    AutoDetectResult ret = adrGuessed;
    m_MasterPath = _T("C:\\msys64"); // just a guess
    wxString tempMasterPath(m_MasterPath);
    bool validInstallationDir = false;

    if (!validInstallationDir)
        return ret;

    wxString cProgramDir = tempMasterPath + wxFILE_SEP_PATH + _T("bin") + wxFILE_SEP_PATH;
    wxString cProgramFullname = cProgramDir + m_Programs.C;
    if ( !wxFileExists(cProgramFullname) )
        return ret;

    wxFile pfFile(cProgramFullname);
    if ( !pfFile.IsOpened() )
       return ret;

    return ret;
}
