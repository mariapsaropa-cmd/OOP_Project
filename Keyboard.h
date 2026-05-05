#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <wx/wx.h>
#include "MyFrame.h"

class Keyboard
{
public:
    Keyboard(wxPanel* parent, MyFrame* frame);
    wxSizer* GetSizer() const;
    void CreateControls(wxPanel* parent, MyFrame* frame);
    void AddRowButtons(wxBoxSizer* rowSizer, const wxString* keys, int count, MyFrame* frame, wxPanel* parent);

private:
    wxBoxSizer* keyboardSizer;
    wxFont keyboardFont;
};

#endif // KEYBOARD_H