/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef _PARSE_WATCH_VALUE_H_
#define _PARSE_WATCH_VALUE_H_

#include "debugger_defs.h"

cb::shared_ptr<GDBWatch> AddChild(cb::shared_ptr<GDBWatch> parent, wxString const &str_name);

bool ParseGDBWatchValue(cb::shared_ptr<GDBWatch> watch, wxString const &value);
bool ParseCDBWatchValue(cb::shared_ptr<GDBWatch> watch, wxString const &value);

struct GDBLocalVariable
{
    GDBLocalVariable(wxString const &nameValue, size_t start, size_t length);

    wxString name, value;
    bool error;
};


void TokenizeGDBLocals(std::vector<GDBLocalVariable> &results, wxString const &value);

/// Parse a line returned by the examine memory command.
/// @return true on success and false on failure. Upon success resultAddr and resultValues
/// have valid values. On failure they are empty.
bool ParseGDBExamineMemoryLine(wxString &resultAddr, std::vector<uint8_t> &resultValues,
                               const wxString &outputLine);

#endif // _PARSE_WATCH_VALUE_H_
