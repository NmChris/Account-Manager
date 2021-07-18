#include "Registry.h"

class RegistryError : public std::runtime_error {
public:
    RegistryError(const char* message, LONG errorCode) : std::runtime_error{ message }, m_errorCode{ errorCode } {};
private:
    LONG m_errorCode;
};

DWORD RegGetDword(std::string subKey, std::string value) {
    DWORD data{};
    DWORD dataSize = sizeof(data);

    LONG returnCode = RegGetValueA(HKEY_CURRENT_USER, subKey.c_str(), value.c_str(), RRF_RT_REG_DWORD, nullptr, &data, &dataSize);
    if (returnCode != ERROR_SUCCESS) {
        throw RegistryError{ "Failed to read DWORD.", returnCode };
    }
    return data;
}

std::string RegGetString(std::string subKey, std::string value) {
    DWORD dataSize{};

    LONG returnCode = RegGetValueA(HKEY_CURRENT_USER, subKey.c_str(), value.c_str(), RRF_RT_REG_SZ, nullptr, nullptr, &dataSize);
    if (returnCode != ERROR_SUCCESS) {
        throw RegistryError{ "Failed to read string from registry.", returnCode };
    }

    std::string data;
    data.resize(dataSize / sizeof(char));

    returnCode = RegGetValueA (HKEY_CURRENT_USER, subKey.c_str(), value.c_str(), RRF_RT_REG_SZ, nullptr, &data[0], &dataSize);
    if (returnCode != ERROR_SUCCESS) {
        throw RegistryError{ "Failed to read string from registry.", returnCode };
    }

    DWORD stringLengthInChars = (dataSize / sizeof(char)) - 1;
    data.resize(stringLengthInChars);

    return data;
}