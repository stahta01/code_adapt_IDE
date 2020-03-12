/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 11847 $
 * $Id: globals.cpp 11847 2019-09-08 22:38:06Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/globals.cpp $
 */

#include "sdk_precomp.h"
#ifndef WX_PRECOMP
    #include <wx/dcmemory.h>            // wxMemoryDC
    #include <wx/choicdlg.h>            // wxSingleChoiceDialog
    #include <wx/textdlg.h>             // wxGetTextFromUserPromptStr
#endif
#ifndef CB_PRECOMP
    #include <wx/file.h>
    #include <wx/filename.h>
    #include <wx/filesys.h>
    #include <wx/image.h>
    #include <wx/imaglist.h>
    #include <wx/listctrl.h>
    #include <wx/menu.h>

    #include "cbexception.h"
    #include "configmanager.h" // ReadBool
    #include "globals.h"
    #include "logmanager.h"
    #include "manager.h"
    #include "projectmanager.h"
#endif

#include <tinyxml.h>

#include <wx/dirdlg.h>
#include <wx/display.h>
#include <wx/filefn.h>
#include <wx/fontmap.h>
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>

#include <algorithm>
#include <string>

#include "wx/wxscintilla.h"
#include "filefilters.h"
#include "tinywxuni.h"
#include "filegroupsandmasks.h"
#include "filemanager.h"

#ifndef __WXMSW__
    #include <unistd.h> // readlink
    #include <sys/stat.h> // lstat
#endif


const wxString DEFAULT_WORKSPACE     = _T("default.workspace");
const wxString DEFAULT_ARRAY_SEP     = _T(";");

#ifndef __WXMAC__
const wxString DEFAULT_CONSOLE_TERM  = _T("xterm -T $TITLE -e");
#else
const wxString DEFAULT_CONSOLE_TERM  = _T("osascript -e 'tell app \"Terminal\"' -e 'activate' -e 'do script quoted form of \"$SCRIPT\"' -e 'end tell'");
#endif
const wxString DEFAULT_CONSOLE_SHELL = _T("/bin/sh -c");

#if defined __WINDOWS__
const wxString cbDEFAULT_OPEN_FOLDER_CMD = _T("explorer.exe /select,");
#elif defined __WXMAC__
const wxString cbDEFAULT_OPEN_FOLDER_CMD = _T("open -R");
#else
const wxString cbDEFAULT_OPEN_FOLDER_CMD = _T("xdg-open");
#endif

void WrapInShExe(wxString& cmd)
{
    wxString command;
    command << wxT("sh.exe -c '");
    // escape any single quoutes
    cmd.Replace("'", "\\'");
    command << cmd << wxT("'");
    cmd = command;
}

bool clIsMSYSEnvironment()
{
// Based on CodeLite clIsMSYSEnvironment function
#ifdef __WINDOWS__
    static bool isMSYS = false;
    static bool firstTime = true;

    if(firstTime) {
        firstTime = false;
        // CL_DEBUG("Testing for MSYS environment...uname -a");
        if ( wxExecute(wxS("where uname"), wxEXEC_SYNC) )
            return false;

        wxArrayString output;
        wxExecute(wxS("uname -a"), output);

        size_t count = output.GetCount();
        for ( size_t n = 0; n < count; n++ )
        {
            output[n].MakeLower();
            if( output[n].Contains("msys") && output[n].Contains("mingw") )
            {
               isMSYS = true;
               break;
            }
        }
    }
    return isMSYS;
#else
    return false;
#endif
}

int GetPlatformsFromString(const wxString& platforms)
{
    bool pW = platforms.Contains(_("Windows"));
    bool pU = platforms.Contains(_("Unix"));
    bool pM = platforms.Contains(_("Mac"));
    bool pA = platforms.Contains(_("All"));

    if (pA || (pW && pU && pM))
        return spAll;

    int     p  = 0;
    if (pW) p |= spWindows;
    if (pU) p |= spUnix;
    if (pM) p |= spMac;
    return p;
}

wxString GetStringFromPlatforms(int platforms, bool forceSeparate)
{
    wxString ret;

    if (!forceSeparate)
    {
        int tmpAll = spWindows | spUnix | spMac;
        if (((platforms & tmpAll) == tmpAll) || ((platforms & spAll) == spAll))
            return _("All");
    }

    if (platforms & spWindows)
        ret << _("Windows;");
    if (platforms & spUnix)
        ret << _("Unix;");
    if (platforms & spMac)
        ret << _("Mac;");
    return ret;
}

/*
    Killerbot : 6 Oktober 2007
    The method has been extended with a bool to specify if the seperator should be appended at the end.
    Ultimate goal : every client gives as a value : false.
    Why : well a seperator should separate, there's nothing to separate at the end (like nothing to separate
    at the beginning, we don't put one there ...), but some client code is having problems when the separator is
    not present at the end. So for compatibility issues we have as default value for the new argument true, so the
    old code has the same behaviour as before [TODO: make those clients no longer dependent on this stupid final separator behaviour]
    New code will specify false as the bool value, so hoping rather soon a search on this method will have all hits showing
    false as the last argument ....
*/

wxString GetStringFromArray(const wxArrayString& array, const wxString& separator, bool SeparatorAtEnd)
{
    wxString out;
    for (unsigned int i = 0; i < array.GetCount(); ++i)
    {
        out << array[i];
        if (i < array.GetCount() - 1 || SeparatorAtEnd)
            out << separator;
    }
    return out;
}

wxArrayString GetArrayFromString(const wxString& text, const wxString& separator, bool trimSpaces)
{
    wxArrayString out;
    wxString search = text;
    int seplen = separator.Length();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.Trim(false);
                search.Trim(true);
            }
            if (!search.IsEmpty())
                out.Add(search);
            break;
        }
        wxString part = search.Left(idx);
        search.Remove(0, idx + seplen);
        if (trimSpaces)
        {
            part.Trim(false);
            part.Trim(true);
        }
        if (!part.IsEmpty())
            out.Add(part);
    }
    return out;
}

wxStringVec GetVectorFromString(const wxString& text, const wxString& separator, bool trimSpaces)
{
    wxStringVec out;
    wxString search = text;
    int seplen = separator.Length();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.Trim(false);
                search.Trim(true);
            }
            if (!search.IsEmpty())
                out.push_back(search);
            break;
        }
        wxString part = search.Left(idx);
        search.Remove(0, idx + seplen);
        if (trimSpaces)
        {
            part.Trim(false);
            part.Trim(true);
        }
        if (!part.IsEmpty())
            out.push_back(part);
    }
    return out;
}

wxArrayString MakeUniqueArray(const wxArrayString& array, bool caseSens)
{
    wxArrayString out;
    for (size_t i = 0; i < array.GetCount(); ++i)
    {
        if (caseSens)
        {
          if (out.Index(array[i]) == wxNOT_FOUND)
              out.Add(array[i]);
        }
        else
        {
          if (out.Index(array[i].Lower()) == wxNOT_FOUND)
              out.Add(array[i].Lower()); // append only lower-case for the moment
        }
    }
    return out;
}

wxString MakeUniqueString(const wxString& text, const wxString& separator, bool caseSens)
{
    return GetStringFromArray( MakeUniqueArray( GetArrayFromString(text, separator), caseSens ), separator, false );
}

void AppendArray(const wxArrayString& from, wxArrayString& to)
{
    for (size_t i = 0; i < from.GetCount(); ++i)
        to.Add(from[i]);
}

