#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "UmlBlocks.hpp"

#include "UmlCanvas.hpp"
#include "Class.hpp"
#include "ClassDialog.hpp"
#include <wx/dialog.h>
#include "Utilities.hpp"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
	PluginRegistrant<UmlBlocks> reg(_T("UmlBlocks"));
}

int NewUmlMenuOptionId = wxNewId();
int NewClassMenuOptionId = wxNewId();
int RevEngiMenuOptionId = wxNewId();
int GenCodeMenuOptionId = wxNewId();
int SavePngMenuOptionId = wxNewId();
// events handling
BEGIN_EVENT_TABLE(UmlBlocks, cbPlugin)
	EVT_MENU(NewUmlMenuOptionId, UmlBlocks::NewUmlMenuOptionFunc)
	EVT_MENU(NewClassMenuOptionId, UmlBlocks::NewClassMenuOptionFunc)
	EVT_MENU(RevEngiMenuOptionId, UmlBlocks::RevEngiMenuOptionFunc)
	EVT_MENU(GenCodeMenuOptionId, UmlBlocks::GenCodeMenuOptionFunc)
	EVT_MENU(SavePngMenuOptionId, UmlBlocks::SavePngMenuOptionFunc)
END_EVENT_TABLE()

// constructor
UmlBlocks::UmlBlocks()
// LETARTARE
	: NewFileMenu(0), UMLMenu(0)
{
	// Make sure our resources are available.
	// In the generated boilerplate code we have no resources but when
	// we add some, it will be nice that this code is in place already ;)
	if(!Manager::LoadResource(_T("UmlBlocks.zip"))) {
		NotifyMissingFile(_T("UmlBlocks.zip"));
	}
}

UmlBlocks::~UmlBlocks() {
}

void UmlBlocks::OnAttach()
{
	// do whatever initialization you need for your plugin
	// NOTE: after this function, the inherited member variable
	// m_IsAttached will be TRUE...
	// You should check for it in other functions, because if it
	// is FALSE, it means that the application did *not* "load"
	// (see: does not need) this plugin...
    Manager::Get()->RegisterEventSink(cbEVT_EDITOR_SWITCHED,
		new cbEventFunctor<UmlBlocks, CodeBlocksEvent>(this, &UmlBlocks::EditorFileSwitched));
	cbPlugin::OnAttach();
}

void UmlBlocks::OnRelease(bool appShutDown)
{
	// do de-initialization for your plugin
	// if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
	// which means you must not use any of the SDK Managers
	// NOTE: after this function, the inherited member variable
	// m_IsAttached will be FALSE...
	for (int i = 0; i < Manager::Get()->GetEditorManager()->GetEditorsCount(); i++)
		if (Manager::Get()->GetEditorManager()->GetEditor(i)->GetTitle().Contains(_T(".cbd")))
			Manager::Get()->GetEditorManager()->GetEditor(i)->Close();

	cbPlugin::OnRelease(appShutDown);
}

int UmlBlocks::Configure()
{
	//create and display the configuration dialog for your plugin
	cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Your dialog title"));
	cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
	if (panel)
	{
		dlg.AttachConfigurationPanel(panel);
		PlaceWindow(&dlg);
		return dlg.ShowModal() == wxID_OK ? 0 : -1;
	}

	return -1;
}

void UmlBlocks::BuildMenu(wxMenuBar* menuBar)
{
	// Lex: This is a section that can often be the cause of a start up crash.

	// Multiline version of the sake of better understanding of the code.
	//NewFileMenu = menuBar->GetMenu(menuBar->FindMenu(_T("File")));
	//NewFileMenu = NewFileMenu->FindItem(NewFileMenu->FindItem(_T("New")))->GetSubMenu();

	NewFileMenu = menuBar->GetMenu(menuBar->FindMenu(_("File")))->FindItem(menuBar->GetMenu(menuBar->FindMenu(_("File")))->FindItem(_("New")))->GetSubMenu();

	// The whole find the "Class..." entry ID process won't work properly, so now shit's hardcoded instead.
	NewFileMenu->Insert( 3, NewUmlMenuOptionId, _("Uml Diagram..."), _("Uml Diagram"),false);

	Manager::Get()->GetLogManager()->Log(_T("MENUBAR DEBUG END"));

	//UML Menu
	UMLMenu = new wxMenu(_T(""));
	menuBar->Insert(menuBar->FindMenu(_("Build"))+1, UMLMenu, _T("Uml"));
	UMLMenu->Append(NewUmlMenuOptionId, _("New Uml Diagram..."), _("Create a new Uml Diagram"));
	UMLMenu->AppendSeparator();
	UMLMenu->Append(NewClassMenuOptionId, _("New Class..."), _("Create a new Class"));
	UMLMenu->AppendSeparator();
	UMLMenu->Append(RevEngiMenuOptionId, _("Reverse Engineer..."), _("Reverse engineer code"));
	UMLMenu->Append(GenCodeMenuOptionId, _("Generate Code..."), _("Generate code from diagram"));
	UMLMenu->Append(SavePngMenuOptionId, _("Save Image..."), _("Create and save a PNG Image"));

	SetUmlTools(false);
}

