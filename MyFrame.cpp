#include "MyFrame.h"
#include "Keyboard.h"
#include "Languages.h"
#include <wx/wx.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <utility>
using json = nlohmann::json;
using namespace std;
using namespace cpr;



wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_ConvertButton, MyFrame::OnConvertButtonClicked)
    EVT_BUTTON(ID_ClearButton, MyFrame::OnClearButtonClicked)
    EVT_BUTTON(ID_SwapButton, MyFrame::OnSwapButtonClicked)
    EVT_CHOICE(ID_InputLanguageChoice, MyFrame::OnLanguageChoice)
    EVT_CHOICE(ID_OutputLanguageChoice, MyFrame::OnLanguageChoice)
wxEND_EVENT_TABLE()


MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 600)), 
      inputText(nullptr), translatedText(nullptr), inputLanguageChoice(nullptr)
{
    CreateControls();
    CreateSizers();
    BindEventHandlers();
}

void MyFrame::CreateControls() {
    wxFont textControlFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColor(204, 233, 245));

    wxArrayString languages;
    
    for (const auto& lang : LANGUAGE_MAP) {
        languages.Add(lang.first); // first - name 
    }

    inputLanguageChoice = new wxChoice(panel, ID_InputLanguageChoice, wxDefaultPosition, wxDefaultSize, languages);
    outputLanguageChoice = new wxChoice(panel, ID_OutputLanguageChoice, wxDefaultPosition, wxDefaultSize, languages);
    inputLanguageChoice->SetSelection(1);  // Default to Greek
    outputLanguageChoice->SetSelection(0);  // Default to English

    inputText = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 200), wxTE_MULTILINE);
    translatedText = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 200), wxTE_MULTILINE | wxTE_READONLY);
    
    inputText->SetBackgroundColour(wxColor(240, 247, 249));
    inputText->SetFont(textControlFont);
    translatedText->SetBackgroundColour(wxColor(240, 247, 249));
    translatedText->SetFont(textControlFont);

    swapButton = new wxButton(panel, ID_SwapButton, "Swap");
    convertButton = new wxButton(panel, ID_ConvertButton, "Convert", wxPoint(250, 550), wxSize(200, 50));
    clearButton = new wxButton(panel, ID_ClearButton, "Clear", wxPoint(500, 550), wxSize(200, 50));
    
    convertButton->SetBackgroundColour(wxColor(176, 209, 165));
    clearButton->SetBackgroundColour(wxColor(244, 169, 216));

    wxPNGHandler* handler = new wxPNGHandler;
    wxImage::AddHandler(handler);
    wxImage image("images/logo.png", wxBITMAP_TYPE_PNG);
    staticBitmap = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(image), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
}