wxString UnixFilename(const wxString& filename, wxPathFormat format)
{
    wxString result = filename;

    if (format == wxPATH_NATIVE)
    {
        if (platform::windows)
            format = wxPATH_WIN;
        else
            format = wxPATH_UNIX;
    }

    // Unc-names always override platform specific settings otherwise they become corrupted
    bool unc_name = result.StartsWith(_T("\\\\"));
    if (format == wxPATH_WIN || unc_name) // wxPATH_WIN == wxPATH_DOS == wxPATH_OS2
    {
        result.Replace(wxT("/"), wxT("\\"));
        while (result.Replace(wxT("\\\\"), wxT("\\")))
            ; // loop for recursive removal of duplicate slashes
        if (unc_name)
            result.Prepend(wxT("\\"));
    }
    else
    {
        result.Replace(wxT("\\"), wxT("/"));
        while (result.Replace(wxT("//"), wxT("/")))
            ; // loop for recursive removal of duplicate slashes
    }

    return result;
}

void QuoteStringIfNeeded(wxString& str)
{
    if ( NeedQuotes(str) )
        str = wxString(_T("\"")) + str + _T("\"");
}

bool NeedQuotes(const wxString &str)
{
    bool hasSpace = str.Find(_T(' ')) != -1;
    bool hasParen = !platform::windows && (str.Find(_T('(')) != -1 || str.Find(_T(')')) != -1);
    return !str.IsEmpty() && str.GetChar(0) != _T('"') && (hasSpace || hasParen);
}

wxString EscapeSpaces(const wxString& str)
{
    wxString ret = str;
    if (!ret.IsEmpty() && ret[0] != _T('"') && ret[0] != _T('\''))
    {
        // TODO: make it faster
        ret.Replace(_T(" "), _T("\\ "));
        ret.Replace(_T("\t"), _T("\\\t"));
    }
    return ret;
}

FileType FileTypeOf(const wxString& filename)
{
    wxString ext = filename.AfterLast(_T('.')).Lower();

    if (ext.IsSameAs(FileFilters::ASM_EXT) ||
        ext.IsSameAs(FileFilters::C_EXT) ||
        ext.IsSameAs(FileFilters::CC_EXT) ||
        ext.IsSameAs(FileFilters::CPP_EXT) ||
        ext.IsSameAs(FileFilters::CXX_EXT) ||
        ext.IsSameAs(FileFilters::CPLPL_EXT) ||
        ext.IsSameAs(FileFilters::S_EXT) ||
        ext.IsSameAs(FileFilters::SS_EXT) ||
        ext.IsSameAs(FileFilters::S62_EXT) ||
        ext.IsSameAs(FileFilters::D_EXT) ||
        ext.IsSameAs(FileFilters::F_EXT) ||
        ext.IsSameAs(FileFilters::F77_EXT) ||
        ext.IsSameAs(FileFilters::F90_EXT) ||
        ext.IsSameAs(FileFilters::F95_EXT) ||
        ext.IsSameAs(FileFilters::FOR_EXT) ||
        ext.IsSameAs(FileFilters::FPP_EXT) ||
        ext.IsSameAs(FileFilters::F03_EXT) ||
        ext.IsSameAs(FileFilters::F08_EXT) ||
        ext.IsSameAs(FileFilters::JAVA_EXT)
       )
        return ftSource;

    else if (ext.IsSameAs(FileFilters::TPP_EXT) ||
             ext.IsSameAs(FileFilters::TCC_EXT)
            )
        return ftTemplateSource;

    else if (ext.IsSameAs(FileFilters::H_EXT) ||
             ext.IsSameAs(FileFilters::HH_EXT) ||
             ext.IsSameAs(FileFilters::HPP_EXT) ||
             ext.IsSameAs(FileFilters::HXX_EXT) ||
             ext.IsSameAs(FileFilters::HPLPL_EXT) ||
             ext.IsSameAs(FileFilters::INL_EXT)
            )
        return ftHeader;

    else if (ext.IsSameAs(FileFilters::CODEBLOCKS_EXT))
        return ftCodeBlocksProject;

    else if (ext.IsSameAs(FileFilters::WORKSPACE_EXT))
        return ftCodeBlocksWorkspace;

    else if (ext.IsSameAs(FileFilters::DEVCPP_EXT))
        return ftDevCppProject;

    else if (ext.IsSameAs(FileFilters::MSVC6_EXT))
        return ftMSVC6Project;

    else if (ext.IsSameAs(FileFilters::MSVC7_EXT))
        return ftMSVC7Project;

    else if (ext.IsSameAs(FileFilters::MSVC10_EXT))
        return ftMSVC10Project;

    else if (ext.IsSameAs(FileFilters::MSVC6_WORKSPACE_EXT))
        return ftMSVC6Workspace;

    else if (ext.IsSameAs(FileFilters::MSVC7_WORKSPACE_EXT))
        return ftMSVC7Workspace;

    else if (ext.IsSameAs(FileFilters::XCODE1_EXT))
        return ftXcode1Project; // Xcode 1.0+ (Mac OS X 10.3)

    else if (ext.IsSameAs(FileFilters::XCODE2_EXT))
        return ftXcode2Project; // Xcode 2.1+ (Mac OS X 10.4)

    else if (ext.IsSameAs(FileFilters::OBJECT_EXT))
        return ftObject;

    else if (ext.IsSameAs(FileFilters::XRCRESOURCE_EXT))
        return ftXRCResource;

    else if (ext.IsSameAs(FileFilters::RESOURCE_EXT))
        return ftResource;

    else if (ext.IsSameAs(FileFilters::RESOURCEBIN_EXT))
        return ftResourceBin;

    else if (ext.IsSameAs(FileFilters::STATICLIB_EXT))
        return ftStaticLib;

    else if (ext.IsSameAs(FileFilters::DYNAMICLIB_EXT))
        return ftDynamicLib;

    else if (ext.IsSameAs(FileFilters::NATIVE_EXT))
        return ftNative;

    else if (ext.IsSameAs(FileFilters::EXECUTABLE_EXT))
        return ftExecutable;

    else if (ext.IsSameAs(FileFilters::XML_EXT))
        return ftXMLDocument;

    else if (ext.IsSameAs(FileFilters::SCRIPT_EXT))
        return ftScript;

    // DrewBoo: Before giving up, see if the ProjectManager
    // considers this extension a source or header
    // TODO (Morten#5#): Do what DrewBoo said: Try removing the above code
    // TODO (Morten#3#): This code should actually be a method of filegroups and masks or alike. So we collect all extension specific things in one place. As of now this would break ABI compatibilty with 08.02 so this should happen later.
    else
    {
        // This code breaks ABI compatibility as noted by (Morten#3#) above.
        // Code commented out by (pecan 2018/04/15). See http://forums.codeblocks.org/index.php/topic,22576.0.html
        // The user can perform an equivalent objective by:
        // 1) Fetching FilesGroupsAndMasks and adding the file extention(s) to file masks in the appropriate group.
        // 2) Using the cbEVT_FILE_ADDED event to set the added file(s) properties (eg., compile and link).

        //ProjectManager *prjMgr = Manager::Get()->GetProjectManager();
        //if ( prjMgr )
        //{
        //    const FilesGroupsAndMasks* fgm = prjMgr->GetFilesGroupsAndMasks();
        //    // Since "ext" var has no "." prefixed, but FilesGropupsAndMasks uses
        //    // dot notation(".ext"), prefix a '.' here.
        //    wxString dotExt = _T(".") + ext;
        //   if (fgm)
        //    {
        //       for (unsigned int i = 0; i != fgm->GetGroupsCount(); ++i)
        //       {
        //            if (fgm->GetGroupName(i) == _T("Sources") && fgm->MatchesMask(dotExt, i))
        //                return ftSource;
        //            if (fgm->GetGroupName(i) == _T("Headers") && fgm->MatchesMask(dotExt, i))
        //                return ftHeader;
        //       }
        //    }
        //}
    }

    return ftOther;
}

