#ifndef SMARTINDENTHDL_H_INCLUDED
#define SMARTINDENTHDL_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxScintillaEvent;

class SmartIndentHDL : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxScintillaEvent& event) const;
        virtual void OnCCDone(cbEditor *ed);
    private:
        int FindBlockStartVHDL(cbEditor* ed, int position, wxString block) const;

        void DoIndent  (cbEditor* ed, const wxString& langname) const;
        void DoUnIndent(cbEditor* ed, const wxString& langname) const;
};

#endif // SMARTINDENTHDL_H_INCLUDED