void MyFrame::CreateSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* imageSizer = new wxBoxSizer(wxHORIZONTAL);
    imageSizer->Add(staticBitmap, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(imageSizer, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxVERTICAL);
    inputSizer->Add(inputLanguageChoice, 0, wxEXPAND | wxALL, 5);
    inputSizer->Add(inputText, 0, wxEXPAND | wxALL, 5);

    wxBoxSizer* outputSizer = new wxBoxSizer(wxVERTICAL);
    outputSizer->Add(outputLanguageChoice, 0, wxEXPAND | wxALL, 5);
    outputSizer->Add(translatedText, 0, wxEXPAND | wxALL, 5);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(inputSizer, 1, wxEXPAND | wxALL, 5);
    topSizer->Add(swapButton, 0, wxALIGN_CENTER | wxALL, 5);
    topSizer->Add(outputSizer, 1, wxEXPAND | wxALL, 5);

    Keyboard* keyboard = new Keyboard(panel, this);
    mainSizer->Add(topSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(keyboard->GetSizer(), 0, wxEXPAND | wxALL, 5);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(convertButton, 0, wxEXPAND | wxALL, 5);
    buttonSizer->Add(clearButton, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
}

void MyFrame::BindEventHandlers() {
    convertButton->Bind(wxEVT_BUTTON, &MyFrame::OnConvertButtonClicked, this);
    clearButton->Bind(wxEVT_BUTTON, &MyFrame::OnClearButtonClicked, this);
    swapButton->Bind(wxEVT_BUTTON, &MyFrame::OnSwapButtonClicked, this);
    inputLanguageChoice->Bind(wxEVT_CHOICE, &MyFrame::OnLanguageChoice, this);
    outputLanguageChoice->Bind(wxEVT_CHOICE, &MyFrame::OnLanguageChoice, this);
}

void MyFrame::OnLanguageChoice(wxCommandEvent& event) {}

void MyFrame::OnConvertButtonClicked(wxCommandEvent& event) {
    TranslateText();
}

void MyFrame::OnClearButtonClicked(wxCommandEvent& event) {
    inputText->Clear();
    translatedText->Clear();
}

void MyFrame::OnSwapButtonClicked(wxCommandEvent& event) {
    wxString tempText = inputText->GetValue();
    inputText->SetValue(translatedText->GetValue());
    translatedText->SetValue(tempText);

    int tempLangIndex = inputLanguageChoice->GetSelection();
    inputLanguageChoice->SetSelection(outputLanguageChoice->GetSelection());
    outputLanguageChoice->SetSelection(tempLangIndex);
}

void MyFrame::OnButtonClicked(wxCommandEvent& event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        wxString label = button->GetLabel();
        if (label == "Backspace") {
            wxString currentText = inputText->GetValue();
            if (!currentText.IsEmpty()) {
                currentText.RemoveLast();
                inputText->SetValue(currentText);
            }
        }
        else if (label == "Enter") { inputText->AppendText("\n"); }
        else if (label == "Space") { inputText->AppendText(" "); }
        else if (label == "Tab") { inputText->AppendText("\t"); }
        else if (label == "Shift") { isShiftPressed = !isShiftPressed; }
        else if (label == "Caps Lock") { isCapsLockOn = !isCapsLockOn; }
        else if (label == "Ctrl" || label == "Alt" || label == "Win" || label == "Menu" || label == "Esc") {}
        else {
            if (isShiftPressed || isCapsLockOn) {
                inputText->AppendText(label.Upper());
                isShiftPressed = false; 
            }
            else { inputText->AppendText(label.Lower()); }
        }
    }
}


wxString MyFrame::GetLanguageCode(const wxString& language) {
    for (const auto& lang : LANGUAGE_MAP) {
        if (lang.first == language) {
            return lang.second; // second-code
        }
    }
    return "en"; // default
}

void MyFrame::TranslateText() {
    wxString input = inputText->GetValue();
    if (input.IsEmpty()) {
        wxMessageBox(wxString::FromUTF8("Please provide something to translate!"), "Warning");
        return;
    }

    wxString sourceName = inputLanguageChoice->GetStringSelection();
    wxString targetName = outputLanguageChoice->GetStringSelection();

    string src = this->GetLanguageCode(sourceName).ToStdString();
    string tgt = this->GetLanguageCode(targetName).ToStdString();

    string langpair = src + "|" + tgt;

    translatedText->SetValue(wxString::FromUTF8("Translation in progress..."));

    try {
        Response r = cpr::Get(
            Url{"https://api.mymemory.translated.net/get"},
            Parameters{
                {"q", input.ToUTF8().data()},
                {"langpair", langpair}
            },
            Timeout{10000},
            VerifySsl{false}
        );

        if (r.status_code == 200) {
            auto j = json::parse(r.text);
            std::string result = j["responseData"]["translatedText"].get<string>();
            translatedText->SetValue(wxString::FromUTF8(result));
        } else {
            wxString errorMsg = wxString::Format("API Error!\nStatus: %ld\n%s", 
                                               r.status_code, r.error.message);
            wxMessageBox(errorMsg, "Error");
            translatedText->SetValue(wxString::FromUTF8("Connection Failure!"));
        }
    } catch (const exception& e) {
        wxMessageBox(e.what(), "Exception");
    }
}