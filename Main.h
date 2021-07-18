#pragma once
#include "wx/wx.h"
#include "wx/artprov.h"
#include "Dialog.h"
#include "Account.h"
#include "Identifiers.h"
#include "Credentials.h"
#include <format>

class Main : public wxFrame {
public:
	Main();
private:
	wxButton* m_loginButton = nullptr;
	wxListBox* m_accountList = nullptr;

	wxMessageDialog* m_confirmationDialog = nullptr;
	wxMessageDialog* m_notificationDialog = nullptr;
	wxMessageDialog* m_displayInfoDialog = nullptr;
	wxMultipleTextDialog* m_accountInfoDialog = nullptr;
	
	wxColor panelBackgroundColor = wxColor(35, 35, 35, 255);
	wxColor menuItemHoverColor = wxColor(60, 60, 60, 255);
	wxColor menuItemBackgroundColor = wxColor(50, 50, 50, 255);
	wxColor menuItemForegroundColor = wxColor(225, 225, 225, 255);

	void OnLoginClick(wxCommandEvent& event);
	void OnMenuAdd(wxCommandEvent& event);
	void OnMenuEdit(wxCommandEvent& event);
	void OnMenuRemove(wxCommandEvent& event);
	void OnMenuInfo(wxCommandEvent& event);
	void OnAccountDoubleClick(wxCommandEvent& event);
	void OnLoginMouseOver(wxMouseEvent& event);
	void OnLoginMouseLeave(wxMouseEvent& event);

	void UpdateDialogText(wxMessageDialog* dialog, wxString title, wxString message) {
		dialog->SetTitle(title);
		dialog->SetMessage(message);
	}

	wxDECLARE_EVENT_TABLE();
};