wxString cbFindFileInPATH(const wxString &filename)
{
    wxString pathValues;
    wxGetEnv(_T("PATH"), &pathValues);
    if (pathValues.empty())
        return wxEmptyString;

    const wxString &sep = platform::windows ? _T(";") : _T(":");
    wxChar pathSep = wxFileName::GetPathSeparator();
    const wxArrayString &pathArray = GetArrayFromString(pathValues, sep);
    for (size_t i = 0; i < pathArray.GetCount(); ++i)
    {
        if (wxFileExists(pathArray[i] + pathSep + filename))
        {
            if (pathArray[i].AfterLast(pathSep).IsSameAs(_T("bin")))
                return pathArray[i];
        }
    }
    return wxEmptyString;
}

void DoRememberSelectedNodes(wxTreeCtrl* tree, wxArrayString& selectedItemPaths)
{
    wxArrayTreeItemIds items;

    if (tree->GetSelections(items) < 1 )
        return;

    for (size_t i=0; i < items.GetCount(); ++i)
    {
        wxString path = wxEmptyString;
        wxTreeItemId item = items[i];
        while(item.IsOk())
        {
            path = _T("/") + tree->GetItemText(item) + path;
            item = tree->GetItemParent(item);
        }
        if (path != wxEmptyString)
            selectedItemPaths.Add(path);
    }
}

void DoSelectRememberedNode(wxTreeCtrl* tree, const wxTreeItemId& parent, wxString& selectedItemPath)
{
    if (tree && !selectedItemPath.IsEmpty())
    {
        wxString tmpPath;
        wxString folder;
        tmpPath = selectedItemPath;
        int pos = tmpPath.Find(_T('/'));
        while (pos == 0)
        {
            tmpPath = tmpPath.Right(tmpPath.Length() - pos - 1);
            pos = tmpPath.Find(_T('/'));
        }

        folder = tmpPath.Left(pos);
        tmpPath = tmpPath.Right(tmpPath.Length() - pos - 1);
        wxTreeItemId item = parent;
        wxTreeItemIdValue cookie = nullptr;

        while (item.IsOk())
        {
            if (tree->GetItemText(item) != folder)
                item = tree->GetNextSibling(item);
            else
            {
                if (pos < 0)
                {
                    tree->SelectItem(item);
                    break;
                }
                else
                {
                    item = tree->GetNextChild(item, cookie);
                    DoSelectRememberedNode(tree, item, tmpPath);
                }
            }
        }

    }
}

bool DoRememberExpandedNodes(wxTreeCtrl* tree, const wxTreeItemId& parent, wxArrayString& nodePaths, wxString& path)
{
    // remember expanded tree nodes of this tree
    if (!tree || !parent.IsOk())
        return false;

    wxString originalPath = path;
    bool found = false;

    wxTreeItemIdValue cookie = nullptr;

    wxTreeItemId child = tree->GetFirstChild(parent, cookie);
    while (child.IsOk())
    {
        if (tree->ItemHasChildren(child) && tree->IsExpanded(child))
        {
            found = true;
            path << _T("/") << tree->GetItemText(child);
            DoRememberExpandedNodes(tree, child, nodePaths, path);
            nodePaths.Add(path);
            path = originalPath;
        }
        child = tree->GetNextChild(parent, cookie);
    }
    return found;
}

void DoExpandRememberedNode(wxTreeCtrl* tree, const wxTreeItemId& parent, const wxString& path)
{
    if (!path.IsEmpty())
    {
        //Manager::Get()->GetLogManager()->Log(mltDevDebug, path);
        wxString tmpPath;
        tmpPath = path;
        wxString folder;
        int pos = tmpPath.Find(_T('/'));
        while (pos == 0)
        {
            tmpPath = tmpPath.Right(tmpPath.Length() - pos - 1);
            pos = tmpPath.Find(_T('/'));
        }

        if (pos < 0) // no '/'
        {
            folder = tmpPath;
            tmpPath.Clear();
        }
        else
        {
            folder = tmpPath.Left(pos);
            tmpPath = tmpPath.Right(tmpPath.Length() - pos - 1);
        }

        //Manager::Get()->GetLogManager()->Log(mltDevDebug, "%s, %s", folder.c_str(), tmpPath.c_str());

        wxTreeItemIdValue cookie = nullptr;

        wxTreeItemId child = tree->GetFirstChild(parent, cookie);
        while (child.IsOk())
        {
            wxString itemText = tree->GetItemText(child);
            if (itemText.Matches(folder))
            {
                tree->Expand(child);
                DoExpandRememberedNode(tree, child, tmpPath);
                break;
            }
            child = tree->GetNextChild(parent, cookie);
        }
    }
}

void SaveTreeState(wxTreeCtrl* tree, const wxTreeItemId& parent, wxArrayString& nodePaths, wxArrayString& selectedItemPaths)
{
    nodePaths.Clear();
    if (!parent.IsOk() || !tree || !tree->ItemHasChildren(parent) || !tree->IsExpanded(parent))
        return;

    wxString tmp;
    if (!DoRememberExpandedNodes(tree, parent, nodePaths, tmp))
        nodePaths.Add(tmp); // just the tree root

    selectedItemPaths.Clear();
    DoRememberSelectedNodes(tree, selectedItemPaths);
}

void RestoreTreeState(wxTreeCtrl* tree, const wxTreeItemId& parent, wxArrayString& nodePaths, wxArrayString& selectedItemPaths)
{
    if (!parent.IsOk() || !tree)
        return;

    if (nodePaths.GetCount() == 0)
    {
        tree->Collapse(parent);
        return;
    }

    for (unsigned int i = 0; i < nodePaths.GetCount(); ++i)
        DoExpandRememberedNode(tree, parent, nodePaths[i]);

    nodePaths.Clear();
    for (unsigned int i = 0; i < selectedItemPaths.GetCount(); ++i)
        DoSelectRememberedNode(tree, tree->GetRootItem(), selectedItemPaths[i]);

    selectedItemPaths.Clear();
}

bool CreateDirRecursively(const wxString& full_path, int perms)
{
    wxFileName tmp(full_path);
    if (wxDirExists(tmp.GetPath())) // early out, even if full_path is a filename, but the path already exists
        return true;

    wxArrayString dirs;
    wxString currdir;
    currdir = tmp.GetVolume() + tmp.GetVolumeSeparator() + wxFILE_SEP_PATH;
    dirs = tmp.GetDirs();

    for (size_t i = 0; i < dirs.GetCount(); ++i)
    {
        currdir << dirs[i];
        if (!wxDirExists(currdir) && !wxMkdir(currdir, perms))
            return false;
        currdir << wxFILE_SEP_PATH;
    }
    return true;
}

bool CreateDir(const wxString& full_path, int perms)
{
    if (!wxDirExists(full_path) && !wxMkdir(full_path, perms))
        return false;

    return true;
}

