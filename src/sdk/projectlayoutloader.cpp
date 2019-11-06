/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 10874 $
 * $Id: projectlayoutloader.cpp 10874 2016-07-16 20:00:28Z jenslody $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/projectlayoutloader.cpp $
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include <wx/confbase.h>
    #include <wx/fileconf.h>
    #include <wx/intl.h>
    #include "manager.h"
    #include "configmanager.h"
    #include "projectmanager.h"
    #include "logmanager.h"
    #include "editormanager.h"
    #include "cbeditor.h"
    #include "cbproject.h"
#endif

#include "projectlayoutloader.h"
#include "annoyingdialog.h"
#include <tinyxml.h>
#include "tinywxuni.h"

ProjectLayoutLoader::ProjectLayoutLoader(cbProject* project)
    : m_pProject(project),
    m_TopProjectFile(nullptr)
{
    //ctor
}

ProjectLayoutLoader::~ProjectLayoutLoader()
{
    //dtor
}

// IMPORTANT! We have to be careful of what to unicode and what not to.
// TinyXML must use NON-unicode strings!

bool ProjectLayoutLoader::Open(const wxString& filename)
{
    TiXmlDocument doc;
    if (!TinyXML::LoadDocument(filename, &doc))
        return false;

    ProjectManager* pMan = Manager::Get()->GetProjectManager();
    LogManager* pMsg = Manager::Get()->GetLogManager();
    if (!pMan || !pMsg)
        return false;

    TiXmlElement* root;
    TiXmlElement* elem;
    wxString fname;
    ProjectFile* pf;

    root = doc.FirstChildElement("CodeBlocks_layout_file");
    if (!root)
    {
        // old tag
        root = doc.FirstChildElement("Code::Blocks_layout_file");
        if (!root)
        {
            pMsg->DebugLog(_T("Not a valid Code::Blocks layout file..."));
            return false;
        }
    }

    int major = 0;
    int minor = 0;

    TiXmlElement* version = root->FirstChildElement("FileVersion");
    // don't show messages if we 're running a batch build (i.e. no gui)
    if (!Manager::IsBatchBuild() && version)
    {
        version->QueryIntAttribute("major", &major);
        version->QueryIntAttribute("minor", &minor);

        if (major >= PROJECT_LAYOUT_FILE_VERSION_MAJOR && minor > PROJECT_LAYOUT_FILE_VERSION_MINOR)
        {
            pMsg->DebugLog(F(_T("Project layout file version is > %d.%d. Trying to load..."), PROJECT_LAYOUT_FILE_VERSION_MAJOR, PROJECT_LAYOUT_FILE_VERSION_MINOR));
            AnnoyingDialog dlg(_("Project layout file format is newer/unknown"),
                                F(_("This project layout file was saved with a newer version of Code::Blocks.\n"
                                "Will try to load, but you might see unexpected results.\n"
                                "In this case close the project, delete %s and reopen the project."),filename.wx_str()),
                                wxART_WARNING,
                                AnnoyingDialog::OK);
            dlg.ShowModal();
        }
        else
        {
            // use one message for all changes
            wxString msg;
            wxString warn_msg;

            if (major == 0 && minor == 0)
            {
                msg << _("0.0 (unversioned) to 1.0:\n");
                msg << _("  * save editor-pane layout and order.\n");
                msg << _("\n");
            }

            if (!msg.IsEmpty())
            {
                msg.Prepend(wxString::Format(_("Project layout file format is older (%d.%d) than the current format (%d.%d).\n"
                                                "The file will automatically be upgraded on close.\n"
                                                "But please read the following list of changes, as some of them\n"
                                                "might not automatically convert existing (old) settings.\n"
                                                "If you don't understand what a change means, you probably don't\n"
                                                "use that feature so you don't have to worry about it.\n\n"
                                                "List of changes:\n"),
                                            major,
                                            minor,
                                            PROJECT_LAYOUT_FILE_VERSION_MAJOR,
                                            PROJECT_LAYOUT_FILE_VERSION_MINOR));
                AnnoyingDialog dlg(_("Project layout file format changed"),
                                    msg,
                                    wxART_INFORMATION,
                                    AnnoyingDialog::OK);
                dlg.ShowModal();
            }

            if (!warn_msg.IsEmpty())
            {
                warn_msg.Prepend(_("!!! WARNING !!!\n\n"));
                AnnoyingDialog dlg(_("Project layout file upgrade warning"),
                                    warn_msg,
                                    wxART_WARNING,
                                    AnnoyingDialog::OK);
                dlg.ShowModal();
            }
        }
    }

    elem = root->FirstChildElement("ActiveTarget");
    if (elem)
    {
        if (elem->Attribute("name"))
            m_pProject->SetActiveBuildTarget(cbC2U(elem->Attribute("name")));
    }

    elem = root->FirstChildElement("File");
    if (!elem)
    {
        //pMsg->DebugLog(_T("No 'File' element in file..."));
        return false;
    }

    while (elem)
    {
        //pMsg->DebugLog(elem->Value());
        fname = cbC2U(elem->Attribute("name"));
        if (fname.IsEmpty())
        {
            //pMsg->DebugLog(_T("'File' node exists, but no filename?!?"));
            pf = nullptr;
        }
        else
            pf = m_pProject->GetFileByFilename(fname);

        if (pf)
        {
            pf->editorOpen = false;
            pf->editorSplit = cbEditor::stNoSplit;
            pf->editorSplitActive = 1;
            pf->editorZoom = 0;
            pf->editorPos = 0;
            pf->editorTopLine = 0;
            pf->editorZoom_2 = 0;
            pf->editorPos_2 = 0;
            pf->editorTopLine_2 = 0;
            int getInt = 0; // used to fetch int values

            if (elem->QueryIntAttribute("open", &getInt) == TIXML_SUCCESS)
                pf->editorOpen = getInt != 0;
            if (elem->QueryIntAttribute("top", &getInt) == TIXML_SUCCESS)
            {
                if (getInt)
                    m_TopProjectFile = pf;
            }
            if (elem->QueryIntAttribute("tabpos", &getInt) == TIXML_SUCCESS)
                pf->editorTabPos = getInt;
            if (elem->QueryIntAttribute("split", &getInt) == TIXML_SUCCESS)
                pf->editorSplit = getInt;
            if (elem->QueryIntAttribute("active", &getInt) == TIXML_SUCCESS)
                pf->editorSplitActive = getInt;
            if (elem->QueryIntAttribute("splitpos", &getInt) == TIXML_SUCCESS)
                pf->editorSplitPos = getInt;
            if (elem->QueryIntAttribute("zoom_1", &getInt) == TIXML_SUCCESS)
                pf->editorZoom = getInt;
            if (elem->QueryIntAttribute("zoom_2", &getInt) == TIXML_SUCCESS)
                pf->editorZoom_2 = getInt;

            TiXmlElement* cursor = elem->FirstChildElement("Cursor");
            if (cursor)
            {
                cursor = cursor->FirstChildElement();
                if (cursor)
                {
                    if (cursor->QueryIntAttribute("position", &getInt) == TIXML_SUCCESS)
                        pf->editorPos = getInt;
                    if (cursor->QueryIntAttribute("topLine", &getInt) == TIXML_SUCCESS)
                        pf->editorTopLine = getInt;
                    if (pf->editorSplit != cbEditor::stNoSplit)
                    {
                        cursor = cursor->NextSiblingElement();
                        if (cursor)
                        {
                            if (cursor->QueryIntAttribute("position", &getInt) == TIXML_SUCCESS)
                                pf->editorPos_2 = getInt;
                            if (cursor->QueryIntAttribute("topLine", &getInt) == TIXML_SUCCESS)
                                pf->editorTopLine_2 = getInt;
                        }
                    }
                }
            }

            TiXmlElement* folding = elem->FirstChildElement("Folding");
            if (folding)
            {
                folding = folding->FirstChildElement();
                while (folding)
                {
                    if (folding->QueryIntAttribute("line", &getInt) == TIXML_SUCCESS)
                        pf->editorFoldLinesArray.Add(getInt);

                    folding = folding->NextSiblingElement();
                }
            }
        }
        elem = elem->NextSiblingElement();
    }

    if (   (major >= 1)
        && (Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/environment/enable_editor_layout"), false)) )
    {
        elem = root->FirstChildElement("EditorTabsLayout");
        if (elem)
            m_NotebookLayout = cbC2U(elem->Attribute("layout"));
    }

    return true;
}

bool ProjectLayoutLoader::Save(const wxString& filename)
{
    const char* ROOT_TAG = "CodeBlocks_layout_file";

    TiXmlDocument doc;
    doc.SetCondenseWhiteSpace(false);
    doc.InsertEndChild(TiXmlDeclaration("1.0", "UTF-8", "yes"));
    TiXmlElement* rootnode = static_cast<TiXmlElement*>(doc.InsertEndChild(TiXmlElement(ROOT_TAG)));
    if (!rootnode)
        return false;

    rootnode->InsertEndChild(TiXmlElement("FileVersion"));
    rootnode->FirstChildElement("FileVersion")->SetAttribute("major", PROJECT_LAYOUT_FILE_VERSION_MAJOR);
    rootnode->FirstChildElement("FileVersion")->SetAttribute("minor", PROJECT_LAYOUT_FILE_VERSION_MINOR);

    TiXmlElement* tgtidx = static_cast<TiXmlElement*>(rootnode->InsertEndChild(TiXmlElement("ActiveTarget")));
    tgtidx->SetAttribute("name", cbU2C(m_pProject->GetActiveBuildTarget()));

    ProjectFile* active = nullptr;
    cbEditor* ed = Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor();
    if (ed)
        active = ed->GetProjectFile();

    for (FilesList::iterator it = m_pProject->GetFilesList().begin(); it != m_pProject->GetFilesList().end(); ++it)
    {
        ProjectFile* f = *it;

        if (f->editorOpen || f->editorPos || f->editorPos_2 || f->editorTopLine || f->editorTopLine_2 || f->editorTabPos)
        {
            TiXmlElement* node = static_cast<TiXmlElement*>(rootnode->InsertEndChild(TiXmlElement("File")));
            node->SetAttribute("name", cbU2C(f->relativeFilename));
            node->SetAttribute("open", f->editorOpen);
            node->SetAttribute("top", (f == active));
            node->SetAttribute("tabpos", f->editorTabPos);
            node->SetAttribute("split", f->editorSplit);
            node->SetAttribute("active", f->editorSplitActive);
            node->SetAttribute("splitpos", f->editorSplitPos);
            node->SetAttribute("zoom_1", f->editorZoom);
            node->SetAttribute("zoom_2", f->editorZoom_2);


            TiXmlElement* cursor = static_cast<TiXmlElement*>(node->InsertEndChild(TiXmlElement("Cursor")));
            TiXmlElement* cursor_1 = static_cast<TiXmlElement*>(cursor->InsertEndChild(TiXmlElement("Cursor1")));
            cursor_1->SetAttribute("position", f->editorPos);
            cursor_1->SetAttribute("topLine", f->editorTopLine);

            if(f->editorSplit != cbEditor::stNoSplit)
            {
                TiXmlElement* cursor_2 = static_cast<TiXmlElement*>(cursor->InsertEndChild(TiXmlElement("Cursor2")));
                cursor_2->SetAttribute("position", f->editorPos_2);
                cursor_2->SetAttribute("topLine", f->editorTopLine_2);
            }

            if (f->editorFoldLinesArray.GetCount() > 0)
            {
                TiXmlElement* folding = static_cast<TiXmlElement*>(node->InsertEndChild(TiXmlElement("Folding")));
                for (unsigned int i = 0; i < f->editorFoldLinesArray.GetCount(); i++)
                {
                    TiXmlElement* line = static_cast<TiXmlElement*>(folding->InsertEndChild(TiXmlElement("Collapse")));
                    line->SetAttribute("line", f->editorFoldLinesArray[i]);
                }
            }
        }
    }
    const wxArrayString& en = m_pProject->ExpandedNodes();
    for (unsigned int i = 0; i < en.GetCount(); ++i)
    {
        if (!en[i].IsEmpty())
        {
            TiXmlElement* node = static_cast<TiXmlElement*>(rootnode->InsertEndChild(TiXmlElement("Expand")));
            node->SetAttribute("folder", cbU2C(en[i]));
        }
    }

    if (Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/environment/enable_editor_layout"), false))
    {
        TiXmlElement *el =
            static_cast<TiXmlElement*>(
                rootnode->InsertEndChild( TiXmlElement("EditorTabsLayout") ) );
        el->SetAttribute("layout", cbU2C( Manager::Get()->GetEditorManager()->GetNotebook()->SavePerspective(m_pProject->GetTitle()) ));
    }
    // else ?!

    return cbSaveTinyXMLDocument(&doc, filename);
}
