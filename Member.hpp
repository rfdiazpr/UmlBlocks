#ifndef Member_HPP
#define Member_HPP
#include <wx/string.h>
#include <wx/gdicmn.h>
//#include "ClassDialog.hpp" //Odd Inclusion loop happened. Forward declaration seems to fix it.
//class ClassDialog; // This is called a forward declaration, you dummy.
class Member // How unconveniently named. Guess i sorta forgot about other kinds of uml diagrams. A member could be anything of anything. blargh.
{
    public:
        enum Accessibility{
            Public,
            Protected,
            Private,
        };

        /** Default constructor */ // No shit.
        Member(); // Bobcat?
        /** Default destructor */ // Virtual and all.
        virtual ~Member(); // Like that crane thing with a massive metal ball of death.
        wxString GetName() const {return Name;} // Because getting your stuff from the drawer is less messy than having it laying it around.
        wxString GetType() const {return Type;} // *Some other odd metaphor like Lex would have written it* (No, it's not pointers)
        bool IsStatic() const {return Static;} // Dude, i've already told you the metaphor thing. I dunno, replace drawer with a door, or gate or tiny coffin, i guess it would be different.
        bool IsConst() const {return Const;} // Get dat shit!
        virtual wxPoint GetPos() const {return Position;}
        wxSize GetSize() const {return Size;}
        //virtual void RefreshData(ClassDialog*)=0; // So virtual you would think it was in a computer! Wait, what?
        Accessibility GetAccessLevel() const {return Access;} // I fucking love enumerators!
    protected: // Time for some notey info. Protected is like Private, though where the private members can't be accessed by derived classes,
               // the protectd can, while still being isolated from outside the scope like the private. It's good costum to not access variables directly on the object.
    private: // And no, you can't reach through your drawer like a ghost and grab your shit. Ghost drawer! OooooOOooOooOo
        wxString Name; // No comments.
        wxString Type; // I can't access it.
        Accessibility Access; // At least not directly.
        bool Static; // It's locked inside my metaphorical drawer.
        bool Const; // Guess public access is like a fruitbasket then.
        // Giving members some diagram related properties.
        wxPoint Position;
        wxSize Size;
};

#endif // Member_HPP