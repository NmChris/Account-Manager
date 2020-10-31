#include "Account.h"
#include "Registry.h"

void Account::init(wxArrayString* account_array) {
    HKEY legacy_key;
    LSTATUS legacy_status = RegOpenKeyA(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH_LEGACY, &legacy_key);
    if (legacy_status == ERROR_SUCCESS) {
        std::vector<std::wstring> sub_keys = Registry::get_sub_keys(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH_LEGACY);
        for (const std::wstring& key : sub_keys) {
            std::wstring username = Registry::get_value_string(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH_LEGACY + key, L"Username");
            std::wstring password = Registry::get_value_string(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH_LEGACY + key, L"Password");
            Account::add(key, username, password);
        }
        RegDeleteTreeA(legacy_key, NULL);
        RegDeleteKeyA(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH_LEGACY);
    }

    std::vector<std::wstring> sub_keys = Registry::get_sub_keys(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH);
    for (const std::wstring &key : sub_keys) {
        account_array->Add(Encryption::decrypt(std::string(key.begin(), key.end())));
    }
}

void Account::add(const wxString &alias, const wxString &username, const wxString &password) {
    wxString alias_encrypted = Encryption::encrpyt(alias.ToStdString());
    HKEY reg_key = Registry::create_key(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH + alias_encrypted.c_str());
    Registry::set_value_string(reg_key, NULL, "f1", Encryption::encrpyt(username.ToStdString()));
    Registry::set_value_string(reg_key, NULL, "f2", Encryption::encrpyt(password.ToStdString()));
    Registry::close_key(reg_key);
}

void Account::remove(const wxString &alias) {
    wxString alias_encrypted = Encryption::encrpyt(alias.ToStdString());
    Registry::delete_key(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH + alias_encrypted.c_str());
}

wxString Account::get_username(const wxString &alias) {
    wxString alias_decrypted = Encryption::encrpyt(alias.ToStdString());
    std::wstring username = Registry::get_value_string(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH + alias_decrypted.c_str(), L"f1");
    return Encryption::decrypt(std::string(username.begin(), username.end()));
}

wxString Account::get_password(const wxString &alias) {
    wxString alias_decrypted = Encryption::encrpyt(alias.ToStdString());
    std::wstring password = Registry::get_value_string(HKEY_CURRENT_USER, ACCOUNT_REGISTRY_PATH + alias_decrypted.c_str(), L"f2");
    return Encryption::decrypt(std::string(password.begin(), password.end()));
}

void Account::login(const wxString &username, const wxString &password) {
    // Get the steam.exe path to start the process
    std::wstring steam_path = Registry::get_value_string(HKEY_CURRENT_USER, STEAM_REGISTRY_PATH, L"SteamExe");

    // Check if steam is running by getting it's process ID and shutting it down if it is running
    DWORD process_id = Registry::get_value_dword(HKEY_CURRENT_USER, STEAM_ACTIVE_PROCESS, L"pid");
    if (process_id != 0) {
        HANDLE steam_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
        TerminateProcess(steam_process, 0);
        CloseHandle(steam_process);
    }

    // Create a steam process so that we can log in
    PROCESS_INFORMATION process_info;
    STARTUPINFO startup_info = { sizeof(startup_info) };
    wxString command_line = "steam.exe -login " + username + " " + password;
    if (CreateProcessW(steam_path.c_str(), LPWSTR(command_line.wc_str()), NULL, NULL, FALSE, NULL, NULL, NULL, &startup_info, &process_info)) {
        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);
    }
}