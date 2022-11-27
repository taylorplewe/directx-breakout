#include <windows.h>
#include "w_boiler.h"

const wchar_t WINDOW_CLASS_NAME[] = L"breakout_main";
const wchar_t WINDOW_TITLE[] = L"Direct2D Breakout - Taylor Plewe (ESC to exit)";

void w_boiler::SetClass(HINSTANCE hInstance, WNDPROC WindowProc) {
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	RegisterClass(&wc);
}

void w_boiler::CreateAndShowMainWindow(HINSTANCE hInstance, int nCmdShow, WNDPROC WindowProc) {
	SetClass(hInstance, WindowProc);
	HWND hwnd = CreateWindowEx(
		0,						// Optional window styles
		WINDOW_CLASS_NAME,		// Window class
		WINDOW_TITLE,			// Window text
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,	// Window style
		//WS_OVERLAPPEDWINDOW,

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, Datastore::WINDOW_SIZE.cx, Datastore::WINDOW_SIZE.cy,

		NULL,		// Parent window
		NULL,		// Menu
		hInstance,	// Handle to instance
		NULL		// Additional application data????
	);

	ShowWindow(hwnd, nCmdShow);
	ds->m_hwnd = hwnd;
}