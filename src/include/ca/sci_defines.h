////////////////////////////////////////////////////////////////////////////
// Name:        sci_defines.h part of wx/stc/stc.h
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

#ifndef STC_DEFINES_H_INCLUDED
#define STC_DEFINES_H_INCLUDED

#define wxSCINTILLA_VERSION _T("3.75.0")

//----------------------------------------------------------------------
// SCI constants generated section {{{

#define wxSCI_INVALID_POSITION -1

/// Define start of Scintilla messages to be greater than all Windows edit (EM_*) messages
/// as many EM_ messages can be used although that use is deprecated.
#define wxSCI_START 2000
#define wxSCI_OPTIONAL_START 3000
#define wxSCI_LEXER_START 4000
#define wxSCI_WS_INVISIBLE 0
#define wxSCI_WS_VISIBLEALWAYS 1
#define wxSCI_WS_VISIBLEAFTERINDENT 2
#define wxSCI_WS_VISIBLEONLYININDENT 3
#define wxSCI_TD_LONGARROW 0
#define wxSCI_TD_STRIKEOUT 1
#define wxSCI_EOL_CRLF 0
#define wxSCI_EOL_CR 1
#define wxSCI_EOL_LF 2

/// The SC_CP_UTF8 value can be used to enter Unicode mode.
/// This is the same value as CP_UTF8 in Windows
#define wxSCI_CP_UTF8 65001
#define wxSCI_IME_WINDOWED 0
#define wxSCI_IME_INLINE 1
#define wxSCI_MARKER_MAX 31
#define wxSCI_MARK_CIRCLE 0
#define wxSCI_MARK_ROUNDRECT 1
#define wxSCI_MARK_ARROW 2
#define wxSCI_MARK_SMALLRECT 3
#define wxSCI_MARK_SHORTARROW 4
#define wxSCI_MARK_EMPTY 5
#define wxSCI_MARK_ARROWDOWN 6
#define wxSCI_MARK_MINUS 7
#define wxSCI_MARK_PLUS 8

/// Shapes used for outlining column.
#define wxSCI_MARK_VLINE 9
#define wxSCI_MARK_LCORNER 10
#define wxSCI_MARK_TCORNER 11
#define wxSCI_MARK_BOXPLUS 12
#define wxSCI_MARK_BOXPLUSCONNECTED 13
#define wxSCI_MARK_BOXMINUS 14
#define wxSCI_MARK_BOXMINUSCONNECTED 15
#define wxSCI_MARK_LCORNERCURVE 16
#define wxSCI_MARK_TCORNERCURVE 17
#define wxSCI_MARK_CIRCLEPLUS 18
#define wxSCI_MARK_CIRCLEPLUSCONNECTED 19
#define wxSCI_MARK_CIRCLEMINUS 20
#define wxSCI_MARK_CIRCLEMINUSCONNECTED 21

/// Invisible mark that only sets the line background colour.
#define wxSCI_MARK_BACKGROUND 22
#define wxSCI_MARK_DOTDOTDOT 23
#define wxSCI_MARK_ARROWS 24
#define wxSCI_MARK_PIXMAP 25
#define wxSCI_MARK_FULLRECT 26
#define wxSCI_MARK_LEFTRECT 27
#define wxSCI_MARK_AVAILABLE 28
#define wxSCI_MARK_UNDERLINE 29
#define wxSCI_MARK_RGBAIMAGE 30
#define wxSCI_MARK_BOOKMARK 31
#define wxSCI_MARK_CHARACTER 10000

/* C::B begin */
#define wxSCI_MARKNUM_LASTUNUSED 22
/* C::B end */
/* CHANGEBAR begin */
// Markers used for outlining and changed column.
#define wxSCI_MARKNUM_CHANGEUNSAVED 23
#define wxSCI_MARKNUM_CHANGESAVED 24
/* CHANGEBAR end */
#define wxSCI_MARKNUM_FOLDEREND 25
#define wxSCI_MARKNUM_FOLDEROPENMID 26
#define wxSCI_MARKNUM_FOLDERMIDTAIL 27
#define wxSCI_MARKNUM_FOLDERTAIL 28
#define wxSCI_MARKNUM_FOLDERSUB 29
#define wxSCI_MARKNUM_FOLDER 30
#define wxSCI_MARKNUM_FOLDEROPEN 31
/* CHANGEBAR begin */
#define wxSCI_MASK_FOLDERS 0xFF800000
/* CHANGEBAR end */
#define wxSCI_MAX_MARGIN 4
#define wxSCI_MARGIN_SYMBOL 0
#define wxSCI_MARGIN_NUMBER 1
#define wxSCI_MARGIN_BACK 2
#define wxSCI_MARGIN_FORE 3
#define wxSCI_MARGIN_TEXT 4
#define wxSCI_MARGIN_RTEXT 5
#define wxSCI_MARGIN_COLOUR 6
/* CHANGEBAR begin */
#define wxSCI_MARGIN_CHANGED 7
/* CHANGEBAR end */

/// Styles in range 32..38 are predefined for parts of the UI and are not used as normal styles.
/// Style 39 is for future use.
#define wxSCI_STYLE_DEFAULT 32
#define wxSCI_STYLE_LINENUMBER 33
#define wxSCI_STYLE_BRACELIGHT 34
#define wxSCI_STYLE_BRACEBAD 35
#define wxSCI_STYLE_CONTROLCHAR 36
#define wxSCI_STYLE_INDENTGUIDE 37
#define wxSCI_STYLE_CALLTIP 38
#define wxSCI_STYLE_FOLDDISPLAYTEXT 39
#define wxSCI_STYLE_LASTPREDEFINED 39
#define wxSCI_STYLE_MAX 255

/// Character set identifiers are used in StyleSetCharacterSet.
/// The values are the same as the Windows *_CHARSET values.
#define wxSCI_CHARSET_ANSI 0
#define wxSCI_CHARSET_DEFAULT 1
#define wxSCI_CHARSET_BALTIC 186
#define wxSCI_CHARSET_CHINESEBIG5 136
#define wxSCI_CHARSET_EASTEUROPE 238
#define wxSCI_CHARSET_GB2312 134
#define wxSCI_CHARSET_GREEK 161
#define wxSCI_CHARSET_HANGUL 129
#define wxSCI_CHARSET_MAC 77
#define wxSCI_CHARSET_OEM 255
#define wxSCI_CHARSET_RUSSIAN 204
#define wxSCI_CHARSET_OEM866 866
#define wxSCI_CHARSET_CYRILLIC 1251
#define wxSCI_CHARSET_SHIFTJIS 128
#define wxSCI_CHARSET_SYMBOL 2
#define wxSCI_CHARSET_TURKISH 162
#define wxSCI_CHARSET_JOHAB 130
#define wxSCI_CHARSET_HEBREW 177
#define wxSCI_CHARSET_ARABIC 178
#define wxSCI_CHARSET_VIETNAMESE 163
#define wxSCI_CHARSET_THAI 222
#define wxSCI_CHARSET_8859_15 1000
#define wxSCI_CASE_MIXED 0
#define wxSCI_CASE_UPPER 1
#define wxSCI_CASE_LOWER 2
#define wxSCI_CASE_CAMEL 3
#define wxSCI_FONT_SIZE_MULTIPLIER 100
#define wxSCI_WEIGHT_NORMAL 400
#define wxSCI_WEIGHT_SEMIBOLD 600
#define wxSCI_WEIGHT_BOLD 700

/// Indicator style enumeration and some constants
#define wxSCI_INDIC_PLAIN 0
#define wxSCI_INDIC_SQUIGGLE 1
#define wxSCI_INDIC_TT 2
#define wxSCI_INDIC_DIAGONAL 3
#define wxSCI_INDIC_STRIKE 4
#define wxSCI_INDIC_HIDDEN 5
#define wxSCI_INDIC_BOX 6
#define wxSCI_INDIC_ROUNDBOX 7
#define wxSCI_INDIC_STRAIGHTBOX 8
#define wxSCI_INDIC_DASH 9
#define wxSCI_INDIC_DOTS 10
#define wxSCI_INDIC_SQUIGGLELOW 11
#define wxSCI_INDIC_DOTBOX 12
#define wxSCI_INDIC_SQUIGGLEPIXMAP 13
#define wxSCI_INDIC_COMPOSITIONTHICK 14
#define wxSCI_INDIC_COMPOSITIONTHIN 15
#define wxSCI_INDIC_FULLBOX 16
#define wxSCI_INDIC_TEXTFORE 17
#define wxSCI_INDIC_POINT 18
#define wxSCI_INDIC_POINTCHARACTER 19
/* C::B begin INDIC_HIGHLIGHT */
#define wxSCI_INDIC_HIGHLIGHT 31 // please change also in wxscintilla.h !!
/* C::B end */
#define wxSCI_INDIC_IME 32
#define wxSCI_INDIC_IME_MAX 35
#define wxSCI_INDIC_MAX 35
#define wxSCI_INDIC_CONTAINER 8
#define wxSCI_INDICVALUEBIT 0x1000000
#define wxSCI_INDICVALUEMASK 0xFFFFFF
#define wxSCI_INDICFLAG_VALUEFORE 1
#define wxSCI_IV_NONE 0
#define wxSCI_IV_REAL 1
#define wxSCI_IV_LOOKFORWARD 2
#define wxSCI_IV_LOOKBOTH 3

/// PrintColourMode - use same colours as screen.
#define wxSCI_PRINT_NORMAL 0

/// PrintColourMode - invert the light value of each style for printing.
#define wxSCI_PRINT_INVERTLIGHT 1

/// PrintColourMode - force black text on white background for printing.
#define wxSCI_PRINT_BLACKONWHITE 2

/// PrintColourMode - text stays coloured, but all background is forced to be white for printing.
#define wxSCI_PRINT_COLOURONWHITE 3

/// PrintColourMode - only the default-background is forced to be white for printing.
#define wxSCI_PRINT_COLOURONWHITEDEFAULTBG 4
#define wxSCI_FIND_WHOLEWORD 0x2
#define wxSCI_FIND_MATCHCASE 0x4
#define wxSCI_FIND_WORDSTART 0x00100000
#define wxSCI_FIND_REGEXP 0x00200000
#define wxSCI_FIND_POSIX 0x00400000
#define wxSCI_FIND_CXX11REGEX 0x00800000
#define wxSCI_FOLDLEVELBASE 0x400
#define wxSCI_FOLDLEVELWHITEFLAG 0x1000
#define wxSCI_FOLDLEVELHEADERFLAG 0x2000
#define wxSCI_FOLDLEVELNUMBERMASK 0x0FFF
#define wxSCI_FOLDDISPLAYTEXT_HIDDEN 0
#define wxSCI_FOLDDISPLAYTEXT_STANDARD 1
#define wxSCI_FOLDDISPLAYTEXT_BOXED 2
#define wxSCI_FOLDACTION_CONTRACT 0
#define wxSCI_FOLDACTION_EXPAND 1
#define wxSCI_FOLDACTION_TOGGLE 2
#define wxSCI_AUTOMATICFOLD_SHOW 0x0001
#define wxSCI_AUTOMATICFOLD_CLICK 0x0002
#define wxSCI_AUTOMATICFOLD_CHANGE 0x0004
#define wxSCI_FOLDFLAG_LINEBEFORE_EXPANDED 0x0002
#define wxSCI_FOLDFLAG_LINEBEFORE_CONTRACTED 0x0004
#define wxSCI_FOLDFLAG_LINEAFTER_EXPANDED 0x0008
#define wxSCI_FOLDFLAG_LINEAFTER_CONTRACTED 0x0010
#define wxSCI_FOLDFLAG_LEVELNUMBERS 0x0040
#define wxSCI_FOLDFLAG_LINESTATE 0x0080
#define wxSCI_TIME_FOREVER 10000000
#define wxSCI_IDLESTYLING_NONE 0
#define wxSCI_IDLESTYLING_TOVISIBLE 1
#define wxSCI_IDLESTYLING_AFTERVISIBLE 2
#define wxSCI_IDLESTYLING_ALL 3
#define wxSCI_WRAP_NONE 0
#define wxSCI_WRAP_WORD 1
#define wxSCI_WRAP_CHAR 2
#define wxSCI_WRAP_WHITESPACE 3
#define wxSCI_WRAPVISUALFLAG_NONE 0x0000
#define wxSCI_WRAPVISUALFLAG_END 0x0001
#define wxSCI_WRAPVISUALFLAG_START 0x0002
#define wxSCI_WRAPVISUALFLAG_MARGIN 0x0004
#define wxSCI_WRAPVISUALFLAGLOC_DEFAULT 0x0000
#define wxSCI_WRAPVISUALFLAGLOC_END_BY_TEXT 0x0001
#define wxSCI_WRAPVISUALFLAGLOC_START_BY_TEXT 0x0002
#define wxSCI_WRAPINDENT_FIXED 0
#define wxSCI_WRAPINDENT_SAME 1
#define wxSCI_WRAPINDENT_INDENT 2
#define wxSCI_CACHE_NONE 0
#define wxSCI_CACHE_CARET 1
#define wxSCI_CACHE_PAGE 2
#define wxSCI_CACHE_DOCUMENT 3
#define wxSCI_PHASES_ONE 0
#define wxSCI_PHASES_TWO 1
#define wxSCI_PHASES_MULTIPLE 2

/// Control font anti-aliasing.
#define wxSCI_EFF_QUALITY_MASK 0xF
#define wxSCI_EFF_QUALITY_DEFAULT 0
#define wxSCI_EFF_QUALITY_NON_ANTIALIASED 1
#define wxSCI_EFF_QUALITY_ANTIALIASED 2
#define wxSCI_EFF_QUALITY_LCD_OPTIMIZED 3
#define wxSCI_MULTIPASTE_ONCE 0
#define wxSCI_MULTIPASTE_EACH 1
#define wxSCI_EDGE_NONE 0
#define wxSCI_EDGE_LINE 1
#define wxSCI_EDGE_BACKGROUND 2
#define wxSCI_EDGE_MULTILINE 3
#define wxSCI_POPUP_NEVER 0
#define wxSCI_POPUP_ALL 1
#define wxSCI_POPUP_TEXT 2
#define wxSCI_STATUS_OK 0
#define wxSCI_STATUS_FAILURE 1
#define wxSCI_STATUS_BADALLOC 2
#define wxSCI_STATUS_WARN_START 1000
#define wxSCI_STATUS_WARN_REGEX 1001
#define wxSCI_CURSORNORMAL -1
#define wxSCI_CURSORARROW 2
#define wxSCI_CURSORWAIT 4
#define wxSCI_CURSORREVERSEARROW 7

/// Constants for use with SetVisiblePolicy, similar to SetCaretPolicy.
#define wxSCI_VISIBLE_SLOP 0x01
#define wxSCI_VISIBLE_STRICT 0x04

/// Caret policy, used by SetXCaretPolicy and SetYCaretPolicy.
/// If CARET_SLOP is set, we can define a slop value: caretSlop.
/// This value defines an unwanted zone (UZ) where the caret is... unwanted.
/// This zone is defined as a number of pixels near the vertical margins,
/// and as a number of lines near the horizontal margins.
/// By keeping the caret away from the edges, it is seen within its context,
/// so it is likely that the identifier that the caret is on can be completely seen,
/// and that the current line is seen with some of the lines following it which are
/// often dependent on that line.
#define wxSCI_CARET_SLOP 0x01

/// If CARET_STRICT is set, the policy is enforced... strictly.
/// The caret is centred on the display if slop is not set,
/// and cannot go in the UZ if slop is set.
#define wxSCI_CARET_STRICT 0x04

/// If CARET_JUMPS is set, the display is moved more energetically
/// so the caret can move in the same direction longer before the policy is applied again.
#define wxSCI_CARET_JUMPS 0x10

/// If CARET_EVEN is not set, instead of having symmetrical UZs,
/// the left and bottom UZs are extended up to right and top UZs respectively.
/// This way, we favour the displaying of useful information: the beginning of lines,
/// where most code reside, and the lines after the caret, eg. the body of a function.
#define wxSCI_CARET_EVEN 0x08
#define wxSCI_SEL_STREAM 0
#define wxSCI_SEL_RECTANGLE 1
#define wxSCI_SEL_LINES 2
#define wxSCI_SEL_THIN 3
#define wxSCI_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE 0
#define wxSCI_CASEINSENSITIVEBEHAVIOUR_IGNORECASE 1
#define wxSCI_MULTIAUTOC_ONCE 0
#define wxSCI_MULTIAUTOC_EACH 1
#define wxSCI_ORDER_PRESORTED 0
#define wxSCI_ORDER_PERFORMSORT 1
#define wxSCI_ORDER_CUSTOM 2
#define wxSCI_CARETSTICKY_OFF 0
#define wxSCI_CARETSTICKY_ON 1
#define wxSCI_CARETSTICKY_WHITESPACE 2
#define wxSCI_ALPHA_TRANSPARENT 0
#define wxSCI_ALPHA_OPAQUE 255
#define wxSCI_ALPHA_NOALPHA 256
#define wxSCI_CARETSTYLE_INVISIBLE 0
#define wxSCI_CARETSTYLE_LINE 1
#define wxSCI_CARETSTYLE_BLOCK 2
#define wxSCI_MARGINOPTION_NONE 0
#define wxSCI_MARGINOPTION_SUBLINESELECT 1
#define wxSCI_ANNOTATION_HIDDEN 0
#define wxSCI_ANNOTATION_STANDARD 1
#define wxSCI_ANNOTATION_BOXED 2
#define wxSCI_ANNOTATION_INDENTED 3
#define wxSCI_UNDO_MAY_COALESCE 1
#define wxSCI_VS_NONE 0
#define wxSCI_VS_RECTANGULARSELECTION 1
#define wxSCI_VS_USERACCESSIBLE 2
#define wxSCI_VS_NOWRAPLINESTART 4
#define wxSCI_TECHNOLOGY_DEFAULT 0
#define wxSCI_TECHNOLOGY_DIRECTWRITE 1

