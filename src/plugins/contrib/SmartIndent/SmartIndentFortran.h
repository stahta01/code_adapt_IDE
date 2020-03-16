#ifndef SMARTINDENTFORTRAN_H_INCLUDED
#define SMARTINDENTFORTRAN_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxStyledTextEvent;

class SmartIndentFortran : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxStyledTextEvent& event) const;

    private:
        void DoBraceCompletion(cbStyledTextCtrl* control, const wxChar& ch) const;
};

#endif // SMARTINDENTFORTRAN_H_INCLUDED