wxString ChooseDirectory(wxWindow* parent,
                         const wxString& message,
                         const wxString& initialPath,
                         const wxString& basePath,
                         bool askToMakeRelative, // relative to initialPath
                         bool showCreateDirButton) // where supported
{
    wxDirDialog dlg(parent, message, _T(""),
                    (showCreateDirButton ? wxDD_NEW_DIR_BUTTON : 0) | wxRESIZE_BORDER);
    dlg.SetPath(initialPath);
    PlaceWindow(&dlg);
    if (dlg.ShowModal() != wxID_OK)
        return wxEmptyString;

    wxFileName path(dlg.GetPath());
    if (askToMakeRelative && !basePath.IsEmpty())
    {
        // ask the user if he wants it to be kept as relative
        if (cbMessageBox(_("Keep this as a relative path?"),
                         _("Question"),
                         wxICON_QUESTION | wxYES_NO) == wxID_YES)
        {
            path.MakeRelativeTo(basePath);
        }
    }
    return path.GetFullPath();
}

// Reads a wxString from a file. File must be open. File is closed automatically.
bool cbRead(wxFile& file, wxString& st, wxFontEncoding encoding)
{
    st.Empty();
    if (!file.IsOpened())
        return false;

    int len = file.Length();
    if (!len)
    {
        file.Close();
        return true;
    }

    char* buff = new char[len+1];
    if (!buff) // remark by killerbot : this is useless, since when out of mem --> exception (this is not malloc you know)
    {
        file.Close();
        return false;
    }
    file.Read((void*)buff, len);
    file.Close();
    buff[len]='\0';

    DetectEncodingAndConvert(buff, st, encoding);
    delete [] buff;

    return true;
}

wxString cbReadFileContents(wxFile& file, wxFontEncoding encoding)
{
    wxString st;
    cbRead(file, st, encoding);
    return st;
}

// Writes a wxString to a file. File must be open. File is closed automatically.
bool cbWrite(wxFile& file, const wxString& buff, wxFontEncoding encoding)
{
    bool result = false;
    if (file.IsOpened())
    {
        wxCSConv conv(encoding);
        result = file.Write(buff,conv);
        if (result)
            file.Flush();
        file.Close();
    }
    return result;
}

// Writes a wxString to a file. Takes care of unicode and uses a temporary file
// to save first and then it copies it over the original.
bool cbSaveToFile(const wxString& filename, const wxString& contents, wxFontEncoding encoding,
                  bool bom, bool robust)
{
    return Manager::Get()->GetFileManager()->Save(filename, contents, encoding, bom, robust);
}

// Save a TinyXML document correctly, even if the path contains unicode characters.
bool cbSaveTinyXMLDocument(TiXmlDocument* doc, const wxString& filename)
{
    return TinyXML::SaveDocument(filename, doc);
}

// Return @c str as a proper unicode-compatible string
wxString cbC2U(const char* str)
{
#if wxUSE_UNICODE
    return wxString(str, wxConvUTF8);
#else
    return wxString(str);
#endif
}

// Return multibyte (C string) representation of the string
const wxWX2MBbuf cbU2C(const wxString& str)
{
    if (platform::unicode)
        return str.mb_str(wxConvUTF8);
    else
        return str.mb_str();
}

// Try converting a C-string from different encodings until a possible match is found.
// This tries the following encoding converters (in the same order):
// utf8, system, default and iso8859-1 to iso8859-15
wxFontEncoding DetectEncodingAndConvert(const char* strIn, wxString& strOut, wxFontEncoding possibleEncoding)
{
    wxFontEncoding encoding = possibleEncoding;
    strOut.Clear();

    if (platform::unicode)
    {
        if (possibleEncoding != wxFONTENCODING_UTF16 &&
            possibleEncoding != wxFONTENCODING_UTF16LE &&
            possibleEncoding != wxFONTENCODING_UTF16BE &&
            possibleEncoding != wxFONTENCODING_UTF32 &&
            possibleEncoding != wxFONTENCODING_UTF32LE &&
            possibleEncoding != wxFONTENCODING_UTF32BE)
        {
            // crashes deep in the runtime (windows, at least)
            // if one of the above encodings, hence the guard
            wxCSConv conv(possibleEncoding);
            strOut = wxString(strIn, conv);

            if (strOut.Length() == 0)
            {
                // oops! wrong encoding...

                // try utf8 first, if that was not what was asked for
                if (possibleEncoding != wxFONTENCODING_UTF8)
                {
                    encoding = wxFONTENCODING_UTF8;
                    strOut = wxString(strIn, wxConvUTF8);
                }

                // check again: if still not right, try system encoding, default encoding and then iso8859-1 to iso8859-15
                if (strOut.Length() == 0)
                {
                    for (int i = wxFONTENCODING_SYSTEM; i < wxFONTENCODING_ISO8859_MAX; ++i)
                    {
                        encoding = (wxFontEncoding)i;
                        if (encoding == possibleEncoding)
                            continue; // skip if same as what was asked
                        wxCSConv csconv(encoding);
                        strOut = wxString(strIn, csconv);
                        if (strOut.Length() != 0)
                            break; // got it!
                    }
                }
            }
        }
        else
        {
            strOut = (const wxChar*) strIn;
        }
    }
    else
    {
        strOut = (const wxChar*) strIn;
    }
    return encoding;
}

wxString GetEOLStr(int eolMode)
{
    if (eolMode == -1)
    {
        static const int defEOL = platform::windows ? wxSCI_EOL_CRLF : wxSCI_EOL_LF;
        eolMode = Manager::Get()->GetConfigManager(wxT("editor"))->ReadInt(wxT("/eol/eolmode"), defEOL);
        if (eolMode == 3) // auto-detect EOL
            eolMode = defEOL;
    }
    switch (eolMode)
    {
      case wxSCI_EOL_CR:
          return wxT("\r");
      case wxSCI_EOL_LF:
          return wxT("\n");
      default: // wxSCI_EOL_CRLF
          return wxT("\r\n");
    }
}

wxString URLEncode(const wxString &str) // not sure this is 100% standards compliant, but I hope so
{
    wxString ret;
    wxString t;
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        wxChar c = str[i];
        if (  (c >= _T('A') && c <= _T('Z'))
           || (c >= _T('a') && c <= _T('z'))
           || (c >= _T('0') && c <= _T('9'))
           || (c == _T('.'))
           || (c == _T('-'))
           || (c == _T('_')) )

            ret.Append(c);
        else if (c == _T(' '))
            ret.Append(_T('+'));
        else
        {
            t.sprintf(_T("%%%02X"), (unsigned int) c);
            ret.Append(t);
        }
    }
    return ret;
}

/** Adds support for backtick'd expressions under Windows. */
typedef std::map<wxString, wxString> BackticksMap;
BackticksMap m_Backticks; // all calls share the same cache
wxString ExpandBackticks(wxString& str) // backticks are written in-place to str
{
    wxString ret;

    // this function is not windows-only anymore because we parse the backticked command's output
    // for compiler/linker search dirs

    size_t start = str.find(_T('`'));
    if (start == wxString::npos)
        return ret; // no backticks here
    size_t end = str.find(_T('`'), start + 1);
    if (end == wxString::npos)
        return ret; // no ending backtick; error?

    while (start != wxString::npos && end != wxString::npos)
    {
        wxString cmd = str.substr(start + 1, end - start - 1);
        cmd.Trim(true);
        cmd.Trim(false);
        if (cmd.IsEmpty())
            break;

        if(::clIsMSYSEnvironment()) {
            WrapInShExe(cmd);
        }

        wxString bt;
        BackticksMap::iterator it = m_Backticks.find(cmd);
        if (it != m_Backticks.end()) // in the cache :)
            bt = it->second;
        else
        {
            Manager::Get()->GetLogManager()->DebugLog(F(_T("Caching result of `%s`"), cmd.wx_str()));
            wxArrayString output;
            if (platform::WindowsVersion() >= platform::winver_WindowsNT2000)
                wxExecute(_T("cmd /c ") + cmd, output, wxEXEC_NODISABLE);
            else
                wxExecute(cmd,                 output, wxEXEC_NODISABLE);
            bt = GetStringFromArray(output, _T(" "), false);
            // add it in the cache
            m_Backticks[cmd] = bt;
            Manager::Get()->GetLogManager()->DebugLog(_T("Cached"));
        }
        ret << bt << _T(' ');
        str = str.substr(0, start) + bt + str.substr(end + 1, wxString::npos);

        // find next occurrence
        start = str.find(_T('`'));
        end = str.find(_T('`'), start + 1);
    }

    return ret; // return a list of the replaced expressions
}

