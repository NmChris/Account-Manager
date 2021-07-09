#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	// DEBUG CONSOLE
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	m_frame = new Main();
	m_frame->Show();

	return true;
}