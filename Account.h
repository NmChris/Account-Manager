#pragma once
#include "wx/wx.h"

namespace Account {
	const LPSTR REGISTRY_PATH = LPSTR("SOFTWARE\\NmACM\\");

	void add_account(const wxString& alias, const wxString& username, const wxString& password);
	void remove_account(const wxString& alias);
	void get_login(const wxString &alias, wxString &username, wxString &password);
}