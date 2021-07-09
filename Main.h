#pragma once
#include "wx/wx.h"
#include "Account.h"

class Main : public wxFrame {
public:
	Main();

public:
	CAccountManager m_accountManager;

	wxTextCtrl* m_alias			= nullptr;
	wxTextCtrl* m_username		= nullptr;
	wxTextCtrl* m_password		= nullptr;
	wxButton*	m_addAccount	= nullptr;
	wxButton*	m_removeAccount	= nullptr;
	wxListBox*	m_accountList	= nullptr;
	wxButton*	m_login			= nullptr;
	wxMessageDialog* m_messageDialog = nullptr;

	void AddAccount(wxCommandEvent &event);
	void RemoveAccount(wxCommandEvent &event);
	void Login(wxCommandEvent &event);
	void AccountSelected(wxCommandEvent &event);
	void AccountDoubleClicked(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};