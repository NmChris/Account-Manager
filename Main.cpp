#include "Main.h"
#include "App.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_TOOL(wxID_ADD, OnToolAdd)
	EVT_TOOL(wxID_REMOVE, OnToolRemove)
	EVT_BUTTON(UID::LOGIN_BUTTON, OnLoginClick)
	EVT_LISTBOX_DCLICK(UID::ACCOUNT_LISTBOX, OnAccountDoubleClick)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Account manager", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX ^ wxRESIZE_BORDER) {
	// Initializes dialogs
	m_accountInfoDialog		= new wxMultipleTextDialog(this, UID::DIALOG_ACCOUNT_INFO, "Edit account");
	m_confirmationDialog	= new wxMessageDialog(this, "Confirmation text", "Confirmation", wxYES_NO | wxCENTRE | wxSTAY_ON_TOP);
	m_notificationDialog	= new wxMessageDialog(this, "Notification text", "Notification", wxOK | wxCENTRE);
	
	// Create and add items to the toolbar
	wxToolBar* actionToolbar = CreateToolBar();
	actionToolbar->AddTool(wxID_ADD, "Add", wxArtProvider::GetBitmap(wxART_PLUS));
	actionToolbar->AddTool(wxID_REMOVE, "Remove", wxArtProvider::GetBitmap(wxART_MINUS));
	actionToolbar->Realize();

	// Initialize account list and login GUI elements
	wxButton* m_loginButton = new wxButton(this, UID::LOGIN_BUTTON, "Login", wxDefaultPosition, wxSize(300, 30));
	m_accountList = new wxListBox(this, UID::ACCOUNT_LISTBOX, wxDefaultPosition, wxSize(300, 300), EnumerateCredentials(), wxLB_SORT);

	// Adjust panel background colors
	this->SetBackgroundColour(wxColor(171, 171, 171, 255));

	// Initialize sizer and apply sizers
	wxBoxSizer* accountSizer = new wxBoxSizer(wxVERTICAL);
	accountSizer->Add(m_accountList, wxSizerFlags(1).Border());
	accountSizer->Add(m_loginButton, wxSizerFlags(0).Border(wxLEFT | wxRIGHT | wxBOTTOM));
	SetSizerAndFit(accountSizer);
}

void Main::OnLoginClick(wxCommandEvent& event) {
	wxString selectedAlias = m_accountList->GetStringSelection();
	if (selectedAlias == "") {
		UpdateDialogText(m_notificationDialog, "No account selected", "You must select an account before you login.");
		m_notificationDialog->ShowModal();
	} else {
		auto [accountUsername, accountPassword] = ReadCredentials(selectedAlias);
		std::cout << accountPassword << std::endl;
		LoginSteam(accountUsername, accountPassword);
	}
	event.Skip();
}

void Main::OnToolAdd(wxCommandEvent& event) {
	wxString selectedAlias = m_accountList->GetStringSelection();
	if (m_accountInfoDialog->ShowPositionedModal() == wxID_YES) {
		auto [accountAlias, accountUsername, accountPassword] = m_accountInfoDialog->GetValue();
		if (accountAlias.length() > 0 && accountUsername.length() > 0 && accountPassword.length() > 0) {
			if (m_accountList->FindString(accountAlias) == -1) {
				m_accountList->AppendString(accountAlias);
				WriteCredentials(accountAlias, accountUsername, accountPassword);
				UpdateDialogText(m_notificationDialog, "Account added", accountAlias + " has been added to your account list.");
				m_notificationDialog->ShowModal();
			} else {
				m_confirmationDialog->SetTitle("Edit account");
				m_confirmationDialog->SetMessage("Are you sure you want to edit " + accountAlias + "?");
				if (m_confirmationDialog->ShowModal() == wxID_YES) {
					WriteCredentials(accountAlias, accountUsername, accountPassword);
					UpdateDialogText(m_notificationDialog, "Account edited", accountAlias + " has been updated.");
					m_notificationDialog->ShowModal();
				}
			}
		} else {
			UpdateDialogText(m_notificationDialog, "Invalid account information", "The account alias, username, and password must not be empty.");
			m_notificationDialog->ShowModal();
		}
	}
	
	event.Skip();
}

void Main::OnToolRemove(wxCommandEvent& event) {
	wxString selectedAlias = m_accountList->GetStringSelection();
	if (selectedAlias == "") {
		UpdateDialogText(m_notificationDialog, "No account selected", "You must select an account to remove.");
		m_notificationDialog->ShowModal();
	} else {
		UpdateDialogText(m_confirmationDialog, "Account removal", "Are you sure you want to remove " + selectedAlias + " from the account list?");
		if (m_confirmationDialog->ShowModal() == wxID_YES) {
			DeleteCredentials(selectedAlias);
			m_accountList->Delete(m_accountList->GetSelection());
			UpdateDialogText(m_notificationDialog, "Account removed", selectedAlias + " has been removed from your account list.");
			m_notificationDialog->ShowModal();
		}
	}
	event.Skip();
}

void Main::OnAccountDoubleClick(wxCommandEvent& event) {
	OnLoginClick(event);
	event.Skip();
}