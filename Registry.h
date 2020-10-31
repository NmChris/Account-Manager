#pragma once
#include "wx/wx.h"

namespace Registry {
	void close_key(HKEY key);
	HKEY create_key(HKEY key, LPCSTR sub_key);
	void delete_key(HKEY key, LPCSTR sub_key);
	std::vector<std::wstring> get_sub_keys(HKEY key, LPCSTR sub_key);

	void set_value_dword(HKEY key, LPCSTR sub_key, LPCSTR value_name, DWORD value);
	void set_value_string(HKEY key, LPCSTR sub_key, LPCSTR value_name, wxString value);
	DWORD get_value_dword(HKEY key, LPCSTR sub_key, std::wstring value_name);
	std::wstring get_value_string(HKEY key, LPCSTR sub_key, std::wstring value_name);
}

class CRegistry {
private:
	HKEY m_regKey;

public:
	CRegistry();
	~CRegistry();
};