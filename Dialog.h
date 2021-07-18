#pragma once
#include "wx/wx.h"
#include "Identifiers.h"


class wxMultipleTextDialog : public wxDialog {
public:
	wxMultipleTextDialog(wxWindow* parent, wxWindowID id, wxString title);

	void SetAliasValue(wxString alias) {
		m_aliasText->SetValue(alias);
	}

	wxString GetAliasValue() {
		return m_aliasText->GetValue();
	}

	void SetUsernameValue(wxString username) {
		m_usernameText->SetValue(username);
	}

	wxString GetUsernameValue() {
		return m_usernameText->GetValue();
	}

	void SetPasswordValue(wxString password) {
		m_passwordText->SetValue(password);
	}

	wxString getPasswordValue() {
		return m_passwordText->GetValue();
	}

	void SetDescriptionValue(wxString description) {
		m_descriptionText->SetValue(description);
	}

	wxString getDescriptionValue() {
		return m_descriptionText->GetValue();
	}

	std::tuple<wxString, wxString, wxString, wxString> GetValue() {
		return std::make_tuple(
			m_aliasText->GetValue(),
			m_usernameText->GetValue(),
			m_passwordText->GetValue(),
			m_descriptionText->GetValue()
		);
	}

	int ShowPositionedModal() {
		wxPoint parentPosition = m_parent->GetPosition();
		parentPosition.x = parentPosition.x + (m_parent->GetSize().x / 2 - this->GetSize().x / 2);
		parentPosition.y = parentPosition.y + (m_parent->GetSize().y / 2 - this->GetSize().y / 2);
		this->SetPosition(parentPosition);
		return this->ShowModal();
	}

private:
	wxWindow*	m_parent;
	wxTextCtrl* m_aliasText		= nullptr;
	wxTextCtrl* m_usernameText	= nullptr;
	wxTextCtrl* m_passwordText	= nullptr;
	wxTextCtrl* m_descriptionText = nullptr;

	void OnYesButtonClick(wxCommandEvent& event);
	void OnNoButtonClick(wxCommandEvent& event);

	// Event loop for custom dialog
	wxDECLARE_EVENT_TABLE();
};