/// Line end types which may be used in addition to LF, CR, and CRLF
/// SC_LINE_END_TYPE_UNICODE includes U+2028 Line Separator,
/// U+2029 Paragraph Separator, and U+0085 Next Line
#define wxSCI_LINE_END_TYPE_DEFAULT 0
#define wxSCI_LINE_END_TYPE_UNICODE 1

/// Maximum value of keywordSet parameter of SetKeyWords.
#define wxSCI_KEYWORDSET_MAX 8
#define wxSCI_TYPE_BOOLEAN 0
#define wxSCI_TYPE_INTEGER 1
#define wxSCI_TYPE_STRING 2

/// Notifications
/// Type of modification and the action which caused the modification.
/// These are defined as a bit mask to make it easy to specify which notifications are wanted.
/// One bit is set from each of SC_MOD_* and SC_PERFORMED_*.
#define wxSCI_MOD_INSERTTEXT 0x1
#define wxSCI_MOD_DELETETEXT 0x2
#define wxSCI_MOD_CHANGESTYLE 0x4
#define wxSCI_MOD_CHANGEFOLD 0x8
#define wxSCI_PERFORMED_USER 0x10
#define wxSCI_PERFORMED_UNDO 0x20
#define wxSCI_PERFORMED_REDO 0x40
#define wxSCI_MULTISTEPUNDOREDO 0x80
#define wxSCI_LASTSTEPINUNDOREDO 0x100
#define wxSCI_MOD_CHANGEMARKER 0x200
#define wxSCI_MOD_BEFOREINSERT 0x400
#define wxSCI_MOD_BEFOREDELETE 0x800
#define wxSCI_MULTILINEUNDOREDO 0x1000
#define wxSCI_STARTACTION 0x2000
#define wxSCI_MOD_CHANGEINDICATOR 0x4000
#define wxSCI_MOD_CHANGELINESTATE 0x8000
#define wxSCI_MOD_CHANGEMARGIN 0x10000
#define wxSCI_MOD_CHANGEANNOTATION 0x20000
#define wxSCI_MOD_CONTAINER 0x40000
#define wxSCI_MOD_LEXERSTATE 0x80000
#define wxSCI_MOD_INSERTCHECK 0x100000
#define wxSCI_MOD_CHANGETABSTOPS 0x200000
#define wxSCI_MODEVENTMASKALL 0x3FFFFF
#define wxSCI_UPDATE_CONTENT 0x1
#define wxSCI_UPDATE_SELECTION 0x2
#define wxSCI_UPDATE_V_SCROLL 0x4
#define wxSCI_UPDATE_H_SCROLL 0x8

/// Symbolic key codes and modifier flags.
/// ASCII and other printable characters below 256.
/// Extended keys above 300.
#define wxSCI_KEY_DOWN 300
#define wxSCI_KEY_UP 301
#define wxSCI_KEY_LEFT 302
#define wxSCI_KEY_RIGHT 303
#define wxSCI_KEY_HOME 304
#define wxSCI_KEY_END 305
#define wxSCI_KEY_PRIOR 306
#define wxSCI_KEY_NEXT 307
#define wxSCI_KEY_DELETE 308
#define wxSCI_KEY_INSERT 309
#define wxSCI_KEY_ESCAPE 7
#define wxSCI_KEY_BACK 8
#define wxSCI_KEY_TAB 9
#define wxSCI_KEY_RETURN 13
#define wxSCI_KEY_ADD 310
#define wxSCI_KEY_SUBTRACT 311
#define wxSCI_KEY_DIVIDE 312
#define wxSCI_KEY_WIN 313
#define wxSCI_KEY_RWIN 314
#define wxSCI_KEY_MENU 315
#define wxSCI_KEYMOD_NORM 0
#define wxSCI_KEYMOD_SHIFT 1
#define wxSCI_KEYMOD_CTRL 2
#define wxSCI_KEYMOD_ALT 4
#define wxSCI_KEYMOD_SUPER 8
#define wxSCI_KEYMOD_META 16
#define wxSCI_AC_FILLUP 1
#define wxSCI_AC_DOUBLECLICK 2
#define wxSCI_AC_TAB 3
#define wxSCI_AC_NEWLINE 4
#define wxSCI_AC_COMMAND 5

/// For SciLexer.h
#define wxSCI_LEX_CONTAINER 0
#define wxSCI_LEX_NULL 1
#define wxSCI_LEX_PYTHON 2
#define wxSCI_LEX_CPP 3
#define wxSCI_LEX_HTML 4
#define wxSCI_LEX_XML 5
#define wxSCI_LEX_PERL 6
#define wxSCI_LEX_SQL 7
#define wxSCI_LEX_VB 8
#define wxSCI_LEX_PROPERTIES 9
#define wxSCI_LEX_ERRORLIST 10
#define wxSCI_LEX_MAKEFILE 11
#define wxSCI_LEX_BATCH 12
#define wxSCI_LEX_XCODE 13
#define wxSCI_LEX_LATEX 14
#define wxSCI_LEX_LUA 15
#define wxSCI_LEX_DIFF 16
#define wxSCI_LEX_CONF 17
#define wxSCI_LEX_PASCAL 18
#define wxSCI_LEX_AVE 19
#define wxSCI_LEX_ADA 20
#define wxSCI_LEX_LISP 21
#define wxSCI_LEX_RUBY 22
#define wxSCI_LEX_EIFFEL 23
#define wxSCI_LEX_EIFFELKW 24
#define wxSCI_LEX_TCL 25
#define wxSCI_LEX_NNCRONTAB 26
#define wxSCI_LEX_BULLANT 27
#define wxSCI_LEX_VBSCRIPT 28
#define wxSCI_LEX_BAAN 31
#define wxSCI_LEX_MATLAB 32
#define wxSCI_LEX_SCRIPTOL 33
#define wxSCI_LEX_ASM 34
#define wxSCI_LEX_CPPNOCASE 35
#define wxSCI_LEX_FORTRAN 36
#define wxSCI_LEX_F77 37
#define wxSCI_LEX_CSS 38
#define wxSCI_LEX_POV 39
#define wxSCI_LEX_LOUT 40
#define wxSCI_LEX_ESCRIPT 41
#define wxSCI_LEX_PS 42
#define wxSCI_LEX_NSIS 43
#define wxSCI_LEX_MMIXAL 44
#define wxSCI_LEX_CLW 45
#define wxSCI_LEX_CLWNOCASE 46
#define wxSCI_LEX_LOT 47
#define wxSCI_LEX_YAML 48
#define wxSCI_LEX_TEX 49
#define wxSCI_LEX_METAPOST 50
#define wxSCI_LEX_POWERBASIC 51
#define wxSCI_LEX_FORTH 52
#define wxSCI_LEX_ERLANG 53
#define wxSCI_LEX_OCTAVE 54
#define wxSCI_LEX_MSSQL 55
#define wxSCI_LEX_VERILOG 56
#define wxSCI_LEX_KIX 57
#define wxSCI_LEX_GUI4CLI 58
#define wxSCI_LEX_SPECMAN 59
#define wxSCI_LEX_AU3 60
#define wxSCI_LEX_APDL 61
#define wxSCI_LEX_BASH 62
#define wxSCI_LEX_ASN1 63
#define wxSCI_LEX_VHDL 64
#define wxSCI_LEX_CAML 65
#define wxSCI_LEX_BLITZBASIC 66
#define wxSCI_LEX_PUREBASIC 67
#define wxSCI_LEX_HASKELL 68
#define wxSCI_LEX_PHPSCRIPT 69
#define wxSCI_LEX_TADS3 70
#define wxSCI_LEX_REBOL 71
#define wxSCI_LEX_SMALLTALK 72
#define wxSCI_LEX_FLAGSHIP 73
#define wxSCI_LEX_CSOUND 74
#define wxSCI_LEX_FREEBASIC 75
#define wxSCI_LEX_INNOSETUP 76
#define wxSCI_LEX_OPAL 77
#define wxSCI_LEX_SPICE 78
#define wxSCI_LEX_D 79
#define wxSCI_LEX_CMAKE 80
#define wxSCI_LEX_GAP 81
#define wxSCI_LEX_PLM 82
#define wxSCI_LEX_PROGRESS 83
#define wxSCI_LEX_ABAQUS 84
#define wxSCI_LEX_ASYMPTOTE 85
#define wxSCI_LEX_R 86
#define wxSCI_LEX_MAGIK 87
#define wxSCI_LEX_POWERSHELL 88
#define wxSCI_LEX_MYSQL 89
#define wxSCI_LEX_PO 90
#define wxSCI_LEX_TAL 91
#define wxSCI_LEX_COBOL 92
#define wxSCI_LEX_TACL 93
#define wxSCI_LEX_SORCUS 94
#define wxSCI_LEX_POWERPRO 95
#define wxSCI_LEX_NIMROD 96
#define wxSCI_LEX_SML 97
#define wxSCI_LEX_MARKDOWN 98
#define wxSCI_LEX_TXT2TAGS 99
#define wxSCI_LEX_A68K 100
#define wxSCI_LEX_MODULA 101
#define wxSCI_LEX_COFFEESCRIPT 102
#define wxSCI_LEX_TCMD 103
#define wxSCI_LEX_AVS 104
#define wxSCI_LEX_ECL 105
#define wxSCI_LEX_OSCRIPT 106
#define wxSCI_LEX_VISUALPROLOG 107
#define wxSCI_LEX_LITERATEHASKELL 108
#define wxSCI_LEX_STTXT 109
#define wxSCI_LEX_KVIRC 110
#define wxSCI_LEX_RUST 111
#define wxSCI_LEX_DMAP 112
#define wxSCI_LEX_AS 113
#define wxSCI_LEX_DMIS 114
#define wxSCI_LEX_REGISTRY 115
#define wxSCI_LEX_BIBTEX 116
#define wxSCI_LEX_SREC 117
#define wxSCI_LEX_IHEX 118
#define wxSCI_LEX_TEHEX 119
#define wxSCI_LEX_JSON 120
#define wxSCI_LEX_EDIFACT 121
#define wxSCI_LEX_INDENT 122
/* C::B begin */
#define wxSCI_LEX_LAST wxSCI_LEX_INDENT // update if the above gets extended!
/* C::B end */

/// When a lexer specifies its language as SCLEX_AUTOMATIC it receives a
/// value assigned in sequence from SCLEX_AUTOMATIC+1.
#define wxSCI_LEX_AUTOMATIC 1000

/// Lexical states for SCLEX_PYTHON
#define wxSCI_P_DEFAULT 0
#define wxSCI_P_COMMENTLINE 1
#define wxSCI_P_NUMBER 2
#define wxSCI_P_STRING 3
#define wxSCI_P_CHARACTER 4
#define wxSCI_P_WORD 5
#define wxSCI_P_TRIPLE 6
#define wxSCI_P_TRIPLEDOUBLE 7
#define wxSCI_P_CLASSNAME 8
#define wxSCI_P_DEFNAME 9
#define wxSCI_P_OPERATOR 10
#define wxSCI_P_IDENTIFIER 11
#define wxSCI_P_COMMENTBLOCK 12
#define wxSCI_P_STRINGEOL 13
#define wxSCI_P_WORD2 14
#define wxSCI_P_DECORATOR 15
#define wxSCI_P_FSTRING 16
#define wxSCI_P_FCHARACTER 17
#define wxSCI_P_FTRIPLE 18
#define wxSCI_P_FTRIPLEDOUBLE 19

/// Lexical states for SCLEX_CPP, SCLEX_BULLANT, SCLEX_COBOL, SCLEX_TACL, SCLEX_TAL
#define wxSCI_C_DEFAULT 0
#define wxSCI_C_COMMENT 1
#define wxSCI_C_COMMENTLINE 2
#define wxSCI_C_COMMENTDOC 3
#define wxSCI_C_NUMBER 4
#define wxSCI_C_WORD 5
#define wxSCI_C_STRING 6
#define wxSCI_C_CHARACTER 7
#define wxSCI_C_UUID 8
#define wxSCI_C_PREPROCESSOR 9
#define wxSCI_C_OPERATOR 10
#define wxSCI_C_IDENTIFIER 11
#define wxSCI_C_STRINGEOL 12
#define wxSCI_C_VERBATIM 13
#define wxSCI_C_REGEX 14
#define wxSCI_C_COMMENTLINEDOC 15
#define wxSCI_C_WORD2 16
#define wxSCI_C_COMMENTDOCKEYWORD 17
#define wxSCI_C_COMMENTDOCKEYWORDERROR 18
#define wxSCI_C_GLOBALCLASS 19
#define wxSCI_C_STRINGRAW 20
#define wxSCI_C_TRIPLEVERBATIM 21
#define wxSCI_C_HASHQUOTEDSTRING 22
#define wxSCI_C_PREPROCESSORCOMMENT 23
#define wxSCI_C_PREPROCESSORCOMMENTDOC 24
#define wxSCI_C_USERLITERAL 25
#define wxSCI_C_TASKMARKER 26
#define wxSCI_C_ESCAPESEQUENCE 27

/// WXSMITH begin #
/// Keep in sync with wxscinilla.h  -> wxSCI_C_WXSMITH
/// Keep in sync with SciLexer.h    -> SCE_C_WXSMITH
/// Keep in sync with lexer_cpp.xml -> Style name="wxSmith-generated code"
/// Notice that due to the "activeFlag" in LexCPP.cxx, the index must be < 64 (0x40).
#define wxSCI_C_WXSMITH 50

/// WXSMITH end #
/// Lexical states for SCLEX_D
#define wxSCI_D_DEFAULT 0
#define wxSCI_D_COMMENT 1
#define wxSCI_D_COMMENTLINE 2
#define wxSCI_D_COMMENTDOC 3
#define wxSCI_D_COMMENTNESTED 4
#define wxSCI_D_NUMBER 5
#define wxSCI_D_WORD 6
#define wxSCI_D_WORD2 7
#define wxSCI_D_WORD3 8
#define wxSCI_D_TYPEDEF 9
#define wxSCI_D_STRING 10
#define wxSCI_D_STRINGEOL 11
#define wxSCI_D_CHARACTER 12
#define wxSCI_D_OPERATOR 13
#define wxSCI_D_IDENTIFIER 14
#define wxSCI_D_COMMENTLINEDOC 15
#define wxSCI_D_COMMENTDOCKEYWORD 16
#define wxSCI_D_COMMENTDOCKEYWORDERROR 17
#define wxSCI_D_STRINGB 18
#define wxSCI_D_STRINGR 19
#define wxSCI_D_WORD5 20
#define wxSCI_D_WORD6 21
#define wxSCI_D_WORD7 22

/// Lexical states for SCLEX_TCL
#define wxSCI_TCL_DEFAULT 0
#define wxSCI_TCL_COMMENT 1
#define wxSCI_TCL_COMMENTLINE 2
#define wxSCI_TCL_NUMBER 3
#define wxSCI_TCL_WORD_IN_QUOTE 4
#define wxSCI_TCL_IN_QUOTE 5
#define wxSCI_TCL_OPERATOR 6
#define wxSCI_TCL_IDENTIFIER 7
#define wxSCI_TCL_SUBSTITUTION 8
#define wxSCI_TCL_SUB_BRACE 9
#define wxSCI_TCL_MODIFIER 10
#define wxSCI_TCL_EXPAND 11
#define wxSCI_TCL_WORD 12
#define wxSCI_TCL_WORD2 13
#define wxSCI_TCL_WORD3 14
#define wxSCI_TCL_WORD4 15
#define wxSCI_TCL_WORD5 16
#define wxSCI_TCL_WORD6 17
#define wxSCI_TCL_WORD7 18
#define wxSCI_TCL_WORD8 19
#define wxSCI_TCL_COMMENT_BOX 20
#define wxSCI_TCL_BLOCK_COMMENT 21

/// Lexical states for SCLEX_HTML, SCLEX_XML
#define wxSCI_H_DEFAULT 0
#define wxSCI_H_TAG 1
#define wxSCI_H_TAGUNKNOWN 2
#define wxSCI_H_ATTRIBUTE 3
#define wxSCI_H_ATTRIBUTEUNKNOWN 4
#define wxSCI_H_NUMBER 5
#define wxSCI_H_DOUBLESTRING 6
#define wxSCI_H_SINGLESTRING 7
#define wxSCI_H_OTHER 8
#define wxSCI_H_COMMENT 9
#define wxSCI_H_ENTITY 10

