// ----------------------------------------------------------------------------
/*
	This file is part of Code Snippets, a plugin for Code::Blocks
	Copyright (C) 2007 Pecan Heber

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
// ----------------------------------------------------------------------------
// RCS-ID: $Id: version.h 11346 2018-03-24 21:29:44Z pecanh $

#ifndef VERSION_H
#define VERSION_H
// ---------------------------------------------------------------------------
// Logging / debugging
// ---------------------------------------------------------------------------
//debugging control
#include <wx/log.h>

#define LOGIT wxLogDebug
#if defined(LOGGING)
 #define LOGGING 1
 #undef LOGIT
 #define LOGIT wxLogMessage
 #define TRAP asm("int3")
#endif

// ----------------------------------------------------------------------------
   #if LOGGING
	extern wxLogWindow*    m_pLog;
   #endif
// ----------------------------------------------------------------------------
class AppVersion
// ----------------------------------------------------------------------------
{
    public:
        AppVersion();
       ~AppVersion();

    wxString GetVersion(){return m_version;}

    wxString m_version;

    protected:
    private:
};

#include <wx/string.h>
//-----Release-Feature-Fix------------------
#define VERSION wxT("1.4.3 2018/03/24")
//------------------------------------------
// Release - Current development level
// Feature - User interface level
// Fix     - bug fix or non UI breaking addition
#endif // VERSION_H

