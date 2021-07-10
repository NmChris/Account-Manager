#pragma once
#include "wx/wx.h"

class wxMultipleTextDialog : public wxDialog {
public:
	wxMultipleTextDialog(wxWindow* parent, wxWindowID id, wxString title);

	void SetAliasValue(wxString alias) {
		aliasText->SetValue(alias);
	}

	wxString GetAliasValue() {
		return aliasText->GetValue();
	}

	void SetUsernameValue(wxString username) {
		usernameText->SetValue(username);
	}

	wxString GetUsernameValue() {
		return usernameText->GetValue();
	}

	void SetPasswordValue(wxString password) {
		passwordText->SetValue(password);
	}

	wxString getPasswordValue() {
		return passwordText->GetValue();
	}

	std::tuple<wxString, wxString, wxString> GetValue() {
		return std::make_tuple(
			aliasText->GetValue(), 
			usernameText->GetValue(), 
			passwordText->GetValue()
		);
	}

private:
	wxTextCtrl* aliasText		= nullptr;
	wxTextCtrl* usernameText	= nullptr;
	wxTextCtrl* passwordText	= nullptr;

	void OnYesButtonClick(wxCommandEvent& event);
	void OnNoButtonClick(wxCommandEvent& event);

	// Event loop for custom dialog
	wxDECLARE_EVENT_TABLE();
};