/// XML and ASP
#define wxSCI_H_TAGEND 11
#define wxSCI_H_XMLSTART 12
#define wxSCI_H_XMLEND 13
#define wxSCI_H_SCRIPT 14
#define wxSCI_H_ASP 15
#define wxSCI_H_ASPAT 16
#define wxSCI_H_CDATA 17
#define wxSCI_H_QUESTION 18

/// More HTML
#define wxSCI_H_VALUE 19

/// X-Code
#define wxSCI_H_XCCOMMENT 20

/// SGML
#define wxSCI_H_SGML_DEFAULT 21
#define wxSCI_H_SGML_COMMAND 22
#define wxSCI_H_SGML_1ST_PARAM 23
#define wxSCI_H_SGML_DOUBLESTRING 24
#define wxSCI_H_SGML_SIMPLESTRING 25
#define wxSCI_H_SGML_ERROR 26
#define wxSCI_H_SGML_SPECIAL 27
#define wxSCI_H_SGML_ENTITY 28
#define wxSCI_H_SGML_COMMENT 29
#define wxSCI_H_SGML_1ST_PARAM_COMMENT 30
#define wxSCI_H_SGML_BLOCK_DEFAULT 31

/// Embedded Javascript
#define wxSCI_HJ_START 40
#define wxSCI_HJ_DEFAULT 41
#define wxSCI_HJ_COMMENT 42
#define wxSCI_HJ_COMMENTLINE 43
#define wxSCI_HJ_COMMENTDOC 44
#define wxSCI_HJ_NUMBER 45
#define wxSCI_HJ_WORD 46
#define wxSCI_HJ_KEYWORD 47
#define wxSCI_HJ_DOUBLESTRING 48
#define wxSCI_HJ_SINGLESTRING 49
#define wxSCI_HJ_SYMBOLS 50
#define wxSCI_HJ_STRINGEOL 51
#define wxSCI_HJ_REGEX 52

/// ASP Javascript
#define wxSCI_HJA_START 55
#define wxSCI_HJA_DEFAULT 56
#define wxSCI_HJA_COMMENT 57
#define wxSCI_HJA_COMMENTLINE 58
#define wxSCI_HJA_COMMENTDOC 59
#define wxSCI_HJA_NUMBER 60
#define wxSCI_HJA_WORD 61
#define wxSCI_HJA_KEYWORD 62
#define wxSCI_HJA_DOUBLESTRING 63
#define wxSCI_HJA_SINGLESTRING 64
#define wxSCI_HJA_SYMBOLS 65
#define wxSCI_HJA_STRINGEOL 66
#define wxSCI_HJA_REGEX 67

/// Embedded VBScript
#define wxSCI_HB_START 70
#define wxSCI_HB_DEFAULT 71
#define wxSCI_HB_COMMENTLINE 72
#define wxSCI_HB_NUMBER 73
#define wxSCI_HB_WORD 74
#define wxSCI_HB_STRING 75
#define wxSCI_HB_IDENTIFIER 76
#define wxSCI_HB_STRINGEOL 77

/// ASP VBScript
#define wxSCI_HBA_START 80
#define wxSCI_HBA_DEFAULT 81
#define wxSCI_HBA_COMMENTLINE 82
#define wxSCI_HBA_NUMBER 83
#define wxSCI_HBA_WORD 84
#define wxSCI_HBA_STRING 85
#define wxSCI_HBA_IDENTIFIER 86
#define wxSCI_HBA_STRINGEOL 87

/// Embedded Python
#define wxSCI_HP_START 90
#define wxSCI_HP_DEFAULT 91
#define wxSCI_HP_COMMENTLINE 92
#define wxSCI_HP_NUMBER 93
#define wxSCI_HP_STRING 94
#define wxSCI_HP_CHARACTER 95
#define wxSCI_HP_WORD 96
#define wxSCI_HP_TRIPLE 97
#define wxSCI_HP_TRIPLEDOUBLE 98
#define wxSCI_HP_CLASSNAME 99
#define wxSCI_HP_DEFNAME 100
#define wxSCI_HP_OPERATOR 101
#define wxSCI_HP_IDENTIFIER 102

/// PHP
#define wxSCI_HPHP_COMPLEX_VARIABLE 104

/// ASP Python
#define wxSCI_HPA_START 105
#define wxSCI_HPA_DEFAULT 106
#define wxSCI_HPA_COMMENTLINE 107
#define wxSCI_HPA_NUMBER 108
#define wxSCI_HPA_STRING 109
#define wxSCI_HPA_CHARACTER 110
#define wxSCI_HPA_WORD 111
#define wxSCI_HPA_TRIPLE 112
#define wxSCI_HPA_TRIPLEDOUBLE 113
#define wxSCI_HPA_CLASSNAME 114
#define wxSCI_HPA_DEFNAME 115
#define wxSCI_HPA_OPERATOR 116
#define wxSCI_HPA_IDENTIFIER 117

/// PHP
#define wxSCI_HPHP_DEFAULT 118
#define wxSCI_HPHP_HSTRING 119
#define wxSCI_HPHP_SIMPLESTRING 120
#define wxSCI_HPHP_WORD 121
#define wxSCI_HPHP_NUMBER 122
#define wxSCI_HPHP_VARIABLE 123
#define wxSCI_HPHP_COMMENT 124
#define wxSCI_HPHP_COMMENTLINE 125
#define wxSCI_HPHP_HSTRING_VARIABLE 126
#define wxSCI_HPHP_OPERATOR 127

/// Lexical states for SCLEX_PERL
#define wxSCI_PL_DEFAULT 0
#define wxSCI_PL_ERROR 1
#define wxSCI_PL_COMMENTLINE 2
#define wxSCI_PL_POD 3
#define wxSCI_PL_NUMBER 4
#define wxSCI_PL_WORD 5
#define wxSCI_PL_STRING 6
#define wxSCI_PL_CHARACTER 7
#define wxSCI_PL_PUNCTUATION 8
#define wxSCI_PL_PREPROCESSOR 9
#define wxSCI_PL_OPERATOR 10
#define wxSCI_PL_IDENTIFIER 11
#define wxSCI_PL_SCALAR 12
#define wxSCI_PL_ARRAY 13
#define wxSCI_PL_HASH 14
#define wxSCI_PL_SYMBOLTABLE 15
#define wxSCI_PL_VARIABLE_INDEXER 16
#define wxSCI_PL_REGEX 17
#define wxSCI_PL_REGSUBST 18
#define wxSCI_PL_LONGQUOTE 19
#define wxSCI_PL_BACKTICKS 20
#define wxSCI_PL_DATASECTION 21
#define wxSCI_PL_HERE_DELIM 22
#define wxSCI_PL_HERE_Q 23
#define wxSCI_PL_HERE_QQ 24
#define wxSCI_PL_HERE_QX 25
#define wxSCI_PL_STRING_Q 26
#define wxSCI_PL_STRING_QQ 27
#define wxSCI_PL_STRING_QX 28
#define wxSCI_PL_STRING_QR 29
#define wxSCI_PL_STRING_QW 30
#define wxSCI_PL_POD_VERB 31
#define wxSCI_PL_SUB_PROTOTYPE 40
#define wxSCI_PL_FORMAT_IDENT 41
#define wxSCI_PL_FORMAT 42
#define wxSCI_PL_STRING_VAR 43
#define wxSCI_PL_XLAT 44
#define wxSCI_PL_REGEX_VAR 54
#define wxSCI_PL_REGSUBST_VAR 55
#define wxSCI_PL_BACKTICKS_VAR 57
#define wxSCI_PL_HERE_QQ_VAR 61
#define wxSCI_PL_HERE_QX_VAR 62
#define wxSCI_PL_STRING_QQ_VAR 64
#define wxSCI_PL_STRING_QX_VAR 65
#define wxSCI_PL_STRING_QR_VAR 66

/// Lexical states for SCLEX_RUBY
#define wxSCI_RB_DEFAULT 0
#define wxSCI_RB_ERROR 1
#define wxSCI_RB_COMMENTLINE 2
#define wxSCI_RB_POD 3
#define wxSCI_RB_NUMBER 4
#define wxSCI_RB_WORD 5
#define wxSCI_RB_STRING 6
#define wxSCI_RB_CHARACTER 7
#define wxSCI_RB_CLASSNAME 8
#define wxSCI_RB_DEFNAME 9
#define wxSCI_RB_OPERATOR 10
#define wxSCI_RB_IDENTIFIER 11
#define wxSCI_RB_REGEX 12
#define wxSCI_RB_GLOBAL 13
#define wxSCI_RB_SYMBOL 14
#define wxSCI_RB_MODULE_NAME 15
#define wxSCI_RB_INSTANCE_VAR 16
#define wxSCI_RB_CLASS_VAR 17
#define wxSCI_RB_BACKTICKS 18
#define wxSCI_RB_DATASECTION 19
#define wxSCI_RB_HERE_DELIM 20
#define wxSCI_RB_HERE_Q 21
#define wxSCI_RB_HERE_QQ 22
#define wxSCI_RB_HERE_QX 23
#define wxSCI_RB_STRING_Q 24
#define wxSCI_RB_STRING_QQ 25
#define wxSCI_RB_STRING_QX 26
#define wxSCI_RB_STRING_QR 27
#define wxSCI_RB_STRING_QW 28
#define wxSCI_RB_WORD_DEMOTED 29
#define wxSCI_RB_STDIN 30
#define wxSCI_RB_STDOUT 31
#define wxSCI_RB_STDERR 40
#define wxSCI_RB_UPPER_BOUND 41

/// Lexical states for SCLEX_VB, SCLEX_VBSCRIPT, SCLEX_POWERBASIC, SCLEX_BLITZBASIC, SCLEX_PUREBASIC, SCLEX_FREEBASIC
#define wxSCI_B_DEFAULT 0
#define wxSCI_B_COMMENT 1
#define wxSCI_B_NUMBER 2
#define wxSCI_B_KEYWORD 3
#define wxSCI_B_STRING 4
#define wxSCI_B_PREPROCESSOR 5
#define wxSCI_B_OPERATOR 6
#define wxSCI_B_IDENTIFIER 7
#define wxSCI_B_DATE 8
#define wxSCI_B_STRINGEOL 9
#define wxSCI_B_KEYWORD2 10
#define wxSCI_B_KEYWORD3 11
#define wxSCI_B_KEYWORD4 12
#define wxSCI_B_CONSTANT 13
#define wxSCI_B_ASM 14
#define wxSCI_B_LABEL 15
#define wxSCI_B_ERROR 16
#define wxSCI_B_HEXNUMBER 17
#define wxSCI_B_BINNUMBER 18
#define wxSCI_B_COMMENTBLOCK 19
#define wxSCI_B_DOCLINE 20
#define wxSCI_B_DOCBLOCK 21
#define wxSCI_B_DOCKEYWORD 22

/// Lexical states for SCLEX_PROPERTIES
#define wxSCI_PROPS_DEFAULT 0
#define wxSCI_PROPS_COMMENT 1
#define wxSCI_PROPS_SECTION 2
#define wxSCI_PROPS_ASSIGNMENT 3
#define wxSCI_PROPS_DEFVAL 4
#define wxSCI_PROPS_KEY 5

/// Lexical states for SCLEX_LATEX
#define wxSCI_L_DEFAULT 0
#define wxSCI_L_COMMAND 1
#define wxSCI_L_TAG 2
#define wxSCI_L_MATH 3
#define wxSCI_L_COMMENT 4
#define wxSCI_L_TAG2 5
#define wxSCI_L_MATH2 6
#define wxSCI_L_COMMENT2 7
#define wxSCI_L_VERBATIM 8
#define wxSCI_L_SHORTCMD 9
#define wxSCI_L_SPECIAL 10
#define wxSCI_L_CMDOPT 11
#define wxSCI_L_ERROR 12

/// Lexical states for SCLEX_LUA
#define wxSCI_LUA_DEFAULT 0
#define wxSCI_LUA_COMMENT 1
#define wxSCI_LUA_COMMENTLINE 2
#define wxSCI_LUA_COMMENTDOC 3
#define wxSCI_LUA_NUMBER 4
#define wxSCI_LUA_WORD 5
#define wxSCI_LUA_STRING 6
#define wxSCI_LUA_CHARACTER 7
#define wxSCI_LUA_LITERALSTRING 8
#define wxSCI_LUA_PREPROCESSOR 9
#define wxSCI_LUA_OPERATOR 10
#define wxSCI_LUA_IDENTIFIER 11
#define wxSCI_LUA_STRINGEOL 12
#define wxSCI_LUA_WORD2 13
#define wxSCI_LUA_WORD3 14
#define wxSCI_LUA_WORD4 15
#define wxSCI_LUA_WORD5 16
#define wxSCI_LUA_WORD6 17
#define wxSCI_LUA_WORD7 18
#define wxSCI_LUA_WORD8 19
#define wxSCI_LUA_LABEL 20

/// Lexical states for SCLEX_ERRORLIST
#define wxSCI_ERR_DEFAULT 0
#define wxSCI_ERR_PYTHON 1
#define wxSCI_ERR_GCC 2
#define wxSCI_ERR_MS 3
#define wxSCI_ERR_CMD 4
#define wxSCI_ERR_BORLAND 5
#define wxSCI_ERR_PERL 6
#define wxSCI_ERR_NET 7
#define wxSCI_ERR_LUA 8
#define wxSCI_ERR_CTAG 9
#define wxSCI_ERR_DIFF_CHANGED 10
#define wxSCI_ERR_DIFF_ADDITION 11
#define wxSCI_ERR_DIFF_DELETION 12
#define wxSCI_ERR_DIFF_MESSAGE 13
#define wxSCI_ERR_PHP 14
#define wxSCI_ERR_ELF 15
#define wxSCI_ERR_IFC 16
#define wxSCI_ERR_IFORT 17
#define wxSCI_ERR_ABSF 18
#define wxSCI_ERR_TIDY 19
#define wxSCI_ERR_JAVA_STACK 20
#define wxSCI_ERR_VALUE 21
#define wxSCI_ERR_GCC_INCLUDED_FROM 22
#define wxSCI_ERR_ESCSEQ 23
#define wxSCI_ERR_ESCSEQ_UNKNOWN 24
#define wxSCI_ERR_ES_BLACK 40
#define wxSCI_ERR_ES_RED 41
#define wxSCI_ERR_ES_GREEN 42
#define wxSCI_ERR_ES_BROWN 43
#define wxSCI_ERR_ES_BLUE 44
#define wxSCI_ERR_ES_MAGENTA 45
#define wxSCI_ERR_ES_CYAN 46
#define wxSCI_ERR_ES_GRAY 47
#define wxSCI_ERR_ES_DARK_GRAY 48
#define wxSCI_ERR_ES_BRIGHT_RED 49
#define wxSCI_ERR_ES_BRIGHT_GREEN 50
#define wxSCI_ERR_ES_YELLOW 51
#define wxSCI_ERR_ES_BRIGHT_BLUE 52
#define wxSCI_ERR_ES_BRIGHT_MAGENTA 53
#define wxSCI_ERR_ES_BRIGHT_CYAN 54
#define wxSCI_ERR_ES_WHITE 55

/// Lexical states for SCLEX_BATCH
#define wxSCI_BAT_DEFAULT 0
#define wxSCI_BAT_COMMENT 1
#define wxSCI_BAT_WORD 2
#define wxSCI_BAT_LABEL 3
#define wxSCI_BAT_HIDE 4
#define wxSCI_BAT_COMMAND 5
#define wxSCI_BAT_IDENTIFIER 6
#define wxSCI_BAT_OPERATOR 7

/// Lexical states for SCLEX_TCMD
#define wxSCI_TCMD_DEFAULT 0
#define wxSCI_TCMD_COMMENT 1
#define wxSCI_TCMD_WORD 2
#define wxSCI_TCMD_LABEL 3
#define wxSCI_TCMD_HIDE 4
#define wxSCI_TCMD_COMMAND 5
#define wxSCI_TCMD_IDENTIFIER 6
#define wxSCI_TCMD_OPERATOR 7
#define wxSCI_TCMD_ENVIRONMENT 8
#define wxSCI_TCMD_EXPANSION 9
#define wxSCI_TCMD_CLABEL 10

/// Lexical states for SCLEX_MAKEFILE
#define wxSCI_MAKE_DEFAULT 0
#define wxSCI_MAKE_COMMENT 1
#define wxSCI_MAKE_PREPROCESSOR 2
#define wxSCI_MAKE_IDENTIFIER 3
#define wxSCI_MAKE_OPERATOR 4
#define wxSCI_MAKE_TARGET 5
#define wxSCI_MAKE_IDEOL 9

/// Lexical states for SCLEX_DIFF
#define wxSCI_DIFF_DEFAULT 0
#define wxSCI_DIFF_COMMENT 1
#define wxSCI_DIFF_COMMAND 2
#define wxSCI_DIFF_HEADER 3
#define wxSCI_DIFF_POSITION 4
#define wxSCI_DIFF_DELETED 5
#define wxSCI_DIFF_ADDED 6
#define wxSCI_DIFF_CHANGED 7

