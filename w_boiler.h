#pragma once
#include <windows.h>
#include "Datastore.h"

class w_boiler
{
	Datastore* ds;
	void SetClass(HINSTANCE hInstance, WNDPROC WindowProc);
public:
	w_boiler(Datastore* ds) { this->ds = ds; }
	~w_boiler() {}
	void CreateAndShowMainWindow(HINSTANCE hInstance, int nCmdShow, WNDPROC WindowProc);
};

