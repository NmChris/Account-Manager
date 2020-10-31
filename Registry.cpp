#include "Registry.h"
#define MAX_KEY_LENGTH 255

HKEY Registry::create_key(HKEY key, LPCSTR sub_key) {
    HKEY reg_key = NULL;
    LSTATUS create_status = RegCreateKeyExA(HKEY_CURRENT_USER, sub_key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg_key, NULL);
    if (create_status != ERROR_SUCCESS) {
        throw "Failed to create key " + create_status;
    }
    return reg_key;
}

void Registry::delete_key(HKEY key, LPCSTR sub_key) {
	LSTATUS delete_status = RegDeleteKeyA(key, sub_key);
    if (delete_status != ERROR_SUCCESS) {
        throw "Failed to delete key " + delete_status;
    }
}

void Registry::close_key(HKEY key) {
    LSTATUS close_status = RegCloseKey(key);
    if (close_status != ERROR_SUCCESS) {
        throw "Failed to close key " + close_status;
    }
}

void Registry::set_value_string(HKEY key, LPCSTR sub_key, LPCSTR value_name, wxString value) {
    LSTATUS set_status = RegSetKeyValueA(key, sub_key, value_name, REG_SZ, value, value.size() + 1);
    if (set_status != ERROR_SUCCESS) {
        throw "Failed to set value " + set_status;
    }
}

void Registry::set_value_dword(HKEY key, LPCSTR sub_key, LPCSTR value_name, DWORD value) {
    LSTATUS set_status = RegSetKeyValueA(key, sub_key, value_name, REG_DWORD, (const BYTE*)&value, sizeof(value));
    if (set_status != ERROR_SUCCESS) {
        throw "Failed to set value " + set_status;
    }
}

DWORD Registry::get_value_dword(HKEY key, LPCSTR sub_key, std::wstring value_name) {
    DWORD result(0);
    HKEY reg_key = NULL;
    LSTATUS open_status = RegOpenKeyA(key, sub_key, &reg_key);
    if (open_status == ERROR_SUCCESS) {
        DWORD buffer_size(sizeof(DWORD));
        LSTATUS query_status = RegQueryValueExW(reg_key, value_name.c_str(), 0, NULL, reinterpret_cast<LPBYTE>(&result), &buffer_size);
        RegCloseKey(reg_key);
        if (query_status != ERROR_SUCCESS) {
            throw "Error querying value ", query_status;
        }
        return result;
    } else {
        throw "Failed opening key ", open_status;
    }
    RegCloseKey(reg_key);
    return 0;
}

std::wstring Registry::get_value_string(HKEY key, LPCSTR sub_key, std::wstring value_name) {
    WCHAR buffer[512];
    HKEY reg_key = NULL;
    LSTATUS open_status = RegOpenKeyA(key, sub_key, &reg_key);
    if (open_status == ERROR_SUCCESS) {
        DWORD buffer_size = sizeof(buffer);
        LSTATUS query_status = RegQueryValueExW(reg_key, value_name.c_str(), 0, NULL, LPBYTE(buffer), &buffer_size);
        if (query_status != ERROR_SUCCESS) {
            throw "Error querying value ", query_status;
        }
        RegCloseKey(reg_key);
        return buffer;
    } else {
        throw "Failed opening key ", open_status;
    }
    RegCloseKey(reg_key);
    return buffer;
}

std::vector<std::wstring> Registry::get_sub_keys(HKEY key, LPCSTR sub_key) {
    HKEY reg_key = NULL;
    std::vector<std::wstring> sub_key_list;
    LSTATUS open_status = RegOpenKeyA(key, sub_key, &reg_key);
    if (open_status != ERROR_SUCCESS) {
        reg_key = create_key(key, sub_key);
    }
    TCHAR       key_name[MAX_KEY_LENGTH];   // Buffer for sub key name
    DWORD       key_size;                   // Size of name string
    DWORD       sub_keys = 0;               // Number of subkeys
    DWORD       max_sub_key;                // Longest subkey size
    FILETIME    last_write_Time;            // Last write time
    LSTATUS query_status = RegQueryInfoKeyA(reg_key, NULL, NULL, NULL, &sub_keys, &max_sub_key, NULL, NULL, NULL, NULL, NULL, &last_write_Time);
    if (query_status != ERROR_SUCCESS) {
        RegCloseKey(reg_key);
        throw "Error querying info ";
    }
    if (sub_key <= 0) {
        RegCloseKey(reg_key);
        return sub_key_list;
    }
    for (DWORD i = 0; i < sub_keys; i++) {
        key_size = MAX_KEY_LENGTH;
        LSTATUS enum_status = RegEnumKeyEx(reg_key, i, key_name, &key_size, NULL, NULL, NULL, &last_write_Time);
        if (enum_status == ERROR_SUCCESS) {
            sub_key_list.push_back(key_name);
        }
    }
    RegCloseKey(reg_key);
    return sub_key_list;
}