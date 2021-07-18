#pragma once
#include <Windows.h>
#include <iostream>

void SetClipboard(std::string data) {
	if (!OpenClipboard(NULL)) {
		std::cout << "Failed to open clipboard" << std::endl; 
		return;
	}
	EmptyClipboard();
	HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 64);
	strcpy_s((char*)hGlob, 64, data.c_str());
	if (SetClipboardData(CF_TEXT, hGlob) == NULL) {
		std::cout << "Set clipboard data failed" << std::endl;
		CloseClipboard();
		GlobalFree(hGlob);
		return;
	}
	CloseClipboard();
}