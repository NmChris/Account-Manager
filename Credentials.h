#pragma once
#include "wx/wx.h"
#include <wincred.h>

void DeleteCredentials(wxString alias);
void WriteCredentials(wxString alias, wxString username, wxString password, wxString description);

wxArrayString EnumerateCredentials();
std::tuple<wxString, wxString, wxString, wxString> ReadCredentials(wxString alias);