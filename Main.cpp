#include "App.h"
#include "Main.h"
#include "Account.h"
#include "Identifiers.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_BUTTON(UID::ADD_ACCOUNT_BUTTON, on_add_account)
	EVT_BUTTON(UID::REMOVE_ACCOUNT_BUTTON, on_remove_account)
	EVT_BUTTON(UID::LOGIN_BUTTON, on_login)
	EVT_LISTBOX(UID::ACCOUNT_LISTBOX, on_account_select)
	EVT_LISTBOX_DCLICK(UID::ACCOUNT_LISTBOX, on_account_double_click)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Account manager", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX ^ wxRESIZE_BORDER) {
	wxArrayString account_array = wxArrayString();
	Account::init(&account_array);

	// Initialize the dialog popup
	m_message_dialog = new wxMessageDialog(this, "", "Confirm the following action", wxYES_NO | wxCENTRE | wxSTAY_ON_TOP, wxDefaultPosition);

	// Initialize frame panels
	wxPanel* left_panel = new wxPanel(this, wxID_ANY);
	wxPanel* right_panel = new wxPanel(this, wxID_ANY);

	// Initialize account list and login GUI elements
	m_login = new wxButton(left_panel, UID::LOGIN_BUTTON, "Login", wxDefaultPosition, wxSize(300, 30));
	m_account_list = new wxListBox(left_panel, UID::ACCOUNT_LISTBOX, wxDefaultPosition, wxSize(300, 300), account_array, wxLB_SORT);

	// Initialize account information elements
	m_alias = new wxTextCtrl(right_panel, UID::ALIAS_TEXTBOX, "");
	m_username = new wxTextCtrl(right_panel, UID::USERNAME_TEXTBOX, "");
	m_password = new wxTextCtrl(right_panel, UID::PASSWORD_TEXTBOX, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	m_add_acc = new wxButton(right_panel, UID::ADD_ACCOUNT_BUTTON, "Add", wxDefaultPosition, wxSize(120, 30));
	m_remove_acc = new wxButton(right_panel, UID::REMOVE_ACCOUNT_BUTTON, "Remove");

	// Initialize static labels
	wxStaticText* alias_label = new wxStaticText(right_panel, wxID_ANY, "Account alias");
	wxStaticText* username_label = new wxStaticText(right_panel, wxID_ANY, "Username");
	wxStaticText* password_label = new wxStaticText(right_panel, wxID_ANY, "Password");

	// Adjust panel background colors
	left_panel->SetBackgroundColour(wxColor(171, 171, 171, 255)); // prev value 171
	right_panel->SetBackgroundColour(wxColor(171, 171, 171, 255));

	// Initialize sizers
	wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* info_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* account_sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);

	// Add GUI elements to sizers
	info_sizer->Add(m_account_list, wxSizerFlags(1).Expand().Border(wxALL, 10));
	info_sizer->Add(m_login, wxSizerFlags(0).Expand().Border(wxALL, 10));

	account_sizer->Add(alias_label, wxSizerFlags(0).Border(wxLEFT | wxRIGHT | wxTOP, 10));
	account_sizer->Add(m_alias, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
	account_sizer->Add(username_label, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));
	account_sizer->Add(m_username, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
	account_sizer->Add(password_label, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));
	account_sizer->Add(m_password, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
	account_sizer->Add(m_remember, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));

	button_sizer->Add(m_add_acc, wxSizerFlags(1).Expand().Border(wxALL, 10));
	button_sizer->Add(m_remove_acc, wxSizerFlags(1).Expand().Border(wxALL, 10));

	account_sizer->AddSpacer(163);
	account_sizer->Add(button_sizer, wxSizerFlags().Bottom());

	panel_sizer->Add(left_panel, wxSizerFlags(1).Expand().Border(wxRIGHT | wxBOTTOM, 10));
	panel_sizer->Add(right_panel, wxSizerFlags(0).Expand().Border(wxRIGHT, 10));

	// Apply sizers
	SetSizerAndFit(account_sizer);
	SetSizerAndFit(info_sizer);
	SetSizerAndFit(panel_sizer);
}

void Main::on_add_account(wxCommandEvent &event) {
	wxString alias		= m_alias->GetValue();
	wxString username	= m_username->GetValue();
	wxString password	= m_password->GetValue();

	int alias_length	= alias.length();
	int username_length = username.length();
	int password_length = password.length();
	
	if (alias_length > 0 && username_length > 0 && password_length > 0) {
		if (m_account_list->FindString(alias) == -1) {
			m_account_list->AppendString(alias);
			Account::add(alias, username, password);
		} else {
			m_message_dialog->SetMessage("Are you sure you want to edit this account?");
			if (m_message_dialog->ShowModal() == wxID_YES) {
				Account::add(alias, username, password);
			}
		}
	} else {
		wxString error_message = "Cannot add account. The following fields are empty: \n";

		if (alias_length == 0)
			error_message += "alias, ";
		if (username_length == 0)
			error_message += "username, ";
		if (password_length == 0)
			error_message += "password, ";

		m_message_dialog->SetMessage(error_message.substr(0, error_message.length() - 2));
		m_message_dialog->ShowModal();
	}
	event.Skip();
}

void Main::on_remove_account(wxCommandEvent &event) {
	const int account_index = m_account_list->GetSelection();
	if (account_index >= 0) {
		wxString alias = m_account_list->GetStringSelection();
		m_message_dialog->SetMessage("Are you sure you want to remove " + alias + " from the account list?");
		if (m_message_dialog->ShowModal() == wxID_YES) {
			m_alias->Clear();
			m_username->Clear();
			m_password->Clear();

			Account::remove(alias);
			m_account_list->Delete(account_index);
		}
	} else {
		m_message_dialog->SetMessage("Select an account to remove.");
		m_message_dialog->ShowModal();
	}
	event.Skip();
}

void Main::on_login(wxCommandEvent &event) {
	if (m_account_list->GetSelection() >= 0) {
		wxString alias = m_account_list->GetStringSelection();
		wxString username = Account::get_username(alias);
		wxString password = Account::get_password(alias);
		Account::login(username, password);
	} else {
		m_message_dialog->SetMessage("Select an account to log in to. ");
		m_message_dialog->ShowModal();
	}
	event.Skip();
}

void Main::on_account_select(wxCommandEvent &event) {
	wxString alias = m_account_list->GetStringSelection();
	wxString username = Account::get_username(alias);
	wxString password = Account::get_password(alias);

	m_alias->SetValue(alias);
	m_username->SetValue(username);
	m_password->SetValue(password);
}

void Main::on_account_double_click(wxCommandEvent &event) {
	if (m_account_list->GetSelection() >= 0) {
		wxString alias = m_account_list->GetStringSelection();
		wxString username = Account::get_username(alias);
		wxString password = Account::get_password(alias);
		Account::login(username, password);
	}
	else {
		m_message_dialog->SetMessage("Select an account to log in to. ");
		m_message_dialog->ShowModal();
	}
	event.Skip();
}