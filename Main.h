#pragma once
#include "wx/wx.h"

class Main : public wxFrame {
public:
	Main();

public:
	wxTextCtrl* m_alias			= nullptr;
	wxTextCtrl* m_username		= nullptr;
	wxTextCtrl* m_password		= nullptr;
	wxButton*	m_add_acc		= nullptr;
	wxButton*	m_remove_acc	= nullptr;
	wxListBox*	m_account_list	= nullptr;
	wxButton*	m_login			= nullptr;
	wxMessageDialog* m_message_dialog = nullptr;

	void on_add_account(wxCommandEvent &event);
	void on_remove_account(wxCommandEvent &event);
	void on_login(wxCommandEvent &event);
	void on_listbox_select(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

