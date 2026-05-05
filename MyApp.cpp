#include "myApp.h"
#include "MyFrame.h"
#include <wx/wx.h>
#include <iostream>
using namespace std;

//we have to let wxWidgets know which class represents our application
//we do that by calling the wx implement app macro with our app class as parameter
wxIMPLEMENT_APP(MyApp);

//entry point in our application
bool MyApp::OnInit(){

    //we create an instance of our myFrame
    MyFrame* frame = new MyFrame("OOP Project");
    //by default the frame will be hidden so we have to call its show method
    frame->Center();
    frame->Show(true);
    //then we return true, this tells wx wigdets that processing should continue
    // if we returned false our application would close immediately
    return true;
}
