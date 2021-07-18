#include "Main.h"
#include "App.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_MENU(wxID_ADD, OnMenuAdd)
	EVT_MENU(wxID_EDIT, OnMenuEdit)
	EVT_MENU(wxID_REMOVE, OnMenuRemove)
	EVT_MENU(wxID_INFO, OnMenuInfo)
	EVT_BUTTON(UID::LOGIN_BUTTON, OnLoginClick)
	EVT_LISTBOX_DCLICK(UID::ACCOUNT_LISTBOX, OnAccountDoubleClick)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Account manager", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX ^ wxRESIZE_BORDER) {
	// Initializes dialogs
	m_accountInfoDialog		= new wxMultipleTextDialog(this, UID::DIALOG_ACCOUNT_INFO, "Edit account");
	m_confirmationDialog	= new wxMessageDialog(this, "Confirmation text", "Confirmation", wxYES_NO | wxCENTRE | wxSTAY_ON_TOP);
	m_notificationDialog	= new wxMessageDialog(this, "Notification text", "Notification", wxOK | wxCENTRE);
	m_displayInfoDialog		= new wxMessageDialog(this, "Account info", "Info", wxICON_INFORMATION | wxOK | wxCENTER);
	
	// Create a menu bar for account operations
	wxMenu* accountMenu = new wxMenu();
	accountMenu->Append(wxID_ADD, "Add");
	accountMenu->Append(wxID_EDIT, "Edit");
	accountMenu->Append(wxID_REMOVE, "Remove");
	accountMenu->Append(wxID_INFO, "Show info");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(accountMenu, "Account");
	SetMenuBar(menuBar);

	// Initialize account list and login GUI elements
	m_loginButton = new wxButton(this, UID::LOGIN_BUTTON, "Login", wxDefaultPosition, wxSize(300, 30), wxNO_BORDER);
	m_accountList = new wxListBox(this, UID::ACCOUNT_LISTBOX, wxDefaultPosition, wxSize(300, 300), EnumerateCredentials(), wxLB_SORT | wxNO_BORDER);

	// Set mouse events
	m_loginButton->Bind(wxEVT_ENTER_WINDOW, &Main::OnLoginMouseOver, this);
	m_loginButton->Bind(wxEVT_LEAVE_WINDOW, &Main::OnLoginMouseLeave, this);

	// Adjust panel background colors
	this->SetBackgroundColour(panelBackgroundColor);

	// Adjust item colors
	m_loginButton->SetBackgroundColour(menuItemBackgroundColor);
	m_loginButton->SetForegroundColour(menuItemForegroundColor);
	m_accountList->SetBackgroundColour(menuItemBackgroundColor);
	m_accountList->SetForegroundColour(menuItemForegroundColor);

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
		auto [accountAlias, accountUsername, accountPassword, accountDescription] = ReadCredentials(selectedAlias);
		std::cout << accountPassword << std::endl;
		LoginSteam(accountUsername, accountPassword);
	}
	event.Skip();
}

void Main::OnMenuAdd(wxCommandEvent& event) {
	m_accountInfoDialog->SetAliasValue("");
	m_accountInfoDialog->SetUsernameValue("");
	m_accountInfoDialog->SetPasswordValue("");
	m_accountInfoDialog->SetDescriptionValue("");
	if (m_accountInfoDialog->ShowPositionedModal() == wxID_YES) {
		auto [accountAlias, accountUsername, accountPassword, accountDescription] = m_accountInfoDialog->GetValue();
		if (accountAlias.length() > 0 && accountUsername.length() > 0 && accountPassword.length() > 0) {
			if (m_accountList->FindString(accountAlias) == -1) {
				m_accountList->AppendString(accountAlias);
				WriteCredentials(accountAlias, accountUsername, accountPassword, accountDescription);
				UpdateDialogText(m_notificationDialog, "Account added", accountAlias + " has been added to your account list.");
				m_notificationDialog->ShowModal();
			} else {
				m_confirmationDialog->SetTitle("Edit account");
				m_confirmationDialog->SetMessage("Are you sure you want to edit " + accountAlias + "?");
				if (m_confirmationDialog->ShowModal() == wxID_YES) {
					WriteCredentials(accountAlias, accountUsername, accountPassword, accountDescription);
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

void Main::OnMenuEdit(wxCommandEvent& event) {
	wxString selectedAlias = m_accountList->GetStringSelection();
	if (selectedAlias == "") {
		UpdateDialogText(m_notificationDialog, "No account selected", "You must select an account to edit.");
		m_notificationDialog->ShowModal();
	} else {
		auto [accountAlias, accountUsername, accountPassword, accountDescription] = ReadCredentials(selectedAlias);
		m_accountInfoDialog->SetAliasValue(accountAlias);
		m_accountInfoDialog->SetUsernameValue(accountUsername);
		m_accountInfoDialog->SetPasswordValue(accountPassword);
		m_accountInfoDialog->SetDescriptionValue(accountDescription);
		if (m_accountInfoDialog->ShowPositionedModal() == wxID_YES) {
			auto [accountAlias, accountUsername, accountPassword, accountDescription] = m_accountInfoDialog->GetValue();
			if (accountAlias.length() > 0 && accountUsername.length() > 0 && accountPassword.length() > 0) {
				if (m_accountList->FindString(accountAlias) == -1) {
					m_accountList->AppendString(accountAlias);
					WriteCredentials(accountAlias, accountUsername, accountPassword, accountDescription);
					UpdateDialogText(m_notificationDialog, "Account added", accountAlias + " has been added to your account list.");
					m_notificationDialog->ShowModal();
				}
				else {
					m_confirmationDialog->SetTitle("Edit account");
					m_confirmationDialog->SetMessage("Are you sure you want to edit " + accountAlias + "?");
					if (m_confirmationDialog->ShowModal() == wxID_YES) {
						WriteCredentials(accountAlias, accountUsername, accountPassword, accountDescription);
						UpdateDialogText(m_notificationDialog, "Account edited", accountAlias + " has been updated.");
						m_notificationDialog->ShowModal();
					}
				}
			}
			else {
				UpdateDialogText(m_notificationDialog, "Invalid account information", "The account alias, username, and password must not be empty.");
				m_notificationDialog->ShowModal();
			}
		}
	}
	event.Skip();
}

void Main::OnMenuRemove(wxCommandEvent& event) {
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

void Main::OnMenuInfo(wxCommandEvent& event) {
	wxString selectedAlias = m_accountList->GetStringSelection();
	if (selectedAlias == "") {
		UpdateDialogText(m_notificationDialog, "No account selected", "You must select an account to display info.");
		m_notificationDialog->ShowModal();
	}
	else {
		auto [accountAlias, accountUsername, accountPassword, accountDescription] = ReadCredentials(selectedAlias);
		std::string accountInfo = std::format("Alias\n{}\n\nUsername\n{}\n\n{}", accountAlias, accountUsername, accountDescription);
		m_displayInfoDialog->SetMessage(accountInfo);
		m_displayInfoDialog->ShowModal();
	}
	event.Skip();
}

void Main::OnAccountDoubleClick(wxCommandEvent& event) {
	OnLoginClick(event);
	event.Skip();
}

void Main::OnLoginMouseOver(wxMouseEvent& event) {
	m_loginButton->SetBackgroundColour(menuItemHoverColor);
}

void Main::OnLoginMouseLeave(wxMouseEvent& event) {
	m_loginButton->SetBackgroundColour(menuItemBackgroundColor);
}