/// Lexical states for SCLEX_CONF (Apache Configuration Files Lexer)
#define wxSCI_CONF_DEFAULT 0
#define wxSCI_CONF_COMMENT 1
#define wxSCI_CONF_NUMBER 2
#define wxSCI_CONF_IDENTIFIER 3
#define wxSCI_CONF_EXTENSION 4
#define wxSCI_CONF_PARAMETER 5
#define wxSCI_CONF_STRING 6
#define wxSCI_CONF_OPERATOR 7
#define wxSCI_CONF_IP 8
#define wxSCI_CONF_DIRECTIVE 9

/// Lexical states for SCLEX_AVE, Avenue
#define wxSCI_AVE_DEFAULT 0
#define wxSCI_AVE_COMMENT 1
#define wxSCI_AVE_NUMBER 2
#define wxSCI_AVE_WORD 3
#define wxSCI_AVE_STRING 6
#define wxSCI_AVE_ENUM 7
#define wxSCI_AVE_STRINGEOL 8
#define wxSCI_AVE_IDENTIFIER 9
#define wxSCI_AVE_OPERATOR 10
#define wxSCI_AVE_WORD1 11
#define wxSCI_AVE_WORD2 12
#define wxSCI_AVE_WORD3 13
#define wxSCI_AVE_WORD4 14
#define wxSCI_AVE_WORD5 15
#define wxSCI_AVE_WORD6 16

/// Lexical states for SCLEX_ADA
#define wxSCI_ADA_DEFAULT 0
#define wxSCI_ADA_WORD 1
#define wxSCI_ADA_IDENTIFIER 2
#define wxSCI_ADA_NUMBER 3
#define wxSCI_ADA_DELIMITER 4
#define wxSCI_ADA_CHARACTER 5
#define wxSCI_ADA_CHARACTEREOL 6
#define wxSCI_ADA_STRING 7
#define wxSCI_ADA_STRINGEOL 8
#define wxSCI_ADA_LABEL 9
#define wxSCI_ADA_COMMENTLINE 10
#define wxSCI_ADA_ILLEGAL 11

/// Lexical states for SCLEX_BAAN
#define wxSCI_BAAN_DEFAULT 0
#define wxSCI_BAAN_COMMENT 1
#define wxSCI_BAAN_COMMENTDOC 2
#define wxSCI_BAAN_NUMBER 3
#define wxSCI_BAAN_WORD 4
#define wxSCI_BAAN_STRING 5
#define wxSCI_BAAN_PREPROCESSOR 6
#define wxSCI_BAAN_OPERATOR 7
#define wxSCI_BAAN_IDENTIFIER 8
#define wxSCI_BAAN_STRINGEOL 9
#define wxSCI_BAAN_WORD2 10
#define wxSCI_BAAN_WORD3 11
#define wxSCI_BAAN_WORD4 12
#define wxSCI_BAAN_WORD5 13
#define wxSCI_BAAN_WORD6 14
#define wxSCI_BAAN_WORD7 15
#define wxSCI_BAAN_WORD8 16
#define wxSCI_BAAN_WORD9 17
#define wxSCI_BAAN_TABLEDEF 18
#define wxSCI_BAAN_TABLESQL 19
#define wxSCI_BAAN_FUNCTION 20
#define wxSCI_BAAN_DOMDEF 21
#define wxSCI_BAAN_FUNCDEF 22
#define wxSCI_BAAN_OBJECTDEF 23
#define wxSCI_BAAN_DEFINEDEF 24

/// Lexical states for SCLEX_LISP
#define wxSCI_LISP_DEFAULT 0
#define wxSCI_LISP_COMMENT 1
#define wxSCI_LISP_NUMBER 2
#define wxSCI_LISP_KEYWORD 3
#define wxSCI_LISP_KEYWORD_KW 4
#define wxSCI_LISP_SYMBOL 5
#define wxSCI_LISP_STRING 6
#define wxSCI_LISP_STRINGEOL 8
#define wxSCI_LISP_IDENTIFIER 9
#define wxSCI_LISP_OPERATOR 10
#define wxSCI_LISP_SPECIAL 11
#define wxSCI_LISP_MULTI_COMMENT 12

/// Lexical states for SCLEX_EIFFEL and SCLEX_EIFFELKW
#define wxSCI_EIFFEL_DEFAULT 0
#define wxSCI_EIFFEL_COMMENTLINE 1
#define wxSCI_EIFFEL_NUMBER 2
#define wxSCI_EIFFEL_WORD 3
#define wxSCI_EIFFEL_STRING 4
#define wxSCI_EIFFEL_CHARACTER 5
#define wxSCI_EIFFEL_OPERATOR 6
#define wxSCI_EIFFEL_IDENTIFIER 7
#define wxSCI_EIFFEL_STRINGEOL 8

/// Lexical states for SCLEX_NNCRONTAB (nnCron crontab Lexer)
#define wxSCI_NNCRONTAB_DEFAULT 0
#define wxSCI_NNCRONTAB_COMMENT 1
#define wxSCI_NNCRONTAB_TASK 2
#define wxSCI_NNCRONTAB_SECTION 3
#define wxSCI_NNCRONTAB_KEYWORD 4
#define wxSCI_NNCRONTAB_MODIFIER 5
#define wxSCI_NNCRONTAB_ASTERISK 6
#define wxSCI_NNCRONTAB_NUMBER 7
#define wxSCI_NNCRONTAB_STRING 8
#define wxSCI_NNCRONTAB_ENVIRONMENT 9
#define wxSCI_NNCRONTAB_IDENTIFIER 10

/// Lexical states for SCLEX_FORTH (Forth Lexer)
#define wxSCI_FORTH_DEFAULT 0
#define wxSCI_FORTH_COMMENT 1
#define wxSCI_FORTH_COMMENT_ML 2
#define wxSCI_FORTH_IDENTIFIER 3
#define wxSCI_FORTH_CONTROL 4
#define wxSCI_FORTH_KEYWORD 5
#define wxSCI_FORTH_DEFWORD 6
#define wxSCI_FORTH_PREWORD1 7
#define wxSCI_FORTH_PREWORD2 8
#define wxSCI_FORTH_NUMBER 9
#define wxSCI_FORTH_STRING 10
#define wxSCI_FORTH_LOCALE 11

/// Lexical states for SCLEX_MATLAB
#define wxSCI_MATLAB_DEFAULT 0
#define wxSCI_MATLAB_COMMENT 1
#define wxSCI_MATLAB_COMMAND 2
#define wxSCI_MATLAB_NUMBER 3
#define wxSCI_MATLAB_KEYWORD 4

/// single quoted string
#define wxSCI_MATLAB_STRING 5
#define wxSCI_MATLAB_OPERATOR 6
#define wxSCI_MATLAB_IDENTIFIER 7
#define wxSCI_MATLAB_DOUBLEQUOTESTRING 8

/// Lexical states for SCLEX_SCRIPTOL
#define wxSCI_SCRIPTOL_DEFAULT 0
#define wxSCI_SCRIPTOL_WHITE 1
#define wxSCI_SCRIPTOL_COMMENTLINE 2
#define wxSCI_SCRIPTOL_PERSISTENT 3
#define wxSCI_SCRIPTOL_CSTYLE 4
#define wxSCI_SCRIPTOL_COMMENTBLOCK 5
#define wxSCI_SCRIPTOL_NUMBER 6
#define wxSCI_SCRIPTOL_STRING 7
#define wxSCI_SCRIPTOL_CHARACTER 8
#define wxSCI_SCRIPTOL_STRINGEOL 9
#define wxSCI_SCRIPTOL_KEYWORD 10
#define wxSCI_SCRIPTOL_OPERATOR 11
#define wxSCI_SCRIPTOL_IDENTIFIER 12
#define wxSCI_SCRIPTOL_TRIPLE 13
#define wxSCI_SCRIPTOL_CLASSNAME 14
#define wxSCI_SCRIPTOL_PREPROCESSOR 15

/// Lexical states for SCLEX_ASM, SCLEX_AS
#define wxSCI_ASM_DEFAULT 0
#define wxSCI_ASM_COMMENT 1
#define wxSCI_ASM_NUMBER 2
#define wxSCI_ASM_STRING 3
#define wxSCI_ASM_OPERATOR 4
#define wxSCI_ASM_IDENTIFIER 5
#define wxSCI_ASM_CPUINSTRUCTION 6
#define wxSCI_ASM_MATHINSTRUCTION 7
#define wxSCI_ASM_REGISTER 8
#define wxSCI_ASM_DIRECTIVE 9
#define wxSCI_ASM_DIRECTIVEOPERAND 10
#define wxSCI_ASM_COMMENTBLOCK 11
#define wxSCI_ASM_CHARACTER 12
#define wxSCI_ASM_STRINGEOL 13
#define wxSCI_ASM_EXTINSTRUCTION 14
#define wxSCI_ASM_COMMENTDIRECTIVE 15

/// Lexical states for SCLEX_FORTRAN
#define wxSCI_F_DEFAULT 0
#define wxSCI_F_COMMENT 1
#define wxSCI_F_NUMBER 2
#define wxSCI_F_STRING1 3
#define wxSCI_F_STRING2 4
#define wxSCI_F_STRINGEOL 5
#define wxSCI_F_OPERATOR 6
#define wxSCI_F_IDENTIFIER 7
#define wxSCI_F_WORD 8
#define wxSCI_F_WORD2 9
#define wxSCI_F_WORD3 10
#define wxSCI_F_PREPROCESSOR 11
#define wxSCI_F_OPERATOR2 12
#define wxSCI_F_LABEL 13
#define wxSCI_F_CONTINUATION 14

/// Lexical states for SCLEX_CSS
#define wxSCI_CSS_DEFAULT 0
#define wxSCI_CSS_TAG 1
#define wxSCI_CSS_CLASS 2
#define wxSCI_CSS_PSEUDOCLASS 3
#define wxSCI_CSS_UNKNOWN_PSEUDOCLASS 4
#define wxSCI_CSS_OPERATOR 5
#define wxSCI_CSS_IDENTIFIER 6
#define wxSCI_CSS_UNKNOWN_IDENTIFIER 7
#define wxSCI_CSS_VALUE 8
#define wxSCI_CSS_COMMENT 9
#define wxSCI_CSS_ID 10
#define wxSCI_CSS_IMPORTANT 11
#define wxSCI_CSS_DIRECTIVE 12
#define wxSCI_CSS_DOUBLESTRING 13
#define wxSCI_CSS_SINGLESTRING 14
#define wxSCI_CSS_IDENTIFIER2 15
#define wxSCI_CSS_ATTRIBUTE 16
#define wxSCI_CSS_IDENTIFIER3 17
#define wxSCI_CSS_PSEUDOELEMENT 18
#define wxSCI_CSS_EXTENDED_IDENTIFIER 19
#define wxSCI_CSS_EXTENDED_PSEUDOCLASS 20
#define wxSCI_CSS_EXTENDED_PSEUDOELEMENT 21
#define wxSCI_CSS_MEDIA 22
#define wxSCI_CSS_VARIABLE 23

/// Lexical states for SCLEX_POV
#define wxSCI_POV_DEFAULT 0
#define wxSCI_POV_COMMENT 1
#define wxSCI_POV_COMMENTLINE 2
#define wxSCI_POV_NUMBER 3
#define wxSCI_POV_OPERATOR 4
#define wxSCI_POV_IDENTIFIER 5
#define wxSCI_POV_STRING 6
#define wxSCI_POV_STRINGEOL 7
#define wxSCI_POV_DIRECTIVE 8
#define wxSCI_POV_BADDIRECTIVE 9
#define wxSCI_POV_WORD2 10
#define wxSCI_POV_WORD3 11
#define wxSCI_POV_WORD4 12
#define wxSCI_POV_WORD5 13
#define wxSCI_POV_WORD6 14
#define wxSCI_POV_WORD7 15
#define wxSCI_POV_WORD8 16

/// Lexical states for SCLEX_LOUT
#define wxSCI_LOUT_DEFAULT 0
#define wxSCI_LOUT_COMMENT 1
#define wxSCI_LOUT_NUMBER 2
#define wxSCI_LOUT_WORD 3
#define wxSCI_LOUT_WORD2 4
#define wxSCI_LOUT_WORD3 5
#define wxSCI_LOUT_WORD4 6
#define wxSCI_LOUT_STRING 7
#define wxSCI_LOUT_OPERATOR 8
#define wxSCI_LOUT_IDENTIFIER 9
#define wxSCI_LOUT_STRINGEOL 10

/// Lexical states for SCLEX_ESCRIPT
#define wxSCI_ESCRIPT_DEFAULT 0
#define wxSCI_ESCRIPT_COMMENT 1
#define wxSCI_ESCRIPT_COMMENTLINE 2
#define wxSCI_ESCRIPT_COMMENTDOC 3
#define wxSCI_ESCRIPT_NUMBER 4
#define wxSCI_ESCRIPT_WORD 5
#define wxSCI_ESCRIPT_STRING 6
#define wxSCI_ESCRIPT_OPERATOR 7
#define wxSCI_ESCRIPT_IDENTIFIER 8
#define wxSCI_ESCRIPT_BRACE 9
#define wxSCI_ESCRIPT_WORD2 10
#define wxSCI_ESCRIPT_WORD3 11

/// Lexical states for SCLEX_PS
#define wxSCI_PS_DEFAULT 0
#define wxSCI_PS_COMMENT 1
#define wxSCI_PS_DSC_COMMENT 2
#define wxSCI_PS_DSC_VALUE 3
#define wxSCI_PS_NUMBER 4
#define wxSCI_PS_NAME 5
#define wxSCI_PS_KEYWORD 6
#define wxSCI_PS_LITERAL 7
#define wxSCI_PS_IMMEVAL 8
#define wxSCI_PS_PAREN_ARRAY 9
#define wxSCI_PS_PAREN_DICT 10
#define wxSCI_PS_PAREN_PROC 11
#define wxSCI_PS_TEXT 12
#define wxSCI_PS_HEXSTRING 13
#define wxSCI_PS_BASE85STRING 14
#define wxSCI_PS_BADSTRINGCHAR 15

/// Lexical states for SCLEX_NSIS
#define wxSCI_NSIS_DEFAULT 0
#define wxSCI_NSIS_COMMENT 1
#define wxSCI_NSIS_STRINGDQ 2
#define wxSCI_NSIS_STRINGLQ 3
#define wxSCI_NSIS_STRINGRQ 4
#define wxSCI_NSIS_FUNCTION 5
#define wxSCI_NSIS_VARIABLE 6
#define wxSCI_NSIS_LABEL 7
#define wxSCI_NSIS_USERDEFINED 8
#define wxSCI_NSIS_SECTIONDEF 9
#define wxSCI_NSIS_SUBSECTIONDEF 10
#define wxSCI_NSIS_IFDEFINEDEF 11
#define wxSCI_NSIS_MACRODEF 12
#define wxSCI_NSIS_STRINGVAR 13
#define wxSCI_NSIS_NUMBER 14
#define wxSCI_NSIS_SECTIONGROUP 15
#define wxSCI_NSIS_PAGEEX 16
#define wxSCI_NSIS_FUNCTIONDEF 17
#define wxSCI_NSIS_COMMENTBOX 18

/// Lexical states for SCLEX_MMIXAL
#define wxSCI_MMIXAL_LEADWS 0
#define wxSCI_MMIXAL_COMMENT 1
#define wxSCI_MMIXAL_LABEL 2
#define wxSCI_MMIXAL_OPCODE 3
#define wxSCI_MMIXAL_OPCODE_PRE 4
#define wxSCI_MMIXAL_OPCODE_VALID 5
#define wxSCI_MMIXAL_OPCODE_UNKNOWN 6
#define wxSCI_MMIXAL_OPCODE_POST 7
#define wxSCI_MMIXAL_OPERANDS 8
#define wxSCI_MMIXAL_NUMBER 9
#define wxSCI_MMIXAL_REF 10
#define wxSCI_MMIXAL_CHAR 11
#define wxSCI_MMIXAL_STRING 12
#define wxSCI_MMIXAL_REGISTER 13
#define wxSCI_MMIXAL_HEX 14
#define wxSCI_MMIXAL_OPERATOR 15
#define wxSCI_MMIXAL_SYMBOL 16
#define wxSCI_MMIXAL_INCLUDE 17

/// Lexical states for SCLEX_CLW
#define wxSCI_CLW_DEFAULT 0
#define wxSCI_CLW_LABEL 1
#define wxSCI_CLW_COMMENT 2
#define wxSCI_CLW_STRING 3
#define wxSCI_CLW_USER_IDENTIFIER 4
#define wxSCI_CLW_INTEGER_CONSTANT 5
#define wxSCI_CLW_REAL_CONSTANT 6
#define wxSCI_CLW_PICTURE_STRING 7
#define wxSCI_CLW_KEYWORD 8
#define wxSCI_CLW_COMPILER_DIRECTIVE 9
#define wxSCI_CLW_RUNTIME_EXPRESSIONS 10
#define wxSCI_CLW_BUILTIN_PROCEDURES_FUNCTION 11
#define wxSCI_CLW_STRUCTURE_DATA_TYPE 12
#define wxSCI_CLW_ATTRIBUTE 13
#define wxSCI_CLW_STANDARD_EQUATE 14
#define wxSCI_CLW_ERROR 15
#define wxSCI_CLW_DEPRECATED 16

