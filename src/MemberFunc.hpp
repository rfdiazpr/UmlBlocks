#ifndef MemberFUNC_HPP
#define MemberFUNC_HPP

#include <vector>
#include <wx/String.h>
#include "MemberVar.hpp"
#include "Member.hpp"

class MemberFunc : public Member
{
    public:
        /** Default constructor */
        MemberFunc(const wxString& a_name = _T("NewFunction"),
				   const wxString& a_type = _T("int"),
				   Accessibility a_access = Public,
				   const std::vector<MemberVar>& a_parameters = std::vector<MemberVar>(),
				   int a_array = 0, int a_pointer = 0, bool a_reference = false,
				   bool a_static = false, bool a_const = false, bool a_virtual = false,
				   bool a_purevirtual = false);
        //MemberFunc(const MemberFunc&);
        /** Default destructor */
        virtual ~MemberFunc();

        //void UpdateParameters(const std::vector<MemberVar>& newparams) {}
        //const wxString& GetUmlString();

        bool IsVirtual() const ;
        bool IsPureVirtual() const ;

        MemberVar& GetParameter(int a) ;
        MemberVar& AddParameter(const MemberVar&, int pos = 0);
        void DeleteParameter(unsigned int i);
        unsigned int GetParameterCount() ;

        void IsVirtual(bool a) ;
        void IsPureVirtual(bool a);

		virtual MemberGroup GetMemberGroup() ;
    protected:
        virtual void CalcUmlString();
    private:
		bool m_Virtual;
        bool m_PureVirtual;
        std::vector<MemberVar> m_Parameters;

        friend class ClassDialog;
};
#endif // MemberFUNC_HPP
