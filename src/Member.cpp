#include "Member.hpp"
#include "Utilities.hpp"

Member::Member(const wxString& a_name, const wxString& a_type,
			   Accessibility a_access, int a_array,
			   unsigned int a_pointer, bool a_reference,
			   bool a_static,  bool a_const)
	: m_Name(a_name), m_Type(a_type), m_Access(a_access), m_PointerDepth(a_pointer),
	m_Reference(a_reference), m_Static(a_static), m_Const(a_const), m_ArraySize(a_array),
	/// LETARTARE
	m_UmlRefresh(true)
{
	if (a_pointer != 0)
		m_Pointer = true;
	else
		m_Pointer = false;

	if (a_array > 0)
		m_Array = true;
	else
		m_Array = false;

		m_UmlString = _T("undefined");
}

Member::~Member()
{
    //dtor
}

const wxString& Member::GetUmlString()
{
	if (m_UmlRefresh)
	{
		m_UmlRefresh = false;
		CalcUmlString();
	}

	return m_UmlString;
}

void Member::CalcUmlString()
{
	wxString strng(m_Name);

	if (m_Const)
		strng.MakeUpper();

	/*if (m_Type != _T("ctor"))
		if (m_Type != _T("dtor"))
			strng.Append(_T(" : ") + m_Type);
		else
			strng.Prepend(_T("~"));*/
	if (m_Type == _T("ctor"))
	{
	}
	else
	if (m_Type == _T("dtor"))
	{
		strng.Prepend(_T("~"));
	}
	else
	{ //Regular type stuff
		strng.Append(_T(" : "));
		if (m_Static)
			strng.Append(_T("static "));
		if (m_Const)
			strng.Append(_T("const "));

		strng.Append(m_Type);
		if (m_Reference)
			strng.Append(_T("&"));
		if (m_Pointer)
			for (int i=0;i<m_PointerDepth;i++)
				strng.Append(_T("*"));
		if (m_Array)
			strng.Append(_T("[]"));

		if (m_Static)
		{
			strng.Append(_T("_"));
			strng.Prepend(_T("_"));
		}
	}

	switch (m_Access)
	{
		case Public:
			strng.Prepend(_T("+"));
			break;
		case Protected:
			strng.Prepend(_T("#"));
			break;
		case Private:
			strng.Prepend(_T("-"));
			break;
	}

    m_UmlString = strng;
}

const wxString& Member::GetName() const
{
	return m_Name;
}

const wxString& Member::GetType() const
{
	return m_Type;
}

bool Member::IsArray() const
{
	return m_Array;
}

int Member::GetArraySize() const
{
	return m_ArraySize;
}

bool Member::GetArray() const
{
	return m_Array;
}

bool Member::IsStatic() const
{
	return m_Static;
}

bool Member::IsConst() const
{
	return m_Const;
}

bool Member::IsPointer() const
{
	return m_Pointer;
}

int Member::GetPointerDepth() const
{
	return m_PointerDepth;
}

bool Member::IsReference() const
{
	return m_Reference;
}

Accessibility Member::GetAccessLevel() const
{
	return m_Access;
}

void Member::SetName(wxString a)
{
	m_Name = a.Trim(false).Trim();
	UpdateUmlString();
}

void Member::SetType(wxString a)
{
	m_Type = a.Trim(false).Trim();
	UpdateUmlString();
}

void Member::IsArray(bool a)
{
	m_Array = a;
	UpdateUmlString();
}

void Member::SetArraySize(int a)
{
	m_ArraySize = a; UpdateUmlString();
}

void Member::SetAccessLevel(Accessibility a)
{
	m_Access = a; UpdateUmlString();
}

void Member::IsPointer(bool a)
{
	m_Pointer = a; UpdateUmlString();
}

void Member::SetPointerDepth(int a)
{
	m_PointerDepth = a; UpdateUmlString();
}

void Member::IsReference(bool a)
{
	m_Reference = a; UpdateUmlString();
}

void Member::IsStatic(bool a)
{
	m_Static = a; UpdateUmlString();
}

void Member::IsConst(bool a)
{
	m_Const = a; UpdateUmlString();
}

void Member::UpdateUmlString()
{
	m_UmlRefresh = true;
}

//bool Member::NeedUmlRefresh() {return m_UmlRefresh;}
//void Member::DoUmlRefresh(bool a = true) {m_UmlRefresh = a;}

const wxString& Member::GetRawUmlString()
{
	return m_UmlString;
}

void Member::SetUmlString(const wxString& a)
{
	m_UmlString = a;
}
