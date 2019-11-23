/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef IDE_ASSERT_H_INCLUDED
#define IDE_ASSERT_H_INCLUDED

#include "logassert.h"

/**
@brief Code::Blocks error handling unit.

Two macros are defined to help error handling in Code::Blocks:
cbAssert() and cbAssertNonFatal().
@note cbAssert() does nothing in release mode. For debug mode, compile with -DcbDEBUG
*/

#ifndef cbDEBUG
    #define cbAssert(expr)
    #define cbAssertNonFatal(expr)
#else

    // non-fatal assertion
    #define cbAssertNonFatal(expr) logAssertNonFatal(expr)
    #define cbAssert(expr) logAssert(expr)
#endif

#endif // IDE_ASSERT_H_INCLUDED
