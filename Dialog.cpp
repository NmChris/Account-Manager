#include "wx/wx.h"
#include "Dialog.h"
#include "Identifiers.h"

wxBEGIN_EVENT_TABLE(wxMultipleTextDialog, wxDialog)
	EVT_BUTTON(UID::DIALOG_YES_BUTTON, OnYesButtonClick)
	EVT_BUTTON(UID::DIALOG_NO_BUTTON, OnNoButtonClick)
wxEND_EVENT_TABLE()

wxMultipleTextDialog::wxMultipleTextDialog(wxWindow* parent, wxWindowID id, wxString title) : wxDialog(parent, id, title) {
	// Create elements for the dialogue
	aliasText					= new wxTextCtrl(this, wxID_ANY);
	usernameText				= new wxTextCtrl(this, wxID_ANY);
	passwordText				= new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	wxButton* m_yesButton		= new wxButton(this, UID::DIALOG_YES_BUTTON, "Yes");
	wxButton* m_noButton		= new wxButton(this, UID::DIALOG_NO_BUTTON, "No");
	wxStaticText* aliasLabel	= new wxStaticText(this, wxID_ANY, "Account alias");
	wxStaticText* usernameLabel = new wxStaticText(this, wxID_ANY, "Username");
	wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, "Password");

	// Create sizers
	wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	// Append and apply sizers to the dialog
	dialogSizer->Add(aliasLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(aliasText, wxSizerFlags(1).Border());
	dialogSizer->Add(usernameLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(usernameText, wxSizerFlags(1).Border());
	dialogSizer->Add(passwordLabel, wxSizerFlags().Border(wxLEFT | wxRIGHT | wxTOP));
	dialogSizer->Add(passwordText, wxSizerFlags(1).Border());
	buttonSizer->Add(m_yesButton, wxSizerFlags(1).Border());
	buttonSizer->Add(m_noButton, wxSizerFlags(1).Border());
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