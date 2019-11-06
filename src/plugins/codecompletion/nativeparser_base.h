/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef NATIVEPARSERBASE_H
#define NATIVEPARSERBASE_H

#if wxCHECK_VERSION(3, 0, 0)
#include <wx/wxcrt.h> // wxIsalnum
#endif
#include <wx/string.h>

#include <map>
#include <queue>

#include "parser/token.h"
#include "parser/tokentree.h"

/** debug only variable, used to print the AI match related log message */
extern bool s_DebugSmartSense;

class NativeParserBase
{
public:
    /** divide a statement to several pieces(parser component), each component has a type member */
    enum ParserTokenType
    {
        pttUndefined = 0,
        pttSearchText,
        pttClass,
        pttNamespace,
        pttFunction
    };

    /** the delimiter separating two Parser Component, See ParserComponent struct for more details */
    enum OperatorType
    {
        otOperatorUndefined = 0,
        otOperatorSquare,
        otOperatorParentheses,
        otOperatorPointer,
        otOperatorStar
    };

    /** @brief a long statement can be divided to a ParserComponent chain.
     *
     * e.g. for a statement like below:
     * @code
     * Ogre::Root::getSingleton().|
     * @endcode
     *
     *  a chains of four ParserComponents will be generated and list below:
     * @code
     *  Ogre             [pttNamespace]
     *  Root             [pttClass]
     *  getSingleton     [pttFunction]
     *  (empty space)    [pttSearchText]
     * @endcode
     *
     * a ParserComponent is mainly an identifier, which we use this identifier name to query on the
     * Symbol tree, and try to get the matched symbols.
     * For this example, we first try to search the Symbol tree by the keyword "Ogre", this will
     * match a symbol which has type "Namespace".
     * The next step, we search the "Root" under the previous returned Symbols.
     * In some special cases, such as "array[7]->b", we gives such result
     * @code
     *  array            [pttNamespace] (variable name?)
     *  []               [pttFunction, which is operator[]]
     *  b                [pttSearchText]
     * @endcode
     */
    struct ParserComponent
    {
        wxString        component;          /// name
        ParserTokenType tokenType;          /// type
        OperatorType    tokenOperatorType;  /// operator type

        ParserComponent() { Clear(); }
        void Clear()
        {
            component         = wxEmptyString;
            tokenType         = pttUndefined;
            tokenOperatorType = otOperatorUndefined;
        }
    };

    /** Constructor */
    NativeParserBase();

    /** Destructor */
    virtual ~NativeParserBase();

protected:

    /** Init cc search member variables */
    void Reset();

    /**@brief Artificial Intelligence Matching
    *
    * All functions that call this recursive function, should already entered a critical section or
    * a mutex to protect the TokenTree.
    *
    * match (consume) the ParserComponent queue from left to right,
    * the output result becomes the search scope of the next match.
    * finally, give the results which match the last ParserComponent.
    * @param components input ParserComponent queue
    * @param parentTokenIdx, initial search scope of the left most component, this is the direct
    * parent of the current statement(expression)
    * @param fullMatch the result should be a full text match or prefix match
    * @return matching token number, it is the size of result
    */
    size_t FindAIMatches(TokenTree*                  tree,
                         std::queue<ParserComponent> components,
                         TokenIdxSet&                result,
                         int                         parentTokenIdx = -1,
                         bool                        isPrefix = false,
                         bool                        caseSensitive = false,
                         bool                        use_inheritance = true,
                         short int                   kindMask = 0xFFFF,
                         TokenIdxSet*                search_scope = 0);

    /** if the expression return the container tokens, which are the
     * parent of the expression.
     * @param[in] procResult input function index collection
     * @param[out] scopeResult filtered output function index collection
     * For example, if we have such code
     * @code
     * class A
     * {
     *      void f()
     *      {
     *         statement|<-----CC here
     *      };
     * }
     * @endcode
     * We try to locate the Tokens their scopes "Cover" the "statement"
     */
    void FindCurrentFunctionScope(TokenTree*         tree,
                                  const TokenIdxSet& procResult,
                                  TokenIdxSet&       scopeResult);