wxMenu* CopyMenu(wxMenu* mnu, bool with_accelerators)
{
    if (!mnu || mnu->GetMenuItemCount() < 1)
        return nullptr;
    wxMenu* theMenu = new wxMenu();

    for (size_t i = 0; i < mnu->GetMenuItemCount();++i)
    {
        wxMenuItem* tmpItem = mnu->FindItemByPosition(i);
        wxMenuItem* theItem = new wxMenuItem(nullptr,
                                             tmpItem->GetId(),
                                             with_accelerators?tmpItem->GetItemLabel():tmpItem->GetItemLabelText(),
                                             tmpItem->GetHelp(),
                                             tmpItem->GetKind(),
                                             CopyMenu(tmpItem->GetSubMenu()));
        theMenu->Append(theItem);
    }
    return theMenu;
}

bool IsWindowReallyShown(wxWindow* win)
{
    while (win && win->IsShown())
    {
        win = win->GetParent();
        if (!win)
            return true;
    }
    return false;
}

bool NormalizePath(wxFileName& f,const wxString& base)
{
    bool result = true;
//    if (!f.IsAbsolute())
    {
        f.Normalize(wxPATH_NORM_ALL & ~wxPATH_NORM_CASE, base);
        result = f.IsOk();
    }
    return result;
}

// Checks whether 'suffix' could be a suffix of 'path' and therefore represents
// the same path. This is used to check whether a relative path could represent
// the same path as absolute path. For instance, for
// suffix = sdk/globals.cpp
// path = /home/user/codeblocks/trunk/src/sdk/globals.cpp
// it returns true. The function expects that 'path' is normalized and compares
// 'path' with 'suffix' starting from the end of the path. When it reaches .. in
// 'suffix' it gives up (there is no way to check relative filename names
// exactly) and if the path compared so far is identical, it returns true
bool IsSuffixOfPath(wxFileName const & suffix, wxFileName const & path)
{
    if (path.GetFullName() != suffix.GetFullName())
    {
        return false;
    }

    wxArrayString suffixDirArray = suffix.GetDirs();
    wxArrayString pathDirArray = path.GetDirs();

    int j = pathDirArray.GetCount() - 1;
    for (int i = suffixDirArray.GetCount() - 1; i >= 0; i--)
    {
        // skip paths like /./././ and ////
        if (suffixDirArray[i] == _T(".") || suffixDirArray[i] == _T(""))
            continue;

        // suffix has more directories than path - cannot represent the same path
        if (j < 0)
            return false;

        // suffix contains ".." - from now on we cannot precisely determine
        // whether suffix and path match - we assume that they do
        if (suffixDirArray[i] == _T(".."))
            return true;
        // the corresponding directories of the two paths differ
        else if (suffixDirArray[i] != pathDirArray[j])
            return false;

        j--;
    }

    if (suffix.IsAbsolute() && (j >= 0 || suffix.GetVolume() != path.GetVolume()))
        return false;

    // 'suffix' is a suffix of 'path'
    return true;
}

bool cbResolveSymLinkedDirPath(wxString& dirpath)
{
#ifdef _WIN32
    return false;
#else
    if (dirpath.empty())
        return false;
    if (dirpath.Last() == wxFILE_SEP_PATH)
        dirpath.RemoveLast();

    struct stat fileStats;
    if (lstat(dirpath.mb_str(wxConvUTF8), &fileStats) != 0)
        return false;

    // If the path is a symbolic link, then try to resolve it.
    // This is needed to prevent infinite loops, when a folder is pointing to itself or its parent folder.
    if (S_ISLNK(fileStats.st_mode))
    {
        char buffer[4096];
        int result = readlink(dirpath.mb_str(wxConvUTF8), buffer, WXSIZEOF(buffer) - 1);
        if (result != -1)
        {
            buffer[result] = '\0'; // readlink() doesn't NUL-terminate the buffer
            wxString pathStr(buffer, wxConvUTF8);
            wxFileName fileName = wxFileName::DirName(pathStr);

            // If this is a relative symbolic link, we need to make it absolute.
            if (!fileName.IsAbsolute())
            {
                wxFileName dirNamePath;
                if (dirpath.Last() == wxFILE_SEP_PATH)
                    dirNamePath = wxFileName::DirName(dirpath);
                else
                    dirNamePath = wxFileName::DirName(dirpath + wxFILE_SEP_PATH);
                dirNamePath.RemoveLastDir();
                // Make the new filename absolute relative to the parent folder.
                fileName.MakeAbsolute(dirNamePath.GetFullPath());
            }

            wxString fullPath = fileName.GetFullPath();
            if (!fullPath.empty() && fullPath.Last() == wxT('.')) // this case should be handled because of a bug in wxWidgets
                fullPath.RemoveLast();
            if (fullPath.length() > 1 && fullPath.Last() == wxFILE_SEP_PATH)
                fullPath.RemoveLast();
            dirpath = fullPath;
            return true;
        }
    }

    return false;
#endif // _WIN32
}

wxString cbResolveSymLinkedDirPathRecursive(wxString dirpath)
{
    while (cbResolveSymLinkedDirPath(dirpath))
        ;
    return dirpath;
}

// function to check the common controls version
#ifdef __WINDOWS__
#include <windows.h>
#include <shlwapi.h>
bool UsesCommonControls6()
{
    bool result = false;
    HINSTANCE hinstDll;
    hinstDll = LoadLibrary(_T("comctl32.dll"));
    if (hinstDll)
    {
        DLLGETVERSIONPROC pDllGetVersion;
        pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");

        if (pDllGetVersion)
        {
            DLLVERSIONINFO dvi;
            HRESULT hr;

            ZeroMemory(&dvi, sizeof(dvi));
            dvi.cbSize = sizeof(dvi);

            hr = (*pDllGetVersion)(&dvi);

            if (SUCCEEDED(hr))
               result = dvi.dwMajorVersion == 6;
        }

        FreeLibrary(hinstDll);
    }
    return result;
}
#else
bool UsesCommonControls6()
{
    // for non-windows platforms, return true
    // as this is only used for knowing if bitmaps support transparency or not
    return true;
}
#endif

static void cbLoadImageFromFS(wxImage &image, const wxString& filename, wxBitmapType bitmapType,
                              wxFileSystem& fs)
{
    // cache this, can't change while we 're running :)
    static bool oldCommonControls = !UsesCommonControls6();

    wxFSFile* f = fs.OpenFile(filename);
    if (f)
    {
        wxInputStream* is = f->GetStream();
        image.LoadFile(*is, bitmapType);
        delete f;
    }
    if (oldCommonControls && image.HasAlpha())
        image.ConvertAlphaToMask();
}

wxBitmap cbLoadBitmap(const wxString& filename, wxBitmapType bitmapType, wxFileSystem *fs)
{
    wxImage im;
    if (fs)
        cbLoadImageFromFS(im, filename, bitmapType, *fs);
    else
    {
        wxFileSystem defaultFS;
        cbLoadImageFromFS(im, filename, bitmapType, defaultFS);
    }

    if (!im.IsOk())
        return wxNullBitmap;

    return wxBitmap(im);
}

