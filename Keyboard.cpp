#include "myframe.h"
#include "keyboard.h"
#include <wx/wx.h>
#include <iostream>
using namespace std;

Keyboard::Keyboard(wxPanel* parent, MyFrame* frame) : keyboardSizer(nullptr) {
    keyboardFont = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Verdana");

    CreateControls(parent, frame);
}

void Keyboard::CreateControls(wxPanel* parent, MyFrame* frame) {
    // Define keys
    wxString row1[] = { "`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace" };
    wxString row2[] = { "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\\" };
    wxString row3[] = { "Caps Lock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter" };
    wxString row4[] = { "Shift", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Shift" };
    wxString row5[] = { "Ctrl", "Win", "Alt", "Space", "Alt", "Win", "Menu", "Ctrl" };

    // Create the main keyboard sizer
    keyboardSizer = new wxBoxSizer(wxVERTICAL);

    // Add rows to the main sizer
    wxBoxSizer* row1Sizer = new wxBoxSizer(wxHORIZONTAL);
    AddRowButtons(row1Sizer, row1, sizeof(row1) / sizeof(wxString), frame, parent);
    keyboardSizer->Add(row1Sizer, 0, wxALIGN_CENTER | wxALL, 1);

    wxBoxSizer* row2Sizer = new wxBoxSizer(wxHORIZONTAL);
    AddRowButtons(row2Sizer, row2, sizeof(row2) / sizeof(wxString), frame, parent);
    keyboardSizer->Add(row2Sizer, 0, wxALIGN_CENTER | wxALL, 1);

    wxBoxSizer* row3Sizer = new wxBoxSizer(wxHORIZONTAL);
    AddRowButtons(row3Sizer, row3, sizeof(row3) / sizeof(wxString), frame, parent);
    keyboardSizer->Add(row3Sizer, 0, wxALIGN_CENTER | wxALL, 1);

    wxBoxSizer* row4Sizer = new wxBoxSizer(wxHORIZONTAL);
    AddRowButtons(row4Sizer, row4, sizeof(row4) / sizeof(wxString), frame, parent);
    keyboardSizer->Add(row4Sizer, 0, wxALIGN_CENTER | wxALL, 1);

    wxBoxSizer* row5Sizer = new wxBoxSizer(wxHORIZONTAL);
    AddRowButtons(row5Sizer, row5, sizeof(row5) / sizeof(wxString), frame, parent);
    keyboardSizer->Add(row5Sizer, 0, wxALIGN_CENTER | wxALL, 1);
}

void Keyboard::AddRowButtons(wxBoxSizer* rowSizer, const wxString* keys, int count, MyFrame* frame, wxPanel* parent) {
    for (int i = 0; i < count; i++) {
        wxString key = keys[i];
        wxButton* button;
        
        if (key == "Space") {
            button = new wxButton(parent, wxID_ANY, key, wxDefaultPosition, wxSize(200, 30));
        }
        else if (key == "Backspace" || key == "Enter" || key == "Shift" || key == "Caps Lock" || key == "Tab") {
            button = new wxButton(parent, wxID_ANY, key, wxDefaultPosition, wxSize(125, 30));
        }
        else {
            button = new wxButton(parent, wxID_ANY, key);
        }

        button->SetBackgroundColour(wxColour(124, 193, 215));
        button->SetForegroundColour(wxColour(255, 255, 255)); // White text
        button->SetFont(keyboardFont); // Set the custom font
        button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClicked, frame);
        rowSizer->Add(button, 0, wxALL, 2);
    }
}

wxSizer* Keyboard::GetSizer() const {
    return keyboardSizer;
}