    /** remove all the container tokens in the token index set.
     * @param searchScope The Tokens we need to remove from the tree
     */
    void CleanupSearchScope(TokenTree*  tree,
                            TokenIdxSet* searchScope);

    /** Returns the start and end of the call-tip highlight region.
     * For a function prototype "void MyNamespace::SomeClass::func(int a, float b)"
     * if we have a function call statement "obj->f(x,y)", when we hover on the "y", we should
     * high light the "float b" in the calltip
     * @param[in] calltip is the calltip string
     * @param[out] start the start index of the high light string
     * @param[out] end the end index of the high light string
     * @param[in] typedCommas e.g. "func(x, y)", in this case, we say we have typed one comma before
     * the hovered "y", so we know we need to high light the second parameter, which is "float b"
     */
    void GetCallTipHighlight(const wxString& calltip,
                             int*            start,
                             int*            end,
                             int             typedCommas);

    /** Finds the position of the opening parenthesis marking the beginning of the params.
     * See GetCallTipHighlight() for more details
     */
    int FindFunctionOpenParenthesis(const wxString& calltip);

    /** helper function to split the statement
     *
     * @param line a statement string
     * @param[out] tokenType the returned type of the string
     * @param[out] tokenOperatorType if it is a function call token, specify which type of function call
     * It contains a string on the following form:
     * @code
     *     char* mychar = SomeNamespace::m_SomeVar.SomeMeth
     *                                                     ^----start from here
     * @endcode
     * Usually, the caret is located at the end of the line.
     *
     * first we locate the first non-space char starting from the *end*:
     * @code
     *     char* mychar = SomeNamespace::m_SomeVar.SomeMeth
     *                    ^----stop here
     * @endcode
     * then we remove everything before it, so we get "SomeNamespace::m_SomeVar.SomeMeth"
     *
     * Now we cut the first component "SomeNamespace" and return it.
     * The statement line becomes:
     * @code
     * m_SomeVar.SomeMeth
     * @endcode
     * so that if we call this function again with the (modified) line,
     * we'll return "m_SomeVar" and modify line (again) to become:
     * @code
     *     SomeMeth
     * @endcode
     * and so on and so forth until we return an empty string...
     * NOTE: if we find () args or [] arrays in our way, we skip them (done in GetNextCCToken)...
     * todo: it looks like [] is not skipped, because we have to handle the operator[]
     * also, if we see a aaa(), we always think it is a function call
     */
    wxString GetCCToken(wxString&        line,
                        ParserTokenType& tokenType,
                        OperatorType&    tokenOperatorType);

    /** helper function to split the statement
     *  @code
     *   "    SomeNameSpace::SomeClass.SomeMethod|"
     *        ^  should stop here  <------------ ^ start from here, go backward(right to left)
     *   "    f(SomeNameSpace::SomeClass.SomeMethod|"
     *          ^ should stop here
     *  @endcode
     *  so, brace level should be considered
     */
    unsigned int FindCCTokenStart(const wxString& line);

    /** helper function to read the next CCToken, begin from the startAt, this point to a non-space
     * character, and fetch the beginning identifier
     * @param startAt this will be updated to the char after the identifier
     * @param tokenOperatorType the type of the operator
     * E.g.
     * @code
     *            SomeMethod()->
     *            ^begin
     * @endcode
     * the returned wxString is "SomeMethod", the tokenOperatorType is pointer member access
     */
    wxString GetNextCCToken(const wxString& line,
                            unsigned int&   startAt,
                            OperatorType&   tokenOperatorType);

    /** Remove the last function's children, when doing codecompletion in a function body, the
     *  function body up to the caret position was parsed, and the local variables defined in
     *  the function were recorded as the function's children.
     *  Note that these tokens are marked as temporary tokens, so if the edit caret moves to another
     *  function body, these temporary tokens should be removed.
     */
    void RemoveLastFunctionChildren(TokenTree* tree, int& lastFuncTokenIdx);

    /** @brief break a statement to several ParserComponents, and store them in a queue.
     * @param actual a statement string to be divided.
     * @param components output variable containing the queue.
     * @return number of ParserComponent
     */
    size_t BreakUpComponents(const wxString&              actual,
                             std::queue<ParserComponent>& components);

