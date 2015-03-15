#include "sdk.h" // Code::Blocks SDK PCH needs to be the first file included.

#ifndef CB_PRECOMP
    #include <manager.h>
#endif // #ifndef CB_PRECOMP

#include "NewEntityDialog.hpp"

NewEntityDialog::NewEntityDialog(int selection)
{
    Create(selection);
}

NewEntityDialog::~NewEntityDialog()
{
    //dtor
}

bool NewEntityDialog::Create(int a)
{
    Initialize();
    switch (a){
        case 1:
            ShowWidgetsA();
            break;
        case 2:
            break;
    }
}

void NewEntityDialog::Initialize()
{
    wxDialog::Create(Manager::Get()->GetAppWindow(),Manager::Get()->GetAppWindow()->GetId(), _T("dat a class"),wxDefaultPosition,wxSize(500,500));
    radbox1 = new wxRadioBox(this,this->GetId(),_("Options"),wxPoint(5,70),wxSize(485,150));
    choice11 = new wxRadioButton(this,this->GetId(), _("Choice"),wxPoint(10,20));
    choice12 = new wxRadioButton(this,this->GetId(), _("Choice"),wxPoint(10,40));
    choice12->Enable(false);
}

void NewEntityDialog::ShowWidgetsA()
{
    SetTitle(_("Add a class"));
    choice11->SetValue(true);
    DeactivateWidgets();
    radbox1->Show(true);
    choice11->Show(true);
    choice12->Show(true);
}

void NewEntityDialog::DeactivateWidgets()
{
    radbox1->Show(false);
    choice11->Show(false);
    choice12->Show(false);
}
