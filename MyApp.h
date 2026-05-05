#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>

class MyApp : public wxApp {
    public:
        virtual bool OnInit();
};
wxDECLARE_APP(MyApp);

#endif // MYAPP_H