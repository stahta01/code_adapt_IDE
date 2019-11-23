#ifndef TEXTGRAPH_H
#define TEXTGRAPH_H


#include <vector>
#include <wx/dc.h>
#include <wx/gdicmn.h>

class NassiView;
class NassiBrick;
class TextCtrlTask;
class wxDC;
class wxArrayInt;

class TextGraph
{
    friend class TextCtrlTask;
public:
    //TextGraph(NassiView *view, const wxString &str);
    TextGraph(NassiView *view, NassiBrick *brick, wxUint32 nmbr);
    virtual ~TextGraph();
public:
    wxUint32 GetNumberOfLines();
    void Draw( wxDC *dc );

    wxUint32 GetTotalHeight();
    wxUint32 GetWidth();
    void CalcMinSize( wxDC *dc );
    void SetOffset(wxPoint off);
    bool HasPoint(const wxPoint &pos);
    const wxString *GetStringPtr();
    bool IsUsed(){ return m_used; }
    void SetUsed(bool used = true){ m_used = used; }
    void SetNumber(wxUint32 nmbr);
private:
    TextGraph &operator=(const TextGraph &rhs);
    TextGraph(const TextGraph &rhs);
private:
    bool m_used;
    std::vector<wxPoint> lineoffsets;
    std::vector<wxPoint> linesizes;
    std::vector<wxArrayInt> linewidths;
    wxPoint offset;
    NassiView *m_view;
    //const wxString &m_str;
    NassiBrick *m_brick;
    wxUint32 m_nmbr;
    const wxString *m_str;

private:
    TextCtrlTask *m_editTask;

public:
    void SetEditTask(TextCtrlTask *editTast);
    void ClearEditTask();

};


#endif // TEXTGRAPH_H
