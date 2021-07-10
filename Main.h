#pragma once
#include "wx/wx.h"
#include "Account.h"
#include "Dialog.h"

class Main : public wxFrame {
public:
	Main();

public:
	CAccountManager m_accountManager;

	wxListBox*	m_accountList	= nullptr;
	wxButton*	m_login			= nullptr;
	wxMessageDialog* m_messageDialog = nullptr;

	//void AddAccount(wxCommandEvent &event);
	//void RemoveAccount(wxCommandEvent &event);
	void Login(wxCommandEvent &event);
	//void AccountSelected(wxCommandEvent &event);
	void AccountDoubleClicked(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};