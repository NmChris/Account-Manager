#include "Dialog.h"


wxBEGIN_EVENT_TABLE(wxMultipleTextDialog, wxDialog)
	EVT_BUTTON(UID::DIALOG_YES_BUTTON, OnYesButtonClick)
	EVT_BUTTON(UID::DIALOG_NO_BUTTON, OnNoButtonClick)
wxEND_EVENT_TABLE()

wxMultipleTextDialog::wxMultipleTextDialog(wxWindow* parent, wxWindowID id, wxString title, bool readOnly) : wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize), m_parent{parent} {
	// Create elements for the dialogue
	wxStaticText* aliasLabel		= new wxStaticText(this, wxID_ANY, "Alias");
	wxStaticText* usernameLabel		= new wxStaticText(this, wxID_ANY, "Username");
	wxStaticText* passwordLabel		= new wxStaticText(this, wxID_ANY, "Password");
	wxStaticText* descriptionLabel	= new wxStaticText(this, wxID_ANY, "Description");

	// Create sizers
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	// Generate buttons and text controls with custom styles
	if (readOnly == true) {
		m_aliasText			= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 25), wxTE_READONLY);
		m_usernameText		= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 25), wxTE_READONLY);
		m_passwordText		= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 25), wxTE_PASSWORD | wxTE_READONLY);
		m_descriptionText	= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 100), wxTE_MULTILINE | wxTE_READONLY | wxTE_NO_VSCROLL);

		wxButton* m_okButton = new wxButton(this, wxID_OK, "Ok", wxDefaultPosition, wxSize(250, 25));
		m_okButton->SetBackgroundColour(menuItemBackgroundColor);
		m_okButton->SetForegroundColour(menuItemForegroundColor);
		buttonSizer->Add(m_okButton, wxSizerFlags(1).Border());
	} else {
		m_aliasText			= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 25));
		m_usernameText		= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 25));
		m_passwordText		= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 25), wxTE_PASSWORD);
		m_descriptionText	= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 100), wxTE_MULTILINE | wxTE_NO_VSCROLL);

		wxButton* m_noButton = new wxButton(this, UID::DIALOG_NO_BUTTON, "No", wxDefaultPosition, wxSize(120, 25));
		wxButton* m_yesButton = new wxButton(this, UID::DIALOG_YES_BUTTON, "Yes", wxDefaultPosition, wxSize(120, 25));
		
		m_noButton->SetBackgroundColour(menuItemBackgroundColor);
		m_noButton->SetForegroundColour(menuItemForegroundColor);

		m_yesButton->SetBackgroundColour(menuItemBackgroundColor);
		m_yesButton->SetForegroundColour(menuItemForegroundColor);

		buttonSizer->Add(m_yesButton, wxSizerFlags(1).Border());
		buttonSizer->Add(m_noButton, wxSizerFlags(1).Border());
	}

	// Adjust object colors
	this->SetBackgroundColour(panelBackgroundColor);
	aliasLabel->SetForegroundColour(menuItemForegroundColor);
	usernameLabel->SetForegroundColour(menuItemForegroundColor);
	passwordLabel->SetForegroundColour(menuItemForegroundColor);
	descriptionLabel->SetForegroundColour(menuItemForegroundColor);
	m_aliasText->SetBackgroundColour(menuItemBackgroundColor);
	m_aliasText->SetForegroundColour(menuItemForegroundColor);
	m_usernameText->SetBackgroundColour(menuItemBackgroundColor);
	m_usernameText->SetForegroundColour(menuItemForegroundColor);
	m_passwordText->SetBackgroundColour(menuItemBackgroundColor);
	m_passwordText->SetForegroundColour(menuItemForegroundColor);
	m_descriptionText->SetBackgroundColour(menuItemBackgroundColor);
	m_descriptionText->SetForegroundColour(menuItemForegroundColor);

	// Append and apply sizers to the dialog
	dialogSizer->Add(aliasLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(m_aliasText, wxSizerFlags(0).Border());
	dialogSizer->Add(usernameLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(m_usernameText, wxSizerFlags(0).Border());
	dialogSizer->Add(passwordLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(m_passwordText, wxSizerFlags(0).Border());
	dialogSizer->Add(descriptionLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(m_descriptionText, wxSizerFlags(1).Border());

	dialogSizer->Add(buttonSizer);
	SetSizerAndFit(dialogSizer);
}

void wxMultipleTextDialog::OnYesButtonClick(wxCommandEvent& event) {
	if (this->IsModal() == true) {
		this->EndModal(wxID_YES);
	} else {
		this->SetReturnCode(wxID_YES);
		this->Hide();
	}
	event.Skip();
}

void wxMultipleTextDialog::OnNoButtonClick(wxCommandEvent& event) {
	if (this->IsModal() == true) {
		this->EndModal(wxID_NO);
	}
	else {
		this->SetReturnCode(wxID_NO);
		this->Hide();
	}
	event.Skip();
}