////////////////////////////////////////////////////////////////////////////
// Name:        wx/stc/stc.h
// Purpose:     A wxWidgets implementation of Scintilla.  This class is the
//              one meant to be used directly by wx applications.  It does not
//              derive directly from the Scintilla classes, and in fact there
//              is no mention of Scintilla classes at all in this header.
//              This class delegates all method calls and events to the
//              Scintilla objects and so forth.  This allows the use of
//              Scintilla without polluting the namespace with all the
//              classes and identifiers from Scintilla.
//
// Author:      Robin Dunn
//
// Created:     13-Jan-2000
// Copyright:   (c) 2000 by Total Control Software
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CA_STC_DEFINES_H_INCLUDED
#define CA_STC_DEFINES_H_INCLUDED

#define wxSTC_INVALID_POSITION -1

/// Define start of Scintilla messages to be greater than all Windows edit (EM_*) messages
/// as many EM_ messages can be used although that use is deprecated.
#define wxSTC_START 2000
#define wxSTC_OPTIONAL_START 3000
#define wxSTC_LEXER_START 4000
#define wxSTC_WS_INVISIBLE 0
#define wxSTC_WS_VISIBLEALWAYS 1
#define wxSTC_WS_VISIBLEAFTERINDENT 2
#define wxSTC_WS_VISIBLEONLYININDENT 3
#define wxSTC_TD_LONGARROW 0
#define wxSTC_TD_STRIKEOUT 1
#define wxSTC_EOL_CRLF 0
#define wxSTC_EOL_CR 1
#define wxSTC_EOL_LF 2

/// Styles in range 32..38 are predefined for parts of the UI and are not used as normal styles.
/// Style 39 is for future use.
#define wxSTC_STYLE_DEFAULT 32
#define wxSTC_STYLE_LINENUMBER 33
#define wxSTC_STYLE_BRACELIGHT 34
#define wxSTC_STYLE_BRACEBAD 35
#define wxSTC_STYLE_CONTROLCHAR 36
#define wxSTC_STYLE_INDENTGUIDE 37
#define wxSTC_STYLE_CALLTIP 38
#define wxSTC_STYLE_FOLDDISPLAYTEXT 39
#define wxSTC_STYLE_LASTPREDEFINED 39
#define wxSTC_STYLE_MAX 255

/// Maximum value of keywordSet parameter of SetKeyWords.
#define wxSTC_KEYWORDSET_MAX 8
#define wxSTC_TYPE_BOOLEAN 0
#define wxSTC_TYPE_INTEGER 1
#define wxSTC_TYPE_STRING 2

#endif // CA_STC_DEFINES_H_INCLUDED