    /** A statement(expression) is expressed by a ParserComponent queue
     *  We do a match from the left of the queue one by one.
     *
     *
     * Here is a simple description about the algorithm, suppose we have such code snippet
     * @code
     * namespace AAA
     * {
     *     class BBB
     *     {
     *     public:
     *         int m_aaa;
     *     }
     *     class CCC
     *     {
     *     public:
     *         BBB fun();
     *     }
     * }
     * AAA::CCC obj;
     * obj.fun().|-----we want to get code suggestion list here
     * @endcode
     * We first split the statement "obj.fun()." into 3 components:
     * component name
     * @code
     * 1, obj
     * 2, fun
     * 3, empty
     * @endcode
     * We do three loops here, each loop, we consume one component. Also each loop's result will
     * serve as the next loop's search scope.
     *
     * Loop 1
     * We first search the tree by the text "obj", we find a matched variable token, which has the
     * type string "AAA::CCC", then the text "AAA::CCC" is resolved to a class kind token "class CCC"
     * Loop 2
     * We search the tree by the text "fun". Here the search scope should be "CCC", it's the result
     * from the previous loop, so we find that there is a function kind token under "class CCC",
     * which is "function fun()" token. Then we need to see the return type of the fun() token,
     * which is the name "BBB". Then we do another text search for "BBB" in the tree, and find a
     * class kind token "class BBB"
     * Loop 3
     * Since the last search text is empty, we just return all the children of the "class BBB" token,
     * so finally, we give the child variable kind token "m_aaa", then the code suggestion should
     * prompt the string "m_aaa"
     *
     * @param tree the token tree pointer
     * @param components expression structure expressed in std::queue<ParserComponent>
     * @param searchScope search scope defined by TokenIdxSet
     * @param[out] the final result token index
     * @param caseSense case sensitive match
     * @param isPrefix match type( full match or prefix match)
     * @return result tokens count
     */
    size_t ResolveExpression(TokenTree*                  tree,
                             std::queue<ParserComponent> components,
                             const TokenIdxSet&          searchScope,
                             TokenIdxSet&                result,
                             bool                        caseSense = true,
                             bool                        isPrefix = false);

    /** used to solve the overloaded operator functions return type
     * @param tokenOperatorType overloaded operator type, could be [], (), ->
     * @param tokens input tokens set
     * @param tree Token tree pointer
     * @param searchScope search scope
     * @param result output result
     */
    void ResolveOperator(TokenTree*          tree,
                         const OperatorType& tokenOperatorType,
                         const TokenIdxSet&  tokens,
                         const TokenIdxSet&  searchScope,
                         TokenIdxSet&        result);

    /** Get the Type information of the searchText string
     * @param searchText input search text
     * @param searchScope search scope defined in TokenIdxSet format
     * @param result result token specify the Type of searchText
     */
    size_t ResolveActualType(TokenTree*         tree,
                             wxString           searchText,
                             const TokenIdxSet& searchScope,
                             TokenIdxSet&       result);

    /** resolve template map [formal parameter] to [actual parameter]
     * @param searchStr input Search String
     * @param actualtypeScope Token type(actual parameter)
     * @param initialScope search scope
     */
    void ResolveTemplateMap(TokenTree*         tree,
                            const wxString&    searchStr,
                            const TokenIdxSet& actualTypeScope,
                            TokenIdxSet&       initialScope);

    /** add template parameter, get the actual parameter from the formal parameter list
     * @param id template token id
     * @param actualTypeScope search scope
     * @param initialScope resolved result
     * @param tree Token tree pointer.
     */
    void AddTemplateAlias(TokenTree*         tree,
                          const int&         id,
                          const TokenIdxSet& actualTypeScope,
                          TokenIdxSet&       initialScope);

    /** Generate the matching results under the Parent Token index set
     *
     * All functions that call this recursive function, should already entered a critical section.
     *
     * @param tree TokenTree pointer
     * @param target Scope (defined in TokenIdxSet)
     * @param result result token index set
     * @param isPrefix whether a full match is used or only do a prefix match
     * @param kindMask define the result tokens filter, such as only class type is OK
     * @return result token set number
     */
    size_t GenerateResultSet(TokenTree*      tree,
                             const wxString& target,
                             int             parentIdx,
                             TokenIdxSet&    result,
                             bool            caseSens = true,
                             bool            isPrefix = false,
                             short int       kindMask = 0xFFFF);

