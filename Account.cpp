#include "Account.h"

void LoginSteam(wxString username, wxString password) {
	// Get the steam.exe path to start the process
	std::string steamExePath = RegGetString("Software\\Valve\\Steam", "SteamExe");

	// Check if steam is running by getting it's process ID and shutting it down if it is running
	DWORD steamProcessID = RegGetDword("Software\\Valve\\Steam\\ActiveProcess", "pid");
	if (steamProcessID != 0) {
		HANDLE steamProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, steamProcessID);
		TerminateProcess(steamProcess, 0);
		CloseHandle(steamProcess);
	}

	// Create a steam process so that we can log in
    PROCESS_INFORMATION processInfo;
    STARTUPINFOA startupInfo = { sizeof(startupInfo) };
	std::string commandLine = std::format("steam.exe -login {} {}", username.ToStdString(), password.ToStdString());
    if (CreateProcessA(steamExePath.c_str(), LPSTR(commandLine.c_str()), NULL, NULL, FALSE, NULL, NULL, NULL, &startupInfo, &processInfo)) {
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
}