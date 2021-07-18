#pragma once
#include <Windows.h>
#include <winreg.h>
#include <string>
#include <stdexcept>


DWORD RegGetDword(std::string subKey, std::string value);
std::string RegGetString(std::string subKey, std::string value);