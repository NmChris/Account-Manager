#include "App.h"
#include "Main.h"
#include "Identifiers.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_BUTTON(UID::LOGIN_BUTTON, Login)
	//EVT_LISTBOX(UID::ACCOUNT_LISTBOX, AccountSelected)
	EVT_LISTBOX_DCLICK(UID::ACCOUNT_LISTBOX, AccountDoubleClicked)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Account manager", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX ^ wxRESIZE_BORDER) {
	m_accountManager = CAccountManager();
	wxArrayString accountArray = wxArrayString();
	m_accountManager.getAccounts(&accountArray);

	// Initialize the dialog popup
	m_messageDialog = new wxMessageDialog(this, "Test messag", "Confirm the following action", wxYES_NO | wxCENTRE | wxSTAY_ON_TOP, wxDefaultPosition);


	// Custom dialog
	/*wxDialog* add_dialog = new wxDialog(this, wxID_ANY, "Add account");
	add_dialog->ShowModal();

	wxTextEntryDialog* test_entry = new wxTextEntryDialog(this, "Test message", "test caption");
	test_entry->ShowModal();*/

	wxMultipleTextDialog* test = new wxMultipleTextDialog(this, wxID_ANY, "Test");
	test->ShowModal();

	// Menu bar
	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* account_menu = new wxMenu();

	account_menu->Append(wxID_ANY, "Add");
	account_menu->Append(wxID_ANY, "Remove");
	account_menu->Append(wxID_ANY, "Edit");

	menubar->Append(account_menu, "Account");
	SetMenuBar(menubar);

	// Initialize account list and login GUI elements
	m_login = new wxButton(this, UID::LOGIN_BUTTON, "Login", wxDefaultPosition, wxSize(300, 30));
	m_accountList = new wxListBox(this, UID::ACCOUNT_LISTBOX, wxDefaultPosition, wxSize(300, 300), accountArray, wxLB_SORT);

	
	// Adjust panel background colors
	this->SetBackgroundColour(wxColor(171, 171, 171, 255));

	// Initialize sizers
	wxBoxSizer* account_sizer = new wxBoxSizer(wxVERTICAL);
	account_sizer->Add(m_accountList, wxSizerFlags(1).Border());
	account_sizer->Add(m_login, wxSizerFlags(0).Border(wxLEFT | wxRIGHT | wxBOTTOM));

	// Apply sizers
	SetSizerAndFit(account_sizer);
}

//void Main::AddAccount(wxCommandEvent &event) {
//	wxString alias		= m_alias->GetValue();
//	wxString username	= m_username->GetValue();
//	wxString password	= m_password->GetValue();
//
//	int alias_length	= alias.length();
//	int username_length = username.length();
//	int password_length = password.length();
//	
//	if (alias_length > 0 && username_length > 0 && password_length > 0) {
//		if (m_accountList->FindString(alias) == -1) {
//			m_accountList->AppendString(alias);
//			m_accountManager.addAccount(alias, username, password);
//		} else {
//			m_messageDialog->SetMessage("Are you sure you want to edit this account?");
//			if (m_messageDialog->ShowModal() == wxID_YES) {
//				m_accountManager.addAccount(alias, username, password);
//			}
//		}
//	} else {
//		wxString error_message = "Cannot add account. The following fields are empty: \n";
//
//		if (alias_length == 0)
//			error_message += "alias, ";
//		if (username_length == 0)
//			error_message += "username, ";
//		if (password_length == 0)
//			error_message += "password, ";
//
//		m_messageDialog->SetMessage(error_message.substr(0, error_message.length() - 2));
//		m_messageDialog->ShowModal();
//	}
//	event.Skip();
//}
//
//void Main::RemoveAccount(wxCommandEvent &event) {
//	const int account_index = m_accountList->GetSelection();
//	if (account_index >= 0) {
//		wxString alias = m_accountList->GetStringSelection();
//		m_messageDialog->SetMessage("Are you sure you want to remove " + alias + " from the account list?");
//		if (m_messageDialog->ShowModal() == wxID_YES) {
//			m_alias->Clear();
//			m_username->Clear();
//			m_password->Clear();
//
//			m_accountManager.removeAccount(alias);
//			m_accountList->Delete(account_index);
//		}
//	} else {
//		m_messageDialog->SetMessage("Select an account to remove.");
//		m_messageDialog->ShowModal();
//	}
//	event.Skip();
//}

void Main::Login(wxCommandEvent &event) {
	if (m_accountList->GetSelection() >= 0) {
		wxString alias = m_accountList->GetStringSelection();
		wxString username = m_accountManager.getAccountUsername(alias);
		wxString password = m_accountManager.getAccountPassword(alias);
		m_accountManager.loginToAccount(username, password);
	} else {
		m_messageDialog->SetMessage("Select an account to log in to. ");
		m_messageDialog->ShowModal();
	}
	event.Skip();
}

//void Main::AccountSelected(wxCommandEvent &event) {
//	wxString alias = m_accountList->GetStringSelection();
//	wxString username = m_accountManager.getAccountUsername(alias);
//	wxString password = m_accountManager.getAccountPassword(alias);
//
//	m_alias->SetValue(alias);
//	m_username->SetValue(username);
//	m_password->SetValue(password);
//}

void Main::AccountDoubleClicked(wxCommandEvent &event) {
	Login(event);
}