/// Lexical states for SCLEX_LOT
#define wxSCI_LOT_DEFAULT 0
#define wxSCI_LOT_HEADER 1
#define wxSCI_LOT_BREAK 2
#define wxSCI_LOT_SET 3
#define wxSCI_LOT_PASS 4
#define wxSCI_LOT_FAIL 5
#define wxSCI_LOT_ABORT 6

/// Lexical states for SCLEX_YAML
#define wxSCI_YAML_DEFAULT 0
#define wxSCI_YAML_COMMENT 1
#define wxSCI_YAML_IDENTIFIER 2
#define wxSCI_YAML_KEYWORD 3
#define wxSCI_YAML_NUMBER 4
#define wxSCI_YAML_REFERENCE 5
#define wxSCI_YAML_DOCUMENT 6
#define wxSCI_YAML_TEXT 7
#define wxSCI_YAML_ERROR 8
#define wxSCI_YAML_OPERATOR 9

/// Lexical states for SCLEX_TEX
#define wxSCI_TEX_DEFAULT 0
#define wxSCI_TEX_SPECIAL 1
#define wxSCI_TEX_GROUP 2
#define wxSCI_TEX_SYMBOL 3
#define wxSCI_TEX_COMMAND 4
#define wxSCI_TEX_TEXT 5
#define wxSCI_METAPOST_DEFAULT 0
#define wxSCI_METAPOST_SPECIAL 1
#define wxSCI_METAPOST_GROUP 2
#define wxSCI_METAPOST_SYMBOL 3
#define wxSCI_METAPOST_COMMAND 4
#define wxSCI_METAPOST_TEXT 5
#define wxSCI_METAPOST_EXTRA 6

/// Lexical states for SCLEX_ERLANG
#define wxSCI_ERLANG_DEFAULT 0
#define wxSCI_ERLANG_COMMENT 1
#define wxSCI_ERLANG_VARIABLE 2
#define wxSCI_ERLANG_NUMBER 3
#define wxSCI_ERLANG_KEYWORD 4
#define wxSCI_ERLANG_STRING 5
#define wxSCI_ERLANG_OPERATOR 6
#define wxSCI_ERLANG_ATOM 7
#define wxSCI_ERLANG_FUNCTION_NAME 8
#define wxSCI_ERLANG_CHARACTER 9
#define wxSCI_ERLANG_MACRO 10
#define wxSCI_ERLANG_RECORD 11
#define wxSCI_ERLANG_PREPROC 12
#define wxSCI_ERLANG_NODE_NAME 13
#define wxSCI_ERLANG_COMMENT_FUNCTION 14
#define wxSCI_ERLANG_COMMENT_MODULE 15
#define wxSCI_ERLANG_COMMENT_DOC 16
#define wxSCI_ERLANG_COMMENT_DOC_MACRO 17
#define wxSCI_ERLANG_ATOM_QUOTED 18
#define wxSCI_ERLANG_MACRO_QUOTED 19
#define wxSCI_ERLANG_RECORD_QUOTED 20
#define wxSCI_ERLANG_NODE_NAME_QUOTED 21
#define wxSCI_ERLANG_BIFS 22
#define wxSCI_ERLANG_MODULES 23
#define wxSCI_ERLANG_MODULES_ATT 24
#define wxSCI_ERLANG_UNKNOWN 31

/// Lexical states for SCLEX_OCTAVE are identical to MatLab
/// Lexical states for SCLEX_MSSQL
#define wxSCI_MSSQL_DEFAULT 0
#define wxSCI_MSSQL_COMMENT 1
#define wxSCI_MSSQL_LINE_COMMENT 2
#define wxSCI_MSSQL_NUMBER 3
#define wxSCI_MSSQL_STRING 4
#define wxSCI_MSSQL_OPERATOR 5
#define wxSCI_MSSQL_IDENTIFIER 6
#define wxSCI_MSSQL_VARIABLE 7
#define wxSCI_MSSQL_COLUMN_NAME 8
#define wxSCI_MSSQL_STATEMENT 9
#define wxSCI_MSSQL_DATATYPE 10
#define wxSCI_MSSQL_SYSTABLE 11
#define wxSCI_MSSQL_GLOBAL_VARIABLE 12
#define wxSCI_MSSQL_FUNCTION 13
#define wxSCI_MSSQL_STORED_PROCEDURE 14
#define wxSCI_MSSQL_DEFAULT_PREF_DATATYPE 15
#define wxSCI_MSSQL_COLUMN_NAME_2 16

/// Lexical states for SCLEX_VERILOG
#define wxSCI_V_DEFAULT 0
#define wxSCI_V_COMMENT 1
#define wxSCI_V_COMMENTLINE 2
#define wxSCI_V_COMMENTLINEBANG 3
#define wxSCI_V_NUMBER 4
#define wxSCI_V_WORD 5
#define wxSCI_V_STRING 6
#define wxSCI_V_WORD2 7
#define wxSCI_V_WORD3 8
#define wxSCI_V_PREPROCESSOR 9
#define wxSCI_V_OPERATOR 10
#define wxSCI_V_IDENTIFIER 11
#define wxSCI_V_STRINGEOL 12
#define wxSCI_V_USER 19
#define wxSCI_V_COMMENT_WORD 20
#define wxSCI_V_INPUT 21
#define wxSCI_V_OUTPUT 22
#define wxSCI_V_INOUT 23
#define wxSCI_V_PORT_CONNECT 24

/// Lexical states for SCLEX_KIX
#define wxSCI_KIX_DEFAULT 0
#define wxSCI_KIX_COMMENT 1
#define wxSCI_KIX_STRING1 2
#define wxSCI_KIX_STRING2 3
#define wxSCI_KIX_NUMBER 4
#define wxSCI_KIX_VAR 5
#define wxSCI_KIX_MACRO 6
#define wxSCI_KIX_KEYWORD 7
#define wxSCI_KIX_FUNCTIONS 8
#define wxSCI_KIX_OPERATOR 9
#define wxSCI_KIX_COMMENTSTREAM 10
#define wxSCI_KIX_IDENTIFIER 31

/// Lexical states for SCLEX_GUI4CLI
#define wxSCI_GC_DEFAULT 0
#define wxSCI_GC_COMMENTLINE 1
#define wxSCI_GC_COMMENTBLOCK 2
#define wxSCI_GC_GLOBAL 3
#define wxSCI_GC_EVENT 4
#define wxSCI_GC_ATTRIBUTE 5
#define wxSCI_GC_CONTROL 6
#define wxSCI_GC_COMMAND 7
#define wxSCI_GC_STRING 8
#define wxSCI_GC_OPERATOR 9

/// Lexical states for SCLEX_SPECMAN
#define wxSCI_SN_DEFAULT 0
#define wxSCI_SN_CODE 1
#define wxSCI_SN_COMMENTLINE 2
#define wxSCI_SN_COMMENTLINEBANG 3
#define wxSCI_SN_NUMBER 4
#define wxSCI_SN_WORD 5
#define wxSCI_SN_STRING 6
#define wxSCI_SN_WORD2 7
#define wxSCI_SN_WORD3 8
#define wxSCI_SN_PREPROCESSOR 9
#define wxSCI_SN_OPERATOR 10
#define wxSCI_SN_IDENTIFIER 11
#define wxSCI_SN_STRINGEOL 12
#define wxSCI_SN_REGEXTAG 13
#define wxSCI_SN_SIGNAL 14
#define wxSCI_SN_USER 19

/// Lexical states for SCLEX_AU3
#define wxSCI_AU3_DEFAULT 0
#define wxSCI_AU3_COMMENT 1
#define wxSCI_AU3_COMMENTBLOCK 2
#define wxSCI_AU3_NUMBER 3
#define wxSCI_AU3_FUNCTION 4
#define wxSCI_AU3_KEYWORD 5
#define wxSCI_AU3_MACRO 6
#define wxSCI_AU3_STRING 7
#define wxSCI_AU3_OPERATOR 8
#define wxSCI_AU3_VARIABLE 9
#define wxSCI_AU3_SENT 10
#define wxSCI_AU3_PREPROCESSOR 11
#define wxSCI_AU3_SPECIAL 12
#define wxSCI_AU3_EXPAND 13
#define wxSCI_AU3_COMOBJ 14
#define wxSCI_AU3_UDF 15

/// Lexical states for SCLEX_APDL
#define wxSCI_APDL_DEFAULT 0
#define wxSCI_APDL_COMMENT 1
#define wxSCI_APDL_COMMENTBLOCK 2
#define wxSCI_APDL_NUMBER 3
#define wxSCI_APDL_STRING 4
#define wxSCI_APDL_OPERATOR 5
#define wxSCI_APDL_WORD 6
#define wxSCI_APDL_PROCESSOR 7
#define wxSCI_APDL_COMMAND 8
#define wxSCI_APDL_SLASHCOMMAND 9
#define wxSCI_APDL_STARCOMMAND 10
#define wxSCI_APDL_ARGUMENT 11
#define wxSCI_APDL_FUNCTION 12

/// Lexical states for SCLEX_BASH
#define wxSCI_SH_DEFAULT 0
#define wxSCI_SH_ERROR 1
#define wxSCI_SH_COMMENTLINE 2
#define wxSCI_SH_NUMBER 3
#define wxSCI_SH_WORD 4
#define wxSCI_SH_STRING 5
#define wxSCI_SH_CHARACTER 6
#define wxSCI_SH_OPERATOR 7
#define wxSCI_SH_IDENTIFIER 8
#define wxSCI_SH_SCALAR 9
#define wxSCI_SH_PARAM 10
#define wxSCI_SH_BACKTICKS 11
#define wxSCI_SH_HERE_DELIM 12
#define wxSCI_SH_HERE_Q 13

/// Lexical states for SCLEX_ASN1
#define wxSCI_ASN1_DEFAULT 0
#define wxSCI_ASN1_COMMENT 1
#define wxSCI_ASN1_IDENTIFIER 2
#define wxSCI_ASN1_STRING 3
#define wxSCI_ASN1_OID 4
#define wxSCI_ASN1_SCALAR 5
#define wxSCI_ASN1_KEYWORD 6
#define wxSCI_ASN1_ATTRIBUTE 7
#define wxSCI_ASN1_DESCRIPTOR 8
#define wxSCI_ASN1_TYPE 9
#define wxSCI_ASN1_OPERATOR 10

/// Lexical states for SCLEX_VHDL
#define wxSCI_VHDL_DEFAULT 0
#define wxSCI_VHDL_COMMENT 1
#define wxSCI_VHDL_COMMENTLINEBANG 2
#define wxSCI_VHDL_NUMBER 3
#define wxSCI_VHDL_STRING 4
#define wxSCI_VHDL_OPERATOR 5
#define wxSCI_VHDL_IDENTIFIER 6
#define wxSCI_VHDL_STRINGEOL 7
#define wxSCI_VHDL_KEYWORD 8
#define wxSCI_VHDL_STDOPERATOR 9
#define wxSCI_VHDL_ATTRIBUTE 10
#define wxSCI_VHDL_STDFUNCTION 11
#define wxSCI_VHDL_STDPACKAGE 12
#define wxSCI_VHDL_STDTYPE 13
#define wxSCI_VHDL_USERWORD 14
#define wxSCI_VHDL_BLOCK_COMMENT 15

/// Lexical states for SCLEX_CAML
#define wxSCI_CAML_DEFAULT 0
#define wxSCI_CAML_IDENTIFIER 1
#define wxSCI_CAML_TAGNAME 2
#define wxSCI_CAML_KEYWORD 3
#define wxSCI_CAML_KEYWORD2 4
#define wxSCI_CAML_KEYWORD3 5
#define wxSCI_CAML_LINENUM 6
#define wxSCI_CAML_OPERATOR 7
#define wxSCI_CAML_NUMBER 8
#define wxSCI_CAML_CHAR 9
#define wxSCI_CAML_WHITE 10
#define wxSCI_CAML_STRING 11
#define wxSCI_CAML_COMMENT 12
#define wxSCI_CAML_COMMENT1 13
#define wxSCI_CAML_COMMENT2 14
#define wxSCI_CAML_COMMENT3 15

/// Lexical states for SCLEX_HASKELL
#define wxSCI_HA_DEFAULT 0
#define wxSCI_HA_IDENTIFIER 1
#define wxSCI_HA_KEYWORD 2
#define wxSCI_HA_NUMBER 3
#define wxSCI_HA_STRING 4
#define wxSCI_HA_CHARACTER 5
#define wxSCI_HA_CLASS 6
#define wxSCI_HA_MODULE 7
#define wxSCI_HA_CAPITAL 8
#define wxSCI_HA_DATA 9
#define wxSCI_HA_IMPORT 10
#define wxSCI_HA_OPERATOR 11
#define wxSCI_HA_INSTANCE 12
#define wxSCI_HA_COMMENTLINE 13
#define wxSCI_HA_COMMENTBLOCK 14
#define wxSCI_HA_COMMENTBLOCK2 15
#define wxSCI_HA_COMMENTBLOCK3 16
#define wxSCI_HA_PRAGMA 17
#define wxSCI_HA_PREPROCESSOR 18
#define wxSCI_HA_STRINGEOL 19
#define wxSCI_HA_RESERVED_OPERATOR 20
#define wxSCI_HA_LITERATE_COMMENT 21
#define wxSCI_HA_LITERATE_CODEDELIM 22

/// Lexical states of SCLEX_TADS3
#define wxSCI_T3_DEFAULT 0
#define wxSCI_T3_X_DEFAULT 1
#define wxSCI_T3_PREPROCESSOR 2
#define wxSCI_T3_BLOCK_COMMENT 3
#define wxSCI_T3_LINE_COMMENT 4
#define wxSCI_T3_OPERATOR 5
#define wxSCI_T3_KEYWORD 6
#define wxSCI_T3_NUMBER 7
#define wxSCI_T3_IDENTIFIER 8
#define wxSCI_T3_S_STRING 9
#define wxSCI_T3_D_STRING 10
#define wxSCI_T3_X_STRING 11
#define wxSCI_T3_LIB_DIRECTIVE 12
#define wxSCI_T3_MSG_PARAM 13
#define wxSCI_T3_HTML_TAG 14
#define wxSCI_T3_HTML_DEFAULT 15
#define wxSCI_T3_HTML_STRING 16
#define wxSCI_T3_USER1 17
#define wxSCI_T3_USER2 18
#define wxSCI_T3_USER3 19
#define wxSCI_T3_BRACE 20

/// Lexical states for SCLEX_REBOL
#define wxSCI_REBOL_DEFAULT 0
#define wxSCI_REBOL_COMMENTLINE 1
#define wxSCI_REBOL_COMMENTBLOCK 2
#define wxSCI_REBOL_PREFACE 3
#define wxSCI_REBOL_OPERATOR 4
#define wxSCI_REBOL_CHARACTER 5
#define wxSCI_REBOL_QUOTEDSTRING 6
#define wxSCI_REBOL_BRACEDSTRING 7
#define wxSCI_REBOL_NUMBER 8
#define wxSCI_REBOL_PAIR 9
#define wxSCI_REBOL_TUPLE 10
#define wxSCI_REBOL_BINARY 11
#define wxSCI_REBOL_MONEY 12
#define wxSCI_REBOL_ISSUE 13
#define wxSCI_REBOL_TAG 14
#define wxSCI_REBOL_FILE 15
#define wxSCI_REBOL_EMAIL 16
#define wxSCI_REBOL_URL 17
#define wxSCI_REBOL_DATE 18
#define wxSCI_REBOL_TIME 19
#define wxSCI_REBOL_IDENTIFIER 20
#define wxSCI_REBOL_WORD 21
#define wxSCI_REBOL_WORD2 22
#define wxSCI_REBOL_WORD3 23
#define wxSCI_REBOL_WORD4 24
#define wxSCI_REBOL_WORD5 25
#define wxSCI_REBOL_WORD6 26
#define wxSCI_REBOL_WORD7 27
#define wxSCI_REBOL_WORD8 28

/// Lexical states for SCLEX_SQL
#define wxSCI_SQL_DEFAULT 0
#define wxSCI_SQL_COMMENT 1
#define wxSCI_SQL_COMMENTLINE 2
#define wxSCI_SQL_COMMENTDOC 3
#define wxSCI_SQL_NUMBER 4
#define wxSCI_SQL_WORD 5
#define wxSCI_SQL_STRING 6
#define wxSCI_SQL_CHARACTER 7
#define wxSCI_SQL_SQLPLUS 8
#define wxSCI_SQL_SQLPLUS_PROMPT 9
#define wxSCI_SQL_OPERATOR 10
#define wxSCI_SQL_IDENTIFIER 11
#define wxSCI_SQL_SQLPLUS_COMMENT 13
#define wxSCI_SQL_COMMENTLINEDOC 15
#define wxSCI_SQL_WORD2 16
#define wxSCI_SQL_COMMENTDOCKEYWORD 17
#define wxSCI_SQL_COMMENTDOCKEYWORDERROR 18
#define wxSCI_SQL_USER1 19
#define wxSCI_SQL_USER2 20
#define wxSCI_SQL_USER3 21
#define wxSCI_SQL_USER4 22
#define wxSCI_SQL_QUOTEDIDENTIFIER 23
#define wxSCI_SQL_QOPERATOR 24