    /** This function is just like the one above, especially that it use a single parent Token id,
     *  not the parent id set in previous one.
     *
     * All functions that call this recursive function, should already entered a critical section.
     *
     */
    size_t GenerateResultSet(TokenTree*         tree,
                             const wxString&    target,
                             const TokenIdxSet& ptrParentID,
                             TokenIdxSet&       result,
                             bool               caseSens = true,
                             bool               isPrefix = false,
                             short int          kindMask = 0xFFFF);

    /** Test if token with this id is allocator class.
     *
     * All functions that call this function, should already entered a critical section.
     *
     * @param tree TokenTree pointer
     * @param id token idx
     */
    bool IsAllocator(TokenTree*   tree,
                     const int&     id);

    /** Test if token with this id depends on allocator class.
     * Currently, this function only identifies STL containers dependent on allocator.
     *
     * All functions that call this recursive function, should already entered a critical section.
     *
     * @param tree TokenTree pointer
     * @param id token idx
     */
    bool DependsOnAllocator(TokenTree*    tree,
                            const int&    id);

    /** Collect search scopes, add the searchScopes's parent scope
     * @param searchScope input search scope
     * @param actualTypeScope returned search scope
     * @param tree TokenTree pointer
     */
    void CollectSearchScopes(const TokenIdxSet& searchScope,
                             TokenIdxSet&       actualTypeScope,
                             TokenTree*         tree);

    /** used to get the correct token index in current line, e.g.
     * @code
     * class A
     * {
     *    void test()
     *    {               // start of the function body
     *       |
     *    };              // end of the function body
     * };
     * @endcode
     * @param tokens all current file's function and class, which cover the current line
     * @param curLine the line of the current caret position
     * @param file editor file name
     */
    int GetTokenFromCurrentLine(TokenTree*         tree,
                                const TokenIdxSet& tokens,
                                size_t             curLine,
                                const wxString&    file);

    /** call tips are tips when you are entering some functions, such as you have a class definition
     * @code
     *  class A {
     *  public:
     *      void A() {};
     *      void test() { };
     *  };
     *  when you are entering some text like
     *  A(|    or  objA.test(|
     * @endcode
     * then there will be a tip window show the function prototype of the function
     *
     */
    void ComputeCallTip(TokenTree*         tree,
                        const TokenIdxSet& tokens,
                        wxArrayString&     items);

    /** For ComputeCallTip()
     * No critical section needed in this recursive function!
     * All functions that call this recursive function, should already entered a critical section. */
    bool PrettyPrintToken(TokenTree*   tree,
                          const Token* token,
                          wxString&    result,
                          bool         isRoot = true);

    // convenient static funcs for fast access and improved readability

    // count commas in lineText (nesting parentheses)
    static int CountCommas(const wxString& lineText, int start)
    {
        int commas = 0;
        int nest = 0;
        while (true)
        {
            wxChar c = lineText.GetChar(start++);
            if (c == '\0')
                break;
            else if (c == '(')
                ++nest;
            else if (c == ')')
                --nest;
            else if (c == ',' && nest == 1)
                ++commas;
        }
        return commas;
    }

    /** check whether the line[startAt] point to the identifier
     * @code
     *  SomeMethod(arg1, arg2)->Method2()
     *  ^^^^^^^^^^ those index will return true
     * @endcode
     */
    static bool InsideToken(int startAt, const wxString& line)
    {
        return (   (startAt >= 0)
                && ((size_t)startAt < line.Len())
                && (   (wxIsalnum(line.GetChar(startAt)))
                    || (line.GetChar(startAt) == '_') ) );
    }

