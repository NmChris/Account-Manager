#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	m_frame = new Main();
	m_frame->SetIcon(wxIcon(wxIconLocation("lock.ico")));
	m_frame->Show();

	// DEBUG CONSOLE
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	return true;
}