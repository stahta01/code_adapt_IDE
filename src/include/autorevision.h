/*0*/
//don't include this header, only configmanager-revision.cpp should do this.
#ifndef AUTOREVISION_H
#define AUTOREVISION_H


#include <wx/string.h>

namespace autorevision
{
	const unsigned int svn_revision = 0;
	const wxString svnRevision(_T("0"));
	const wxString svnDate(_T("unknown date"));
}

#endif
