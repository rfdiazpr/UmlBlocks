#ifndef Member_HPP
#define Member_HPP

#include <wx/string.h>
#include <wx/gdicmn.h>

enum Accessibility
{
	Public = 0,
	Protected = 1,
	Private = 2,
};

enum MemberGroup
{
	Variables,
	Functions,
};

class Member
{
    public:
        Member(const wxString& a_name = _T("NewMember"), const wxString& a_type = _T("void"),
			   Accessibility a_access = Public, int a_array = 0,
			   unsigned int a_pointer = 0, bool a_reference = false,
			   bool a_static = false, bool a_const = false);

        virtual ~Member();

        const wxString& GetUmlString();

        const wxString& GetName() const ;
        const wxString& GetType() const ;
        bool IsArray() const ;
        int GetArraySize() const ;
        bool GetArray() const ;
        bool IsStatic() const ;
        bool IsConst() const ;
        bool IsPointer() const ;
        int GetPointerDepth() const ;
        bool IsReference() const ;
        Accessibility GetAccessLevel() const ;

	virtual MemberGroup GetMemberGroup() = 0;

        void SetName(wxString a) ;
        void SetType(wxString a) ;
        void IsArray(bool a) ;
        void SetArraySize(int a) ;
        void SetAccessLevel(Accessibility a) ;
        void IsPointer(bool a) ;
        void SetPointerDepth(int a) ;
        void IsReference(bool a) ;
        void IsStatic(bool a) ;
        void IsConst(bool a) ;

    protected:
        void UpdateUmlString();
        virtual void CalcUmlString();
        //bool NeedUmlRefresh() ;
        //void DoUmlRefresh(bool a = true) ;
        const wxString& GetRawUmlString() ;
        void SetUmlString(const wxString& a) ;

    private:
        wxString m_Name;
        wxString m_Type;
        bool m_Array;
        int m_ArraySize;
        Accessibility m_Access;
        bool m_Pointer;
        int m_PointerDepth;
	bool m_Reference;
        bool m_Static;
        bool m_Const;

        wxString m_UmlString;
/// LETARTARE
        bool m_UmlRefresh ;

};

#endif // Member_HPP
