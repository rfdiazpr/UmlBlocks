#include "UmlEditor.hpp"

BEGIN_EVENT_TABLE(UmlEditor, EditorBase)
	EVT_SIZE(UmlEditor::OnSize)
END_EVENT_TABLE()

UmlEditor::UmlEditor(wxWindow* parent, const wxString& filename)
	: EditorBase(parent, filename)
{
	m_rRealtime = false;
}

UmlEditor::~UmlEditor()
{
	//dtor
}

UmlCanvas* UmlEditor::GetCanvas() const
{
	return m_pCanvas;
}

void UmlEditor::SetCanvas(UmlCanvas* a)
{
	m_pCanvas = a;
}

bool UmlEditor::IsRealtime()
{
	return m_rRealtime;
}

void UmlEditor::OnSize(wxSizeEvent& event)
{
	m_pCanvas->SetSize(this->GetSize());
}
