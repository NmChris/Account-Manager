#pragma once
#include "wx/wx.h"
#include <wincred.h>

void DeleteCredentials(wxString alias);
void WriteCredentials(wxString alias, wxString username, wxString password);

wxArrayString EnumerateCredentials();
std::tuple<wxString, wxString> ReadCredentials(wxString alias);