/// Lexical states for SCLEX_SMALLTALK
#define wxSCI_ST_DEFAULT 0
#define wxSCI_ST_STRING 1
#define wxSCI_ST_NUMBER 2
#define wxSCI_ST_COMMENT 3
#define wxSCI_ST_SYMBOL 4
#define wxSCI_ST_BINARY 5
#define wxSCI_ST_BOOL 6
#define wxSCI_ST_SELF 7
#define wxSCI_ST_SUPER 8
#define wxSCI_ST_NIL 9
#define wxSCI_ST_GLOBAL 10
#define wxSCI_ST_RETURN 11
#define wxSCI_ST_SPECIAL 12
#define wxSCI_ST_KWSEND 13
#define wxSCI_ST_ASSIGN 14
#define wxSCI_ST_CHARACTER 15
#define wxSCI_ST_SPEC_SEL 16

/// Lexical states for SCLEX_FLAGSHIP (clipper)
#define wxSCI_FS_DEFAULT 0
#define wxSCI_FS_COMMENT 1
#define wxSCI_FS_COMMENTLINE 2
#define wxSCI_FS_COMMENTDOC 3
#define wxSCI_FS_COMMENTLINEDOC 4
#define wxSCI_FS_COMMENTDOCKEYWORD 5
#define wxSCI_FS_COMMENTDOCKEYWORDERROR 6
#define wxSCI_FS_KEYWORD 7
#define wxSCI_FS_KEYWORD2 8
#define wxSCI_FS_KEYWORD3 9
#define wxSCI_FS_KEYWORD4 10
#define wxSCI_FS_NUMBER 11
#define wxSCI_FS_STRING 12
#define wxSCI_FS_PREPROCESSOR 13
#define wxSCI_FS_OPERATOR 14
#define wxSCI_FS_IDENTIFIER 15
#define wxSCI_FS_DATE 16
#define wxSCI_FS_STRINGEOL 17
#define wxSCI_FS_CONSTANT 18
#define wxSCI_FS_WORDOPERATOR 19
#define wxSCI_FS_DISABLEDCODE 20
#define wxSCI_FS_DEFAULT_C 21
#define wxSCI_FS_COMMENTDOC_C 22
#define wxSCI_FS_COMMENTLINEDOC_C 23
#define wxSCI_FS_KEYWORD_C 24
#define wxSCI_FS_KEYWORD2_C 25
#define wxSCI_FS_NUMBER_C 26
#define wxSCI_FS_STRING_C 27
#define wxSCI_FS_PREPROCESSOR_C 28
#define wxSCI_FS_OPERATOR_C 29
#define wxSCI_FS_IDENTIFIER_C 30
#define wxSCI_FS_STRINGEOL_C 31

/// Lexical states for SCLEX_CSOUND
#define wxSCI_CSOUND_DEFAULT 0
#define wxSCI_CSOUND_COMMENT 1
#define wxSCI_CSOUND_NUMBER 2
#define wxSCI_CSOUND_OPERATOR 3
#define wxSCI_CSOUND_INSTR 4
#define wxSCI_CSOUND_IDENTIFIER 5
#define wxSCI_CSOUND_OPCODE 6
#define wxSCI_CSOUND_HEADERSTMT 7
#define wxSCI_CSOUND_USERKEYWORD 8
#define wxSCI_CSOUND_COMMENTBLOCK 9
#define wxSCI_CSOUND_PARAM 10
#define wxSCI_CSOUND_ARATE_VAR 11
#define wxSCI_CSOUND_KRATE_VAR 12
#define wxSCI_CSOUND_IRATE_VAR 13
#define wxSCI_CSOUND_GLOBAL_VAR 14
#define wxSCI_CSOUND_STRINGEOL 15

/// Lexical states for SCLEX_INNOSETUP
#define wxSCI_INNO_DEFAULT 0
#define wxSCI_INNO_COMMENT 1
#define wxSCI_INNO_KEYWORD 2
#define wxSCI_INNO_PARAMETER 3
#define wxSCI_INNO_SECTION 4
#define wxSCI_INNO_PREPROC 5
#define wxSCI_INNO_INLINE_EXPANSION 6
#define wxSCI_INNO_COMMENT_PASCAL 7
#define wxSCI_INNO_KEYWORD_PASCAL 8
#define wxSCI_INNO_KEYWORD_USER 9
#define wxSCI_INNO_STRING_DOUBLE 10
#define wxSCI_INNO_STRING_SINGLE 11
#define wxSCI_INNO_IDENTIFIER 12

/// Lexical states for SCLEX_OPAL
#define wxSCI_OPAL_SPACE 0
#define wxSCI_OPAL_COMMENT_BLOCK 1
#define wxSCI_OPAL_COMMENT_LINE 2
#define wxSCI_OPAL_INTEGER 3
#define wxSCI_OPAL_KEYWORD 4
#define wxSCI_OPAL_SORT 5
#define wxSCI_OPAL_STRING 6
#define wxSCI_OPAL_PAR 7
#define wxSCI_OPAL_BOOL_CONST 8
#define wxSCI_OPAL_DEFAULT 32

/// Lexical states for SCLEX_SPICE
#define wxSCI_SPICE_DEFAULT 0
#define wxSCI_SPICE_IDENTIFIER 1
#define wxSCI_SPICE_KEYWORD 2
#define wxSCI_SPICE_KEYWORD2 3
#define wxSCI_SPICE_KEYWORD3 4
#define wxSCI_SPICE_NUMBER 5
#define wxSCI_SPICE_DELIMITER 6
#define wxSCI_SPICE_VALUE 7
#define wxSCI_SPICE_COMMENTLINE 8

/// Lexical states for SCLEX_CMAKE
#define wxSCI_CMAKE_DEFAULT 0
#define wxSCI_CMAKE_COMMENT 1
#define wxSCI_CMAKE_STRINGDQ 2
#define wxSCI_CMAKE_STRINGLQ 3
#define wxSCI_CMAKE_STRINGRQ 4
#define wxSCI_CMAKE_COMMANDS 5
#define wxSCI_CMAKE_PARAMETERS 6
#define wxSCI_CMAKE_VARIABLE 7
#define wxSCI_CMAKE_USERDEFINED 8
#define wxSCI_CMAKE_WHILEDEF 9
#define wxSCI_CMAKE_FOREACHDEF 10
#define wxSCI_CMAKE_IFDEFINEDEF 11
#define wxSCI_CMAKE_MACRODEF 12
#define wxSCI_CMAKE_STRINGVAR 13
#define wxSCI_CMAKE_NUMBER 14

/// Lexical states for SCLEX_GAP
#define wxSCI_GAP_DEFAULT 0
#define wxSCI_GAP_IDENTIFIER 1
#define wxSCI_GAP_KEYWORD 2
#define wxSCI_GAP_KEYWORD2 3
#define wxSCI_GAP_KEYWORD3 4
#define wxSCI_GAP_KEYWORD4 5
#define wxSCI_GAP_STRING 6
#define wxSCI_GAP_CHAR 7
#define wxSCI_GAP_OPERATOR 8
#define wxSCI_GAP_COMMENT 9
#define wxSCI_GAP_NUMBER 10
#define wxSCI_GAP_STRINGEOL 11

/// Lexical state for SCLEX_PLM
#define wxSCI_PLM_DEFAULT 0
#define wxSCI_PLM_COMMENT 1
#define wxSCI_PLM_STRING 2
#define wxSCI_PLM_NUMBER 3
#define wxSCI_PLM_IDENTIFIER 4
#define wxSCI_PLM_OPERATOR 5
#define wxSCI_PLM_CONTROL 6
#define wxSCI_PLM_KEYWORD 7

/// Lexical state for SCLEX_PROGRESS
#define wxSCI_ABL_DEFAULT 0
#define wxSCI_ABL_NUMBER 1
#define wxSCI_ABL_WORD 2
#define wxSCI_ABL_STRING 3
#define wxSCI_ABL_CHARACTER 4
#define wxSCI_ABL_PREPROCESSOR 5
#define wxSCI_ABL_OPERATOR 6
#define wxSCI_ABL_IDENTIFIER 7
#define wxSCI_ABL_BLOCK 8
#define wxSCI_ABL_END 9
#define wxSCI_ABL_COMMENT 10
#define wxSCI_ABL_TASKMARKER 11
#define wxSCI_ABL_LINECOMMENT 12

/// Lexical states for SCLEX_ABAQUS
#define wxSCI_ABAQUS_DEFAULT 0
#define wxSCI_ABAQUS_COMMENT 1
#define wxSCI_ABAQUS_COMMENTBLOCK 2
#define wxSCI_ABAQUS_NUMBER 3
#define wxSCI_ABAQUS_STRING 4
#define wxSCI_ABAQUS_OPERATOR 5
#define wxSCI_ABAQUS_WORD 6
#define wxSCI_ABAQUS_PROCESSOR 7
#define wxSCI_ABAQUS_COMMAND 8
#define wxSCI_ABAQUS_SLASHCOMMAND 9
#define wxSCI_ABAQUS_STARCOMMAND 10
#define wxSCI_ABAQUS_ARGUMENT 11
#define wxSCI_ABAQUS_FUNCTION 12

/// Lexical states for SCLEX_ASYMPTOTE
#define wxSCI_ASY_DEFAULT 0
#define wxSCI_ASY_COMMENT 1
#define wxSCI_ASY_COMMENTLINE 2
#define wxSCI_ASY_NUMBER 3
#define wxSCI_ASY_WORD 4
#define wxSCI_ASY_STRING 5
#define wxSCI_ASY_CHARACTER 6
#define wxSCI_ASY_OPERATOR 7
#define wxSCI_ASY_IDENTIFIER 8
#define wxSCI_ASY_STRINGEOL 9
#define wxSCI_ASY_COMMENTLINEDOC 10
#define wxSCI_ASY_WORD2 11

/// Lexical states for SCLEX_R
#define wxSCI_R_DEFAULT 0
#define wxSCI_R_COMMENT 1
#define wxSCI_R_KWORD 2
#define wxSCI_R_BASEKWORD 3
#define wxSCI_R_OTHERKWORD 4
#define wxSCI_R_NUMBER 5
#define wxSCI_R_STRING 6
#define wxSCI_R_STRING2 7
#define wxSCI_R_OPERATOR 8
#define wxSCI_R_IDENTIFIER 9
#define wxSCI_R_INFIX 10
#define wxSCI_R_INFIXEOL 11

/// Lexical state for SCLEX_MAGIK
#define wxSCI_MAGIK_DEFAULT 0
#define wxSCI_MAGIK_COMMENT 1
#define wxSCI_MAGIK_HYPER_COMMENT 16
#define wxSCI_MAGIK_STRING 2
#define wxSCI_MAGIK_CHARACTER 3
#define wxSCI_MAGIK_NUMBER 4
#define wxSCI_MAGIK_IDENTIFIER 5
#define wxSCI_MAGIK_OPERATOR 6
#define wxSCI_MAGIK_FLOW 7
#define wxSCI_MAGIK_CONTAINER 8
#define wxSCI_MAGIK_BRACKET_BLOCK 9
#define wxSCI_MAGIK_BRACE_BLOCK 10
#define wxSCI_MAGIK_SQBRACKET_BLOCK 11
#define wxSCI_MAGIK_UNKNOWN_KEYWORD 12
#define wxSCI_MAGIK_KEYWORD 13
#define wxSCI_MAGIK_PRAGMA 14
#define wxSCI_MAGIK_SYMBOL 15

/// Lexical state for SCLEX_POWERSHELL
#define wxSCI_POWERSHELL_DEFAULT 0
#define wxSCI_POWERSHELL_COMMENT 1
#define wxSCI_POWERSHELL_STRING 2
#define wxSCI_POWERSHELL_CHARACTER 3
#define wxSCI_POWERSHELL_NUMBER 4
#define wxSCI_POWERSHELL_VARIABLE 5
#define wxSCI_POWERSHELL_OPERATOR 6
#define wxSCI_POWERSHELL_IDENTIFIER 7
#define wxSCI_POWERSHELL_KEYWORD 8
#define wxSCI_POWERSHELL_CMDLET 9
#define wxSCI_POWERSHELL_ALIAS 10
#define wxSCI_POWERSHELL_FUNCTION 11
#define wxSCI_POWERSHELL_USER1 12
#define wxSCI_POWERSHELL_COMMENTSTREAM 13
#define wxSCI_POWERSHELL_HERE_STRING 14
#define wxSCI_POWERSHELL_HERE_CHARACTER 15
#define wxSCI_POWERSHELL_COMMENTDOCKEYWORD 16

/// Lexical state for SCLEX_MYSQL
#define wxSCI_MYSQL_DEFAULT 0
#define wxSCI_MYSQL_COMMENT 1
#define wxSCI_MYSQL_COMMENTLINE 2
#define wxSCI_MYSQL_VARIABLE 3
#define wxSCI_MYSQL_SYSTEMVARIABLE 4
#define wxSCI_MYSQL_KNOWNSYSTEMVARIABLE 5
#define wxSCI_MYSQL_NUMBER 6
#define wxSCI_MYSQL_MAJORKEYWORD 7
#define wxSCI_MYSQL_KEYWORD 8
#define wxSCI_MYSQL_DATABASEOBJECT 9
#define wxSCI_MYSQL_PROCEDUREKEYWORD 10
#define wxSCI_MYSQL_STRING 11
#define wxSCI_MYSQL_SQSTRING 12
#define wxSCI_MYSQL_DQSTRING 13
#define wxSCI_MYSQL_OPERATOR 14
#define wxSCI_MYSQL_FUNCTION 15
#define wxSCI_MYSQL_IDENTIFIER 16
#define wxSCI_MYSQL_QUOTEDIDENTIFIER 17
#define wxSCI_MYSQL_USER1 18
#define wxSCI_MYSQL_USER2 19
#define wxSCI_MYSQL_USER3 20
#define wxSCI_MYSQL_HIDDENCOMMAND 21
#define wxSCI_MYSQL_PLACEHOLDER 22

/// Lexical state for SCLEX_PO
#define wxSCI_PO_DEFAULT 0
#define wxSCI_PO_COMMENT 1
#define wxSCI_PO_MSGID 2
#define wxSCI_PO_MSGID_TEXT 3
#define wxSCI_PO_MSGSTR 4
#define wxSCI_PO_MSGSTR_TEXT 5
#define wxSCI_PO_MSGCTXT 6
#define wxSCI_PO_MSGCTXT_TEXT 7
#define wxSCI_PO_FUZZY 8
#define wxSCI_PO_PROGRAMMER_COMMENT 9
#define wxSCI_PO_REFERENCE 10
#define wxSCI_PO_FLAGS 11
#define wxSCI_PO_MSGID_TEXT_EOL 12
#define wxSCI_PO_MSGSTR_TEXT_EOL 13
#define wxSCI_PO_MSGCTXT_TEXT_EOL 14
#define wxSCI_PO_ERROR 15

/// Lexical states for SCLEX_PASCAL
#define wxSCI_PAS_DEFAULT 0
#define wxSCI_PAS_IDENTIFIER 1
#define wxSCI_PAS_COMMENT 2
#define wxSCI_PAS_COMMENT2 3
#define wxSCI_PAS_COMMENTLINE 4
#define wxSCI_PAS_PREPROCESSOR 5
#define wxSCI_PAS_PREPROCESSOR2 6
#define wxSCI_PAS_NUMBER 7
#define wxSCI_PAS_HEXNUMBER 8
#define wxSCI_PAS_WORD 9
#define wxSCI_PAS_STRING 10
#define wxSCI_PAS_STRINGEOL 11
#define wxSCI_PAS_CHARACTER 12
#define wxSCI_PAS_OPERATOR 13
#define wxSCI_PAS_ASM 14

/// Lexical state for SCLEX_SORCUS
#define wxSCI_SORCUS_DEFAULT 0
#define wxSCI_SORCUS_COMMAND 1
#define wxSCI_SORCUS_PARAMETER 2
#define wxSCI_SORCUS_COMMENTLINE 3
#define wxSCI_SORCUS_STRING 4
#define wxSCI_SORCUS_STRINGEOL 5
#define wxSCI_SORCUS_IDENTIFIER 6
#define wxSCI_SORCUS_OPERATOR 7
#define wxSCI_SORCUS_NUMBER 8
#define wxSCI_SORCUS_CONSTANT 9

/// Lexical state for SCLEX_POWERPRO
#define wxSCI_POWERPRO_DEFAULT 0
#define wxSCI_POWERPRO_COMMENTBLOCK 1
#define wxSCI_POWERPRO_COMMENTLINE 2
#define wxSCI_POWERPRO_NUMBER 3
#define wxSCI_POWERPRO_WORD 4
#define wxSCI_POWERPRO_WORD2 5
#define wxSCI_POWERPRO_WORD3 6
#define wxSCI_POWERPRO_WORD4 7
#define wxSCI_POWERPRO_DOUBLEQUOTEDSTRING 8
#define wxSCI_POWERPRO_SINGLEQUOTEDSTRING 9
#define wxSCI_POWERPRO_LINECONTINUE 10
#define wxSCI_POWERPRO_OPERATOR 11
#define wxSCI_POWERPRO_IDENTIFIER 12
#define wxSCI_POWERPRO_STRINGEOL 13
#define wxSCI_POWERPRO_VERBATIM 14
#define wxSCI_POWERPRO_ALTQUOTE 15
#define wxSCI_POWERPRO_FUNCTION 16

