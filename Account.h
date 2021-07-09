#pragma once
#include "wx/wx.h"
#include "Registry.h"
#include "Encryption.h"

class CAccountManager {
private:
	CRegistry m_accountRegistry = CRegistry(HKEY_CURRENT_USER, LPCSTR("SOFTWARE\\CleanWow64\\"));
	CRegistry m_steamRegistry	= CRegistry(HKEY_CURRENT_USER, LPCSTR("SOFTWARE\\Valve\\Steam\\"));
	CRegistry m_steamActiveProcess = CRegistry(HKEY_CURRENT_USER, LPCSTR("SOFTWARE\\Valve\\Steam\\ActiveProcess"));

public:
	void loginToAccount(wxString &username, wxString &password);
	void addAccount(wxString &alias, wxString &username, wxString &password);
	void removeAccount(wxString &alias);

	void getAccounts(wxArrayString* accountArray);
	wxString getAccountUsername(wxString &alias);
	wxString getAccountPassword(wxString &alias);
};