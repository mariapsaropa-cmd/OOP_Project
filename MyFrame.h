#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>
#include <wx/choice.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

    // Event Handlers
    void OnConvertButtonClicked(wxCommandEvent& event);
    void OnClearButtonClicked(wxCommandEvent& event);
    void OnSwapButtonClicked(wxCommandEvent& event);
    void OnLanguageChoice(wxCommandEvent& event);
    void OnButtonClicked(wxCommandEvent& event); // keyboard

private:
    // UI organization functions
    void CreateControls();
    void CreateSizers();
    void BindEventHandlers();
    
    // helper functions
    void TranslateText();
    wxString GetLanguageCode(const wxString& language);

    // UI 
    wxPanel* panel;
    wxTextCtrl* inputText;
    wxTextCtrl* translatedText;
    wxChoice* inputLanguageChoice;
    wxChoice* outputLanguageChoice;
    wxButton* convertButton;
    wxButton* clearButton;
    wxButton* swapButton;
    wxStaticBitmap* staticBitmap;

    // keyboard
    bool isShiftPressed = false;
    bool isCapsLockOn = false;

    // IDs
    enum {
        ID_InputLanguageChoice = 1001,
        ID_OutputLanguageChoice,
        ID_ConvertButton,
        ID_ClearButton,
        ID_SwapButton
    };

    wxDECLARE_EVENT_TABLE();
};

#endif //MYFRAME_H