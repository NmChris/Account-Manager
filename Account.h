#pragma once
#include "wx/wx.h"
#include "Encryption.h"

namespace Account {
	const LPSTR ACCOUNT_REGISTRY_PATH	= LPSTR("SOFTWARE\\CleanWow64\\");
	const LPSTR STEAM_REGISTRY_PATH		= LPSTR("SOFTWARE\\Valve\\Steam");
	const LPSTR STEAM_ACTIVE_PROCESS	= LPSTR("SOFTWARE\\Valve\\Steam\\ActiveProcess");
	const LPSTR ACCOUNT_REGISTRY_PATH_LEGACY = LPSTR("SOFTWARE\\NmACM\\");
	
	void init(wxArrayString* account_array);
	void add(const wxString &alias, const wxString &username, const wxString &password);
	void login(const wxString &username, const wxString &password);
	void remove(const wxString &alias);

	wxString get_username(const wxString &alias);
	wxString get_password(const wxString &alias);
}