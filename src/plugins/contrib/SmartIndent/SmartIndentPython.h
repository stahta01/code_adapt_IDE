#ifndef SMARTINDENTPYTHON_H_INCLUDED
#define SMARTINDENTPYTHON_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxStyledTextEvent;

class SmartIndentPython : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxStyledTextEvent& event) const;
};

#endif // SMARTINDENTPYTHON_H_INCLUDED