    /** go to the first character of the identifier, e.g
     * @code
     * "    f(SomeNameSpace::SomeClass.SomeMethod"
     *                    return value^         ^begin
     * @endcode
     *   this is the index before the first character of the identifier
     */
    static int BeginOfToken(int startAt, const wxString& line)
    {
        while (   (startAt >= 0)
               && ((size_t)startAt < line.Len())
               && (   (wxIsalnum(line.GetChar(startAt)))
                   || (line.GetChar(startAt) == '_') ) )
            --startAt;
        return startAt;
    }
    static int BeforeToken(int startAt, const wxString& line)
    {
        if (   (startAt > 0)
            && ((size_t)startAt < line.Len() + 1)
            && (   (wxIsalnum(line.GetChar(startAt - 1)))
                || (line.GetChar(startAt - 1) == '_') ) )
            --startAt;
        return startAt;
    }

    /** check startAt is at some character like:
     * @code
     *  SomeNameSpace::SomeClass
     *                ^ here is a double colon
     *  SomeObject->SomeMethod
     *             ^ here is a pointer member access operator
     * @endcode
     */
    static bool IsOperatorEnd(int startAt, const wxString& line)
    {
        return (   (startAt > 0)
                && ((size_t)startAt < line.Len())
                && (   (   (line.GetChar(startAt) == '>')
                        && (line.GetChar(startAt - 1) == '-') )
                    || (   (line.GetChar(startAt) == ':')
                        && (line.GetChar(startAt - 1) == ':') ) ) );
    }
    static bool IsOperatorPointer(int startAt, const wxString& line)
    {
        return (   (startAt > 0)
            && ((size_t)startAt < line.Len())
            && (   (   (line.GetChar(startAt) == '>')
                    && (line.GetChar(startAt - 1) == '-') )));
    }

    /** check if startAt point to "->" or "::" operator */
     // FIXME (ollydbg#1#): should be startAt+1 < line.Len()?
    static bool IsOperatorBegin(int startAt, const wxString& line)
    {
        return (   (startAt >= 0)
                && ((size_t)startAt < line.Len())
                && (   (   (line.GetChar(startAt ) == '-')
                        && (line.GetChar(startAt + 1) == '>') )
                    || (   (line.GetChar(startAt) == ':')
                        && (line.GetChar(startAt + 1) == ':') ) ) );
    }

    /** check whether line[startAt] is a dot character */
    static bool IsOperatorDot(int startAt, const wxString& line)
    {
        return (   (startAt >= 0)
                && ((size_t)startAt < line.Len())
                && (line.GetChar(startAt) == '.') );
    }

    /** move to the char before whitespace and tabs, e.g.
     * @code
     *  SomeNameSpace       ::  SomeClass
     *              ^end   ^begin
     * note if there some spaces in the beginning like below
     *      "       f::"
     *     ^end    ^begin
     * @endcode
     * the returned index is -1.
     * @return the cursor after the operation
     */
    static int BeforeWhitespace(int startAt, const wxString& line)
    {
        while (   (startAt >= 0)
               && ((size_t)startAt < line.Len())
               && (   (line.GetChar(startAt) == ' ')
                   || (line.GetChar(startAt) == '\t') ) )
            --startAt;
        return startAt;
    }

    /** search from left to right, move the cursor to the first character after the space
     * @code
     *  "       ::   f"
     *   ^begin ^end
     * @endcode
     * @param[in] startAt the begin of the cursor
     * @param[in] line the string buffer
     * @return the location of the cursor
     */
    static int AfterWhitespace(int startAt, const wxString& line)
    {
        if (startAt < 0)
            startAt = 0;
        while (   ((size_t)startAt < line.Len())
               && (   (line.GetChar(startAt) == ' ')
                   || (line.GetChar(startAt) == '\t') ) )
            ++startAt;
        return startAt;
    }

    /** Test whether the current character is a '(' or '['
     * @param startAt the current cursor on the buffer
     * @return true if test is OK
     */
    static bool IsOpeningBracket(int startAt, const wxString& line)
    {
        return (   ((size_t)startAt < line.Len())
                && (   (line.GetChar(startAt) == '(')
                    || (line.GetChar(startAt) == '[') ) );
    }

    /** check the current char (line[startAt]) is either ')' or ']'  */
    static bool IsClosingBracket(int startAt, const wxString& line)
    {
        return (   (startAt >= 0)
                && (   (line.GetChar(startAt) == ')')
                    || (line.GetChar(startAt) == ']') ) );
    }

protected:

private:
    // Helper utilities called only by GenerateResultSet!
    // No critical section needed! All functions that call these functions,
    // should already entered a critical section.