/// Lexical states for SCLEX_SML
#define wxSCI_SML_DEFAULT 0
#define wxSCI_SML_IDENTIFIER 1
#define wxSCI_SML_TAGNAME 2
#define wxSCI_SML_KEYWORD 3
#define wxSCI_SML_KEYWORD2 4
#define wxSCI_SML_KEYWORD3 5
#define wxSCI_SML_LINENUM 6
#define wxSCI_SML_OPERATOR 7
#define wxSCI_SML_NUMBER 8
#define wxSCI_SML_CHAR 9
#define wxSCI_SML_STRING 11
#define wxSCI_SML_COMMENT 12
#define wxSCI_SML_COMMENT1 13
#define wxSCI_SML_COMMENT2 14
#define wxSCI_SML_COMMENT3 15

/// Lexical state for SCLEX_MARKDOWN
#define wxSCI_MARKDOWN_DEFAULT 0
#define wxSCI_MARKDOWN_LINE_BEGIN 1
#define wxSCI_MARKDOWN_STRONG1 2
#define wxSCI_MARKDOWN_STRONG2 3
#define wxSCI_MARKDOWN_EM1 4
#define wxSCI_MARKDOWN_EM2 5
#define wxSCI_MARKDOWN_HEADER1 6
#define wxSCI_MARKDOWN_HEADER2 7
#define wxSCI_MARKDOWN_HEADER3 8
#define wxSCI_MARKDOWN_HEADER4 9
#define wxSCI_MARKDOWN_HEADER5 10
#define wxSCI_MARKDOWN_HEADER6 11
#define wxSCI_MARKDOWN_PRECHAR 12
#define wxSCI_MARKDOWN_ULIST_ITEM 13
#define wxSCI_MARKDOWN_OLIST_ITEM 14
#define wxSCI_MARKDOWN_BLOCKQUOTE 15
#define wxSCI_MARKDOWN_STRIKEOUT 16
#define wxSCI_MARKDOWN_HRULE 17
#define wxSCI_MARKDOWN_LINK 18
#define wxSCI_MARKDOWN_CODE 19
#define wxSCI_MARKDOWN_CODE2 20
#define wxSCI_MARKDOWN_CODEBK 21

/// Lexical state for SCLEX_TXT2TAGS
#define wxSCI_TXT2TAGS_DEFAULT 0
#define wxSCI_TXT2TAGS_LINE_BEGIN 1
#define wxSCI_TXT2TAGS_STRONG1 2
#define wxSCI_TXT2TAGS_STRONG2 3
#define wxSCI_TXT2TAGS_EM1 4
#define wxSCI_TXT2TAGS_EM2 5
#define wxSCI_TXT2TAGS_HEADER1 6
#define wxSCI_TXT2TAGS_HEADER2 7
#define wxSCI_TXT2TAGS_HEADER3 8
#define wxSCI_TXT2TAGS_HEADER4 9
#define wxSCI_TXT2TAGS_HEADER5 10
#define wxSCI_TXT2TAGS_HEADER6 11
#define wxSCI_TXT2TAGS_PRECHAR 12
#define wxSCI_TXT2TAGS_ULIST_ITEM 13
#define wxSCI_TXT2TAGS_OLIST_ITEM 14
#define wxSCI_TXT2TAGS_BLOCKQUOTE 15
#define wxSCI_TXT2TAGS_STRIKEOUT 16
#define wxSCI_TXT2TAGS_HRULE 17
#define wxSCI_TXT2TAGS_LINK 18
#define wxSCI_TXT2TAGS_CODE 19
#define wxSCI_TXT2TAGS_CODE2 20
#define wxSCI_TXT2TAGS_CODEBK 21
#define wxSCI_TXT2TAGS_COMMENT 22
#define wxSCI_TXT2TAGS_OPTION 23
#define wxSCI_TXT2TAGS_PREPROC 24
#define wxSCI_TXT2TAGS_POSTPROC 25

/// Lexical states for SCLEX_A68K
#define wxSCI_A68K_DEFAULT 0
#define wxSCI_A68K_COMMENT 1
#define wxSCI_A68K_NUMBER_DEC 2
#define wxSCI_A68K_NUMBER_BIN 3
#define wxSCI_A68K_NUMBER_HEX 4
#define wxSCI_A68K_STRING1 5
#define wxSCI_A68K_OPERATOR 6
#define wxSCI_A68K_CPUINSTRUCTION 7
#define wxSCI_A68K_EXTINSTRUCTION 8
#define wxSCI_A68K_REGISTER 9
#define wxSCI_A68K_DIRECTIVE 10
#define wxSCI_A68K_MACRO_ARG 11
#define wxSCI_A68K_LABEL 12
#define wxSCI_A68K_STRING2 13
#define wxSCI_A68K_IDENTIFIER 14
#define wxSCI_A68K_MACRO_DECLARATION 15
#define wxSCI_A68K_COMMENT_WORD 16
#define wxSCI_A68K_COMMENT_SPECIAL 17
#define wxSCI_A68K_COMMENT_DOXYGEN 18

/// Lexical states for SCLEX_MODULA
#define wxSCI_MODULA_DEFAULT 0
#define wxSCI_MODULA_COMMENT 1
#define wxSCI_MODULA_DOXYCOMM 2
#define wxSCI_MODULA_DOXYKEY 3
#define wxSCI_MODULA_KEYWORD 4
#define wxSCI_MODULA_RESERVED 5
#define wxSCI_MODULA_NUMBER 6
#define wxSCI_MODULA_BASENUM 7
#define wxSCI_MODULA_FLOAT 8
#define wxSCI_MODULA_STRING 9
#define wxSCI_MODULA_STRSPEC 10
#define wxSCI_MODULA_CHAR 11
#define wxSCI_MODULA_CHARSPEC 12
#define wxSCI_MODULA_PROC 13
#define wxSCI_MODULA_PRAGMA 14
#define wxSCI_MODULA_PRGKEY 15
#define wxSCI_MODULA_OPERATOR 16
#define wxSCI_MODULA_BADSTR 17

/// Lexical states for SCLEX_COFFEESCRIPT
#define wxSCI_COFFEESCRIPT_DEFAULT 0
#define wxSCI_COFFEESCRIPT_COMMENT 1
#define wxSCI_COFFEESCRIPT_COMMENTLINE 2
#define wxSCI_COFFEESCRIPT_COMMENTDOC 3
#define wxSCI_COFFEESCRIPT_NUMBER 4
#define wxSCI_COFFEESCRIPT_WORD 5
#define wxSCI_COFFEESCRIPT_STRING 6
#define wxSCI_COFFEESCRIPT_CHARACTER 7
#define wxSCI_COFFEESCRIPT_UUID 8
#define wxSCI_COFFEESCRIPT_PREPROCESSOR 9
#define wxSCI_COFFEESCRIPT_OPERATOR 10
#define wxSCI_COFFEESCRIPT_IDENTIFIER 11
#define wxSCI_COFFEESCRIPT_STRINGEOL 12
#define wxSCI_COFFEESCRIPT_VERBATIM 13
#define wxSCI_COFFEESCRIPT_REGEX 14
#define wxSCI_COFFEESCRIPT_COMMENTLINEDOC 15
#define wxSCI_COFFEESCRIPT_WORD2 16
#define wxSCI_COFFEESCRIPT_COMMENTDOCKEYWORD 17
#define wxSCI_COFFEESCRIPT_COMMENTDOCKEYWORDERROR 18
#define wxSCI_COFFEESCRIPT_GLOBALCLASS 19
#define wxSCI_COFFEESCRIPT_STRINGRAW 20
#define wxSCI_COFFEESCRIPT_TRIPLEVERBATIM 21
#define wxSCI_COFFEESCRIPT_COMMENTBLOCK 22
#define wxSCI_COFFEESCRIPT_VERBOSE_REGEX 23
#define wxSCI_COFFEESCRIPT_VERBOSE_REGEX_COMMENT 24
#define wxSCI_COFFEESCRIPT_INSTANCEPROPERTY 25

/// Lexical states for SCLEX_AVS
#define wxSCI_AVS_DEFAULT 0
#define wxSCI_AVS_COMMENTBLOCK 1
#define wxSCI_AVS_COMMENTBLOCKN 2
#define wxSCI_AVS_COMMENTLINE 3
#define wxSCI_AVS_NUMBER 4
#define wxSCI_AVS_OPERATOR 5
#define wxSCI_AVS_IDENTIFIER 6
#define wxSCI_AVS_STRING 7
#define wxSCI_AVS_TRIPLESTRING 8
#define wxSCI_AVS_KEYWORD 9
#define wxSCI_AVS_FILTER 10
#define wxSCI_AVS_PLUGIN 11
#define wxSCI_AVS_FUNCTION 12
#define wxSCI_AVS_CLIPPROP 13
#define wxSCI_AVS_USERDFN 14

/// Lexical states for SCLEX_ECL
#define wxSCI_ECL_DEFAULT 0
#define wxSCI_ECL_COMMENT 1
#define wxSCI_ECL_COMMENTLINE 2
#define wxSCI_ECL_NUMBER 3
#define wxSCI_ECL_STRING 4
#define wxSCI_ECL_WORD0 5
#define wxSCI_ECL_OPERATOR 6
#define wxSCI_ECL_CHARACTER 7
#define wxSCI_ECL_UUID 8
#define wxSCI_ECL_PREPROCESSOR 9
#define wxSCI_ECL_UNKNOWN 10
#define wxSCI_ECL_IDENTIFIER 11
#define wxSCI_ECL_STRINGEOL 12
#define wxSCI_ECL_VERBATIM 13
#define wxSCI_ECL_REGEX 14
#define wxSCI_ECL_COMMENTLINEDOC 15
#define wxSCI_ECL_WORD1 16
#define wxSCI_ECL_COMMENTDOCKEYWORD 17
#define wxSCI_ECL_COMMENTDOCKEYWORDERROR 18
#define wxSCI_ECL_WORD2 19
#define wxSCI_ECL_WORD3 20
#define wxSCI_ECL_WORD4 21
#define wxSCI_ECL_WORD5 22
#define wxSCI_ECL_COMMENTDOC 23
#define wxSCI_ECL_ADDED 24
#define wxSCI_ECL_DELETED 25
#define wxSCI_ECL_CHANGED 26
#define wxSCI_ECL_MOVED 27

/// Lexical states for SCLEX_OSCRIPT
#define wxSCI_OSCRIPT_DEFAULT 0
#define wxSCI_OSCRIPT_LINE_COMMENT 1
#define wxSCI_OSCRIPT_BLOCK_COMMENT 2
#define wxSCI_OSCRIPT_DOC_COMMENT 3
#define wxSCI_OSCRIPT_PREPROCESSOR 4
#define wxSCI_OSCRIPT_NUMBER 5
#define wxSCI_OSCRIPT_SINGLEQUOTE_STRING 6
#define wxSCI_OSCRIPT_DOUBLEQUOTE_STRING 7
#define wxSCI_OSCRIPT_CONSTANT 8
#define wxSCI_OSCRIPT_IDENTIFIER 9
#define wxSCI_OSCRIPT_GLOBAL 10
#define wxSCI_OSCRIPT_KEYWORD 11
#define wxSCI_OSCRIPT_OPERATOR 12
#define wxSCI_OSCRIPT_LABEL 13
#define wxSCI_OSCRIPT_TYPE 14
#define wxSCI_OSCRIPT_FUNCTION 15
#define wxSCI_OSCRIPT_OBJECT 16
#define wxSCI_OSCRIPT_PROPERTY 17
#define wxSCI_OSCRIPT_METHOD 18

/// Lexical states for SCLEX_VISUALPROLOG
#define wxSCI_VISUALPROLOG_DEFAULT 0
#define wxSCI_VISUALPROLOG_KEY_MAJOR 1
#define wxSCI_VISUALPROLOG_KEY_MINOR 2
#define wxSCI_VISUALPROLOG_KEY_DIRECTIVE 3
#define wxSCI_VISUALPROLOG_COMMENT_BLOCK 4
#define wxSCI_VISUALPROLOG_COMMENT_LINE 5
#define wxSCI_VISUALPROLOG_COMMENT_KEY 6
#define wxSCI_VISUALPROLOG_COMMENT_KEY_ERROR 7
#define wxSCI_VISUALPROLOG_IDENTIFIER 8
#define wxSCI_VISUALPROLOG_VARIABLE 9
#define wxSCI_VISUALPROLOG_ANONYMOUS 10
#define wxSCI_VISUALPROLOG_NUMBER 11
#define wxSCI_VISUALPROLOG_OPERATOR 12
#define wxSCI_VISUALPROLOG_CHARACTER 13
#define wxSCI_VISUALPROLOG_CHARACTER_TOO_MANY 14
#define wxSCI_VISUALPROLOG_CHARACTER_ESCAPE_ERROR 15
#define wxSCI_VISUALPROLOG_STRING 16
#define wxSCI_VISUALPROLOG_STRING_ESCAPE 17
#define wxSCI_VISUALPROLOG_STRING_ESCAPE_ERROR 18
#define wxSCI_VISUALPROLOG_STRING_EOL_OPEN 19
#define wxSCI_VISUALPROLOG_STRING_VERBATIM 20
#define wxSCI_VISUALPROLOG_STRING_VERBATIM_SPECIAL 21
#define wxSCI_VISUALPROLOG_STRING_VERBATIM_EOL 22

/// Lexical states for SCLEX_STTXT
#define wxSCI_STTXT_DEFAULT 0
#define wxSCI_STTXT_COMMENT 1
#define wxSCI_STTXT_COMMENTLINE 2
#define wxSCI_STTXT_KEYWORD 3
#define wxSCI_STTXT_TYPE 4
#define wxSCI_STTXT_FUNCTION 5
#define wxSCI_STTXT_FB 6
#define wxSCI_STTXT_NUMBER 7
#define wxSCI_STTXT_HEXNUMBER 8
#define wxSCI_STTXT_PRAGMA 9
#define wxSCI_STTXT_OPERATOR 10
#define wxSCI_STTXT_CHARACTER 11
#define wxSCI_STTXT_STRING1 12
#define wxSCI_STTXT_STRING2 13
#define wxSCI_STTXT_STRINGEOL 14
#define wxSCI_STTXT_IDENTIFIER 15
#define wxSCI_STTXT_DATETIME 16
#define wxSCI_STTXT_VARS 17
#define wxSCI_STTXT_PRAGMAS 18

/// Lexical states for SCLEX_KVIRC
#define wxSCI_KVIRC_DEFAULT 0
#define wxSCI_KVIRC_COMMENT 1
#define wxSCI_KVIRC_COMMENTBLOCK 2
#define wxSCI_KVIRC_STRING 3
#define wxSCI_KVIRC_WORD 4
#define wxSCI_KVIRC_KEYWORD 5
#define wxSCI_KVIRC_FUNCTION_KEYWORD 6
#define wxSCI_KVIRC_FUNCTION 7
#define wxSCI_KVIRC_VARIABLE 8
#define wxSCI_KVIRC_NUMBER 9
#define wxSCI_KVIRC_OPERATOR 10
#define wxSCI_KVIRC_STRING_FUNCTION 11
#define wxSCI_KVIRC_STRING_VARIABLE 12

/// Lexical states for SCLEX_RUST
#define wxSCI_RUST_DEFAULT 0
#define wxSCI_RUST_COMMENTBLOCK 1
#define wxSCI_RUST_COMMENTLINE 2
#define wxSCI_RUST_COMMENTBLOCKDOC 3
#define wxSCI_RUST_COMMENTLINEDOC 4
#define wxSCI_RUST_NUMBER 5
#define wxSCI_RUST_WORD 6
#define wxSCI_RUST_WORD2 7
#define wxSCI_RUST_WORD3 8
#define wxSCI_RUST_WORD4 9
#define wxSCI_RUST_WORD5 10
#define wxSCI_RUST_WORD6 11
#define wxSCI_RUST_WORD7 12
#define wxSCI_RUST_STRING 13
#define wxSCI_RUST_STRINGR 14
#define wxSCI_RUST_CHARACTER 15
#define wxSCI_RUST_OPERATOR 16
#define wxSCI_RUST_IDENTIFIER 17
#define wxSCI_RUST_LIFETIME 18
#define wxSCI_RUST_MACRO 19
#define wxSCI_RUST_LEXERROR 20
#define wxSCI_RUST_BYTESTRING 21
#define wxSCI_RUST_BYTESTRINGR 22
#define wxSCI_RUST_BYTECHARACTER 23

