#ifndef SMARTINDENTXML_H_INCLUDED
#define SMARTINDENTXML_H_INCLUDED

#include <cbplugin.h> // for "class cbSmartIndentPlugin"

class cbEditor;
class wxStyledTextEvent;

class SmartIndentXML : public cbSmartIndentPlugin
{
    public:
        virtual void OnEditorHook(cbEditor* ed, wxStyledTextEvent& event) const;
};

#endif // SMARTINDENTXML_H_INCLUDED
