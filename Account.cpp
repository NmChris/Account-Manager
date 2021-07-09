#include "Account.h"

void CAccountManager::getAccounts(wxArrayString* accountArray) {
    std::vector<std::wstring> subKeys = m_accountRegistry.collectSubKeys();
    for (const std::wstring& key : subKeys) {
        accountArray->Add(Encryption::decrypt(std::string(key.begin(), key.end())));
    }
}

void CAccountManager::addAccount(wxString& alias, wxString& username, wxString& password) {
    wxString encryptedAlias = Encryption::encrpyt(alias.ToStdString());
    if (m_accountRegistry.addSubKey(encryptedAlias) == true) {
        m_accountRegistry.setValue(encryptedAlias, "f1", Encryption::encrpyt(username.ToStdString()));
        m_accountRegistry.setValue(encryptedAlias, "f2", Encryption::encrpyt(password.ToStdString()));
    }
}

void CAccountManager::removeAccount(wxString& alias) {
    wxString encryptedAlias = Encryption::encrpyt(alias.ToStdString());
    m_accountRegistry.deleteKey(encryptedAlias);
}

wxString CAccountManager::getAccountUsername(wxString& alias) {
    wxString encryptedAlias = Encryption::encrpyt(alias.ToStdString());
    std::wstring accountUsername = m_accountRegistry.getValueString(encryptedAlias.c_str(), L"f1");
    return Encryption::decrypt(std::string(accountUsername.begin(), accountUsername.end()));
}

wxString CAccountManager::getAccountPassword(wxString& alias) {
    wxString encryptedAlias = Encryption::encrpyt(alias.ToStdString());
    std::wstring accountPassword = m_accountRegistry.getValueString(encryptedAlias.c_str(), L"f2");
    return Encryption::decrypt(std::string(accountPassword.begin(), accountPassword.end()));
}

void CAccountManager::loginToAccount(wxString &username, wxString &password) {
    // Get the steam.exe path to start the process
    std::wstring steamPath = m_steamRegistry.getValueString(NULL, L"SteamExe");

    // Check if steam is running by getting it's process ID and shutting it down if it is running
    DWORD processID = m_steamActiveProcess.getValueDWORD(NULL, L"pid");
    if (processID != 0) {
        HANDLE steamProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
        TerminateProcess(steamProcess, 0);
        CloseHandle(steamProcess);
    }

    // Create a steam process so that we can log in
    PROCESS_INFORMATION processInfo;
    STARTUPINFO startupInfo = { sizeof(startupInfo) };
    wxString commandLine = "steam.exe -login " + username + " " + password;
    if (CreateProcessW(steamPath.c_str(), LPWSTR(commandLine.wc_str()), NULL, NULL, FALSE, NULL, NULL, NULL, &startupInfo, &processInfo)) {
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
}