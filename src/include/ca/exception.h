/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef CA_EXCEPTION_H_INCLUDED
#define CA_EXCEPTION_H_INCLUDED

#include <wx/string.h>
#include <wx/log.h> // for wxSafeShowMessage()

#include "globals.h" // for cbC2U()

/**
@brief Code::Blocks error handling unit.

One macros is defined to help error handling in Code::Blocks:
caThrow().
*/

/** @brief The base Code::Blocks exception object. */
class DLLIMPORT caException
{
    public:
        caException(const wxString& msg, const wxString& file, int line);
        virtual ~caException();

        /** @brief Display exception error message.
          * @param safe If true, wxSafeShowMessage will be used to display the error,
          *             else a normal message box will be used.
          */
        void ShowErrorMessage(bool safe = true);

        // public members
        wxString Message; ///< The exception's error message.
        wxString File; ///< The file where the exception was raised.
        int Line; ///< The line in the file where the exception was raised.
};

#if wxUSE_UNICODE
    #define caThrow(message) throw caException(message, cbC2U(__FILE__), __LINE__)
#else
    #define caThrow(message) throw caException(message, __FILE__, __LINE__)
#endif

#endif // CA_EXCEPTION_H_INCLUDED
