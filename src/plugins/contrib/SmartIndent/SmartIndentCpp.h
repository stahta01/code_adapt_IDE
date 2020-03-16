#ifndef SMARTINDENTCPP_H_INCLUDED
#define SMARTINDENTCPP_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class SmartIndentCpp : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxStyledTextEvent& event) const;

    private:
        void DoSmartIndent(cbEditor *ed, const wxChar &ch)const;
        bool BraceIndent(cbStyledTextCtrl *control, wxString &indent)const;
        void DoSelectionBraceCompletion(cbStyledTextCtrl *control, const wxChar &ch)const;
        void DoBraceCompletion(cbStyledTextCtrl *control, const wxChar& ch)const;
};

#endif // SMARTINDENTCPP_H_INCLUDED