void UmlBlocks::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
	//Some library module is ready to display a pop-up menu.
	//Check the parameter \"type\" and see which module it is
	//and append any items you need in the menu...
	//TIP: for consistency, add a separator as the first item...
	NotImplemented(_T("UmlBlocks::BuildModuleMenu()"));
}

bool UmlBlocks::BuildToolBar(wxToolBar* toolBar)
{
	//The application is offering its toolbar for your plugin,
	//to add any toolbar items you want...
	//Append any items you need on the toolbar...
	NotImplemented(_T("UmlBlocks::BuildToolBar()"));

	// return true if you add toolbar items
	return false;
}

void UmlBlocks::NewUmlMenuOptionFunc(wxCommandEvent& event)
{
    wxString FileName = _T("Untitled.cbd");

	Manager::Get()->GetLogManager()->Log(_T("New Uml Menu Option Function Invoked"));
	new UmlCanvas(new wxSFDiagramManager(), new UmlEditor(Manager::Get()->GetAppWindow(),FileName));


	ProjectManager* prjMan = Manager::Get()->GetProjectManager();
    cbProject* prj = prjMan->GetActiveProject();

    /*ClassWizardDlg dlg(Manager::Get()->GetAppWindow());
    PlaceWindow(&dlg);
    if (dlg.ShowModal() == wxID_OK)
    {*/
        if (!prj)
        {
            cbMessageBox(   _("The new class has been created."),
                            _("Information"),
                            wxOK | wxICON_INFORMATION,
                            Manager::Get()->GetAppWindow());
        }
        else
		if( cbMessageBox( _("The new diagram has been created.\n"
                            "Do you want to add it to the current project?"),
                            _("Add to project?"),
                            wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION,
                            Manager::Get()->GetAppWindow()) == wxID_YES)
        {
            wxArrayInt targets;
            prjMan->AddFileToProject(FileName, prj, targets);
            /// LETARTARE   svn > 9830
            prjMan->GetUI().RebuildTree();
            /// svn <= 9830
          //  prjMan->RebuildTree();
        }
    //}
}

void UmlBlocks::NewClassMenuOptionFunc(wxCommandEvent& event)
{
	Manager::Get()->GetLogManager()->Log(_T("New Uml Class Option Function Invoked"));
	ClassDialog dlg(Manager::Get()->GetAppWindow());
    PlaceWindow(&dlg);
	if ( dlg.ShowModal() == wxID_OK )
	{
		Manager::Get()->GetLogManager()->Log(_T("Creating shape!"));

		Class* clss = static_cast<Class*>(static_cast<UmlEditor*>(Manager::Get()->GetEditorManager()->GetActiveEditor())
		->GetCanvas()->GetDiagramManager()->AddShape(CLASSINFO(Class),wxPoint(50,50)))
		->Init(dlg.GetClassName());

		clss->SetDescription(dlg.GetClassDescription());
		clss->UpdateFunctions(dlg.GetFunctionList());
		clss->UpdateVariables(dlg.GetVariableList());


		static_cast<UmlEditor*>(Manager::Get()->GetEditorManager()->GetActiveEditor())->GetCanvas()->Refresh(false);
	}
}

void UmlBlocks::RevEngiMenuOptionFunc(wxCommandEvent& event)
{
	Manager::Get()->GetLogManager()->Log(_T("Rev Engi Menu Option Function Invoked"));
}

void UmlBlocks::GenCodeMenuOptionFunc(wxCommandEvent& event)
{
	Manager::Get()->GetLogManager()->Log(_T("Gen Code Menu Option Function Invoked"));
}

void UmlBlocks::SavePngMenuOptionFunc(wxCommandEvent& event)
{
	Manager::Get()->GetLogManager()->Log(_T("Save Png Menu Option Function Invoked"));
}

void UmlBlocks::EditorFileSwitched(CodeBlocksEvent& event)
{
	Manager::Get()->GetLogManager()->Log(_T("Editor Switched File"));
	if (Manager::Get()->GetEditorManager()->GetActiveEditor()->GetTitle().EndsWith(_T(".cbd"))) {
		Manager::Get()->GetLogManager()->Log(_T("File is a diagram"));
		SetUmlTools(true);
	}
	else {
		Manager::Get()->GetLogManager()->Log(_T("File is a text"));
		SetUmlTools(false);
	}
}

void UmlBlocks::SetUmlTools(bool a)
{
    if (a)
        Manager::Get()->GetLogManager()->Log(_T("Tools Activated"));
	else
        Manager::Get()->GetLogManager()->Log(_T("Tools Deactivated"));

	UMLMenu->Enable(NewClassMenuOptionId,a);
	UMLMenu->Enable(RevEngiMenuOptionId,a);
	UMLMenu->Enable(GenCodeMenuOptionId,a);
	UMLMenu->Enable(SavePngMenuOptionId,a);
}
