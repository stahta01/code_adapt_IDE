#ifndef SMARTINDENTPYTHON_H_INCLUDED
#define SMARTINDENTPYTHON_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxScintillaEvent;

class SmartIndentPython : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxScintillaEvent& event) const;
};

#endif // SMARTINDENTPYTHON_H_INCLUDED
