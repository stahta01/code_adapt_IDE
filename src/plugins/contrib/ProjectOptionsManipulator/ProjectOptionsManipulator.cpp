/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 11839 $
 * $Id: ProjectOptionsManipulator.cpp 11839 2019-09-06 06:55:07Z mortenmacfly $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/plugins/contrib/ProjectOptionsManipulator/ProjectOptionsManipulator.cpp $
 */

#include "ProjectOptionsManipulator.h"

#include <wx/arrstr.h>

#include <cbproject.h>
#include <compiler.h>
#include <compilerfactory.h>
#include <globals.h> // cbMessageBox
#include <manager.h>
#include <projectmanager.h>

#include <vector>

#include "ProjectOptionsManipulatorDlg.h"
#include "ProjectOptionsManipulatorResultDlg.h"

// Register the plugin
namespace
{
  PluginRegistrant<ProjectOptionsManipulator> reg(_T("ProjectOptionsManipulator"));
  long ID_PROJECT_OPTIONS_DLG        = wxNewId();
  long ID_PROJECT_OPTIONS_RESULT_DLG = wxNewId();
};

// Identifiers for settings dialog
BEGIN_EVENT_TABLE(ProjectOptionsManipulator, cbPlugin)
END_EVENT_TABLE()

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

ProjectOptionsManipulator::ProjectOptionsManipulator() :
  m_Dlg(NULL)
{
  //ctor
}// ProjectOptionsManipulator

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

ProjectOptionsManipulator::~ProjectOptionsManipulator()
{
  //dtor
}//~ProjectOptionsManipulator

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::OnAttach()
{
  // do whatever initialization you need for your plugin
  // NOTE: after this function, the inherited member variable
  // m_IsAttached will be TRUE...
  // You should check for it in other functions, because if it
  // is FALSE, it means that the application did *not* "load"
  // (see: does not need) this plugin...

  m_Dlg = new ProjectOptionsManipulatorDlg( Manager::Get()->GetAppWindow(), ID_PROJECT_OPTIONS_DLG );
}// OnAttach

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::OnRelease(bool WXUNUSED(appShutDown))
{
  // do de-initialization for your plugin
  // if appShutDown is false, the plugin is unloaded because Code::Blocks is being shut down,
  // which means you must not use any of the SDK Managers
  // NOTE: after this function, the inherited member variable
  // m_IsAttached will be FALSE...

  if (m_Dlg)
    m_Dlg->Destroy();
}// OnRelease

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

int ProjectOptionsManipulator::Execute()
{
  if ( !IsAttached() || !m_Dlg )
    return -1;

  if ( wxID_OK != m_Dlg->ShowModal() )
    return 0; // Cancelled

  wxArrayString result;
  if      ( m_Dlg->GetScanForWorkspace() )
  {
    if ( !OperateWorkspace(result) )
    {
      cbMessageBox(_("Processing options for workspace failed!"), _("Error"),
                   wxICON_ERROR, Manager::Get()->GetAppWindow());
      return -1;
    }
  }
  else if ( m_Dlg->GetScanForProject()   )
  {
    if ( !OperateProject( m_Dlg->GetProjectIdx(), result ) )
    {
      cbMessageBox(_("Processing options for project failed!"), _("Error"),
                   wxICON_ERROR, Manager::Get()->GetAppWindow());
      return -1;
    }
  }

  if ( result.IsEmpty() )
  {
    cbMessageBox(_("No projects/targets found where chosen options apply."), _("Information"),
                 wxICON_INFORMATION, Manager::Get()->GetAppWindow());
  }
  else
  {
    ProjectOptionsManipulatorResultDlg dlg( Manager::Get()->GetAppWindow(), ID_PROJECT_OPTIONS_RESULT_DLG );
    dlg.ApplyResult(result);
    dlg.ShowModal(); // Don't care about return value

    ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
    if (   (scan_opt != ProjectOptionsManipulatorDlg::eSearch)
        && (scan_opt != ProjectOptionsManipulatorDlg::eSearchNot) )
    {
      if ( wxID_YES == cbMessageBox(_("Do you want to save all (modified) projects now?"),
                                    _("Confirmation"), wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT,
                                      Manager::Get()->GetAppWindow()) )
      {
        if ( !Manager::Get()->GetProjectManager()->SaveAllProjects() )
        {
          cbMessageBox(_("Saving all projects failed!"), _("Error"),
                       wxICON_ERROR, Manager::Get()->GetAppWindow());
        }
      }
    }
  }

  return 0;
}// Execute

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

