#include "sdk.h" // Code::Blocks SDK PCH needs to be the first file included.

#ifndef CB_PRECOMP
    #include <manager.h>
#endif // #ifndef CB_PRECOMP

#include "QuickEditPopup.hpp"

QuickEditPopup::QuickEditPopup(const wxPoint& a_Position):wxPopupTransientWindow(Manager::Get()->GetAppWindow())
{
    //ctor
    Position(a_Position,wxSize(50,50));
}

QuickEditPopup::~QuickEditPopup()
{
    //dtor
}
