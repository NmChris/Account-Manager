#include "App.h"
#include "Main.h"
#include "Account.h"
#include "Identifiers.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_BUTTON(UID::ADD_ACCOUNT_BUTTON, on_add_account)
	EVT_BUTTON(UID::REMOVE_ACCOUNT_BUTTON, on_remove_account)
	EVT_BUTTON(UID::LOGIN_BUTTON, on_login)
	EVT_LISTBOX(UID::ACCOUNT_LISTBOX, on_listbox_select)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Account manager", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX^ wxRESIZE_BORDER) {
	// Initialize the dialog popup
	m_message_dialog = new wxMessageDialog(this, "", "Confirm the following action", wxYES_NO | wxCENTRE | wxSTAY_ON_TOP, wxDefaultPosition);

	// Initialize frame panels
	wxPanel* left_panel = new wxPanel(this, wxID_ANY);
	wxPanel* right_panel = new wxPanel(this, wxID_ANY);

	// Initialize account list and login GUI elements
	m_login			= new wxButton(left_panel, UID::LOGIN_BUTTON, "Login", wxDefaultPosition, wxSize(300, 30));
	m_account_list	= new wxListBox(left_panel, UID::ACCOUNT_LISTBOX, wxDefaultPosition, wxSize(300, 300));
	

	// Initialize account information elements
	m_alias		= new wxTextCtrl(right_panel, UID::ALIAS_TEXTBOX, "");
	m_username	= new wxTextCtrl(right_panel, UID::USERNAME_TEXTBOX, "");
	m_password	= new wxTextCtrl(right_panel, UID::PASSWORD_TEXTBOX, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	m_add_acc	= new wxButton(right_panel, UID::ADD_ACCOUNT_BUTTON, "Add", wxDefaultPosition, wxSize(120, 30));
	m_remove_acc = new wxButton(right_panel, UID::REMOVE_ACCOUNT_BUTTON, "Remove");

	// Initialize static labels
	wxStaticText* alias_label = new wxStaticText(right_panel, wxID_ANY, "Account alias");
	wxStaticText* username_label = new wxStaticText(right_panel, wxID_ANY, "Username");
	wxStaticText* password_label = new wxStaticText(right_panel, wxID_ANY, "Password");

	// Adjust panel background colors
	left_panel->SetBackgroundColour(wxColor(171, 171, 171, 255));
	right_panel->SetBackgroundColour(wxColor(171, 171, 171, 255));

	// Initialize sizers
	wxBoxSizer* panel_sizer		= new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* info_sizer		= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* account_sizer	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* button_sizer	= new wxBoxSizer(wxHORIZONTAL);

	// Add GUI elements to sizers
	info_sizer->Add(m_account_list, wxSizerFlags(1).Expand().Border(wxALL, 10));
	info_sizer->Add(m_login, wxSizerFlags(0).Expand().Border(wxALL, 10));

	account_sizer->Add(alias_label, wxSizerFlags(0).Border(wxLEFT | wxRIGHT | wxTOP, 10));
	account_sizer->Add(m_alias, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
	account_sizer->Add(username_label, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));
	account_sizer->Add(m_username, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
	account_sizer->Add(password_label, wxSizerFlags(0).Border(wxLEFT | wxRIGHT, 10));
	account_sizer->Add(m_password, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));

	button_sizer->Add(m_add_acc, wxSizerFlags(1).Expand().Border(wxALL, 10));
	button_sizer->Add(m_remove_acc, wxSizerFlags(1).Expand().Border(wxALL, 10));

	account_sizer->AddSpacer(163);
	account_sizer->Add(button_sizer);

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

	if (alias.length() > 0 && username.length() > 0 && password.length() > 0) {
		if (m_account_list->FindString(alias) == -1) {
			m_account_list->AppendString(alias);
			Account::add_account(alias, username, password);
		} else {
			m_message_dialog->SetMessage("Are you sure you want to edit this account?");
			if (m_message_dialog->ShowModal() == wxID_YES) {
				Account::add_account(alias, username, password);
			}
		}
	}
	event.Skip();
}

void Main::on_remove_account(wxCommandEvent &event) {
	const int selection = m_account_list->GetSelection();
	if (selection >= 0) {
		m_message_dialog->SetMessage("Are you sure you want to remove the following account?");
		if (m_message_dialog->ShowModal() == wxID_YES) {
			m_alias->Clear();
			m_username->Clear();
			m_password->Clear();
			m_account_list->Delete(selection);
			Account::remove_account(m_account_list->GetStringSelection());
		}
	}
	event.Skip();
}

void Main::on_login(wxCommandEvent &event) {
	wxString username;
	wxString password;
	wxString alias = m_account_list->GetStringSelection();

	Account::get_login(alias, username, password);
	std::cout << username << std::endl;
	// TODO: Stop current steam process or logout
	// TODO: Use Windows SendMessage to enter the accounts password
	event.Skip();
}

void Main::on_listbox_select(wxCommandEvent &event) {
	m_alias->SetValue(m_account_list->GetStringSelection());
	m_username->Clear(); // TODO: fetch username from account info
	m_password->Clear();
}