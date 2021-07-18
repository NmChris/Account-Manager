#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	/*AllocConsole();
	freopen("CONOUT$", "w", stdout);*/

	m_frame = new Main();
	m_frame->SetIcon(wxIcon(wxIconLocation("lock.ico")));
	m_frame->Show();
	return true;
}