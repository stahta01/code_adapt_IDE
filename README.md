# WARNING
## CodeAdapt IDE is pre-alpha and I am still force pushing to master branch

# INFO
## CodeAdapt IDE is a manual fork of Code::Blocks IDE to use under MSys2

# Build Directions
### Global Variables
#### CA_RELEASE_TYPE
##### base: -g
#### CA_PCH_TYPE
##### base: -DcaPRECOMP -Winvalid-pch
### Build bootCodeAdapt_wx31-msys2.cbp as normal for an CB Project
### Build all other projects under MSys2 Mingw64 prompt using the above project

# Goals
## Short term goals
### wxWidgets MSys2 package work
#### split wxconfig from wxWidgets package
#### Finish work on wxWidgets3.1 package
### Create CompilerMSYS2 class and xml files [IN-WORK]
### Fix wizards to work with MSys2
#### Console Fixed by CompilerMSYS2 changes [DONE]
#### C::B Plugin [HOLD]
#### FLTK needs to enter C:\msys64\mingw64 as base path
#### GLFW can not find flfw.h; should look for flfw3.h instead
#### GLUT can not find glut32; should look for freeglut instead
#### GTK does NOT use default compiler by default
#### irrlicht can not find irrlicht; should try looking for irrlicht/irrlicht.h
#### ogre can not find files
#### opencv can not find libopencv_core411d.dll.a; should try looking for libopencv_core.dll.a
#### openGL [DONE]
#### Qt5 does NOT list msys2mingw compiler
#### SDL needs to enter C:\msys64\mingw64 as base path
#### SDL2 example code needs changes and must define global var sdl2
#### SFML needs to enter C:\msys64\mingw64 as base path
#### Win32GUI [DONE]
#### wxWidgets needs work fails to locate files
### Fix PCH issues [HOLD]
### Set internal paths [DONE]
#### sdHome home_folder [DONE]
#### sdConfig config_folder GetUserDataFolder() [DONE]
### Add
#### logassert.h defines logAssert [DONE]
#### cbassert.h defines cbAssert and cbAssertNonFatal [DONE]
### Change branding from codeblocks to codeadapt
### Edit
#### include/branding.h [PARTIAL]
#### sdk/cbplugin.cpp
#### sdk/cbproject.cpp
#### sdk/compiler.cpp
#### sdk/configmanager.cpp
#### sdk/editorlexerloader.cpp
#### sdk/filefilters.cpp
#### sdk/macrosmanager.cpp
#### sdk/newfromtemplatedlg.cpp
#### sdk/pluginmanager.cpp
#### sdk/pluginsconfigurationdlg.cpp
#### sdk/projectfile.cpp
#### sdk/projectlayoutloader.cpp
#### sdk/projectloader.cpp
#### sdk/projecttemplateloader.cpp
#### sdk/uservarmanager.cpp
#### sdk/workspaceloader.cpp
#### sdk/resources/projectfile_options.xrc
#### sdk/scripting/bindings/sc_globals.cpp
#### src/resources.rc [PARTIAL]
#### src/app.cpp
#### src/dlgabout.cpp
#### src/main.cpp
#### src/startherepage.cpp
#### src/resources/app_compiler_settings.xrc
#### src/resources/ask_assocs.xrc
#### src/resources/env_settings.xrc
#### src/resources/main_menu.xrc
#### src/resources/manage_assocs.xrc
#### src/resources/new_from_template.xrc
#### src/resources/project_options.xrc
#### src/resources/resources.rc
#### src/resources/start_here/start_here.html
#### src/resources/start_here/title_1312.svg
#### codesnippets/codesnippets.cpp
#### Cscope/CscopeConfigPanel.cpp
#### DoxyBlocks/ConfigPanel.cpp
#### FileManager/FileExplorer.cpp
#### headerfixup/defaults.cpp
#### lib_finder/projectmissinglibs.cpp
#### SpellChecker/DictionariesNeededDialog.cpp
#### ToolsPlus/CmdConfigDialog.cpp
#### wxSmith/wxsresourcetree.cpp
#### wxSmith wxshyperlinkctrl.cpp
#### debuggergdb/debuggergdb.cpp
#### cb_share_config/mainframe.cpp
### Replace wx/wxscintilla.h with cbstyledtextctrl.h or ???
#### plugins/codecompletion/wxsmith/CCTestFrame.wxs
### wxSmith needs to regenerate code after CCTestFrame.wxs is fixed
#### plugins/codecompletion/cctest/cctest_frame.h
### Replace
#### CodeBlocksDDEServer with CodeAdaptDDEServer [DONE]
#### CodeBlocksApp with CodeAdaptApp [DONE]
#### codeblocks.exe with codeadapt.exe [DONE]
#### cbDPI_AWARE_ON with caDPI_AWARE_ON [DONE]
#### CB_PRECOMP with caPRECOMP [PARTIAL]
#### CB_RELEASE_TYPE with CA_RELEASE_TYPE [DONE]
#### CB_PCH_TYPE with CA_PCH_TYPE [DONE]
#### "cbDEBUG" with "caDEBUG" [DONE]
#### "cbAssert" with "caAssert" [DONE]
#### "cbAssertNonFatal" with "caAssertNonFatal" [DONE]
#### "cbThrow" with "caThrow" [DONE]
#### "cbException" with "caException" [DONE]
#### ../../../include with $(#CA.include) [HOLD]
#### ../../../include/scripting with $(#CA.include)/scripting [HOLD]
#### ../../../include/tinyxml with $(#CA.include)/tinyxml [HOLD]
#### ../../../sdk/wxscintilla with $(#CA)/sdk/wxscintilla [HOLD]
#### ../../../src with $(#CA)/src [HOLD]
#### www.codeblocks.org with ??? [HOLD]
#### wiki.codeblocks.org with ??? [HOLD]
### Move headers from "include" to "include/ca"
#### assert.h (formerly cbassert.h) [DONE]
#### logassert.h [DONE]
#### exception.h (formerly cbexception.h) [DONE]

## Mid term goals
### Change SpellCheck to use MSys hunspell
### Change cpb2make to use MSys tinyxml or tinyxml2 [HOLD]
### Replace wxMSW with wxGTK/Win [IN-WORK]
#### Changed from GTK/GDK version 2 to version 3 to fix crashing [DONE]
### Replace wxScintilla_cb with wxStyledTextCtrl/wxSTC [IN-WORK] [CRASHES]
#### Need to fork wxWidgets wxStyledTextCtrl/wxSTC [DONE]

## Long term goals
### Git Add or Rename
#### Rename folder "compilergcc" to "compiler"
#### Rename folder "debuggergdb" to "debugger"
#### Rename folder "src/src" to "src/core_app"
### Remove features
#### auto adding pch header path
### Compare using wxSmith, wxFormBuilder, wxCrafter, or wxglade
#### By rewriting ToolsPlus
### Remove or replace
#### wxSmith
#### CodeCompletion
#### squirrel scripting
### Add features
#### manual file dependency inside project
#### assembly code support
### Extend features
#### custom makefile support
