#include "Credentials.h"

std::tuple<wxString, wxString> ReadCredentials(wxString alias) {
	std::string targetName = "Account Manager:" + alias.ToStdString();

	PCREDENTIALA credentials;
	BOOL readSuccessful = CredReadA(targetName.c_str(), CRED_TYPE_GENERIC, 0, &credentials);
	if (readSuccessful == FALSE) {
		return {
			"Empty username",
			"Empty password"
		};
	} else {
		return {
			std::string(credentials->UserName),
			std::string(LPSTR(credentials->CredentialBlob))
		};
	}
}

void WriteCredentials(wxString alias, wxString username, wxString password) {
	std::string targetName = "Account Manager:" + alias.ToStdString();

	CREDENTIALA credentials { 0 };
	credentials.Flags				= 0;
	credentials.Type				= CRED_TYPE_GENERIC;
	credentials.Persist				= CRED_PERSIST_LOCAL_MACHINE;
	credentials.TargetName			= LPSTR(targetName.c_str());
	credentials.TargetAlias			= LPSTR(alias.c_str().AsChar());
	credentials.UserName			= LPSTR(username.c_str().AsChar());
	credentials.CredentialBlob		= LPBYTE(password.c_str().AsChar());
	credentials.CredentialBlobSize	= password.length();
	CredWriteA(&credentials, 0);
}

void DeleteCredentials(wxString alias) {
	std::string targetName = "Account Manager:" + alias.ToStdString();
	CredDeleteA(targetName.c_str(), CRED_TYPE_GENERIC, 0);
}

wxArrayString EnumerateCredentials() {
	DWORD count = 0;
	PCREDENTIALA* credentials;
	CredEnumerateA("Account Manager:*", 0, &count, &credentials);
	
	wxArrayString accountArray = wxArrayString();
	for (int i = 0; i < count; i++) {
		std::cout << credentials[i]->TargetName << std::endl;
		accountArray.Add(credentials[i]->TargetAlias);
	}
	return accountArray;
}