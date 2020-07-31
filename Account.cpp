#include "Account.h"

void Account::add_account(const wxString &alias, const wxString &username, const wxString &password) {
	HKEY hkey = NULL;
	LSTATUS create_status = RegCreateKeyExA(HKEY_CURRENT_USER, REGISTRY_PATH + alias.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | DELETE, NULL, &hkey, NULL);
	if (create_status == ERROR_SUCCESS && hkey != NULL) {
		RegSetKeyValueA(hkey, NULL, LPSTR("Username"), REG_SZ, username, username.size() + 1);
		RegSetKeyValueA(hkey, NULL, LPSTR("Password"), REG_SZ, password, password.size() + 1);
		RegCloseKey(hkey);
	}
}

void Account::remove_account(const wxString &alias) {
	LSTATUS delete_status = RegDeleteTreeW(HKEY_CURRENT_USER, REGISTRY_PATH + alias.c_str());
	std::cout << delete_status << std::endl;
	if (delete_status == ERROR_SUCCESS) {
		std::cout << "Successfully delted registry key.\n";
	}
}

void Account::get_login(const wxString &alias, wxString &username, wxString &password) {

}