wxBitmap cbLoadBitmapScaled(const wxString& filename, wxBitmapType bitmapType, double scaleFactor,
                            wxFileSystem *fs)
{

    wxImage im;
    if (fs)
        cbLoadImageFromFS(im, filename, bitmapType, *fs);
    else
    {
        wxFileSystem defaultFS;
        cbLoadImageFromFS(im, filename, bitmapType, defaultFS);
    }

    if (!im.IsOk())
        return wxNullBitmap;

#if defined(__WXOSX__) || (defined(__WXGTK3__) && wxCHECK_VERSION(3, 1, 2))
    return wxBitmap(im, -1, scaleFactor);
#else
    (void)scaleFactor;
    return wxBitmap(im);
#endif // defined(__WXOSX__) || (defined(__WXGTK3__) && wxCHECK_VERSION(3, 1, 2))
}

double cbGetContentScaleFactor(const wxWindow &window)
{
#if wxCHECK_VERSION(3, 0, 0)
    return window.GetContentScaleFactor();
#else
    return 1.0;
#endif // wxCHECK_VERSION(3, 0, 0)
}

#ifdef __WXGTK__
// GTK 2 doesn't support scaling.
// GTK 3 supports scaling, but doesn't support fractional values.
// In both cases we need to make up our on scaling value.
// For other platforms the value returned by GetContentScalingFactor seems adequate.
double cbGetActualContentScaleFactor(cb_unused const wxWindow &window)
{
#if wxCHECK_VERSION(3, 0, 0)
    // It is possible to use the window to find a display, but unfortunately this doesn't work well,
    // because we call this function mostly on windows which haven't been shown. This leads to
    // warnings in the log about ClientToScreen failures.
    // If there are problems on multi-monitor setups we should think about some other solution. :(
    const wxSize ppi = wxGetDisplayPPI();
    return ppi.y / 96.0;
#else // wxCHECK_VERSION(3, 0, 0)
    // This code is the simplest version which works in the most common case.
    // If people complain that multi-monitor setups behave strangely, this should be revised with
    // direct calls to GTK/GDK functions.

    // This function might return bad results for multi screen setups.
    const wxSize mm = wxGetDisplaySizeMM();
    if (mm.x == 0 || mm.y == 0)
        return 1.0;
    const wxSize pixels = wxGetDisplaySize();

    const double ppiX = wxRound((pixels.x * inches2mm) / mm.x);
    const double ppiY = wxRound((pixels.y * inches2mm) / mm.y);

    // My guess is that smaller scaling factor would look better. Probably it has effect only in
    // multi monitor setups where there are monitors with different dpi.
    return std::min(ppiX / 96.0, ppiY /96.0);
#endif // wxCHECK_VERSION(3, 0, 0)
}
#else // __WXGTK__
double cbGetActualContentScaleFactor(const wxWindow &window)
{
    return cbGetContentScaleFactor(window);
}
#endif // __WXGTK__

int cbFindMinSize(int targetSize, const int possibleSize[], int numWidths)
{
    int selected = possibleSize[0];
    for (int ii = 0; ii < numWidths; ++ii)
    {
        if (possibleSize[ii] <= targetSize)
            selected = possibleSize[ii];
        else
            break;
    }
    return selected;
}

int cbFindMinSize16to64(int targetSize)
{
    const int sizes[] = { 16, 20, 24, 28, 32, 40, 48, 56, 64 };
    return cbFindMinSize(targetSize, sizes, cbCountOf(sizes));
}

std::unique_ptr<wxImageList> cbMakeScaledImageList(int size, double scaleFactor,
                                                   int &outActualSize)
{
#ifdef __WXMSW__
    outActualSize = size;
#else
    outActualSize = floor(size / scaleFactor);
#endif // __WXMSW__

    return std::unique_ptr<wxImageList>(new wxImageList(outActualSize, outActualSize));
}

bool cbAddBitmapToImageList(wxImageList &list, const wxBitmap &bitmap, int size, int listSize,
                            double scaleFactor)
{
    if (bitmap.IsOk())
    {
        list.Add(bitmap);
        return true;
    }
    else
    {
        wxBitmap missingBitmap;
#if wxCHECK_VERSION(3, 1, 0)
        missingBitmap.CreateScaled(listSize, listSize,  wxBITMAP_SCREEN_DEPTH, scaleFactor);
#else
        (void)scaleFactor;
        missingBitmap.Create(listSize, listSize);
#endif // wxCHECK_VERSION(3, 1, 0)

        {
            // Draw red square image. Do the drawing in a separate scope, because we need to
            // deselect the missing bitmap from the DC before calling the Add method.
            wxMemoryDC dc;
            dc.SelectObject(missingBitmap);
            dc.SetBrush(*wxRED_BRUSH);
            dc.DrawRectangle(0, 0, size, size);
        }

        list.Add(missingBitmap);
        return false;
    }
}

// this doesn't work under wxGTK, and is only needed on wxMSW, we work around it on wxGTK
#ifdef __WXMSW__
void SetSettingsIconsStyle(wxListCtrl* lc, SettingsIconsStyle style)
{
    long flags = lc->GetWindowStyleFlag();
    switch (style)
    {
#if wxCHECK_VERSION(3, 0, 0)
        case sisNoIcons: flags = (flags & ~wxLC_MASK_TYPE) | wxLC_LIST; break;
#else
        case sisNoIcons: flags = (flags & ~wxLC_MASK_TYPE) | wxLC_SMALL_ICON; break;
#endif
        default: flags = (flags & ~wxLC_MASK_TYPE) | wxLC_ICON; break;
    }
    lc->SetWindowStyleFlag(flags);
}
#else
void SetSettingsIconsStyle(cb_unused wxListCtrl* lc, cb_unused SettingsIconsStyle style) {}
#endif

SettingsIconsStyle GetSettingsIconsStyle(cb_unused wxListCtrl* lc)
{
    return GetSettingsIconsStyle();
}

SettingsIconsStyle GetSettingsIconsStyle()
{
    return SettingsIconsStyle(Manager::Get()->GetConfigManager(_T("app"))->ReadInt(_T("/environment/settings_size"), 0));
}

wxRect cbGetMonitorRectForWindow(wxWindow *window)
{
    wxRect monitorRect;
    if (wxDisplay::GetCount() > 0)
    {
        int displayIdx = wxDisplay::GetFromWindow(window);
        if (displayIdx == wxNOT_FOUND)
            displayIdx = 0;
        wxDisplay display(displayIdx);
        monitorRect = display.GetClientArea();
        // This is needed because on Linux the client area returned for the first monitor in a twin
        // monitor setup with nVidia card is spanning the two monitors.
        // The intersection function will return just the client for the specified monitor.
        monitorRect = display.GetGeometry().Intersect(monitorRect);
    }
    else
    {
        int width, height;
        wxDisplaySize(&width, &height);
        monitorRect = wxRect(0, 0, width, height);
    }
    return monitorRect;
}

cbChildWindowPlacement cbGetChildWindowPlacement(ConfigManager &appConfig)
{
    int intChildWindowPlacement = appConfig.ReadInt(wxT("/dialog_placement/child_placement"),
                                                    int(cbChildWindowPlacement::CenterOnParent));
    if (intChildWindowPlacement < 0 || intChildWindowPlacement >= 3)
        intChildWindowPlacement = 0;

    return cbChildWindowPlacement(intChildWindowPlacement);
}

