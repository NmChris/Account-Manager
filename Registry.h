#pragma once
#include "wx/wx.h"

class CRegistry {
private:
	HKEY m_regKey;

public:
	CRegistry(HKEY regKey, LPCSTR subKey) {
		LSTATUS errorStatus = RegCreateKeyExA(regKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_regKey, NULL);
		if (errorStatus != ERROR_SUCCESS)
			std::cout << "Error creating key" << subKey << "\nError: " << errorStatus << std::endl;
	}
	
	void createKey(HKEY regKey, LPCSTR subKey);

	void setValue(LPCSTR subKey, LPCSTR valueName, DWORD value);
	void setValue(LPCSTR subKey, LPCSTR valueName, wxString value);

	DWORD getValueDWORD(LPCSTR subKey, wxString valueName);
	std::wstring getValueString(LPCSTR subKey, wxString valueName);

	bool addSubKey(LPCSTR subKey);
	void deleteKey(LPCSTR subkey);
	std::vector<std::wstring> collectSubKeys();
};