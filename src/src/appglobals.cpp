/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 11901 $
 * $Id: appglobals.cpp 11901 2019-11-04 19:35:26Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/src/appglobals.cpp $
 */

#include <sdk.h>
#ifndef CB_PRECOMP
    #include <wx/utils.h>
    #include <wx/intl.h>
    #include "configmanager.h"
#endif
#include <branding.h>
#include "cbplugin.h"
#include "appglobals.h"

namespace appglobals
{
    const wxString AppVendor             = wxT_2(BRANDING_APP_NAME_FANCY);
    const wxString AppName               = wxT_2(BRANDING_APP_NAME_FANCY);

#if SVN_BUILD
    const wxString AppVersion            = _T("svn build");
    const wxString AppActualVersionVerb  = _T("svn build  rev ")           + ConfigManager::GetRevisionString();
    const wxString AppActualVersion      = _T("svn-r")                     + ConfigManager::GetRevisionString();
#else
    const wxString AppVersion            = _T(RELEASE);
    const wxString AppActualVersionVerb  = _T("Release " RELEASE "  rev ") + ConfigManager::GetRevisionString();
    const wxString AppActualVersion      = _T(RELEASE "-r")                + ConfigManager::GetRevisionString();
#endif

    const wxString AppSDKVersion         = wxString::Format(wxT("%d.%d.%d"),
                                                            static_cast<int>(PLUGIN_SDK_VERSION_MAJOR),
                                                            static_cast<int>(PLUGIN_SDK_VERSION_MINOR),
                                                            static_cast<int>(PLUGIN_SDK_VERSION_RELEASE));

    const wxString AppUrl                = _T("http://www.codeblocks.org");
    const wxString AppContactEmail       = wxT_2(BRANDING_EMAIL_CONTACT);

#if defined(__WINDOWS__)
    const wxString AppPlatform           = _T("Windows");
#elif defined(__WXOS2__)
    const wxString AppPlatform           = _T("OS/2");
#elif defined(__WXMAC__) || defined(__WXCOCOA__)
    const wxString AppPlatform           = _T("Mac OS X");
#elif defined(__APPLE__)
    const wxString AppPlatform           = _T("Darwin");
#elif defined(__FreeBSD__)
    const wxString AppPlatform           = _T("FreeBSD");
#elif defined(__UNIX__)
    const wxString AppPlatform           = _T("Linux");
#else
    const wxString AppPlatform           = _T("Unknown");
#endif

    const wxString AppWXAnsiUnicode      = platform::unicode ? wxT("unicode") : wxT("ANSI");

#if defined(_LP64) || defined(_WIN64)
    const wxString bit_type              = wxT(" - 64 bit");
#else
    const wxString bit_type              = wxT(" - 32 bit");
#endif

    const wxString AppBuildTimestamp     = (  wxString(wxT(__DATE__)) + wxT(", ")
                                            + wxT(__TIME__) + wxT(" - wx")
                                            + wxString(wxT(wxVERSION_NUM_DOT_STRING))
#if defined(__clang__)
                                            + wxString::Format(wxT(" - clang %d.%d.%d"),
                                                               __clang_major__, __clang_minor__, __clang_patchlevel__)
#elif defined(__GNUC__)
                                            + wxT(" - gcc ") + (wxString() << __GNUC__)
                                            + wxT(".")       + (wxString() << __GNUC_MINOR__)
                                            + wxT(".")       + (wxString() << __GNUC_PATCHLEVEL__)
#endif
                                            + wxT(" (") + AppPlatform + wxT(", ")
                                            + AppWXAnsiUnicode + wxT(")") + bit_type );

    const wxString DefaultBatchBuildArgs = _T("-na -nd -ns --batch-build-notify");
}
namespace cbHelpers
{

/// Read the toolbar size setting from config.
/// We store the value selected by the user without applying the scale factor.
/// There are only 4 allow values to choose from.
///
/// These are the allowed values (1x column) and their values after the scale factor is applied.
/// |-------|-----|-----|-----|-----|-----|-----|-----|
/// |       |1x   |1.25x|1.5x |1.75 |2x   |2.5x |3x   |
/// |-------|-----|-----|-----|-----|-----|-----|-----|
/// |Normal |16   |20   |24   |28   |32   |40   |48   |
/// |Large  |24   |28   |32   |40   |48   |56   |64   |
/// |Larger |32   |40   |48   |56   |64   |64   |64   |
/// |Largest|64   |64   |64   |64   |64   |64   |64   |
/// |-------|-----|-----|-----|-----|-----|-----|-----|
///
int ReadToolbarSizeFromConfig()
{
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("app"));

    int size = defaultToolbarSize;
    if (!cfg->Read(_T("/environment/toolbar_size"), &size))
    {
        bool smallSize = true;
        if (cfg->Read(_T("/environment/toolbar_size"), &smallSize))
            size = (smallSize ? 16 : 24);
    }
    if (size == 22)
        size = 24;
    const int possibleSizes[] = { 16, 24, 32, 64 };
    return cbFindMinSize(size, possibleSizes, cbCountOf(possibleSizes));
}

} // namespace cbHelpers
