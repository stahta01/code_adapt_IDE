/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef IDE_LOGASSERT_H_INCLUDED
#define IDE_LOGASSERT_H_INCLUDED

#include <wx/string.h>
#include <wx/log.h> // for wxSafeShowMessage()

#include "globals.h" // for cbC2U()

    // In unix we use kill to terminate the application, that makes gdb
    // keep it alive which makes debugging easier.
    // (thanks go to an unknown author)
    #ifdef __WINDOWS__
        #define DIE() exit(1)
    #else
        #include <csignal>
        #define DIE() kill(getpid(), SIGINT)
    #endif

    #if wxUSE_UNICODE
        #define logAssertMessage(expr) \
            wxString err; \
            err.Printf(_T("Assertion failed in %s at %s:%d.\n\n%s"), cbC2U(__PRETTY_FUNCTION__).wx_str(), cbC2U(__FILE__).c_str(), __LINE__, cbC2U(#expr).c_str());
    #else
        #define logAssertMessage(expr) \
            wxString err; \
            err.Printf(_T("Assertion failed in %s at %s:%d.\n\n%s"), __PRETTY_FUNCTION__, __FILE__, __LINE__, #expr);
    #endif

    // non-fatal assertion
    #define logAssertNonFatal(expr) \
        if (!(expr)) \
        { \
            logAssertMessage(expr); \
            wxSafeShowMessage(_T("Assertion error"), err); \
        }

    // fatal assertion
    #define logAssert(expr) \
        if (!(expr)) \
        { \
            logAssertMessage(expr); \
            wxSafeShowMessage(_T("Fatal assertion error"), err); \
            DIE(); \
        }

#endif // IDE_LOGASSERT_H_INCLUDED
