#include "Registry.h"
#define MAX_KEY_LENGTH 255

void CRegistry::createKey(HKEY regKey, LPCSTR subKey) {
    HKEY resultKey;
    LSTATUS createStatus = RegCreateKeyExA(regKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &resultKey, NULL);
    if (createStatus != ERROR_SUCCESS) {
        std::cout << "Error creating key: " << subKey << "\n Error code: " << createStatus << std::endl;
    }
}

bool CRegistry::addSubKey(LPCSTR subKey) {
    HKEY regSubKey;
    LSTATUS createStatus = RegCreateKeyExA(m_regKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &regSubKey, NULL);
    if (createStatus != ERROR_SUCCESS) {
        std::cout << "Error creating subkey " << subKey << "\nError: " << createStatus << std::endl;
        RegCloseKey(regSubKey);
        return false;
    }
    return true;
}

void CRegistry::deleteKey(LPCSTR subKey) {
    LSTATUS deleteStatus = RegDeleteKeyA(m_regKey, subKey);
    if (deleteStatus != ERROR_SUCCESS)
        std::cout << "Error deleting subkey " << subKey << "\nError: " << deleteStatus << std::endl;
}

void CRegistry::setValue(LPCSTR subKey, LPCSTR valueName, wxString value) {
    LSTATUS setStatus = RegSetKeyValueA(m_regKey, subKey, valueName, REG_SZ, value, value.size() + 1);
    if (setStatus != ERROR_SUCCESS)
        std::cout << "Error setting string value: " << valueName << "\nError: "<< setStatus << std::endl;
}

void CRegistry::setValue(LPCSTR subKey, LPCSTR valueName, DWORD value) {
    LSTATUS setStatus = RegSetKeyValueA(m_regKey, subKey, valueName, REG_DWORD, (const BYTE*)&value, sizeof(value));
    if (setStatus != ERROR_SUCCESS)
        std::cout << "Error setting DWORD value: " << valueName << "\nError: " << setStatus << std::endl;
}

DWORD CRegistry::getValueDWORD(LPCSTR subKey, wxString valueName) {
    DWORD result(0);
    DWORD bufferSize(sizeof(DWORD));

    HKEY regKey;
    LSTATUS openStatus = RegOpenKeyA(m_regKey, subKey, &regKey);
    if (openStatus != ERROR_SUCCESS) {
        std::cout << "Error opening key: " << subKey << "\nError: " << openStatus << std::endl;
    }

    LSTATUS queryStatus = RegQueryValueExW(regKey, valueName.c_str(), 0, NULL, reinterpret_cast<LPBYTE>(&result), &bufferSize);
    if (queryStatus != ERROR_SUCCESS)
        std::cout << "Error getting dword value: " << valueName << "\nError: " << queryStatus << std::endl;

    return result;
}

std::wstring CRegistry::getValueString(LPCSTR subKey, wxString valueName) {
    WCHAR result[512];
    DWORD bufferSize = sizeof(result);

    HKEY regKey;
    LSTATUS openStatus = RegOpenKeyA(m_regKey, subKey, &regKey);
    if (openStatus != ERROR_SUCCESS) {
        std::cout << "Error opening key: " << subKey << "\nError: " << openStatus << std::endl;
    }

    LSTATUS queryStatus = RegQueryValueExW(regKey, valueName.c_str(), 0, NULL, LPBYTE(result), &bufferSize);
    if (queryStatus != ERROR_SUCCESS)
        std::cout << "Error getting dword value: " << valueName << "\nError: " << queryStatus << std::endl;

    return result;
}

std::vector<std::wstring> CRegistry::collectSubKeys() {
    TCHAR       keyName[MAX_KEY_LENGTH];   // Buffer for sub key name
    DWORD       keySize;                   // Size of name string
    DWORD       subKeys = 0;               // Number of subkeys
    DWORD       maxSubKeys;                // Longest subkey size
    FILETIME    lastWriteTime;            // Last write time

    std::vector<std::wstring> subKeyList;
    LSTATUS queryStatus = RegQueryInfoKeyA(m_regKey, NULL, NULL, NULL, &subKeys, &maxSubKeys, NULL, NULL, NULL, NULL, NULL, &lastWriteTime);

    if (queryStatus != ERROR_SUCCESS)
        std::cout << "Error query key " << "\nError: " << queryStatus << std::endl;
    if (subKeys <= 0)
        return subKeyList;

    for (DWORD i = 0; i < subKeys; i++) {
        keySize = MAX_KEY_LENGTH;
        LSTATUS enumStatus = RegEnumKeyEx(m_regKey, i, keyName, &keySize, NULL, NULL, NULL, &lastWriteTime);
        if (enumStatus == ERROR_SUCCESS)
            subKeyList.push_back(keyName);
    }
    return subKeyList;
}