/// Lexical states for SCLEX_DMAP
#define wxSCI_DMAP_DEFAULT 0
#define wxSCI_DMAP_COMMENT 1
#define wxSCI_DMAP_NUMBER 2
#define wxSCI_DMAP_STRING1 3
#define wxSCI_DMAP_STRING2 4
#define wxSCI_DMAP_STRINGEOL 5
#define wxSCI_DMAP_OPERATOR 6
#define wxSCI_DMAP_IDENTIFIER 7
#define wxSCI_DMAP_WORD 8
#define wxSCI_DMAP_WORD2 9
#define wxSCI_DMAP_WORD3 10

/// Lexical states for SCLEX_DMIS
#define wxSCI_DMIS_DEFAULT 0
#define wxSCI_DMIS_COMMENT 1
#define wxSCI_DMIS_STRING 2
#define wxSCI_DMIS_NUMBER 3
#define wxSCI_DMIS_KEYWORD 4
#define wxSCI_DMIS_MAJORWORD 5
#define wxSCI_DMIS_MINORWORD 6
#define wxSCI_DMIS_UNSUPPORTED_MAJOR 7
#define wxSCI_DMIS_UNSUPPORTED_MINOR 8
#define wxSCI_DMIS_LABEL 9

/// Lexical states for SCLEX_REGISTRY
#define wxSCI_REG_DEFAULT 0
#define wxSCI_REG_COMMENT 1
#define wxSCI_REG_VALUENAME 2
#define wxSCI_REG_STRING 3
#define wxSCI_REG_HEXDIGIT 4
#define wxSCI_REG_VALUETYPE 5
#define wxSCI_REG_ADDEDKEY 6
#define wxSCI_REG_DELETEDKEY 7
#define wxSCI_REG_ESCAPED 8
#define wxSCI_REG_KEYPATH_GUID 9
#define wxSCI_REG_STRING_GUID 10
#define wxSCI_REG_PARAMETER 11
#define wxSCI_REG_OPERATOR 12

/// Lexical state for SCLEX_BIBTEX
#define wxSCI_BIBTEX_DEFAULT 0
#define wxSCI_BIBTEX_ENTRY 1
#define wxSCI_BIBTEX_UNKNOWN_ENTRY 2
#define wxSCI_BIBTEX_KEY 3
#define wxSCI_BIBTEX_PARAMETER 4
#define wxSCI_BIBTEX_VALUE 5
#define wxSCI_BIBTEX_COMMENT 6

/// Lexical state for SCLEX_SREC
#define wxSCI_HEX_DEFAULT 0
#define wxSCI_HEX_RECSTART 1
#define wxSCI_HEX_RECTYPE 2
#define wxSCI_HEX_RECTYPE_UNKNOWN 3
#define wxSCI_HEX_BYTECOUNT 4
#define wxSCI_HEX_BYTECOUNT_WRONG 5
#define wxSCI_HEX_NOADDRESS 6
#define wxSCI_HEX_DATAADDRESS 7
#define wxSCI_HEX_RECCOUNT 8
#define wxSCI_HEX_STARTADDRESS 9
#define wxSCI_HEX_ADDRESSFIELD_UNKNOWN 10
#define wxSCI_HEX_EXTENDEDADDRESS 11
#define wxSCI_HEX_DATA_ODD 12
#define wxSCI_HEX_DATA_EVEN 13
#define wxSCI_HEX_DATA_UNKNOWN 14
#define wxSCI_HEX_DATA_EMPTY 15
#define wxSCI_HEX_CHECKSUM 16
#define wxSCI_HEX_CHECKSUM_WRONG 17
#define wxSCI_HEX_GARBAGE 18

/// Lexical state for SCLEX_IHEX (shared with Srec)
/// Lexical state for SCLEX_TEHEX (shared with Srec)
/// Lexical states for SCLEX_JSON
#define wxSCI_JSON_DEFAULT 0
#define wxSCI_JSON_NUMBER 1
#define wxSCI_JSON_STRING 2
#define wxSCI_JSON_STRINGEOL 3
#define wxSCI_JSON_PROPERTYNAME 4
#define wxSCI_JSON_ESCAPESEQUENCE 5
#define wxSCI_JSON_LINECOMMENT 6
#define wxSCI_JSON_BLOCKCOMMENT 7
#define wxSCI_JSON_OPERATOR 8
#define wxSCI_JSON_URI 9
#define wxSCI_JSON_COMPACTIRI 10
#define wxSCI_JSON_KEYWORD 11
#define wxSCI_JSON_LDKEYWORD 12
#define wxSCI_JSON_ERROR 13
#define wxSCI_EDI_DEFAULT 0
#define wxSCI_EDI_SEGMENTSTART 1
#define wxSCI_EDI_SEGMENTEND 2
#define wxSCI_EDI_SEP_ELEMENT 3
#define wxSCI_EDI_SEP_COMPOSITE 4
#define wxSCI_EDI_SEP_RELEASE 5
#define wxSCI_EDI_UNA 6
#define wxSCI_EDI_UNH 7
#define wxSCI_EDI_BADSEGMENT 8

//}}}
//----------------------------------------------------------------------


#if defined(__clang__) || wxCHECK_GCC_VERSION(4, 5)
    #define wxSCI_STRINGIFY(X) #X
    #define wxSCI_DEPRECATED_MACRO_VALUE(value,msg) \
        _Pragma(wxSCI_STRINGIFY(GCC warning msg)) value
#else
    #define wxSCI_DEPRECATED_MACRO_VALUE(value,msg) value
#endif

//----------------------------------------------------------------------
// Commands that can be bound to keystrokes section {{{


/// Redoes the next action on the undo history.
#define wxSCI_CMD_REDO 2011

/// Select all the text in the document.
#define wxSCI_CMD_SELECTALL 2013

/// Undo one action in the undo history.
#define wxSCI_CMD_UNDO 2176

/// Cut the selection to the clipboard.
#define wxSCI_CMD_CUT 2177

/// Copy the selection to the clipboard.
#define wxSCI_CMD_COPY 2178

/// Paste the contents of the clipboard into the document replacing the selection.
#define wxSCI_CMD_PASTE 2179

/// Clear the selection.
#define wxSCI_CMD_CLEAR 2180

/// Move caret down one line.
#define wxSCI_CMD_LINEDOWN 2300

/// Move caret down one line extending selection to new caret position.
#define wxSCI_CMD_LINEDOWNEXTEND 2301

/// Move caret up one line.
#define wxSCI_CMD_LINEUP 2302

/// Move caret up one line extending selection to new caret position.
#define wxSCI_CMD_LINEUPEXTEND 2303

/// Move caret left one character.
#define wxSCI_CMD_CHARLEFT 2304

/// Move caret left one character extending selection to new caret position.
#define wxSCI_CMD_CHARLEFTEXTEND 2305

/// Move caret right one character.
#define wxSCI_CMD_CHARRIGHT 2306

/// Move caret right one character extending selection to new caret position.
#define wxSCI_CMD_CHARRIGHTEXTEND 2307

/// Move caret left one word.
#define wxSCI_CMD_WORDLEFT 2308

/// Move caret left one word extending selection to new caret position.
#define wxSCI_CMD_WORDLEFTEXTEND 2309

/// Move caret right one word.
#define wxSCI_CMD_WORDRIGHT 2310

/// Move caret right one word extending selection to new caret position.
#define wxSCI_CMD_WORDRIGHTEXTEND 2311

/// Move caret to first position on line.
#define wxSCI_CMD_HOME 2312

/// Move caret to first position on line extending selection to new caret position.
#define wxSCI_CMD_HOMEEXTEND 2313

/// Move caret to last position on line.
#define wxSCI_CMD_LINEEND 2314

/// Move caret to last position on line extending selection to new caret position.
#define wxSCI_CMD_LINEENDEXTEND 2315

/// Move caret to first position in document.
#define wxSCI_CMD_DOCUMENTSTART 2316

/// Move caret to first position in document extending selection to new caret position.
#define wxSCI_CMD_DOCUMENTSTARTEXTEND 2317

/// Move caret to last position in document.
#define wxSCI_CMD_DOCUMENTEND 2318

/// Move caret to last position in document extending selection to new caret position.
#define wxSCI_CMD_DOCUMENTENDEXTEND 2319

/// Move caret one page up.
#define wxSCI_CMD_PAGEUP 2320

/// Move caret one page up extending selection to new caret position.
#define wxSCI_CMD_PAGEUPEXTEND 2321

/// Move caret one page down.
#define wxSCI_CMD_PAGEDOWN 2322

/// Move caret one page down extending selection to new caret position.
#define wxSCI_CMD_PAGEDOWNEXTEND 2323

/// Switch from insert to overtype mode or the reverse.
#define wxSCI_CMD_EDITTOGGLEOVERTYPE 2324

/// Cancel any modes such as call tip or auto-completion list display.
#define wxSCI_CMD_CANCEL 2325

/// Delete the selection or if no selection, the character before the caret.
#define wxSCI_CMD_DELETEBACK 2326

/// If selection is empty or all on one line replace the selection with a tab character.
/// If more than one line selected, indent the lines.
#define wxSCI_CMD_TAB 2327

/// Dedent the selected lines.
#define wxSCI_CMD_BACKTAB 2328

/// Insert a new line, may use a CRLF, CR or LF depending on EOL mode.
#define wxSCI_CMD_NEWLINE 2329

/// Insert a Form Feed character.
#define wxSCI_CMD_FORMFEED 2330

/// Move caret to before first visible character on line.
/// If already there move to first character on line.
#define wxSCI_CMD_VCHOME 2331

/// Like VCHome but extending selection to new caret position.
#define wxSCI_CMD_VCHOMEEXTEND 2332

/// Magnify the displayed text by increasing the sizes by 1 point.
#define wxSCI_CMD_ZOOMIN 2333

/// Make the displayed text smaller by decreasing the sizes by 1 point.
#define wxSCI_CMD_ZOOMOUT 2334

/// Delete the word to the left of the caret.
#define wxSCI_CMD_DELWORDLEFT 2335

/// Delete the word to the right of the caret.
#define wxSCI_CMD_DELWORDRIGHT 2336

/// Delete the word to the right of the caret, but not the trailing non-word characters.
#define wxSCI_CMD_DELWORDRIGHTEND 2518

/// Cut the line containing the caret.
#define wxSCI_CMD_LINECUT 2337

/// Delete the line containing the caret.
#define wxSCI_CMD_LINEDELETE 2338

/// Switch the current line with the previous.
#define wxSCI_CMD_LINETRANSPOSE 2339

/// Duplicate the current line.
#define wxSCI_CMD_LINEDUPLICATE 2404

/// Transform the selection to lower case.
#define wxSCI_CMD_LOWERCASE 2340

/// Transform the selection to upper case.
#define wxSCI_CMD_UPPERCASE 2341

/// Scroll the document down, keeping the caret visible.
#define wxSCI_CMD_LINESCROLLDOWN 2342

/// Scroll the document up, keeping the caret visible.
#define wxSCI_CMD_LINESCROLLUP 2343

/// Delete the selection or if no selection, the character before the caret.
/// Will not delete the character before at the start of a line.
#define wxSCI_CMD_DELETEBACKNOTLINE 2344

/// Move caret to first position on display line.
#define wxSCI_CMD_HOMEDISPLAY 2345

/// Move caret to first position on display line extending selection to
/// new caret position.
#define wxSCI_CMD_HOMEDISPLAYEXTEND 2346

/// Move caret to last position on display line.
#define wxSCI_CMD_LINEENDDISPLAY 2347

/// Move caret to last position on display line extending selection to new
/// caret position.
#define wxSCI_CMD_LINEENDDISPLAYEXTEND 2348

/// Like Home but when word-wrap is enabled goes first to start of display line
/// HomeDisplay, then to start of document line Home.
#define wxSCI_CMD_HOMEWRAP 2349

/// Like HomeExtend but when word-wrap is enabled extends first to start of display line
/// HomeDisplayExtend, then to start of document line HomeExtend.
#define wxSCI_CMD_HOMEWRAPEXTEND 2450

/// Like LineEnd but when word-wrap is enabled goes first to end of display line
/// LineEndDisplay, then to start of document line LineEnd.
#define wxSCI_CMD_LINEENDWRAP 2451

/// Like LineEndExtend but when word-wrap is enabled extends first to end of display line
/// LineEndDisplayExtend, then to start of document line LineEndExtend.
#define wxSCI_CMD_LINEENDWRAPEXTEND 2452

/// Like VCHome but when word-wrap is enabled goes first to start of display line
/// VCHomeDisplay, then behaves like VCHome.
#define wxSCI_CMD_VCHOMEWRAP 2453

/// Like VCHomeExtend but when word-wrap is enabled extends first to start of display line
/// VCHomeDisplayExtend, then behaves like VCHomeExtend.
#define wxSCI_CMD_VCHOMEWRAPEXTEND 2454

/// Copy the line containing the caret.
#define wxSCI_CMD_LINECOPY 2455

/// Move to the previous change in capitalisation.
#define wxSCI_CMD_WORDPARTLEFT 2390

/// Move to the previous change in capitalisation extending selection
/// to new caret position.
#define wxSCI_CMD_WORDPARTLEFTEXTEND 2391

/// Move to the change next in capitalisation.
#define wxSCI_CMD_WORDPARTRIGHT 2392

/// Move to the next change in capitalisation extending selection
/// to new caret position.
#define wxSCI_CMD_WORDPARTRIGHTEXTEND 2393

/// Delete back from the current position to the start of the line.
#define wxSCI_CMD_DELLINELEFT 2395

/// Delete forwards from the current position to the end of the line.
#define wxSCI_CMD_DELLINERIGHT 2396

/// Move caret down one paragraph (delimited by empty lines).
#define wxSCI_CMD_PARADOWN 2413

/// Extend selection down one paragraph (delimited by empty lines).
#define wxSCI_CMD_PARADOWNEXTEND 2414

/// Move caret up one paragraph (delimited by empty lines).
#define wxSCI_CMD_PARAUP 2415

/// Extend selection up one paragraph (delimited by empty lines).
#define wxSCI_CMD_PARAUPEXTEND 2416

/// Move caret down one line, extending rectangular selection to new caret position.
#define wxSCI_CMD_LINEDOWNRECTEXTEND 2426

/// Move caret up one line, extending rectangular selection to new caret position.
#define wxSCI_CMD_LINEUPRECTEXTEND 2427

/// Move caret left one character, extending rectangular selection to new caret position.
#define wxSCI_CMD_CHARLEFTRECTEXTEND 2428

/// Move caret right one character, extending rectangular selection to new caret position.
#define wxSCI_CMD_CHARRIGHTRECTEXTEND 2429

/// Move caret to first position on line, extending rectangular selection to new caret position.
#define wxSCI_CMD_HOMERECTEXTEND 2430

/// Move caret to before first visible character on line.
/// If already there move to first character on line.
/// In either case, extend rectangular selection to new caret position.
#define wxSCI_CMD_VCHOMERECTEXTEND 2431

/// Move caret to last position on line, extending rectangular selection to new caret position.
#define wxSCI_CMD_LINEENDRECTEXTEND 2432

/// Move caret one page up, extending rectangular selection to new caret position.
#define wxSCI_CMD_PAGEUPRECTEXTEND 2433

/// Move caret one page down, extending rectangular selection to new caret position.
#define wxSCI_CMD_PAGEDOWNRECTEXTEND 2434

/// Move caret to top of page, or one page up if already at top of page.
#define wxSCI_CMD_STUTTEREDPAGEUP 2435

/// Move caret to top of page, or one page up if already at top of page, extending selection to new caret position.
#define wxSCI_CMD_STUTTEREDPAGEUPEXTEND 2436

/// Move caret to bottom of page, or one page down if already at bottom of page.
#define wxSCI_CMD_STUTTEREDPAGEDOWN 2437

/// Move caret to bottom of page, or one page down if already at bottom of page, extending selection to new caret position.
#define wxSCI_CMD_STUTTEREDPAGEDOWNEXTEND 2438

/// Move caret left one word, position cursor at end of word.
#define wxSCI_CMD_WORDLEFTEND 2439

/// Move caret left one word, position cursor at end of word, extending selection to new caret position.
#define wxSCI_CMD_WORDLEFTENDEXTEND 2440

/// Move caret right one word, position cursor at end of word.
#define wxSCI_CMD_WORDRIGHTEND 2441

/// Move caret right one word, position cursor at end of word, extending selection to new caret position.
#define wxSCI_CMD_WORDRIGHTENDEXTEND 2442

/// Centre current line in window.
#define wxSCI_CMD_VERTICALCENTRECARET 2619

/// Move the selected lines up one line, shifting the line above after the selection
#define wxSCI_CMD_MOVESELECTEDLINESUP 2620

/// Move the selected lines down one line, shifting the line below before the selection
#define wxSCI_CMD_MOVESELECTEDLINESDOWN 2621

/// Scroll to start of document.
#define wxSCI_CMD_SCROLLTOSTART 2628

/// Scroll to end of document.
#define wxSCI_CMD_SCROLLTOEND 2629

/// Move caret to before first visible character on display line.
/// If already there move to first character on display line.
#define wxSCI_CMD_VCHOMEDISPLAY 2652

/// Like VCHomeDisplay but extending selection to new caret position.
#define wxSCI_CMD_VCHOMEDISPLAYEXTEND 2653

//}}}
//----------------------------------------------------------------------

#endif // STC_DEFINES_H_INCLUDED