void PlaceWindow(wxTopLevelWindow *w, cbPlaceDialogMode mode, bool enforce)
{
    if (!w)
        cbThrow(_T("Passed NULL pointer to PlaceWindow."));

    int the_mode;

    if (!enforce)
    {
        ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("app"));
        const cbChildWindowPlacement placement =  cbGetChildWindowPlacement(*cfg);
        switch (placement)
        {
            case cbChildWindowPlacement::CenterOnParent:
                w->CenterOnParent();
                return;
            case cbChildWindowPlacement::CenterOnDisplay:
            {
                if (mode == pdlBest)
                    the_mode = cfg->ReadInt(_T("/dialog_placement/dialog_position"), (int) pdlCentre);
                else
                    the_mode = (int) mode;
                break;
            }
            case cbChildWindowPlacement::LeaveToWM:
                return;
        }
    }

    wxWindow* referenceWindow = Manager::Get()->GetAppWindow();
    if (!referenceWindow)    // no application window available, so this is as good as we can get
        referenceWindow = w;

    const wxRect monitorRect = cbGetMonitorRectForWindow(referenceWindow);
    wxRect windowRect = w->GetRect();

    switch(the_mode)
    {
        case pdlCentre:
        {
            windowRect.x = monitorRect.x + (monitorRect.width  - windowRect.width)/2;
            windowRect.y = monitorRect.y  + (monitorRect.height - windowRect.height)/2;
        }
        break;


        case pdlHead:
        {
            windowRect.x = monitorRect.x + (monitorRect.width  - windowRect.width)/2;
            windowRect.y = monitorRect.y  + (monitorRect.height - windowRect.height)/3;
        }
        break;


        case pdlConstrain:
        {
            int x1 = windowRect.x;
            int x2 = windowRect.x + windowRect.width;
            int y1 = windowRect.y;
            int y2 = windowRect.y + windowRect.height;

            if (windowRect.width > monitorRect.width) // cannot place without clipping, so centre it
            {
                x1 = monitorRect.x + (monitorRect.width  - windowRect.width)/2;
                x2 = x1 + windowRect.width;
            }
            else
            {
                x2 = std::min(monitorRect.GetRight(), windowRect.GetRight());
                x1 = std::max(x2 - windowRect.width, monitorRect.x);
                x2 = x1 + windowRect.width;
            }
            if (windowRect.height > monitorRect.height) // cannot place without clipping, so centre it
            {
                y1 = monitorRect.y + (monitorRect.height  - windowRect.height)/2;
                y2 = y1 + windowRect.height;
            }
            else
            {
                y2 = std::min(monitorRect.GetBottom(), windowRect.GetBottom());
                y1 = std::max(y2 - windowRect.height, monitorRect.y);
                y2 = y1 + windowRect.height;
            }
            windowRect = wxRect(x1, y1, x2-x1, y2-y1);
        }
        break;

        case pdlClip:
        {
            int x1 = windowRect.x;
            int x2 = windowRect.x + windowRect.width;
            int y1 = windowRect.y;
            int y2 = windowRect.y + windowRect.height;

            x1 = std::max(x1, monitorRect.x);
            x2 = std::min(x2, monitorRect.GetRight());
            y1 = std::max(y1, monitorRect.y);
            y2 = std::min(y2, monitorRect.GetBottom());

            windowRect = wxRect(x1, y1, x2-x1, y2-y1);
        }
        break;
    }

    w->SetSize(windowRect.x,  windowRect.y, windowRect.width, windowRect.height, wxSIZE_ALLOW_MINUS_ONE);
}

void cbFixWindowSizeAndPlace(wxTopLevelWindow* const w)
{
    if (w == nullptr)
        return;

    const int displayNumber = wxDisplay::GetFromWindow(w); // The display number this window is targeted from the layout file
    if (displayNumber == wxNOT_FOUND)
    {
        // this window is not on a valid display.
        // Place the window to the centre of the current display
        const wxDisplay currentDisplay;

        const int displayHeight = currentDisplay.GetClientArea().GetHeight();
        const int displayWidth  = currentDisplay.GetClientArea().GetWidth();
        const int panelHeight   = w->GetSize().GetHeight();
        const int panelWidth    = w->GetSize().GetWidth();
        if (panelHeight > displayHeight ||
            panelWidth  > displayWidth)
        {
            // If the window is bigger then the current display
            // Rescale the window to 1/3 of the current resolution
            // try to keep the aspect ratio
            const float windowRatio = (float) panelHeight / panelWidth;
            const float scaledWidth = displayWidth / 3.0f;
            float scaledHeight = scaledWidth * windowRatio;
            if (scaledHeight > displayHeight)
            {
                // If the window is still to tall we break the aspect ratio
                scaledHeight = displayHeight / 3.0f;
            }
            w->SetSize(scaledWidth, scaledHeight);
        }
        // Replace it to the centre of the screen...
        Manager::Get()->GetLogManager()->Log(wxString::Format(_("Window \"%s\" was on an invalid display, relocate it to main display"), w->GetTitle().ToUTF8().data()));
        PlaceWindow(w, pdlCentre, true);
    }
}

DirAccessCheck cbDirAccessCheck(const wxString& dir)
{
    wxString actualDir = dir;
    // append ending path separator if needed
    if (actualDir.Last() != _T('/') && actualDir.Last() != _T('\\'))
        actualDir << wxFILE_SEP_PATH;

    if (!wxDirExists(actualDir))
        return dacInvalidDir;

    wxString testFile = wxFileName::CreateTempFileName(actualDir);
    if (!testFile.IsEmpty())
    {
        // ok, write-access confirmed
        // now remove the temporary file and return success
        wxRemoveFile(testFile);
        return dacReadWrite;
    }

    // if we reached here, the directory is not writable
    return dacReadOnly;
}


namespace platform
{
    windows_version_t cb_get_os()
    {
        if (!platform::windows)
        {
            return winver_NotWindows;
        }
        else
        {

            int famWin95 = wxOS_WINDOWS_9X;
            int famWinNT = wxOS_WINDOWS_NT;

            int Major = 0;
            int Minor = 0;
            int family = wxGetOsVersion(&Major, &Minor);

            if (family == famWin95)
                 return winver_Windows9598ME;

            if (family == famWinNT)
            {
                if (Major == 5 && Minor == 0)
                    return winver_WindowsNT2000;

                if (Major == 5 && Minor == 1)
                    return winver_WindowsXP;

                if (Major == 5 && Minor == 2)
                    return winver_WindowsServer2003;

                if (Major == 6 && Minor == 0)
                    return winver_WindowsVista;

                if (Major == 6 && Minor == 1)
                    return winver_Windows7;
            }

            return winver_UnknownWindows;
        }
    }

    windows_version_t WindowsVersion()
    {
        static const windows_version_t theOS = cb_get_os();
        return theOS;
    }
}

