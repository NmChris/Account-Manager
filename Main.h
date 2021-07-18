#pragma once
#include "wx/wx.h"
#include "Account.h"
#include "Dialog.h"
#include "Identifiers.h"
#include "wx/artprov.h"
#include "Credentials.h"

class Main : public wxFrame {
public:
	Main();
private:
	wxListBox* m_accountList = nullptr;
	wxMessageDialog* m_confirmationDialog = nullptr;
	wxMessageDialog* m_notificationDialog = nullptr;
	wxMultipleTextDialog* m_accountInfoDialog = nullptr;

	void OnLoginClick(wxCommandEvent& event);
	void OnToolAdd(wxCommandEvent& event);
	void OnToolRemove(wxCommandEvent& event);
	void OnAccountDoubleClick(wxCommandEvent& event);

	void UpdateDialogText(wxMessageDialog* dialog, wxString title, wxString message) {
		dialog->SetTitle(title);
		dialog->SetMessage(message);
	}

	wxDECLARE_EVENT_TABLE();
};