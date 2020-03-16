#ifndef SMARTINDENTPASCAL_H_INCLUDED
#define SMARTINDENTPASCAL_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxStyledTextEvent;

class SmartIndentPascal : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxStyledTextEvent& event) const;

    private:
        void DoIndent  (cbEditor* ed, const wxString& langname) const;
        void DoUnIndent(cbEditor* ed, const wxString& langname) const;
};

#endif // SMARTINDENTPASCAL_H_INCLUDED
