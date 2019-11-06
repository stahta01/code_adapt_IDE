/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef CLASSBROWSERBUILDERTHREAD_H
#define CLASSBROWSERBUILDERTHREAD_H

#include <wx/thread.h>
#include <wx/treectrl.h>

#include "cctreectrl.h"
#include "nativeparser.h"
#include "parser/token.h"
#include "parser/parser.h"

/** worker thread to build the symbol browser tree controls(both the top tree and the bottom tree)
 *  When the thread is started, it is waiting for the semaphore, and once the GUI post the semaphore
 *  the builder will do the dirty job, once finished, it will wait again.
 */
class ClassBrowserBuilderThread : public wxThread
{
public:
    /** the builder threads' event sent to the GUI(class browser window) */
    enum EThreadEvent
    {
        selectItemRequired,  /// an item is selected
        buildTreeStart,      /// the thread is starting to (re)build the tree
        buildTreeEnd         /// finishing (re)build the tree
    };

    /** constructor
     * @param evtHandler parent window notification events will sent to
     * @param sem a semaphore reference which is used synchronize the GUI and the builder thread
     */
    ClassBrowserBuilderThread(wxEvtHandler* evtHandler, wxSemaphore& sem);

    /** destructor */
    virtual ~ClassBrowserBuilderThread();

    // Called from external:
    void Init(NativeParser* np, CCTreeCtrl* treeTop, CCTreeCtrl* treeBottom,
              const wxString& active_filename, void* user_data/*active project*/,
              const BrowserOptions& bo, TokenTree* tt,
              int idThreadEvent);


    /** construct the children of the tree item
     *  Called from external, BuildTree():
     */
    void ExpandItem(wxTreeItemId item);
#ifndef CC_NO_COLLAPSE_ITEM
    /** remove the children of the tree item
     *  Called from external, BuildTree(), RemoveInvalidNodes():
     */
    void CollapseItem(wxTreeItemId item);
#endif // CC_NO_COLLAPSE_ITEM

    // Called from external and SelectItemRequired():
    void SelectItem(wxTreeItemId item);

    // Called from external:
    void SelectItemRequired();

    /** ask the worker thread to die
     *  Called from external: when the class browser window get destroyed
     */
    void RequestTermination(bool terminate = true) { m_TerminationRequested = terminate; }

protected:
    virtual void* Entry();

    // Called from Entry():
    void BuildTree();

    /** Remove any nodes no longer valid (due to update)
     *
     * Recursively enters all existing nodes and deletes the node if the token it references is invalid
     * @param tree the symbol tree
     * @param parent the node Id
     * Called from BuildTree():
     */
    void RemoveInvalidNodes(CCTreeCtrl* tree, wxTreeItemId parent);

    /** recursively construct the children of node's children, which matches tokenKind
     *  Called from BuildTree():
     *  @param level the recursive level
     */
    void ExpandNamespaces(wxTreeItemId node, TokenKind tokenKind, int level);

    // Called from ExpandItem():
    bool CreateSpecialFolders(CCTreeCtrl* tree, wxTreeItemId parent);

    // Called from CreateSpecialFolders():
    wxTreeItemId AddNodeIfNotThere(CCTreeCtrl* tree, wxTreeItemId parent,
                                   const wxString& name, int imgIndex = -1, CCTreeCtrlData* data = 0);

    /** Add the child nodes of the specified token
     * @param tree the symbol tree control
     * @param parent the specified node
     * @param parentTokenIdx the Token index associated with the node
     * Called from ExpandItem()
     */
    bool AddChildrenOf(CCTreeCtrl* tree, wxTreeItemId parent, int parentTokenIdx,
                       short int tokenKindMask = 0xffff, int tokenScopeMask = 0);
    bool AddAncestorsOf(CCTreeCtrl* tree, wxTreeItemId parent, int tokenIdx);
    bool AddDescendantsOf(CCTreeCtrl* tree, wxTreeItemId parent, int tokenIdx, bool allowInheritance = true);
    // Called from ExpandItem(), SelectItem():
    void AddMembersOf(CCTreeCtrl* tree, wxTreeItemId node);

private:
    // Called from AddChildrenOf(), AddAncestorsOf(), AddDescendantsOf():
    bool AddNodes(CCTreeCtrl* tree, wxTreeItemId parent, const TokenIdxSet* tokens,
                  short int tokenKindMask = 0xffff, int tokenScopeMask = 0, bool allowGlobals = false);

    /** if the token should be shown in the tree, it will return true
     *
     * The view option of the symbol browser determines which tokens should be shown in the tree
     * Called from RemoveInvalidNodes(), AddNodes(), CreateSpecialFolder()
     */
    bool TokenMatchesFilter(const Token* token, bool locked = false);
    // Called from AddNodes():
    bool TokenContainsChildrenOfKind(const Token* token, int kind);

    // Called from BuildTree():
    void SaveExpandedItems(CCTreeCtrl* tree, wxTreeItemId parent, int level);
    void ExpandSavedItems(CCTreeCtrl* tree, wxTreeItemId parent, int level);
    void SaveSelectedItem();
    void SelectSavedItem();

protected:
    wxEvtHandler*    m_Parent;
    wxSemaphore&     m_ClassBrowserSemaphore;

    /** Some member functions of ClassBrowserBuilderThread such as ExpandItem() can either be called
     * from the main GUI thread(in ClassBrowser::OnTreeItemExpanding(wxTreeEvent& event)), or be
     * called in the worker thread(in BuildTree() which is called in ClassBrowserBuilderThread::Entry()),
     * to protect the member variables of the class(especially the wxTreeCtrl, we use the Mutex so
     * that only one thread can access to those member variables.
     */
    wxMutex          m_ClassBrowserBuilderThreadMutex;
    NativeParser*    m_NativeParser;

    /** pointer to the top wxTreeCtrl */
    CCTreeCtrl*      m_CCTreeCtrlTop;
    /** pointer to the bottom wxTreeCtrl */
    CCTreeCtrl*      m_CCTreeCtrlBottom;

    wxString         m_ActiveFilename;
    void*            m_UserData; // active project
    BrowserOptions   m_BrowserOptions;
    TokenTree*       m_TokenTree;

    // pair of current-file-filter
    /** A file set which contains a header file and the associated implementation file
     *
     * If the view option "Current file's symbols" is selected, the symbol tree will show tokens
     * from those files, e.g. if the a.cpp shown in the current active editor, then m_CurrentFileSet
     * maybe contains two files: a.cpp and a.h
     */
    TokenFileSet     m_CurrentFileSet;

    /** Tokens belong to the m_CurrentFileSet file set */
    TokenIdxSet      m_CurrentTokenSet;

    /** Special global scope tokens belong to the m_CurrentFileSet file set  */
    TokenIdxSet      m_CurrentGlobalTokensSet;

private:
    ExpandedItemVect m_ExpandedVect;
    SelectedItemPath m_SelectedPath;
    bool             m_InitDone;

    /** if this variable is true, the Entry() function should return */
    bool             m_TerminationRequested;
    int              m_idThreadEvent;
    wxTreeItemId     m_SelectItemRequired;
};

#endif // CLASSBROWSERBUILDERTHREAD_H