bool ProjectOptionsManipulator::OperateWorkspace(wxArrayString& result)
{
  ProjectsArray* pa = Manager::Get()->GetProjectManager()->GetProjects();
  bool success = true;
  if (pa)
  {
    for (size_t i=0; i<pa->GetCount(); ++i)
      success &= OperateProject( pa->Item(i), result );
  }

  return success;
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

bool ProjectOptionsManipulator::OperateProject(size_t prj_idx, wxArrayString& result)
{
  ProjectsArray* pa = Manager::Get()->GetProjectManager()->GetProjects();
  bool success = true;
  if (pa)
    success &= OperateProject( pa->Item(prj_idx), result );

  return success;
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

bool ProjectOptionsManipulator::OperateProject(cbProject* prj, wxArrayString& result)
{
  if (!prj) return false;

  const wxString src = m_Dlg->GetSearchFor();
  const wxString dst = m_Dlg->GetReplaceWith();

  size_t manipulations = result.GetCount(); // remember current amount of manipulations

  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  if      (scan_opt == ProjectOptionsManipulatorDlg::eFiles)
    ProcessFiles(prj, result);
  else if (scan_opt == ProjectOptionsManipulatorDlg::eChangeCompiler)
    ProcessChangeCompiler(prj, src, dst, result);
  else
  {
    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eCompiler) )
      ProcessCompilerOptions(prj, src, dst, result);

    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eLinker) )
      ProcessLinkerOptions(prj, src, dst, result);

    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eResCompiler) )
      ProcessResCompilerOptions(prj, src, dst, result);

    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eCompilerPaths) )
      ProcessCompilerPaths(prj, src, dst, result);

    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eLinkerPaths) )
      ProcessLinkerPaths(prj, src, dst, result);

    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eResCompPaths) )
      ProcessResCompPaths(prj, src, dst, result);

    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eLinkerLibs) )
      ProcessLinkerLibs(prj, src, dst, result);

    const wxString val = m_Dlg->GetCustomVarValue();
    if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eCustomVars) )
      ProcessCustomVars(prj, src, val, result);
  }

  if (   (manipulations != result.GetCount()) // if no. of manipulations increased...
      && (scan_opt != ProjectOptionsManipulatorDlg::eSearch)
      && (scan_opt != ProjectOptionsManipulatorDlg::eSearchNot) )
  {                                           // ...and its a modification run ...
    prj->SetModified(true);                   // ...mark the project modified
  }

  return true;
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessFiles(cbProject* prj, wxArrayString& result)
{
  result.Add(wxString::Format(_("Project '%s': Scanning %d files for assigned targets..."),
                              prj->GetTitle().wx_str(), prj->GetFilesCount()));

  // First: scan for file not manipulating the file list
  std::vector<ProjectFile*> files_to_remove;
  for (int idx=0; idx<prj->GetFilesCount(); ++idx)
  {
    ProjectFile* prj_file = prj->GetFile(idx);
    if (prj_file->GetBuildTargets().IsEmpty())
      files_to_remove.push_back(prj_file);
  }

  // Second: manipulate the file list and remove the files not assigned to any target
  for (unsigned int idx=0; idx<files_to_remove.size(); ++idx)
  {
    ProjectFile* prj_file  = files_to_remove.at(idx);
    wxString     file_path = prj_file->file.GetFullPath().wx_str();
    prj->RemoveFile(prj_file); // Don't care about return value
    result.Add(wxString::Format(_("Project '%s': Removed file '%s' not assigned to any target."),
                                prj->GetTitle().wx_str(), file_path.wx_str()));
  }

  result.Add(wxString::Format(_("Project '%s': %d files assigned to targets (%d files removed)."),
                              prj->GetTitle().wx_str(), prj->GetFilesCount(), files_to_remove.size()));
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessChangeCompiler(cbProject* prj, const wxString& src, const wxString& dst, wxArrayString& result)
{
  Compiler* dst_comp = CompilerFactory::GetCompilerByName(dst);
  Compiler* src_comp = nullptr;
  if (nullptr == dst_comp)
  {
    cbMessageBox(_("Invalid destination compiler name!"), _("Error"),
                 wxICON_ERROR, Manager::Get()->GetAppWindow());
    return;
  }

  if (!src.IsEmpty())
  {
    src_comp = CompilerFactory::GetCompilerByName(src);
    if (nullptr == src_comp)
    {
      cbMessageBox(_("Invalid source compiler name!"), _("Error"),
                   wxICON_ERROR, Manager::Get()->GetAppWindow());
      return;
    }
  }

  bool changed = false;

  if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
  {
    if (nullptr != src_comp) // replace only if compiler match
    {
      if ( prj->GetCompilerID().IsSameAs(src_comp->GetID()) )
      {
          prj->SetCompilerID(dst_comp->GetID());
          changed = true;
      }

    }
    else
    {
        prj->SetCompilerID(dst_comp->GetID()); // replace every compiler of this target
        changed = true;
    }

    if(changed)
        result.Add(wxString::Format(_("Project '%s': Changed compiler to '%s'."),
                                        prj->GetTitle().wx_str(), dst_comp->GetName().wx_str()));

  }

  if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
  {
    for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
    {
      ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
      if ( !IsValidTarget(tgt) )
        continue;

      if (nullptr != src_comp) // replace only if compiler match
      {
        if ( tgt->GetCompilerID().IsSameAs(src_comp->GetID()) )
        {
            tgt->SetCompilerID(dst_comp->GetID());
            changed = true;
        }

      }
      else
      {
          tgt->SetCompilerID(dst_comp->GetID()); // replace every compiler of this target
          changed = true;
      }


      if(changed)
        result.Add(wxString::Format(_("Project '%s', target '%s': Changed compiler to '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), dst_comp->GetName().wx_str()));
    }
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessCompilerOptions(cbProject* prj, const wxString& opt, const wxString& opt_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetCompilerOptions(), opt);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains compiler option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain compiler option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetCompilerOptions(), opt);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains compiler option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain compiler option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_opt;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetCompilerOptions(), opt, full_opt) )
        {
          for (size_t fo=0; fo<full_opt.GetCount(); fo++)
          {
            prj->RemoveCompilerOption( full_opt.Item(fo) );
            result.Add(wxString::Format(_("Project '%s': Removed compiler option '%s'."),
                                        prj->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetCompilerOptions(), opt, full_opt) )
          {
            for (size_t fo=0; fo<full_opt.GetCount(); fo++)
            {
              tgt->RemoveCompilerOption(opt);
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed compiler option '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetCompilerOptions(), opt) )
        {
          prj->AddCompilerOption(opt);
          result.Add(wxString::Format(_("Project '%s': Added compiler option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetCompilerOptions(), opt) )
          {
            tgt->AddCompilerOption(opt);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added compiler option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_opt;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetCompilerOptions(), opt, full_opt) )
        {
          for (size_t fo=0; fo<full_opt.GetCount(); fo++)
          {
            prj->ReplaceCompilerOption(full_opt.Item(fo), ManipulateOption(full_opt.Item(fo), opt, opt_new));
            result.Add(wxString::Format(_("Project '%s': Replaced compiler option '%s'."),
                                        prj->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetCompilerOptions(), opt, full_opt) )
          {
            for (size_t fo=0; fo<full_opt.GetCount(); fo++)
            {
              tgt->ReplaceCompilerOption(full_opt.Item(fo), ManipulateOption(full_opt.Item(fo), opt, opt_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced compiler option '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessLinkerOptions(cbProject* prj, const wxString& opt, const wxString& opt_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetLinkerOptions(), opt);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains linker option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain linker option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }

      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetLinkerOptions(), opt);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains linker option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain linker option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_opt;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetLinkerOptions(), opt, full_opt) )
        {
          for (size_t fo=0; fo<full_opt.GetCount(); fo++)
          {
            prj->RemoveLinkerOption(full_opt.Item(fo));
            result.Add(wxString::Format(_("Project '%s': Removed linker option '%s'."),
                                        prj->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetLinkerOptions(), opt, full_opt) )
          {
            for (size_t fo=0; fo<full_opt.GetCount(); fo++)
            {
              tgt->RemoveLinkerOption(full_opt.Item(fo));
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed linker option '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetLinkerOptions(), opt) )
        {
          prj->AddLinkerOption(opt);
          result.Add(wxString::Format(_("Project '%s': Added linker option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetLinkerOptions(), opt) )
          {
            tgt->AddLinkerOption(opt);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added linker option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_opt;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetLinkerOptions(), opt, full_opt) )
        {
          for (size_t fo=0; fo<full_opt.GetCount(); fo++)
          {
            prj->ReplaceLinkerOption(full_opt.Item(fo), ManipulateOption(full_opt.Item(fo), opt, opt_new));
            result.Add(wxString::Format(_("Project '%s': Replaced linker option '%s'."),
                                        prj->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetLinkerOptions(), opt, full_opt) )
          {
            for (size_t fo=0; fo<full_opt.GetCount(); fo++)
            {
              tgt->ReplaceLinkerOption(full_opt.Item(fo), ManipulateOption(full_opt.Item(fo), opt, opt_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced linker option '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessResCompilerOptions(cbProject* prj, const wxString& opt, const wxString& opt_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetResourceCompilerOptions(), opt);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains resource compiler option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain resource compiler option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetResourceCompilerOptions(), opt);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains resource compiler option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain resource compiler option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_opt;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetResourceCompilerOptions(), opt, full_opt) )
        {
          for (size_t fo=0; fo<full_opt.GetCount(); fo++)
          {
            prj->RemoveResourceCompilerOption(full_opt.Item(fo));
            result.Add(wxString::Format(_("Project '%s': Removed resource compiler option '%s'."),
                                        prj->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetResourceCompilerOptions(), opt, full_opt) )
          {
            for (size_t fo=0; fo<full_opt.GetCount(); fo++)
            {
              tgt->RemoveResourceCompilerOption(full_opt.Item(fo));
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed resource compiler option '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetResourceCompilerOptions(), opt) )
        {
          prj->AddResourceCompilerOption(opt);
          result.Add(wxString::Format(_("Project '%s': Added resource compiler option '%s'."),
                                      prj->GetTitle().wx_str(), opt.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetResourceCompilerOptions(), opt) )
          {
            tgt->AddResourceCompilerOption(opt);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added resource compiler option '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), opt.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_opt;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetResourceCompilerOptions(), opt, full_opt) )
        {
          for (size_t fo=0; fo<full_opt.GetCount(); fo++)
          {
            prj->ReplaceResourceCompilerOption(full_opt.Item(fo), ManipulateOption(full_opt.Item(fo), opt, opt_new));
            result.Add(wxString::Format(_("Project '%s': Replaced resource compiler option '%s'."),
                                        prj->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetResourceCompilerOptions(), opt, full_opt) )
          {
            for (size_t fo=0; fo<full_opt.GetCount(); fo++)
            {
              tgt->ReplaceResourceCompilerOption(full_opt.Item(fo), ManipulateOption(full_opt.Item(fo), opt, opt_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced resource compiler option '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_opt.Item(fo).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessCompilerPaths(cbProject* prj, const wxString& path, const wxString& path_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetIncludeDirs(), path);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains compiler path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain compiler path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetIncludeDirs(), path);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains compiler path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain compiler path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_path;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetIncludeDirs(), path, full_path) )
        {
          for (size_t fp=0; fp<full_path.GetCount(); fp++)
          {
            prj->RemoveIncludeDir(full_path.Item(fp));
            result.Add(wxString::Format(_("Project '%s': Removed compiler path '%s'."),
                                        prj->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetIncludeDirs(), path, full_path) )
          {
            for (size_t fp=0; fp<full_path.GetCount(); fp++)
            {
              tgt->RemoveIncludeDir(full_path.Item(fp));
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed compiler path '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetIncludeDirs(), path) )
        {
          prj->AddIncludeDir(path);
          result.Add(wxString::Format(_("Project '%s': Added compiler path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetIncludeDirs(), path) )
          {
            tgt->AddIncludeDir(path);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added compiler path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_path;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetIncludeDirs(), path, full_path) )
        {
          for (size_t fp=0; fp<full_path.GetCount(); fp++)
          {
            prj->ReplaceIncludeDir(full_path.Item(fp), ManipulateOption(full_path.Item(fp), path, path_new));
            result.Add(wxString::Format(_("Project '%s': Replaced compiler path '%s'."),
                                        prj->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetIncludeDirs(), path, full_path) )
          {
            for (size_t fp=0; fp<full_path.GetCount(); fp++)
            {
              tgt->ReplaceIncludeDir(full_path.Item(fp), ManipulateOption(full_path.Item(fp), path, path_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced compiler path '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessLinkerPaths(cbProject* prj, const wxString& path, const wxString& path_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetLibDirs(), path);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains linker path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain linker path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetLibDirs(), path);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains linker path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain linker path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_path;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetLibDirs(), path, full_path) )
        {
          for (size_t fp=0; fp<full_path.GetCount(); fp++)
          {
            prj->RemoveLibDir(full_path.Item(fp));
            result.Add(wxString::Format(_("Project '%s': Removed linker path '%s'."),
                                        prj->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetLibDirs(), path, full_path) )
          {
            for (size_t fp=0; fp<full_path.GetCount(); fp++)
            {
              tgt->RemoveLibDir(full_path.Item(fp));
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed linker path '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetLibDirs(), path) )
        {
          prj->AddLibDir(path);
          result.Add(wxString::Format(_("Project '%s': Added linker path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetLibDirs(), path) )
          {
            tgt->AddLibDir(path);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added linker path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_path;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetLibDirs(), path, full_path) )
        {
          for (size_t fp=0; fp<full_path.GetCount(); fp++)
          {
            prj->ReplaceLibDir(full_path.Item(fp), ManipulateOption(full_path.Item(fp), path, path_new));
            result.Add(wxString::Format(_("Project '%s': Replaced linker path '%s'."),
                                        prj->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetLibDirs(), path, full_path) )
          {
            for (size_t fp=0; fp<full_path.GetCount(); fp++)
            {
              tgt->ReplaceLibDir(full_path.Item(fp), ManipulateOption(full_path.Item(fp), path, path_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced linker path '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessResCompPaths(cbProject* prj, const wxString& path, const wxString& path_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetResourceIncludeDirs(), path);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains resource compiler path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain resource compiler path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetResourceIncludeDirs(), path);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains resource compiler path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain resource compiler path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_path;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetResourceIncludeDirs(), path, full_path) )
        {
          for (size_t fp=0; fp<full_path.GetCount(); fp++)
          {
            prj->RemoveResourceIncludeDir(full_path.Item(fp));
            result.Add(wxString::Format(_("Project '%s': Removed resource compiler path '%s'."),
                                        prj->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetResourceIncludeDirs(), path, full_path) )
          {
            for (size_t fp=0; fp<full_path.GetCount(); fp++)
            {
              tgt->RemoveResourceIncludeDir(full_path.Item(fp));
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed resource compiler path '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetResourceIncludeDirs(), path) )
        {
          prj->AddResourceIncludeDir(path);
          result.Add(wxString::Format(_("Project '%s': Added resource compiler path '%s'."),
                                      prj->GetTitle().wx_str(), path.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetResourceIncludeDirs(), path) )
          {
            tgt->AddResourceIncludeDir(path);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added resource compiler path '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), path.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_path;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetResourceIncludeDirs(), path, full_path) )
        {
          for (size_t fp=0; fp<full_path.GetCount(); fp++)
          {
            prj->ReplaceResourceIncludeDir(full_path.Item(fp), ManipulateOption(full_path.Item(fp), path, path_new));
            result.Add(wxString::Format(_("Project '%s': Replaced resource compiler path '%s'."),
                                        prj->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetResourceIncludeDirs(), path, full_path) )
          {
            for (size_t fp=0; fp<full_path.GetCount(); fp++)
            {
              tgt->ReplaceResourceIncludeDir(full_path.Item(fp), ManipulateOption(full_path.Item(fp), path, path_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced resource compiler path '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_path.Item(fp).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessLinkerLibs(cbProject* prj, const wxString& lib, const wxString& lib_new, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_opt = HasOption(prj->GetLinkLibs(), lib);
        if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Contains linker lib '%s'."),
                                      prj->GetTitle().wx_str(), lib.wx_str()));
        }
        else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not contain linker lib '%s'."),
                                      prj->GetTitle().wx_str(), lib.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_opt = HasOption(tgt->GetLinkLibs(), lib);
          if (has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Contains linker lib '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), lib.wx_str()));
          }
          else if (!has_opt && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not contain linker lib '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), lib.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      wxArrayString full_lib;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetLinkLibs(), lib, full_lib) )
        {
          for (size_t fl=0; fl<full_lib.GetCount(); fl++)
          {
            prj->RemoveLinkLib(full_lib.Item(fl));
            result.Add(wxString::Format(_("Project '%s': Removed linker lib '%s'."),
                                        prj->GetTitle().wx_str(), full_lib.Item(fl).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetLinkLibs(), lib, full_lib) )
          {
            for (size_t fl=0; fl<full_lib.GetCount(); fl++)
            {
              tgt->RemoveLinkLib(full_lib.Item(fl));
              result.Add(wxString::Format(_("Project '%s', target '%s': Removed linker lib '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_lib.Item(fl).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( !HasOption(prj->GetLinkLibs(), lib) )
        {
          prj->AddLinkLib(lib);
          result.Add(wxString::Format(_("Project '%s': Added linker lib '%s'."),
                                      prj->GetTitle().wx_str(), lib.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( !HasOption(tgt->GetLinkLibs(), lib) )
          {
            tgt->AddLinkLib(lib);
            result.Add(wxString::Format(_("Project '%s', target '%s': Added linker lib '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), lib.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      wxArrayString full_lib;
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        if ( HasOption(prj->GetLinkLibs(), lib, full_lib) )
        {
          for (size_t fl=0; fl<full_lib.GetCount(); fl++)
          {
            prj->ReplaceLinkLib(full_lib.Item(fl), ManipulateOption(full_lib.Item(fl), lib, lib_new));
            result.Add(wxString::Format(_("Project '%s': Replaced linker lib '%s'."),
                                        prj->GetTitle().wx_str(), full_lib.Item(fl).wx_str()));
          }
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          if ( HasOption(tgt->GetLinkLibs(), lib, full_lib) )
          {
            for (size_t fl=0; fl<full_lib.GetCount(); fl++)
            {
              tgt->ReplaceLinkLib(full_lib.Item(fl), ManipulateOption(full_lib.Item(fl), lib, lib_new));
              result.Add(wxString::Format(_("Project '%s', target '%s': Replaced linker lib '%s'."),
                                          prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), full_lib.Item(fl).wx_str()));
            }
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

void ProjectOptionsManipulator::ProcessCustomVars(cbProject* prj, const wxString& var, const wxString& value, wxArrayString& result)
{
  ProjectOptionsManipulatorDlg::EProjectScanOption scan_opt = m_Dlg->GetScanOption();
  switch (scan_opt)
  {
    case ProjectOptionsManipulatorDlg::eSearch:
    case ProjectOptionsManipulatorDlg::eSearchNot:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        bool has_var = prj->HasVar(var);
        if (has_var && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
        {
          result.Add(wxString::Format(_("Project '%s': Does not define custom var '%s'."),
                                      prj->GetTitle().wx_str(), var.wx_str()));
        }
        else if (has_var && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
        {
          result.Add(wxString::Format(_("Project '%s': Defines custom var '%s'."),
                                      prj->GetTitle().wx_str(), var.wx_str()));
        }
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          bool has_var = prj->HasVar(var);
          if (has_var && scan_opt==ProjectOptionsManipulatorDlg::eSearchNot)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Does not define custom var '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), var.wx_str()));
          }
          else if (has_var && scan_opt==ProjectOptionsManipulatorDlg::eSearch)
          {
            result.Add(wxString::Format(_("Project '%s', target '%s': Defines custom var '%s'."),
                                        prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), var.wx_str()));
          }
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eRemove:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        prj->UnsetVar(var);
        result.Add(wxString::Format(_("Project '%s': Removed custom var '%s'."),
                                    prj->GetTitle().wx_str(), var.wx_str()));
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          tgt->UnsetVar(var);
          result.Add(wxString::Format(_("Project '%s', target '%s': Removed custom var '%s'."),
                                      prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), var.wx_str()));
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eAdd:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        prj->SetVar(var, value);
        result.Add(wxString::Format(_("Project '%s': Added custom var '%s'."),
                                    prj->GetTitle().wx_str(), var.wx_str()));
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          tgt->SetVar(var, value);
          result.Add(wxString::Format(_("Project '%s', target '%s': Added custom var '%s'."),
                                      prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), var.wx_str()));
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eReplace:
    {
      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eProject) )
      {
        prj->SetVar(var, value, true); // only if exist
        result.Add(wxString::Format(_("Project '%s': Replaced custom var '%s'."),
                                    prj->GetTitle().wx_str(), var.wx_str()));
      }

      if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eTarget) )
      {
        for (int i=0; i<prj->GetBuildTargetsCount(); ++i)
        {
          ProjectBuildTarget* tgt = prj->GetBuildTarget(i);
          if ( !IsValidTarget(tgt) )
            continue;

          tgt->SetVar(var, value, true); // only if exist
          result.Add(wxString::Format(_("Project '%s', target '%s': Replaced custom var '%s'."),
                                      prj->GetTitle().wx_str(), tgt->GetTitle().wx_str(), var.wx_str()));
        }
      }
    }
    break;

    case ProjectOptionsManipulatorDlg::eFiles:          // fall-through
    case ProjectOptionsManipulatorDlg::eChangeCompiler: // fall-through
    default:
    break;
  }
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

bool ProjectOptionsManipulator::HasOption(const wxArrayString& opt_array, const wxString& opt)
{
  wxArrayString dummy;
  return HasOption(opt_array, opt, dummy);
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

bool ProjectOptionsManipulator::HasOption(const wxArrayString& opt_array, const wxString& opt, wxArrayString& full_opt)
{
  bool found_option = false;
  switch ( m_Dlg->GetSearchOption() )
  {
    case (ProjectOptionsManipulatorDlg::eContains):
    {
      for (size_t i=0; i<opt_array.Count(); ++i)
      {
        if ( opt_array.Item(i).Contains(opt) )
        {
          full_opt.Add( opt_array.Item(i) );
          found_option= true;
        }
      }
    }
    break;

    case (ProjectOptionsManipulatorDlg::eEquals): // fall through
    default:
    {
      int idx = opt_array.Index(opt);
      if (idx!=wxNOT_FOUND)
      {
        full_opt.Add( opt_array.Item(idx) );
        found_option = true;
      }
    }
    break;
  }

  return found_option;
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

bool ProjectOptionsManipulator::IsValidTarget(const ProjectBuildTarget* tgt)
{
  if (!tgt)
    return false;

  if (   (m_Dlg->GetTargetTypeOption() == ProjectOptionsManipulatorDlg::eApplication)
      && (tgt->GetTargetType()         != ttConsoleOnly)
      && (tgt->GetTargetType()         != ttExecutable) )
  {
    return false;
  }
  if (   (m_Dlg->GetTargetTypeOption() == ProjectOptionsManipulatorDlg::eStaticLib)
      && (tgt->GetTargetType()         != ttStaticLib) )
  {
    return false;
  }
  if (   (m_Dlg->GetTargetTypeOption() == ProjectOptionsManipulatorDlg::eDynamicLib)
      && (tgt->GetTargetType()         != ttDynamicLib) )
  {
    return false;
  }

  return true;
}

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

wxString ProjectOptionsManipulator::ManipulateOption(wxString opt, const wxString& src, const wxString& dst)
{
  if ( m_Dlg->GetOptionActive(ProjectOptionsManipulatorDlg::eReplacePattern) )
  {
    opt.Replace(src, dst); // Don't care about return value
    return opt;
  }
  return dst;
}