// returns the real path of a file by resolving symlinks
// not yet optimal but should do for now
// one thing that's not checked yet are circular symlinks - watch out!
wxString realpath(const wxString& path)
{
#ifdef __WINDOWS__
    // no symlinks support on windows
    return path;
#else
    char buf[2048] = {};
    struct stat buffer;
    std::string ret = (const char*)cbU2C(path);
    size_t lastPos = 0;
    size_t slashPos = ret.find('/', lastPos);
    while (slashPos != std::string::npos)
    {
        if (lstat(ret.substr(0, slashPos).c_str(), &buffer) == 0)
        {
            if (S_ISLNK(buffer.st_mode))
            {
                int s = readlink(ret.substr(0, slashPos).c_str(), buf, sizeof(buf));
                buf[s] = 0;
                if (s > 0 && buf[0] != '/' && buf[0] != '~')
                {
                    // relative
                    ret = ret.substr(0, lastPos) + buf + ret.substr(slashPos, ret.size() - slashPos);
                }
                else
                {
                    // absolute
                    ret = buf + ret.substr(slashPos, ret.size() - slashPos);

                    // start again at the beginning in case the path returned also
                    // has symlinks. For example if using /etc/alternatives this will
                    // be the case
                    s = 0;
                }
                slashPos = s;
            }
        }

        while (ret[++slashPos] == '/')
            ;
        lastPos = slashPos;
        slashPos = ret.find('/', slashPos);
    }
    return cbC2U(ret.c_str());
#endif
}

int cbMessageBox(const wxString& message, const wxString& caption, int style, wxWindow *parent, int x, int y)
{
    if (!parent)
        parent = Manager::Get()->GetAppWindow();

    // Cannot create a wxMessageDialog with a NULL as parent
    if (!parent)
    {
      // wxMessage*Box* returns any of: wxYES, wxNO, wxCANCEL, wxOK.
      int answer = wxMessageBox(message, caption, style, parent, x, y);
      switch (answer)
      {
        // map answer to the one of wxMessage*Dialog* to ensure compatibility
        case (wxOK):
          return wxID_OK;
        case (wxCANCEL):
          return wxID_CANCEL;
        case (wxYES):
          return wxID_YES;
        case (wxNO):
          return wxID_NO;
        default:
          return -1; // NOTE: Cannot happen unless wxWidgets API changes
      }
    }

    wxMessageDialog dlg(parent, message, caption, style, wxPoint(x,y));
    PlaceWindow(&dlg);
    // wxMessage*Dialog* returns any of wxID_OK, wxID_CANCEL, wxID_YES, wxID_NO
    return dlg.ShowModal();
}

DLLIMPORT int cbGetSingleChoiceIndex(const wxString& message, const wxString& caption,
                                     const wxArrayString& choices, wxWindow *parent,
                                     const wxSize &size, int initialSelection)
{
    if (!parent)
        parent = Manager::Get()->GetAppWindow();

    wxSingleChoiceDialog dialog(parent, message, caption, choices);
    dialog.SetSelection(initialSelection);
    dialog.SetSize(size);
    PlaceWindow(&dialog);
    return (dialog.ShowModal() == wxID_OK ? dialog.GetSelection() : -1);
}

DLLIMPORT wxArrayInt cbGetMultiChoiceDialog(const wxString& message, const wxString& caption,
                                     const wxArrayString& choices, wxWindow *parent,
                                     const wxSize& size, const wxArrayInt& initialSelection)
{
    if (!parent)
        parent = Manager::Get()->GetAppWindow();

    wxMultiChoiceDialog dialog(parent, message, caption, choices);
    dialog.SetSelections(initialSelection);
    dialog.SetSize(size);
    PlaceWindow(&dialog);

    if (dialog.ShowModal() == wxID_OK)
        return dialog.GetSelections();
    else
        return wxArrayInt();
}

#if wxCHECK_VERSION(3, 0, 0)
const char* cbGetTextFromUserPromptStr = wxGetTextFromUserPromptStr;
#else
const wxChar* cbGetTextFromUserPromptStr = wxGetTextFromUserPromptStr;
#endif // wxCHECK_VERSION

wxString cbGetTextFromUser(const wxString& message, const wxString& caption, const wxString& defaultValue,
                           wxWindow *parent, wxCoord x, wxCoord y, bool centre)
{
    if (!parent)
        parent = Manager::Get()->GetAppWindow();

    long style = wxTextEntryDialogStyle;
    if (centre)
        style |= wxCENTRE;
    else
        style &= ~wxCENTRE;

    wxTextEntryDialog dialog(parent, message, caption, defaultValue, style, wxPoint(x, y));
    PlaceWindow(&dialog);
    wxString str;
    if (dialog.ShowModal() == wxID_OK)
        str = dialog.GetValue();
    return str;
}


std::unique_ptr<wxImageList> cbProjectTreeImages::MakeImageList(int baseSize, wxWindow &treeParent)
{
    static const wxString imgs[fvsLast] =
    {
        // NOTE: Keep in sync with FileVisualState in globals.h!

        // The following are related to (editable, source-) file states
        _T("file.png"),                  // fvsNormal
        _T("file-missing.png"),          // fvsMissing,
        _T("file-modified.png"),         // fvsModified,
        _T("file-readonly.png"),         // fvsReadOnly,

        // The following are related to version control systems (vc)
        _T("rc-file-added.png"),         // fvsVcAdded,
        _T("rc-file-conflict.png"),      // fvsVcConflict,
        _T("rc-file-missing.png"),       // fvsVcMissing,
        _T("rc-file-modified.png"),      // fvsVcModified,
        _T("rc-file-outofdate.png"),     // fvsVcOutOfDate,
        _T("rc-file-uptodate.png"),      // fvsVcUpToDate,
        _T("rc-file-requireslock.png"),  // fvsVcRequiresLock,
        _T("rc-file-external.png"),      // fvsVcExternal,
        _T("rc-file-gotlock.png"),       // fvsVcGotLock,
        _T("rc-file-lockstolen.png"),    // fvsVcLockStolen,
        _T("rc-file-mismatch.png"),      // fvsVcMismatch,
        _T("rc-file-noncontrolled.png"), // fvsVcNonControlled,

        // The following are related to C::B workspace/project/folder/virtual
        _T("workspace.png"),             // fvsWorkspace,         WorkspaceIconIndex()
        _T("workspace-readonly.png"),    // fvsWorkspaceReadOnly, WorkspaceIconIndex(true)
        _T("project.png"),               // fvsProject,           ProjectIconIndex()
        _T("project-readonly.png"),      // fvsProjectReadOnly,   ProjectIconIndex(true)
        _T("folder_open.png"),           // fvsFolder,            FolderIconIndex()
        _T("vfolder_open.png"),          // fvsVirtualFolder,     VirtualFolderIconIndex()
    };

    const double scaleFactor = cbGetContentScaleFactor(treeParent);
    const int targetHeight = floor(baseSize * cbGetActualContentScaleFactor(treeParent));
    const int size = cbFindMinSize16to64(targetHeight);

    int imageListSize;
    std::unique_ptr<wxImageList> images = cbMakeScaledImageList(size, scaleFactor, imageListSize);

    const wxString prefix = ConfigManager::ReadDataPath()
                          + wxString::Format(_T("/resources.zip#zip:images/tree/%dx%d/"),
                                             size, size);
    wxBitmap bmp;
    for (const wxString &img : imgs)
    {
        bmp = cbLoadBitmapScaled(prefix + img, wxBITMAP_TYPE_PNG, scaleFactor);
        cbAddBitmapToImageList(*images, bmp, size, imageListSize, scaleFactor);
    }
    return images;
}

int cbProjectTreeImages::WorkspaceIconIndex(bool read_only)
{
    if (read_only)
        return (int)fvsWorkspaceReadOnly;

    return (int)fvsWorkspace;
}

int cbProjectTreeImages::ProjectIconIndex(bool read_only)
{
    if (read_only)
        return (int)fvsProjectReadOnly;

    return (int)fvsProject;
}

int cbProjectTreeImages::FolderIconIndex()
{
    return (int)fvsFolder;
}

int cbProjectTreeImages::VirtualFolderIconIndex()
{
    return (int)fvsVirtualFolder;
}