    /** @brief collect child tokens of the specified token, the specified token must be unnamed.
     *
     * used for GenerateResultSet() function
     * @param tree TokenTree pointer
     * @param parent we need to collect the children of this token
     * @param result collected tokens
     * @return bool true if parent is an unnamed class or enum
     */
    bool AddChildrenOfUnnamed(TokenTree* tree, const Token* parent, TokenIdxSet& result)
    {
        if (  ( (parent->m_TokenKind & (tkClass | tkEnum)) != 0 )
            && parent->m_IsAnonymous == true )
        {
            // add all its children
            for (TokenIdxSet::const_iterator it = parent->m_Children.begin();
                                             it != parent->m_Children.end(); ++it)
            {
                Token* tokenChild = tree->at(*it);
                if (    tokenChild
                    && (parent->m_TokenKind == tkClass || tokenChild->m_Scope != tsPrivate) )
                {
                    // NOTE: recurse (eg: class A contains struct contains union or enum)
                    if ( !AddChildrenOfUnnamed(tree, tokenChild, result) )
                    {
                        result.insert(*it);
                        AddChildrenOfEnum(tree, tokenChild, result);
                    }
                }
            }
            return true;
        }
        return false;
    }

    bool AddChildrenOfEnum(TokenTree* tree, const Token* parent, TokenIdxSet& result)
    {
        if (parent->m_TokenKind == tkEnum)
        {
            // add all its children
            for (TokenIdxSet::const_iterator it = parent->m_Children.begin();
                                             it != parent->m_Children.end(); ++it)
            {
                Token* tokenChild = tree->at(*it);
                if (tokenChild && tokenChild->m_Scope != tsPrivate)
                    result.insert(*it);
            }

            return true;
        }
        return false;
    }

    /** @brief check to see if the token is an unnamed class or enum under the parent token
     *
     * This function will internally recursive call itself.
     * @param tree pointer to the TokenTree
     * @param targetIdx the checked token index
     * @param parentIdx the search scope
     * @return bool true if success
     */
    bool IsChildOfUnnamedOrEnum(TokenTree* tree, const int targetIdx, const int parentIdx)
    {
        if (targetIdx == parentIdx)
            return true;
        if (parentIdx == -1)
            return false;

        Token* parent = tree->at(parentIdx);
        if (parent && (parent->m_TokenKind & tkClass))
        {
            // loop all children of the parent token
            for (TokenIdxSet::const_iterator it = parent->m_Children.begin();
                                             it != parent->m_Children.end(); ++it)
            {
                Token* token = tree->at(*it);
                // an unnamed class is much similar like the enum
                if (token && (((token->m_TokenKind & tkClass)
                                && (token->m_IsAnonymous == true))
                             || (token->m_TokenKind & tkEnum)))
                {
                    // if target token matches on child, we can return success
                    // other wise, we try to see the target token matches child's child.
                    if ((targetIdx == (*it)) || IsChildOfUnnamedOrEnum(tree, targetIdx, (*it)))
                        return true;
                }
            }
        }
        return false;
    }


    /**  loop on the input Token index set (source), add all its public constructors to output Token index set (dest) */
    void AddConstructors(TokenTree *tree, const TokenIdxSet& source, TokenIdxSet& dest);

    // for GenerateResultSet()
    bool MatchText(const wxString& text, const wxString& target, bool caseSens, bool isPrefix)
    {
        if (isPrefix && target.IsEmpty())
            return true;
        if (!isPrefix)
            return text.CompareTo(target.wx_str(), caseSens ? wxString::exact : wxString::ignoreCase) == 0;
        // isPrefix == true
        if (caseSens)
            return text.StartsWith(target);
        return text.Upper().StartsWith(target.Upper());
    }

    // for GenerateResultSet()
    bool MatchType(TokenKind kind, short int kindMask)
    {
        return kind & kindMask;
    }

private:
    ParserComponent              m_LastComponent;
    std::map<wxString, wxString> m_TemplateMap;
};

#endif // NATIVEPARSERBASE_H
