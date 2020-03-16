#ifndef SMARTINDENTLUA_H_INCLUDED
#define SMARTINDENTLUA_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxStyledTextEvent;

class SmartIndentLua : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxStyledTextEvent& event) const;

    private:
        bool BraceIndent(cbStyledTextCtrl *stc, wxString &indent)const;
};

#endif // SMARTINDENTLUA_H_INCLUDED

