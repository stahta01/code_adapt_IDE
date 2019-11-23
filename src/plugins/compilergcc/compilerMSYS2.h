/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef COMPILER_MSYS2_H
#define COMPILER_MSYS2_H

#include "compilerMINGW.h"

class CompilerMSYS2 : public CompilerMINGW
{
    public:
        CompilerMSYS2(wxString arch);
        ~CompilerMSYS2();
        virtual AutoDetectResult AutoDetectInstallationDir();
    protected:
        virtual Compiler* CreateCopy();
        wxString m_Arch;
    private:

};

#endif // COMPILER_MSYS2_H
