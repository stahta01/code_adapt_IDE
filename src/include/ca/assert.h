/*
 * This file is part of the CodeAdapt IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef CA_ASSERT_H_INCLUDED
#define CA_ASSERT_H_INCLUDED

#include "ca/logassert.h"

/**
@brief CodeAdapt error handling unit.

Two macros are defined to help error handling in CodeAdapt:
caAssert() and caAssertNonFatal().
@note caAssert() does nothing in release mode. For debug mode, compile with -DcaDEBUG
*/

#ifndef caDEBUG
    #define caAssert(expr)
    #define caAssertNonFatal(expr)
#else

    // non-fatal assertion
    #define caAssertNonFatal(expr) logAssertNonFatal(expr)
    #define caAssert(expr) logAssert(expr)
#endif

#endif // CA_ASSERT_H_INCLUDED
