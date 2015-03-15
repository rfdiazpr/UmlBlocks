#ifndef MemberVAR_HPP
#define MemberVAR_HPP

#include <wx/String.h>
#include "Member.hpp"

class MemberVar : public Member
{
    public:
        MemberVar(const wxString& a_name = _T("NewVariable"),
				  const wxString& a_type = _T("int"),
				  Accessibility a_access = Public,
				  int a_array = 0,
				  int a_pointer = 0,
				  bool a_reference = false,
				  bool a_static = false,
				  bool a_const = false,
				  const wxString& a_defval = _T(""));
		//MemberVar(const MemberVar&);
        virtual ~MemberVar();

        //virtual const wxString& GetUmlString();

        const wxString& GetDefaultValue() {return m_DefaultVal;}

        void SetDefaultValue(wxString a) {m_DefaultVal = a.Trim(false).Trim(); UpdateUmlString();}

		virtual MemberGroup GetMemberGroup() { return Variables; }
    protected:
        virtual void CalcUmlString();
    private:
		wxString m_DefaultVal;
};
#endif // MemberVAR_HPP
